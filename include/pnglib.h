/* 
 * File:   pnglib.h
 * Author: iwabuchik
 *
 * Created on May 11, 2014, 12:42 AM
 */

#ifndef PNGLIB_H
#define	PNGLIB_H
//#endif

#ifndef LIB_H
#include "lib.h"
#endif

#include <zlib.h>

typedef unsigned char   uch;  // readpng.h
typedef unsigned short  ush;  // readpng.h
typedef unsigned long   ulg;  // readpng.h

typedef unsigned char png_byte;  // png.h
typedef const png_byte        * png_const_bytep;  // png.h
typedef size_t png_size_t;  // png.h

#define PNG_LIBPNG_VER_STRING "1.6.10"  // png.h

#ifdef	__cplusplus
extern "C" {
#endif

    void show_message_png(void);
    
    int readpng_init(FILE *, ulg *, ulg *);
    
    int png_sig_cmp
    (png_const_bytep, png_size_t, png_size_t);


#ifdef	__cplusplus
}
#endif

#endif	/* PNGLIB_H */

