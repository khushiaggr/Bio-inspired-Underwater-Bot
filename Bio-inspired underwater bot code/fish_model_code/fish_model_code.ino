//Including the required libraries 
#include <Servo.h>
#include <IBusBM.h>

//Creating ibus object
IBusBM ibus;

//Creating servo object
Servo myservo1;
Servo myservo2;

int pos = 0;

// Channel Values
int rcCH1 = 0; //direction
int rcCH3 = 0; // flapping of the tail
 

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup()
{
//Start serial monitor for debugging
   Serial.begin(115200);
//Attach iBus object to serial port
   ibus.begin(Serial1);

//Connecting servos.
  myservo1.attach(12);
  myservo2.attach(13);
}
 
void loop() {
 
// Get RC channel values
  rcCH1 = readChannel(0, -100, 100, 0);
  rcCH3 = readChannel(2, -100, 100, -100);
  
// Print values to serial monitor for debugging
  Serial.print("Ch1 = ");
  Serial.print(rcCH1);
  Serial.print("|");
  Serial.print("Ch3 = ");
  Serial.print(rcCH3);
  Serial.print("\n");

// Direcetion control of bot
if ((rcCH1 < -50) && (rcCH1 >= -100)){
     myservo1.write(55); }
       
else if ((rcCH1 > 50) && (rcCH1 <=100)){
     myservo1.write(125); }
       
else{
   myservo1.write(90); } 
 
// Flapping of tail
if (rcCH3 > 0){ 
  for (pos = 90; pos <= 135; pos += 5) { // goes from 90 degrees to 135 degrees
    myservo2.write(pos);              
    delay(20);                       }
  for (pos = 135; pos >= 90; pos -= 5) { // goes from 135 degrees to 90 degrees
    myservo2.write(pos);              
    delay(20);                       } 
  for (pos = 90; pos >= 45; pos -= 5) { // goes from 90 degrees to 45 degrees
    myservo2.write(pos);              
    delay(20);                       } 
  for (pos = 45; pos <= 90; pos += 5) { // goes from 45 degrees to 90 degrees
    myservo2.write(pos);              
    delay(20);                       } 
  }
else{ 
    myservo2.write(90);}
}
