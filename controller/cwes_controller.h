#ifndef __C_WES_CONTROLLER_H__
#define __C_WES_CONTROLLER_H__

#include "../modules/utilities/utils.h"
#include "../protocol/http/cwes_http.h"
#include "cwes_compiler.h"

#define __MSG__ "What do you want?"

#define __SOURCE_ROOT__ "./sources"
#define __STATIC_ROOT__ "./statics"

char* controller_control_everything(const char* req_msg)
{
    /*
     *  todo @controller_control_everything check and make decision for all http request
     */
    if (http_req_validate(req_msg) != 1) return __MSG__;

    HTTP_REQ req = http_req_parse_msg(req_msg);
    char* path = (char*)malloc(__SIZE_LARGE__);

    /* For static file */
    sprintf(path, "%s%s", __STATIC_ROOT__, req.uri);
    if (unix_x86_64_linux_get_stat_type(path) == 1)
        return http_res_compose(http_res_build_up(__HTTP_OK__, file_read_text(path)));

    /* For c source file */
    sprintf(path, "%s%s", __SOURCE_ROOT__, req.uri);
    /* C source file not found */
    if (unix_x86_64_linux_get_stat_type(path) <= 0)
        return http_res_compose(http_res_build_up(__HTTP_NOT_FOUND__, "Object not found"));

    /* Found c source file */
    char* params = (char*)malloc(__SIZE_LARGE__);
    sprintf(
            params,
            "method=%s&uri=%s&%s&%s",
            req.method,
            req.uri,
            list_pair_compose_x(req.headers),
            list_pair_compose_x(req.params)
            );

    LIST_STRING list = list_string_init();

    list_string_append(&list, params);

    return http_res_compose(
            http_res_build_up(
                    __HTTP_OK__,
                    controller_compiler(path, list)
                    ));
}


#endif // __C_WES_CONTROLLER_H__