add_executable(unp_main main.c)
add_executable(daytimetcpcli daytimetcpcli.c)
target_link_libraries(daytimetcpcli unp)