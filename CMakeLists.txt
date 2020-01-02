cmake_minimum_required(VERSION 3.15)
project(Whiteboard C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Whiteboard
    Message.c
    Message.h
        Client.c
        IPC_Server.c
    Topic.c
    Topic.h
    User.c
    User.h
    Whiteboard.c
    Whiteboard.h)
