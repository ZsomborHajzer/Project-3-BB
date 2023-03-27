
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

<<<<<<< HEAD
=======
// boolean turnedRight = false;

unsigned int countRW = 0;
unsigned int countLW = 0;
>>>>>>> 9db7bcf (Fix: adjusted turns and timings)

void setup()
{

    Serial.begin(9600);
<<<<<<< HEAD
    pinMode(RWF,OUTPUT);
    pinMode(RWB,OUTPUT);
    pinMode(LWF,OUTPUT);
    pinMode(LWB,OUTPUT);
    
=======

>>>>>>> 9db7bcf (Fix: adjusted turns and timings)
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
<<<<<<< HEAD
    if (leftDistance > 9.2)
=======
    querySensors();
    // Serial.println("Left Distance: " + String(leftDistance) + "cm, Forward distance: " + String(forwardDistance) + "cm.");
    // return;

    if (leftDistance > 25)
    {
        // stop();
        // wait(150);
        return performLeftTurn();
    }

    if (leftDistance < 25 && forwardDistance < 12)
    {
        stop();
        return performRightTurn();
    }

    goForward();
}

// void loop()
// {
//     adjustedTurnRight();
//     return wait(1500);
// }

// movement functions

void goForward()
// the function defines the behaviour of the car when it is going forward
// it adjusts the car so that it is constantly 8.2 cm away from the wall
{
    if (leftDistance > 8.5)
>>>>>>> 9db7bcf (Fix: adjusted turns and timings)
    {
        analogWrite(RWF, 255);
        // analogWrite(LWF, 232 - 10 * (leftDistance - 7));
        analogWrite(LWF, 192);
    }
<<<<<<< HEAD
    else if (leftDistance < 7.2)
    {
        analogWrite(RWF, 205);
        // analogWrite(RWF, 255 - 10 * abs(leftDistance - 4));
        analogWrite(LWF, 232);
=======
    else if (leftDistance < 5.5)
    {
        analogWrite(RWF, 225);
        analogWrite(LWF, 255);
>>>>>>> 9db7bcf (Fix: adjusted turns and timings)
    }
    else
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232);
    }

    // turnedRight = false;
}


<<<<<<< HEAD
//===================================|| END OF MAZE GO STRAIGHT FUNCTION || =======================
=======
    while (countRW < ticks)
    {
        analogWrite(RWF, 255);
        analogWrite(LWF, 232);

        // Serial.println(String(countRW) + "/" + String(ticks));
        Serial.print("");
    }

    stop();

    // turnedRight = false;
}

void performLeftTurn()
{
    // goInTicks(15);
    goInTicks(20);
    wait(300);

    basicTurnLeft();
    wait(300);

    querySensors();
    if (forwardDistance > 20)
    {
        goInTicks(25);
    }

    // turnedRight = false;
}

void performRightTurn()
{
    wait(150);

    basicTurnRight();

    wait(100);

    querySensors();
    if (forwardDistance > 15)
    {
        wait(100);
        return goInTicks(25);
    }

    return wait(300);
}

void stop()
{
    analogWrite(RWF, 0);
    analogWrite(RWB, 0);
    analogWrite(LWF, 0);
    analogWrite(LWB, 0);
}

// void turnRightLeftWheel()
// {
//     // Serial.println("performing a right turn with only left wheel");

//     stop();
//     resetCounters();

//     while (countLW < 32)
//     {
//         // analogWrite(LWF, 185);
//         analogWrite(LWF, 255);

//         Serial.print("");
//     }

//     stop();
// }

// void turnRightRightWheel()
// {
//     // Serial.println("performing a right turn with only right wheel");

//     stop();
//     resetCounters();

//     while (countRW < 32)
//     {
//         // analogWrite(LWF, 185);
//         analogWrite(RWB, 255);

//         Serial.print("");
//     }

//     stop();
// }

// basic movement functions
// they are simple functions to turn precisely

void basicTurnLeft()
{
    stop();

    resetCounters();
    while (countLW < 14)
    {
        analogWrite(RWF, 255);
        analogWrite(LWB, 255);

        // Serial.println(String(countLW) + "/" + String(14));
        Serial.print("");
    }

    stop();
}

// void basicTurnLeft()
// {
//     stop();

//     resetCounters();
//     while (countRW < 32)
//     {
//         analogWrite(RWF, 255);
//         // analogWrite(LWB, 255);

//         // Serial.println(String(countLW) + "/" + String(14));
//         Serial.println("");
//     }

//     stop();
// }

void basicTurnRight()
{
    // Serial.println("performing a basic right turn");
    stop();

    resetCounters();
    while (countRW < 11)
    {
        analogWrite(LWF, 255);
        analogWrite(RWB, 255);

        Serial.print("");
    }

    stop();
}

// void adjustedTurnRight()
// {
//     stop();

//     resetCounters();

//     if (turnedRight == false)
//     {
//         while (countRW < 32)
//         {
//             // analogWrite(LWF, 185);
//             analogWrite(RWB, 255);

//             Serial.println("");
//         }

//         turnedRight = true;
//     }
//     else
//     {
//         while (countLW < 32)
//         {
//             // analogWrite(LWF, 185);
//             analogWrite(LWF, 255);

//             Serial.println("");
//         }
//     }

//     stop();
// }

// counter functions
// used to update the counters of the encoders
>>>>>>> 9db7bcf (Fix: adjusted turns and timings)

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

//===================================|| END OF ENCODER FUNCTIONS|| ================================

//===================================|| DISTANCE MEASUREMENT SENSORS|| ============================
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
//===================================|| END OF DISTANCE MEASUREMENTS || ===========================

void loop()
{
    querySensors();
    goForwardToWall();
}
