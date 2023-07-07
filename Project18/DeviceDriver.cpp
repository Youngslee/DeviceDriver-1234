#include "DeviceDriver.h"

#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int iteration = 4;
    int ret = (int)(m_hardware->read(address));
	while(iteration--)
	{
        if (ret != (int)(m_hardware->read(address))) throw std::exception("ReadFailException");
	}
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}