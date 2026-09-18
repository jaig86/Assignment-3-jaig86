#include "barcode.h"
#include <stdlib.h>
#include <string.h>

static const char* LEFT_PATTERNS[10] = {
    "1110010",
    "1100110",
    "1101100",
    "1010000",
    "1011100",
    "1001110",
    "1000010",
    "1000100",
    "1001000",
    "1110100"
};


/*
 * Fill one vertical column.
 *
 * white = 1 -> RGB 255,255,255
 * white = 0 -> RGB 0,0,0
 */
void fill_column(
    struct image* img,
    int x,
    int white
) {

    int value;

    if (white) {
        value = 255;
    } else {
        value = 0;
    }

    for (int y = 0; y < img->height; y++) {

        int index =
            y * img->width + x;

        img->pixels[index].r = value;
        img->pixels[index].g = value;
        img->pixels[index].b = value;
    }
}


/*
 * Write a pattern such as "010" or "1110010".
 *
 * invert = 0 -> use pattern normally
 * invert = 1 -> reverse white/black
 */
void fill_pattern(
    struct image* img,
    int* x,
    const char* pattern,
    int invert
) {

    for (int i = 0;
         pattern[i] != '\0';
         i++) {

        int bit =
            pattern[i] - '0';

        if (invert) {
            bit = !bit;
        }

        fill_column(
            img,
            *x,
            bit
        );

        (*x)++;
    }
}


struct image* barcode(
    char* data,
    int width,
    int height
) {

    // Barcode must contain exactly 12 digits
    if (strlen(data) != 12) {
        return NULL;
    }

    // Verify all characters are digits
    for (int i = 0; i < 12; i++) {

        if (data[i] < '0' ||
            data[i] > '9') {

            return NULL;
        }
    }

    // Barcode itself requires 113 columns
    if (width < 113 ||
        height <= 0) {

        return NULL;
    }


    struct image* img =
        malloc(sizeof(struct image));

    if (img == NULL) {
        return NULL;
    }


    img->width = width;
    img->height = height;


    img->pixels =
        malloc(
            sizeof(struct pixel)
            * width
            * height
        );

    if (img->pixels == NULL) {

        free(img);

        return NULL;
    }


    // Start with entire image white
    for (int i = 0;
         i < width * height;
         i++) {

        img->pixels[i].r = 255;
        img->pixels[i].g = 255;
        img->pixels[i].b = 255;
    }


    int x = 0;


    // Quiet zone - 9 white columns
    for (int i = 0; i < 9; i++) {
        fill_column(img, x, 1);
        x++;
    }


    // Start pattern
    fill_pattern(
        img,
        &x,
        "010",
        0
    );


    // First 6 digits use left encoding
    for (int i = 0; i < 6; i++) {

        int digit =
            data[i] - '0';

        fill_pattern(
            img,
            &x,
            LEFT_PATTERNS[digit],
            0
        );
    }


    // Middle pattern
    fill_pattern(
        img,
        &x,
        "10101",
        0
    );


    // Last 6 digits use inverted encoding
    for (int i = 6; i < 12; i++) {

        int digit =
            data[i] - '0';

        fill_pattern(
            img,
            &x,
            LEFT_PATTERNS[digit],
            1
        );
    }


    // End pattern
    fill_pattern(
        img,
        &x,
        "010",
        0
    );


    // Final quiet zone
    for (int i = 0; i < 9; i++) {

        fill_column(
            img,
            x,
            1
        );

        x++;
    }


    return img;
}