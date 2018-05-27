#include "game_board.h"
#include "log.h"
#include "errno.h"


int generate_board(FILE *board_file, board play_board) {

    int index = 0;

    char tmp = EOF;
    char *str_val;
    str_val = &tmp;
    char *endptr;
    int val;
    while (fscanf(board_file, "%s", str_val) != EOF) {
        val = (int) strtol(str_val, &endptr, 0);
        if (errno == ERANGE || str_val == endptr) {
            write_message(5);
            write_message(0);
            if(index > 2){
                free(play_board->vector);
            }
            return EXIT_FAILURE;
        }
        switch (index) {
            case 0: {
                play_board = set_width(play_board, val);
                index++;
                break;
            }
            case 1: {
                play_board = set_height(play_board, val);
                play_board = init_vector(play_board);
                if (play_board->vector == NULL) {
                    free(play_board->vector);
                    free(play_board);
                    return EXIT_FAILURE;
                }
                index++;
                break;
            }
            default: {
                if (val != 0 && val != 1) {
                    write_message(5);
                    write_message(0);
                    free(play_board->vector);
                    free(play_board);
                    return EXIT_FAILURE;
                }
                play_board = add(play_board, val);
            }
        }
    }
    if (play_board->index != (play_board->width * play_board->height)) {
        write_message(5);
        write_message(0);
        free(play_board->vector);
        return EXIT_FAILURE;
    }
    print_board(play_board);
    return 0;
}

int generate_states(board play_board, long states, enum neighbourhood_type neighbourhood) {
    long i = 0;

    board play_board_v2 = init_board();
    if (play_board_v2 == NULL) {
        free(play_board_v2);
        return EXIT_FAILURE;
    }

    play_board_v2 = set_width(play_board_v2, play_board->width);
    play_board_v2 = set_height(play_board_v2, play_board->height);
    play_board_v2 = init_vector(play_board_v2);
    if (play_board_v2->vector == NULL) {
        free(play_board_v2->vector);
        free(play_board_v2);
        free(play_board->vector);
        free(play_board);
        return EXIT_FAILURE;
    }

    create_board_file(play_board, "first_gen");
    while (i < states) {
        png_gen(play_board, i);
        if (i % 2 == 0)
            next_state(play_board, neighbourhood, play_board_v2);
        else
            next_state(play_board_v2, neighbourhood, play_board);
        i++;
    }
    create_board_file(play_board, "last_gen");

    free(play_board->vector);
    free(play_board);
    free(play_board_v2->vector);
    free(play_board_v2);
    return 0;
}

void next_state(board play_board, enum neighbourhood_type neighbourhood, board play_board_v2) {

    int checked_value = 0;
    int i;
    for (i = 0; i < play_board->index; i++) {
        if (neighbourhood == M) {
            checked_value = check_Moore(play_board, i);
        }
        if (neighbourhood == N) {
            checked_value = check_Neumman(play_board, i);
        }

        if (play_board->vector[i] == 0) {
            if (checked_value == 3) {
                add(play_board_v2, 1);
            } else {
                add(play_board_v2, 0);
            }
        }
        if (play_board->vector[i] == 1) {
            if (checked_value == 3 || checked_value == 2) {
                add(play_board_v2, 1);
            } else {
                add(play_board_v2, 0);
            }
        }
    }
    play_board->index = 0;
}

void print_board(board play_board) {
    int i;
    for (i = 0; i < play_board->index; i++) {
        printf(" %i ", play_board->vector[i]);
        if ((i + 1) % (play_board->width) == 0)
            printf("\n");
    }
    printf("\n\n");
}

void create_board_file(board play_board, char *filename) {
    FILE *out;
    int x, y;

    out = fopen(filename, "w");
    if (out == NULL) {
        write_message(8);
        return;
    }


    fprintf(out, "%d %d\n", play_board->width, play_board->height);

    for (y = 0; y < play_board->height; y++) {
        for (x = 0; x < play_board->width; x++) {
            fprintf(out, "%d ", play_board->vector[y * play_board->width + x]);
        }
        fprintf(out, "\n");
    }
    fclose(out);
}
