#pragma once
#include <Windows.h>

class Window {
public:
	Window( );
	virtual ~Window( );
public:
	static LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	int create( );
	HWND getWindowHandle( ) const;
private:
	HWND _window_handle;
};

