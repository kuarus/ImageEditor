#include <afxdlgs.h>
#include "Window.h"
#include "resource.h"
#include "Editor.h"
#include "define.h"

const LPCWSTR CLASS_NAME = L"IE";
const char* TITLE_NAME = "ImageEditor";

Window::Window( ) {
}


Window::~Window( ) {
}

int Window::create( ) {
	WNDCLASSEXW wc = { };
	wc.cbSize			= sizeof( WNDCLASSEXW );
	wc.style			= CS_CLASSDC;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0L;
	wc.cbWndExtra		= 0L;
	wc.hInstance		= NULL;
	wc.hIcon			= NULL;
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	wc.lpszMenuName		= MAKEINTRESOURCEW( IDR_MENU1 );
	wc.lpszClassName	= CLASS_NAME;
	wc.hIconSm			= NULL;

	if ( RegisterClassExW( &wc ) == 0 ) {
		return FALSE;
	}
	_window_handle = CreateWindowExW(
		WS_EX_ACCEPTFILES,
		CLASS_NAME, LPCWSTR( ),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL,
		NULL, NULL
	);
	if ( !_window_handle ) {
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK Window::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
    switch( msg ) {
	case WM_DESTROY:
		PostQuitMessage( 0 );
        return 0L;
	case WM_COMMAND://MENU_COMMOND
		std::shared_ptr< Editor >( Editor::getInstance( ) )->excuteCommand( hWnd, wParam );
	}
    return  DefWindowProc( hWnd, msg, wParam, lParam );
}

HWND Window::getWindowHandle( ) const {
	return _window_handle;
}