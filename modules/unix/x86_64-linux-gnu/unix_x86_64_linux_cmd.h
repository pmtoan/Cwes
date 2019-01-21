#ifndef __C_MODULES_UNIX_X86_64_LINUX_FILE_UTILS_H__
#define __C_MODULES_UNIX_X86_64_LINUX_FILE_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../utilities/utilities.h"

/*----------------------------------------------------------------*/
void UNIX_X86_64_LINUX_silent_cmd(const char* cmd);
char* UNIX_X86_64_LINUX_cmd(const char* cmd);
/*----------------------------------------------------------------*/

void UNIX_X86_64_LINUX_silent_cmd(const char* cmd)
{
    /*
     *  todo @UNIX_X86_64_LINUX_silent_cmd execute a command line and not get output
    */
    char* do_cmd = (char*)malloc(__SIZE_LARGE__);

    /* Execute command */
    sprintf(do_cmd, "%s > /dev/null", cmd);
    system(do_cmd);

    free(do_cmd);

    return;
}

char* UNIX_X86_64_LINUX_cmd(const char* cmd)
{
    /*
     *  todo @UNIX_X86_64_LINUX_cmd execute a command and return output
    */
    FILE* fp;
    fp = popen(cmd, "r");

    if (!fp)
        return "Command error!";

    char* rt = (char*)malloc(__SIZE_EXTRA__);
    fread(rt, __SIZE_EXTRA__, 1, fp);
    fclose(fp);
    return rt;
}



#endif // __C_MODULES_UNIX_X86_64_LINUX_FILE_UTILS_H__