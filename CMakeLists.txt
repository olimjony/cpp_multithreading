cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

add_executable (CMakeProject1 "main.cpp" )

set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)