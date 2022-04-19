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
	#    set(CMOCKA /usr/local/Cellar/cmocka/1.1.5)
    find_package(uriparser 0.9.6 CONFIG REQUIRED char)
endif ()

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

aux_source_directory(./src/mini_http_server DIR_SRCS)
add_subdirectory(libs src/concurrency)

# for executable.
add_executable(mini_http_server ${DIR_SRCS})
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(mini_http_server PUBLIC core m pthread ${URIPARSER_LIBRARIES})
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(mini_http_server PUBLIC core m pthread uriparser::uriparser)
endif ()

# c primer plus
add_executable(main src/main.c)

# unix apue
add_executable(apue_main src/apue/1_3.c)
target_link_libraries(apue_main apue)

# unix unp
add_executable(unp_main src/unp/main.c)
add_executable(server src/networking_in_action/server.c)
add_executable(client src/networking_in_action/client.c)
add_executable(daytimetcpcli src/unp/daytimetcpcli.c)
target_link_libraries(daytimetcpcli unp)

# core_in_c
add_executable(core_in_c src/core_in_c/main.c)

add_executable(test_cmocka src/core_in_c/test_cmocka.c)
target_link_libraries(test_cmocka cmocka)

add_executable(main_vector src/concurrency/main.cpp)
add_executable(1.5.1 src/essential/1.5.1.cpp)
add_executable(1.5.2 src/essential/1.5.2.cpp)
add_executable(1.7 src/essential/1.7.cpp)
