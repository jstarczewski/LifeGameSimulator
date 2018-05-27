#include "game_board.h"

board init_board() {
    board play_board = (board) malloc(sizeof(struct life_game_board));
    play_board->index = 0;
    return play_board;
}

board set_width(board play_board, int width) {
    play_board->width = width;
    return play_board;
}

board set_height(board play_board, int height) {
    play_board->height = height;
    return play_board;
}

board init_vector(board play_board) {
    play_board->size = play_board->height * play_board->width;
    play_board->vector = (int *) malloc(play_board->size * sizeof(int));
    return play_board;
}

board add(board play_board, int value) {
    play_board->vector[play_board->index++] = value;
    return play_board;
}

