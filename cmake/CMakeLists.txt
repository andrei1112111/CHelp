cmake_minimum_required(VERSION 3.29)
project(CHelp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(../chelp)


### SOURCE FILES ###
SET(  TERMINAL_SOURCE_UNIX
        ../chelp/src/terminal/unix/Terminal.cpp
)
######


### ASSEMBLE LIBRARIES ###
add_library(TerminalUnix STATIC ${TERMINAL_SOURCE_UNIX})
target_include_directories(TerminalUnix PRIVATE ../chelp/include/terminal ../chelp/include/terminal/unix ../chelp/src/terminal/unix)
set_target_properties(TerminalUnix PROPERTIES LINKER_LANGUAGE CXX)
######


### LINK LIBRARIES ###

######


### MAKE APPLICATION ###
add_executable(chelp ../chelp/console_utility_main.cpp)

target_link_libraries(chelp PRIVATE TerminalUnix)
######
