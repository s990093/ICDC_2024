#include <Wire.h>
#include <Servo.h>

// Constants

#define SERVO_MIN_ANGLE -90     // 最小角度（负值）
#define SERVO_MAX_ANGLE 0       // 最大角度
#define SERVO_NEUTRAL_ANGLE 90  // 中立角度（0度）
#define STEP_SIZE 5             // 每次调整的角度步长（1度）
#define SERVO_DELAY 3           // 每次调整的角度步长（1度）
#define ACCELEROMETER_ADDR 0x19 // Accelerometer I2C address

// =================================================================
// X
// =================================================================
#define DOWN_RANGE -16
#define UPPER_RANGE 130
#define X_SERVO_PIN 8

// =================================================================
// Y
// =================================================================
#define UPPER_RANGE_Y 48
#define DOWN_RANGE_Y -120
#define Y_SERVO_PIN 7
int currentAngle_Y = 0; // 初始角度设为90度

// c
int currentAngle = 0; // 初始角度设为90度

// Global variables
Servo servo1;

Servo y_servo;

// Function prototypes
void initializeAccelerometer();
void readAccelerometerData(int &xAccl, int &yAccl, int &zAccl);
// void adjustServoAngle();
void toHandle_X(int xAccl);
void toHandle_Y(int yAccl);

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  servo1.attach(X_SERVO_PIN); // Attach the servo to pin 9
  y_servo.attach(Y_SERVO_PIN);

  initializeAccelerometer();          // Configure the accelerometer
  servo1.write(SERVO_NEUTRAL_ANGLE);  // Set initial position to 90 degrees
  y_servo.write(SERVO_NEUTRAL_ANGLE); // Set initial position to 90 degrees

  delay(100);
}

void loop()
{
  int xAccl, yAccl, zAccl;
  readAccelerometerData(xAccl, yAccl, zAccl); // Read accelerometer data
  // Serial.println(xAccl);

  // Serial.println(yAccl);

  toHandle_X(xAccl);
  toHandle_Y(yAccl);

  // delay(500);
}

// Initialize accelerometer settings
void initializeAccelerometer()
{
  Wire.beginTransmission(ACCELEROMETER_ADDR);
  Wire.write(0x20);
  Wire.write(0x27); // Enable X, Y, Z axes, power mode, 50Hz data rate
  Wire.endTransmission();

  Wire.beginTransmission(ACCELEROMETER_ADDR);
  Wire.write(0x23);
  Wire.write(0x00); // Set range to ±100g, continuous update
  Wire.endTransmission();

  delay(20);
}

// Read accelerometer data
void readAccelerometerData(int &xAccl, int &yAccl, int &zAccl)
{
  unsigned int data[6];
  for (int i = 0; i < 6; i++)
  {
    Wire.beginTransmission(ACCELEROMETER_ADDR);
    Wire.write(0x28 + i); // Data register
    Wire.endTransmission();

    Wire.requestFrom(ACCELEROMETER_ADDR, 1);
    if (Wire.available() == 1)
    {
      data[i] = Wire.read();
    }
  }

  // Process data
  xAccl = ((data[1] << 8) | data[0]);
  yAccl = ((data[3] << 8) | data[2]);
  zAccl = ((data[5] << 8) | data[4]);

  if (xAccl > 0x7FFF)
    xAccl -= 0x10000;
  if (yAccl > 0x7FFF)
    yAccl -= 0x10000;
  if (zAccl > 0x7FFF)
    zAccl -= 0x10000;
}

void adjustServoAngle()
{
  servo1.write(SERVO_NEUTRAL_ANGLE + STEP_SIZE); // 将伺服电机的位置设置为 pos + 90，范围在 0 到 180 度之间
  delay(15);                                     // 等待伺服电机完成移动
}

void toHandle_Y(int yAccl)
{
  if (yAccl < DOWN_RANGE_Y || yAccl > UPPER_RANGE_Y)
  {

    if (yAccl < DOWN_RANGE_Y)
    {
      // Serial.println(" Down");
      currentAngle_Y = currentAngle_Y - STEP_SIZE;
      y_servo.write(currentAngle_Y);
      delay(SERVO_DELAY);
    }
    else if (yAccl > UPPER_RANGE_Y)
    {
      // Serial.println(currentAngle_Y);
      currentAngle_Y = currentAngle_Y + STEP_SIZE;
      y_servo.write(currentAngle_Y);
      delay(SERVO_DELAY);
    }
  }
  else
  {
    // Serial.println("Stop");

    currentAngle_Y = SERVO_NEUTRAL_ANGLE;
    y_servo.write(SERVO_NEUTRAL_ANGLE); // Set initial position to 90 degrees
    delay(SERVO_DELAY);
  }
}
void toHandle_X(int xAccl)
{
  // Serial.println(xAccl);
  if (xAccl < DOWN_RANGE || xAccl > UPPER_RANGE)
  {
    // Serial.println(xAcc  l);

    if (xAccl < DOWN_RANGE)
    {
      // Serial.println(" Down");
      currentAngle = currentAngle + STEP_SIZE;
      servo1.write(currentAngle);
      delay(SERVO_DELAY);
    }
    else if (xAccl > UPPER_RANGE)
    {
      // Serial.println(" UP");
      currentAngle = currentAngle - STEP_SIZE;

      servo1.write(currentAngle); // 将伺服电机的位置设置为 pos + 90，范围在 0 到 180 度之间
      delay(SERVO_DELAY);
    }
  }
  else
  {
    currentAngle = SERVO_NEUTRAL_ANGLE;
    servo1.write(SERVO_NEUTRAL_ANGLE); // Set initial position to 90 degrees
    delay(SERVO_DELAY);
  }
}
