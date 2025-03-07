/*******************************************************************************
    テストシェルのひな型
      コンパイル方法：
         gcc test_shell.c -lreadline -o test_shell
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>          // isspace()などを使う時必要
#include <stdint.h>         // intXX_tを使う時必要
#include <stdbool.h>        // boolを使うとき必要


// =========================================================
// ユーティリティ
// =========================================================
/*******************************************************************************
* Function Name: str_split
* Description  : 文字列を分割する
* Arguments    : 
*      string       : 入力文字列
*      separator    : 区切り文字のリスト
*      result       : 分割後の各単語の先頭へのポインタ格納領域
*      result_size  : 分割後の各単語の先頭へのポインタ格納領域のサイズ(分割数)
* Return Value : 分割した単語数
*                空文字列が入力されたら0
*                区切り文字がなかったら1
*                result_size以上の単語があった場合はresult_size
* Note         : 入力文字列の区切り文字は`\0`に置換されるので注意
********************************************************************************/
int str_split(char* string, const char* separator, char** result, size_t result_size)
{
    // 領域サイズが1以下だったらエラー
    if (result_size <= 1) {
        return 0;
    }
    
    char*   save_ptr = string;       // 文字列先頭
    int i;

    // result_size - 1個に分割する
    for (i = 0; i < result_size - 1; i++) {
        char* p = strtok_r(save_ptr, separator, &save_ptr);
        result[i] = p;
        if (p == NULL) {
            // result_size - 1個 以下ならここでリターン
            return i;
        }
    }
    
    if (*save_ptr == '\0') {
        // result_size - 1個に分割された
    } else {
        // まだ続きがある
        // result_size個目に続きの先頭を格納
        result[i] = save_ptr;
        i++;    // 最後に追加したのでインクリメント
    }

    return i;
}


/*******************************************************************************
* Function Name: rtrim
* Description  : 文字列の右側の空白文字を削除する
* Arguments    : 
*      string       : 入力文字列
* Return Value : 文字列へのポインタ
* Note         : 
********************************************************************************/
char* rtrim(char* string)
{
    char*  tmp = (char*) string;
    
    // 文字列の大きさ - ヌルバイトの位置
    int s = (strlen(tmp) - 1);
    
    for (; s >= 0 && isspace(tmp[s]); s--) {
        // 空白文字の間sをデクリメントしていく
    }
    
    tmp[s + 1] = 0x00;
    return tmp;
}


/*******************************************************************************
* Function Name: str_to_uint32
* Description  : 文字列をuint32_t型の数値に変換する
* Arguments    : 
*      s            : 入力文字列
*      pData        : 結果格納領域へのポインタ
*      base         : 基数
* Return Value : 0 : 成功  /  -1: 失敗
* Note         : 
********************************************************************************/
int str_to_uint32(char* s, uint32_t* pData, int base)
{
    char* e;
    unsigned long data = strtoul(s, &e, base);
    if (*e != '\0') {
        // 数値以外が含まれている
        return -1;
    }
    // unsigned longが4バイトの処理系とそれ以外があるので
    // 4バイトより大きい場合は範囲チェック
    if ((sizeof(unsigned long) > 4) && (data > 0xffffffff)) {
        // uint32の範囲に収まらない
        return -1;
    }

    *pData = (uint32_t)data;
    return 0;
}
