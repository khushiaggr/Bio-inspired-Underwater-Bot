//Include the required libraries
#include "CytronMotorDriver.h"
#include <Servo.h>
#include <IBusBM.h>

// Creating ibus object
IBusBM ibus;

//Creating servo object
Servo myservo1;
Servo myservo2;

// Configure the motor driver.
CytronMD motor1(PWM_DIR, 3, 4);  // PWM = Pin 3, DIR = Pin 4
CytronMD motor2(PWM_DIR, 5, 6);  // PWM = Pin 5, DIR = Pin 6

// Channel Values
 int rcCH1 = 0;
 int rcCH2 = 0; 
 int rcCH4 = 0;

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void setup()
{
// Start serial monitor for debugging
  Serial.begin(115200);
// Attach iBus object to serial port
  ibus.begin(Serial1);

// connecting servos.
  myservo1.attach(8);
  myservo2.attach(9);
}
 
void loop() {
 
  // Get RC channel values
  rcCH1 = readChannel(0, -100, 100, 0);
  rcCH2 = readChannel(1, -100, 100, 0);
  rcCH4 = readChannel(3, -100, 100, 0);
  
 // Print values to serial monitor for debugging
  Serial.print("Ch1 = ");
  Serial.print(rcCH1);
  Serial.print("Ch2 = ");
  Serial.print(rcCH2);
  Serial.print("Ch4 = ");
  Serial.print(rcCH4);
  Serial.print("\n");
  delay(100);

// For right motor control
if ((rcCH1 > 0) && (rcCH1 <= 50)){
    motor1.setSpeed(128); }
if ((rcCH1 > 50) && (rcCH1 <= 100)){
    motor1.setSpeed(225); }
if ((rcCH1 < 0) && (rcCH1 >= -50)){
    motor1.setSpeed(-128); }
if ((rcCH1 < -50) && (rcCH1 >= -100)){
    motor1.setSpeed(-225); }
else{
    motor1.setSpeed(0); } 

// For left motor control
if ((rcCH2 > 0) && (rcCH2 <= 50)){
    motor2.setSpeed(128); }
if ((rcCH2 > 50) && (rcCH2 <= 100)){
    motor2.setSpeed(225); }
if ((rcCH2 < 0) && (rcCH2 >= -50)){
    motor2.setSpeed(-128); }
if ((rcCH2 < -50) && (rcCH2 >= -100)){
    motor2.setSpeed(-225); }
else{
    motor2.setSpeed(0); } 

// For direction control
if ((rcCH4 > 0) && (rcCH4 <= 50)){
    myservo1.write(25);  
    myservo2.write(25);    }
if ((rcCH4 > 50) && (rcCH4 <= 100)){
    myservo1.write(45);  
    myservo2.write(45);    }
if ((rcCH4 < 0) && (rcCH4 >= -50)){
    myservo1.write(-25);  
    myservo2.write(-25);    }
if ((rcCH4 < -50) && (rcCH4 >= -100)){
    myservo1.write(-45);  
    myservo2.write(-45);    }
else{
    myservo1.write(0);  
    myservo2.write(0);    } 
}
