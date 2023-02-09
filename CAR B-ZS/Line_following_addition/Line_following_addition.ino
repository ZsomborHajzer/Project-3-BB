//======================||VARIABLES AND PINS||========================

#define IR A0
#define IR1 A1
#define IR2 A2
#define IR3 A3
#define IR4 A4
#define IR5 A5
#define IR6 A6
#define IR7 A7

int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
int s7;
int s8;

int s1m;
int s2m;
int s3m;
int s4m;
int s5m;
int s6m;
int s7m;
int s8m;

int directionCalc;
int sensorTreshMark = 500;

const int RWF = 10;
const int RWB = 9;
const int LWF = 6;
const int LWB = 5;

//======================||END OF VARIABLES AND PINS||========================


//======================||SETUP||========================
void setup()
{
  Serial.begin(9600);
  pinMode(RWF, OUTPUT); // LEFT WHEEL BACKWARDS -- LEFT MOST ON THE PINOUT
  pinMode(RWB, OUTPUT); // LEFT WHEEL FORWARDS -- SECOND LEFT MOST ON THE PINOUT
  pinMode(LWF, OUTPUT); // RIGHT WHEEL FORWARDS -- LEFT MIDDLE ON THE PINOUT
  pinMode(LWB, OUTPUT); // RIGHT WHEEL BACKWARDS -- RIGHT MIDDLE ON THE PINOUT
}

//======================||END OF SETUP||========================


//======================||DIRECTION FUNCTIONS||========================
void sharpRight()
{
  analogWrite(RWF, 180);
  analogWrite(RWB, 0);
  analogWrite(LWF, 255);
  analogWrite(LWB, 0);
}

void slowRight()
{
  analogWrite(RWF, 220);
  analogWrite(RWB, 0);
  analogWrite(LWF, 255);
  analogWrite(LWB, 0);
}


void forward()
{
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 255);
  analogWrite(LWB, 0);
}

void sharpLeft()
{
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 180);
  analogWrite(LWB, 0);
}

void slowLeft()
{
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 220);
  analogWrite(LWB, 0);
}

void carstop()
{
  analogWrite(RWF, 0);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 0);
}

//======================||END OF DIRECTION FUNCTIONS||========================

//======================||LINE FOLLOWING READINGS||========================

void makeReadings()
{
  s1 = analogRead(IR);
  s2 = analogRead(IR1);
  s3 = analogRead(IR2);
  s4 = analogRead(IR3);
  s5 = analogRead(IR4);
  s6 = analogRead(IR5);
  s7 = analogRead(IR6);
  s8 = analogRead(IR7);

  if (s1 > sensorTreshMark)
  {
    s1 = 1;
    s1m = 3;
  }
  else if (s1 <= sensorTreshMark)
  {
    s1 = 0;
    s1m = 0;
  }

  if (s2 > sensorTreshMark)
  {
    s2 = 1;
    s2m = 2;
  }
  else if (s2 <= sensorTreshMark)
  {
    s2 = 0;
    s2m = 0;
  }

  if (s3 > sensorTreshMark)
  {
    s3 = 1;
    s3m = 1;
  }
  else if (s3 <= sensorTreshMark)
  {
    s3 = 0;
    s3m = 0;
  }

  if (s4 > sensorTreshMark)
  {
    s4 = 0;
    s4m = 0;
  }
  else if (s4 <= sensorTreshMark)
  {
    s4 = 0;
    s4m = 0;
  }

  if (s5 > sensorTreshMark)
  {
    s5 = 1;
    s5m = 0;
  }
  else if (s5 <= sensorTreshMark)
  {
    s5 = 0;
    s5m = 0;
  }

  if (s6 > sensorTreshMark)
  {
    s6 = 1;
    s6m = -1;
  }
  else if (s6 <= sensorTreshMark)
  {
    s6 = 0;
    s6m = 0;
  }

  if (s7 > sensorTreshMark)
  {
    s7 = 1;
    s7m = -2;
  }
  else if (s7 <= sensorTreshMark)
  {
    s7 = 0;
    s7m = 0;
  }

  if (s8 > sensorTreshMark)
  {
    s8 = 1;
    s8m = -3;
  }
  else if (s8 <= sensorTreshMark)
  {
    s8 = 0;
    s8m = 0;
  }
}

void sensorMath()
{

  directionCalc = s1m + s2m + s3m + s4m + s5m + s6m + s7m + s8m;
  Serial.println(directionCalc);
}

//======================||END OF LINE FOLLOWING READINGS||========================

//======================||LOOP||========================
void loop()
{

  makeReadings();
  sensorMath();
  
  if((s1m == 3) && (s2m == 2) && (s3m == 1) && (s4m == 0) && (s5m == 0) && (s6m == -1) && (s7m == -2) && (s8m == -3)) {
    carstop();
    Serial.println("STOP");
  
 }else {
   if (directionCalc > 0 && directionCalc < 3){
     Serial.println("slowRight");
     slowRight();
    
    }else if (directionCalc >= 3){
       Serial.println("fastRight");
       sharpRight();
    }

  if (directionCalc < 0 && directionCalc > -3){
     Serial.println("slowLeft");
     slowLeft();
  }else if(directionCalc <= -3){
     Serial.println("fastLeft");
     sharpLeft();
    }

  if (directionCalc == 0){
     Serial.println("Forward");
     forward();
    }
    }
  
delay(50) ;
    
}

//======================||END OF LOOP||========================
