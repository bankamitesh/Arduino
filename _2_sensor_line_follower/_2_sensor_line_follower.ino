int s1=A0;
int s2=A1;
int k=300;
int m1=5;
int m2=4;
int m3=3;
int m4=2;
int sen1;
int sen2;
void setup() {
Serial.begin(9600);
pinMode(s1,INPUT);
pinMode(s2,INPUT);
pinMode(m4,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m1,OUTPUT);
}

void loop() {
  sensor_check();
  if(sen1==1&&sen2==1)
  pwm_forward();
  else if(sen1==0)
  pwm_left();
  else
  pwm_right();
}
 
void sensor_check()
{
  int ss1=analogRead(s1);
  int ss2=analogRead(s2);
  
  if (ss1>k)
  sen1=1;
  else
  sen1=0;
  if(ss2>k)
  sen2=1;
  else
  sen2=0;
}
void pwm_backward()
{
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);
}
void pwm_forward()
{
  
  digitalWrite(m2,HIGH);
  digitalWrite(m1,LOW);
  digitalWrite(m4,LOW);
  digitalWrite(m3,HIGH);
}
void pwm_right()
{
  digitalWrite(m2,HIGH);
  digitalWrite(m1,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,LOW);
  
}

void pwm_left()
{
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m4,LOW);
  digitalWrite(m3,HIGH);
}
void halt()
{
 digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m4,LOW);
  digitalWrite(m3,LOW);
}
