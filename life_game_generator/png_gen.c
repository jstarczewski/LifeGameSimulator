#ifndef PNG_GEN
#define PNG_GEN

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include <png.h>
#include "log.h"

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int PIXEL_SCALE = 16;
png_bytep *row_pointers;

void write_png_file(char *file_name) {
    int y;
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
        write_message(6);

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        write_message(6);

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        write_message(6);

    if (setjmp(png_jmpbuf(png_ptr)))
        write_message(6);

    png_init_io(png_ptr, fp);

    if (setjmp(png_jmpbuf(png_ptr)))
        write_message(6);

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 bit_depth, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
        write_message(6);

    png_write_image(png_ptr, row_pointers);

    if (setjmp(png_jmpbuf(png_ptr)))
        write_message(6);

    png_write_end(png_ptr, NULL);

    png_destroy_info_struct(png_ptr, &info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    for (y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}

void write_row(png_byte *row, int vec_y, int vec_width, const int vector[]) {
    int vec_x, scale_counter;
    for (vec_x = 0; vec_x < width / PIXEL_SCALE; vec_x++) {
        for (scale_counter = 0; scale_counter < PIXEL_SCALE; scale_counter++)
            row[vec_x * PIXEL_SCALE + scale_counter] = (png_byte) (vector[vec_y * vec_width + vec_x] == 1 ? 255 : 0);;
    }
}

void process_board(board play_board) {
    width = play_board->width * PIXEL_SCALE;
    height = play_board->height * PIXEL_SCALE;
    bit_depth = 8;
    color_type = PNG_COLOR_TYPE_GRAY;
    int y;
    int vec_y;

    row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
    for (y = 0; y < height; y++)
        row_pointers[y] = (png_byte *) malloc(sizeof(png_byte) * width);


    for (vec_y = 0; vec_y < height / PIXEL_SCALE; vec_y++) {
        for (y = 0; y < PIXEL_SCALE; y++) {
            png_byte *row = row_pointers[vec_y * PIXEL_SCALE + y];
            write_row(row, vec_y, play_board->width, play_board->vector);
        }
    }
}


void png_gen(board play_board, long gen_counter) {
    process_board(play_board);
    char filename[20];
    sprintf(filename, "gen_%li", gen_counter);
    write_png_file(filename);
}

#endif