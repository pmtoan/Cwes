#ifndef __C_MODULES_UTILITIES_LIST_PAIR_H__
#define __C_MODULES_UTILITIES_LIST_PAIR_H__

#include "types.h"
#include "strings.h"

/*----------------------------------------------------------------*/
LIST_PAIR LIST_PAIR_init();
void LIST_PAIR_free(LIST_PAIR* list);
void LIST_PAIR_print(LIST_PAIR list);
void LIST_PAIR_append(LIST_PAIR* list, const char* key, const char* value);
char* LIST_PAIR_find(LIST_PAIR list, const char* key);
LIST_PAIR LIST_PAIR_parse_x_www_form_urlencoded(const char* msg);
char* LIST_PAIR_compose_string(LIST_PAIR list);
char* LIST_PAIR_compose_object_string(LIST_PAIR list);
/*----------------------------------------------------------------*/






LIST_PAIR LIST_PAIR_init()
{
	/*
	 *	todo @LIST_PAIR_init() initialize a list of pair holder
	 *	usage LIST_PAIR list = LIST_PAIR_init()
	*/
	LIST_PAIR list;
	list.len = 0;
	list.head = NULL;
	return list;
}

void LIST_PAIR_free(LIST_PAIR* list)
{
	/*
	 *	todo @LIST_PAIR_free release memory of @list
	 *	usage
	 *		LIST_PAIR list = LIST_PAIR_init()
	 *		...
	 *		LIST_PAIR_free(&list)
	*/
	while(list->head != NULL)
	{
		PAIR* i = list->head;
		list->head = list->head->next;
		free(i->key);
		free(i->value);
		i->next = NULL;
		free(i);
	}
}

void LIST_PAIR_print(LIST_PAIR list)
{
	/*
	*	todo @LIST_PAIR_print print @list
	*/
	int i = 0;
	while(i < list.len)
	{
		_("%s: %s\n", list.head->key, list.head->value);
		i++;
		list.head = list.head->next;
	}
}

void LIST_PAIR_append(LIST_PAIR* list, const char* key, const char* value)
{
	/*
	 *	todo @LIST_PAIR_append append a @key-@value pair to @list
	 *	usage
	 *		LIST_PAIR list = LIST_PAIR_init()
	 *		LIST_PAIR_append(&list, "name", "list_pair");
	 *		...
	 *		LIST_PAIR_free(&list)
	*/
	if (list->len == 0)
	{
		list->head = (PAIR*)malloc(sizeof(PAIR*));
		list->head->key = strdup(key);
		list->head->value = strdup(value);
		list->head->next = NULL;
	}
	else
	{
		PAIR* i = list->head;
		while(i->next != NULL)
			i = i->next;
		PAIR* next = (PAIR*)malloc(sizeof(PAIR*));
		next->key = strdup(key);
		next->value = strdup(value);
		next->next = NULL;
		i->next = next;
	}
	list->len++;
}

char* LIST_PAIR_find(LIST_PAIR list, const char* key)
{
	/*
	 *	todo @LIST_PAIR_find search and get value contain @key from @list
	 *	Return "" if key is not found, otherwise, return value of pair
	 *	usage
	 *		LIST_PAIR list = LIST_PAIR_init()
	 *		LIST_PAIR_append(&list, "name", "list_pair");
	 *		...
	 *		LIST_PAIR_find(list, "name"); --> return "list_pair"
	 *		LIST_PAIR_find(list, "msg"); --> return NULL
	 *		LIST_PAIR_free(&list)
	*/

	while(list.head != NULL)
	{
		if (strcmp(list.head->key, key) == 0)
			return list.head->value;
		list.head = list.head->next;
	}
	return "";
}

LIST_PAIR LIST_PAIR_parse_x_www_form_urlencoded(const char* msg)
{
	/*
	 *	todo @LIST_PAIR_parse_x_www_form_urlencoded parse a string in x-www-form-urlencoded format
	 *	x-www-form-urlencoded format: name=toan&school=university of information technology
	 *	usage
	 *		LIST_PAIR list = LIST_PAIR_parse_x_www_form_urlencoded("name=toan&school=university of information technology")
	 *		list = {
	 *			"name": "toan",
	 *			"school": "university of information technology"
	 *		}
	*/
	LIST_PAIR list = LIST_PAIR_init();
	int estimate_length = STRING_count_cha(msg, '&');
	char** pairs = STRING_split(msg, "&", estimate_length);
	for (int i = 0; i <= estimate_length; ++i)
	{
		char** pair = STRING_split(pairs[i], "=", 1);
		LIST_PAIR_append(&list, STRING_to_ascii(pair[0]), STRING_to_ascii(pair[1]));
		free(pair[0]);
		free(pair[1]);
		free(pair);
	}
	for (int i = 0; i <= estimate_length; ++i)
		free(pairs[i]);
	free(pairs);
	return list;
}

char* LIST_PAIR_compose_string(LIST_PAIR list)
{
	/*
	 *	todo @LIST_PAIR_compose_string compose LIST_PAIR to x-www-form-urlencoded string
	 *	x-www-form-urlencoded string: name=toan&school=university of information technology
	 *	usage
	 *		LIST_PAIR list = LIST_PAIR_init()
	 *		LIST_PAIR_append(&list, "name", "toan");
	 *		LIST_PAIR_append(&list, "school", "university of information technology");
	 *		char* str = LIST_PAIR_compose_string(list)
	 *		...
	 *		LIST_PAIR_free(&list)
	*/
	char* buffer = (char*)malloc(__SIZE_EXTRA__);
	for (int i = 0; i < list.len; ++i)
	{
		if (i==0)
			sprintf(buffer, "%s=%s", list.head->key, list.head->value);
		else
			sprintf(buffer, "%s&%s=%s", buffer, list.head->key, list.head->value);
		list.head = list.head->next;
	}
	char* rt = strdup(buffer);
	free(buffer);
	return rt;
}

char* LIST_PAIR_compose_object_string(LIST_PAIR list)
{
	/*
	 *	todo @LIST_PAIR_compose_object_string compose a LIST_PAIR to object string
	 *	object string: {"name":"toan","school":"university of information technology"}
	 *	usage
	 *		LIST_PAIR list = LIST_PAIR_init()
	 *		LIST_PAIR_append(&list, "name", "toan");
	 *		LIST_PAIR_append(&list, "school", "university of information technology");
	 *		char* obj_string = LIST_PAIR_compose_object_string(list)
	 *		...
	 *		LIST_PAIR_free(&list)
	*/
	char* buffer = (char*)malloc(__SIZE_EXTRA__);
	sprintf(buffer, "{");
	for (int i = 0; i < list.len; ++i)
	{
		if (i==0)
			sprintf(buffer, "%s\"%s\":\"%s\"", buffer, list.head->key, list.head->value);
		else
			sprintf(buffer, "%s,\"%s\":\"%s\"", buffer, list.head->key, list.head->value);
		list.head = list.head->next;
	}
	sprintf(buffer, "%s}", buffer);
	char* obj_string = strdup(buffer);
	free(buffer);
	return obj_string;
}

#endif // __C_MODULES_UTILITIES_LIST_PAIR_H__