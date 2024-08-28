#include <Arduino.h>

class SensorFilter
{
private:
    float alpha;          // 低通滤波系数
    int filterWindowSize; // 中值滤波窗口大小
    int *buffer;          // 存储窗口数据
    int bufferIndex;      // 窗口当前索引
    int prevValue;        // 上一次低通滤波的值

public:
    // 构造函数
    SensorFilter(float alpha, int filterWindowSize)
        : alpha(alpha), filterWindowSize(filterWindowSize), bufferIndex(0), prevValue(0)
    {
        buffer = new int[filterWindowSize](); // 初始化缓冲区
    }

    // 析构函数
    ~SensorFilter()
    {
        delete[] buffer;
    }

    // 中值滤波函数
    int medianFilter(int newValue)
    {
        buffer[bufferIndex] = newValue;
        bufferIndex = (bufferIndex + 1) % filterWindowSize;

        int *sortedBuffer = new int[filterWindowSize];
        memcpy(sortedBuffer, buffer, sizeof(int) * filterWindowSize);
        sort(sortedBuffer, sortedBuffer + filterWindowSize);

        int medianValue = sortedBuffer[filterWindowSize / 2];
        delete[] sortedBuffer;
        return medianValue;
    }

    // 低通滤波函数
    int lowPassFilter(int currentValue)
    {
        int filteredValue = alpha * currentValue + (1 - alpha) * prevValue;
        prevValue = filteredValue;
        return filteredValue;
    }

    // 综合滤波函数
    int applyFilters(int value)
    {
        int medianFiltered = medianFilter(value); // 先应用中值滤波
        return lowPassFilter(medianFiltered);     // 再应用低通滤波
    }
};
