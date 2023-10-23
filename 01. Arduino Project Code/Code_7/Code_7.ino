#include <Servo.h>  //  add the servo libraries
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;  
int pos1=80, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)
const int right_X = A2; //  define the right X pin to A2 
const int right_Y = A5; //  define the right Y pin to A5 
const int right_key = 7; // define the right key pin to 7（that is Z value）

const int left_X = A3; //define the left X pin to A3
const int left_Y = A4;  // define the left Y pin to A4
const int left_key = 8; // define the left key pin to 8（that is Z value）

int x1,y1,z1;  // define the variable, used to save the joystick value.
int x2,y2,z2;
int s1,s2,s3,s4;
int jiyi1[20];  //define 4 array, separately used to save the angle of four servo.
int jiyi2[20];  // （array length is 20，namely can save angle data of 0~20 servo）
int jiyi3[20];  //if need to save more data, just change the number 20 to be more larger number.
int jiyi4[20];
int i=0;  // for loop
int j=0;  //  save the last value of i

void setup() 
{
  // boot posture
  myservo1.write(pos1);  //turn servo 1 to 90 degrees
  delay(1000);
  myservo2.write(pos2);  // turn servo 2 to 90 degrees
  myservo3.write(pos3);  // turn servo 3 to 120 degrees
  myservo4.write(pos4);  // turn servo 4 to 35 degrees 
  delay(1500);
    
  
  pinMode(right_key, INPUT);   // set the right/left key to INOUT
  pinMode(left_key, INPUT);
  Serial.begin(9600);   // set the baud rate to 9600
}

void loop() 
{
  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  // set the control pin of servo 2 to A0
  myservo3.attach(6);   //set the control pin of servo 3 to D6
  myservo4.attach(9);   // set the control pin of servo 4 to D9
  
  x1 = analogRead(right_X); // read the right X value
  y1 = analogRead(right_Y);  //read the right Y value
  z1 = digitalRead(right_key);  //read the right Z value 
  
  x2 = analogRead(left_X);  //  read the left X value
  y2 = analogRead(left_Y);  // read the left Y value
  z2 = digitalRead(left_key);  // read the left Z value
  //delay(5);  // delay, used to reduce the joystick value read, that is reduce the whole speed.
  if(z1==1)   // if the joystick right key is pressed
  {
    delay(10);  // delay for eliminating shake 
    if(z1==1)   // judge again if the right key is pressed
    {
      s1=myservo1.read();  // read the angle value of servo 1 and assign it to s1
      delay(100);
      Serial.println(s1); // print out the angle value of servo 1 on the serial monitor
      s2=myservo2.read();  //  read the angle value of servo 2 and assign it to s2
      delay(100);
      Serial.println(s2);
      s3=myservo3.read();   //  read the angle value of servo 3 and assign it to s3
      delay(100);
      Serial.println(s3);
      s4=myservo4.read();   // read the angle value of servo 4 and assign it to s4 
      delay(100);
      Serial.println(s4);
       
      jiyi1[i]=s1;  // Save the read servo value to the array sequentially
      jiyi2[i]=s2;
      jiyi3[i]=s3;
      jiyi4[i]=s4;
      i++;   //i plus 1
      j=i;   // assign the last value of i to j
      delay(100);  // delay 100ms
      Serial.println(i);  // print out the value i
    }
  }
  if(z2==1) //  if the left joystick key is pressed
  {
    delay(10);  // delay for eliminating shake 
    if(z2==1)   //judge again if the left key is pressed 
    {
      pos1 = myservo1.read();  // memorize the angle value of 4 servo posture
      pos2 = myservo2.read();
      pos3 = myservo3.read();
      pos4 = myservo4.read();
      
      while(z2==1)  // loop, make the arm repeat the action.
      {
        for(int k=1;k<j;k++)  //for loop, perform all the stored actions.
        {
          if(pos1<jiyi1[k])   // if the current servo 1 angle is less than the value stored in array 1.
          {
            while(pos1<jiyi1[k])  //while loop, make servo turn to the position of value stored in the array.
            {
              myservo1.write(pos1);  //servo 1 performs the action 
              delay(5);   //delay 5ms，controlling the servo rotating speed.
              pos1++;   //pos1 plus 1
              //Serial.println(pos1);
            }
          }
          else   //if the current servo 1 angle is greater than the value stored in array 1.
          {
           while(pos1>jiyi1[k])    //while loop, make servo turn to the position of value stored in the array.
            {
              myservo1.write(pos1);  //servo 1 performs the action
              delay(5);   //delay 5ms，controlling the servo rotating speed.
              pos1--;   //pos1 subtracts 1
              //Serial.println(pos1);
            }
          }
  //***************************************************************
  //the explanation is the same as the previous servo. 
          if(pos2<jiyi2[k])
          {
            while(pos2<jiyi2[k])
            {
              myservo2.write(pos2);
              delay(5);
              pos2++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos2>jiyi2[k])
            {
              myservo2.write(pos2);
              delay(5);
              pos2--;
              //Serial.println(pos1);
            }
          }
   //*********************************************
   //the explanation is the same as the previous servo.
          if(pos3<jiyi3[k])
          {
            while(pos3<jiyi3[k])
            {
              myservo3.write(pos3);
              delay(5);
              pos3++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos3>jiyi3[k])
            {
              myservo3.write(pos3);
              delay(5);
              pos3--;
              //Serial.println(pos1);
            }
          }
//*********************************************
//the explanation is the same as the previous servo.
          if(pos4<jiyi4[k])
          {
            while(pos4<jiyi4[k])
            {
              myservo4.write(pos4);
              delay(5);
              pos4++;
              //Serial.println(pos1);
            }
          }
          else
          {
           while(pos4>jiyi4[k])
            {
              myservo4.write(pos4);
              delay(5);
              pos4--;
              //Serial.println(pos1);
            }
          }
        }
//************************************************************
// for exiting the loop
            z1 = digitalRead(right_key);  // read the right Z value
            if(z1==1)  // if the right key is pressed
            {
              delay(10);  //eliminate the shake
              if(z1==1)  // if the key z1 is pressed
              {
                pos1=jiyi1[(j-1)];  // assign the last angle value saved in array to pos
                pos2=jiyi2[(j-1)];  // for exiting the loop, still access to joystick control.
                pos3=jiyi3[(j-1)];  
                pos4=jiyi4[(j-1)];
                i=0;  // assign i as 0，prepare for saving the angle value using array
                z2=0; // assign z2 as 0，for exiting the while loop
                break;  //exit the current loop
              }
            }
//********************************************************
      }
    }
  }
  
  //claw
  zhuazi();
  //turn
  zhuandong();
  //upper arm
  xiaobi();
  //lower arm
  dabi();
}


//claw
void zhuazi()
{
    //claw
  if(x2<50) // if push the left joystick to the right 
  {
      pos4=pos4-2;  // angle of servo 4, subtract 2 (change the value you subtract, thus change the closed speed of claw)
      //Serial.println(pos4);
      myservo4.write(pos4);  //  servo 4 operates the motion and claw is gradually closed.
      delay(5);
      if(pos4<2)  // if pos4 value subtracts to 2, the claw in 37 degrees we have tested is closed.）
      {            //（should change the value based on the fact）
        pos4=2;   //stop subtraction when reduce to 2
      }
   }
  if(x2>1000) ////if push the left joystick to the left
  {
      pos4=pos4+8; //current angle of servo 4 plus 8（change the value you plus, thus change the open speed of claw）
      //Serial.println(pos4);
      myservo4.write(pos4); // servo 4 operates the action, claw gradually opens.
      delay(5);
      if(pos4>90)  //limit the largest angle opened
      {
        pos4=90;
      }
  }
}
//******************************************************
 //turn
void zhuandong()
{
  if(x1<50)  //if push the right joystick to the right 
  {
    pos1=pos1-1;  //pos1 subtracts 1
    myservo1.write(pos1);  // servo 1 performs the action, the robot arm turns right.
    delay(5);
    if(pos1<1)   // limit the right turning angle 
    {
      pos1=1;
    }
  }
  if(x1>1000)  // if push the right joystick to the left
  {
    pos1=pos1+1;  //pos1 plus 1
    myservo1.write(pos1);  //the robot arm turns left.
    delay(5);
    if(pos1>180)  //limit the left turning angle 
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
    myservo2.write(pos2); // the robot arm will lift
    delay(5);
    if(pos2<0)  // limit the lifting angle 
    {
      pos2=0;
    }
  }
  if(y1<50)  // if push the right joystick downward
  {
    pos2=pos2+1;  
    myservo2.write(pos2);  // the robot arm will go down
    delay(5);
    if(pos2>180)  // limit the declining angle 
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
    if(pos3<35)  // limit the stretched angle 
    {
      pos3=35;
    }
  }
  
  if(y2<50)  // if push the right joystick downward
  {
    pos3=pos3+1;
    myservo3.write(pos3);  // the lower arm will draw back
    delay(5);
    if(pos3>180)   // limit the retraction angle 
    {
      pos3=180;
    }
  }  
}
