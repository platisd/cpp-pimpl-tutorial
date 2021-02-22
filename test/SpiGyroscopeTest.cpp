#include <gtest/gtest.h>

#include "MockCommunicationBus.h"
#include "SpiGyroscope.h"

using ::testing::_;
using ::testing::Return;

struct SpiGyroscopeTest : public ::testing::Test
{
    const int kDummyTemperature = 1;
    MockCommunicationBus mCommunicationBus;
    SpiGyroscope mGyroscope{mCommunicationBus, kDummyTemperature};
};

TEST_F(SpiGyroscopeTest,
       getAngularDisplacement_WhenCalled_WillReadFromCorrectAddress)
{
    const auto expectedAddress = 0xAA;
    EXPECT_CALL(mCommunicationBus, read(expectedAddress));

    mGyroscope.getAngularDisplacement();
}

TEST_F(SpiGyroscopeTest,
       getAngularDisplacement_WhenCalled_WillReturnNormalizedAddress)
{
    const auto temperatureToReturn = 10;
    EXPECT_CALL(mCommunicationBus, read(_))
        .WillOnce(Return(temperatureToReturn));

    const auto expectedTemperature
        = temperatureToReturn + kDummyTemperature * 10;
    EXPECT_EQ(mGyroscope.getAngularDisplacement(), expectedTemperature);
}
