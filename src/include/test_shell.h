#ifndef __TEST_SHELL_H__
#define __TEST_SHELL_H__

// コマンド情報構造体
typedef struct _TSHELL_FUNC_INFO {
    char*       command;
    int         (*func)(int param_num, char* params[], struct _TSHELL_FUNC_INFO* pInfo);
    char*       usage;
} TSHELL_FUNC_INFO;


// 終了フラグ
extern volatile bool shell_terminate_flag;

#endif  /* !__TEST_SHELL_H__ */
