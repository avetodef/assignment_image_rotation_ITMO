#include "img.h"
#include "pixel.h"
#include <malloc.h>


struct image img_create(uint32_t width, uint32_t height)
{
    struct pixel *pixels = malloc(sizeof(struct pixel) * width * height);
    return (struct image){width, height, pixels};
}

void img_destroy(struct image image){
   free(image.pixels);
}

struct pixel* img_get(const struct image img, const uint32_t x, const uint32_t y){
    if (x >= img.width || y>= img.height){return NULL;}
    return img.pixels + x + y*img.width;
}
