#include "Robot.h"

Robot::Robot() { }
Robot::~Robot() { }

void Robot::Start(int value1, int value2)
{
	pinMode(LED, OUTPUT);
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	Serial.begin(9600);

	front.attach(FRONT_SERVO);
	back.attach(BACK_SERVO);

	frontDefaultAngle = value1;
	backDefaultAngle = value2;

	frontStepAngle = 7;
	backStepAngle = 20;

	front.write(frontDefaultAngle);
	back.write(backDefaultAngle);

	lastDistance = 0;
	danger = false;
}

void Robot::Stop()
{
	front.write(frontDefaultAngle);
	back.write(backDefaultAngle);
}

void Robot::Walk(int speed)
{
	if ((speed == 0) || (speed > 10) || (speed < -10))
		return;

	if (speed > 0)
		StepForward(speed);
	else
		StepBackward(speed * -1.0);
}

int Robot::Distance()
{
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);

	int distance = pulseIn(ECHO, HIGH, 10000) / 58.0;

	if (!distance)
		distance = 100;

	Serial.println(distance);
	return distance;
}

bool Robot::Danger()
{
	int distance = Distance();

	if ((distance < 10) && (lastDistance - distance > 15))
		danger = true;

	if (distance > 15)
		danger = false;

	lastDistance = distance;



	return danger;
}

void Robot::StepForward(int speed)
{
	int Delay = 20.0 / speed;

	for (int i = front.read(); i < frontDefaultAngle + frontStepAngle; i++)
	{
		front.write(i);
		delay(Delay);
	}

	for (int i = back.read(); i > backDefaultAngle - backStepAngle; i--)
	{
		back.write(i);
		delay(Delay * 2.0);
	}

	for (int i = front.read(); i > frontDefaultAngle - frontStepAngle; i--)
	{
		front.write(i);
		delay(Delay);
	}

	for (int i = back.read(); i < backDefaultAngle + backStepAngle; i++)
	{
		back.write(i);
		delay(Delay * 2.0);
	}
}

void Robot::StepBackward(int speed)
{
	int Delay = 20.0 / speed;

	for (int i = front.read(); i < frontDefaultAngle + frontStepAngle; i++)
	{
		front.write(i);
		delay(Delay);
	}

	for (int i = back.read(); i < backDefaultAngle + backStepAngle; i++)
	{
		back.write(i);
		delay(Delay * 2);
	}

	for (int i = front.read(); i > frontDefaultAngle - frontStepAngle; i--)
	{
		front.write(i);
		delay(Delay);
	}

	for (int i = back.read(); i > backDefaultAngle - backStepAngle; i--)
	{
		back.write(i);
		delay(Delay * 2);
	}
}
