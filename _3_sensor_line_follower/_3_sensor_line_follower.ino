int s1=3;
int s2=A0;
int s3=A1;
int s4=A2;
int s5=A3;
int s6=A4;
int s7=A5;
int s8=2;
int lp=13;
int m1=9;
int m2=10;
int p1=11;
int p2=6;
int m4=7;
int m3=8;
int a1=0;
int ls=0;
int sen1;
int sen2;
int sen3;
int sen4;
int sen5;
int sen6;
int sen7;
int sen8;
int counter=0;
void setup() {
Serial.begin(9600);
pinMode(s1,INPUT);
pinMode(s2,INPUT);
pinMode(s3,INPUT);
pinMode(s4,INPUT);
pinMode(s5,INPUT);
pinMode(s6,INPUT);
pinMode(s7,INPUT);
pinMode(s8,INPUT);
pinMode(lp,OUTPUT);
pinMode(m4,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m1,OUTPUT);
pinMode(p1,OUTPUT);
pinMode(p2,OUTPUT);
analogWrite(p1,60);
analogWrite(p2,60);
digitalWrite(lp,HIGH);
}

void loop() {

  sensor_check();
  if((sen1==0))
  ls=1;
  else if((sen8==0))
  ls=2;
  sensor_check();
  
  if(sen4==0||sen5==0)
  {
    pwm_forward();
    
  }
  else if(sen2==0&&sen7==1)
  {
    left();
    Serial.println("left ");
    
  }
  else if(sen2==1&&sen7==0)
  {
    right();
    Serial.println("right ");
  }

   else if(sen2==1&&sen4==1&&sen5==1&&sen7==1)
    {
        
        if(ls==1)
        pwm_left();
        else if(ls==2)
        pwm_right();
        
          
    }
}
 
void sensor_check()
{
  
  sen1 = digitalRead(s1);
  sen2 = digitalRead(s2);
  sen3 = digitalRead(s3);
  sen4 = digitalRead(s4);
  sen5 = digitalRead(s5);
  sen6 = digitalRead(s6);
  sen7 = digitalRead(s7);
  sen8 = digitalRead(s8);
  
}
void pwm_forward()
{
  a1=1;
  digitalWrite(m2,HIGH);
  digitalWrite(m1,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("Forward");
}
void right()
{
  
  a1=1;
  digitalWrite(m2,HIGH);
  digitalWrite(m1,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,LOW);
  Serial.println("Right");
  
}

void left()
{
  
  a1=1;
  digitalWrite(m1,LOW);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("LEFT");
}
void pwm_backward()
{
  a1=1;
  
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);
  Serial.println("Backward");
}

void pwm_right()
{
  
  a1=1;
  digitalWrite(m2,HIGH);
  digitalWrite(m1,LOW);
  digitalWrite(m3,LOW);
  digitalWrite(m4,HIGH);
  Serial.println("Right");
  
}

void pwm_left()
{
  
  a1=1;
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  Serial.println("LEFT");
}

void halt()
{
  digitalWrite(m1,0);
  digitalWrite(m2,0);
  digitalWrite(m4,0);
  digitalWrite(m3,0);
  Serial.println("STOP");
}
  

