#include <stdio.h>
#include <string.h>
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要

#include <readline/readline.h>
#include <readline/history.h>

#include "test_shell.h"
#include "cmd_table.h"

// =========================================================
// 補完処理
// =========================================================
// コマンド候補の作成
char *command_generator(const char *text, int state)
{
    static int list_index, len;
    
    if (!state) {
        // 初めてコールされたときはindexとlengthを初期化
        list_index = 0;
        len = strlen(text);
    }
    
    // コマンド情報テーブルをサーチする
    while (tshell_funcs[list_index].command != NULL) {
        char* name = tshell_funcs[list_index].command;    // コマンド情報のコマンド文字列
        list_index++;                                     // indexを進める
        if (strncasecmp(name, text, len) == 0) {
            // 入力文字列とコマンド文字列が部分一致した(大文字/小文字を区別しない)
            return strdup(name);
        }
    }
    
    return NULL;
}

// 補完処理
char **my_completion(const char *text, int start, int end)
{
    char **matches = (char **)NULL;
    
    // 2番目の単語以降でファイル名補完が動かないようにする
    rl_attempted_completion_over = 1;
    
    if (start == 0) {
        // 最初の単語のみ実行
        matches = rl_completion_matches(text, command_generator);
    }

    return matches;
}
