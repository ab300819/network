add_executable(core_in_c main.c)
add_executable(test_cmocka test_cmocka.c)
target_link_libraries(test_cmocka cmocka)