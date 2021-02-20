#include "CommunicationBus.h"

class I2cCommunicationBus : public CommunicationBus
{
public:
    int read(int registerAddress) override;
};
