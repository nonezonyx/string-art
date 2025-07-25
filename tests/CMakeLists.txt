find_package(GTest REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(string-art-test string_art_test.cpp)

target_link_libraries(string-art-test
    PRIVATE
        string_art_lib
        GTest::gtest
        GTest::gtest_main
        ${OpenCV_LIBS}
)

add_test(NAME string-art-test COMMAND string-art-test)
