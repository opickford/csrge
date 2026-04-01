add_executable(test_v3
    "test_v3.c"
)

target_link_libraries(test_v3 PRIVATE engine)

add_test(NAME test_v3 COMMAND test_v3)
