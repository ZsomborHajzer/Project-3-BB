/*
    pins definition

    RWF - right wheel forward
    RWB - right wheel backward

    LWF / LWB - left wheel

    encoderRW / encoderLW - right / left wheel encoder

    fProxEcho / fProxTrig - front proximity sensor echo / trigger
    lProxEcho / lProxTrig - proximity sensor on the left side, echo / trigger
*/

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

float forwardDistance = .0f;
float leftDistance = .0f;

boolean turnedRight = false;

volatile int countRW = 0;
volatile int countLW = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(fProxEcho, INPUT);
    pinMode(fProxTrig, OUTPUT);

    pinMode(lProxEcho, INPUT);
    pinMode(lProxTrig, OUTPUT);

    pinMode(encoderRW, INPUT);
    pinMode(encoderLW, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderRW), updateRW, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderLW), updateLW, CHANGE);
}

void loop()
{
    querySensors();

    if (leftDistance > 25)
    {
        return performLeftTurn();
    }

    if (leftDistance < 25 && forwardDistance < 12)
    {
        return performRightTurn();
    }

    goForward();
}

// movement functions

void goForward()
// the function defines the behaviour of the car when it is going forward
// it adjusts the car so that it is constantly 8.2 cm away from the wall
{
    if (leftDistance > 9.2)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 180);
    }
    else if (leftDistance < 7.2)
    {
        analogWrite(RWF, 225);
        analogWrite(LWF, 255);
    }
    else
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232);
    }

    turnedRight = false;
}

void goForwardInTicks(int ticks)
// moves the car forward for a given number of ticks
{
    resetCounters();

    while (countRW < ticks)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232);
    }

    turnedRight = false;

    stop();
}

void goBackwardInTicks(int ticks)
{
    resetCounters();

    while (countRW < ticks)
    {
        analogWrite(RWB, 255);
        analogWrite(LWB, 242);
    }

    turnedRight = false;

    stop();
}

void performLeftTurn()
{
    goForwardInTicks(20);
    wait(300);

    basicTurnLeft();

    wait(150);

    querySensors();
    if (forwardDistance > 25)
    {
        goForwardInTicks(20);
    }

    turnedRight = false;

    return wait(150);
}

void performRightTurn()
{
    stop();

    wait(150);

    if (leftDistance < 6 || turnedRight)
    {
        basicTurnRight();
        turnedRight = true;
    }
    else
    {
        adjustToWall();
    }

    wait(150);

    querySensors();
    if (forwardDistance > 15)
    {
        wait(100);
        goForwardInTicks(25);
    }

    return wait(150);
}

// while performing a right turn, the car might need
// to be adjusted to the wall
void adjustToWall()
{
    stop();
    resetCounters();

    while (countRW < 10)
    {
        analogWrite(RWB, 255);
    }

    stop();
    resetCounters();

    while (countRW < 12)
    {
        analogWrite(RWB, 235);
        analogWrite(LWB, 255);
    }

    stop();
    resetCounters();

    while (countRW < 12)
    {
        analogWrite(RWF, 255);
    }

    stop();
    resetCounters();

    while (countRW < 8)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 255);
    }

    stop();
    resetCounters();
}

// basic movement functions
// those are that actually do the movement
// as an example, basicTurnLeft() turns the car left by 90 degrees

void stop()
{
    analogWrite(RWF, 0);
    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
    analogWrite(LWB, 0);
}

void basicTurnLeft()
{
    stop();

    resetCounters();
    while (countRW < 16)
    {
        analogWrite(RWF, 255);
        analogWrite(LWB, 255);
    }

    stop();
}

void basicTurnRight()
{
    stop();

    resetCounters();
    while (countLW < 17)
    {
        analogWrite(LWF, 255);
        analogWrite(RWB, 255);
    }

    stop();
}

// counter functions
// used to update the counters of the encoders

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

void resetCounters()
{
    countRW = 0;
    countLW = 0;
}

// sound sensors functions

void querySensors()
// TODO: might be optimised as the sensors always get queried together
{
    forwardDistance = getForwardDistance();
    leftDistance = getLeftDistance();
}

float pulse(int proxTrig, int proxEcho)
// might be renamed as it returns the distance in cm
// TODO: also might be optimised as the sensors always get queried together
{
    digitalWrite(proxTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(proxTrig, LOW);

    float duration_us = pulseIn(proxEcho, HIGH);

    return duration_us * .017;
}

float getForwardDistance()
// returns forward distance in cm
{
    return round(pulse(fProxTrig, fProxEcho) * 100.0) / 100.0;
}

float getLeftDistance()
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
}
