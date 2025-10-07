add_library(solver AST.cpp Lexer.cpp Parser.cpp)
target_include_directories(solver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
