#pragma once

class CommunicationBus
{
public:
    virtual ~CommunicationBus() = default;

    virtual int read(int registerAddress) = 0;
};
