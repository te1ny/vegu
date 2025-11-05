cmake_minimum_required(VERSION 4.0)
project(vegu
    VERSION 0.0.0
    LANGUAGES CXX
)

include(cmake/common.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(nlohmann_json REQUIRED COMPOMENTS nlohmann_json)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)

append_libraries(LIBRARIES Qt6::Core)
append_libraries(LIBRARIES Qt6::Widgets)

add_subdirectory(src)
