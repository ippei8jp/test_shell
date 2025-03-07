#include <stdio.h>
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要

#include "test_shell.h"
#include "util.h"
#include "cmd_ABC1.h"


//  { "ABC1",       tshell_command_ABC1,    .usage = "<addr> <data>", },
int tshell_command_ABC1(int param_num, char* params[], TSHELL_FUNC_INFO* pInfo)
{
    if (param_num == 3) {
        // コマンドとパラメータ2個の処理
        uint32_t addr;
        if (str_to_uint32(params[1], &addr, 0)) {
            fprintf(stderr, "*** Not number ***\n");
            return -1;
        }
        uint32_t data;
        if (str_to_uint32(params[2], &data, 0)) {
            fprintf(stderr, "*** Not number ***\n");
            return -1;
        }
        printf("%s execute #### %d  %d ####\n", pInfo->command, addr, data);
    } else {
        fprintf(stderr, "USAGE:    %s %s\n", pInfo->command, pInfo->usage);
        return -1;
    }
    return 0;
}

