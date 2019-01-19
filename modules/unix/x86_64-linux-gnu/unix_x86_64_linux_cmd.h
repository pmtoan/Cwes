#ifndef __C_MODULES_UNIX_X86_64_LINUX_FILE_UTILS_H__
#define __C_MODULES_UNIX_X86_64_LINUX_FILE_UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../utilities/utilities.h"

#define __TMP_OUTPUT__ "__unix_cmd_tmp__"

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
    sprintf(do_cmd, "%s > %s", cmd, __TMP_OUTPUT__);
    system(do_cmd);

    /* Clear up */
    sprintf(do_cmd, "rm -rf %s", __TMP_OUTPUT__);
    system(do_cmd);
    free(do_cmd);

    return;
}

char* UNIX_X86_64_LINUX_cmd(const char* cmd)
{
    /*
     *  todo @UNIX_X86_64_LINUX_cmd execute a command and return output
    */
    char* do_cmd = (char*)malloc(__SIZE_LARGE__);

    /* Execute command */
    sprintf(do_cmd, "%s > %s", cmd, __TMP_OUTPUT__);
    system(do_cmd);

    char* rt = FILE_read_text(__TMP_OUTPUT__);

    /* Clear up */
    sprintf(do_cmd, "rm -rf %s", __TMP_OUTPUT__);
    system(do_cmd);
    free(do_cmd);

    return rt;
}



#endif // __C_MODULES_UNIX_X86_64_LINUX_FILE_UTILS_H__