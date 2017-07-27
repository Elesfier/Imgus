cmake_minimum_required(VERSION 3.6)
project(Imgus)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -lboost_system -lboost_filesystem")
set(SOURCE_FILES
main.cpp
src/headers/main.h
src/headers/common.h
src/headers/format.h
src/headers/image.h
src/headers/operation.h
src/headers/operations.h
src/headers/point.h
src/headers/window.h
src/headers/windows.h
src/formats/PNG-manually.cpp
src/formats/PNG-manually.h
src/formats/PNG-decoder-encoder.h
src/formats/PNG-decoder-encoder.cpp
src/windows/QT.cpp
src/windows/QT.h
src/operations/cut.cpp
src/operations/move.cpp
src/operations/blending.cpp
src/operations/copy.cpp
src/operations/close.cpp
src/operations/open.cpp
src/operations/dilatation.cpp
src/operations/division.cpp
src/operations/lowpass.cpp
src/operations/erosion.cpp
src/operations/exponentiation.cpp
src/operations/gradient.cpp
src/operations/stretching.cpp
src/operations/global-thresholding.cpp
src/operations/local-thresholding.cpp
src/operations/multi-thresholding.cpp
src/operations/histogram.cpp
src/operations/log.cpp
src/operations/mediana.cpp
src/operations/multiplication.cpp
src/operations/nthRoot.cpp
src/operations/sum.cpp
src/operations/highpass.cpp
)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.58.0 REQUIRED)

find_package(PNG REQUIRED)
find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#MESSAGE("Searching for QWT")
FIND_PATH(QWT_INCLUDE_DIR NAMES qwt.h PATHS
  /usr/local/qwt-6.1.3/include
  PATH_SUFFIXES qwt-qt4 qwt
  )

FIND_LIBRARY(QWT_LIBRARY NAMES qwt qwt5 qwt-qt4 qwt5-qt4 PATHS
  /usr/local/qwt-6.1.3/lib
  )

IF (QWT_INCLUDE_DIR AND QWT_LIBRARY)
  SET(QWT_FOUND TRUE)
ENDIF (QWT_INCLUDE_DIR AND QWT_LIBRARY)

IF (QWT_FOUND)
  IF (NOT QWT_FIND_QUIETLY)
    MESSAGE(STATUS "Found QWT: ${QWT_LIBRARY}")
    include_directories(${QWT_INCLUDE_DIR})
  ENDIF (NOT QWT_FIND_QUIETLY)
ELSE (QWT_FOUND)
  IF (QWT_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find QWT")
  ENDIF (QWT_FIND_REQUIRED)
ENDIF (QWT_FOUND)

if(Boost_FOUND AND PNG_FOUND AND Qt5Widgets_FOUND)
    include_directories(${PNG_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(${Qt5Widgets_INCLUDE_DIRS})
    add_executable(Imgus ${SOURCE_FILES})
    target_link_libraries(Imgus ${PNG_LIBRARY})
    target_link_libraries(Imgus ${Boost_LIBRARIES})
    target_link_libraries(Imgus ${Qt5Widgets_LIBRARIES})
    target_link_libraries(Imgus ${QWT_LIBRARY})
endif()
