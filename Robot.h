#ifndef __ROBOT_H
#define __ROBOT_H

#include <Arduino.h>
#include <Servo.h>
#include "Pins.h"

class Robot
{
  private:
    Servo front;
    Servo back;

    int frontDefaultAngle;
    int backDefaultAngle;
   
    int frontStepAngle;
    int backStepAngle;

    void StepForward(int speed);
    void StepBackward(int speed);

    bool danger;
    int lastDistance;
    
  public:

    Robot();
    ~Robot();
    void Start (int value1, int value2);
    void Stop ();
    void Walk(int speed);
    int Distance ();
    bool Danger();
};

#endif
