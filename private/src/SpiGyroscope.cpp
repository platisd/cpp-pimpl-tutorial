#include "SpiGyroscope.h"

SpiGyroscope::SpiGyroscope(CommunicationBus& communicationBus, int temperature)
    : mCommunicationBus{communicationBus}
    , mTemperature{temperature}
{
}

int SpiGyroscope::getAngularDisplacement()
{
    const auto registerValue       = mCommunicationBus.read(0xAA);
    const auto adjustedOrientation = registerValue + mTemperature * 10;

    return adjustedOrientation % 360;
}
