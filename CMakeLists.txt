cmake_minimum_required(VERSION 3.0)

project("LUrlParser")

add_executable(Example Example.cpp LUrlParser.cpp LUrlParser.h)

set_property(TARGET Example PROPERTY CXX_STANDARD 11)
set_property(TARGET Example PROPERTY CXX_STANDARD_REQUIRED ON)
