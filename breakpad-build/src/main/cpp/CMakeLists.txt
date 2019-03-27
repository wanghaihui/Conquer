# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)

project(breakpad-core)

set(ENABLE_INPROCESS ON)
set(ENABLE_OUTOFPROCESS ON)
set(ENABLE_LIBCORKSCREW ON)
set(ENABLE_LIBUNWIND ON)
set(ENABLE_LIBUNWINDSTACK ON)
set(ENABLE_CXXABI ON)
set(ENABLE_STACKSCAN ON)

# 指令add_definitions可以用來加入Preprocessor定义
if (${ENABLE_INPROCESS})
    add_definitions(-DENABLE_INPROCESS)
endif ()
if (${ENABLE_OUTOFPROCESS})
    add_definitions(-DENABLE_OUTOFPROCESS)
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror=implicit-function-declaration")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

# breakpad
include_directories(external/libbreakpad/src external/libbreakpad/src/common/android/include)
add_subdirectory(external/libbreakpad)
# APPEND添加新元素到列表中
list(APPEND LINK_LIBRARIES breakpad)

add_library(breakpad-core SHARED breakpad.cpp)
target_link_libraries(breakpad-core ${LINK_LIBRARIES} log)