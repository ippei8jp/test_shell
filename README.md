# 概要

makefileを使ったプロジェクトのひな型としてまとめてみた。  
元のソースは[test shellのひな型](https://ippei8jp.github.io/memoBlog/2023/05/15/test_shell_1.html){:target="_blank"}  
これをmakefileでの例にできるように無理やりファイル分割した。  
また、元記事はlinux環境前提だったけど、今回はWindows + MinGW-w64 を使用している。  

コマンドヒストリや補完とかも使えてなかなか便利だと自画自賛。  
(ひな型なので、コマンドそのものに意味はない)  
ついでに最近やってみた(イマサラ？)カバレッジ測定にも対応してみた。  

# 開発環境

- コンパイラ MinGW-w64 Release of 14.2.0-rt_v12-rev1 [niXman/mingw-builds-binaries](https://github.com/niXman/mingw-builds-binaries/releases){:target="_blank"}   
- make MSYS2でインストールしたものにpathを通してコマンドプロンプトから使用できるようにした  


# 使い方

makeするだけ
カバレッジ測定用にbuildしたいときは、makefileの先頭の``COVERAGE := 1`` の部分を有効にする。  
makeは MSYS2で以下のコマンドでインストールできる。
```
pacman -S base-devel
    or
pacman -S make
```


makefileとしては、依存関係の自動生成とか、文字コードをUTF-8にするとか、
「どうやるんだっけ？」となりがちなところを対応しておいた。  

# カバレッジ結果表示方法
lcovはMSYS2のものを使う。  
lcovのインストールはMSYS2から  
```
pacman -S lcov
```
でインストールできる  
(色々面倒な手順を紹介しているページもあるけど、これイッパツでOK)  

カバレッジ測定用にbuildした後実行し、以下のコマンドを実行すればcovディレクトリにhtmlファイルが生成される。  
```
make cov
```

> lcovはexeではなくperlスクリプトなのでコマンドプロンプトから直接実行できない。  
> で、bash -c "lcov 〜" と実行するのだけど、  
> そのままだとコマンド内部で実行されるfindコマンドが C:\WINDOWS\system32\find.exe を実行してしまい正常に動作しない。
> そこで、PATHの先頭に c:\msys64\usr\bin を追加して実行すると正常に動作するようになる。  
> (gcovにもpathが通ってる必要があるので、通ってないときは通してください(MINGW_BIN_DIR を追加))
> 逐一設定するのはめんどなので、make経由で実行できるようにした。  
