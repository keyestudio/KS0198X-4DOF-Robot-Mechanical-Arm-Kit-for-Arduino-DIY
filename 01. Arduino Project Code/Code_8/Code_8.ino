void setup() 
{
  Serial.begin(9600);     // set the serial baud rate to 9600
}

void loop()
{
  char val;    // define a variable, used to receive the value read from Bluetooth.
  if(Serial.available())     // if receive the value 
  {
    val = Serial.read();       // assign the value read to val
    Serial.println(val);
  }
}
