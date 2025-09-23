
cmake_minimum_required(VERSION 3.16)
project(DDS_FUZZ LANGUAGES C CXX)


if(NOT fastcdr_FOUND)
    find_package(fastcdr REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
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

file(GLOB FUZZER_CPP ${TARGET_DIR}/Fuzzer/lib/Fuzzer_*.cpp)
file(GLOB FAST_DDS_CPP ${TARGET_DIR}/Fastdds/lib/Fast-dds_*.cpp)
file(GLOB FAST_DDS_CXX ${TARGET_DIR}/Fastdds/lib/Fast-dds_*.cxx)


add_executable(FastddsFuzz ${TARGET_DIR}/Fastdds/src/Fast-dds.cpp ${FAST_DDS_CPP} ${FAST_DDS_CXX} ${FUZZER_CPP})

target_link_libraries(FastddsFuzz fastrtps fastcdr)




