cmake_minimum_required(VERSION 3.28)
project(CaptureKeyUtility)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBEVDEV_INCLUDE_PATH ${PATH_TO_SYSROOT}/usr/include/libevdev-1.0)
# Поиск библиотеки libevdev
find_library(LIBEVDEV_LIBRARY
        NAMES evdev
        PATHS /usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib /lib ${PATH_TO_SYSROOT}/usr/lib
        NO_DEFAULT_PATH
)

if (LIBEVDEV_LIBRARY)
    message(STATUS "Found libevdev: ${LIBEVDEV_LIBRARY}")
else()
    message(FATAL_ERROR "libevdev not found. Please install libevdev development files.")
endif()

message(STATUS "env PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/yaml-cpp/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/yaml-cpp)

add_executable(CaptureKeyUtility main.cpp)

target_include_directories(CaptureKeyUtility PRIVATE ${LIBEVDEV_INCLUDE_PATH})
target_link_libraries(CaptureKeyUtility PRIVATE ${LIBEVDEV_LIBRARY})

target_link_libraries(CaptureKeyUtility PRIVATE yaml-cpp::yaml-cpp)

target_include_directories(CaptureKeyUtility PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)
