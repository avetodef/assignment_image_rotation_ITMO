#ifndef BMP_STATUS_H
#define BMP_STATUS_H

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_PIXELS,
    READ_INVALID_HEADER,
    READ_INVALID_HEADER_BITCOUNT,
    READ_SEEK_ERROR
};

enum write_status {
    WRITE_OK = 0,
    WRITE_HEADER_ERROR,
    WRITE_PIXELS_ERROR,
    WRITE_PADDING_ERROR,
    WRITE_SEEK_ERROR
};

void print_read_status(enum read_status status);
void print_write_status(enum write_status status);

#endif
