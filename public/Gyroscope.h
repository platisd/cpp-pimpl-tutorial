#pragma once

#include <memory>

class Gyroscope
{
public:
    Gyroscope(int temperature);
    ~Gyroscope();

    int getOrientation();

private:
    class GyroscopeImpl; // Very secret or platform-specific
    std::unique_ptr<GyroscopeImpl> mGyroscope;
};
