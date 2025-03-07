#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要

#include "test_shell.h"
#include "cmd_table.h"
#include "cmd_launcher.h"
#include "util.h"


// =========================================================
// コマンドランチャー
// =========================================================
/*******************************************************************************
* Function Name: command_launcher
* Description  : コマンド文字を解析してコマンド実行する
* Arguments    : 
*      input    : 入力コマンド文字列
* Return Value : 
*                0 : 空行のためなにもしなかった
*               -1 : コマンドが見つからなかっら
*                1 : コマンドを実行した(コマンドの実行結果については考慮していない)
* Note         :
********************************************************************************/
int command_launcher(char* input)
{
    int   ret_val = 0;
    
    // 入力文字列から改行文字(LF CR)と#を検索(#以降をコメントとするため)
    char* ln = strpbrk(input, "\n\r#");
    if (ln != NULL) {
       *ln = '\0';                      // 最初に見つかった部分以降を削除
    }
    
    // 右側の空白を削除
    rtrim(input);
    
    // 空行ならスキップ
    if (strlen(input) == 0) {
        return 0;
    }
    
    // 入力コマンド確認
    // fprintf(stderr, "INPUT COMMAND: '%s'\n", input);
    
    // 入力文字列のコピーを作成(パラメータに分割するので)
    char* buff = strdup(input);
    
    // パラメータに分割
    char*   params[16];     // パラメータとして認識できる数
    int param_num = str_split(buff, " ", params, sizeof(params)/sizeof(params[0]));
    if (param_num == 0) {
        // 空行
        ret_val = 0;
        goto out;
    }
    
    // ショートカットキーの処理
    if (strlen(params[0]) == 1) {
        if ((params[0][0] == 'q') || (params[0][0] == 'Q')) {
            params[0] = "QUIT";     // コマンドを差し替え。ポインタなのでstrcpyではない。
            param_num = 1;
        } else if ((params[0][0] == 'h') || (params[0][0] == 'H')) {
            params[0] = "HELP";     // コマンドを差し替え。ポインタなのでstrcpyではない。
            param_num = 1;
        }
    }
    
    // コマンド文字列からコンソールコマンド情報を取得
    TSHELL_FUNC_INFO* pFunc = search_tshell_func(params[0]);
    if (!pFunc) {
        // 見つからなかった
        fprintf(stderr, "*** UNKNOWN COMMAND ***\n");
        ret_val = -1;
        goto out;
    } else {
        // 見つかった
        pFunc->func(param_num, params, pFunc);
        ret_val = 1;
        goto out;
    }

out:
    free(buff);
    return ret_val;
}

