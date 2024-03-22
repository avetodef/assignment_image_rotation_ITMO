#include "bmp.h"

#include "bmp_status.h"
#include "img.h"
#include "pixel.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTES_IN_PIXEL 3

#define BM_HEX 0x4D42
#define RESERVED 0
#define INFO_HEADER_SIZE 40
#define NUMBER_OF_PLANES 1
#define BITS_PER_PIXEL_RGB 24
#define NO_COMPRESSION 0
#define PIXELS_PER_METER 2834
#define USED_COLORS 0
#define IMPORTANT_COLORS 0
#define GARBAGE 0

struct bmp_header
{
        uint16_t bfType;
        uint32_t bfileSize;
        uint32_t bfReserved;
        uint32_t bOffBits;
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
} __attribute__((packed));

static uint32_t padding_calculate(uint32_t img_width_pixels)
{
    const uint32_t img_width_bytes = img_width_pixels * BYTES_IN_PIXEL;

    if (img_width_bytes % 4 == 0)
    {
        return 0;
    }
    else
    {
        return 4 - (img_width_bytes % 4);
    }
}

static uint32_t padding_calculate_all(uint32_t img_width_pixels, uint32_t img_height_pixels)
{
    return padding_calculate(img_width_pixels) * (img_height_pixels + 1);
}

FILE *file_open_to_read(char *in_file)
{
    return fopen(in_file, "rb");
}

void close_bmp(FILE* file){
    fclose(file);
}

FILE *file_open_to_write(char *out_file)
{
    return fopen(out_file, "wb");
}

static struct bmp_header header_create(struct image *img){
    struct bmp_header file_header = {0};
    const uint32_t img_size = img->width * img->height * BYTES_IN_PIXEL + padding_calculate_all(img->width, img->height);

    file_header.bfType = BM_HEX;
    file_header.bfileSize = sizeof(struct bmp_header) + img_size;
    file_header.bfReserved = RESERVED;
    file_header.bOffBits = sizeof(struct bmp_header);

    file_header.biSize = INFO_HEADER_SIZE;
    file_header.biWidth = img->width;
    file_header.biHeight = img->height;

    file_header.biPlanes = NUMBER_OF_PLANES;
    file_header.biBitCount = BITS_PER_PIXEL_RGB;
    file_header.biCompression = NO_COMPRESSION;
    file_header.biSizeImage = img_size;

    file_header.biXPelsPerMeter = PIXELS_PER_METER;
    file_header.biYPelsPerMeter = PIXELS_PER_METER;
    file_header.biClrUsed = USED_COLORS;
    file_header.biClrImportant = IMPORTANT_COLORS;

    return file_header;
}
static enum read_status check_bmp_header_read(FILE *in, struct bmp_header* header){
    if (fread(header, sizeof(struct bmp_header), 1, in) != 1){
        return READ_INVALID_HEADER;
    }
    
    if (header->bfType != BM_HEX){
         return READ_INVALID_SIGNATURE;
    }

    if (header->biBitCount != BITS_PER_PIXEL_RGB){
        return READ_INVALID_HEADER_BITCOUNT;
    }
    return READ_OK;
}

enum read_status from_bmp(FILE *in, struct image *img){
    struct bmp_header header = {0};

    enum read_status header_check = check_bmp_header_read(in, &header);

    if (header_check!= READ_OK){
        return header_check;
    }
    
    const uint32_t file_width = header.biWidth;
    const uint32_t file_height = header.biHeight;

    struct image img_temp = img_create(file_width, file_height);

    const uint32_t padding = padding_calculate(file_width);

    for (size_t i = 0; i < file_height; i++)
    {
        if (fread(img_temp.pixels + i * file_width, sizeof(struct pixel), file_width, in) != file_width) {
            img_destroy(img_temp);
            return READ_INVALID_PIXELS;
        }

        if(fseek(in, padding, SEEK_CUR) == -1){
            img_destroy(img_temp);
            return READ_SEEK_ERROR;
        }
    }

    *img = img_temp;

    return READ_OK;
}

enum write_status to_bmp(FILE *out, struct image *img){
    const char garbage[4] = {GARBAGE, GARBAGE, GARBAGE, GARBAGE};

    const struct bmp_header file_header = header_create(img);  

    if (fwrite(&file_header, sizeof(struct bmp_header), 1, out)!= 1){
        return WRITE_HEADER_ERROR;
    }

    struct pixel *pixels = img->pixels;

    for (size_t i = 0; i < img->height; i++)
    {
        if (fwrite(pixels + i * img->width, sizeof(struct pixel), img->width, out)!= img->width){
            return WRITE_PIXELS_ERROR;
        }
        uint32_t padding = padding_calculate(img->width);
        if (fwrite(&garbage, sizeof(int8_t), padding, out)!= padding) return WRITE_PADDING_ERROR;
            
    }

    return WRITE_OK;
}
