#ifndef __C_WES_LOADER_H__
#define __C_WES_LOADER_H__

#include "../modules/unix/x86_64-linux-gnu/unix_x86_64_linux_files.h"
#include "../modules/unix/x86_64-linux-gnu/unix_x86_64_linux_cmd.h"
#include "../modules/utilities/utilities.h"

char* CONTROLLER_load(const char* bin, LIST_STRING params)
{
    /*
     *  todo @CONTROLLER_load load, run and get output of a binary file via BASH
     *  **** NOTE ****
     *      -> use in LINUX environment only
     *  usage:
     *      To run command "ls -lsah /etc"
     *      LIST_STRING params = LIST_STRING_init()
     *      LIST_STRING_append(params, "-lsa")
     *      LIST_STRING_append(params, "/etc")
     *      char* output = CONTROLLER_load("/bin/ls", params)
    */

    char* cmd = (char*)malloc(__SIZE_LARGE__); // command line buffer
    sprintf(cmd, "%s", bin);
    for (int i = 0; i < params.len; ++i) {
        sprintf(cmd, "%s \"%s\"", cmd, params.head->value);
        params.head = params.head->next;
    }
    return UNIX_X86_64_LINUX_cmd(cmd);
}



#endif // __C_WES_LOADER_H__