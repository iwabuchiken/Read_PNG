/* 
 * File:   main.c
 * Author: iwabuchik
 *
 * Created on May 11, 2014, 12:29 AM
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef PNGLIB_H
#include "include/pnglib.h"
#endif

#include <png.h>

//#include <allegro.h>

void _test_ReadPNG(void);
void _test_LibPNG(void);


/*
 * 
 */
int main(int argc, char** argv) {

    printf("yes\n");
    
    _test_LibPNG();
    
    

    
    show_message_png();
    
    _test_ReadPNG();
    
    return (EXIT_SUCCESS);
}

void _test_ReadPNG(void)
{

    FILE *fp;
    
    ulg pWidth, pHeight;
    
    char *fname_src = "/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images/080f921b_PutumayoPresents_LatinJazz.png";
    
    fp = fopen(fname_src, "rb");
    
    if(fp == NULL) {
        
        //log
        printf("[%s : %d] fp => NULL\n", base_name(__FILE__), __LINE__);
        
        exit(1);

    } else {
        
        //log
        printf("[%s : %d] file => opened\n", base_name(__FILE__), __LINE__);

        
        
    }
    
    // readpng_init()
    int res_i = readpng_init(fp, &pWidth, &pHeight);
    
    //log
    printf("[%s : %d] res_i => %d\n", base_name(__FILE__), __LINE__, res_i);

    
    fclose(fp);
    
}

void _test_LibPNG()
{
    png_structp png_ptr;
    
    //log
    printf("[%s : %d] PNG_LIBPNG_VER_STRING => %s\n",
            base_name(__FILE__), __LINE__, PNG_LIBPNG_VER_STRING);
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    //log
    printf("[%s : %d] png_create_read_struct => done\n", base_name(__FILE__), __LINE__);

    
}