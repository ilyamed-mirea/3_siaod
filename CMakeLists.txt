cmake_minimum_required(VERSION 3.22)
project(siaod)

set(CMAKE_CXX_STANDARD 20)

add_executable(siaod oop/main.cpp oop/Reader.h oop/Setter.h oop/Ident.h)
