cmake_minimum_required(VERSION 3.13)
project(pImplTutorial)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(
    -Wcast-align
    -Wpedantic
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wnon-virtual-dtor
    -Wmissing-include-dirs
    -Wdisabled-optimization
    -Winit-self
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wparentheses
    -Wredundant-decls
    -Wshadow
    -Wsign-promo
    -Wstrict-aliasing
    -Wall
    -Wextra
    -Werror
)

add_subdirectory(external)
enable_testing()
add_subdirectory(public)
add_subdirectory(private)

add_executable(i2c_gyroscope_main gyroscope_main.cpp)
target_link_libraries(i2c_gyroscope_main
    PRIVATE
    i2c_gyroscope_implementation)

add_executable(spi_gyroscope_main gyroscope_main.cpp)
target_link_libraries(spi_gyroscope_main
    PRIVATE
    spi_gyroscope_implementation)

add_executable(brittle_gyroscope_main brittle_gyroscope_main.cpp)
target_link_libraries(brittle_gyroscope_main
    PRIVATE
    brittle_gyroscope)

add_subdirectory(test)
