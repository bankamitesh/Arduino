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
  
#define MAX_DISTANCE  200

int VCC1=2;
int VCC2=A2;

int GND2=3;
int GND1=A3;

int d1;
int d2;

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); 

void setup() {
  
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
   
  digitalWrite(VCC1,HIGH);
  digitalWrite(GND1,LOW);
  
  digitalWrite(VCC2,HIGH);
  digitalWrite(GND2,LOW);
  
  Forward();
  Go(200);
  delay(800);
  
}

void loop() {

  
  
  d1=sonar1.ping_cm();
  d2=sonar2.ping_cm();

  
  if((d2<=14&&d2>=2))
  {
    Go(160);
    
    Turn_Right();
    delay(320);
  }

  else if(d1<=4&&d1!=0)
  {
    Go(160);
    Turn_Right();
  }
  else if(d1>=7&&d1<=10)
  {
    Go(160);
    Turn_Left();
  }
  
  else
  {
    Go(160);
    Forward();
  }
  
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

void Left_Stop()
{
  digitalWrite(Left_Dir1, LOW);
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

void Right_Stop()
{
  digitalWrite(Right_Dir1, LOW);
  digitalWrite(Right_Dir2, LOW);
}

void Go(int s)
{
  analogWrite(Right_Speed, s-21);
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

void Left() 
{
  Right_Forward();
  Left_Stop();
}

void Turn_Right() 
{
  Right_Reverse();
  Left_Forward();
}

void Right() 
{
  Right_Stop();
  Left_Forward();
}

void Stop() 
{
  analogWrite(Left_Speed,0);
  analogWrite(Right_Speed, 0);
}
