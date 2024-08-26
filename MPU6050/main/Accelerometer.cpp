#include "Accelerometer.h"
#include <Wire.h>

Accelerometer::Accelerometer(int addr) : address(addr) {}

void Accelerometer::initialize()
{
    Wire.beginTransmission(address);
    Wire.write(0x20);
    Wire.write(0x27); // Enable X, Y, Z axes, power mode, 50Hz data rate
    Wire.endTransmission();

    Wire.beginTransmission(address);
    Wire.write(0x23);
    Wire.write(0x00); // Set range to ±100g, continuous update
    Wire.endTransmission();

    delay(20);
}

/// @brief 
/// @param xAccl 
/// @param yAccl 
/// @param zAccl 
void Accelerometer::readData(int &xAccl, int &yAccl, int &zAccl)
{
    unsigned int data[6];
    for (int i = 0; i < 6; i++)
    {
        Wire.beginTransmission(address);
        Wire.write(0x28 + i); // Data register
        Wire.endTransmission();

        Wire.requestFrom(address, 1);
        if (Wire.available() == 1)
        {
            data[i] = Wire.read();
        }
    }

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
