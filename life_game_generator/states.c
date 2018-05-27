

#include "game_board.h"

int check_Moore(board play_board, int index) {
    int neighbours_state = 0;
    int sindex = 0;
    int left = (-1);
    int right = 1;
    int width = play_board->width;
    int height = play_board->height;
    if ((index % width) == 0) {
        right = 1;
        left = width - 1;
    }
    if (((index + 1) % width) == 0) {
        right = (-1 * width) + 1;
        left = -1;
    }

    if (play_board->vector[index + right] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[index + left] == 1) {
        neighbours_state++;
    }
    if (index - width < 0) {
        sindex = index + (width * height) - width;
    } else {
        sindex = index - width;
    }
    if (play_board->vector[sindex] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[sindex + right] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[sindex + left] == 1) {
        neighbours_state++;
    }
    if (index + width >= (width * height)) {
        sindex = index - (width * (height - 1));
    } else {
        sindex = index + width;
    }
    if (play_board->vector[sindex] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[sindex + right] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[sindex + left] == 1) {
        neighbours_state++;
    }
    return neighbours_state;
}


int check_Neumman(board play_board, int index) {
    int neighbours_state = 0;
    int sindex = 0;
    int left = (-1);
    int right = 1;
    int width = play_board->width;
    int height = play_board->height;
    if ((index % width) == 0) {
        right = 1;
        left = width - 1;
    }
    if (((index + 1) % width) == 0) {
        right = (-1 * width) + 1;
        left = -1;
    }

    if (play_board->vector[index + right] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[index + left] == 1) {
        neighbours_state++;
    }
    if (index - width < 0) {
        sindex = index + (width * height) - width;
    } else {
        sindex = index - width;
    }
    if (play_board->vector[sindex] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[sindex + right] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[sindex + left] == 1) {
        neighbours_state++;
    }
    if (index + width >= (width * height)) {
        sindex = index - (width * (height - 1));
    } else {
        sindex = index + width;
    }
    if (play_board->vector[sindex] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[sindex + right] == 1) {
        neighbours_state++;
    }
    if (play_board->vector[sindex + left] == 1) {
        neighbours_state++;
    }
    return neighbours_state;
}
