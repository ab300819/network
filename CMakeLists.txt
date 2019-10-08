cmake_minimum_required(VERSION 3.5.1)
project(unix_programming C)

set(CMAKE_C_STANDARD 11)

message(STATUS ${CMAKE_SYSTEM_NAME})
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(APUE /home/think/Projects/apue.3e)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(APUE /Users/mengshen/Project/apue)
endif ()

include_directories(${APUE}/include)
link_directories(${APUE}/lib)

# unix unp
add_executable(unp unp/main.c)

# unix programming
add_executable(1-3-ls apue/1_3_ls.c)
target_link_libraries(1-3-ls apue)

add_executable(1-4-io apue/1_4_io.c)
target_link_libraries(1-4-io apue)