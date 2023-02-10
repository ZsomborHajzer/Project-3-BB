
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

int directionCalc;
int sensorTreshMark = 600;

boolean IRActive= true;

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

//======================||IR SENSOR FUNCTIONS||=================================                                               END OF SETUP
void makeIRReadings()
{
  
  s0 = analogRead(IR);
  s1 = analogRead(IR1);
  s2 = analogRead(IR2);
  s3 = analogRead(IR3);
  s4 = analogRead(IR4);
  s5 = analogRead(IR5);
  s6 = analogRead(IR6);
  s7 = analogRead(IR7);

  if (s0 > sensorTreshMark)
  {
    s0 = 1;
  }
  else if (s0 <= sensorTreshMark)
  {
    s0 = 0;
  }

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
  }  


void printIRReadings(){
  
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
void updateRW() {
  noInterrupts();
  
  countRW =countRW + 1;
  
  interrupts();
}

void updateLW() {
  noInterrupts();
  
  countLW++;
  
  interrupts();
}

void printEncoderMesurements(){

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

//=====================||END OF ENCODER FUNCTIONS||====================================                                     END OF ENCODEDR SENSOR FUNCTION

//=====================||TURN DIRECTION FUNCTIONS||==========================================

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

/*void turnAround()
{
  IRActive = false;
  resetCounters(); 
  
  if((countRW > 26 ) || (countLW > 26)){
    resetCounters();
    IRActive = true;
    exit(0);
  } else if((countRW <= 26 )|| (countLW <= 26)){ 
  printEncoderMesurements();
  analogWrite(RWF, 180);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 180);  
  }
  
  
}*/

void turnAround()
{
  
  IRActive = false;
  resetCounters(); 
  carStop();
  delay(500);
  
  while (countLW < 35) {
  printEncoderMesurements();
  analogWrite(RWF, 180);
  analogWrite(RWB, 0);
  analogWrite(LWF, 0);
  analogWrite(LWB, 180);  
  }
  
 resetCounters();
 IRActive = true;
 carStop();
 delay(500);
 loop();
  
}




//=====================||END OF TURN DIRECTION FUNCTIONS||====================================                            END OF TURN DIRECTION FUNCTIONS
//=====================||LINE FOLLOWING DIRECTION FUNCTIONS||=================================         

void forwards(){
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

//=====================||LINE FOLLOWING FUNCTIONS||===========================================

void followLine() {
  if (IRActive == true) {
  if (
    ((s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 0))||
    ((s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))||
    ((s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))||
    ((s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))||
    ((s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0))||
    ((s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 0))||
    ((s2 == 0) && (s3 == 1) && (s4 == 0) && (s5 == 0))){
      
    forwards();
  
  }else if(s1 == 1) {
    slowLeft();
  }else if( s6 == 1){
    slowRight();
  }else if(s0 == 1){
    sharpLeft();
  }else if(s7 == 1){
    sharpRight();
  }else if((s0 == 0)&&(s1 == 0)&&(s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0)) {
    turnAround(); 
  }/*else if ((s0 == 1)&&(s1 == 1)&&(s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0) && (s6 == 0) && (s7 == 0)){
    turnLeft();
  }else if ((s0 == 0)&&(s1 == 0)&&(s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1)){
    turnRight();
  }*/
 }
}


//=====================||END OF LINE FOLLOWING FUNCTIONS||====================================                          END OF LINE FOLLOWING FUNCTIONS

//=====================||PATTERN RECOGNITION FUNCTIONS||======================================
// MAYBE PATTERN RECOGNITION SHOULD BE DONE IN THE LOOP AND NOT IN ITS OWN FUNCTIONS
//ON THE OTHER HAND I STILL NEED TO FIGURE OUT HOW TO TELL THE CAR TO CHECK ---> STORE DATA ---> MOVE FORWARD ---> CHECK AGAIN ---> COMPARE ---> DECIDE
//=====================||END OF PATTERN RECOGNITION FUNCTIONS||===============================

void loop(){

makeIRReadings();
printEncoderMesurements();
followLine();

}
