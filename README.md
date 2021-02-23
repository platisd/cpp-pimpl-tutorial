# C++ pImpl idiom tutorial :movie_camera:

The Pointer to Implementation (`pImpl`) idiom in C++ is one technique that allows you to hide implementation
details from an interface.

Some practical benefits of `pImpl` are:
1. Optimize compilation time<br>
   Changes in the implementation do not require components that depend on the interface to be recompiled.
   This is very important when distributing precompiled libraries since your users' software will be
   **binary compatible** with your different deliveries regardless of the changes you do as long as the
   public interface is not modified.
2. Hide implementation completely when distributing a precompiled library.<br>
   If you want to share your library without giving access to the source code, you typically distribute
   one or more header files that include the various *declarations* used during **compilation** along with
   a (shared) library (e.g. a `.so` or `.dll` file). The precompiled library includes the definitions/implementations
   of the contents of the header file(s) and is utilized during **linking**.<br>
   `pImpl` allows you to not share dependencies and private member declarations which would have otherwise
   been necessary to be included in the header file.
3. Switch class implementations, transparently to the user of the class.<br>
   Determine which class to use during linking.

This tutorial can also be found on [YouTube](https://youtu.be/lETcZQuKQBs).

## Code to refactor

Let's assume a gyroscope that uses the `I2C` bus to transmit data and here's its C++ representation:

```cpp
// Gyroscope.h
#include "I2cCommunicationBus.h"

class Gyroscope
{
public:
    Gyroscope(int temperature);

    int getOrientation();

private:
    const int mTemperature;
    I2cCommunicationBus i2c;
};
```

```cpp
// Gyroscope.cpp
Gyroscope::Gyroscope(int temperature)
    : mTemperature{temperature}
{
}

int Gyroscope::getOrientation()
{
    const auto registerValue       = i2c.read(0xFF);
    const auto adjustedOrientation = registerValue + mTemperature / 2;

    return adjustedOrientation % 360;
}
```

We face the following issues:

1. Any changes to the `Gyroscope` class implementation (or its dependencies) will
   require recompilation of software that depends/uses the `Gyroscope` class.
2. Distributing the `Gyroscope` as a shared library will require you to not only distribute
   `Gyroscope.h` but also `I2cCommunicationBus.h` and so on.
3. If a Gyroscope variant is introduced and this should be transparent to the user, it may not be
   trivial to switch implementations during linking when details are leaked through the header file.
   For example, if the user's code needs to run on a different hardware platform where `SPI` is used
   instead of `I2C`, the dependency to I2C is still visible through its inclusion in `Gyroscope.h`.

## pImpl

### Gyroscope interface (public)

One way to solve the problems outlined above is by applying the `pImpl` idiom. The key concept is to
hide *all* implementation details and dependencies into `.cpp` files by **forward declaring** an
"implementation" class and maintain a pointer to it as a member variable.

```cpp
// Gyroscope.h
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
```

`Gyroscope.h` can be shared with our users and includes the bare minimum information they must know to
integrate our class into their code.<br>
As you can see we have forward-declared the `GyroscopeImpl` class, which is to be defined elsewhere, along with
a unique pointer to a `GyroscopeImpl` instance.

### I2C implementation (private)

```cpp
// I2cGyroscopeImpl.cpp
#include "Gyroscope.h"
#include "I2cCommunicationBus.h"

class Gyroscope::GyroscopeImpl
{
public:
    GyroscopeImpl(int temperature)
        : mTemperature{temperature}
    {
    }

    int getOrientation()
    {
        const auto registerValue       = i2c.read(0xFF);
        const auto adjustedOrientation = registerValue + mTemperature / 2;

        return adjustedOrientation % 360;
    }

private:
    const int mTemperature;
    I2cCommunicationBus i2c;
};
```

In the `I2cGyroscopeImpl.cpp` file, which will not be shared with our users and its contents will eventually
reside in a shared library, we have the *definition* of the `GyroscopeImpl` class that we forward-declared
in `Gyroscope.h`.<br>
Note that the dependency to `I2cCommunicationBus` is no longer exposed via the `Gyroscope.h` we share with
the users.

Then, we define the `Gyroscope` class that merely relays information to and from the `GyroscopeImpl`.

```cpp
Gyroscope::Gyroscope(int temperature)
    : mGyroscope{std::make_unique<GyroscopeImpl>(temperature)}
{
}

Gyroscope::~Gyroscope()
{
    // Defined this in the .cpp file(s) or you will get incomplete type errors
}

int Gyroscope::getOrientation()
{
    return mGyroscope->getOrientation();
}
```

Here you should be aware that the `Gyroscope` destructor cannot be default constructed or defined in the
`Gyroscope.h` header file, since at the time it is not known to the compiler how to destruct the member variable
(that is a `unique_ptr`). Keep in mind that in `Gyroscope.h`, we have only forward-declared the `GyroscopeImpl` class.
Nothing else is known about it and therefore the `Gyroscope` destructor does not know how to destruct it.

This is why we would have to *define* the `Gyroscope` destructor in our implementation file and **after** it is known
*how* to destruct the `GyroscopeImpl` class, i.e. after the `GyroscopeImpl` class' destructor has been (default)
constructed.

### SPI implementation (private & testable)

Declaring and defining a class entirely inside an implementation file does not mean you should throw design best
practices out of the window. For example, in `I2cGyroscopeImpl.cpp` our business logic is tightly coupled to the
`I2cCommunicationBus` class which is concrete.

We can still inject dependencies by breaking the actual implementation in separate files,
e.g. `SpiGyroscope.h` and `SpiGyroscope.cpp`.

```cpp
// SpiGyroscope.h
#include "CommunicationBus.h"

class SpiGyroscope
{
public:
    SpiGyroscope(CommunicationBus& communicationBus, int temperature);

    int getAngularDisplacement();

private:
    CommunicationBus& mCommunicationBus; // This is a pure abstract interface!
    const int mTemperature;
};
```

This allows the `GyroscopeImpl` class to be considered as the "integration scope" and `SpiGyroscope` to contain
the core business logic that should be unit tested.

```cpp
// SpiGyroscopeImpl.cpp
#include "Gyroscope.h"
#include "SpiCommunicationBus.h"
#include "SpiGyroscope.h"

class Gyroscope::GyroscopeImpl
{
public:
    GyroscopeImpl(int temperature)
        : mGyroscope{mSpi, temperature}
    {
    }

    int getOrientation()
    {
        return mGyroscope.getAngularDisplacement();
    }

private:
    SpiCommunicationBus mSpi;
    SpiGyroscope mGyroscope;
};
```
