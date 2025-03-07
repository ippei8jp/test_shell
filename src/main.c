/*******************************************************************************
    テストシェルのひな型
      コンパイル方法：
         gcc test_shell.c -lreadline -o test_shell
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要
#include <readline/readline.h>
#include <readline/history.h>

#include "cmd_launcher.h"
#include "completion.h"
#include "util.h"


// 終了フラグ
volatile bool shell_terminate_flag = false;

// =========================================================
// メインルーチン
// =========================================================
int main(int argc, char *argv[])
{
    // 補完処理関数を指定
    rl_attempted_completion_function = my_completion;
    
    while (!shell_terminate_flag) {   // 終了フラグが立つまでループ
        char* input = readline(">> ");      // コマンド入力待ち
        if (input == NULL) {
            // CTRL-Dなどで終了
            break;
        }
        // printf("input: '%s'\n", input);
        
        // コマンド実行
        int ret = command_launcher(input);
        
        if (ret != 0) {
            // 空行でなければヒストリに追加しておく
            using_history();                               // 履歴参照ポイント初期化
            HIST_ENTRY* pPrevHist = previous_history();    // 前回の履歴取得
            if ((pPrevHist == NULL) || (strcasecmp(pPrevHist->line, input))) {
                // 前回の履歴がないか前回の履歴と今回の内容が異なる
                // printf("%%%%%% ADD %%%%%%\n");
                add_history(input);
            }
        }
        
        // メモリ解放を忘れずに
        free(input);
    }
    return 0;
}
