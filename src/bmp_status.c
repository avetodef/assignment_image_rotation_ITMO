#include "bmp_status.h"
#include <stdio.h>


static const char* const READ_STATUS_MSG[]={
    [READ_INVALID_PIXELS] = "READ_INVALID_PIXELS:the number of pixels read from the file is not equal to the width of the file itself.\n",
    [READ_INVALID_HEADER_BITCOUNT] = "READ_INVALID_HEADER_BITCOUNT: invalid header: BitCount is not RGB\n",
    [READ_INVALID_HEADER] = "READ_INVALID_HEADER: header is not readable\n",
    [READ_INVALID_SIGNATURE] = "READ_INVALID_SIGNATURE: file format is not bmp\n",
    [READ_SEEK_ERROR] = "READ_SEEK_ERROR: error during seeking occured\n",
    [READ_OK] = "READ_OK: file is read successfully\n"
};
static const char* const WRITE_STATUS_MSG[] = {
    [WRITE_PIXELS_ERROR] = "WRITE_PIXELS_ERROR: the number of pixels written to the file is not equal to the width of the file itself.\n",
    [WRITE_HEADER_ERROR] = "READ_INVALID_HEADER_BITCOUNT: invalid header: BitCount is not RGB\n",
    [WRITE_PADDING_ERROR] = "WRITE_PADDING_ERROR: size of written padding is not equal to the calculated one\n",
    [WRITE_SEEK_ERROR] = "WRITE_SEEK_ERROR: error occured during seeking\n",
    [WRITE_OK] = "WRITE_OK: image is written successfully\n"
};

void print_read_status(enum read_status status){
    if (status == READ_OK){
        fputs(READ_STATUS_MSG[status], stdout);
    }
    else{
        fputs(READ_STATUS_MSG[status], stderr);
    }
}

void print_write_status(enum write_status status){
    if (status == WRITE_OK){
        fputs(WRITE_STATUS_MSG[status], stdout);
    }
    else{
        fputs(WRITE_STATUS_MSG[status], stderr);
    }
}
