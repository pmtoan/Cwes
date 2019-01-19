#ifndef __C_MODULES_UTILITIES_FILES_H__
#define __C_MODULES_UTILITIES_FILES_H__

#include "types.h"
#include "bytes.h"
#include "strings.h"

/*----------------------------------------------------------------*/
unsigned long FILE_sizeof(const char* path);
char* FILE_read_text(const char* path);
void FILE_write_text(const char* path, char* buffer);
BYTES FILE_read_bin(const char* path);
void FILE_write_bin(const char* path, BYTES buffer);
char* FILE_get_extension(const char* path);
/*----------------------------------------------------------------*/

unsigned long FILE_sizeof(const char* path)
{
    /*
     *  todo @FILE_sizeof get size of @path
     *  if @path is not a file, return -1
    */
    FILE* fp = fopen(path, "r");
    if (fp == NULL) return -1;
    fseek(fp, 0L, SEEK_END);
    unsigned long fs = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    fclose(fp);
    return fs;
}

char* FILE_read_text(const char* path)
{
    /*
     *  todo @FILE_read_text read all text from @path
     *  if @path is not found, return NULL
    */
    FILE* fp = fopen(path, "r");
    if (fp == NULL) return NULL;
    int fs = FILE_sizeof(path);
    char* buffer = (char*)malloc(fs + 1);
    fread(buffer, fs, 1, fp);
    buffer[fs] = '\0';
    fclose(fp);
    return buffer;
}

void FILE_write_text(const char* path, char* buffer)
{
    /*
    *  todo @FILE_write_text write @buffer to @path
    */
    FILE* fp = fopen(path, "w");
    if (fp == NULL) return;
    fwrite(buffer, strlen(buffer), 1, fp);
    fclose(fp);
}

BYTES FILE_read_bin(const char* path)
{
    BYTES bytes = BYTES_init();
    BYTES_read_file(&bytes, path);
    return bytes;
}

void FILE_write_bin(const char* path, BYTES buffer)
{
    BYTES_write_file(buffer, path);
    return;
}

char* FILE_get_extension(const char* path)
{
    /*
     *  todo @FILE_get_extension extension of a file
     *  usage:
     *      char* FILE_get_extension("hello.txt") -> txt
    */
    if (STRING_count_cha(path, '.') == 0) return "";
    char* ext = strdup(path);
    while(STRING_count_cha(ext, '.') > 0)
        ext = STRING_cut(ext, '.');
    return ext;
}

#endif // __C_MODULES_UTILITIES_FILES_H__