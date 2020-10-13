cmake_minimum_required(VERSION 3.5.1)
project(unix_programming C)

set(CMAKE_C_STANDARD 11)

message(STATUS ${CMAKE_SYSTEM_NAME})
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    # set(APUE apue.3e)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    # set(APUE /Users/mason/Project/book_source/unix/apue.3e)
endif ()

set(APUE apue.3e)
include_directories(${APUE}/include)
link_directories(${APUE}/lib)

# c primer plus
add_executable(main src/main.c)

# unix apue
add_executable(apue_main src/apue/1_3.c)
target_link_libraries(apue_main apue)

# unix unp
add_executable(unp_main src/unp/main.c)

add_executable(server src/explore/server.c)
add_executable(client src/explore/client.c)