cmake_minimum_required(VERSION 3.10)

# set the project name
project(BigFun)

set(CURSES_USE_NCURSES TRUE)
set(CURSES_LIBRARY "C:/mingw64/mingw64/opt/lib/libncursesw.a")
set(CURSES_INCLUDE_PATH "C:/mingw64/mingw64/opt/include")

include_directories("include")
include_directories(${CURSES_INCLUDE_PATH})
file(GLOB_RECURSE srcfiles src/*)
find_package(Curses REQUIRED)


# add the executable
add_executable(BigFun ${srcfiles})
target_link_libraries(BigFun ${CURSES_LIBRARY})