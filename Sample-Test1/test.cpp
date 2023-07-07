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
TEST(DeviceDriverTest, ReadSuccessTest) {
	FlashMemoryDeviceMock flashMemoryDeviceMock;
	EXPECT_CALL(flashMemoryDeviceMock, read(0x2000))
		.Times(5)
		.WillRepeatedly(Return(1000));
	DeviceDriver dd(&flashMemoryDeviceMock);
	cout << dd.read(0x2000) << "\n";
}