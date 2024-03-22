#ifndef IMAGE_H
#define IMAGE_H

#include <stddef.h>
#include  <stdint.h>

struct image {
    size_t width;
    size_t height;
    struct pixel *pixels;
};
void img_destroy(struct image);
struct image img_create(uint32_t width, uint32_t height);
struct pixel* img_get(const struct image, const uint32_t, const uint32_t);

#endif
