add_library(i2c_gyroscope_implementation SHARED
    src/I2cGyroscopeImpl.cpp
    src/I2cCommunicationBus.cpp)
target_include_directories(i2c_gyroscope_implementation PRIVATE include)
target_link_libraries(i2c_gyroscope_implementation
    PUBLIC
    gyroscope_interface)

add_library(spi_gyroscope src/SpiGyroscope.cpp)
target_include_directories(spi_gyroscope PUBLIC include)

add_library(spi_gyroscope_implementation SHARED
    src/SpiGyroscopeImpl.cpp
    src/SpiCommunicationBus.cpp)
target_include_directories(spi_gyroscope_implementation PRIVATE include)
target_link_libraries(spi_gyroscope_implementation
    PRIVATE
    spi_gyroscope
    PUBLIC
    gyroscope_interface)
