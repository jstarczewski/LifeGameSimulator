

#ifndef LIFE_GAME_GENERATOR_BOARD_H
#define LIFE_GAME_GENERATOR_BOARD_H

typedef struct life_game_board {
    int index;
    int size;
    int *vector;
    int height;
    int width;
} *board;

board init_board();

board init_vector(board play_board);

board set_width(board play_board, int width);

board set_height(board play_board, int height);

board add(board play_board, int value);

#endif
