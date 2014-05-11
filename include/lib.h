/* 
 * File:   lib.h
 * Author: IwabuchiK
 *
 * Created on 2014/05/06, 13:26
 */

#define UBUNTU

#ifndef LIB_H
#define	LIB_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef UBUNTU//---------------------------
#ifndef WIN_H
#define WIN_H
#include <windows.h>
#define std_con_out GetStdHandle(STD_OUTPUT_HANDLE)
#endif//#ifndef WIN_H

#else//#ifndef UBUNTU
    
#define RED  "\033[22;31m"
#define GREEN  "\033[22;32m"
#define RESETCOLOR "\033[0m"

    
#endif//#ifndef UBUNTU//---------------------------

#ifndef ASSERT_H
#define ASSERT_H
#include <assert.h>
#endif

#ifndef TYPES_H
#define TYPES_H
#include <sys/types.h>
#endif
    
#ifndef STAT_H
#define STAT_H
#include <sys/stat.h>
#endif
    
#ifndef UNISTD_H
#define UNISTD_H
#include <unistd.h>
#endif

#ifndef DIRENT_H
#define DIRENT_H
#include <dirent.h>
#endif

//REF http://www.gnu.org/software/libc/manual/html_node/Error-Codes.html
#ifndef ERRNO_H
#define ERRNO_H
#include <errno.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif
    
#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif
    
#ifndef STRING_H
#define STRING_H
#include <string.h>
#endif

    
///////////////////////////////////////////////////////

// Global variables

///////////////////////////////////////////////////////
//unsigned short int console_textColor = -1;
//unsigned short int console_backgroundColor = -1;
	// C:/WORKS/WS/WS_Android_20130929_122122/IP/main.c:26: multiple definition of `console_textColor'
	//build/Debug/MinGW-Windows/lib.o(.data+0x0):C:/WORKS/WS/WS_Android_20130929_122122/IP/lib.c:7: first defined here
	//build/Debug/MinGW-Windows/main.o(.data+0x2): In function `main':
unsigned short int console_textColor;
unsigned short int console_backgroundColor;

///////////////////////////////////////////////////////

// Enum

///////////////////////////////////////////////////////
//enum concol
typedef enum
{
	black=0,
	dark_blue=1,
	dark_green=2,
	dark_aqua,dark_cyan=3,
	dark_red=4,
	dark_purple=5,dark_pink=5,dark_magenta=5,
	dark_yellow=6,
	dark_white=7,
	gray_color=8,
	blue=9,
	green=10,
	aqua=11,cyan=11,
	red=12,
	purple=13,pink=13,magenta=13,
	yellow=14,
	white=15
} concol;

//enum RetVals {
typedef enum
{


	DirDoesntExist = 0, DirExists, UnknownDir,

	DirCreated, CreateDirFailed,

	// file
	FileDoesntExist, FileExists, UnknownFile,

	// PGM
	Format_NotP5, Header_Obtained, PGM_Obtained,

	PGM_GRAYS_WRITTEN,
	PGM_WRITTEN,

	// PPM
	Format_NotP3, PPM_Obtained, PPM_NotObtained, PPM_WRITTEN,
	Format_NotP3NotP6,

	// get_Filename_2
	FileName_Obtained,

	// conversion
	Conv_PPM2PGM_Done, Conv_PGM2PPM_Done,

	// generics
	Ret_OK, Ret_Error

} RetVals;

///////////////////////////////////////////////////////

// Prototypes

///////////////////////////////////////////////////////
char *get_FileSep_Str(void);
char* base_name(char*);	    // abc\def.txt ==> \def.txt
char* base_name_2(char*);   // abc\def.txt ==> def.txt (No separator)

char get_FileSep(void);

int textcolor(void);
int backcolor(void);

#ifndef UBUNTU
void consolColor_Change(int, int);
#else
void consolColor_Change(char *);
#endif//#ifndef UBUNTU


void consolColor_Init(void);
void consolColor_Reset(void);

char** str_split_3(char*, const char, int*);

char* concat3(char *s1, char *s2, char *s3);

char* dir_name(char*);

int dirExists(char *);

int fileExists(char *);

char ** str_split_r_2(char *, char, int, int *);

char* concat(char *, char *);

#ifdef	__cplusplus
}
#endif

#endif	/* LIB_H */

