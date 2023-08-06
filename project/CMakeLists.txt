cmake_minimum_required(VERSION 3.10)
project(example)

add_executable(${PROJECT_NAME} main.cpp)

include(ExternalProject)

set(NAVIGATOR_SOURCE_DIR "${CMAKE_SOURCE_DIR}/../source/")

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(LIB_EXT "dylib")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIB_EXT "dll")
else()
    set(LIB_EXT "so")
endif()

target_link_libraries(
    ${PROJECT_NAME}
        "${NAVIGATOR_SOURCE_DIR}/libbluerobotics_navigator.${LIB_EXT}"
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
target_include_directories(${PROJECT_NAME} PRIVATE "${NAVIGATOR_SOURCE_DIR}")
