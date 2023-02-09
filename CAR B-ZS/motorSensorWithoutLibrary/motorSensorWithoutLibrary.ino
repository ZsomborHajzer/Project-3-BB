
//===================||WHEEL SENSOR PINS AND VARIABLES||====================
#define encoderRW 2 // 36 signals for a 90 degree turn
#define encoderLW 3
int countRW = 0;
int countLW = 0;
//========================================================================
//================||WHEEL MOTOR PINS|| ==================================
const int LWF = 10;
const int LWB = 9;
const int RWF = 6;
const int RWB = 5;
//========================================================================

void setup(){
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

//=====================||ENCODER FUNCTIONS||====================================
void updateRW() {
  noInterrupts();
  countRW++;
  interrupts();
}

void updateLW() {
  noInterrupts();
  countLW++;
  interrupts();
}

void printSensorMesurements(){
  Serial.print("Right Wheel: ");
  Serial.print(countRW);
  Serial.print(" , ");
  Serial.print("Left Wheel: ");
  Serial.println(countLW);
}

void resetCounters(){
  countRW = 0;
  countLW = 0;
}

//=====================||END OF ENCODER FUNCTIONS||====================================

//=====================||DIRECTION FUNCTIONS||==========================================
void rightAngleRight()
{
  analogWrite(RWF, 0);
  analogWrite(RWB, 0);
  analogWrite(LWF, 255);
  analogWrite(LWB, 0);
  if (countLW > 28){
    carStop();
  }
}

void rightAngleLeft()
{ 
  
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 0);  
  if (countRW > 28){
    carStop();
  }
}

void turnAround()
{
  
  analogWrite(RWF, 255);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 255);  
  if (countRW > 23 && countLW > 23){
    carStop();
  }
}

void carStop()
{
  analogWrite(RWF, 0);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 0);
}

//=====================||END OF DIRECTION FUNCTIONS||==========================================

void loop(){
  printSensorMesurements();
 turnAround();
  
  delay(100);
 
}
