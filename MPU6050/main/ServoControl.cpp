#include "ServoControl.h"

ServoControl::ServoControl(int pin, int lowerRange, int upperRange, int neutralAngle, int stepSize, int servoDelay)
    : lowerRange(lowerRange), upperRange(upperRange), neutralAngle(neutralAngle), stepSize(stepSize), servoDelay(servoDelay)
{
    currentAngle = neutralAngle;
    attach(pin);
    // moveToNeutral();
}

void ServoControl::attach(int pin)
{
    servo.attach(pin);
}

void ServoControl::moveToNeutral()
{
    setAngle(neutralAngle);
}

void ServoControl::increaseAngle()
{
    currentAngle += stepSize;
    setAngle(currentAngle);
}

void ServoControl::decreaseAngle()
{
    currentAngle -= stepSize;
    setAngle(currentAngle);
}

void ServoControl::setAngle(int angle)
{
    currentAngle = angle;
    servo.write(currentAngle);
    delay(servoDelay);
}

int ServoControl::getAngle()
{
    return currentAngle;
}

/**
 * @brief Adjusts the angle of the servo based on the sensor value within the specified range.
 *
 * This function checks if the sensor value is within the lower and upper range. If it's outside the range,
 * the function decreases or increases the angle of the servo accordingly. If the sensor value is within the range,
 * the function moves the servo to the neutral angle.
 *
 * @param sensorValue The current value of the sensor.
 *
 * @return void
 */
void ServoControl::adjustAngleBasedOnRange(int sensorValue)
{
    if (sensorValue < lowerRange || sensorValue > upperRange)
    {
        // Serial.println(xAcc  l);

        if (sensorValue < lowerRange)
        {
            decreaseAngle();
        }
        else if (sensorValue > upperRange)
        {
            increaseAngle();
        }
    }
    else
    {
        moveToNeutral();
    }
}
