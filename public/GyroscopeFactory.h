#pragma once

#include <memory>

#include "BrittleGyroscope.h"

class GyroscopeFactory
{
public:
    std::unique_ptr<BrittleGyroscope> create();
};
