// no no no non on on onm on onmo nn n n
// a preliminary version
// not to be seen by teachers

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

bool previouslyTurned = false;

// if the correction is positive, the robot is too far to the right
// if the correction is negative, the robot is too far to the left
int correction = 0;

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

  // turn whenever possible
  if (leftDistance > 25)
  {
    return performLeftTurn();
  }

  // if (leftDistance > 10)
  // {
  //   return adjust(80, 1);
  // }

  // if (leftDistance < 4)
  // {
  //   return adjust(80, -1);
  // }

  if (leftDistance > 13 || leftDistance < 4)
  {
    return go(80, true);
  }

  go(80, false);
  return 0;

  querySensors();
  Serial.println("left distance: " + String(leftDistance));

  if (leftDistance > 25)
  {
    return performLeftTurn();
  }

  if (forwardDistance <= 12 && leftDistance <= 25)
  {
    return performRightTurn();
  }

  return go(100, false);
}

// query the sensors
void querySensors()
{
  forwardDistance = getForwardDistance();
  leftDistance = getLeftDistance();
}

//
//
//
//
//
//
// moving
//
void go(int timeToGo, bool needsAdjustement)
{
  if (!needsAdjustement)
  {
    analogWrite(RWF, 255);
    analogWrite(LWF, 240);

    waiter(timeToGo);

    analogWrite(RWF, 0);
    analogWrite(LWF, 0);
  }
  else
  {
    Serial.println("adjustement needed");
    // stop();
    // waiter(1000);

    if (leftDistance > 13)
    {
      Serial.println("left adjustement needed");
      analogWrite(RWF, 255);
      analogWrite(LWB, 185);

      waiter(150);

      analogWrite(RWF, 0);
      analogWrite(LWB, 0);

      Serial.println("performed a semi-turn, awaiting a second");
      // waiter(1000);

      Serial.println("started to go forward");
      analogWrite(RWF, 215);
      analogWrite(LWF, 255);

      waiter(300);

      analogWrite(RWF, 0);
      analogWrite(LWF, 0);

      Serial.println("stopped, awaiting a second");
      // waiter(1000);
    }
  }
  if (previouslyTurned)
  {
    previouslyTurned = false;
  }
}

// if side > 0, then the robot is too far to the right
// if side < 0, then the robot is too far to the left
void adjust(int timeToGo, int side)
{
  stop();
  if (side > 0)
  {
    Serial.println("perofming adjustement to the left as the left distance is: " + String(leftDistance));
    analogWrite(RWF, 255);
    // analogWrite(LWF, 185);

    waiter(100);
    stop();

    // analogWrite(RWF, 245);
    analogWrite(LWF, 245);

    waiter(100);
  }
  else
  {
    Serial.println("perofming adjustement to the right as the left distance is: " + String(leftDistance));
    // analogWrite(RWF, 205);
    analogWrite(LWF, 240);

    waiter(100);
    stop();

    analogWrite(RWF, 245);
    // analogWrite(LWF, 225);

    waiter(100);
  }

  stop();
}

void stop()
{
  analogWrite(RWF, 0);
  analogWrite(LWF, 0);

  analogWrite(RWB, 0);
  analogWrite(LWB, 0);
}

void goBackward(int time = 100)
{
  stop();

  analogWrite(RWB, 255);
  analogWrite(LWB, 246.5);

  waiter(time);

  stop();
}

void turnLeft()
{
  Serial.println("turning left with left distance: " + String(leftDistance) + ".....");
  stop();
  goBackward();

  analogWrite(RWF, 255);
  analogWrite(LWB, 232.5);

  waiter(425);
  stop();
}

void turnRight()
{
  stop();
  goBackward();

  analogWrite(RWB, 255);
  analogWrite(LWF, 232.5);

  waiter(400);
  stop();
}

// void adjustedRightTurn()
// {
//   stop();
//   goBackward();

//   Serial.print("trying to perform right turn with left distance: ");
//   Serial.print(leftDistance);
//   Serial.println(".....");

//   analogWrite(RWB, 175 + (leftDistance * 3));
//   analogWrite(LWF, 232.5 - (leftDistance * 5));

//   waiter(600 + (leftDistance * 12.5));

//   Serial.println("done!");

//   stop();
// }

void rightTurnHelper()
{
  stop();
  waiter(100);
  goBackward(600);
  stop();
  waiter(1000);

  analogWrite(RWF, 245);
  analogWrite(LWB, 165);
  waiter(300);

  stop();
  waiter(500);

  analogWrite(RWF, 185);
  analogWrite(LWF, 235);
  waiter(400);

  analogWrite(RWF, 235);
  analogWrite(LWF, 255);
  waiter(300);

  stop();

  // go(200);

  stop();
  return waiter(100);
}

void adjustedRightTurn()
{
  stop();
  // goBackward();

  if (leftDistance > 5.5 && !previouslyTurned)
  {
    return rightTurnHelper();
  }
  turnRight();

  previouslyTurned = true;
  Serial.println("done!");

  return stop();
}

void performLeftTurn()
{
  stop();
  go(400, false);
  stop();
  waiter(100);
  turnLeft();
  stop();
  waiter(100);
  go(500, false);
}

void performRightTurn()
{
  stop();
  Serial.println("Started performing right turn...");
  waiter(1000);

  adjustedRightTurn();
  waiter(1000);
}

//
//
//
//
//
//
// distance sensor
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
float getForwardDistance()
{
  return round(pulse(fProxTrig, fProxEcho) * 100.0) / 100.0;
}

float getLeftDistance()
{
  return round(pulse(lProxTrig, lProxEcho) * 100.0) / 100.0;
}

float pulse(int proxTrig, int proxEcho)
{
  digitalWrite(proxTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(proxTrig, LOW);

  float duration_us = pulseIn(proxEcho, HIGH);

  if (duration_us == 0)
  {
    return 1000.0;
  }

  return duration_us * .017;
}

//
//
//
//
//
//
//
// u know the waiters
void waiter(int timeToWait)
{
  long time = millis();
  // stop();
  while (millis() < time + timeToWait)
    ;
}
