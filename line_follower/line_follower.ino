int s1=A0;
int s2=A1;
int s3=A2;
int s4=A3;
int s5=A4;
int lp=13;
int k=300;
int m1=6;
int m2=5;
int m3=10;
int m4=11;
int a1=0;
int ls=0;
int sen1;
int sen2;
int sen3;
int sen4;
int sen5;
void setup() {
Serial.begin(9600);
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
  if(sen1==0||(sen2==0&&sen4==1))
  ls=1;
  else if(sen5==0||(sen4==0&&sen2==1))
  ls=2;
  display();
  if(a1==0)
  {
    while(1)
    {
    halt();
    sensor_check();
    if(sen1!=sen2||sen1!=sen3||sen1!=sen4||sen1!=sen5)
    {
      a1=1;
      break;
    }
    }
  }
 else if((sen3==0&&sen1==0&&sen2==0&&sen4==0&&sen5==0)||(sen3==0&&sen1==1&&sen5==1))
  {
    pwm_backward();
  }
  else if(sen1==0||(sen2==0&&sen4==1))
  {
    pwm_left();
    
  }
  else if(sen5==0||(sen2==1&&sen4==0))
  {
    pwm_right();
    
  }

   else if(sen1==1&&sen2==1&&sen3==1&&sen4==1&&sen5==1)
    {
      
      if(ls==1)
      pwm_left();
      else if(ls==2)
      pwm_right();
      else if(ls==0)
      pwm_forward();
    }
}
 void display()
 {
  Serial.println(sen1);
  Serial.println(sen2);
  Serial.println(sen3);
  Serial.println(sen4);
  Serial.println(sen5);
  if(ls==0)
  Serial.println("Back");
  else if(ls==2)
  Serial.println("Right");
  else
  Serial.println("Left");
 }
void sensor_check()
{
  int ss1=analogRead(s1);
  int ss2=analogRead(s2);
  int ss3=analogRead(s3);
  int ss4=analogRead(s4);
  int ss5=analogRead(s5);
  if (ss1>k)
  sen1=1;
  else
  sen1=0;
  if(ss2>k)
  sen2=1;
  else
  sen2=0;
  if(ss3>k)
  sen3=1;
  else
  sen3=0;
  if(ss4>k)
  sen4=1;
  else
  sen4=0;
  if(ss5>k)
  sen5=1;
  else
  sen5=0;
}
void pwm_forward()
{
  a1=1;
  analogWrite(m1,255);
  analogWrite(m2,0);
  analogWrite(m3,0);
  analogWrite(m4,255);
}
void pwm_backward()
{
  a1=1;
  digitalWrite(lp,HIGH);
  analogWrite(m2,255);
  analogWrite(m1,0);
  analogWrite(m4,0);
  analogWrite(m3,255);
}
void pwm_right()
{
  
  a1=1;
  analogWrite(m2,255);
  analogWrite(m1,0);
  analogWrite(m3,0);
  analogWrite(m4,0);
  
}

void pwm_left()
{
  
  a1=1;
  analogWrite(m1,0);
  analogWrite(m2,0);
  analogWrite(m4,0);
  analogWrite(m3,255);
}
void halt()
{
digitalWrite(m1,LOW);
 digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m4,LOW);
  digitalWrite(m3,LOW);
}
  

