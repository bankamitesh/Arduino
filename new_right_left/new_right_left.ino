
#include <NewPing.h>
#define TRIGGER_PIN  4  
#define ECHO_PIN     3  
#define MAX_DISTANCE 400 
int vcc=12;
#define WBG  0
#define BBG  1
#define analogref 300
int d;
int digitalval = 1;
int leftdiff ; 
int rightdiff ; 
int s1=A0;
int s2=A1;
int s3=A2;
int s4=A3;
int s5=A4;
int lp=13;
int m1=6;
int m2=5;
int m3=10;
int m4=11;
int a1=0;
int sen1;
int sen2;
int sen3;
int sen4;
int sen5;
int lt=0;
int bt=0;
int stk[20]={0};
int stk2[20]={0};
int top=0;
int top2=0;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
void push(int a)
{
  stk[top++]=a;
  stk2[top2++]=a;
}
int pop()
{
  int check=0;
  if(stk2[top2-1]==0)
  {
    top2--;
    check=1;
  }
  stk2[top2-1]=0;
  if(stk2[top2-2]==0&&check==0)
  top2--;
  return (stk[--top]);
}
int pop_stk2()
{
  if(top2!=0)
  return stk2[--top2];
  else
  return -1;
}
void display_route()
{
  int i;
  Serial.println("--------------------------------------");
  for(i=0;i<top;i++)
  Serial.println(stk[i]);
  Serial.println("--------------------------------------");
   Serial.println("--------------------------------------");
  for(i=0;i<top2;i++)
  Serial.println(stk2[i]);
  Serial.println("--------------------------------------");

}
void shortest_path()
{
  sensor_check();
  if(sen3==1&&sen1==0&&sen5==0)
  pwm_backward();
  else if(sen2==1&&sen4==0)
  {
    right();
    bt=1;
  }
  else if(sen4==1&&sen2==0)
  {
    left();
    bt=1;
    
  }
  else if(sen2==0&&sen3==0&&sen4==0&&bt==1)
  pwm_forward();
  else if((sen2==1&&sen3==1&&sen4==1)&&(sen1==1||sen5==1))
  {
    display_route();
    lt=pop_stk2();
    if(lt==0)
    {
      Serial.println("Wrong Track");
      pwm_backward();
      delay(100);
    }
    if(lt==2)
    {
      Serial.println("Left taken");
      pwm_right();
    }
    else if(lt==1)
    {
      Serial.println("Right taken");
      pwm_left();
    }
    else if(lt==-1)
    halt();
    
  }
    else if(sen2==0&&sen3==0&&sen4==0&&sen1==0&&sen5==0)
  {
    halt();
    Serial.println("Reached Starting point");
    display_route();
      digitalWrite(lp,HIGH);
  delay(50);
  digitalWrite(lp,LOW);
  delay(50);
  }
  shortest_path();
}
void setup() {
Serial.begin(9600);
 pinMode(12,OUTPUT);
  digitalWrite(vcc,HIGH);
pinMode(s1,INPUT);
pinMode(s2,INPUT);
pinMode(s3,INPUT);
pinMode(s4,INPUT);
pinMode(s5,INPUT);
 pinMode(lp,OUTPUT);
pinMode(m4,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m1,OUTPUT);
}

void loop() {
  sensor_check();
  if(sen3==1&&sen1==0&&sen5==0&&d>10)
  pwm_backward();
  else if(sen2==1&&sen4==0)
  {
    right();
    bt=1;
  }
  else if(sen4==1&&sen2==0)
  {
    left();
    bt=1;
    
  }
  else if(sen2==0&&sen3==0&&sen4==0&&bt==1)
  pwm_forward();
  else if(d>=4&&d<=10)
  {
     Serial.println("Reached End Point");
      Serial.println("Shortest path");
    pwm_forward();
  delay(300);
  sensor_check();
  left();
  delay(300);
  sensor_check();
     while(sen4!=1&&sen3!=1)
      {
        left();
        sensor_check();
      }
      halt();
     
 shortest_path();
  }
  else if(sen1==1&&sen2==1&&sen3==1&&sen4==1){
  display_route();
  Serial.println("Left Taken");
  pwm_right();
  push(1);
  }
  
  else if(sen5==1&&sen3==1&&sen4==1&&sen2==1){
    display_route();
    Serial.println("Right Taken");
    pwm_left();
 push(2);
 }
  
  else if(sen2==0&&sen3==0&&sen4==0&&sen1==0&&sen5==0&&a1==0)
  halt();
  else if(sen2==0&&sen3==0&&sen4==0&&sen1==0&&sen5==0&&a1==1)
  {
    sensor_check();
      Serial.println("Backtrack");
      while(sen2!=1&&sen3!=1)
      {
        right();
        sensor_check();
      }
      while(sen1!=1||sen5!=1)
      {
  if(sen3==1)
  pwm_backward();
  else if(sen2==1&&sen4==0)
  right();
  else if(sen4==1&&sen2==0)
  left();
  else if(sen3==0&&sen4==0&&sen2==0)
  pwm_forward();
  sensor_check();
      }
      display_route();
      lt=pop();
        if(lt==2)
          {
            pwm_left();
            Serial.println("Right Taken");
          }
          else
          {
            pwm_right();
            Serial.println("Left Taken");
          }
          display_route();
          Serial.println("Backtracking Done");
       
  }
  }
int analogdiff(int pin)
{
  if( abs(analogRead(pin) - analogRead(s2))  > analogref ) return true;
  if( abs(analogRead(pin) - analogRead(s3))  > analogref ) return true;
  if( abs(analogRead(pin) - analogRead(s4))  > analogref ) return true;
  return false;
}

void sensor_check()
{
  leftdiff = analogdiff(s1) ;
  rightdiff = analogdiff(s5) ;
  if( leftdiff and rightdiff )
  {
    if( analogRead(s1) > analogref and analogRead(s5) > analogref and digitalval ==  BBG )
    {
      Serial.println("White Background");
      digitalval = WBG;
    }
    else if( analogRead(s1) < analogref and analogRead(s5) < analogref and digitalval ==  WBG )
    {
      Serial.println("Black Background");
      digitalval = BBG;
    }
  }
    d=sonar.ping_cm();                     
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); 
  Serial.println("cm");
  sen1 = (analogRead(s1) > analogref) ? digitalval : !digitalval ;
  sen2 = (analogRead(s2) > analogref) ? digitalval : !digitalval ;
  sen3 = (analogRead(s3) > analogref) ? digitalval : !digitalval ;
  sen4 = (analogRead(s4) > analogref) ? digitalval : !digitalval ;
  sen5 = (analogRead(s5) > analogref) ? digitalval : !digitalval ;
}
void pwm_forward()
{
  digitalWrite(lp,LOW);
  analogWrite(m1,70);
  analogWrite(m2,0);
  analogWrite(m3,0);
  analogWrite(m4,70);
  a1=1;
  bt=0;
}
void pwm_backward()
{
  digitalWrite(lp,HIGH);
  analogWrite(m2,70);
  analogWrite(m1,0);
  analogWrite(m4,0);
  analogWrite(m3,70);
  a1=1;
  bt=0;
}
void pwm_right()
{
  pwm_backward();
  delay(200);
  sensor_check();
  while(sen1!=1)
  {
    right();
    sensor_check();
  }
  while(sen3!=1)
  {
    right();
    sensor_check();
  }
  pwm_forward();
  delay(100);
  a1=1;
}
void pwm_left()
{
  pwm_backward();
  delay(200);
  sensor_check();
  while(sen5!=1)
  {
    left();
    sensor_check();
  }
  while(sen3!=1)
  {
    left();
    sensor_check();
  }
  pwm_forward();
  delay(100);
  a1=1;
}

void right()
{
  
  analogWrite(m2,60);
  analogWrite(m1,0);
  analogWrite(m3,0);
  analogWrite(m4,50);
  a1=1;
}

void left()
{
  
  analogWrite(m1,50);
  analogWrite(m2,0);
  analogWrite(m4,0);
  analogWrite(m3,60);
  a1=1;
}
void halt()
{
digitalWrite(m1,HIGH);
  digitalWrite(m2,HIGH);
  digitalWrite(m4,HIGH);
  digitalWrite(m3,HIGH);
  digitalWrite(lp,LOW);
  
}

