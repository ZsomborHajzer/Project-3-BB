// defines arduino pins numbers
const int trigPin = 2;
const int echoPin = 3;

// defines variables
long duration;
int distance;

const int trigPinFront = 4;
const int echoPinFront = 5;

// defines variables
long durationFront;
int distanceFront;

void setup() 
{  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(trigPinFront, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinFront, INPUT); // Sets the echoPin as an Input
  
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
 distancePrint();
}

void distancePrint()
{
   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  
  //Prints the distance on the Serial Monitor
  Serial.print("Distance from the object = ");
  Serial.print(distance);
  Serial.println(" cm");  
  delay(150);

// <<-------------- FRONT SENSOR ------------>>

  // Clears the trigPin
  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationFront = pulseIn(echoPinFront, HIGH);
  
  // Calculating the distance
  distanceFront= durationFront*0.034/2;
  
  //Prints the distance on the Serial Monitor
  Serial.print("Distance FRONT from the object = ");
  Serial.print(distanceFront);
  Serial.println(" cm");  
  delay(150);
  
  }
