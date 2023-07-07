#include "DeviceDriver.h"

#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::readData(long address)
{
	return (int)(m_hardware->read(address));
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int iteration = ITERATION_READ;
    int ret = readData(address);
    iteration--;
	while(iteration--)
	{
        if (ret != readData(address)) throw std::exception("ReadFailException");
	}
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}