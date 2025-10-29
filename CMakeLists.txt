cmake_minimum_required(VERSION 4.0)
project(vegu
    VERSION 0.0.0
    LANGUAGES CXX
)

include(cmake/common.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)

file(GLOB_RECURSE HEADERS "*.hpp")
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE UI_FILES "*.ui")

append_libraries(LIBRARIES Qt6::Core)
append_libraries(LIBRARIES Qt6::Widgets)

set(EXECUTABLE_NAME vegu)
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCES} ${UI_FILES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_20)

# LINKING
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARIES})
