#define Left_Dir1 5
#define Left_Dir2 4
#define Left_Speed 6
#define Right_Dir1 8
#define Right_Dir2 7
#define Right_Speed 9

#define buzzer 11

int s1=2;
int s2=A5;
int s3=A4;
int s4=A3;
int s5=A2;
int s6=A1;
int s7=A0;
int s8=3;

int lp=13;
int ls=1;

int sen1;
int sen2;
int sen3;
int sen4;
int sen5;
int sen6;
int sen7;
int sen8;

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
pinMode(Left_Dir1, OUTPUT);
  pinMode(Left_Dir2, OUTPUT);
  pinMode(Left_Speed, OUTPUT);
  pinMode(Right_Dir1, OUTPUT);
  pinMode(Right_Dir2, OUTPUT);
  pinMode(Right_Speed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(lp, HIGH);
  
  Stop();

  Go(180);
  
  Forward();
  
  beep();
}

void loop() {
   sensor_check();
  if(sen7==1||sen8==1||(sen6==1&&sen3==0))
  ls=2;
  else if(sen1==1||sen2==1||(sen3==1&&sen6==0))
  ls=1;
   sensor_check();
   if(sen2==1||sen1==1)
   {
    Turn_Left();
   }
   else if(sen4==1||sen5==1)
   {
    Forward();
   }
   
   else if((sen2==0&&sen3==0&&sen4==0&&sen5==0&&sen6==0&&sen7==0))
   {
        if(ls==1)
        Turn_Left();
        else if(ls==2)
        Turn_Right();
   }
   
  }
void sensor_check()
{
  sen1=digitalRead(s1);
  sen2=digitalRead(s2);
  sen3=digitalRead(s3);
  sen4=digitalRead(s4);
  sen5=digitalRead(s5);
  sen6=digitalRead(s6);
  sen7=digitalRead(s7);
  sen8=digitalRead(s8);
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


