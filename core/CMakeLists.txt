cmake_minimum_required(VERSION 3.16)
project(DDS_FUZZ LANGUAGES C CXX)

add_subdirectory(Fuzzer)
add_subdirectory(cyclonedds)
add_subdirectory(Fastdds)
add_subdirectory(Opendds)