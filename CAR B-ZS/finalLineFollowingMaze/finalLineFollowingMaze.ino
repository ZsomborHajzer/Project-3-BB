
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

int pinServo = 7;

int directionCalc;
int sensorTreshMark = 800;
boolean intersectionDecision = true;
boolean endCheck = true;
boolean activeIRReading = true;
unsigned long time;
int finishDanceSequenceCounter = 0;

int blackBlockCounter = 0;
boolean startProgram = true;

//========================|| Distance Sensor pins/variables || =================

int trigPin = 8;    // Trigger
int echoPin = 4;    // Echo
volatile long duration, cm;

//==============================================================================

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
  // Initialize hardware
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinServo, OUTPUT);
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
  if (activeIRReading == true)
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

void printIRReadings() // For testing
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
  wait(200);

  while (countLW < 22)
  {
    printEncoderMesurements();
    analogWrite(RWF, 242);
    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
    analogWrite(LWB, 255);
  }
  resetCounters();

  while (countLW <= 15)
  {
    printEncoderMesurements();
    analogWrite(RWF, 0);
    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
    analogWrite(LWB, 255);
  }
  resetCounters();

  while (countLW <= 23)
  {
    printEncoderMesurements();
    analogWrite(RWF, 0);
    analogWrite(RWB, 242);
    analogWrite(LWF, 0);
    analogWrite(LWB, 255);
  }

  resetCounters();
  carStop();
  closeGripper();
  wait(200);
  loop();
}

void rightAngleRight()
{
  resetCounters();
  carStop();
  wait(200);

  while (countLW < 3)
  {
    printEncoderMesurements();
    analogWrite(RWF, 255);
    analogWrite(RWB, 0);
    analogWrite(LWF, 255);
    analogWrite(LWB, 0);
  }
  resetCounters();
  carStop();
  wait(200);

  while (countLW < 35)
  {
    printEncoderMesurements();
    analogWrite(RWF, 0);
    analogWrite(RWB, 0);
    analogWrite(LWF, 255);
    analogWrite(LWB, 0);
  }
  resetCounters();
  carStop();
  closeGripper();
  wait(200);
  loop();
}

void rightAngleLeft()
{
  carStop();
  wait(200);
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
  closeGripper();
  wait(200);
  loop();
}

void carBackwards()
{
  resetCounters();
  while (countRW <= 20)
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
  analogWrite(RWF, 242);
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
  analogWrite(RWF, 150);
  analogWrite(RWB, 0);
  analogWrite(LWF, 242);
  analogWrite(LWB, 0);
}

void slowLeft()
{
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 158);
  analogWrite(LWB, 0);
}

//=====================||END OF LINE FOLLOWING DIRECTION FUNCTIONS||==========================                          END OF LINE FOLLOWING DIRECTION FUNCTIONS

//=====================||Gripper Functions||==========================

void openGripper()
{
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(pinServo, HIGH);
    delayMicroseconds(1500);
    digitalWrite(pinServo, LOW);
    delay(10);
  }
}

// forloop 8-10x
void closeGripper()
{
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(pinServo, HIGH);
    delayMicroseconds(1000);
    digitalWrite(pinServo, LOW);
    delay(10);
  }
}

//=====================||END OF Gripper Functions||==========================

//=====================|| Wait FUNCTIONS||============================

void wait(int timeToWait)
{
  time = millis();
  carStop();
  while (millis() < time + timeToWait);
}
//=====================||END OF WAIT FUNCTIONS||=====================


// ====================|| START / END SEQUENCE || ===================
void startProgramFun()
{
  carStop();
  openGripper();
  wait(1000);
  resetCounters();

  while (countLW < 39)
  {
    printEncoderMesurements();
    analogWrite(RWF, 222);
    analogWrite(RWB, 0);
    analogWrite(LWF, 234 );
    analogWrite(LWB, 0);
  }
  resetCounters();
  carStop();
  wait(1000);
  closeGripper();
  wait(1000);
  startProgram = false;
  rightAngleLeft();
}

void endProgramFun()
{
  finishDanceSequenceCounter++;
  if (finishDanceSequenceCounter == 1)
  {
    openGripper();
    resetCounters();
    while (countRW <= 60) // DANCE Sequence
    {
      printEncoderMesurements();
      analogWrite(RWF, 0);
      analogWrite(RWB, 255);
      analogWrite(LWF, 0);
      analogWrite(LWB, 255);
    }
    resetCounters();

    for (int i = 0; i < 5; i++)
    {
      resetCounters();

      while (countRW <= 45)
      {
        printEncoderMesurements();
        analogWrite(RWF, 255);
        analogWrite(RWB, 0);
        analogWrite(LWF, 0);
        analogWrite(LWB, 255);
      }

      resetCounters();

      while (countLW <= 45)
      {
        printEncoderMesurements();
        analogWrite(RWF, 0);
        analogWrite(RWB, 255);
        analogWrite(LWF, 255);
        analogWrite(LWB, 0);
      }

      resetCounters();
      for (int j = 0; j < 10; j++)
      {
        for (int i = 0; i < 10; i++) // Close Grippers
        {
          digitalWrite(pinServo, HIGH);
          delayMicroseconds(1100);
          digitalWrite(pinServo, LOW);
          delay(10);
        }

        for (int i = 0; i < 10; i++) // Open Grippers
        {
          digitalWrite(pinServo, HIGH);
          delayMicroseconds(1600);
          digitalWrite(pinServo, LOW);
          delay(10);
        }
      }
    }
    intersectionDecision = false;
    endCheck = false;
    loop();
  }
}

// ====================|| END OF START / END SEQUENCE || ===================

//=====================||LINE FOLLOWING FUNCTIONS||===========================================

void followLine()
{
  if (startProgram == false)
  {
    if (intersectionDecision == true && endCheck == true)
    {
      if ((s0 == 1) && (s7 == 1))
      {
        endCheck = false;
        wait(200);
      }
      else if ((s0 == 1) && (s2 == 1) && (s7 == 0))
      {
        rightAngleLeft();
      }
      else if ((s7 == 1) && (s5 == 1) && (s0 == 0))
      {
        intersectionDecision = false;
        wait(200);
      }
      else if ((s0 == 0) && (s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0))
      {
        turnAround();
      }
      else if (directionCalc >= -1 && directionCalc <= 1)
      {
        forwards();
      }
      else if (directionCalc >= -6 && directionCalc <= -2)
      {
        slowLeft();
      }
      else if (directionCalc <= 6 && directionCalc >= 2)
      {
        slowRight();
      }
      else if (directionCalc < -6)
      {
        slowLeft();
      }
      else if (directionCalc > 6)
      {
       slowRight();
      }
    }
    else if (intersectionDecision == false && endCheck == true)
    {
      if (s2 == 1 || s3 == 1 || s4 == 1 || s5 == 1)
      {
        intersectionDecision = true;
        loop();
      }
      else if (s3 == 0 || s4 == 0)
      {
        rightAngleRight();
        intersectionDecision = true;
        loop();
      }
    }
    else if (intersectionDecision == true && endCheck == false)
    {
      if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1 && s6 == 1)
      {

        endProgramFun();
      }
      else if (s2 == 1 || s3 == 1 || s4 == 1 || s5 == 1)
      {
        endCheck = true;
        loop();
      }
      else if (s3 == 0 && s4 == 0)
      {
        rightAngleLeft();
        endCheck = true;
        loop();
      }
    }
    else if (intersectionDecision == false && endCheck == false)
    {
      carStop();
    }
  }
}
//=====================||END OF LINE FOLLOWING FUNCTIONS||====================================                          END OF LINE FOLLOWING FUNCTIONS

//=====================||Distance Sensing||======================================

void distanceSensing()
{
  if(startProgram == true)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = (duration/2) / 29.1; 
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();  
    if(cm < 24){
      startProgramFun();
    }
  }
}
//=====================||END OF Distance Sensing FUNCTIONS||===============================

void loop()
{
  distanceSensing();
  makeIRReadings();
  followLine();
}
