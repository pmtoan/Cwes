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
char* STRING_to_ascii(const char* string);
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

char* STRING_to_ascii(const char* string)
{
    /*
     *  todo @STRING_to_ascii convert a string to valid ASCII string
    */
    char* rt = STRING_replace(string, "%20", " ");
    rt = STRING_replace(rt, "%21", "!");
    rt = STRING_replace(rt, "%22", "\"");
    rt = STRING_replace(rt, "%23", "#");
    rt = STRING_replace(rt, "%24", "$");
    rt = STRING_replace(rt, "%25", "%");
    rt = STRING_replace(rt, "%26", "&");
    rt = STRING_replace(rt, "%27", "'");
    rt = STRING_replace(rt, "%28", "(");
    rt = STRING_replace(rt, "%29", ")");
    rt = STRING_replace(rt, "%2A", "*");
    rt = STRING_replace(rt, "%2B", "+");
    rt = STRING_replace(rt, "%2C", ",");
    rt = STRING_replace(rt, "%2D", "-");
    rt = STRING_replace(rt, "%2E", ".");
    rt = STRING_replace(rt, "%2F", "/");
    rt = STRING_replace(rt, "%30", "0");
    rt = STRING_replace(rt, "%31", "1");
    rt = STRING_replace(rt, "%32", "2");
    rt = STRING_replace(rt, "%33", "3");
    rt = STRING_replace(rt, "%34", "4");
    rt = STRING_replace(rt, "%35", "5");
    rt = STRING_replace(rt, "%36", "6");
    rt = STRING_replace(rt, "%37", "7");
    rt = STRING_replace(rt, "%38", "8");
    rt = STRING_replace(rt, "%39", "9");
    rt = STRING_replace(rt, "%3A", ":");
    rt = STRING_replace(rt, "%3B", ";");
    rt = STRING_replace(rt, "%3C", "<");
    rt = STRING_replace(rt, "%3D", "=");
    rt = STRING_replace(rt, "%3E", ">");
    rt = STRING_replace(rt, "%3F", "?");
    rt = STRING_replace(rt, "%40", "@");
    rt = STRING_replace(rt, "%41", "A");
    rt = STRING_replace(rt, "%42", "B");
    rt = STRING_replace(rt, "%43", "C");
    rt = STRING_replace(rt, "%44", "D");
    rt = STRING_replace(rt, "%45", "E");
    rt = STRING_replace(rt, "%46", "F");
    rt = STRING_replace(rt, "%47", "G");
    rt = STRING_replace(rt, "%48", "H");
    rt = STRING_replace(rt, "%49", "I");
    rt = STRING_replace(rt, "%4A", "J");
    rt = STRING_replace(rt, "%4B", "K");
    rt = STRING_replace(rt, "%4C", "L");
    rt = STRING_replace(rt, "%4D", "M");
    rt = STRING_replace(rt, "%4E", "N");
    rt = STRING_replace(rt, "%4F", "O");
    rt = STRING_replace(rt, "%50", "P");
    rt = STRING_replace(rt, "%51", "Q");
    rt = STRING_replace(rt, "%52", "R");
    rt = STRING_replace(rt, "%53", "S");
    rt = STRING_replace(rt, "%54", "T");
    rt = STRING_replace(rt, "%55", "U");
    rt = STRING_replace(rt, "%56", "V");
    rt = STRING_replace(rt, "%57", "W");
    rt = STRING_replace(rt, "%58", "X");
    rt = STRING_replace(rt, "%59", "Y");
    rt = STRING_replace(rt, "%5A", "Z");
    rt = STRING_replace(rt, "%5B", "[");
    rt = STRING_replace(rt, "%5C", "\\");
    rt = STRING_replace(rt, "%5D", "]");
    rt = STRING_replace(rt, "%5E", "^");
    rt = STRING_replace(rt, "%5F", "_");
    rt = STRING_replace(rt, "%60", "_");
    rt = STRING_replace(rt, "%61", "a");
    rt = STRING_replace(rt, "%62", "b");
    rt = STRING_replace(rt, "%63", "c");
    rt = STRING_replace(rt, "%64", "d");
    rt = STRING_replace(rt, "%65", "e");
    rt = STRING_replace(rt, "%66", "f");
    rt = STRING_replace(rt, "%67", "g");
    rt = STRING_replace(rt, "%68", "h");
    rt = STRING_replace(rt, "%69", "i");
    rt = STRING_replace(rt, "%6A", "j");
    rt = STRING_replace(rt, "%6B", "k");
    rt = STRING_replace(rt, "%6C", "l");
    rt = STRING_replace(rt, "%6D", "m");
    rt = STRING_replace(rt, "%6E", "n");
    rt = STRING_replace(rt, "%6F", "o");
    rt = STRING_replace(rt, "%70", "p");
    rt = STRING_replace(rt, "%71", "q");
    rt = STRING_replace(rt, "%72", "r");
    rt = STRING_replace(rt, "%73", "s");
    rt = STRING_replace(rt, "%74", "t");
    rt = STRING_replace(rt, "%75", "u");
    rt = STRING_replace(rt, "%76", "v");
    rt = STRING_replace(rt, "%77", "w");
    rt = STRING_replace(rt, "%78", "x");
    rt = STRING_replace(rt, "%79", "y");
    rt = STRING_replace(rt, "%7A", "z");
    rt = STRING_replace(rt, "%7B", "{");
    rt = STRING_replace(rt, "%7C", "|");
    rt = STRING_replace(rt, "%7D", "}");
    rt = STRING_replace(rt, "%7E", "~");
    return rt;
}

#endif // __C_MODULES_UTILITIES_STRINGS_H__
