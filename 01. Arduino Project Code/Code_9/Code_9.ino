#include <Servo.h>  // add the servo libraries
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos1=80, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)
char val;
char val2;

void setup()
{
   // boot posture
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);

  Serial.begin(9600); //  set the baud rate to 9600
}

void loop() 
{
  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  // set the control pin of servo 2 to A0
  myservo3.attach(6);   // set the control pin of servo 3 to D6
  myservo4.attach(9);   // set the control pin of servo 4 to D9

  if(Serial.available())   // if receive the data
  {
    val=Serial.read();    // read the received data
    val2=val;             //Give the value of val to val2
    Serial.println(val);
   
    switch(val)   
    {
      case 'L':  T_left();  break;   // execute the corresponding function when receive the value 
      case 'R':  T_right();  break;
      case 'f':  RF();  break;
      case 'b':  rb();  break;
      case 'F':  ZK();  break;
      case 'B':  ZB();  break;
      case 'l':  LF();  break;
      case 'r':  lb();  break;
      case 'S':  servo_stop();  break;       //stop instruction 
    }

  }
  else
  {
      switch(val2)                //When the button is pressed and not released, 
     {                            //"else" is executed because Bluetooth does not send characters,
                                  // and the value of val2 is the value of the previously pressed button, 
                                  //so the command of pressing the button will be repeated
    
      case 'L':  T_left();  break;   // execute the corresponding function when receive the value 
      case 'R':  T_right();  break;
      case 'f':  RF();  break;
      case 'b':  rb();  break;
      case 'F':  ZK();  break;
      case 'B':  ZB();  break;
      case 'l':  LF();  break;
      case 'r':  lb();  break;
      case 'S':  servo_stop();  break;     //stop instruction 
    }
   }
}
//**************************************************
// turn left
void T_left()
{
    pos1=pos1+1;
    myservo1.write(pos1);
    delay(5);
    if(pos1>180)
    {
      pos1=180;
    }
}
//turn right 
void T_right()
{
    pos1=pos1-1;
    myservo1.write(pos1);
    delay(5);
    if(pos1<1)
    {
      pos1=1;
    }
}
//********************************************
//open the claw
void ZK()
{
      pos4=pos4-2;
      Serial.println(pos4);
      myservo4.write(pos4);
      delay(5);
      if(pos4<2)
      {
        pos4=0;
      }
}
// close the claw
void ZB()
{
    pos4=pos4+8;
      Serial.println(pos4);
      myservo4.write(pos4);
      delay(5);
      if(pos4>108)
      {
        pos4=108;
      }
}

//******************************************
// the upper arm will lift up 
void RF()
{
    pos2=pos2-1;
    myservo2.write(pos2);
    delay(5);
    if(pos2<0)
    {
      pos2=0;
    }
}
// the upper arm will go down 
void rb()
{
    pos2=pos2+1;
    myservo2.write(pos2);
    delay(5);
    if(pos2>180)
    {
      pos2=180;
    }
}

//***************************************
// the lower arm will stretch out 
void lb()
{
  pos3=pos3+1;
    myservo3.write(pos3);
    delay(5);
    if(pos3>180)
    {
      pos3=180;
    }
}
// the lower arm will draw back 
void LF()
{
  pos3=pos3-1;
    myservo3.write(pos3);
    delay(5);
    if(pos3<35)
    {
      pos3=35;
    }
}

void servo_stop()
{
   
    myservo1.write(pos1);
    myservo2.write(pos2);
    myservo3.write(pos3); 
    myservo4.write(pos4);
   
}
