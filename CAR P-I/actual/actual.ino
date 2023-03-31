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
bool goingForward = false;

unsigned long countRW = 0;
unsigned long countLW = 0;

// bool previouslyTurned = false;

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
    // goForwardEqualised();
    // printEncoderMesurements();

    querySensors();
    goForwardToWall();
}

void goForwardEqualised()
{
    if (countRW > countLW)
    {
        analogWrite(RWF, 255 - 10 * (countRW - countLW));
        analogWrite(LWF, 255);
    }
    else if (countLW > countRW)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 255 - 10 * (countLW - countRW));
    }
    else
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 255);
    }
}

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
    }
    else
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232);
    }
}

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
    Serial.print("Right Wheel: ");
    Serial.print(countRW);
    Serial.print(" , ");
    Serial.print("Left Wheel: ");
    Serial.println(countLW);
}

void resetCounters()
{
    countRW = 0;
    countLW = 0;
}

void querySensors()
{
    forwardDistance = getForwardDistance();
    leftDistance = getLeftDistance();
}

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
