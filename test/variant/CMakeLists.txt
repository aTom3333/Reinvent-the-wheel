add_executable(variantTest ../tests.cpp test_variant.cpp)
target_link_libraries(variantTest PUBLIC Catch::Catch)
target_link_libraries(variantTest PRIVATE variant)

# Register test
add_test(NAME "Test_variant"
        COMMAND variantTest)
