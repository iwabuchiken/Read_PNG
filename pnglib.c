#ifndef PNGLIB_H
#include "include/pnglib.h"
#include "include/pnginfo.h"
#endif

void show_message_png()
{
    
    //log
    printf("[%s : %d] pnglib\n", base_name(__FILE__), __LINE__);

    
}

int lib_readpng_init(FILE *infile, ulg *pWidth, ulg *pHeight)
{

    uch sig[8];


    /* first do a quick check that the file really is a PNG image; could
     * have used slightly more general png_sig_cmp() function instead */

    fread(sig, 1, 8, infile);
    
    //log
    printf("[%s : %d] sig => %s\n", base_name(__FILE__), __LINE__, sig);

    int res_i = png_sig_cmp(sig, 0, 8);
    
    //log
    printf("[%s : %d] png_sig_cmp => %d\n", base_name(__FILE__), __LINE__, res_i);

    
    if (res_i)
//    if (png_sig_cmp(sig, 0, 8))
        return 1;   /* bad signature */

    
    
    return 0;
    
}

int lib_png_sig_cmp
(png_const_bytep sig, png_size_t start, png_size_t num_to_check)
{
   png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};

   if (num_to_check > 8)
      num_to_check = 8;

   else if (num_to_check < 1)
      return (-1);

   if (start > 7)
      return (-1);

   if (start + num_to_check > 8)
      num_to_check = 8 - start;

//   //test
//   int i;
//   
//   for (i = 0; i < num_to_check; i++) {
//
//       //log
//        printf("[%s : %d] sig[%d] => %d (%%c=%c) / png_signature[%d] => %d\n", 
//                base_name(__FILE__), __LINE__, i, sig[i], sig[i], i, png_signature[i]);
//
//    }

   
   return ((int)(memcmp(&sig[start], &png_signature[start], num_to_check)));
}
//
/*************************************
void abort_(const char * s, ...)
 *  
 * message
 * REF http://zarb.org/~gc/html/libpng.html
 
 **************************************/
void abort_(const char * s, ...)
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}
//
///*************************************
// * void read_png_file(char* file_name)
// *  
// * REF http://zarb.org/~gc/html/libpng.html
// 
// **************************************/
//void read_png_file
//(char* file_name, png_structp png_ptr,
//        png_infop info_ptr, png_bytep * row_pointers,
//        int *number_of_passes, int *width, int *height,
//        png_byte *color_type, png_byte *bit_depth)
//{
//        char header[8];    // 8 is the maximum size that can be checked
//
//        int x, y;
//        
//        /* open file and test for it being a png */
//        FILE *fp = fopen(file_name, "rb");
//        if (!fp)
//                abort_("[read_png_file] File %s could not be opened for reading", file_name);
//        fread(header, 1, 8, fp);
//        if (png_sig_cmp(header, 0, 8))
//                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
//
//
//        /* initialize stuff */
//        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//        if (!png_ptr)
//                abort_("[read_png_file] png_create_read_struct failed");
//
//        info_ptr = png_create_info_struct(png_ptr);
//        if (!info_ptr)
//                abort_("[read_png_file] png_create_info_struct failed");
//
//        if (setjmp(png_jmpbuf(png_ptr)))
//                abort_("[read_png_file] Error during init_io");
//
//        png_init_io(png_ptr, fp);
//        png_set_sig_bytes(png_ptr, 8);
//
//        png_read_info(png_ptr, info_ptr);
//
//        *width = png_get_image_width(png_ptr, info_ptr);
//        *height = png_get_image_height(png_ptr, info_ptr);
//        *color_type = png_get_color_type(png_ptr, info_ptr);
//        *bit_depth = png_get_bit_depth(png_ptr, info_ptr);
////        width = png_get_image_width(png_ptr, info_ptr);
////        height = png_get_image_height(png_ptr, info_ptr);
////        color_type = png_get_color_type(png_ptr, info_ptr);
////        bit_depth = png_get_bit_depth(png_ptr, info_ptr);
//
//        *number_of_passes = png_set_interlace_handling(png_ptr);
////        number_of_passes = png_set_interlace_handling(png_ptr);
//        png_read_update_info(png_ptr, info_ptr);
//
//
//        /* read file */
//        if (setjmp(png_jmpbuf(png_ptr)))
//                abort_("[read_png_file] Error during read_image");
//
//        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * (*height));
////        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
//        for (y=0; y < *height; y++)
////        for (y=0; y<height; y++)
//                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
//
//        png_read_image(png_ptr, row_pointers);
//
//        fclose(fp);
//}
//
///*************************************
// *  void write_png_file()
// * 
// * char* file_name      => dst fine name
// * png_structp png_ptr  => empty pnt pointer
// * png_infop info_ptr   => empty info pointer
// * png_bytep * row_pointers     => value-carrying row pointers
// * int *height          => height of the png image
// 
// **************************************/
//
//void write_png_file
//(char* file_name, png_structp png_ptr,
//    png_infop info_ptr, png_bytep * row_pointers,
//    int *width, int *height,
//    png_byte *color_type, png_byte *bit_depth)
//{
//    int y;
//    
//    //log
//    printf("[%s : %d] row_pointers[0][0] => %d\n",
//            base_name(__FILE__), __LINE__, row_pointers[0][0]);
//
//    
//    /* create file */
//    FILE *fp = fopen(file_name, "wb");
//    if (!fp)
//            abort_("[write_png_file] File %s could not be opened for writing", file_name);
//
//    //log
//    printf("[%s : %d] file => opened: %s\n", base_name(__FILE__), __LINE__, file_name);
//
//
//    /* initialize stuff */
//    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//
//    if (!png_ptr)
//            abort_("[write_png_file] png_create_write_struct failed");
//
//    //log
//    printf("[%s : %d] png_ptr => created\n", base_name(__FILE__), __LINE__);
//
//    
//    info_ptr = png_create_info_struct(png_ptr);
//    if (!info_ptr)
//            abort_("[write_png_file] png_create_info_struct failed");
//
//    if (setjmp(png_jmpbuf(png_ptr)))
//            abort_("[write_png_file] Error during init_io");
//
//    //log
//    printf("[%s : %d] png_create_info_struct => done\n", base_name(__FILE__), __LINE__);
//
//    
//    png_init_io(png_ptr, fp);
//
//    //log
//    printf("[%s : %d] png_init_io => done\n", base_name(__FILE__), __LINE__);
//
//
//    /* write header */
//    if (setjmp(png_jmpbuf(png_ptr)))
//            abort_("[write_png_file] Error during writing header");
//
//    png_set_IHDR(png_ptr, info_ptr, *width, *height,
//                 *bit_depth, *color_type, PNG_INTERLACE_NONE,
//                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
//
//    //log
//    printf("[%s : %d] png_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->height);
//    
//    printf("[%s : %d] info_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, info_ptr->height);
//
//    
//    //log
//    printf("[%s : %d] png_set_IHDR => done\n", base_name(__FILE__), __LINE__);
//
//    
//    png_write_info(png_ptr, info_ptr);
//
//    //log
//    printf("[%s : %d] png_write_info => done\n", base_name(__FILE__), __LINE__);
////
//    //log
//    printf("[%s : %d] png_ptr->height => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->height);
//    printf("[%s : %d] png_ptr->width => %d\n",
//            base_name(__FILE__), __LINE__, png_ptr->width);
////
////    /* write bytes */
////    if (setjmp(png_jmpbuf(png_ptr)))
////            abort_("[write_png_file] Error during writing bytes");
////
////    png_write_image(png_ptr, row_pointers);
////
////    //log
////    printf("[%s : %d] png_write_image => done\n", base_name(__FILE__), __LINE__);
////
////
////    /* end write */
////    if (setjmp(png_jmpbuf(png_ptr)))
////            abort_("[write_png_file] Error during end of write");
//
////    png_write_end(png_ptr, NULL);
//
//    /* cleanup heap allocation */
//    for (y=0; y < *height; y++)
////    for (y=0; y<height; y++)
//            free(row_pointers[y]);
//    free(row_pointers);
//
//    fclose(fp);
//}//void write_png_file()
