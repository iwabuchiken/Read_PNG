#ifndef LIB_H
#include "include/lib.h"
#endif


char *get_FileSep_Str()
{
	char *sep = (char *) malloc (sizeof(char) * 2);

#ifdef _WIN32

	sep[0] = '\\';

	sep[1] = '\0';

//	printf("[%s:%d] sep => %s\n", __FILE__, __LINE__, sep);

	return sep;
//	return '\\';
#else
	sep[0] = '/';

	sep[1] = '\0';

//	printf("[%s:%d] sep => %s\n", __FILE__, __LINE__, sep);


	return sep;
//	return '/';
#endif

}

char* base_name(char* fullpath)
{
    char sep = get_FileSep();

    char *base = strrchr(fullpath, sep);

    if (base == NULL) {

	    return fullpath;

    }

    return base;

}

char* base_name_2(char* fullpath)
{
    char sep = get_FileSep();

    char *base = strrchr(fullpath, sep);

    if (base == NULL) {

	    return fullpath;

    }

    if (*base == '\\') {

	return (base + 1);
	
    } else {
	
	return base;
	
    }
    
//    return (base + 1);

}

char get_FileSep()
{
#ifdef _WIN32
	return '\\';
#else
	return '/';
#endif

}

#ifndef UBUNTU
int textcolor()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(std_con_out,&csbi);
    int a=csbi.wAttributes;
    return a%16;
}

int backcolor(void)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(std_con_out,&csbi);
    int a=csbi.wAttributes;
    return (a/16)%16;

}
#endif

#ifndef UBUNTU
void consolColor_Change(int backcol, int textcol)
//void change_ConsoleColors(int backcol, int textcol)
{
//	int backcol = 0x09;
//	int textcol = 0x0C;
    unsigned short wAttributes= ((unsigned)backcol<<4)|(unsigned)textcol;
	    SetConsoleTextAttribute(std_con_out, wAttributes);

}
#else
void consolColor_Change(char *color_code)
{
    printf("%s", color_code);
//    printf(color_code);
}
#endif


void consolColor_Init(void)
{
#ifndef UBUNTU
    console_textColor = textcolor();
//    console_textColor = 0x0E;
    console_backgroundColor = backcolor();
#endif
//    //log
//    printf("[%s:%d] color init => textcolor=%d, backcolor=%d\n",
//	    base_name(__FILE__), __LINE__,
//	    console_textColor,
//	    console_backgroundColor);

    
}

#ifndef UBUNTU
void consolColor_Reset(void)
{
//    //log
//    printf("[%s:%d] Reset color: text=%d back=%d\n",
//	    base_name(__FILE__), __LINE__, console_textColor, console_backgroundColor);

    
    consolColor_Change(console_backgroundColor, console_textColor);
}
#else
void consolColor_Reset(void)
{
    printf(RESETCOLOR);
}

#endif//#ifndef UBUNTU


/************************************
 * str_split_3
	(char* a_str, const char a_delim, int *num)

	@param
		num => Number of tokes obtained: for return purpose
************************************/
char** str_split_3
(char* a_str, const char a_delim, int *num)
{
	/************************************
	 * vars
	************************************/
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

//    //log
//    printf("[%s:%d] delim => %s\n", base_name(__FILE__), __LINE__, delim);

    
    char *a_str_new;

    char** result    = 0;

    //REF size_t http://stackoverflow.com/questions/1119370/where-do-i-find-the-definition-of-size-t answered Jul 13 '09 at 13:18
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;

    char* token;

    /************************************
     * operations
    ************************************/
//    //log
//    printf("[%s:%d] a_str = %s\n", base_name(__FILE__), __LINE__, a_str);

    
    a_str_new = (char *) malloc(sizeof(char) * (strlen(a_str) + 1));
//    a_str_new = malloc(sizeof(char) * (strlen(a_str) + 1));
    
    //log
    printf("[%s:%d] malloc => done for a_str_new (a_str=%s)\n",
	    base_name(__FILE__), __LINE__, a_str);

    if (a_str_new == NULL) {

    	//log
	    printf("[%s:%d] malloc => NULL\n", base_name(__FILE__), __LINE__);

	    exit(1);

    } else {

	    //log
	    printf("[%s:%d] malloc done for => a_str_new\n", base_name(__FILE__), __LINE__);


    }

    strcpy(a_str_new, a_str);

    //log
    printf("[%s : %d] strcpy => done\n", base_name(__FILE__), __LINE__);

    
    while (*tmp)
    {

	    if (a_delim == *tmp)
	    {
		    count++;
		    last_comma = tmp;

	    }

	    tmp++;

    }

    count += last_comma < (a_str + strlen(a_str) - 1);

    if (count < 1) {

	    (*num) = 0;

	    return NULL;
//		return 0;

    }

    //log
    printf("[%s : %d] count >= 1\n", base_name(__FILE__), __LINE__);

    
    // Input value to the param 'num'
    (*num) = count;
//	*num = count;

    count ++;



//	//log
//	printf("[%s:%d] count => %d\n", base_name(__FILE__), __LINE__, count);


    result = malloc(sizeof(char*) * count);

    if (result == NULL) {

    //log
	    printf("[%s:%d] malloc => NULL\n", base_name(__FILE__), __LINE__);

	    exit(1);

    }
    
    //log
    printf("[%s : %d] malloc => done\n", base_name(__FILE__), __LINE__);




    if (result)
    {

        size_t idx  = 0;
//
        token = strtok(a_str_new, delim);

        while (token)
        {

            assert(idx < count);

            *(result + idx++) = strdup(token);

//            //log
//			printf("[%s:%d] token => %s\n", base_name(__FILE__), __LINE__, token);


            token = strtok(0, delim);

        }

#ifndef UBUNTU
        assert(idx == count - 1);
#endif

        *(result + idx) = 0;

    }//if (result)

    //log
    printf("[%s : %d] tokenize => done\n", base_name(__FILE__), __LINE__);

    
//    if(result) {
//
//    	int i;
//
//    	for (i = 0; *(result + i); ++i) {
//
//    		//log
//			printf("[%s:%d] tokens[%d] => %s\n",
//					base_name(__FILE__), __LINE__, i, *(result + i));
//
//		}
//
//    }//if(result)

//    //log
//    while(*result) {
//
//    	//log
//		printf("[%s:%d] *result => %s\n", base_name(__FILE__), __LINE__, *result);
//
//		result ++;
//
//    }

    return result;

}//char** str_split(char* a_str, const char a_delim)

char* concat3(char *s1, char *s2, char *s3)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = strlen(s3);

    char *result = malloc(len1+len2+len3+1);//+1 for the zero-terminator

    if (result == NULL) {

    	//log
		printf("[%s:%d] malloc => NULL\n", base_name(__FILE__), __LINE__);

		exit(1);

	}

//    char *result = malloc(len1+len2+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2);
    memcpy(result+len1+len2, s3, len3+1);//+1 to copy the null-terminator
//    memcpy(result+len1, s2, len2+1);//+1 to copy the null-terminator

    return result;

}

char* dir_name(char* fullpath)
{

//REF http://stackoverflow.com/questions/12971499/how-to-get-the-file-separator-symbol-in-standard-c-c-or answered Oct 19 '12 at 9:43
#ifdef _WIN32
	char separator = '\\';
#else
	char separator = '/';
#endif

	//REF strrchr http://www.techonthenet.com/c_language/standard_library_functions/string_h/strrchr.php
	//REF basename http://stackoverflow.com/questions/5802191/use-gnu-versions-of-basename-and-dirname-in-c-source answered Apr 27 '11 at 13:30
	char *base = strrchr(fullpath, separator);
//	char *base = strrchr(fullpath, '\\');
//	char *base = strrchr(fullpath, '/');

	//log
//        printf("[%s:%d] fullpath = %s / separator = %c\n",
//		base_name(__FILE__), __LINE__, fullpath, separator);

	
	if (base == NULL) {
	    //log
	    printf("[%s:%d] base => NULL\n", base_name(__FILE__), __LINE__);
	    
//	    exit(-1);
	    return NULL;

	}

	
//	//log
//        printf("[%s:%d] base => %s\n", base_name(__FILE__), __LINE__, base);
	
	if (strlen(base) > 1) {
	    
//	    printf("[%s:%d] (base + 1) => %s\n",
//		    base_name(__FILE__), __LINE__, (base + 1));

	}
	
	int diff;

	char *dirname;

//	char separator;


//	printf("separator=%c\n", separator);

	//REF strlen http://www.programmingsimplified.com/c-program-find-string-length
//	printf("fullpath=%d(%s len=%d)\n", &fullpath, fullpath, strlen(fullpath));
//	printf("base=%d(%s len=%d)\n", &base, base, strlen(base));

//	printf("diff=%d\n", (&base - &fullpath));

	diff = strlen(fullpath) - strlen(base);

	// malloc
	//REF http://www.codingunit.com/c-tutorial-the-functions-malloc-and-free
	dirname = (char *) malloc (sizeof(char) * diff + 1);
//	dirname = (char *) malloc (sizeof(char) * diff);

	//REF memcpy http://stackoverflow.com/questions/4214314/get-a-substring-of-a-char answered Nov 18 '10 at 11:41
	memcpy(dirname, fullpath, diff);

	dirname[diff] = '\0';
//	dirname[diff - 1] = '\0';

	printf("dirname=%s\n", dirname);

//	char dname[strlen(dirname)];
//
//	memcpy(dname, dirname, strlen(dirname));
//
//	free(dirname);
//
//	return dname;
	return dirname;
//	return "ok";

}

/*******************************
  int dirExists(char *dpath)
 * @return 1 => dir exists
 *	    -1 => Unknown dir path
 *	    ENOENT => dir doesn't exist
 *******************************/
int dirExists(char *dpath)
//int dirExists(char *dpath)
{
	/************************************
	 * vars
	************************************/
	DIR* dir = opendir(dpath);

	int res;

	/************************************
	 * operations
	************************************/
	if (dir)
	{
	    /* Directory exists. */
	    closedir(dir);

	    res = 1;

	}
	else if (ENOENT == errno)
	{
	    /* Directory does not exist. */
	    res = ENOENT;

	}
	else
	{

	    /* opendir() failed for some other reason. */
	    res = -1;
		
	}

	return res;

}//enum RetVals dirExists(char *dpath)

/*******************************
 @return 1 => exists
 *	0   => doesn't 
 *******************************/
int fileExists(char *fpath)
{

    FILE *fp;

    if ( (fp = fopen( fpath, "r" ))==NULL ) {
	    //log
	    printf("[%s:%d] The file doesn't exist: %s\n",
//				base_name(__FILE__), __LINE__, fpath_stripped);
			    base_name(__FILE__), __LINE__, fpath);

	    return 0;

    } else {

	    fclose(fp);

	    return 1;

    }

}//enum RetVals fileExists(char *fpath)

/************************************
 * char ** str_split_r_2
 * @param
 * 		position		=> Split at the Xth delim from the right
 * 		num_of_tokens	=> Number of tokens obtained
 *
 * @return NULL => delim not found in string
************************************/
char ** str_split_r_2
(char *string, char delim, int position, int *num_of_tokens)
{
	char **result;

	char *bottom = strrchr(string, delim);

	//log
	printf("[%s:%d] bottom => %s\n", base_name(__FILE__), __LINE__, bottom);

	/************************************
	 * If strrchr returns a NULL pointer
	 * 	=> return NULL
	************************************/
	if (bottom == NULL) {

		return NULL;

	}

	/************************************
	 * malloc
	************************************/
	result = malloc(sizeof(char*) * 2);

	/************************************
	 * diff
	************************************/
	int dif = bottom - string;

	//log
	printf("[%s:%d] dif => %d\n", base_name(__FILE__), __LINE__, dif);

	/************************************
	 * first token
	************************************/
	char *token_1 = malloc(sizeof(char) * (dif + 1));

	strncpy(token_1, string, dif);
	*(token_1 + dif) = '\0';

	//log
	printf("[%s:%d] token_1 => %s\n", base_name(__FILE__), __LINE__, token_1);

	/************************************
	 * Build: tokens
	************************************/
	*(result) = strdup(token_1);
	*(result + 1) = strdup(bottom + 1);

        //log
    printf("[%s : %d] result => prepared\n", base_name(__FILE__), __LINE__);


//		return string;
	return result;

}//char ** str_split_r_2

/************************************
 * REF concat() http://stackoverflow.com/questions/8465006/how-to-concatenate-2-strings-in-c answered Dec 11 '11 at 15:20
************************************/
char* concat(char *s1, char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = malloc(len1+len2+1);//+1 for the zero-terminator

    if (result == NULL) {

    	//log
		printf("[%s:%d] malloc => NULL\n", base_name(__FILE__), __LINE__);

		exit(1);

	}


    //in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);//+1 to copy the null-terminator
    return result;
}

char get_FileSeparator()
{
#ifdef _WIN32
	return '\\';
#else
	return '/';
#endif

}
