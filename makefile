# カバレッジ測定するときは以下を有効化
# COVERAGE := 1

# lcov実行時、MSYS2の/usr/binがC:\WINDOWS\system32\より前にないといけないので設定
# 具体的にはfindがWindowsのものでなくMSYS2のものが実行されるようにする
PATH := c:/msys64/usr/bin;$(PATH)

# ターゲット
TARGET = test_shell.exe

# minGW トップディレクトリ
MINGW_DIR := c:/mingw/mingw64-14.2.0

MINGW_BIN_DIR := $(MINGW_DIR)/bin
MINGW_OPT_DIR := $(MINGW_DIR)/opt

# optディレクトリのincludeとlib
OPT_INCLUDE := $(MINGW_OPT_DIR)/include
OPT_LIB     := $(MINGW_OPT_DIR)/lib
OPT_BIN     := $(MINGW_OPT_DIR)/bin

CC    := $(MINGW_BIN_DIR)/gcc
LD    := $(MINGW_BIN_DIR)/gcc

# ディレクトリ
SRC_DIR = src
OBJ_DIR = obj

# ソースファイル類のパス
SRCPATH = $(SRC_DIR) $(SRC_DIR)/cmd $(SRC_DIR)/readline $(SRC_DIR)/util
INCPATH = . $(SRCPATH) $(SRC_DIR)/include $(OPT_INCLUDE)

# ソースファイル(ディレクトリは付加しない)
SRCS  = main.c
SRCS += cmd_AAA.c cmd_ABC.c cmd_ABC1.c cmd_ABC12.c cmd_BBB.c 
SRCS += cmd_misc.c cmd_launcher.c cmd_table.c
SRCS += completion.c 
SRCS += util.c

# オブジェクトファイルと依存関係ファイル
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

# VPATHの設定(:区切りに)
VPATH  = $(SRCPATH:%=:%)

# インクルードパスをgccのオプション形式に変換(-Iを付加)
IPATH  = $(INCPATH:%=-I%)

# コンパイラのフラグ設定
CPPFLAGS = $(IPATH)
CFLAGS   = -g -Wall -finput-charset=UTF-8 -fexec-charset=UTF-8

# 依存関係ファイル生成のためのフラグ設定
# -MTで出力するターゲット名を指定できる(ディレクトリ込みで出力できる)
# ｰMMでなく-MMDを指定することでコンパイルと依存関係ファイル生成を同時に行える
# -MFのパラメータはDEPS設定に合わせること
DEPSFLAGS = -MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.d

# リンカのフラグ設定
LDFLAGS  = -L $(OPT_LIB)
LIBS     = -lreadline 

# カバレッジ測定時の追加設定
ifdef COVERAGE
    CFLAGS  += --coverage
    LIBS    += -lgcov 
endif

COV_INFO = cov.info
COV_DIR  = cov


# makeルール
all : $(TARGET)

clean : release
	rm -f $(TARGET) 

release :
	rm -f $(OBJS)  $(DEPS) $(OBJS:.o=.gcda) $(OBJS:.o=.gcno)

# リンクルール
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
	@echo
	@echo
	@echo ============================================
	@echo PATH に $(OPT_BIN) を追加してください
	@echo "set PATH=$(subst /,\,$(OPT_BIN));%PATH%"
	@echo ============================================
	@echo
	@echo

 
 

# コンパイルルール
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPSFLAGS) -c $< -o $@

# 依存関係ファイルのインクルード
sinclude $(DEPS)

# カバレッジ結果の集計
cov :
	# lcov/genhtml はperlスクリプトなので、bashを起動して実行する
	bash -c "lcov -c -d $(OBJ_DIR) -o $(COV_INFO)"
	bash -c "genhtml $(COV_INFO) -o $(COV_DIR)"

cov_clean :
	rm -fr $(COV_INFO) $(COV_DIR)

