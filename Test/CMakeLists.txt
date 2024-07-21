cmake_policy(SET CMP0135 NEW)

set(YGG_TEST_EXE_NAME Ygg_Test)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${YGG_TEST_EXE_NAME}
        lsys_test.cc
		TerrainGenerator.cc
)

target_link_libraries(${YGG_TEST_EXE_NAME}
        GTest::gtest_main Ygg
)

include(GoogleTest)
gtest_discover_tests(${YGG_TEST_EXE_NAME})