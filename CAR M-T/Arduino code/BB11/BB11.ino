
// Define the sensor pins
const int sensorPin1 = A0; // Sensor pin 1
const int sensorPin2 = A1; // Sensor pin 2
const int sensorPin3 = A2; // Sensor pin 3
const int sensorPin4 = A3; // Sensor pin 4
const int sensorPin5 = A4; // Sensor pin 5
const int sensorPin6 = A5; // Sensor pin 6
const int sensorPin7 = A6; // Sensor pin 7
const int sensorPin8 = A7; // Sensor pin 8

// Define distance sensor pins
#define Trig 7
#define Echo 8

#define distanceThreshold 15 // threshold distance in cm to detect an obstacle


// Define the pins for the left and right motor drivers
const int rightMotorPin1 = 6;
const int rightMotorPin2 = 5;
const int leftMotorPin1 = 10;
const int leftMotorPin2 = 9;


const byte interruptPin1 = 2;
const byte interruptPin2 = 3;
int counter1 = 0;
int counter2 = 0;
volatile byte state = LOW;

int inter = 2;

// Define the motor speed
const int motorSpeed = 255;

// Define the threshold for detecting the black line
const int threshold = 700;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  
  // Set distance sensor pins
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  // Set the motor pins as output
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), counterLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), counterRight, CHANGE);
}

void loop() {

  // Measure distance to nearby objects using the ultrasonic sensor
  long duration, distance;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = duration * 0.034 / 2;

// Print distance sensor readings
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();

  if(distance == 14 || distance == 15 || distance == 16){
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

  if(sensor1 > 950 && sensor2 > 950 && sensor3 > 950 && sensor4 > 950 && sensor5 > 950 && sensor6 > 950 && sensor7 > 950 && sensor8 > 950){
  halt;
  }
  else if(sensor4 > threshold && sensor5 > threshold ){
    goforward();
    }
    else if(sensor1 > threshold && sensor2 > threshold){
      turnLeft();
      }
      else if(sensor3 > threshold){
        slowLeft();
        }
        else if(sensor7 > threshold && sensor8 > threshold){
          turnRight();
          }
          else if(sensor6 > threshold){
            slowRight();
            }
}




void avoidObstacle() {
  // Set the speed and duration of the turn
  int turnDuration = 300;
  int turn2Duration = 400;
  int driveDuration = 800;
  int drive2Duration = 600;

  // Turn left for turnDuration milliseconds
  int startTime = millis();
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
  }

}

void findLine(){

  int linedetector = 0;
  
  while(linedetector == 0){

  int sensor1 = analogRead(sensorPin1);
  int sensor2 = analogRead(sensorPin2);
  int sensor3 = analogRead(sensorPin3);
  int sensor4 = analogRead(sensorPin4);
  int sensor5 = analogRead(sensorPin5);
  int sensor6 = analogRead(sensorPin6);
  int sensor7 = analogRead(sensorPin7);
  int sensor8 = analogRead(sensorPin8);
  
  goforward();
  
  if(sensor1 > 700 || sensor2 > 700 || sensor3 > 700 || sensor4 > 700 || sensor5 > 700 || sensor6 > 700 || sensor7 > 700 || sensor8 > 700){
    linedetector = 1;
    }
  }
  
}


// Function definition for moving forward
void goforward() {
  if(counter1 <= inter && counter2<= inter) {
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
  if(counter1 <= inter && counter2<= inter) {
  analogWrite(leftMotorPin1, 50);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 250);
  analogWrite(rightMotorPin2, 0);
  }else {
    halt();
    counterReset();
  }
}

void turnLeftObstacle() {
  if(counter1 <= inter && counter2<= inter) {
  analogWrite(leftMotorPin1, 0);
  analogWrite(leftMotorPin2, 250);
  analogWrite(rightMotorPin1, 250);
  analogWrite(rightMotorPin2, 0);
  }else {
    halt();
    counterReset();
  }
}

void turnRightObstacle() {
  if(counter1 <= inter && counter2<= inter) {
  analogWrite(leftMotorPin1, 250);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 0);
  analogWrite(rightMotorPin2, 250);
  }else {
    halt();
    counterReset();
  }
}

void slowLeft() {
  if(counter1 <= inter && counter2<= inter) {
  analogWrite(leftMotorPin1, 200);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 255);
  analogWrite(rightMotorPin2, 0);
  }else {
    halt();
    counterReset();
  }
}

void slowRight() {
  if(counter1 <= inter && counter2<= inter) {
  analogWrite(leftMotorPin1, 255);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 200);
  analogWrite(rightMotorPin2, 0);
  }else {
    halt();
    counterReset();
  }
}

// Define function to turn right
void turnRight() {
  if(counter1 <= inter && counter2<= inter) {
  analogWrite(leftMotorPin1, 250);
  analogWrite(leftMotorPin2, 0);
  analogWrite(rightMotorPin1, 50);
  analogWrite(rightMotorPin2, 0);
}else {
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

void counterLeft() {
  noInterrupts();
  counter1++;
  interrupts();
}

void counterRight() {
  noInterrupts();
  counter2++;
  interrupts();
}

void counterReset() {
  counter1 = 0;
  counter2 = 0;
}
