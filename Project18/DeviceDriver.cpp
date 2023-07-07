#include "DeviceDriver.h"

#include <exception>

class WriteFailException : public std::exception {
public:
    const char* what() const throw()
    {
        return "WriteFailException";
    }
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    int ret = read(address);
    if (ret != 0xFF) throw* (new WriteFailException);
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
