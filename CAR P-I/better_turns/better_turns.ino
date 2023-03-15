#define RWF 6
#define RWB 5
#define LWB 9
#define LWF 10

#define fProxEcho 11
#define fProxTrig 12

#define lProxEcho 3
#define lProxTrig 4

float forwardDistance = 0;
float leftDistance = 0;
bool goingForward = false;

// bool previouslyTurned = false;

void setup()
{
    Serial.begin(9600);
    pinMode(fProxEcho, INPUT);
    pinMode(fProxTrig, OUTPUT);

    pinMode(lProxEcho, INPUT);
    pinMode(lProxTrig, OUTPUT);
}

void loop()
{
    querySensors();
    Serial.println("Forward distance: " + String(forwardDistance));
    Serial.println("Left distance: " + String(leftDistance));

    if (leftDistance > 25)
    {
        return turnLeft();
    }

    return goForward(100);
}

void querySensors()
{
    forwardDistance = getForwardDistance();
    leftDistance = getLeftDistance();

    // digitalWrite(fProxTrig, HIGH);
    // digitalWrite(lProxTrig, HIGH);
    // delayMicroseconds(10);
    // digitalWrite(fProxTrig, LOW);
    // digitalWrite(lProxTrig, LOW);

    // float fDuration = pulseIn(fProxEcho, HIGH) * .017;
    // float lDuration = pulseIn(lProxEcho, HIGH) * .017;

    // forwardDistance = round(fDuration * 100.0) / 100.0;
    // leftDistance = round(lDuration * 100.0) / 100.0;
}

void turnLeft()
{
    goForward(300);
    stop();
    waiter(500);
    basicTurnLeft();
    stop();
    waiter(100);
    goForward(400);
}

// basic turns are turns on the spot, they do not change robot's position
void basicTurnLeft()
{
    analogWrite(RWF, 255);
    analogWrite(LWB, 232);

    waiter(465);
    analogWrite(RWF, 0);
    analogWrite(LWB, 0);
}

void basicTurnRight()
{
    analogWrite(RWB, 255);
    analogWrite(LWF, 232);

    waiter(410);

    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
}

// stop function is better to avoid, but when no info is given - it is better to use it
void stop()
{
    analogWrite(RWF, 0);
    analogWrite(LWF, 0);

    analogWrite(RWB, 0);
    analogWrite(LWB, 0);

    goingForward = false;
}

// go forward for a certain amount of time
void goForward(int timeToGo)
{
    Serial.println("going forward for " + String(timeToGo));
    if (!goingForward)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232.5);

        goingForward = true;
    }

    waiter(timeToGo);

    // analogWrite(RWF, 0);
    // analogWrite(LWF, 0);
    // if (previouslyTurned)
    // {
    //     previouslyTurned = false;
    // }
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

void waiter(int timeToWait)
{
    long time = millis();

    while (millis() < time + timeToWait)
        ;
}
