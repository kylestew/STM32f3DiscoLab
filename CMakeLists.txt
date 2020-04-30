cmake_minimum_required(VERSION 3.9)

project(stm32f3-disco CXX C)

# Set the C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

include_directories(libs)
add_subdirectory(libs)

if (HARDWARE MATCHES true)
    add_subdirectory(apps)
else()
    add_subdirectory(tests)
endif()
