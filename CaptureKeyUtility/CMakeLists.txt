cmake_minimum_required(VERSION 3.5)

set(CMAKE_TOOLCHAIN_FILE "/home/dmitriy/buildroot2/buildroot/output/host/share/buildroot/toolchainfile.cmake")

set(CMAKE_BUILD_TYPE Release)

set(PATH_TO_SYSROOT "/home/dmitriy/buildroot2/buildroot/output/host/aarch64-buildroot-linux-gnu/sysroot")


set(LIBEVDEV_INCLUDE_PATH ${PATH_TO_SYSROOT}/usr/include/libevdev-1.0)
set(LIBEVDEV_LIBRARY ${PATH_TO_SYSROOT}/usr/lib/libevdev.so)


set(YAML_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp)
set(YAML_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libyaml-cpp.a)


project(CaptureKeyUtility LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавьте исполняемый файл
add_executable(CaptureKeyUtility main.cpp)


# Подключите библиотеки и заголовочные файлы
target_include_directories(CaptureKeyUtility PRIVATE ${LIBEVDEV_INCLUDE_PATH})
target_link_libraries(CaptureKeyUtility PRIVATE ${LIBEVDEV_LIBRARY})

target_include_directories(CaptureKeyUtility PRIVATE ${YAML_INCLUDE_PATH})
target_link_libraries(CaptureKeyUtility PRIVATE ${YAML_LIBRARY})

target_include_directories(CaptureKeyUtility PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)
