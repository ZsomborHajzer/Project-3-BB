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

float forwardDistance = 0;
float leftDistance = 0;

// might be used in future, WIP
// bool goingForward = false;

unsigned long countRW = 0;
unsigned long countLW = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(RWF, OUTPUT);
    pinMode(RWB, OUTPUT);
    pinMode(LWF, OUTPUT);
    pinMode(LWB, OUTPUT);

    pinMode(fProxEcho, INPUT);
    pinMode(fProxTrig, OUTPUT);

    pinMode(lProxEcho, INPUT);
    pinMode(lProxTrig, OUTPUT);

    pinMode(encoderRW, INPUT);
    pinMode(encoderLW, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderRW), updateRW, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderLW), updateLW, CHANGE);
}

//===================================|| MAZE GO STRAIGHT FUNCTION || =======================
void goForwardToWall()
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

//===================================|| END OF MAZE GO STRAIGHT FUNCTION || =======================

//===================================|| ENCODER FUNCTIONS || ======================================
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
    Serial.println("Left wheel: " + String(countLW) + ", right wheel:" + String(countRW));
}

void resetCounters()
{
    countRW = 0;
    countLW = 0;
}

//===================================|| END OF ENCODER FUNCTIONS|| ================================

//===================================|| DISTANCE MEASUREMENT SENSORS|| ============================
void querySensors()
{
    // TODO: might be optimised as the sensors always get queried together
    forwardDistance = getForwardDistance();
    leftDistance = getLeftDistance();
}

// might be renamed as it returns the distance in cm
// also might be optimised as the sensors always get queried together
float pulse(int proxTrig, int proxEcho)
{
    digitalWrite(proxTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(proxTrig, LOW);

    float duration_us = pulseIn(proxEcho, HIGH);

    return duration_us * .017;
}

float getForwardDistance()
{
    return round(pulse(fProxTrig, fProxEcho) * 100.0) / 100.0;
}

float getLeftDistance()
{
    return round(pulse(lProxTrig, lProxEcho) * 100.0) / 100.0;
}
//===================================|| END OF DISTANCE MEASUREMENTS || ===========================

void loop()
{
    querySensors();
    goForwardToWall();
}
