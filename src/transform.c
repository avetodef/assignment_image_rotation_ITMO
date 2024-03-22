#include "transform.h"
#include "img.h"
#include "pixel.h"
#include <stddef.h>
#include <stdio.h>

static void swap(struct pixel *a, struct pixel *b)
{
   struct pixel temp = *a;
   *a = *b;
   *b = temp;
}

static void img_mirror_horisontally(struct image *img){
   for (size_t i = 0; i < img->height / 2; i++)
   {
      for (size_t j = 0; j < img->width; j++)
      {
         swap(img_get(*img, j, i), img_get(*img, j, img->height - i - 1) );
      }
   }
}

static struct image img_transpose(struct image img){
   struct image transposed = img_create(img.height, img.width);
   for (size_t i = 0; i < img.height; i++)
   {
      for (size_t j = 0; j < img.width; j++)
      {
         struct pixel *pixel_transposed = img_get(transposed, i, j);
         *pixel_transposed = *img_get(img, j, i);
      }
   }
   return transposed;
}

struct image transform_counterclockwise_90_degrees(struct image *img){ 

   img_mirror_horisontally(img);
   struct image result = img_transpose(*img);

   return result;
}
