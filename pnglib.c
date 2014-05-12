#ifndef PNGLIB_H
#include "include/pnglib.h"
#endif

void show_message_png()
{
    
    //log
    printf("[%s : %d] pnglib\n", base_name(__FILE__), __LINE__);

    
}

int readpng_init(FILE *infile, ulg *pWidth, ulg *pHeight)
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

int png_sig_cmp
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
