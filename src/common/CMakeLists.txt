set(DIR_LIB_SRCS helpers.c )
add_library(core ${DIR_LIB_SRCS})

add_executable(thread thread.c)
target_link_libraries(thread pthread)