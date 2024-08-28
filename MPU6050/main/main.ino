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
#define DebounceDelay 3000

unsigned long LastActionTime = 0; // 宣告並初始化 LastActionTime 變數

//
// obj
// ServoControl x_servo(X_SERVO_PIN, X_DOWN_RANGE, X_UPPER_RANGE);
// ServoControl y_servo(Y_SERVO_PIN, Y_DOWN_RANGE, Y_UPPER_RANGE);
Accelerometer accelerometer(ACCELEROMETER_ADDR);

Servo x_servo_right;
Servo x_servo_left;
Servo y_servo_right;
Servo y_servo_left;

// c
int y_currentAngle = 0;
int x_currentAngle = 0;

int x_currentAngle_left = x_currentAngle;
int x_currentAngle_right = x_currentAngle;

int y_currentAngle_left = y_currentAngle;
int y_currentAngle_right = y_currentAngle;

int lastYAccl = 0;
int lastXAccl = 0;

int yAcclBuffer[Y_MOVING_AVERAGE_WINDOW]; // 数据缓冲区
int xAcclBuffer[X_MOVING_AVERAGE_WINDOW]; // X 轴数据缓冲区

void setup()
{
  Wire.begin();
  Serial.begin(SERIAL_BAUD_RATE);

  accelerometer.initialize();

  // x_servo.moveToNeutral();
  // y_servo.moveToNeutral();

  x_servo_left.attach(X_SERVO_PIN_LEFT);   // Attach the servo to pin 9
  x_servo_right.attach(X_SERVO_PIN_RIGHT); // Attach the servo to pin 9
  y_servo_right.attach(Y_SERVO_PIN_RIGHT);
  y_servo_left.attach(Y_SERVO_PIN_LEFT);

  x_servo_left.write(SERVO_NEUTRAL_ANGLE);  // Set initial position to 90 degrees
  x_servo_right.write(SERVO_NEUTRAL_ANGLE); // Set initial position to 90 degrees

  y_servo_right.write(Y_SERVO_NEUTRAL_ANGLE_RIGHT); // Set initial position to 90 degrees
  y_servo_left.write(Y_SERVO_NEUTRAL_ANGLE_LEFT);   // Set initial position to 90 degrees

  pinMode(X_LED_PIN, OUTPUT); // 设置 X 轴 LED 引脚为输出
  pinMode(Y_LED_PIN, OUTPUT); // 设置 Y 轴 LED 引脚为输出

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

  toHandle_X(xAccl);
  toHandle_Y(yAccl);

  unsigned long currentMillis = millis();

  // 检查加速度是否在范围内，并且20秒内没有触发过
  if ((xAccl > 300) &&
      (currentMillis - LastActionTime >= DebounceDelay))
  {

    Serial.write("action: true\n");
    // digitalWrite(buzzerPin, HIGH);  // 蜂鸣器发声
    LastActionTime = currentMillis; // 更新最后触发时间
  }

  delay(10);
}

// =================================================================

void smoothMove(int targetAngle, Servo &servo)
{
  int step = (targetAngle > x_currentAngle) ? 1 : -1; // 根據目標角度設置增量或減量

  while (x_currentAngle != targetAngle)
  {
    x_currentAngle += step;
    servo.write(x_currentAngle); // 使用傳入的伺服對象來調整角度
    delay(15);                   // 每次移動之間的延遲
  }
}

// 计算并返回过滤后的 X 轴加速度值
int getFilteredXAccl(int xAccl)
{
  xAcclBuffer[xBufferIndex] = xAccl;                           // 将当前值放入 X 轴缓冲区
  xBufferIndex = (xBufferIndex + 1) % X_MOVING_AVERAGE_WINDOW; // 更新索引

  long sum = 0;
  for (int i = 0; i < X_MOVING_AVERAGE_WINDOW; i++)
  {
    sum += xAcclBuffer[i]; // 计算 X 轴缓冲区中所有值的总和
  }

  return sum / X_MOVING_AVERAGE_WINDOW; // 返回 X 轴的平均值
}

// 计算并返回过滤后的 Y 轴加速度值
int getFilteredYAccl(int yAccl)
{
  yAcclBuffer[yBufferIndex] = yAccl;                           // 将当前值放入 Y 轴缓冲区
  yBufferIndex = (yBufferIndex + 1) % Y_MOVING_AVERAGE_WINDOW; // 更新索引

  long sum = 0;
  for (int i = 0; i < Y_MOVING_AVERAGE_WINDOW; i++)
  {
    sum += yAcclBuffer[i]; // 计算 Y 轴缓冲区中所有值的总和
  }

  return sum / Y_MOVING_AVERAGE_WINDOW; // 返回 Y 轴的平均值
}

// =================================================================
//
// X
//
// =================================================================

void toHandle_Y(int yAccl)
{
  bool yMotion = false;

  if (abs(yAccl - lastYAccl) > Y_DEBOUNCE_THRESHOLD)
  {
    if (yAccl < Y_DOWN_RANGE || yAccl > Y_UPPER_RANGE)
    {

      yMotion = true;

      if (yAccl < Y_DOWN_RANGE)
      {
        y_currentAngle_left -= STEP_SIZE;
        y_currentAngle_right += STEP_SIZE;
      }
      else if (yAccl > Y_UPPER_RANGE)
      {
        y_currentAngle_left += STEP_SIZE;
        y_currentAngle_right -= STEP_SIZE;
      }

      y_servo_left.write(y_currentAngle_left);
      y_servo_right.write(y_currentAngle_right);

      delay(SERVO_DELAY);
    }
  }
  else
  {
    y_currentAngle_left = Y_SERVO_NEUTRAL_ANGLE_LEFT;
    y_currentAngle_right = Y_SERVO_NEUTRAL_ANGLE_RIGHT;

    y_servo_left.write(Y_SERVO_NEUTRAL_ANGLE_LEFT);
    y_servo_right.write(Y_SERVO_NEUTRAL_ANGLE_RIGHT);

    delay(SERVO_DELAY);
  }

  889(Y_LED_PIN, yMotion ? HIGH : LOW);
  lastYAccl = yAccl;
}

// =================================================================
//
// X
//
// =================================================================

void toHandle_X(int xAccl)
{
  bool xMotion = false;

  // Serial.println(abs(xAccl - lastXAccl));
  if (abs(xAccl - lastXAccl) > X_DEBOUNCE_THRESHOLD)
  {
    if (xAccl < X_DOWN_RANGE || xAccl > X_UPPER_RANGE)
    {

      xMotion = true;

      if (xAccl < X_DOWN_RANGE)
      {
        x_currentAngle_left -= STEP_SIZE;
        x_currentAngle_right += STEP_SIZE;
      }
      else if (xAccl > X_UPPER_RANGE)
      {
        x_currentAngle_left += STEP_SIZE;
        x_currentAngle_right -= STEP_SIZE;
      }

      x_servo_left.write(x_currentAngle_left);
      x_servo_right.write(x_currentAngle_right);

      delay(SERVO_DELAY);
    }
  }
  else
  {
    x_currentAngle_left = SERVO_NEUTRAL_ANGLE;
    x_currentAngle_right = SERVO_NEUTRAL_ANGLE;

    x_servo_left.write(SERVO_NEUTRAL_ANGLE);
    x_servo_right.write(SERVO_NEUTRAL_ANGLE);

    delay(SERVO_DELAY);
  }

  digitalWrite(X_LED_PIN, xMotion ? HIGH : LOW);
  lastXAccl = xAccl; // Update lastXAccl for the next call
}