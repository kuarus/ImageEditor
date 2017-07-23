#include "DxLib.h"
#include "resource.h"

const LPCWSTR CLASS_NAME = L"ImageEditor";
const char* TITLE_NAME = "ImageEditor";
const int INIT_X = 10;
const int INIT_Y = 10;
const int INIT_WIDTH = 1280;
const int INIT_HEIGHT = 720;

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
int createWindow( HWND* hWnd, HINSTANCE hInstance );
int processMessage( HWND hWnd, int nCmdShow );


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	//MAKEINTRESOURCE( IDR_MENU1 );
	// ウィンドウを生成する
	HWND hWnd = NULL;
	if ( createWindow( &hWnd, hInstance ) == FALSE ) {
		MessageBox( NULL, "ウィンドウの作成に失敗しました", "エラー", MB_OK );
		return GetLastError( );
	}
	DxLib::SetUserWindow( hWnd );
	ShowWindow( hWnd, nCmdShow );
	if ( DxLib_Init( ) == -1 ) {
		return -1;
	}
	SetDrawScreen( DX_SCREEN_BACK );
	int x = 0;
	int y = 0;
	while ( processMessage( hWnd, nCmdShow ) == TRUE ) {
		if ( CheckHitKey( KEY_INPUT_A ) != 0 ) {
			int check = 0;
		}
		ClearDrawScreen( );
		x++;
		y++;
		DrawBox( 0, 0, x, y, GetColor( 100, 0, 0 ), TRUE );
		ScreenFlip( );
	}
	return 0;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	/*
	HDC hdc;
    PAINTSTRUCT ps;
    static COLORREF color = RGB( 0, 0, 0 );
	static int x = 0;
	static int y = 0;
    //渡された message から、イベントの種類を解析する
    switch( msg ){
    case WM_CREATE:
        color = RGB( 0, 0, 0 );            //最初は黒色
        x = 50;
        y = 50;
        break;
    case WM_KEYDOWN:
        switch(wParam){
        case 'R':
            color = RGB( 255, 0, 128 );    //'R' red 赤色
            break;
        case 'B':
            color = RGB( 0, 128, 255 );    //'B' blue 青色
            break;
        case VK_RIGHT: if(x<100) x++; break;
        case VK_LEFT:  if(x>  0) x--; break;
        case VK_DOWN:  if(y<100) y++; break;
        case VK_UP:    if(y>  0) y--; break;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
        break;
    //----ペイント----
    case WM_PAINT:
        hdc= BeginPaint (hWnd, &ps);
        SetTextColor(hdc, color);
		//SetPixel( hdc, x, y, color );
        TextOut( hdc, x, y, "使用例 sample", 13 );
        EndPaint(hWnd, &ps);
        break;
    //----終了処理----
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0L;
    }
	*/
    //デフォルトの処理
    return  DefWindowProc(hWnd,msg,wParam,lParam);
}

int createWindow( HWND* hWnd, HINSTANCE hInstance ) {
	WNDCLASSEXW wc = { };
	wc.cbSize			= sizeof( WNDCLASSEXW );
	wc.style			= CS_CLASSDC;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0L;
	wc.cbWndExtra		= 0L;
	wc.hInstance		= hInstance;
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName		= MAKEINTRESOURCEW( IDR_MENU1 );
	wc.lpszClassName	= CLASS_NAME;
	wc.hIconSm			= NULL;

	if ( RegisterClassExW( &wc ) == 0 ) {
		return FALSE;
	}
	*hWnd = CreateWindowExW(
		WS_EX_ACCEPTFILES,
		CLASS_NAME, LPCWSTR( ),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hInstance, NULL
	);
	if ( !*hWnd ) {
		return FALSE;
	}
	return TRUE;
}


int processMessage( HWND hWnd, int nCmdShow ) {
	if ( CheckHitKey( KEY_INPUT_ESCAPE ) != 0 ) {
		return FALSE;
	}
	if ( ProcessMessage( ) != 0 ) {
		return FALSE;
	}
	MSG Msg = MSG( );
	if ( !GetMessage( &Msg, NULL, 0, 0 ) ) {
		return FALSE;
	}
	return TRUE;
}