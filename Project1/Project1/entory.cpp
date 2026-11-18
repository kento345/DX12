#include<Windows.h>
#pragma comment(lib, "d3d12.lib")   // DirectX12 の本体処理を利用する為に必要なライブラリ
#pragma comment(lib, "dxgi.lib")    // 画面への表示や管理を行う機能を利用する為のライブラリ
#include<cassert>

#include"Application.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // アプリケーションクラスのインスタンスを生成
    Application app;

    if (app.initialize(hInstance)) {
        assert(false && "ウィンドウの初期化に失敗しました");
    }

    // アプリケーションループを開始
    app.loop();

    return 0;
}