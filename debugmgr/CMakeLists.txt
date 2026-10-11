cmake_minimum_required(VERSION 3.20)
project(debugmgr CXX)

include(JornadaCE)

jornada_add_executable(debugmgr main.cpp protocol.cpp server.cpp mailbox.cpp device_ce.cpp)
target_link_libraries(debugmgr PRIVATE jornada::winsock)
