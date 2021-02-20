#include <iostream>

#include "SpiCommunicationBus.h"

int SpiCommunicationBus::read(int registerAddress)
{
    std::cout << "Reading from SPI address: " << registerAddress << std::endl;

    return 20;
}
