cmake_minimum_required(VERSION 3.6)
project(Images)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system -lboost_filesystem")
set(SOURCE_FILES main.cpp common/images.hpp common/gui.hpp operations/1/1/operation.cpp forward-declaration.hpp common/common.hpp)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

# Including Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.58.0 REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(Images ${SOURCE_FILES})
    file(COPY graphics DESTINATION Storage)
    file(COPY documentation DESTINATION Storage)
    file(COPY graphics DESTINATION ${CMAKE_SOURCE_DIR}/bin)
    file(COPY documentation DESTINATION ${CMAKE_SOURCE_DIR}/bin)
    target_link_libraries(Images ${PNG_LIBRARY})
    target_link_libraries(Images ${Boost_LIBRARIES})
endif()