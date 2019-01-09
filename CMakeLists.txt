cmake_minimum_required(VERSION 3.10.2)
project(mechO)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(mechO ${SOURCES})