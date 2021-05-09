#include <iostream>

#include "Gyroscope.h"

int main()
{
    Gyroscope g{42};
    std::cout << g.getOrientation() << std::endl;

    return 0;
}
