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
add_executable(1-3 src/apue/1_3.c)
target_link_libraries(1-3 apue)

add_executable(1-4 src/apue/1_4.c)
target_link_libraries(1-4 apue)

add_executable(1-5 src/apue/1_5.c)
target_link_libraries(1-5 apue)

add_executable(1-6 src/apue/1_6.c)
target_link_libraries(1-6 apue)

add_executable(1-7 src/apue/1_7.c)
target_link_libraries(1-7 apue)

# unix unp
add_executable(unp src/unp/main.c)
