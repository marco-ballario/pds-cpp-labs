cmake_minimum_required(VERSION 3.19)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp Message.cpp Message.h DurationLogger.cpp DurationLogger.h MessageStore.cpp MessageStore.h)