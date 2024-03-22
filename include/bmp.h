#ifndef BMP_H
#define BMP_H
#include <stdint.h>
#include <stdio.h>
#include "img.h"
#include "bmp_status.h"

FILE *file_open_to_read(char *);
FILE *file_open_to_write(char *);
void close_bmp(FILE*);
enum read_status from_bmp(FILE *, struct image *);
enum write_status to_bmp(FILE *, struct image *);

#endif
