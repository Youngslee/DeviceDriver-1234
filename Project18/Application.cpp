#include "Application.h"

#include <iostream>

void Application::ReadAndPrint(long startAddr, long endAddr)
{
	for (long i = startAddr; i <= endAddr; i++)
	{
		std::cout << dd->read(i) << '\n';
	}
}

void Application::WriteAll(int value)
{
	for (long i = 0x00; i <= 0x04; i++)
	{
		dd->write(i, value);
	}
}

