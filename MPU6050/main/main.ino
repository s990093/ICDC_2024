#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
// self-written libraries
// #include "ServoControl.h"
#include "Accelerometer.h"
#include "config.h"
//
#define TimeRange 20
#define BuzzerPin 9;
#define DebounceDelay 3000;

unsigned long LastActionTime = 0;

//
// obj
// ServoControl x_servo(X_SERVO_PIN, X_DOWN_RANGE, X_UPPER_RANGE);
// ServoControl y_servo(Y_SERVO_PIN, Y_DOWN_RANGE, Y_UPPER_RANGE);
Accelerometer accelerometer(ACCELEROMETER_ADDR);
Servo x_servo;
Servo y_servo;

// c
int y_currentAngle = 0;
int x_currentAngle = 0;

void setup()
{
  Wire.begin();
  Serial.begin(SERIAL_BAUD_RATE);

  accelerometer.initialize();

  // x_servo.moveToNeutral();
  // y_servo.moveToNeutral();

  x_servo.attach(X_SERVO_PIN); // Attach the servo to pin 9
  y_servo.attach(Y_SERVO_PIN);

  x_servo.write(SERVO_NEUTRAL_ANGLE); // Set initial position to 90 degrees
  y_servo.write(SERVO_NEUTRAL_ANGLE); // Set initial position to 90 degrees

  pinMode(buzzerPin, OUTPUT);

  // d
  delay(100);
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
  // Serial.println(xAccl);

  // Adjust X-axis and Y-axis servo angles based on accelerometer data
  // x_servo.adjustAngleBasedOnRange(xAccl);
  // y_servo.adjustAngleBasedOnRange(yAccl);

  // toHandle_X(xAccl);
  // toHandle_Y(yAccl);

  unsigned long currentMillis = millis();

  // 检查加速度是否在范围内，并且20秒内没有触发过
  if ((xAccl > 300) &&
      (currentMillis - lastActionTime >= DebounceDelay))
  {

    Serial.write("action: true\n");
    // digitalWrite(buzzerPin, HIGH);  // 蜂鸣器发声
    lastActionTime = currentMillis; // 更新最后触发时间
  }

  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    // Process data
    Serial.println(data); // Just an example of processing
  }

  delay(10);
}

void toHandle_Y(int yAccl)
{
  if (yAccl < Y_DOWN_RANGE || yAccl > Y_UPPER_RANGE)
  {

    if (yAccl < Y_DOWN_RANGE)
    {
      // Serial.println(" Down");
      y_currentAngle = y_currentAngle - STEP_SIZE;
      y_servo.write(y_currentAngle);
      delay(SERVO_DELAY);
    }
    else if (yAccl > Y_UPPER_RANGE)
    {
      // Serial.println(currentAngle_Y);
      y_currentAngle = y_currentAngle + STEP_SIZE;
      y_servo.write(y_currentAngle);
      delay(SERVO_DELAY);
    }
  }
  else
  {
    // Serial.println("Stop");

    y_currentAngle = SERVO_NEUTRAL_ANGLE;
    y_servo.write(SERVO_NEUTRAL_ANGLE); // Set initial position to 90 degrees
    delay(SERVO_DELAY);
  }
}
void toHandle_X(int xAccl)
{
  // Serial.println(xAccl);
  if (xAccl < X_DOWN_RANGE || xAccl > X_UPPER_RANGE)
  {
    // Serial.println(xAcc  l);

    if (xAccl < X_DOWN_RANGE)
    {
      // Serial.println(" Down");
      x_currentAngle = x_currentAngle + STEP_SIZE;
      x_servo.write(x_currentAngle);
      delay(SERVO_DELAY);
    }
    else if (xAccl > X_UPPER_RANGE)
    {
      // Serial.println(" UP");
      x_currentAngle = x_currentAngle - STEP_SIZE;

      x_servo.write(x_currentAngle); // 将伺服电机的位置设置为 pos + 90，范围在 0 到 180 度之间
      delay(SERVO_DELAY);
    }
  }
  else
  {
    x_currentAngle = SERVO_NEUTRAL_ANGLE;
    x_servo.write(SERVO_NEUTRAL_ANGLE); // Set initial position to 90 degrees
    delay(SERVO_DELAY);
  }
}
