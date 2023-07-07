#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project18/DeviceDriver.cpp"
#include "../Project18/Application.cpp"

using namespace testing;
using namespace std;
class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public testing::Test
{
public:
	FlashMemoryDeviceMock flashMemoryDeviceMock;

	void checkReadFailException() {
		try
		{
			DeviceDriver dd(&flashMemoryDeviceMock);
			dd.read(0x2000);
			FAIL();
		}
		catch (ReadFailException e)
		{

		}
	}
};
class ApplicationFixture : public testing::Test
{
public:
	FlashMemoryDeviceMock flashMemoryDeviceMock;
	long startAddr;
	long endAddr;
	void checkReadFailException() {
		try
		{
			DeviceDriver dd(&flashMemoryDeviceMock);
			Application app(&dd);
			app.ReadAndPrint(10, 12);
			FAIL();
		}
		catch (ReadFailException e)
		{

		}
	}
};
TEST_F(DeviceDriverFixture, ReadSuccessTest) {
	EXPECT_CALL(flashMemoryDeviceMock, read(0x2000))
		.Times(5)
		.WillRepeatedly(Return(1000));
	DeviceDriver dd(&flashMemoryDeviceMock);
	cout << dd.read(0x2000) << "\n";
}

TEST_F(DeviceDriverFixture, ReadFailTest) {

	EXPECT_CALL(flashMemoryDeviceMock, read(0x2000))
		.Times(3)
		.WillOnce(Return(1000))
		.WillOnce(Return(1000))
		.WillOnce(Return(1));
	checkReadFailException();
}

TEST_F(ApplicationFixture, ReadAndPrintPassTest) {
	startAddr = 10;
	endAddr = 12;
	for (int i = startAddr; i <= endAddr; i++)
	{
		EXPECT_CALL(flashMemoryDeviceMock, read(i))
			.Times(5)
			.WillRepeatedly(Return(1000));
	}
	DeviceDriver dd(&flashMemoryDeviceMock);
	Application app(&dd);
	app.ReadAndPrint(10, 12);
}
TEST_F(ApplicationFixture, ReadAndPrintFailTest) {
	EXPECT_CALL(flashMemoryDeviceMock, read(10))
		.Times(5)
		.WillRepeatedly(Return(0xF));

	EXPECT_CALL(flashMemoryDeviceMock, read(11))
		.Times(2)
		.WillOnce(Return(0xF))
		.WillOnce(Return(0x1));
	checkReadFailException();
}

TEST_F(ApplicationFixture, WriteAllPassTest) {
	startAddr = 0;
	endAddr = 4;
	for (int i = startAddr; i <= endAddr; i++)
	{
		EXPECT_CALL(flashMemoryDeviceMock, read(i))
			.WillRepeatedly(Return(0xFF));
		EXPECT_CALL(flashMemoryDeviceMock, write(i, 4));
	}
	DeviceDriver dd(&flashMemoryDeviceMock);
	Application app(&dd);
	app.WriteAll(4);
}

