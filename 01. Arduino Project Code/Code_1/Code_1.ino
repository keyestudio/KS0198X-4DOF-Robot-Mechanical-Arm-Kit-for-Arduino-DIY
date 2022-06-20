#include <Servo.h>
Servo myservo;  // create servo object to control a servo

void setup()
{
  Serial.begin(9600); 
  delay(1000);
}

void loop() 
{
  myservo.attach(A0);  // modify each pin to adjust 
  myservo.write(0);  // angle value  
  delay(1000);
}
