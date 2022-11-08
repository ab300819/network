add_executable(thread thread.c)
target_link_libraries(thread pthread)

add_library(core helpers.c)
add_library(utils utils.c)

add_executable(kqueue_tcp_server kqueue_tcp_server.c)