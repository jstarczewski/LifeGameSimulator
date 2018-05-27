#ifndef PNG_GEN
#define PNG_GEN

#include "board.h"


void write_png_file(char *file_name);

void process_board(board play_board);

void png_gen(board play_board, long gen_counter);

#endif
