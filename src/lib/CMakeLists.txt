add_subdirectory(yolanda)

add_executable(thread thread.c)
target_link_libraries(thread pthread)

add_library(core helpers.c)
add_library(utils utils.c)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_executable(event_server epoll_tcp_server.c)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_executable(event_server kqueue_tcp_server.c)
endif ()

