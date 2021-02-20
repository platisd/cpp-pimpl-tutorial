#include "Gyroscope.h"
#include "I2cCommunicationBus.h"

class Gyroscope::GyroscopeImpl
{
public:
    GyroscopeImpl(int temperature)
        : mTemperature{temperature}
    {
    }

    int getOrientation()
    {
        const auto registerValue       = i2c.read(0xFF);
        const auto adjustedOrientation = registerValue + mTemperature / 2;

        return adjustedOrientation % 360;
    }

private:
    const int mTemperature;
    I2cCommunicationBus i2c;
};

Gyroscope::Gyroscope(int temperature)
    : mGyroscope{std::make_unique<GyroscopeImpl>(temperature)}
{
}

Gyroscope::~Gyroscope()
{
    // Defined this in the .cpp file(s) or you will get incomplete type errors
}

int Gyroscope::getOrientation()
{
    return mGyroscope->getOrientation();
}
