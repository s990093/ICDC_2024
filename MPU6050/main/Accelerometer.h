#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H
#include <Arduino.h>

class Accelerometer
{
private:
    int address;

public:
    Accelerometer(int addr);
    void initialize();
    void readData(int &xAccl, int &yAccl, int &zAccl);
};

#endif
