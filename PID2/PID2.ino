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

float Kp = 110;   
float Ki = 0;
float Kd = 120;

float error = 0;
float previousError = 0;
float totalError = 0;

float power = 0;

int PWM_Right, PWM_Left, bs=160, ms=220;

int ls=1;

int aw=0;

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
  
  //pinMode(buzzer, OUTPUT);
  //digitalWrite(buzzer, LOW);
  
  for(int i=0; i<8; i++) {
    pinMode(sensor[i], INPUT);
  }
  
  Stop();
  
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

/*void beep() 
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
*/
void PID_program()
{ 
    readSensor();
    if(aw==0){
       
      error = avgSensor - 4.5; // Count how much robot deviate from center
      totalError += error; // Accumulate error for integral
      
      power = (Kp*error) + (Kd*(error-previousError)) + (Ki*totalError);
      
      previousError = error; // save previous error for differential
      
      PWM_Right = bs - int(power); 
      PWM_Left = bs + int(power);
      
      if(PWM_Right > ms) 
      {
        PWM_Right = ms;
       
      }
      
       if(PWM_Left > ms)
      {
        
        PWM_Left = ms;
      }
      if(PWM_Right < 0)
      {
        PWM_Right = 0;
      }
      if(PWM_Left < 0)
      {
        PWM_Left = 0;
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
   else
   {
    aw=0;
    ff=0;
    delay(200);
    readSensor();
    if(aw==1)
    {
      aw=0;
    Go(200);
    if(ls==1)
    Turn_Left();
    else if(ls==2)
    Turn_Right();
    }
    
   }
}

void readSensor(void) {

      sensorReading[0] = digitalRead(sensor[0]);
      if(sensorReading[0]==1) { activeSensor+=1; }
      totalSensor += sensorReading[0] * (1);
      
      sensorReading[1] = digitalRead(sensor[1]);
      if(sensorReading[1]==1) { activeSensor+=1; }
      totalSensor += sensorReading[1] * (2);
  
      sensorReading[2] = digitalRead(sensor[2]);
      if(sensorReading[2]==1) { activeSensor+=1; }
      totalSensor += sensorReading[2] * (3);
      
      sensorReading[3] = digitalRead(sensor[3]);
      if(sensorReading[3]==1) { activeSensor+=1; }
      totalSensor += sensorReading[3] * (4);

      sensorReading[4] = digitalRead(sensor[4]);
      if(sensorReading[4]==1) { activeSensor+=1; }
      totalSensor += sensorReading[4] * (5);

      sensorReading[5] = digitalRead(sensor[5]);
      if(sensorReading[5]==1) { activeSensor+=1; }
      totalSensor += sensorReading[5] * (6);

      sensorReading[6] = digitalRead(sensor[6]);
      if(sensorReading[6]==1) { activeSensor+=1; }
      totalSensor += sensorReading[6] * (7);

      sensorReading[7] = digitalRead(sensor[7]);
      if(sensorReading[7]==1) { activeSensor+=1; }
      totalSensor += sensorReading[7] * (8);
    

      aw=(activeSensor==0)?1:0;
    
    if(aw==0)
    {
      if(sensorReading[7]==1)
      ls=2;
      else if(sensorReading[0]==1)
      ls=1;
       
      
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

