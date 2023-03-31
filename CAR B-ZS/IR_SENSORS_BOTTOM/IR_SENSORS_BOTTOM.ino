 
//=======||INFRA RED SENSOR PINS||============
#define IR A0
#define IR1 A1
#define IR2 A2
#define IR3 A3
#define IR4 A4
#define IR5 A5
#define IR6 A6
#define IR7 A7
//================================================

//==============||Variables for pins||============
int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
int s7;
int s8;
//==================================================

//===========||MOTOR PINS||=========================
const int RWF = 10;
const int RWB = 9;
const int LWF = 6;
const int LWB = 5;
//==================================================

//==========|| ||
const int sensorTreshMark = 800;

void setup()
{
  Serial.begin(9600);
  pinMode(RWF, OUTPUT); // LEFT WHEEL BACKWARDS -- LEFT MOST ON THE PINOUT
  pinMode(RWB, OUTPUT); // LEFT WHEEL FORWARDS -- SECOND LEFT MOST ON THE PINOUT
  pinMode(LWF, OUTPUT); // RIGHT WHEEL FORWARDS -- LEFT MIDDLE ON THE PINOUT
  pinMode(LWB, OUTPUT); // RIGHT WHEEL BACKWARDS -- RIGHT MIDDLE ON THE PINOUT
}

void fastForward()
{
  analogWrite(RWF, 200);
  analogWrite(RWB, 0);
  analogWrite(LWF, 200);
  analogWrite(LWB, 0);
}

void slowForward()
{
  analogWrite(RWF, 180);
  analogWrite(RWB, 0);
  analogWrite(LWF, 180);
  analogWrite(LWB, 0);
}

void sharpRight()
{
  analogWrite(RWF, 0);
  analogWrite(RWB, 0);
  analogWrite(LWF, 255);
  analogWrite(LWB, 0);
}

void slowRight()
{
  analogWrite(RWF, 180);
  analogWrite(RWB, 0);
  analogWrite(LWF, 255);
  analogWrite(LWB, 0);
}

void sharpLeft()
{
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 0);
}

void slowLeft()
{
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 180);
  analogWrite(LWB, 0);
}

void carstop()
{
  analogWrite(RWF, 0);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 0);
}

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
  }
  else if (s1 <= sensorTreshMark)
  {
    s1 = 0;
  }

  if (s2 > sensorTreshMark)
  {
    s2 = 1;
  }
  else if (s2 <= sensorTreshMark)
  {
    s2 = 0;
  }

  if (s3 > sensorTreshMark)
  {
    s3 = 1;
  }
  else if (s3 <= sensorTreshMark)
  {
    s3 = 0;
  }

  if (s4 > sensorTreshMark)
  {
    s4 = 1;
  }
  else if (s4 <= sensorTreshMark)
  {
    s4 = 0;
  }

  if (s5 > sensorTreshMark)
  {
    s5 = 1;
  }
  else if (s5 <= sensorTreshMark)
  {
    s5 = 0;
  }

  if (s6 > sensorTreshMark)
  {
    s6 = 1;
  }
  else if (s6 <= sensorTreshMark)
  {
    s6 = 0;
  }

  if (s7 > sensorTreshMark)
  {
    s7 = 1;
  }
  else if (s7 <= sensorTreshMark)
  {
    s7 = 0;
  }

  if (s8 > sensorTreshMark)
  {
    s8 = 1;
  }
  else if (s8 <= sensorTreshMark)
  {
    s8 = 0;
  }
}

void printReadings()
{
  Serial.print(s1);
  Serial.print(",");
  Serial.print(s2);
  Serial.print(",");
  Serial.print(s3);
  Serial.print(",");
  Serial.print(s4);
  Serial.print(",");
  Serial.print(s5);
  Serial.print(",");
  Serial.print(s6);
  Serial.print(",");
  Serial.print(s7);
  Serial.print(",");
  Serial.println(s8);
}

void loop()
{

  makeReadings();
  printReadings();
  /*
  if (
      ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1) && (s6 == 0) && (s7 == 0) && (s8 == 0)) ||
      ((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 0) && (s8 == 0)) ||
      ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1) && (s8 == 0)) ||
      ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 0) && (s8 == 0)) ||
       ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1) && (s8 == 1)) ||
      ((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 0) && (s7 == 0) && (s8 == 0)))
  {
    fastForward();
  }

  else if (
      ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0) && (s6 == 0) && (s7 == 0) && (s8 == 0)) ||
      ((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 0) && (s6 == 0) && (s7 == 0) && (s8 == 0)) ||
      ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0) && (s8 == 0)))

  {
    slowRight();
  }
  else if (((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0) && (s8 == 0))||
  ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0) && (s8 == 0))||
  ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0) && (s6 == 0) && (s7 == 0) && (s8 == 0))||
  ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 0) && (s7 == 0) && (s8 == 0))||
  ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 0) && (s8 == 0))||
  ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1) && (s8 == 0)))
  {
    sharpRight();
  }

  else if (
      ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 1) && (s7 == 1) && (s8 == 0)) ||
      ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 1) && (s6 == 1) && (s7 == 0) && (s8 == 0)) ||
      ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 1) && (s6 == 1) && (s7 == 1) && (s8 == 0)))
  {
    slowLeft();
  }
  else if (((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 1) && (s7 == 1) && (s8 == 1)) ||
           ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 1) && (s8 == 1))||
           (((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0) && (s8 == 1))||
           ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 01) && (s6 == 1) && (s7 == 1) && (s8 == 1))||
           ((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1) && (s8 == 1))||
           ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1) && (s8 == 1))||
           ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 1) && (s6 == 1) && (s7 == 1) && (s8 == 1))))
  {
    sharpLeft();
  }
  else if(((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0) && (s8 == 0))){  
    carstop();
    }else {
      carstop();
      }
 */
 
 
  delay(100);
}
