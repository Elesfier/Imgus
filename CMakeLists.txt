cmake_minimum_required(VERSION 3.6)
project(Images)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system -lboost_filesystem")
set(SOURCE_FILES main.cpp src/operations/ImageNegation/operation.cpp src/common/common.hpp src/common/formats/PNG.cpp src/common/formats/PNG.hpp src/common/windows/QT.cpp src/common/windows/QT.hpp src/operations/operations.hpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.58.0 REQUIRED)

find_package(PNG REQUIRED)
find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(Boost_FOUND AND PNG_FOUND AND Qt5Widgets_FOUND)
    include_directories(${PNG_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(${Qt5Widgets_INCLUDE_DIRS})
    add_executable(Images ${SOURCE_FILES})
    target_link_libraries(Images ${PNG_LIBRARY})
    target_link_libraries(Images ${Boost_LIBRARIES})
    target_link_libraries(Images ${Qt5Widgets_LIBRARIES})
endif()