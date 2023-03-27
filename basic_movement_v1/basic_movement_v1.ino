#include "TimerOne.h"

const int motorA1 = 12;
const int motorA2 = 11;
const int motorB1 = 10;  
const int motorB2 = 9;

int speed = 255;

void setup() {
  
  pinMode (motorA1, OUTPUT);
  pinMode (motorA2, OUTPUT);
  pinMode (motorB1, OUTPUT);
  pinMode (motorB2, OUTPUT);
  
}

void loop() {
  goRight();

}

void goBack()
{
  analogWrite(motorA1, 0);
  analogWrite(motorA2, speed);
  analogWrite(motorB1, speed);
  analogWrite(motorB2, 0);
}

void goForward()
{
  digitalWrite(motorA1, speed);
  digitalWrite(motorA2, 0);
  digitalWrite(motorB1, 0);
  digitalWrite(motorB2, speed);
  }

void goRight()
{
  digitalWrite(motorA1, speed);
  digitalWrite(motorA2, 0);
  digitalWrite(motorB1, speed);
  digitalWrite(motorB2, 0);
}

void goLeft()
{
  digitalWrite(motorA1, 0);
  digitalWrite(motorA2, speed);
  digitalWrite(motorB1, 0);
  digitalWrite(motorB2, speed);
  
}
