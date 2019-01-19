#ifndef __C_MODULES_UTILITIES_STRINGS_H__
#define __C_MODULES_UTILITIES_STRINGS_H__

#include "types.h"

/*----------------------------------------------------------------*/
char* STRING_timestamp();
int STRING_count_cha(const char* string, char character);
int STRING_count_str(const char* string, const char* substr);
char* STRING_replace(const char* string, const char* substr, const char* replacement);
char* STRING_shift(const char* string, int byte);
char* STRING_cut(const char* string, char to);
char* STRING_extract(const char* string, char to);
char** STRING_split(const char* string, const char* delimiter, int times);
/*----------------------------------------------------------------*/






char* STRING_timestamp()
{
    /*
     *	todo @STRING_timestamp get current date time and build up a ctime string format
     *	ctime string format: "Sat Jan  5 17:39:45 2019"
    */
	time_t ltime; /* calendar time */
    ltime = time(NULL); /* get current cal time */
    return STRING_replace(asctime(localtime(&ltime)), "\n", "");
}

int STRING_count_cha(const char* string, char character)
{
    /*
     *	todo @STRING_count_cha count how many @character in @string
    */
    int count = 0;
    for (int i = 0; i < strlen(string); ++i)
        if (string[i] == character)
            count++;
    return count;
}

int STRING_count_str(const char* string, const char* substr)
{
    /*
     *   todo @STRING_count_str count how many @substr in @string
    */
    int count = 0;
    for(int i=0;string[i]!='\0';i++)
    {
        if (string[i] == substr[0])
        {
            int j = 0;
            for(j=0;substr[j]!='\0';j++)
            {
                if (string[i+j] != substr[j])
                    break;
            }
            if (substr[j] == '\0')
                count++;
        }
    }
    return count;
}

char* STRING_replace(const char* string, const char* substr, const char* replacement)
{
    /*
     *	todo @STRING_replace replace @substr with @replacement in @string
     *	usage
     *	    char* msg = STRING_replace("hello you", "you", "adam")
     *	    --->    msg = "hello adam"
    */
    char* tok = NULL;
    char* newstr = NULL;
    char* oldstr = NULL;
    int   oldstr_len = 0;
    int   substr_len = 0;
    int   replacement_len = 0;
    newstr = strdup(string);
    substr_len = strlen(substr);
    replacement_len = strlen(replacement);

    if (substr == NULL || replacement == NULL) {
        return newstr;
    }
    while ((tok = strstr(newstr, substr))) {
        oldstr = newstr;
        oldstr_len = strlen(oldstr);
        newstr = (char*)malloc(sizeof(char) * (oldstr_len - substr_len + replacement_len + 1));
        if (newstr == NULL) {
            free(oldstr);
            return NULL;
        }
        memcpy(newstr, oldstr, tok - oldstr);
        memcpy(newstr + (tok - oldstr), replacement, replacement_len);
        memcpy(newstr + (tok - oldstr) + replacement_len, tok + substr_len, oldstr_len - substr_len - (tok - oldstr));
        memset(newstr + oldstr_len - substr_len + replacement_len, 0, 1);
        free(oldstr);
    }
    return newstr;
}

char* STRING_shift(const char* string, int byte)
{
    /*
     *  todo @STRING_shift shift @string left @byte character
     *  usage
     *      char* ex = STRING_shift("hello", 2) --> "llo"
    */
    int len = strlen(string);
    if (len <= byte) return "";
    char* rt = (char*)malloc(len - byte + 1);
    int i = 0;
    int j = byte;
    while (string[j] != '\0')
    {
        rt[i] = string[j];
        i++; j++;
    }
    rt[i] = '\0';
    return rt;
}

char* STRING_extract(const char* string, char to)
{
    /*
     *  todo @STRING_extract get a copy string from beginning to @to in @string
     *  usage
     *      char* ex_string = STRING_extract("hello you", ' ')
     *      ---> return "hello"
     */
    char* buffer = (char*)malloc(strlen(string) + 1);
    int i = 0;
    while(string[i] != '\0' && string[i] != to)
    {
        buffer[i] = string[i];
        i++;
    }
    buffer[i] = '\0';
    char* rt = strdup(buffer);
    free(buffer);
    return rt;
}

char* STRING_cut(const char* string, char to)
{
    /*
    *  todo @STRING_cut get a copy string from @to to end of @string
    *  usage
    *      char* ex_string = STRING_cut("hello you", ' ')
    *      ---> return "you"
    */
    if (STRING_count_cha(string, to) < 1) return "";
    char* buffer = (char*)malloc(strlen(string) + 1);
    int i = 0;
    while(string[i] != to)
        i++;
    i++;
    int j = 0;
    while(string[i] != '\0')
    {
        buffer[j] = string[i];
        i++; j++;
    }
    buffer[j] = '\0';
    char* rt = strdup(buffer);
    free(buffer);
    return rt;
}

char** STRING_split(const char* string, const char* delimiter, int times)
{
    /*
     *	todo @STRING_split split a string into array of sub-string
     *	params @delimiter is string which string split at
     *	params @times is number split, it mean have times+1 substring in array return
     *  usage
     *      char** ex_string = STRING_split("hello adam hello alice hello john", "hello ", 2)
     *      --->    ex_string[0] = "adam "
     *              ex_string[1] = "alice "
     *              ex_string[2] = "hello john"
    */
    char* tmp = STRING_replace(string, delimiter, "\v");
    char** rt = (char**)malloc(sizeof(char*) * (times + 1));
    int i = 0;
    while(i < times)
    {
        rt[i] = STRING_extract(tmp, '\v');
        tmp = STRING_cut(tmp, '\v');
        i++;
    }
    rt[i] = strdup(STRING_replace(tmp, "\v", delimiter));
    return rt;
}

#endif // __C_MODULES_UTILITIES_STRINGS_H__
