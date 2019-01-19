#include <stdio.h>
#include "../modules/utilities/utilities.h"


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
        LIST_PAIR params = LIST_PAIR_parse_x_www_form_urlencoded(argv[1]);
        printf("<html>"
               "<head>"
               "<title>Hello from cwes</title>"
               "</head>"
               "<body>"
               "<h1>Hello %s</h1>"
               "</body>"
               "</html", LIST_PAIR_find(params, "name"));
    }
}