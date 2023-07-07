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
		.Times(2)
	.WillOnce(Return(1000))
	.WillOnce(Return(1))
	.WillRepeatedly(Return(1000));
	DeviceDriver dd(&flashMemoryDeviceMock);
	EXPECT_THROW(dd.read(0x2000), exception);
}