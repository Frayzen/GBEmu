cmake_minimum_required(VERSION 3.30)
project(GBEnum VERSION 1.0 DESCRIPTION "A GameBoy emulator" LANGUAGES C)

find_package(Curses REQUIRED)


file(GLOB_RECURSE sources RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(GBEmu ${sources})
target_link_libraries(GBEmu ${NCURSES_LIBRARIES})
target_include_directories(GBEmu PRIVATE ${PROJECT_SOURCE_DIR}/src ${NCURSES_INCLUDE_DIRS})

