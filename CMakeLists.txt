cmake_minimum_required(VERSION 2.8.0)
project(mechO)

find_package(WiringPi REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(mechO ${SOURCES})

target_link_libraries(mechO ${WIRINGPI_LIBRARIES})
