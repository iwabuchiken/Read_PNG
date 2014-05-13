/* 
 * File:   main.c
 * Author: iwabuchik
 *
 * Created on May 11, 2014, 12:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#ifndef PNGLIB_H
#include "include/pnglib.h"
#include "include/pnginfo.h"
#endif

//#include <png.h>

//#include <allegro.h>

void _test_ReadPNG(void);
void _test_LibPNG(void);
void _test_ReadPNG_Simple(void);
void _test_ReadPNG_Simple_v2(void);
void _test_ReadPNG_Simple_v3(void);

//void abort_(const char *, ...);

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void read_png_file(char* file_name)
{
        char header[8];    // 8 is the maximum size that can be checked

        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
        

        /* initialize stuff */
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[read_png_file] png_create_read_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[read_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        width = png_get_image_width(png_ptr, info_ptr);
        height = png_get_image_height(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (y=0; y<height; y++)
                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);

        fclose(fp);
}


void write_png_file(char* file_name)
{
        /* create file */
        FILE *fp = fopen(file_name, "wb");
        if (!fp)
                abort_("[write_png_file] File %s could not be opened for writing", file_name);


        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[write_png_file] png_create_write_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[write_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during init_io");

        png_init_io(png_ptr, fp);


        /* write header */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing header");

        png_set_IHDR(png_ptr, info_ptr, width, height,
                     bit_depth, color_type, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);


        /* write bytes */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing bytes");

        png_write_image(png_ptr, row_pointers);


        /* end write */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during end of write");

        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
        for (y=0; y<height; y++)
                free(row_pointers[y]);
        free(row_pointers);

        fclose(fp);
}


void process_file(void)
{
//        if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
//                abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
//                       "(lacks the alpha channel)");
//
//        if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
//                abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
//                       PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));
        
        for (y=0; y<height; y++) {
                png_byte* row = row_pointers[y];
                for (x=0; x<width; x++) {
                        png_byte* ptr = &(row[x*3]);
//                        printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d\n",
//                               x, y, ptr[0], ptr[1], ptr[2]);
//                        png_byte* ptr = &(row[x*4]);
//                        printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
//                               x, y, ptr[0], ptr[1], ptr[2], ptr[3]);

                        /* set red value to 0 and green value to the blue one */
//                        ptr[0] = 0;
//                        ptr[1] = ptr[2];
                        ptr[0] = 0;
                        ptr[1] = 0;
                        ptr[2] = 255 - ptr[2];
//                        ptr[1] = 255 - ptr[0];
//                        ptr[2] = 255 - ptr[0];
//                        ptr[1] = ptr[2];
                }
        }//for (y=0; y<height; y++)
        
        //log
    printf("[%s : %d] processing => done\n", base_name(__FILE__), __LINE__);

}


int main(int argc, char **argv)
{
        if (argc != 3)
                abort_("Usage: program_name <file_in> <file_out>");

        read_png_file(argv[1]);
        
        //log
        printf("[%s : %d] png_ptr->color_type = %d\n",
            base_name(__FILE__), __LINE__, png_ptr->color_type);
        
//        //log
//        printf("[%s : %d] png_ptr->color_type = %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->);

        //log
        printf("[%s : %d] PNG_COLOR_TYPE_RGB = %d\n",
            base_name(__FILE__), __LINE__, PNG_COLOR_TYPE_RGB);
        
        //log
        printf("[%s : %d] PNG_COLOR_TYPE_RGBA = %d\n",
            base_name(__FILE__), __LINE__, PNG_COLOR_TYPE_RGBA);

        
        process_file();
        write_png_file(argv[2]);

        return 0;
}




/*
 * 
 */
//int main(int argc, char** argv) {
//
//    printf("yes\n");
//    
////    _test_LibPNG();
////    
////    show_message_png();
////    
////    _test_ReadPNG();
////    _test_ReadPNG_Simple();
//    
//    _test_ReadPNG_Simple_v2();
////    _test_ReadPNG_Simple_v3();
//    
//    
//    
//    //log
//    printf("[%s : %d] done\n", base_name(__FILE__), __LINE__);
//
//    return (EXIT_SUCCESS);
//}


//
//void _test_ReadPNG(void)
//{
//
//    png_infop info_ptr;
//    
//    FILE *fp;
//    
//    ulg pWidth, pHeight;
//    
//    char *fname_src = "/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images/080f921b_PutumayoPresents_LatinJazz.png";
//    
//    fp = fopen(fname_src, "rb");
//    
//    if(fp == NULL) {
//        
//        //log
//        printf("[%s : %d] fp => NULL\n", base_name(__FILE__), __LINE__);
//        
//        exit(1);
//
//    } else {
//        
//        //log
//        printf("[%s : %d] file => opened\n", base_name(__FILE__), __LINE__);
//
//        
//        
//    }
//    
//    // readpng_init()
//    int res_i = readpng_init(fp, &pWidth, &pHeight);
//    
//    //log
//    printf("[%s : %d] res_i => %d\n", base_name(__FILE__), __LINE__, res_i);
//
//    
//    fclose(fp);
//    
//}
//
//void _test_LibPNG()
//{
//    png_structp png_ptr;
//    
//    //log
//    printf("[%s : %d] PNG_LIBPNG_VER_STRING => %s\n",
//            base_name(__FILE__), __LINE__, PNG_LIBPNG_VER_STRING);
//    
//    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//    
//    //log
//    printf("[%s : %d] png_create_read_struct => done\n", base_name(__FILE__), __LINE__);
//
//    
//}
//
//void _test_ReadPNG_Simple()
//{
//    int x, y;
//
//    int width, height;
//    png_byte color_type;  // typedef unsigned char : pngconf.h
//    png_byte bit_depth;
//
//    png_structp png_ptr;
//    png_infop info_ptr;
//    int number_of_passes;
//    png_bytep * row_pointers;
//    
//    //log
//    printf("[%s : %d] Starts => _test_ReadPNG_Simple()\n", base_name(__FILE__), __LINE__);
//
//    char header[8];    // 8 is the maximum size that can be checked
//    
////    char *fname_src = "/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images/080f921b_PutumayoPresents_LatinJazz.png";
//    char *fname_src = "/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images/download-jpg.png";
//
//    /* open file and test for it being a png */
//    FILE *fp = fopen(fname_src, "rb");
//    if (!fp)
//        abort_("[read_png_file] File %s could not be opened for reading", fname_src);
//    fread(header, 1, 8, fp);
//    
//    if (png_sig_cmp(header, 0, 8))
//            abort_("[read_png_file] File %s is not recognized as a PNG file", fname_src);
//    
//    //log
//    printf("[%s : %d] png_sig_cmp() => done\n", base_name(__FILE__), __LINE__);
//
//    /* initialize stuff */
//    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//    if (!png_ptr)
//            abort_("[read_png_file] png_create_read_struct failed");
//
//    info_ptr = png_create_info_struct(png_ptr);
//    
//    if (!info_ptr)
//            abort_("[read_png_file] png_create_info_struct failed");
//
//    if (setjmp(png_jmpbuf(png_ptr)))
//            abort_("[read_png_file] Error during init_io");
//    
//    png_init_io(png_ptr, fp);
//    
//    //log
//    printf("[%s : %d] png_init_io() => done\n", base_name(__FILE__), __LINE__);
//
//    //log
//    printf("[%s : %d] png_ptr.pixel_depth => %d\n", 
////            base_name(__FILE__), __LINE__, png_ptr.pixel_depth);
////            base_name(__FILE__), __LINE__, png_ptr->);
//            base_name(__FILE__), __LINE__, png_ptr->pixel_depth);
//    
//    png_set_sig_bytes(png_ptr, 8);
//    
//    //log
//    printf("[%s : %d] png_set_sig_bytes() => done\n", base_name(__FILE__), __LINE__);
//
//    png_read_info(png_ptr, info_ptr);
//    
//    //log
//    printf("[%s : %d] png_read_info() => done\n", base_name(__FILE__), __LINE__);
//
//    //log
//    printf("[%s : %d] info_ptr->height => %d\n", base_name(__FILE__), __LINE__, info_ptr->height);
//
//    
//    width = png_get_image_width(png_ptr, info_ptr);
//    
//    //log
//    printf("[%s : %d] width => %d\n", base_name(__FILE__), __LINE__, width);
////    printf("[%s : %d] width => %d\n", base_name(__FILE__), __LINE__, info_ptr->height);
//
//    width = png_get_image_width(png_ptr, info_ptr);
//    height = png_get_image_height(png_ptr, info_ptr);
//    color_type = png_get_color_type(png_ptr, info_ptr);
//    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
//    
//    number_of_passes = png_set_interlace_handling(png_ptr);
//    png_read_update_info(png_ptr, info_ptr);
//    
//    //log
//    printf("[%s : %d] number_of_passes => %d\n", base_name(__FILE__), __LINE__, number_of_passes);
//
//    /* read file */
//    if (setjmp(png_jmpbuf(png_ptr)))
//            abort_("[read_png_file] Error during read_image");
//
//    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
//    
//    for (y=0; y<height; y++)
//            row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
//
//    png_read_image(png_ptr, row_pointers);
//    
//    //log
//    printf("[%s : %d] png_read_image() => done\n", base_name(__FILE__), __LINE__);
//
//    //log
//    int i;
//    for(i = 0; i < 20; i++) {
//        
//        printf("[%s : %d] row_pointers[0][%d] => %d\n",
//                base_name(__FILE__), __LINE__, i, row_pointers[0][i]);
//        
//    }
//
//    
//    
////    //log
////    printf("[%s : %d] *row_pointers => %c(%%c)\n",
//////    printf("[%s : %d] row_pointers[0] => %d\n",
////            base_name(__FILE__), __LINE__, *row_pointers);
////            base_name(__FILE__), __LINE__, (int) row_pointers[0]);
//    //log
////    printf("[%s : %d] *row_pointers => %d(%%d)\n",
//////    printf("[%s : %d] row_pointers[0] => %d\n",
////            base_name(__FILE__), __LINE__, row_pointers[0]);
////            base_name(__FILE__), __LINE__, (int) row_pointers[0]);
//    //log
////    printf("[%s : %d] row_pointers[10] => %c(%%d = %d)\n",
////            base_name(__FILE__), __LINE__, row_pointers[10], row_pointers[10]);
//    //log
////    printf("[%s : %d] *(row_pointers + 10) => %c(%%d = %d)\n",
////            base_name(__FILE__), __LINE__, *(row_pointers + 10), *(row_pointers + 10));
//
//    
//
//    /*************************************
// 
//     * close file
// 
//     **************************************/
//    fclose(fp);
//    
//}
//
////void abort_(const char * s, ...)
////{
////        va_list args;
////        va_start(args, s);
////        vfprintf(stderr, s, args);
////        fprintf(stderr, "\n");
////        va_end(args);
////        abort();
////}
//
//
//void _test_ReadPNG_Simple_v2(void)
//{
//    int width, height;
//    png_byte color_type;  // typedef unsigned char : pngconf.h
//    png_byte bit_depth;
//
//    png_structp png_ptr;
//    png_infop info_ptr;
//    int number_of_passes;
//    png_bytep * row_pointers;
//    
//    char *fname_src = "/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images/download-jpg.png";
//    char *fname_dst = "/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images/copy.png";
////    char *fname_dst = "/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images/download-jpg.copy.png";
//
//    //log
//    printf("[%s : %d] Starts => _test_ReadPNG_Simple_v2()\n", base_name(__FILE__), __LINE__);
//
//    
//    read_png_file
//    (fname_src, png_ptr, info_ptr, row_pointers,
//        &number_of_passes, &width, &height,
//        &color_type, &bit_depth);
//        
//    //log
//    printf("[%s : %d] height => %d\n", base_name(__FILE__), __LINE__, height);
//
//    //test
//    int i;
//    
//    for(i = 0; i < 10; i++) {
//        
//        //log
//        printf("[%s : %d] row_pointers[0][%d] = %d\n", 
//                base_name(__FILE__), __LINE__, i, row_pointers[0][i]);
//
//    }
//    
//    /*************************************
// 
//     * Write png
// 
//     **************************************/
//    png_structp png_ptr_2;
//    png_infop info_ptr_2;
//    
//    write_png_file
//    (fname_dst, png_ptr_2, info_ptr_2, row_pointers,
//        &width, &height, &color_type, &bit_depth);
//    
//    //log
//    printf("[%s : %d] write_png_file() => done\n", base_name(__FILE__), __LINE__);
//
//}
//
//void _test_ReadPNG_Simple_v3()
//{
//    char *fname_dst = "/home/iwabuchik/WORKS/WS/WS_Prog/Read_PNG/images/copy.png";
//    
//    FILE *fp = fopen(fname_dst, "wb");
////    FILE *fp = fopen("test.png", "wb");
//    if (!fp) {
//      fprintf(stderr, "Cannot open %s.\n", fname_dst);
////      fprintf(stderr, "Cannot open %s.\n", "test.png");
//      return;
////      return 1;
//    }
//
//    png_voidp user_error_ptr;
//    png_error_ptr user_error_fn, user_warning_fn;
//    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, user_error_ptr, user_error_fn, user_warning_fn);
//    if (!png_ptr) return;
////    if (!png_ptr) return 1;
//
//    png_infop info_ptr = png_create_info_struct(png_ptr);
//    if (!info_ptr) {
//       png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
//       return;
////       return 1;
//    }
//
//    png_init_io(png_ptr, fp);
//                                  // w h depth
////    png_set_IHDR(png_ptr, info_ptr, 1, 1, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
//    png_set_IHDR(png_ptr, info_ptr, 1, 1, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
//
//    png_write_info(png_ptr, info_ptr);
//    
//    png_byte px[4] = {0x30, 0x20, 0x10, 0xff};
//    png_byte *row_pointers[1];
//    row_pointers[0] = (png_byte *) px;
//    //Write the image data.
//    png_write_image(png_ptr, row_pointers);
//
//    png_write_end(png_ptr, info_ptr);
//
//    png_destroy_write_struct(&png_ptr, &info_ptr);
//    fclose(fp);
//
//    //log
//    printf("[%s : %d] _test_ReadPNG_Simple_v3() => done\n", base_name(__FILE__), __LINE__);
//
//}
