#include "Gyroscope.h"
#include "SpiCommunicationBus.h"
#include "SpiGyroscope.h"

class Gyroscope::GyroscopeImpl
{
public:
    GyroscopeImpl(int temperature)
        : mGyroscope{mSpi, temperature}
    {
    }

    int getOrientation()
    {
        return mGyroscope.getAngularDisplacement();
    }

private:
    SpiCommunicationBus mSpi;
    SpiGyroscope mGyroscope;
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
