#include <Servo.h>

/*
Into Robotics
*/
 
int servoPin = 9;
 
Servo servo;  
 
int servoAngle = 0;   // servo position in degrees
 
void setup()
{
  Serial.begin(9600);  
  servo.attach(servoPin);
}
 
 
void loop()
{
//control the servo's direction and the position of the motor

 
   servo.write(90);      // Turn SG90 servo Left to 45 degrees
   delay(1000);          // Wait 1 second
   servo.write(0);      // Turn SG90 servo back to 90 degrees (center position)
   delay(1000); 
   delay(5000);// Wait 1 second
   


}
