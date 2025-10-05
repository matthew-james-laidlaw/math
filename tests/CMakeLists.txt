add_executable(tests
    LexerTests.cpp
    ParserTests.cpp
    SimplifierTests.cpp)

target_link_libraries(tests gmock_main solver)
