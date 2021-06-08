#pragma once

#include "BrittleGyroscope.h"

class I2cBrittleGyroscope : public BrittleGyroscope
{
public:
    int getOrientation() override;

private:
    // Some dependencies we don't want to share
};
