cmake_minimum_required(VERSION 3.5.2)
project(bigfile_performance)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pg")

set(SOURCE_FILES main.cpp)
add_executable(bigfile_performance ${SOURCE_FILES})

find_package(Boost COMPONENTS thread system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(bigfile_performance ${Boost_LIBRARIES})

