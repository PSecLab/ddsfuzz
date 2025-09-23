
cmake_minimum_required(VERSION 3.16)
project(DDS_FUZZ LANGUAGES C CXX)


# Find requirements
if(NOT TARGET CycloneDDS::ddsc)
  find_package(CycloneDDS REQUIRED)
endif()

# Set C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(-std=c++11 -fpic)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(TARGET_DIR $ENV{HOME}/DDS-FUZZ/core)

idlc_generate(TARGET HelloWorldData_lib FILES "Eclipse_HelloWorldData.idl" WARNINGS no-implicit-extensibility)

file(GLOB FUZZER_CPP ${TARGET_DIR}/Fuzzer/lib/Fuzzer_*.cpp)
file(GLOB ECLIPSE_CPP ${TARGET_DIR}/cyclonedds/lib/Eclipse_*.cpp)
file(GLOB ECLIPSE_C ${TARGET_DIR}/cyclonedds/lib/Eclipse_*.c)

add_executable(CycloneddsFuzz ${TARGET_DIR}/cyclonedds/src/Eclipse.cpp ${ECLIPSE_CPP} ${ECLIPSE_C} ${FUZZER_CPP})

target_link_libraries(CycloneddsFuzz CycloneDDS::ddsc)

