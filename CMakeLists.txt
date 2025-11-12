cmake_minimum_required(VERSION 4.0)
project(vegu
    VERSION 0.0.0
    LANGUAGES CXX
)

include(cmake/common.cmake)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Svg SvgWidgets)
add_subdirectory(externals/tomlplusplus)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)

append_libraries(LIBRARIES Qt6::Core)
append_libraries(LIBRARIES Qt6::Widgets)
append_libraries(LIBRARIES Qt6::Gui)
append_libraries(LIBRARIES Qt6::Svg)
append_libraries(LIBRARIES Qt6::SvgWidgets)
append_libraries(LIBRARIES tomlplusplus::tomlplusplus)

add_subdirectory(src)
