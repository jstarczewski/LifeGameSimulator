#include <stdio.h>
#include <stdlib.h>
#include "game_board.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "log.h"


int main(int argc, char **argv) {


    open_log();
    write_message(9);

    if (argc != 5) {
        write_message(1);
        write_message(0);
        close_log();
        return EXIT_FAILURE;
    }

    char *first_gen_filename;
    first_gen_filename = argv[1];

    char *endptr;
    errno = 0;
    long gen_number;
    gen_number = strtol(argv[2], &endptr, 0);
    if (errno == ERANGE || *endptr != '\0' || argv[2] == endptr) {
        write_message(2);
        write_message(0);
        close_log();
        return EXIT_FAILURE;
    }

    enum neighbourhood_type neighbourhood;
    if (strcmp(argv[3], "-M") == 0) neighbourhood = M;
    else if (strcmp(argv[3], "-N") == 0) neighbourhood = N;
    else {
        write_message(3);
        write_message(0);
        close_log();
        return EXIT_FAILURE;
    }

    char *output_dir = argv[4];

    board play_board = init_board();
    FILE *in = fopen(first_gen_filename, "r");
    if (in == NULL) {
        write_message(8);
        write_message(0);
        free(play_board);
        close_log();
        return EXIT_FAILURE;
    }
    if (generate_board(in, play_board) == EXIT_FAILURE) {
        free(play_board);
	fclose(in);
        close_log();
        return EXIT_FAILURE;
    }

    fclose(in);

    write_message(10);
    if (play_board == NULL) {
        close_log();
        return EXIT_FAILURE;
    }

    write_message(11);
    struct stat st = {0};
    if (stat("output", &st) == -1) {
        mkdir("output", 0777);
    }

    chdir("output");


    if (stat(output_dir, &st) == -1) {
        mkdir(output_dir, 0777);
    } else {
        write_message(4);
        write_message(0);
        close_log();
        free(play_board);
        return EXIT_FAILURE;
    }

    chdir(output_dir);

    write_message(12);
    if (generate_states(play_board, gen_number, neighbourhood) == EXIT_FAILURE) {
        write_message(5);
        write_message(0);
        close_log();
        return EXIT_FAILURE;
    };


    write_message(13);
    close_log();
    return 0;
}
