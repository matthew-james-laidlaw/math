add_executable(tests
    LexerTests.cpp
    ParserTests.cpp
    SimplifierTests.cpp)

target_link_libraries(tests PRIVATE gmock_main solver)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/src)
