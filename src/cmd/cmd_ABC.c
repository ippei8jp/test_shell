#include <stdio.h>
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要

#include "test_shell.h"
#include "util.h"
#include "cmd_ABC.h"


//  { "ABC",        tshell_command_ABC,     .usage = "addr", },
int tshell_command_ABC(int param_num, char* params[], TSHELL_FUNC_INFO* pInfo)
{
    if (param_num == 2) {
        // コマンドとパラメータ1個の処理
        uint32_t addr;
        if (str_to_uint32(params[1], &addr, 0)) {
            fprintf(stderr, "*** Not number ***\n");
            return -1;
        }
        printf("%s execute #### %d ####\n", pInfo->command, addr);
    } else {
        fprintf(stderr, "USAGE:    %s %s\n", pInfo->command, pInfo->usage);
        return -1;
    }
    return 0;
}
