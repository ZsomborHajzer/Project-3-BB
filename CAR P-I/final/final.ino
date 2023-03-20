// pins
//
// RWF - right wheel forward
// RWB - right wheel backward
//
// LWF / LWB - left wheel
//
// encoderRW / encoderLW - right / left wheel encoder
//
// fProxEcho / fProxTrig - front proximity sensor echo / trigger
// lProxEcho / lProxTrig - proximity sensor on the left side, echo / trigger

int RWF = 6;
int RWB = 5;

int LWF = 10;
int LWB = 9;

int encoderRW = 2;
int encoderLW = 3;

int fProxEcho = 11;
int fProxTrig = 12;

int lProxEcho = 7;
int lProxTrig = 8;

float forwardDistance = 0;
float leftDistance = 0;

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
    goForwardToWall();
}

// movement functions

void goForwardToWall()
// the function defines the behaviour of the car when it is going forward
// it adjusts the car so that it is constantly 8.2 cm away from the wall
{
    if (leftDistance > 9.2)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 192);
    }
    else if (leftDistance < 7.2)
    {
        // TODO: should be reviewed as the left wheel is not using max speed
        analogWrite(RWF, 205);
        analogWrite(LWF, 232);
    }
    else
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232);
    }
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

void printEncoderMesurements()
// TODO: be removed on release
{
    Serial.println("Left wheel: " + String(countLW) + ", right wheel:" + String(countRW));
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
