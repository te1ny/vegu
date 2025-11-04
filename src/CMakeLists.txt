file(GLOB_RECURSE HEADERS "*.hpp")
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE UI_FILES "*.ui")

set(EXECUTABLE_NAME vegu)
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCES} ${UI_FILES})
target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_20)
target_link_libraries(${EXECUTABLE_NAME} ${LIBRARIES})
