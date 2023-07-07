#include "DeviceDriver.h"
#include <exception>
#include <iostream>

class WriteFailException : public std::exception {
public:
    const char* what() const throw()
    {
        return "WriteFailException";
    }
};
class ReadFailException : public std::exception {
public:
    const char* what() const throw()
    {
        return "ReadFailException";
    }
};

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
        if (ret != readData(address)) throw *(new ReadFailException);
	}
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    int ret = read(address);
    if (ret != 0xFF) throw* (new WriteFailException);
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
