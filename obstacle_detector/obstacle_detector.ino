
#include <NewPing.h>

#define TRIGGER_PIN  4  
#define ECHO_PIN     3  
#define MAX_DISTANCE 400 
int vcc=12;
int m1=6;
int m2=5;
int m3=10;
int m4=11;
int lp=13;
int d;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  digitalWrite(vcc,HIGH);
  pinMode(m4,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m1,OUTPUT);
pinMode(lp,OUTPUT);
}

void loop() {
  delay(50);
  d=sonar.ping_cm();                     
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); 
  Serial.println("cm");
  if(d>=3&&d<=7)
  {
    pwm_forward();
    delay(500);
    right();
    delay(1000);
    halt();
    d=sonar.ping_cm();                     
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); 
  Serial.println("cm");
  if(d>=3&&d<=7)
  {
    left();
    delay(2000);
    halt();
  }
  }
  else
  pwm_backward();
}
void pwm_forward()
{
  analogWrite(m1,150);
  analogWrite(m2,0);
  analogWrite(m3,0);
  analogWrite(m4,150);
}
void pwm_backward()
{
  digitalWrite(lp,HIGH);
  analogWrite(m2,150);
  analogWrite(m1,0);
  analogWrite(m4,0);
  analogWrite(m3,150);
  
}
void right()
{
  
  analogWrite(m2,150);
  analogWrite(m1,0);
  analogWrite(m3,0);
  analogWrite(m4,150);
  
}

void left()
{
  
  analogWrite(m1,150);
  analogWrite(m2,0);
  analogWrite(m4,0);
  analogWrite(m3,150);
}
void halt()
{
digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m4,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(lp,LOW);
  
}

