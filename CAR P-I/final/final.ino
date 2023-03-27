<<<<<<< HEAD
=======
/*
    pins definition

    RWF - right wheel forward
    RWB - right wheel backward

    LWF / LWB - left wheel

    encoderRW / encoderLW - right / left wheel encoder

    fProxEcho / fProxTrig - front proximity sensor echo / trigger
    lProxEcho / lProxTrig - proximity sensor on the left side, echo / trigger
*/
>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb

#define RWF 6
#define RWB 5

#define LWF 10
#define LWB 9

#define encoderRW 2
#define encoderLW 3

#define fProxEcho 11
#define fProxTrig 12

#define lProxEcho 7
#define lProxTrig 8

<<<<<<< HEAD
float forwardDistance = 0;
float leftDistance = 0;
bool goingForward = false;

unsigned long countRW = 0;
unsigned long countLW = 0;


void setup()
{

    Serial.begin(9600);
    pinMode(RWF,OUTPUT);
    pinMode(RWB,OUTPUT);
    pinMode(LWF,OUTPUT);
    pinMode(LWB,OUTPUT);
    
=======
float forwardDistance = .0f;
float leftDistance = .0f;

unsigned int countRW = 0;
unsigned int countLW = 0;

void setup()
{
    Serial.begin(9600);

    // can be left out as it does nothing

    // pinMode(RWF, OUTPUT);
    // pinMode(RWB, OUTPUT);

    // pinMode(LWF, OUTPUT);
    // pinMode(LWB, OUTPUT);

>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb
    pinMode(fProxEcho, INPUT);
    pinMode(fProxTrig, OUTPUT);

    pinMode(lProxEcho, INPUT);
    pinMode(lProxTrig, OUTPUT);

    pinMode(encoderRW, INPUT);
    pinMode(encoderLW, INPUT);
<<<<<<< HEAD
    attachInterrupt(digitalPinToInterrupt(encoderRW), updateRW, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderLW), updateLW, CHANGE);
  
}

//===================================|| MAZE GO STRAIGHT FUNCTION || =======================
void goForwardToWall()
{
    if (leftDistance > 9.2)
    {
        analogWrite(RWF, 255);
        // analogWrite(LWF, 232 - 10 * (leftDistance - 7));
        analogWrite(LWF, 192);
    }
    else if (leftDistance < 7.2)
    {
        analogWrite(RWF, 205);
        // analogWrite(RWF, 255 - 10 * abs(leftDistance - 4));
        analogWrite(LWF, 232);
=======

    attachInterrupt(digitalPinToInterrupt(encoderRW), updateRW, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderLW), updateLW, CHANGE);
}

void loop()
{
    querySensors();

    if (leftDistance > 25)
    {
        stop();
        wait(150);
        return performLeftTurn();
    }

    goForward();
}

// movement functions

void goForward()
// the function defines the behaviour of the car when it is going forward
// it adjusts the car so that it is constantly 8.2 cm away from the wall
{
    if (leftDistance > 4)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 180);
    }
    else if (leftDistance < 3)
    {
        // TODO: should be reviewed as the left wheel is not using max speed
        analogWrite(RWF, 225);
        analogWrite(LWF, 255);
>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb
    }
    else
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232);
    }
}

<<<<<<< HEAD

//===================================|| END OF MAZE GO STRAIGHT FUNCTION || =======================

//===================================|| ENCODER FUNCTIONS || ======================================
=======
void goInTicks(int ticks)
// moves the car forward for a given number of ticks
{
    resetCounters();

    while (countRW < ticks)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232);

        // Serial.println(String(countRW) + "/" + String(ticks));
        Serial.println("");
    }

    stop();
}

void performLeftTurn()
{
    goInTicks(15);
    wait(300);

    basicTurnLeft();
    wait(300);

    goInTicks(10);
}

void stop()
{
    analogWrite(RWF, 0);
    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
    analogWrite(LWB, 0);
}

// basic movement functions
// they are simple functions to turn precisely

void basicTurnLeft()
{
    stop();

    resetCounters();
    while (countLW < 14)
    {
        analogWrite(RWF, 255);
        analogWrite(LWB, 254);

        // Serial.println(String(countLW) + "/" + String(14));
        Serial.println("");
    }

    stop();
}

// counter functions
// used to update the counters of the encoders

>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb
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
<<<<<<< HEAD
{
    Serial.print("Right Wheel: ");
    Serial.print(countRW);
    Serial.print(" , ");
    Serial.print("Left Wheel: ");
    Serial.println(countLW);
=======
// TODO: be removed on release
{
    Serial.println("Left wheel: " + String(countLW) + ", right wheel:" + String(countRW));
>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb
}

void resetCounters()
{
    countRW = 0;
    countLW = 0;
}

<<<<<<< HEAD
//===================================|| END OF ENCODER FUNCTIONS|| ================================

//===================================|| DISTANCE MEASUREMENT SENSORS|| ============================
void querySensors()
=======
// sound sensors functions

void querySensors()
// TODO: might be optimised as the sensors always get queried together
>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb
{
    forwardDistance = getForwardDistance();
    leftDistance = getLeftDistance();
}

float pulse(int proxTrig, int proxEcho)
<<<<<<< HEAD
=======
// might be renamed as it returns the distance in cm
// TODO: also might be optimised as the sensors always get queried together
>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb
{
    digitalWrite(proxTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(proxTrig, LOW);

    float duration_us = pulseIn(proxEcho, HIGH);

    return duration_us * .017;
}

float getForwardDistance()
<<<<<<< HEAD
=======
// returns forward distance in cm
>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb
{
    return round(pulse(fProxTrig, fProxEcho) * 100.0) / 100.0;
}

float getLeftDistance()
<<<<<<< HEAD
{
    return round(pulse(lProxTrig, lProxEcho) * 100.0) / 100.0;
}
//===================================|| END OF DISTANCE MEASUREMENTS || ===========================

void loop()
{
    querySensors();
    goForwardToWall();
=======
// returns left distance in cm
{
    return round(pulse(lProxTrig, lProxEcho) * 100.0) / 100.0;
}

// other functions

void wait(int timeToWait)
// waits for an amount of time in milliseconds
// used to eliminate the need to use the delay() function
{
    long time = millis();

    while (millis() < time + timeToWait)
        ;
>>>>>>> 072727ed2f605ac2a4ec67c3fbebbee5af411efb
}
