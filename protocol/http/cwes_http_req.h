#ifndef __C_WES_HTTP_REQUEST_H__
#define __C_WES_HTTP_REQUEST_H__
#include "cwes_http_format.h"

/*===================================================================================
*		FUNCTION DECLARATION
*==================================================================================*/

HTTP_REQ HTTP_REQ_init();
void HTTP_REQ_free(HTTP_REQ* req);
HTTP_REQ HTTP_REQ_parse_msg(const char* msg);
void _HTTP_REQ_parse_request_line(HTTP_REQ* req, const char* rl);
void _HTTP_REQ_parse_headers(HTTP_REQ* req, const char* hd);
char* HTTP_REQ_get_header(HTTP_REQ req, const char* key);
int HTTP_REQ_validate(const char* msg);




/*===================================================================================
*		FUNCTION IMPLEMENT
*==================================================================================*/
HTTP_REQ HTTP_REQ_parse_msg(const char* msg)
{
    /*
     *	todo: @HTTP_REQ_parse_msg parse a http request msg to HTTP_REQUEST structure
     *	usage:
     *	    HTTP_REQ req = HTTP_REQ_parse_msg(ms);
    */
    HTTP_REQ req = HTTP_REQ_init();

    /* split http request headers and payload */
    char** headers_payload = STRING_split(msg, "\r\n\r\n", 1);

    /* 1. time to parse request line and headers */
    char** request_line_headers = STRING_split(headers_payload[0], "\r\n", 1);

    /* 1.1. time to parse request-line */
    _HTTP_REQ_parse_request_line(&req, request_line_headers[0]);

    /* 1.2. time to parse headers, request_line_headers[1] */
    _HTTP_REQ_parse_headers(&req, request_line_headers[1]);

    /* 2. time to parse parameters in payload if have */
    if (strstr(headers_payload[1], "="))
        req.params = LIST_PAIR_parse_x_www_form_urlencoded(headers_payload[1]);

    /* release memory */
    free(headers_payload[0]);
    free(headers_payload);

    free(request_line_headers[0]);
    free(request_line_headers[1]);
    free(request_line_headers);

    return req;
}

HTTP_REQ HTTP_REQ_init()
{
    /*
     *	todo: @HTTP_REQ_init initialize a HTTP_REQUEST
     *	usage:
     *	    HTTP_REQ req = HTTP_REQ_init()
    */
    HTTP_REQ req;
    req.headers = LIST_PAIR_init();
    req.params = LIST_PAIR_init();
    return req;
}

void HTTP_REQ_free(HTTP_REQ* req)
{
    /*
     *	todo: @HTTP_REQ_free release memory of a HTTP_REQUEST
     *	usage:
     *	    HTTP_REQ req = HTTP_REQ_init()
     *	    ...
     *	    HTTP_REQ_free(&req)
    */
    free(req->method);
    free(req->uri);
    free(req->version);
    LIST_PAIR_free(&(req->headers));
    LIST_PAIR_free(&(req->params));
}

void _HTTP_REQ_parse_request_line(HTTP_REQ* req, const char* rl)
{
    /*
    *	@_HTTP_REQ_parse_request_line parse a http request-line
    */
    char** rl_pattern = STRING_split(rl, " ", 2);

    /* time to parse http method */
    req->method = strdup(rl_pattern[0]);

    /* parse http get prameter if have */
    if (STRING_count_cha(rl_pattern[1], '?') > 0)
    {
        /* get method contain parameters, ex: http://127.0.0.1/index.html?name=toan */
        char** get_uri_params = STRING_split(rl_pattern[1], "?", 1);
        req->params = LIST_PAIR_parse_x_www_form_urlencoded(get_uri_params[1]);
        req->uri = strdup(get_uri_params[0]);
        free(get_uri_params[0]);
        free(get_uri_params[1]);
        free(get_uri_params);
    }
    else
        /* get method not contain parameters, ex: http://127.0.0.1/index.html */
        req->uri = strdup(rl_pattern[1]);

    /* 1.1.3. parse http version */
    req->version = strdup(rl_pattern[2]);
    free(rl_pattern[0]);
    free(rl_pattern[1]);
    free(rl_pattern[2]);
    free(rl_pattern);
}

void _HTTP_REQ_parse_headers(HTTP_REQ* req, const char* hd)
{
    /*
    *	@_HTTP_REQ_parse_headers parse http headers
    */
    int number_of_header = STRING_count_str(hd, "\r\n");
    char** request_headers = STRING_split(hd, "\r\n", number_of_header);

    for (int i = 0; i <= number_of_header; ++i)
    {
        char** header = STRING_split(request_headers[i], ": ", 1);
        LIST_PAIR_append(&(req->headers), header[0], header[1]);
        free(header[0]);
        free(header[1]);
        free(header);
    }
    for (int i = 0; i < number_of_header; ++i)
        free(request_headers[i]);
    free(request_headers);
}

char* HTTP_REQ_get_header(HTTP_REQ req, const char* key)
{
    /*
     * 	todo: @HTTP_REQ_get_header get header value from @req with @key
     * 	usage:
     * 	    HTTP_REQ req = HTTP_REQ_parse_msg(msg)
     * 	    ...
     * 	    char* cookie = HTTP_REQ_get_header(req, "Cookie")
     * 	    ...
    */
    return LIST_PAIR_find(req.headers, key);
}

int HTTP_REQ_validate(const char* msg)
{
    /*
     *  todo: @HTTP_REQ_validate validate a http request message
     *  return 1 if request is valid, otherwise, return 0
    */
    if (!strstr(msg, " HTTP")) return 0;
    if (!strstr(msg, "GET")
    && !strstr(msg, "POST")
    && !strstr(msg, "PUT")
    && !strstr(msg, "HEAD")
    && !strstr(msg, "DELETE")
    && !strstr(msg, "PATCH")) return 0;
    return 1;
}

#endif  // __C_WES_HTTP_REQUEST_H__