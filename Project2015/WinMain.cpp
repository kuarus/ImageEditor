#include <Windows.h>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	WNDCLASSEXW windowClass = { };
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = L"";
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);


	if ( RegisterClassExW( &windowClass ) == 0 ) {
		MessageBox( NULL, "ウィンドウの作成に失敗しました", "エラー", MB_OK );
		return GetLastError( );
	}


	// ウィンドウを生成する
	HWND windowHandle = CreateWindowEx(
		0,
		"", "",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);
	if ( windowHandle == NULL ) {
		MessageBox( NULL, "ウィンドウの作成に失敗しました", "エラー", MB_OK );
		return GetLastError( );
	}
	//SetHookWinProc( WndProc );
	return 0;
}