#include <NewPing.h>

#define Left_Dir1 5
#define Left_Dir2 4
#define Left_Speed 6

#define Right_Dir1 8
#define Right_Dir2 7
#define Right_Speed 9

#define TRIGGER_PIN2  A1  
#define ECHO_PIN2     A0
 
#define TRIGGER_PIN1  A5  
#define ECHO_PIN1     A4
  
#define MAX_DISTANCE  500

#define buzzer 11

int VCC1=2;
int VCC2=A2;

int GND2=3;
int GND1=A3;

float avgSensor = 7; // Average sensor reading

float Kp = 10;
float Ki = 0;
float Kd = 35;

float error = 0;
float previousError = 0;
float totalError = 0;

float power = 0;

int PWM_Right, PWM_Left;


int ls=1;

int w=0;
int ff=0;
int d1;
int d2;

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); 

void setup()
{
  Serial.begin(9600);
  
  pinMode(VCC1,OUTPUT);
  pinMode(VCC2,OUTPUT);
   
  pinMode(GND1,OUTPUT);
  pinMode(GND2,OUTPUT);
 
  pinMode(Left_Dir1, OUTPUT);
  pinMode(Left_Dir2, OUTPUT);
  pinMode(Left_Speed, OUTPUT);
  pinMode(Right_Dir1, OUTPUT);
  pinMode(Right_Dir2, OUTPUT);
  pinMode(Right_Speed, OUTPUT);
  
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(buzzer, LOW);
  
  digitalWrite(VCC1,HIGH);
  digitalWrite(GND1,LOW);
  
  digitalWrite(VCC2,HIGH);
  digitalWrite(GND2,LOW);
  
  Forward();
  Go(120);
  
  
}

void loop()
{

   wallFollow();
}

void Left_Forward() 
{
  digitalWrite(Left_Dir1, LOW);
  digitalWrite(Left_Dir2, HIGH);
}

void Left_Reverse() 
{
  digitalWrite(Left_Dir1, HIGH);
  digitalWrite(Left_Dir2, LOW);
}

void Right_Forward()
{
  digitalWrite(Right_Dir1, LOW);
  digitalWrite(Right_Dir2, HIGH);
}

void Right_Reverse()
{
  digitalWrite(Right_Dir1, HIGH);
  digitalWrite(Right_Dir2, LOW);
}

void Go(int s)
{
  analogWrite(Right_Speed, s);
  analogWrite(Left_Speed, s);
}

void Forward()
{
  Left_Forward();
  Right_Forward();
}

void Reverse() 
{
  Left_Reverse();
  Right_Reverse();
}

void Turn_Left() 
{
  Right_Forward();
  Left_Reverse();
}

void Turn_Right() 
{
  Right_Reverse();
  Left_Forward();
}

void Stop() 
{
  analogWrite(Left_Speed,0);
  analogWrite(Right_Speed, 0);
}

void beep() 
{
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
}

void PID_program()
{ 
    readSensor();
    if(w==0){
    previousError = error; // save previous error for differential 
    error = 7 - avgSensor; // Count how much robot deviate from center
    totalError += error; // Accumulate error for integral
    
    power = (Kp*error) + (Kd*(error-previousError)) + (Ki*totalError);
    
    if( power>120 ) { power = 120.0; }
    if( power<-120.0 ) { power = -120.0; }
    
    if(power<0) // Turn left
    {
      PWM_Right = 120;
      PWM_Left = 120 - abs(int(power));
    }
    
    else // Turn right
    {
      PWM_Right = 120 - abs(int(power));
      PWM_Left = 120;
    }
    
    }
}

void wallFollow(void) {
   PID_program();
   
   if(w==0){
    
   if(ff==0){
   Forward();
   ff=1;
   }
   
   analogWrite(Left_Speed, PWM_Left);
   analogWrite(Right_Speed, PWM_Right);
   }
   
   else
   {
    w=0;
    ff=0;
    Go(100);
    d2=sonar2.ping_cm();
    while(d2<10)
    {
    Turn_Right();
    d2=sonar2.ping_cm();
    }
   
    
   }
}

void readSensor(void) {
  
  d1=sonar1.ping_cm();
  d2=sonar2.ping_cm();
  if(d2<=10&&d2>=3)
  {
    w=1;
  }
  if(d1==0||d1>=14)
  {
    d1=7;
  }
  avgSensor=d1;  
    
}

/*void testSensor(void) {
   for(int i=0; i<8; i++) {
    Serial.print(!digitalRead(sensor[i]));
  }
  Serial.println("");
  delay(20);
}*/

