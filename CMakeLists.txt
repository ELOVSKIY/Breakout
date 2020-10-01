cmake_minimum_required(VERSION 3.17)
project(Breakout)

set(CMAKE_CXX_STANDARD 20)

add_executable(Breakout WIN32 main.cpp  )
target_link_libraries(Breakout)