#include "CommunicationBus.h"

class SpiCommunicationBus : public CommunicationBus
{
public:
    int read(int registerAddress) override;
};
