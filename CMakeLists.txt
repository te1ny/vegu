cmake_minimum_required(VERSION 4.0)
project(vegu
    VERSION 0.0.0
    LANGUAGES CXX
)

include(cmake/common.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)

append_libraries(LIBRARIES Qt6::Core)
append_libraries(LIBRARIES Qt6::Widgets)
append_libraries(LIBRARIES Qt6::Gui)

add_subdirectory(src)
