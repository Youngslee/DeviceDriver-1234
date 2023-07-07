#pragma once
#include "DeviceDriver.h"
class Application
{
public:
	explicit Application(DeviceDriver* dd)
		: dd(dd){}
	void ReadAndPrint(long startAddr, long endAddr);
	void WriteAll(int value);

private:
	DeviceDriver *dd;
};