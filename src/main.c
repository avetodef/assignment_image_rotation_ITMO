#include "bmp.h"
#include "bmp_status.h"
#include "img.h"
#include "transform.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc!=3){
        fputs("Incorrect amount of arguments", stderr);
        return -1;
    } 
    (void)argc;
    (void)argv; // supress 'unused parameters' warning

    struct image img = {0};

    char* in_file_name = argv[1];
    char* out_file_name = argv[2];
    
    FILE* in_file = file_open_to_read(in_file_name);
    
    if (!in_file)
    {
        fputs("no such file", stderr);
        return -1;
    }
    FILE* out_file = file_open_to_write(out_file_name);

    enum read_status status_r = from_bmp(in_file, &img);

    print_read_status(status_r);
    if (status_r != READ_OK){
        return -1;
    }

    struct image result = transform_counterclockwise_90_degrees(&img);

    enum write_status status_w = to_bmp(out_file, &result);

    print_write_status(status_w);
    if (status_w != WRITE_OK){    
        return -1;
    }
    
    img_destroy(result);
    img_destroy(img);

    close_bmp(in_file);
    close_bmp(out_file);

    return 0;
}
