cmake_minimum_required(VERSION 3.6)
project(SPAM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Common/image-operation.h Common/gui.h Common/tools.h Projects/1/1/operation.cpp forward-declaration.h)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

# Including Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.60.0 REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(SPAM ${SOURCE_FILES})
    target_link_libraries(SPAM ${PNG_LIBRARY})
    target_link_libraries(SPAM ${Boost_LIBRARIES})
endif()