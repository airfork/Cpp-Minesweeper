cmake_minimum_required(VERSION 3.21)
project(HW5)

set(CMAKE_CXX_STANDARD 14)

add_executable(HW5 main.cpp Point.cpp Point.h MineField.cpp MineField.h GameManager.cpp GameManager.h Position.h Position.cpp Helpers.cpp Helpers.h)
