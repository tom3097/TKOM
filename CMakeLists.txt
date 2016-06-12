cmake_minimum_required(VERSION 2.8)
project(tkom)
set(CMAKE_BUILD_TYPE Debug)

include_directories(.
                    src
                    src/structs
                    src/structs/tokens
                    src/structs/objects
                    src/structs/variables
                    src/tests/testCase1)					
set(SOURCES
    src/structs/tokens/Token.cpp
    src/structs/objects/Objects.cpp
    src/structs/TextPosition.cpp
    src/structs/variables/VariableType.cpp
    src/tests/testCase1/Testcase1.cpp
    src/ErrorsCommunicator.cpp
    src/Source.cpp
    src/Lexer.cpp
    src/main.cpp
    src/Parser.cpp
    src/Storehouse.cpp
    src/Factory.cpp
   )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

add_executable(tkom ${SOURCES})
target_link_libraries(tkom ${PROJECT_LINK_LIBS})
