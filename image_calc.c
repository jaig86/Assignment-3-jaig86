#include "barcode.h"
#include "loader.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {

    if (argc != 5) {
        printf(
            "Incorrect number of arguments. "
            "Expected: ./build/image_calc "
            "<barcode_value> <width> <height> <output_image_path>\n"
        );

        return -1;
    }

    char* barcode_value = argv[1];
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    char* output_filepath = argv[4];

    struct image* result =
        barcode(barcode_value, width, height);

    if (result == NULL) {
        printf("ERROR: could not create barcode image\n");
        return -1;
    }

    int err = saveimage(output_filepath, result);

    if (err == -1) {
        printf("ERROR saving image\n");

        free(result->pixels);
        free(result);

        return -1;
    }

    free(result->pixels);
    free(result);

    return 0;
}