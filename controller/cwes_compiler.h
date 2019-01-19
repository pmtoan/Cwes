#ifndef __C_WES_COMPILER_H__
#define __C_WES_COMPILER_H__

#include "cwes_loader.h"

#define __BIN_NAME_AFTER_COMPILE__  "./__c_wes_bin__"
#define __GNU_C_COMPILER__  "gcc"

int _CONTROLLER_check_gcc()
{
    /*
     *  @_CONTROLLER_check_gcc check gcc compiler exists or not
     *  return 1 if compiler exists
    */
    LIST_STRING list = LIST_STRING_init();
    LIST_STRING_append(&list, __GNU_C_COMPILER__);
    char* gcc = CONTROLLER_load("which", list); // from cwes_loader.h
    if (strstr(gcc, __GNU_C_COMPILER__)) return 1;
    return 0;
}

int _CONTROLLER_do_compile(const char* path)
{
    /*
     *  @_CONTROLLER_do_compile do compile a c source file
     *  cmd: gcc -w -o __c_wes_bin__ <source_file> > __gcc_tmp__
     *  return 1 on success
    */

    char* cmd = (char*)malloc(__SIZE_LARGE__); // command line buffer

    /* Remove old binary */
    sprintf(cmd, "rm -rf %s", __BIN_NAME_AFTER_COMPILE__);
    UNIX_X86_64_LINUX_silent_cmd(cmd);

    /* Do compile new binary file from source */
    sprintf(cmd, "%s -w -o %s %s", __GNU_C_COMPILER__, __BIN_NAME_AFTER_COMPILE__, path);
    UNIX_X86_64_LINUX_silent_cmd(cmd);

    /* Check compile status */
    return UNIX_X86_64_LINUX_stat_type(__BIN_NAME_AFTER_COMPILE__);
}

char* CONTROLLER_compiler(const char* path, LIST_STRING params)
{
    /*
     *  todo  @CONTROLLER_compiler compile, run and get output of a validate c source file
     *  @validate c source file:
     *      . Include main() function
     *      . Can run independence
    */

    /* If compiler not found */
    if (_CONTROLLER_check_gcc() == 0)
        return "Compiler not found!";

    if (_CONTROLLER_do_compile(path) != 1)
        return "Compile error!";

    return CONTROLLER_load(__BIN_NAME_AFTER_COMPILE__, params);
}

#endif  // __C_WES_COMPILER_H__