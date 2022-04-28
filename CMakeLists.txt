cmake_minimum_required(VERSION 3.5.1)
project(unix_programming CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS ${CMAKE_SYSTEM_NAME})
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(APUE /opt/apue.3e)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    find_package(PkgConfig REQUIRED)
    pkg_search_module(URIPARSER REQUIRED liburiparser)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(CMAKE_OSX_DEPLOYMENT_TARGET)
    set(APUE /Users/mason/Project/book_source/unix/apue.3e)
    set(UNPV13 /Users/mason/Project/book_source/unix/unpv13e)
    find_package(uriparser 0.9.6 CONFIG REQUIRED char)
endif ()

# C 单元测试模块
find_package(cmocka REQUIRED)

include(CheckIncludeFiles)
check_include_files("pthread.h;stdatomic.h;sys/socket.h;netinet/in.h;unistd.h" EDEPS)
if (EPTHREAD EQUAL 1)
    message(FATAL_ERROR "Necessary header files are not found!")
endif ()

include_directories(.
        /usr/local/include
        ${APUE}/include
        ${UNPV13}/include)

link_directories(${APUE}/lib
        ${UNPV13}/lib)

add_subdirectory(libs)
add_subdirectory(src/apue)
add_subdirectory(src/concurrency)
add_subdirectory(src/core_in_c)
add_subdirectory(src/essential)
add_subdirectory(src/mini_http_server)
add_subdirectory(src/networking_in_action)
add_subdirectory(src/unp)

add_executable(main src/main.c)