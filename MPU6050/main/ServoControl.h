#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <Servo.h>

class ServoControl
{
private:
    Servo servo;
    int currentAngle;
    int neutralAngle;
    int stepSize;
    int servoDelay;
    int lowerRange; // 下限范围
    int upperRange; // 上限范围

public:
    ServoControl(int pin, int lowerRange, int upperRange, int neutralAngle = 90, int stepSize = 5, int servoDelay = 3);
    /**
     * @brief Moves the servo to the neutral position.
     *
     * This function sets the current angle of the servo to the neutral angle.
     * The neutral angle is set during the initialization of the ServoControl object.
     *
     * @return void
     */
    void attach(int pin);
    void moveToNeutral();
    void increaseAngle();
    void decreaseAngle();
    void setAngle(int angle);
    int getAngle();
    void adjustAngleBasedOnRange(int sensorValue);
};

#endif
