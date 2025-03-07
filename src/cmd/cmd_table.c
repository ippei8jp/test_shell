#include <stdio.h>
#include <string.h>
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要

#include "test_shell.h"
#include "cmd_table.h"

#include "cmd_AAA.h"
#include "cmd_ABC.h"
#include "cmd_ABC1.h"
#include "cmd_ABC12.h"
#include "cmd_BBB.h"
#include "cmd_misc.h"
#include "cmd_launcher.h"

// コマンド情報テーブル
TSHELL_FUNC_INFO tshell_funcs[] = {
    { "HELP",       tshell_command_HELP,    .usage = "", },
    { "QUIT",       tshell_command_QUIT,    .usage = "", },
    { "AAA",        tshell_command_AAA,     .usage = "[ON | OFF]    omitted: ON", },
    { "ABC",        tshell_command_ABC,     .usage = "<addr>", },
    { "ABC1",       tshell_command_ABC1,    .usage = "<addr> <data>", },
    { "ABC12",      tshell_command_ABC12,   .usage = "<addr> [data]", },
    { "BBB",        tshell_command_BBB,     .usage = "<ON | OFF>", },
    { NULL,         NULL,                   .usage = NULL, },           // リストの終わり
};

/*******************************************************************************
* Function Name: search_tshell_func
* Description  : コマンド文字列からコマンド情報を取得する
* Arguments    : 
*      cmd      : サーチするコマンド文字列
* Return Value : コマンド情報へのポインタ
* Note         :
********************************************************************************/
TSHELL_FUNC_INFO* search_tshell_func(char* cmd)
{
    for (int i = 0; tshell_funcs[i].command != NULL; i++) {
        if (strcasecmp(cmd, tshell_funcs[i].command) == 0) {
            // 見つかった
            return &tshell_funcs[i];
        }
    }
    // 見つからなかった
    return NULL;
}

