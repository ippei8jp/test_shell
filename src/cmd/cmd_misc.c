#include <stdio.h>
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要

#include "test_shell.h"
#include "cmd_table.h"
#include "cmd_misc.h"


int tshell_command_HELP(int param_num, char* params[], TSHELL_FUNC_INFO* pInfo)
{
    extern TSHELL_FUNC_INFO tshell_funcs[];
    
    // パラメータ数のチェックは省略(指定されても無視)
    
    fprintf(stderr, "==== USAGE ====\n");
    for (int i = 0; tshell_funcs[i].command != NULL; i++) {
        fprintf(stderr, "    %s %s\n", tshell_funcs[i].command, tshell_funcs[i].usage);
    }
    fprintf(stderr, "\n\n");
    return 0;
}

int tshell_command_QUIT(int param_num, char* params[], TSHELL_FUNC_INFO* pInfo)
{
    // パラメータ数のチェックは省略(指定されても無視)
    
    // 終了フラグをセット
    shell_terminate_flag = true;

    return 0;
}

