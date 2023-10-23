#include <Servo.h>  // add servo libraries
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;  
int pos1=80, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)

const int right_X = A2; // define the right X pin to A2 
const int right_Y = A5; // define the right Y pin to A3 
const int right_key = 7; // define the right key pin to 7（that is Z value）

const int left_X = A3; // define the left X pin to A3
const int left_Y = A4;  // define the left Y pin to A4
const int left_key = 8; // define the left key pin to 8（that is Z value）

int x1,y1,z1;  // define the variable, used to save the joystick value.
int x2,y2,z2;
int s1,s2,s3,s4;

void setup() 
{
  // boot posture
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);
    
  
  pinMode(right_key, INPUT);   // set the right/left key to INPUT 
  pinMode(left_key, INPUT);
  Serial.begin(9600); //  set the baud rate to 9600
}

void loop() 
{
  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  // set the control pin of servo 2 to A0
  myservo3.attach(6);   //set the control pin of servo 3 to D6
  myservo4.attach(9);   //set the control pin of servo 4 to D9
  
  x1 = analogRead(right_X); // read the right X value
  y1 = analogRead(right_Y);  // read the right Y value
  z1 = digitalRead(right_key);  //// read the right key Z value
  
  x2 = analogRead(left_X);  // read the left X value
  y2 = analogRead(left_Y);  //read the left Y value
  z2 = digitalRead(left_key);  //read the left key Z value
  //delay(5);  // reduce the speed overall
  if(z1==1)  // if the right joystick key is pressed
  {
    delay(10);  // delay for eliminating shake 
    if(z1==1)    // judge again if the right key is pressed
    {
      s1=myservo1.read();  // read the angle value of each servo 
      s2=myservo2.read();
      s3=myservo3.read();
      s4=myservo4.read();
    }
  }
  if(z2==1) // if the left key is pressed
  {
    delay(10);
    if(z2==1)
    {
        pos1=myservo1.read();  // record the angle value of 4 servos in current posture
        pos2=myservo2.read();
        pos3=myservo3.read();
        pos4=myservo4.read();

        if(pos1<s1)  // if angle of servo 1 is smaller than variable s1 value
        {
          while(pos1<s1)  //while loop，rotate the servo to the position of the value stored in the array.
          {
            myservo1.write(pos1); // servo 1 operates the motion
            pos1++;  //pos1 plus 1
            delay(5);  // delay for 5ms，controlling the rotation speed of servo. 
          }
          
        }
        else  // if angle of servo 1 is greater than the value stored in array 1.
        {
          while(pos1>s1)     //while loop,rotate the servo to the position of the value stored in the array.
          {
            myservo1.write(pos1);  //  servo 1 operates the motion
            pos1--;     //pos1 subtracts 1
            delay(5);   // delay for 5ms，controlling the rotation speed of servo.
          }
        }
      //*************************************************  
      // the explanation is the same as servo 1 
        if(pos2<s2)
        {
          while(pos2<s2)
          {
            myservo2.write(pos2);
            pos2++;
            delay(5);
          }
        }
        else
        {
          while(pos2>s2)
          {
            myservo2.write(pos2);
            pos2--;
            delay(5);
          }
        }
     //*************************************************  
      // the explanation is the same as servo 1
        if(pos3<s3)
        {
          while(pos3<s3)
          {
            myservo3.write(pos3);
            pos3++;
            delay(5);
          }
        }
        else
        {
          while(pos3>s3)
          {
            myservo3.write(pos3);
            pos3--;
            delay(5);
          }
        }
      //*************************************************  
      // the explanation is the same as servo 1
        if(pos4<s4)
        {
          while(pos4<s4)
          {
            myservo4.write(pos4);
            pos4++;
            delay(5);
          }
        }
        else
        {
          while(pos4>s4)
          {
            myservo4.write(pos4);
            pos4--;
            delay(5);
          }
        }
        
    }
  }
  
  //claw
  zhuazi();
  //turn
  zhuandong();
  // upper arm 
  xiaobi();
  // lower arm
  dabi();
}


//claw
void zhuazi()
{
    //claw
  if(x2<50) // if push the left joystick to the right
  {
      pos4=pos4-2;  // current angle of servo 4 subtracts 2（change the value you subtract, thus change the closed speed of claw）
      //Serial.println(pos4);
      myservo4.write(pos4);  //servo 4 operates the action, claw is gradually closed
      delay(5);
      if(pos4<2)  // if pos4 value subtracts to 2, the claw in 37 degrees we have tested is closed.）
      {            //（should change the value based on the fact）
        pos4=2;   // stop subtraction when reduce to 2
      }
   }
  if(x2>1000) //// if push the left joystick to the left 
  {
      pos4=pos4+8; // current angle of servo 4 plus 8（change the value you plus, thus change the open speed of claw）
      //Serial.println(pos4);
      myservo4.write(pos4); //  servo 4 operates the motion, the claw gradually opens. 
      delay(5);
      if(pos4>90)  // limit the largest angle when open 
      {
        pos4=90;
      }
  }
}
//******************************************************
 // turn
void zhuandong()
{
  if(x1<50)  // if push the right joystick to the right 
  {
    pos1=pos1-1;  //pos1 subtracts 1
    myservo1.write(pos1);  // servo 1 operates the motion, the arm turns right. 
    delay(5);
    if(pos1<1)   //  limit the angle when turn right
    {
      pos1=1;
    }
  }
  if(x1>1000)  // if push the right joystick to the left
  {
    pos1=pos1+1;  //pos1 plus 1
    myservo1.write(pos1);  // robot arm turns left
    delay(5);
    if(pos1>180)  // limit the angle when turn left 
    {
      pos1=180;
    }
  }
}

//**********************************************************/
// upper arm
void xiaobi()
{
    if(y1>1000) // if push the right joystick upward 
  {
    pos2=pos2-1;
    myservo2.write(pos2); // the upper arm will lift 
    delay(5);
    if(pos2<0)  // limit the lifting angle
    {
      pos2=0;
    }
  }
  if(y1<50)  // if push the right joystick downward 
  {
    pos2=pos2+1;  
    myservo2.write(pos2);  // the upper arm will go down 
    delay(5);
    if(pos2>180)  // limit the angle when go down 
    {
      pos2=180;
    }
  }
}

//*************************************************************/
// lower arm
void dabi()
{
  if(y2>1000)  // if push the left joystick upward 
  {
    pos3=pos3-1;
    myservo3.write(pos3);  // the lower arm will stretch out
    delay(5);
    if(pos3<35)  //  limit the stretched angle
    {
      pos3=35;
    }
  }
  
  if(y2<50)  // if push the left joystick downward
  {
    pos3=pos3+1;
    myservo3.write(pos3);  // the lower arm will draw back 
    delay(5);
    if(pos3>180)   // limit the retracted angle 
    {
      pos3=180;
    }
  }  
}
