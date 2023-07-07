#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project18/DeviceDriver.cpp"

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
	void checkWriteFailException() {
		try
		{
			DeviceDriver dd(&flashMemoryDeviceMock);
			dd.write(0x2000, 100);
			FAIL();
		}
		catch (WriteFailException e)
		{

		}
	}
};

TEST_F(DeviceDriverFixture, WriteSuccessTest) {
	EXPECT_CALL(flashMemoryDeviceMock, read(0x2000))
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flashMemoryDeviceMock, write(0x2000, 100));
	DeviceDriver dd(&flashMemoryDeviceMock);
	dd.write(0x2000, 100);
}

TEST_F(DeviceDriverFixture, WriteFailTest) {

	EXPECT_CALL(flashMemoryDeviceMock, read(0x2000))
		.WillRepeatedly(Return(0xAA));
	checkWriteFailException();
}