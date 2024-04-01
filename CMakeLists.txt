cmake_minimum_required(VERSION 3.5.1)
project(unix_programming CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# 确保 -std=c++xx
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 生成 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# 显示原始编译信息
set(CMAKE_VERBOSE_MAKEFILE ON)

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# 判断操作系统
message(STATUS "Current platform: ${CMAKE_SYSTEM_NAME}")
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_search_module(URIPARSER REQUIRED liburiparser)

    find_package(LIBEVENT REQUIRED)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_compile_options(-Wno-incompatible-function-pointer-types)
    find_package(uriparser CONFIG REQUIRED char)
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(LIBEVENT REQUIRED libevent)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    #to-do
endif ()

message(STATUS "apue dir: ${APUE}")
message(STATUS "unp dir: ${UNPV13}")
message(STATUS "csapp dir: ${CSAPP}")
message(STATUS "libevent dir: ${LIBEVENT_LINK_LIBRARIES}")

# 判断编译器
message(STATUS "Use ${CMAKE_CXX_COMPILER_ID}")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # using Visual Studio C++
endif ()

if (POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)
endif ()

include(CheckIncludeFiles)
check_include_files("pthread.h;stdatomic.h;sys/socket.h;netinet/in.h;unistd.h" HAS_HEADER)

if (NOT HAS_HEADER)
    message(FATAL_ERROR "Necessary header files are not found!")
endif ()

include(CheckSymbolExists)
check_symbol_exists(epoll_create "sys/epoll.h" EPOLL_EXISTS)
if (EPOLL_EXISTS)
    # Linux下设置为epoll
    set(EPOLL_ENABLE 1 CACHE INTERNAL "enable epoll")

    # Linux下也设置为poll
    # set(EPOLL_ENABLE "" CACHE INTERNAL "not enable epoll")
else ()
    set(EPOLL_ENABLE "" CACHE INTERNAL "not enable epoll")
endif ()

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/yolanda/config.h.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/include/config.h
)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/include
        /usr/local/include
        ${APUE}/include
        ${UNPV13}/lib
        ${CSAPP}/include
        src/lib
        src/lib/yolanda
        ${LIBEVENT_INCLUDE_DIRS}
)

link_directories(
        ${APUE}/lib
        ${UNPV13}
        ${CSAPP}/lib
)

add_subdirectory(src/lib)
# Essential C++
add_subdirectory(src/essential)
# C++ Primer
add_subdirectory(src/cpp_primer)
add_subdirectory(src/csapp)
add_subdirectory(src/apue)
add_subdirectory(src/unp)
add_subdirectory(src/concurrency)
add_subdirectory(src/core_in_c)
add_subdirectory(src/networking_in_action)
add_subdirectory(src/mini_http_server)
add_subdirectory(src/algorithm)
add_subdirectory(src/playground)
add_subdirectory(tests)

add_executable(main src/main.cpp)
