## cwes, C socket http server

### What is cwes
> cwes is a socket server implement http protocol. It used for RestAPI server or web server.  

### Simple install
```bash
sudo apt-install gcc build-essential
git clone https://github.com/pmtoan/cwes.git
cd cwes
gcc -o cwes cwes.c
sudo ./cwes 2> error.log
```

### How it work?
* Static files  
cwes serve static files which locate in static directory.  
Example when user request url http://domain.name/index.html, cwes looking for and return ./static/index.html file.  
Or when user request url http://domain.name/css/style.css, cwes looking for and return ./static/css/style.css

* Serve C source file  
cwes can serve C soure file as well which locate in source directory.  
Example when user request url http://domain.name/hello_world.c, cwes looking for, compile, run, get output and return file ./source/hello_world.c  
**Note: Request of C source file**  
> * C source file must have main() function   
> * C source file can run independently  

### Documents  
* Create new C source file  

> Example create file ./source/hello.c with following code:  
```c
#include <stdio.h>

int main()
{
	printf("<html>"
		"<head>"
		"<title>Hello world</title>"
		"</head>"
		"<body>"
		"<h1>Hello World!<h1>"
		"</body>"
		"</html>");	
}
```

> Go to http://domain.name/hello.c and get output: "Hello World!"  

* Get http request method, uri  
```c
#include <stdio.h>
#include "../../modules/utilities/utilities.h"

int main(int argc, char** argv)
{
    if (argc < 2)
        printf("\n");
    else
    {
        LIST_PAIR list = LIST_PAIR_parse_x_www_form_urlencoded(argv[1]);
        
        char* method = LIST_PAIR_find(list, "method");
        char* uri = LIST_PAIR_find(list, "uri");

        LIST_PAIR_free(&list);
    }
    return 0;
}
```  

* Get request parameters
```c
#include <stdio.h>
#include "../../modules/utilities/utilities.h"

int main(int argc, char** argv)
{
    if (argc < 2)
        printf("\n");
    else
    {
        LIST_PAIR list = LIST_PAIR_parse_x_www_form_urlencoded(argv[1]);
        
        char* value = LIST_PAIR_find(list, "key");

        LIST_PAIR_free(&list);
    }
    return 0;
}
```  

* Get request headers
```c
#include <stdio.h>
#include "../../modules/utilities/utilities.h"

int main(int argc, char** argv)
{
    if (argc < 2)
        printf("\n");
    else
    {
        LIST_PAIR list = LIST_PAIR_parse_x_www_form_urlencoded(argv[1]);
        
        char* user_agent = LIST_PAIR_find(list, "User-Agent");

        LIST_PAIR_free(&list);
    }
    return 0;
}
```  
