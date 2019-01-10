cmake_minimum_required(VERSION 2.8.0)
project(mechO)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(mechO ${SOURCES})