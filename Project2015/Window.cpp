#include "Window.h"
#include "resource.h"
#include "Editor.h"
#include "DxLib.h"
#include "define.h"

const char* CLASS_NAME = "IE";
const char* TITLE_NAME = "ImageEditor";

Window::Window( ) {
}


Window::~Window( ) {
}

int Window::create( ) {
	WNDCLASSEX wc = { };
	//サイズ
	wc.cbSize			= sizeof( WNDCLASSEX );
	//ウィンドウスタイル
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	//ウィンドウのメッセージ処理をする関数
	wc.lpfnWndProc		= WndProc;
	//補足バイト数
	wc.cbClsExtra		= 0L;
	wc.cbWndExtra		= 0L;
	//インスタンスハンドル
	wc.hInstance		= NULL;
	//アイコンのハンドル
	wc.hIcon			= NULL;
	//カーソルのハンドル
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	//背景カラーを指定
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	//メニューバーの名前
	wc.lpszMenuName		= MAKEINTRESOURCE( IDR_MENU1 );
	//ウィンドウクラス(this)の名前
	wc.lpszClassName	= CLASS_NAME;
	//16x16のアイコン
	wc.hIconSm			= NULL;

	//ウィンドウクラスの登録
	if ( RegisterClassEx( &wc ) == 0 ) {
		return FALSE;
	}

	//ウィンドウの生成
	_window_handle = CreateWindowEx(
		WS_EX_ACCEPTFILES,
		CLASS_NAME, TITLE_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL,
		NULL, NULL
	);

	//ウィンドウのハンドルがNULLの場合はエラー
	if ( !_window_handle ) {
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK Window::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
    switch( msg ) {
	case WM_SIZE:
		//ウィンドウサイズ変更した
		break;
	case WM_DESTROY:
		//ウィンドウを閉じた
		PostQuitMessage( 0 );
        return 0L;
	case WM_COMMAND:
		//メニューバーのコマンドを選択した
		std::shared_ptr< Editor >( Editor::getInstance( ) )->excuteCommand( hWnd, wParam );
	}
    return  DefWindowProc( hWnd, msg, wParam, lParam );
}

HWND Window::getWindowHandle( ) const {
	return _window_handle;
}