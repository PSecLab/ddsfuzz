
cmake_minimum_required(VERSION 3.16)
project(DDS_FUZZ LANGUAGES C CXX)



find_package(OpenDDS REQUIRED)

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
file(GLOB OPEN_DDS_CPP ${TARGET_DIR}/Opendds/lib/Open-dds_*.cpp)

add_executable(OpenddsFuzz ${TARGET_DIR}/Opendds/src/Open-dds.cpp ${OPEN_DDS_CPP} ${FUZZER_CPP})

configure_file(${TARGET_DIR}/Opendds/lib/Open-dds_rtps.ini . COPYONLY)

set(opendds_libs
  OpenDDS::Dcps # Core OpenDDS Library
  OpenDDS::InfoRepoDiscovery OpenDDS::Tcp # For run_test.pl
  OpenDDS::Rtps OpenDDS::Rtps_Udp # For run_test.pl --rtps
  OpenDDS::Security # For run_test.pl --security
)

target_link_libraries(OpenddsFuzz ${opendds_libs})


