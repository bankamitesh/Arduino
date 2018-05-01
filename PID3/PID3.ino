#define Left_Dir1 5
#define Left_Dir2 4
#define Left_Speed 6
#define Right_Dir1 8
#define Right_Dir2 7
#define Right_Speed 9

#define buzzer 11

int sensor[8] = { 2,A5,A4,A3,A2,A1,A0,3 }; // Pin assignment

int sensorReading[8] = { 0 }; // Sensor reading array

float activeSensor = 0; // Count active sensors
float totalSensor = 0; // Total sensor readings
float avgSensor = 4.5; // Average sensor reading

float Kp = 100;
float Ki = 0;
float Kd = 125;

float error = 0;
float previousError = 0;
float totalError = 0;

float power = 0;

int PWM_Right, PWM_Left;


int ls=1;

int aw=0;
int ab=0;
int ff=0;

void setup()
{
  //Serial.begin(9600);
  
  pinMode(Left_Dir1, OUTPUT);
  pinMode(Left_Dir2, OUTPUT);
  pinMode(Left_Speed, OUTPUT);
  pinMode(Right_Dir1, OUTPUT);
  pinMode(Right_Dir2, OUTPUT);
  pinMode(Right_Speed, OUTPUT);
  
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  
  for(int i=0; i<8; i++) {
    pinMode(sensor[i], INPUT);
  }
  
  Stop();
  Go(255);
  Forward();
  //beep();
  
}

void loop()
{

   lineFollow();
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
    if(aw==0){
    previousError = error; // save previous error for differential 
    error = avgSensor - 4.5; // Count how much robot deviate from center
    totalError += error; // Accumulate error for integral
    
    power = (Kp*error) + (Kd*(error-previousError)) + (Ki*totalError);
    
    if( power>180 ) { power = 180.0; }
    if( power<-180.0 ) { power = -180.0; }
    
    if(power<0) // Turn left
    {
      PWM_Right = 180;
      PWM_Left = 180 - abs(int(power));
    }
    
    else // Turn right
    {
      PWM_Right = 180 - abs(int(power));
      PWM_Left = 180;
    }
    if(PWM_Right==PWM_Left)
    {
      PWM_Right=220;
      PWM_Left=220;
    }
    }
}

void lineFollow(void) {
   PID_program();
   if(aw==0){
    
   if(ff==0){
   Forward();
   ff=1;
   }
   
   analogWrite(Left_Speed, PWM_Left);
   analogWrite(Right_Speed, PWM_Right);
   }
   
   else if(aw==1)
   {
    aw=0;
    
    
    if(ff==1)
    {
      delay(50);  
    }
    ff=0;
    Go(160);
   
    if(ls==1)
    Turn_Left();
    else
    Turn_Right();
    
   
    
   }
}

void readSensor(void) {
  for(int i=0; i<8; i++) 
    {
      sensorReading[i] = digitalRead(sensor[i]);
      if(sensorReading[i]==1) { activeSensor+=1; }
      totalSensor += sensorReading[i] * (i+1);
    }

 
 if(sensorReading[0]==1)
    ls=1;
    else if(sensorReading[7]==1)
    ls=2;
    if(activeSensor==8)
    {
      ab=1;
    }
    if(activeSensor==0)
    {
      aw=1;  
    }
    
    else
    {
    avgSensor = totalSensor/activeSensor;
    activeSensor = 0; totalSensor = 0;
    }
    
}

/*void testSensor(void) {
   for(int i=0; i<8; i++) {
    Serial.print(!digitalRead(sensor[i]));
  }
  Serial.println("");
  delay(20);
}*/

