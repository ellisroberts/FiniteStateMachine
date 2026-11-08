cmake_minimum_required(VERSION 3.12)
project(StateMachineProject VERSION 1.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find CppUnit package dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(CPPUNIT REQUIRED cppunit)

set(SOURCES
    src/Init.cpp
    src/Exponent.cpp
    src/Invalid.cpp

)

# Test Binary Target
add_executable(StateMachineTests src/TestRunner.cpp ${SOURCES})
target_include_directories(StateMachineTests PRIVATE src ${CPPUNIT_INCLUDE_DIRS})
target_link_libraries(StateMachineTests PRIVATE ${CPPUNIT_LIBRARIES})
