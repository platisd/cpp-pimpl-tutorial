#include "GyroscopeFactory.h"
#include "I2cBrittleGyroscope.h"

std::unique_ptr<BrittleGyroscope> GyroscopeFactory::get()
{
    return std::make_unique<I2cBrittleGyroscope>();
}
