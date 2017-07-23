#include "DxLib.h"

const LPCWSTR CLASS_NAME = L"ImageEditor";
const LPCWSTR TITLE_NAME = L"ImageEditor";
const int INIT_X = 10;
const int INIT_Y = 10;
const int INIT_WIDTH = 1280;
const int INIT_HEIGHT = 720;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	WNDCLASSEXW wc = { };
	wc.cbSize			= sizeof( WNDCLASSEXW );
	wc.style			= CS_CLASSDC;
	wc.lpfnWndProc		= DefWindowProc;
	wc.cbClsExtra		= 0L;
	wc.cbWndExtra		= 0L;
	wc.hInstance		= hInstance;
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= CLASS_NAME;
	wc.hIconSm			= NULL;

	//ウィンドウクラスの登録　エラー時は0が返ってくる
	if ( RegisterClassExW( &wc ) == 0 ) {
		MessageBox( NULL, "ウィンドウの作成に失敗しました", "エラー", MB_OK );
		return GetLastError( );
	}


	// ウィンドウを生成する
	HWND window_handle = CreateWindowExW(
		WS_EX_ACCEPTFILES,
		CLASS_NAME, TITLE_NAME,
		WS_OVERLAPPEDWINDOW,
		INIT_X, INIT_Y,
		INIT_WIDTH, INIT_HEIGHT,
		NULL, NULL,
		hInstance, NULL
	);
	if ( window_handle == NULL ) {
		MessageBox( NULL, "ウィンドウの作成に失敗しました", "エラー", MB_OK );
		return GetLastError( );
	}
	ShowWindow( window_handle, nCmdShow );
	SetUserWindow( window_handle );
	SetHookWinProc( DefWindowProc );
	ChangeWindowMode( TRUE );

	if ( DxLib_Init( ) == -1 ) {
		return -1;
	}

	while ( CheckHitKey( KEY_INPUT_ESCAPE ) == 0 ) {

	}
	return 0;
}