cmake_minimum_required(VERSION 3.27)
project(student C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(student
        manage.c
        pass.c
        Student.c
        studentsystem.c
        studentsystem.h
        Teacher.c)
