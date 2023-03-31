//INCLUDED LIBRARIES

#include <Adafruit_NeoPixel.h>
#include <Servo.h>



//================ start of Neopixels pins====================
#define PIN 13          // Set the pin for NeoPixel data input
#define NUM_PIXELS 4    // Set the number of pixels in your NeoPixel strip

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);
//============ end of Neopixels pins=========================

// Define the sensor pins
const int sensorPin1 = A0; // Sensor pin 1
const int sensorPin2 = A1; // Sensor pin 2
const int sensorPin3 = A2; // Sensor pin 3
const int sensorPin4 = A3; // Sensor pin 4
const int sensorPin5 = A4; // Sensor pin 5
const int sensorPin6 = A5; // Sensor pin 6
const int sensorPin7 = A6; // Sensor pin 7
const int sensorPin8 = A7; // Sensor pin 8

unsigned long duration, distance = 30;

// Define distance sensor pins
#define Trig 7
#define Echo 8

#define distanceThreshold 15 // threshold distance in cm to detect an obstacle



// Define the pins for the left and right motor drivers
const int rightMotorPin1 = 6;
const int rightMotorPin2 = 5;
const int leftMotorPin1 = 10;
const int leftMotorPin2 = 9;

// Define the servo and gripper pins
Servo gripper;
int gripperPin = 12;
int pinServo = 12;

// Set the int needed
int s0;
int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
int s7;
int endLineCounter = 0;

const byte interruptPin1 = 2;
const byte interruptPin2 = 3;
int counter1 = 0;
int counter2 = 0;
volatile byte state = LOW;

int inter = 2;

// Define the motor speed
const int motorSpeed = 255;

// Define the threshold for detecting the black line
const int threshold = 800;

// Some functions declaration
bool startLineFunctionExecuted = false;
bool endLineFunctionExecuted = false;


unsigned long time, lasttime;

//================ START OF SETUP  ====================
void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Initialize the Neopixel strip
  pixels.begin();

  // Set distance sensor pins
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  // Set the motor pins as output
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  pinMode(gripperPin, OUTPUT);

  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), counterLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), counterRight, CHANGE);
}

//================ END OF SETUP  ===============================================

//================ START OF LOOP  ===============================================
void loop() {

  
  //========start of loop for neopixels=========================================
  // Set the color of the first pixel to red
  pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // Red

  // Set the color of the second pixel to green
  pixels.setPixelColor(1, pixels.Color(0, 255, 0)); // Green

  // Set the color of the third pixel to blue
  pixels.setPixelColor(2, pixels.Color(0, 0, 255)); // Blue

  // Set the color of the fourth pixel to pink
  pixels.setPixelColor(3, pixels.Color(0, 0, 255)); // Pink

  // Show the updated colors on the Neopixel strip
  pixels.show();

  //======== end of loop for neopixels=========================================
  
  if (!startLineFunctionExecuted) {

    startLine();

    startLineFunctionExecuted = true;
  }

  if (endLineCounter > 1) {
    halt();
  }

  // Measure distance to nearby objects us bing the ultrasonic sensor
  
 unsigned long time1 = millis();
  
  if( time1 > 10000) 
  {
 distanceMeasure();
  }

  
  if (distance < 13 ) {
    Serial.println("Long sentence to see iif this function gets triggered easily");
    avoidObstacle();
    findLine();
  }
  
  // Read the sensor values
  int sensor1 = analogRead(sensorPin1);
  int sensor2 = analogRead(sensorPin2);
  int sensor3 = analogRead(sensorPin3);
  int sensor4 = analogRead(sensorPin4);
  int sensor5 = analogRead(sensorPin5);
  int sensor6 = analogRead(sensorPin6);
  int sensor7 = analogRead(sensorPin7);
  int sensor8 = analogRead(sensorPin8);

  // Print the sensor readings in the serial monitor
  Serial.print(sensor1);
  Serial.print("\t");
  Serial.print(sensor2);
  Serial.print("\t");
  Serial.print(sensor3);
  Serial.print("\t");
  Serial.print(sensor4);
  Serial.print("\t");
  Serial.print(sensor5);
  Serial.print("\t");
  Serial.print(sensor6);
  Serial.print("\t");
  Serial.print(sensor7);
  Serial.print("\t");
  Serial.print(sensor8);
  Serial.println();

  if (sensor1 > 900 && sensor2 > 900 && sensor3 > 900 && sensor4 > 900 && sensor5 > 900 && sensor6 > 900 && sensor7 > 900 && sensor8 > 900) {
    goforward();
    delay(100);
    // Read the sensor values again
    int sensor1 = analogRead(sensorPin1);
    int sensor2 = analogRead(sensorPin2);
    int sensor3 = analogRead(sensorPin3);
    int sensor4 = analogRead(sensorPin4);
    int sensor5 = analogRead(sensorPin5);
    int sensor6 = analogRead(sensorPin6);
    int sensor7 = analogRead(sensorPin7);
    int sensor8 = analogRead(sensorPin8);

    if (sensor1 > 950 && sensor2 > 950 && sensor3 > 950 && sensor4 > 950 && sensor5 > 950 && sensor6 > 950 && sensor7 > 950 && sensor8 > 950) {
      halt();

      openGripper();
      delay(500); // Wait for the gripper to open
      moveBack();
      delay(1000);
      endLineCounter++;
    }
  }

  else if (sensor1 > threshold || sensor2 > threshold || sensor3 > threshold) {
    turnLeft();
  }
  else if (sensor3 > threshold) {
    turnLeft();
  }
  else if (sensor7 > threshold || sensor8 > threshold) {
    turnRight();
  }
  else if (sensor6 > threshold) {
    turnRight();
  }
  else if (sensor4 > threshold || sensor5 > threshold ) {
    goforward();
  }
}


void avoidObstacle() {
  // Set the speed and duration of the turn
  int turnDuration = 300;
  int turn2Duration = 450;
  int driveDuration = 600;
  int drive2Duration = 500;

  // Turn left for turnDuration milliseconds
  unsigned long startTime = millis();
  while (millis() - startTime < turnDuration) {
    turnLeftObstacle(); // It turns left somehow
  }

  startTime = millis();
  while (millis() - startTime < driveDuration) {
    goforward();
  }
  // Drive forward for a short time

  startTime = millis();
  while (millis() - startTime < turn2Duration) {
    turnRightObstacle();
 // Turn right for short amount of time
  }
}

// function needed to find line
void findLine() {

  int linedetector = 0;

  while (linedetector == 0) {

    int sensor1 = analogRead(sensorPin1);
    int sensor2 = analogRead(sensorPin2);
    int sensor3 = analogRead(sensorPin3);
    int sensor4 = analogRead(sensorPin4);
    int sensor5 = analogRead(sensorPin5);
    int sensor6 = analogRead(sensorPin6);
    int sensor7 = analogRead(sensorPin7);
    int sensor8 = analogRead(sensorPin8);

    goforward();

    // go forward until it detects line

    if (sensor1 > 700 || sensor2 > 700 || sensor3 > 700 || sensor4 > 700 || sensor5 > 700 || sensor6 > 700 || sensor7 > 700 || sensor8 > 700) {
      linedetector = 1;
    }
  }
}

//================ END OF LOOP  ===============================================================

//================ START FUNCTION DECLARATIONS  ===============================================
// Function definition for moving forward
void goforward() {
  if (counter1 <= inter && counter2 <= inter) {
    // Move both motors forward
    analogWrite(leftMotorPin1, 255);
    analogWrite(leftMotorPin2, 0);
    analogWrite(rightMotorPin1, 255);
    analogWrite(rightMotorPin2, 0);
  } else {
    halt();
    counterReset();
  }
}

// Define function to turn left
void turnLeft() {
  if (counter1 <= inter && counter2 <= inter) {
    analogWrite(leftMotorPin1, 0);
    analogWrite(leftMotorPin2, 0);
    analogWrite(rightMotorPin1, 200);
    analogWrite(rightMotorPin2, 0);
  } else {
    halt();
    counterReset();
  }
}

// Define function to turn left to avoid obstacle
void turnLeftObstacle() {
  if (counter1 <= inter && counter2 <= inter) {
    analogWrite(leftMotorPin1, 0);
    analogWrite(leftMotorPin2, 255);
    analogWrite(rightMotorPin1, 255);
    analogWrite(rightMotorPin2, 0);
  } else {
    halt();
    counterReset();
  }
}

// Define function to turn right to avoid obstacle
void turnRightObstacle() {
  if (counter1 <= inter && counter2 <= inter) {
    analogWrite(leftMotorPin1, 255);
    analogWrite(leftMotorPin2, 0);
    analogWrite(rightMotorPin1, 0);
    analogWrite(rightMotorPin2, 255);
  } else {
    halt();
    counterReset();
  }
}
// Define function to turn slow left
void slowLeft() {
  if (counter1 <= inter && counter2 <= inter) {
    analogWrite(leftMotorPin1, 155);
    analogWrite(leftMotorPin2, 0);
    analogWrite(rightMotorPin1, 255);
    analogWrite(rightMotorPin2, 0);
  } else {
    halt();
    counterReset();
  }
}

// Define function to turn slow right
void slowRight() {
  if (counter1 <= inter && counter2 <= inter) {
    analogWrite(leftMotorPin1, 255);
    analogWrite(leftMotorPin2, 0);
    analogWrite(rightMotorPin1, 155);
    analogWrite(rightMotorPin2, 0);
  } else {
    halt();
    counterReset();
  }
}

// Define function to turn right
void turnRight() {
  if (counter1 <= inter && counter2 <= inter) {
    analogWrite(leftMotorPin1, 200
               );
    analogWrite(leftMotorPin2, 0);
    analogWrite(rightMotorPin1, 0);
    analogWrite(rightMotorPin2, 0);
  } else {
    halt();
    counterReset();
  }
}

// Define function to halt
void halt() {
  analogWrite(leftMotorPin1, 0);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 0);
  analogWrite(rightMotorPin2, 0);
}

// Define function to counterLeft
void counterLeft() {
  noInterrupts();
  counter1++;
  interrupts();
}

// Define function to counterRight
void counterRight() {
  noInterrupts();
  counter2++;
  interrupts();
}

// Define function to counterReset
void counterReset() {
  counter1 = 0;
  counter2 = 0;
}

// Define function to move from parking spot
void startLine() {
  moveForward();
  delay(500);

  closeGripper();
  Leftturn ();
  moveForward();
  delay(50);
}

// Function definition for moving forward

void moveForward() {
  analogWrite(leftMotorPin1, 255);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 255);
  analogWrite(rightMotorPin2, 0);
}

// Function definition for moving backward
void moveBack() {
  analogWrite(leftMotorPin1, 0);
  analogWrite(leftMotorPin2, 255);
  analogWrite(rightMotorPin1, 0);
  analogWrite(rightMotorPin2, 255);
}

//Function definition to Turn left
void Leftturn() {
  analogWrite(leftMotorPin1, 150);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 0);
  analogWrite(rightMotorPin2, 0);
  delay(1000);
}

//Function definition to close Gripper
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

//Function definition to open Gripper
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

//Function definition for dropping the cone and moving backwards
void endLine() {
  openGripper();
  delay(500);
  moveBack();
  delay(500);
  closeGripper();
  halt();
  delay(50);
  endLineCounter++;
}

// Function needed to read ultra-sonic sensor values
void distanceMeasure()
{
  
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration * 0.034/2;
  Serial.println(distance);
    // Print distance sensor readings
}




//================ END FUNCTION DECLARATIONS  ===============================================
