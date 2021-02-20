#include <iostream>

#include "I2cCommunicationBus.h"

int I2cCommunicationBus::read(int registerAddress)
{
    std::cout << "Reading from I2C address: " << registerAddress << std::endl;

    return 10;
}
