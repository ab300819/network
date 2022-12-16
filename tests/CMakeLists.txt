if (NOT DEFINED GoogleTest_DIR)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
    )

    if (CMAKE_SYSTEM_NAME MATCHES "Windows")
        # For Windows: Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif ()

    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)
else ()
    find_package(GoogleTest REQUIRED)
endif ()

enable_testing()

add_executable(
        hello_test
        hello_test.cpp
)

target_link_libraries(
        hello_test
        GTest::gtest_main
)

gtest_discover_tests(hello_test)