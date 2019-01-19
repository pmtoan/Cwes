#ifndef __C_WES_CONTROLLER_H__
#define __C_WES_CONTROLLER_H__

#include "../modules/utilities/utilities.h"
#include "../protocol/http/cwes_http.h"
#include "cwes_compiler.h"

#define __MSG__ "What do you want?"

#define __SOURCE__ROOT__    "./source"
#define __STATIC_ROOT__     "./static"

char* CONTROLLER_control_everything(const char* req_msg)
{
    /*
     *  todo @CONTROLLER_control_everything check and make decision for all http request
     */
    if (HTTP_REQ_validate(req_msg) != 1) return __MSG__;

    HTTP_REQ req = HTTP_REQ_parse_msg(req_msg);
    char* path = (char*)malloc(__SIZE_LARGE__);

    /* For static file */
    sprintf(path, "%s%s", __STATIC_ROOT__, req.uri);
    if (UNIX_X86_64_LINUX_stat_type(path) == 1)
        return HTTP_RES_compose(HTTP_RES_build_up(__HTTP_OK__, FILE_read_text(path)));

    /* For c source file */
    sprintf(path, "%s%s", __SOURCE__ROOT__, req.uri);
    /* C source file not found */
    if (UNIX_X86_64_LINUX_stat_type(path) == -1)
        return HTTP_RES_compose(HTTP_RES_build_up(__HTTP_NOT_FOUND__, "Object not found"));

    /* Found c source file */
    char* params = LIST_PAIR_compose_string(req.params);
    LIST_STRING list = LIST_STRING_init();
    LIST_STRING_append(&list, params);

    return HTTP_RES_compose(
            HTTP_RES_build_up(
                    __HTTP_OK__,
                    CONTROLLER_compiler(path, list)
                    ));
}


#endif // __C_WES_CONTROLLER_H__