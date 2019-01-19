#ifndef __C_MODULES_UTILITIES_TYPES_H__
#define __C_MODULES_UTILITIES_TYPES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _ printf

#define __SIZE_TINY__   32
#define __SIZE_SMALL__  512
#define __SIZE_LARGE__  1024
#define __SIZE_EXTRA__  1024<<10

/* --- pair data structure --- */
typedef struct PAIR
{
    char* key;
    char* value;
    struct PAIR* next;
}PAIR;

typedef struct LIST_PAIR
{
    /*
    *  @LIST_PAIR a single link list of PAIR
    */
    int len;
    PAIR* head;
}LIST_PAIR;


/* --- string list data structure --- */
typedef struct STRING
{
    int len;
    char* value;
    struct STRING* next;
}STRING;

typedef struct LIST_STRING
{
    /*
    *  @LIST_STRING a single link list of STRING
    */
    int len;
    STRING* head;
}LIST_STRING;


/* --- bytes data structure --- */
typedef struct BYTES
{
    int len;    // length of array
    char* buffer; // bytes buffer
}BYTES;



#endif // __C_MODULES_UTILITIES_TYPES_H__