#pragma once

#include <gmock/gmock.h>

#include "CommunicationBus.h"

class MockCommunicationBus : public CommunicationBus
{
public:
    MOCK_METHOD(int, read, (int registerAddress), (override));
};
