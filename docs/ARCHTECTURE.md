# HINAN-構成

## hinan (namespace)
全てのクラス等はここに格納される

- hinan::Core (QObject)  
コンストラクタで引数解析、MainWindowとPracticeKitの管理  

- hinan::PracticeKit (QObject)  
スクリプト解析とポート管理をそれぞれスレッドで実行させる

- hinan::ProgramReader (QObject)  
C言語のプログラムをAngelScriptとして読み込み、実行する

- hinan::PortManager (QObject)  
PracticeKitが持つProgramReaderのポインタを格納、ポートの状況を管理する

- hinan::Actions  
様々なコマンドの集合、MainWindow用ToolBar/MenuBarの管理

## hinan::gui
QWidget系のクラスを継承したものを入れる

- hinan::gui::MainWindow (QMainWindow)  
メインウィンドウ

## hinan::port (namespace)  
ポートと、それに対応する文字列
{P1~P9,PA,PB}D[D]R

例:  
hinan::port::P1DR => "P1DR"  
hinan::port::PBDDR => "PBDDR"  

- hinan::port::port_list (QStringList)  
ポート全部格納  
`for(auto str: port_list)`するためのもの

- hinan::port::port_dr (QStringList)  
P*DRが格納されている

- hinan::port::port_ddr (QStringList)  
P*DDRが格納されている
