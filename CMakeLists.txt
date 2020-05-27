cmake_minimum_required(VERSION 3.16)
project(Euler1dPlot)

set(CMAKE_CXX_STANDARD 17)

# import qt5 library
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/rustam/Program/Qt/5.14.2/gcc_64")
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Qt5Charts) # For math-figure


# add solver for 1d Euler problem
add_subdirectory(GodunovsMethod/src)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
message(${SOURCES})

add_executable(Euler1dPlot ${HEADERS} ${SOURCES})
target_link_libraries(Euler1dPlot Qt5::Core Qt5::Widgets Qt5::Charts GodunovMethod)