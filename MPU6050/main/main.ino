#include <Wire.h>
// self-written libraries
#include "ServoControl.h"
#include "Accelerometer.h"
#include "config.h"

ServoControl x_servo(X_SERVO_PIN, X_DOWN_RANGE, X_UPPER_RANGE);
ServoControl y_servo(Y_SERVO_PIN, Y_DOWN_RANGE, Y_UPPER_RANGE);
Accelerometer accelerometer(ACCELEROMETER_ADDR);

void setup()
{
  Wire.begin();
  Serial.begin(SERIAL_BAUD_RATE);

  accelerometer.initialize();

  x_servo.moveToNeutral();
  y_servo.moveToNeutral();
}

/**
 * @brief Main loop function that continuously reads accelerometer data and adjusts the angles of the X and Y servos.
 *
 * This function reads the accelerometer data in the X, Y, and Z axes. It then adjusts the angles of the X and Y servos
 * based on the accelerometer data using the adjustAngleBasedOnRange method of the ServoControl class.
 *
 * @return This function does not return any value.
 */
void loop()
{
  int xAccl, yAccl, zAccl;
  accelerometer.readData(xAccl, yAccl, zAccl);

  // Adjust X-axis and Y-axis servo angles based on accelerometer data
  x_servo.adjustAngleBasedOnRange(xAccl);
  y_servo.adjustAngleBasedOnRange(yAccl);
}
