#pragma once

class BrittleGyroscope
{
public:
    virtual ~BrittleGyroscope() = default;

    virtual int getOrientation() = 0;
};
