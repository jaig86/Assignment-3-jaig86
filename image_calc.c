#include "barcode.h"
#include "loader.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv){
    // TODO: parse the arguments in argv. 
    // You can expect argv[1] to be the digits to encode
    // You can expect argv[2] to be the integer width
    // You can expect argv[3] to be the integer height
    // You can expect argv[4] to be the output filepath.

    if(argc != 5) {
        printf("Incorrect number of arguments. Expected: ./build/image_calc <barcode_value> <width> <height> <output_image_path>\n");
        return -1;
    }


    // TODO: call barcode
    
    // TODO: save result to file
}
