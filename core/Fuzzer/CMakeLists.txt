
cmake_minimum_required(VERSION 3.16)
project(DDS_FUZZ LANGUAGES C CXX)

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

add_executable(security_mutator ${TARGET_DIR}/Fuzzer/src/security_mutator.cpp ${TARGET_DIR}/Fuzzer/lib/Fuzzer_SecurityUtility.cpp)
target_link_libraries(security_mutator)