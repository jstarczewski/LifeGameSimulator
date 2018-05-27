
#ifndef LIFE_GAME_GENERATOR_GAME_BOARD_H
#define LIFE_GAME_GENERATOR_GAME_BOARD_H

#include "states.h"
#include "board.h"
#include "png_gen.h"
#include <stdlib.h>
#include <stdio.h>

enum neighbourhood_type {
    M, N
};

int generate_board(FILE* board_file, board play_board);

void next_state(board play_board, enum neighbourhood_type neighbourhood, board play_board_v2);

void print_board(board play_board);

void create_board_file(board play_board, char *filename);

int generate_states(board play_board, long states, enum neighbourhood_type neighbourhood);


#endif
