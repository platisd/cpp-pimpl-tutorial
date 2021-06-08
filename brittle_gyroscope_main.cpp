#include <iostream>

#include "GyroscopeFactory.h"

int main()
{
    GyroscopeFactory gyroscopeFactory;

    auto gyroscope = gyroscopeFactory.get();
    std::cout << gyroscope->getOrientation() << std::endl;

    return 0;
}
