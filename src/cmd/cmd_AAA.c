#include <stdio.h>
#include <string.h>
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要

#include "test_shell.h"
#include "cmd_AAA.h"


//  { "AAA",        tshell_command_AAA,     .usage = "[ON | OFF]    omitted: ON", },
int tshell_command_AAA(int param_num, char* params[], TSHELL_FUNC_INFO* pInfo)
{
    if (param_num == 1) {
        // パラメータ1個(コマンドのみ)の処理
        printf("%s execute #### ON ####\n", pInfo->command);
    } else if (param_num == 2) {
        if (strcasecmp(params[1], "ON") == 0) {
            // パラメータ2個(コマンドとパラメータ1個)の処理
            printf("%s execute #### ON ####\n", pInfo->command);
        } else if (strcasecmp(params[1], "OFF") == 0) {
            printf("%s execute #### OFF ####\n", pInfo->command);
        } else {
            fprintf(stderr, "*** unkknown parameter %s ***\n", params[1]);
            return -1;
        }
    } else {
        fprintf(stderr, "USAGE:    %s %s\n", pInfo->command, pInfo->usage);
        return -1;
    }
    return 0;
}

