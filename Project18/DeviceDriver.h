#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    int readData(long address);
    FlashMemoryDevice* m_hardware;
    const int ITERATION_READ = 5;
};