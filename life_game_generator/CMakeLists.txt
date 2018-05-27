cmake_minimum_required(VERSION 3.9)
project(life_game_generator C)

set(CMAKE_C_STANDARD 99)

add_executable(life_game_generator main.c game_board.h game_board.c states.h states.c board.h board.c png_gen.h png_gen.c log.c log.h)
target_link_libraries(life_game_generator png)