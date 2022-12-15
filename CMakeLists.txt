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

# 判断操作系统
message(STATUS "Current platform: ${CMAKE_SYSTEM_NAME}")
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(APUE /opt/apue.3e)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    find_package(PkgConfig REQUIRED)
    pkg_search_module(URIPARSER REQUIRED liburiparser)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
#    set(CMAKE_OSX_DEPLOYMENT_TARGET)
    set(APUE /Users/mason/Project/book_source/unix/apue.3e)
    set(UNPV13 /Users/mason/Project/book_source/unix/unpv13e)
    find_package(uriparser 0.9.6 CONFIG REQUIRED char)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")

endif ()

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

include(CheckIncludeFiles)
check_include_files("pthread.h;stdatomic.h;sys/socket.h;netinet/in.h;unistd.h" HAS_HEADER)

if (NOT HAS_HEADER)
    message(FATAL_ERROR "Necessary header files are not found!")
endif ()

# C 单元测试模块
find_package(cmocka REQUIRED)

include_directories(.
        /usr/local/include
        ${APUE}/include
        ${UNPV13}/include
        src/common)

link_directories(${APUE}/lib
        ${UNPV13}/lib)

add_subdirectory(src/common)
add_subdirectory(src/apue)
add_subdirectory(src/concurrency)
add_subdirectory(src/core_in_c)
add_subdirectory(src/essential)
add_subdirectory(src/mini_http_server)
add_subdirectory(src/networking_in_action)
add_subdirectory(src/unp)
add_subdirectory(src/algorithm)
add_subdirectory(tests)

add_executable(main src/main.cpp)