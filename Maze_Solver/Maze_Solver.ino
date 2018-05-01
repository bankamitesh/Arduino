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

float Kp = 110;   // Max deviation = 8-4.5 = 3.5 ||  160/3.5 = 51
float Ki = 0;
float Kd = 110;

float error = 0;
float previousError = 0;
float totalError = 0;

float power = 0;

int PWM_Right, PWM_Left;


int ls=2;

int aw=0;

int ff=0;

int tr=0;

int ab=0;

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
  
  Forward();
  
  
  
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
    
    if(aw==0 && tr==0) {
    
        previousError = error; // save previous error for differential 
        error = avgSensor - 4.5; // Count how much robot deviate from center
        totalError += error; // Accumulate error for integral
        
        power = (Kp*error) + (Kd*(error-previousError)) + (Ki*totalError);
        
        if( power>190 ) { power = 190.0; }
        if( power<-190.0 ) { power = -190.0; }
        
        if(power<0) // Turn left
        {
          PWM_Right = 190;
          PWM_Left = 190 - abs(int(power));
        }
        
        else // Turn right
        {
          PWM_Right = 190 - abs(int(power));
          PWM_Left = 190;
        }
    
    }
}

void lineFollow(void) {
   
   PID_program();
   
   if(aw==0 && tr==0) {
    
       if(ff==0) {
         Forward();
         ff=1;
       }
       
       analogWrite(Left_Speed, PWM_Left);
       analogWrite(Right_Speed, PWM_Right); 
       
   }
   
   else if(tr==1) {
      
      ab=0;
      tr=0;
      ff=0;
      
      Go(200);
      Turn_Right();
      delay(200);
      
   }
   
   else if(aw==1) {
      
      aw=0;
      ff=0;
      
      Go(200);
      
      if(ls==2)
      Turn_Right();
      else if(ls==1)
      Turn_Left();
      
   }
}

void readSensor(void) {
  
  for(int i=0; i<8; i++) {
      
      sensorReading[i] = !digitalRead(sensor[i]);
      if(sensorReading[i]==1) { activeSensor+=1; }
      totalSensor += sensorReading[i] * (i+1);
  }
    
  if(sensorReading[7]==1)
  ls=2;
  else if(sensorReading[0]==1)
  ls=1;
    
  tr=(totalSensor>=30)?1:0;
  
  ab=(activeSensor==8)?1:0;
    
  aw=(activeSensor==0)?1:0;
    
  if(aw==0) {
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

