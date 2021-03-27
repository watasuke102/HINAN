# HINAN-構成

## hinan (namespace)
全てのクラス等はここに格納される

- hinan::Core (QObject)  
コンストラクタで引数解析、MainWindowとPracticeKitの管理  
エラー時用のダイアログ表示関数を持つ

- hinan::PracticeKit (QObject)  
スクリプト解析とポート管理をそれぞれスレッドで実行させる

- hinan::ProgramReader (QObject)  
C言語のプログラムをAngelScriptとして読み込み、実行する

- hinan::ComponentManager (QObject)  
hinan::componentsで定義されているLEDやボタンを管理、更新  
MainWindow上のDockWidgetとして表示される、ポート状態の一覧を表示できるウィジェット (QTreeWidget) を持つ

- hinan::Actions (QObject)  
様々なコマンドの集合、MainWindow用ToolBar/MenuBarの管理

## hinan::gui (namespace)
QWidget系のクラスを継承したものを入れる

- hinan::gui::MainWindow (QMainWindow)  
メインウィンドウ

- hinan::gui::KitMainUi (QSvgWidget)  
SVGによる実習キット全体像の表示

## hinan::components (namespace)
実習キット上のLEDやボタンのまとまり

- hinan::components::ComponentInterface (QWidget)  
全コンポーネントの基底クラス

- hinan::components::LED (ComponentInterface)  
ポートBを読み取り、LEDを表示

- hinan::components::Segment (ComponentInterface)  
ポート4を読み取り、7セグメントLEDを表示

- hinan::components::ToggleSwitches (ComponentInterface)  
トグルスイッチの状態をポート2に格納

- hinan::components::TactSwitches (ComponentInterface)  
タクトスイッチの状態をポート5に格納

## hinan::port (namespace)  
ポートと、それに対応する文字列
P[1-9AB]D(D?)R

例:  
hinan::port::P1DR => "P1DR"  
hinan::port::PBDDR => "PBDDR"  

ポート状態の取得は `PracticeKit::Instance().reader->GetPortValue(hinan::port)` で行う

- hinan::port::port_list (QStringList)  
ポート全部格納  
`for(auto str: port_list)`するためのもの

- hinan::port::port_dr (QStringList)  
P*DRが格納されている

- hinan::port::port_ddr (QStringList)  
P*DDRが格納されている
