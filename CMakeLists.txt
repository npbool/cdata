cmake_minimum_required(VERSION 3.5)
project(cdata)
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/DataFrame.cpp
        src/DataFrame.h src/Series.h src/main.cpp src/Series.cpp)
    
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")


add_executable(cdata ${SOURCE_FILES})
