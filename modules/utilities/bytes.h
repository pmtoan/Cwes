#ifndef __C_MODULES_UTILITIES_BYTES_H__
#define __C_MODULES_UTILITIES_BYTES_H__

#include "types.h"

/*----------------------------------------------------------------*/
BYTES BYTES_init();
void BYTES_free(BYTES* bytes);
void BYTES_print(BYTES bytes);
void BYTES_print_d(BYTES bytes);
void BYTES_print_x(BYTES bytes);
int BYTES_read_file(BYTES* buffer, const char* path);
int BYTES_write_file(BYTES buffer, const char* path);
/*----------------------------------------------------------------*/

BYTES BYTES_init()
{
    BYTES bytes;
    bytes.len = 0;
    bytes.buffer = NULL;
    return bytes;
}

void BYTES_free(BYTES* bytes)
{
    free(bytes->buffer);
}

void BYTES_print(BYTES bytes)
{
    BYTES_print_x(bytes);
}

void BYTES_print_d(BYTES bytes)
{
    for (int i = 0; i < bytes.len; ++i)
    {
        if((i != 0) && (i % 10 == 0))
            printf("\n");
        printf("%03d ", bytes.buffer[i]);
    }
    printf("\n");
}

void BYTES_print_x(BYTES bytes)
{
    for (int i = 0; i < bytes.len; ++i)
    {
        if((i != 0) && (i % 10 == 0))
            printf("\n");
        printf("%02x ", bytes.buffer[i]);
    }
    printf("\n");
}

int BYTES_read_file(BYTES* buffer, const char* path)
{
    FILE* fp = fopen(path, "rb");
    if (fp == 0) return 0;
    fseek(fp, 0L, SEEK_END);
    int fs = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    buffer->len = fs;
    buffer->buffer = (char*)malloc(fs);
    fread(buffer->buffer, fs, 1, fp);
    fclose(fp);
    return fs;
}

int BYTES_write_file(BYTES buffer, const char* path)
{
    FILE* fp = fopen(path, "wb");
    if (fp == 0) return 0;
    fwrite(buffer.buffer, buffer.len, 1, fp);
    fclose(fp);
    return buffer.len;
}

#endif // __C_MODULES_UTILITIES_BYTES_H__