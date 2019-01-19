#ifndef __C_MODULES_UTILITIES_LIST_STRING_H__
#define __C_MODULES_UTILITIES_LIST_STRING_H__

#include "types.h"
#include "strings.h"

/*----------------------------------------------------------------*/
LIST_STRING LIST_STRING_init();
void LIST_STRING_free(LIST_STRING* list);
void LIST_STRING_print(LIST_STRING list);
void LIST_STRING_append(LIST_STRING* list, const char* value);
char* LIST_STRING_compose_list_string(LIST_STRING list);
/*----------------------------------------------------------------*/

LIST_STRING LIST_STRING_init()
{
    /*
	 *	todo @LIST_STRING_init() initialize a list of string holder
	 *	usage LIST_STRING list = LIST_STRING_init()
	*/
    LIST_STRING list;
    list.len = 0;
    list.head = NULL;
    return list;
}

void LIST_STRING_free(LIST_STRING* list)
{
    /*
	 *	todo @LIST_STRING_free release memory of @list
	 *	usage
	 *		LIST_STRING list = LIST_STRING_init()
	 *		...
	 *		LIST_STRING_free(&list)
	*/
    while(list->head != NULL)
    {
        STRING* i = list->head;
        list->head = list->head->next;
        free(i->value);
        i->next = NULL;
        free(i);
    }
}

void LIST_STRING_print(LIST_STRING list)
{
    /*
	*	todo @LIST_STRING_print print @list
	*/
    int i = 0;
    while(i < list.len)
    {
        _("%s\n", list.head->value);
        i++;
        list.head = list.head->next;
    }
}

void LIST_STRING_append(LIST_STRING* list, const char* value)
{
    /*
	 *	todo @LIST_STRING_append append a @STRING to @list
	 *	usage
	 *		LIST_STRING list = LIST_STRING_init()
	 *		LIST_STRING_append(&list, "hello name");
	 *		...
	 *		LIST_STRING_free(&list)
	*/
    if (list->len == 0)
    {
        list->head = (STRING*)malloc(sizeof(STRING*));
        list->head->value = strdup(value);
        list->head->len = strlen(value);
        list->head->next = NULL;
    }
    else
    {
        STRING* i = list->head;
        while(i->next != NULL)
            i = i->next;
        STRING* next = (STRING*)malloc(sizeof(STRING*));
        next->value = strdup(value);
        next->len = strlen(value);
        next->next = NULL;
        i->next = next;
    }
    list->len++;
}

char* LIST_STRING_compose_list_string(LIST_STRING list)
{
    /*
	 *	todo @LIST_STRING_compose_list_string compose a LIST_STRING to list string
	 *	list string: ["hello","you"]
	 *	usage
	 *		LIST_STRING list = LIST_STRING_init()
	 *		LIST_STRING_append(&list, "hello");
	 *		LIST_STRING_append(&list, "you");
	 *		char* list_string = LIST_STRING_compose_list_string(list)
	 *		...
	 *		LIST_STRING_free(&list)
	*/
    char* buffer = (char*)malloc(__SIZE_EXTRA__);
    sprintf(buffer, "[");
    for (int i = 0; i < list.len; ++i)
    {
        if (i==0)
            sprintf(buffer, "%s\"%s\"", buffer, list.head->value);
        else
            sprintf(buffer, "%s,\"%s\"", buffer, list.head->value);
        list.head = list.head->next;
    }
    sprintf(buffer, "%s]", buffer);
    char* list_string = strdup(buffer);
    free(buffer);
    return list_string;
}

#endif // __C_MODULES_UTILITIES_LIST_STRING_H__