#include <PS2X_lib.h>

PS2X ps2x; // create PS2 Controller Class


//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte vibrate = 0;

#include <Servo.h>  // add the servo libraries 
Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;

int pos1=80, pos2=60, pos3=130, pos4=0;  // define the variable of 4 servo angle and assign the initial value( that is the boot posture angle value)

void setup(){
 Serial.begin(57600);

// boot posture
  myservo1.write(pos1);  
  delay(1000);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  delay(1500);
  
 error = ps2x.config_gamepad(13,11,10,12);   //setup GamePad(clock, command, attention, data) pins, check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
   //Serial.print(ps2x.Analog(1), HEX);
 
 
 ps2x.enableRumble();              //enable rumble vibration motors
 ps2x.enablePressures();           //enable reading the pressure values from the buttons. 
  

  
}

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */

  myservo1.attach(A1);  // set the control pin of servo 1 to A1
  myservo2.attach(A0);  // set the control pin of servo 2 to A0
  myservo3.attach(6);   // set the control pin of servo 3 to D6
  myservo4.attach(9);   // set the control pin of servo 4 to D9
  
 if(error != 0)
  return; 
  
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
  
  if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
       Serial.println("Start is being held");
  if(ps2x.Button(PSB_SELECT))
       Serial.println("Select is being held");
       
       
   if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
     Serial.print("Up held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
     Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
     Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
     Serial.print("DOWN held this hard: ");
   Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   

  
    vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                            //how hard you press the blue (X) button    
  
  if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
  {
      if(ps2x.Button(PSB_R3))
        
       Serial.println("R3 pressed");
     
       
      if(ps2x.Button(PSB_L3))
       Serial.println("L3 pressed");
      
      if(ps2x.Button(PSB_L2))
       Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
       Serial.println("R2 pressed");
      if(ps2x.Button(PSB_GREEN))
       Serial.println("Triangle pressed");
       
  }   
       
  
  if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
       Serial.println("Circle just pressed");
       
  if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
       Serial.println("Square just released");     
  
  if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
       Serial.println("X just changed");    

    //转动
    zhuandong();
    //爪子
    zhuazi();
    //大臂
    dabi();
    //小臂
    xiaobi();
    
  if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
  {
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
  }    
  delay(5);    
}
//********************************************************************
// turn
void zhuandong()
{
//turn right
   if(ps2x.Analog (PSS_RX) > 200)  // if push the right joystick to the right 
    {
      //Serial.println(ps2x.Analog(PSS_RX), DEC);
      pos1=pos1-1;    //pos1 subtracts 1
      myservo1.write(pos1);   // servo 1 executes the action, the arm will turn right.
      // delay(5);
      if(pos1<1)   // limit the right turning angle 
      {
        pos1=1;
      }
     }
      // turn left
     if(ps2x.Analog (PSS_RX) < 50)    // if push the right joystick to the left
     {
       //Serial.println(ps2x.Analog(PSS_RX), DEC);
       pos1=pos1+1;   //pos1 plus 1
       myservo1.write(pos1);     // the arm turns left 
       // delay(5);
       if(pos1>180)     // limit the left turning angle
       {
         pos1=180;
       }
     }
 }
 //**********************************************************************  
 // upper arm 
void xiaobi()
{
  //upper arm front
   if(ps2x.Analog(PSS_RY)<50)  // if push the right joystick upward
   {
      pos2=pos2-1;
      myservo2.write(pos2);    // the upper arm will lift
      delay(5);
      if(pos2<0)    // limit the lifting angle
      {
        pos2=0;
      }
    }
    //upper arm back
    if(ps2x.Analog(PSS_RY)>200)    // if push the right joystick downward
    {
      pos2=pos2+1;
      myservo2.write(pos2);   // the upper arm will go down
      delay(5);
      if(pos2>180)  // limit the declining angle
      {
        pos2=180;
      }
    }
}
//***************************************************************
void zhuazi()
{
// close the claw
   if(ps2x.Analog(PSS_LX)>220)   // if push the left joystick to the right
   {
      pos4=pos4-1;
      Serial.println(pos4);
      myservo4.write(pos4);  // servo 4 carries out the action and the claw is gradually closed.
      delay(5);
      if(pos4<0)   // if pos4 value subtracts to 37, the claw in 37 degrees we have tested is closed.）
      {
        pos4=0;
      }
    }
    // open the claw
    if(ps2x.Analog(PSS_LX)<10)   // if push the left joystick to the left
    {
      pos4=pos4+8;
      Serial.println(pos4);
      myservo4.write(pos4);   // servo 4 carries out the action and the claw is gradually opened
      delay(5);
      if(pos4>108)    // limit the maximum opening angle 
      {
        pos4=108;
      }
    }
} 
//*********************************************************
void dabi()
{
  // lower arm front
  if(ps2x.Analog(PSS_LY)>200)  // if push the left joystick upward
  {
    pos3=pos3+1;
    myservo3.write(pos3);  // the lower arm will stretch out
    delay(5);
    if(pos3>180)   // limit the stretched angle
    {
      pos3=180;
    }
   }
  if(ps2x.Analog(PSS_LY)<10)    //if push the left joystick downward
  {
    pos3=pos3-1;
    myservo3.write(pos3);   // the lower arm will draw back
    delay(5);
    if(pos3<35)    // limit the retracted angle
    {
      pos3=35;
    }
   }
}
