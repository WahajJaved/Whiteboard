cmake_minimum_required(VERSION 3.15)
project(Whiteboard C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Whiteboard
        TCP_Client.c
        TCP_Server.c Whiteboard.c Whiteboard.h User.c User.h Topic.c Topic.h Message.c Message.h)
