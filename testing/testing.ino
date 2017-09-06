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
int k=300;
int sen1;
int sen2;
int sen3;
int sen4;
int sen5;
int lt=0;
int bt=0;
int stk[20]={0};
int top=0;
void push(int a)
{
  stk[top++]=a;
}
int pop()
{
  return stk[--top];
}
void display_route()
{
  int i;
  Serial.println("--------------------------------------");
  for(i=0;i<top;i++)
  Serial.println(stk[i]);
  Serial.println("--------------------------------------");
}
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
  display_route();
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
  else if(sen1==1&&sen5==1)
  {
    lt=stk[top-1];
    if(lt==1)
    {
      pwm_right();
      push(1);
    }
    else
    {
      pwm_left();
      push(2);
    }
  }
  else if(sen1==1&&sen2==1&&sen3==1){
  pwm_right();
  push(1);
  }
  
  else if(sen5==1&&sen3==1&&sen4==1){
    pwm_left();
 push(2);
 }
  
  else if(sen2==0&&sen3==0&&sen4==0&&sen1==0&&sen5==0&&a1==0)
  halt();
  else if(sen2==0&&sen3==0&&sen4==0&&sen1==0&&sen5==0&&a1==1)
  {
      while(sen2!=1||sen3!=1)
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
      lt=pop();
        if(lt==2)
          pwm_left();
          else
          pwm_right();
       
  }
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
  digitalWrite(lp,LOW);
  analogWrite(m1,100);
  analogWrite(m2,0);
  analogWrite(m3,0);
  analogWrite(m4,100);
  a1=1;
  bt=0;
}
void pwm_backward()
{
  digitalWrite(lp,HIGH);
  analogWrite(m2,100);
  analogWrite(m1,0);
  analogWrite(m4,0);
  analogWrite(m3,100);
  a1=1;
  bt=0;
}
void pwm_right()
{
  pwm_backward();
  delay(300);
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
  a1=1;
}
void pwm_left()
{
  pwm_backward();
  delay(300);
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
  a1=1;
}

void right()
{
  
  analogWrite(m2,100);
  analogWrite(m1,0);
  analogWrite(m3,0);
  analogWrite(m4,100);
  a1=1;
}

void left()
{
  
  analogWrite(m1,100);
  analogWrite(m2,0);
  analogWrite(m4,0);
  analogWrite(m3,100);
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

