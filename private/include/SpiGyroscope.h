#pragma once

#include "CommunicationBus.h"

class SpiGyroscope
{
public:
    SpiGyroscope(CommunicationBus& communicationBus, int temperature);

    int getAngularDisplacement();

private:
    CommunicationBus& mCommunicationBus;
    const int mTemperature;
};
