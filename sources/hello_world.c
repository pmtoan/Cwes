#include <stdio.h>
#include "../modules/data_structure/list_pair.h"
#include "../modules/utilities/utils.h"


int main(int argc, char** argv)
{
    if (argc < 2)
        printf("<html>"
               "<head>"
               "<title>Hello from cwes</title>"
               "</head>"
               "<body>"
               "<h1>Hello world</h1>"
               "</body>"
               "</html");
    else
    {
        LIST_PAIR params = list_pair_parse_x_www_form_urlencoded(argv[1]);
        printf("<html>"
               "<head>"
               "<title>Hello from cwes</title>"
               "</head>"
               "<body>"
               "<h1>Hello %s</h1>"
               "</body>"
               "</html", list_pair_find(params, "name"));
    }
}