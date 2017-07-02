cmake_minimum_required(VERSION 3.7)
project(testAsyncTimer)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -pthread")
set(SOURCE_FILES main.cpp asynctimerqueue.h)
add_executable(testAsyncTimer ${SOURCE_FILES})