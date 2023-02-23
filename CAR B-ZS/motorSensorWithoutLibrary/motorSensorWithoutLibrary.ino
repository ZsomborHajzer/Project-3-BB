
//====================|| IR SENSOR PINS AND VARIABLES||===========================

#define IR A0
#define IR1 A1
#define IR2 A2
#define IR3 A3
#define IR4 A4
#define IR5 A5
#define IR6 A6
#define IR7 A7

int s0;
int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
int s7;
int s0m;
int s1m;
int s2m;
int s3m;
int s4m;
int s5m;
int s6m;
int s7m;

int directionCalc;
int sensorTreshMark = 800;
boolean activeLineFollowing = true;
boolean activeIRReading = true;
unsigned long time;

//===============================================================================

//===================||WHEEL SENSOR PINS AND VARIABLES||====================

#define encoderRW 2 // 36 signals for a 90 degree turn
#define encoderLW 3
unsigned long countRW = 0;
unsigned long countLW = 0;

//========================================================================
//================||WHEEL MOTOR PINS|| ==================================
const int LWF = 10;
const int LWB = 9;
const int RWF = 6;
const int RWB = 5;
//========================================================================                                                   END OF VARIABLES

void setup()
{
  // Initialize encoders
  Serial.begin(9600);
  pinMode(encoderRW, INPUT);
  pinMode(encoderLW, INPUT);
  pinMode(RWF, OUTPUT); // LEFT WHEEL BACKWARDS -- LEFT MOST ON THE PINOUT
  pinMode(RWB, OUTPUT); // LEFT WHEEL FORWARDS -- SECOND LEFT MOST ON THE PINOUT
  pinMode(LWF, OUTPUT); // RIGHT WHEEL FORWARDS -- LEFT MIDDLE ON THE PINOUT
  pinMode(LWB, OUTPUT); // RIGHT WHEEL BACKWARDS -- RIGHT MIDDLE ON THE PINOUT

  // encoder interrupts
  attachInterrupt(digitalPinToInterrupt(encoderRW), updateRW, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderLW), updateLW, CHANGE);
}

//======================||IR SENSOR FUNCTIONS||=================================                                               END OF SETUP
void makeIRReadings()
{
if(activeIRReading == true)
{
 s0 = analogRead(IR);
  s1 = analogRead(IR1);
  s2 = analogRead(IR2);
  s3 = analogRead(IR3);
  s4 = analogRead(IR4);
  s5 = analogRead(IR5);
  s6 = analogRead(IR6);
  s7 = analogRead(IR7); 
}

  if (s0 > sensorTreshMark)
  {
    s0 = 1;
    s0m = -9;
  }
  else if (s0 <= sensorTreshMark)
  {
    s0 = 0;
    s0m = 0;
  }

  if (s1 > sensorTreshMark)
  {
    s1 = 1;
    s1m = -4;
  }
  else if (s1 <= sensorTreshMark)
  {
    s1 = 0;
    s1m = 0;
  }

  if (s2 > sensorTreshMark)
  {
    s2 = 1;
    s2m = -2;
  }
  else if (s2 <= sensorTreshMark)
  {
    s2 = 0;
    s2m = 0;
  }

  if (s3 > sensorTreshMark)
  {
    s3 = 1;
    s3m = -1;
  }
  else if (s3 <= sensorTreshMark)
  {
    s3 = 0;
    s3m = 0;
  }

  if (s4 > sensorTreshMark)
  {
    s4 = 1;
    s4m = 1;
  }
  else if (s4 <= sensorTreshMark)
  {
    s4 = 0;
    s4m = 0;
  }

  if (s5 > sensorTreshMark)
  {
    s5 = 1;
    s5m = 2;
  }
  else if (s5 <= sensorTreshMark)
  {
    s5 = 0;
    s5m = 0;
  }

  if (s6 > sensorTreshMark)
  {
    s6 = 1;
    s6m = 4;
  }
  else if (s6 <= sensorTreshMark)
  {
    s6 = 0;
    s6m = 0;
  }

  if (s7 > sensorTreshMark)
  {
    s7 = 1;
    s7m = 9;
  }
  else if (s7 <= sensorTreshMark)
  {
    s7 = 0;
    s7m = 0;
  }

  directionCalc = s0m + s1m + s2m + s3m + s4m + s5m + s6m + s7m;
}

void printIRReadings()
{

  Serial.print(s0);
  Serial.print(",");
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
  Serial.println(s7);
}

//=================||END OF IR SENSOR FUNCTIONS||===============================                                       END OF IR SENSOR FUNCTIONS

//=====================||ENCODER FUNCTIONS||====================================
void updateRW()
{
  noInterrupts();
  countRW = countRW + 1;
  interrupts();
}

void updateLW()
{
  noInterrupts();

  countLW++;

  interrupts();
}

void printEncoderMesurements()
{
  Serial.print("Right Wheel: ");
  Serial.print(countRW);
  Serial.print(" , ");
  Serial.print("Left Wheel: ");
  Serial.println(countLW);
}

void resetCounters()
{
  countRW = 0;
  countLW = 0;
}

//=====================||END OF ENCODER FUNCTIONS||====================================                                     END OF ENCODEDR SENSOR FUNCTION

//=====================||TURN DIRECTION FUNCTIONS||==========================================

void turnAround()
{

  resetCounters();
  carStop();
  wait(1000);

  while (countLW < 23)
  {
    printEncoderMesurements();
    analogWrite(RWF, 255);
    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
    analogWrite(LWB, 255);
  }
  resetCounters();

  while (countLW <= 5)
  {
    printEncoderMesurements();
    analogWrite(RWF, 0);
    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
    analogWrite(LWB, 255);
  }

  resetCounters();

  while (countLW <= 25)
  {
    printEncoderMesurements();
    analogWrite(RWF, 0);
    analogWrite(RWB, 255);
    analogWrite(LWF, 0);
    analogWrite(LWB, 255);
  }

  resetCounters();
  carStop();
  wait(1000);
  loop();
}

void rightAngleRight()
{

  carStop();
  wait(1000);
  resetCounters();

  while (countLW <= 1)
  {
    printEncoderMesurements();
    analogWrite(RWF, 230);
    analogWrite(RWB, 0);
    analogWrite(LWF, 230);
    analogWrite(LWB, 0);
  }

  resetCounters();

  while (countLW < 44)
  {
    printEncoderMesurements();
    analogWrite(RWF, 0);
    analogWrite(RWB, 0);
    analogWrite(LWF, 255);
    analogWrite(LWB, 0);
  }

  resetCounters();
  carStop();
  wait(1000);
  loop();
}

void rightAngleLeft()
{

  carStop();
  wait(1000);
  resetCounters();

  while (countRW <= 1)
  {
    printEncoderMesurements();
    analogWrite(RWF, 255);
    analogWrite(RWB, 0);
    analogWrite(LWF, 255);
    analogWrite(LWB, 0);
  }
  resetCounters();
  while (countRW < 34)
  {
    printEncoderMesurements();
    analogWrite(RWF, 255);
    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
    analogWrite(LWB, 0);
  }
  resetCounters();
  carStop();
  wait(1000);
  loop();
}

void carStopStrong()
{
  resetCounters();
  while (countRW <= 3)
  {
    printEncoderMesurements();
    analogWrite(RWF, 0);
    analogWrite(RWB, 255);
    analogWrite(LWF, 0);
    analogWrite(LWB, 255);
  }
  resetCounters();
  loop();
}

//=====================||END OF TURN DIRECTION FUNCTIONS||====================================                            END OF TURN DIRECTION FUNCTIONS
//=====================||LINE FOLLOWING DIRECTION FUNCTIONS||=================================

void forwards()
{
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 255);
  analogWrite(LWB, 0);
}
void carStop()
{
  analogWrite(RWF, 0);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 0);
}

void slowRight()
{
  analogWrite(RWF, 190);
  analogWrite(RWB, 0);
  analogWrite(LWF, 240);
  analogWrite(LWB, 0);
}

void slowLeft()
{
  analogWrite(RWF, 240);
  analogWrite(RWB, 0);
  analogWrite(LWF, 190);
  analogWrite(LWB, 0);
}

void sharpRight()
{
  analogWrite(RWF, 160);
  analogWrite(RWB, 0);
  analogWrite(LWF, 255);
  analogWrite(LWB, 0);
}

void sharpLeft()
{
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 160);
  analogWrite(LWB, 0);
}

//=====================||END OF LINE FOLLOWING DIRECTION FUNCTIONS||==========================                          END OF LINE FOLLOWING DIRECTION FUNCTIONS

//=====================||INTERSECTION DECISION MAKING FUNCTIONS||============================

void wait(int timeToWait)
{
  time = millis();
  carStop();
  while(millis() < time+timeToWait);
}

int waitAndMesure()
{

  wait(200);
  
  s2 = analogRead(IR2);
  s3 = analogRead(IR3);
  s4 = analogRead(IR4);
  s5 = analogRead(IR5);
  
  return s2, s3, s4, s5;
}

//=====================||END OF INTERSECTION DECISION MAKING FUNCTIONS||=====================

//=====================||LINE FOLLOWING FUNCTIONS||===========================================

void followLine()
{
  if (activeLineFollowing == true)
  {
    if ((s0 == 1) && (s7 == 1))
    {
      rightAngleLeft();
      // wait 0.1 second
      // measure again
      /* if((s0 == 0) && (s7 == 0))
      {
       sharpLeft();
      }
       else if (blackBlock counter == 0)
      {
        startSequence();
        blackBlockCounter++;
      }
      else if(blackBlockCounter == 1)
      {
        endSequence();
      }
       */

      //  activeLineFollowing = false;
    }
    else if ((s0 == 1) && (s2 == 1) && (s7 == 0))
    {
      rightAngleLeft();
    }
    else if ((s7 == 1) && (s5 == 1) && (s0 == 0))
    {
     // rightAngleRight();
      activeLineFollowing = false;
      wait(200);
    }
    else if ((s0 == 0) && (s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0))
    {
      turnAround();
    }
    else if (directionCalc >= -2 && directionCalc <= 2)
    {
      forwards();
    }
    else if (directionCalc >= -6 && directionCalc <= -3)
    {
      slowLeft();
    }
    else if (directionCalc <= 6 && directionCalc >= 3)
    {
      slowRight();
    }
    else if (directionCalc < -6)
    {
      sharpLeft();
    }
    else if (directionCalc > 6)
    {
      sharpRight();
    }
  }
  else
  {
    if(s2 == 1 || s3 == 1 || s4 == 1 || s5 == 1)
      {
        activeLineFollowing=true;
        loop();
      }
      else if(s3 == 0 || s4 == 0)
      {
        rightAngleRight();
        activeLineFollowing=true;
        loop();
      }
  }
}

//=====================||END OF LINE FOLLOWING FUNCTIONS||====================================                          END OF LINE FOLLOWING FUNCTIONS

//=====================||PATTERN RECOGNITION FUNCTIONS||======================================
// MAYBE PATTERN RECOGNITION SHOULD BE DONE IN THE LOOP AND NOT IN ITS OWN FUNCTIONS
// ON THE OTHER HAND I STILL NEED TO FIGURE OUT HOW TO TELL THE CAR TO CHECK ---> STORE DATA ---> MOVE FORWARD ---> CHECK AGAIN ---> COMPARE ---> DECIDE
//=====================||END OF PATTERN RECOGNITION FUNCTIONS||===============================

void loop()
{
  makeIRReadings();
  printIRReadings();
  // printEncoderMesurements();
  followLine();
}
