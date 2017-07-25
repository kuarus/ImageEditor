#pragma once
#include <Windows.h>
#include "Task.h"

class Window : public Task {
public:
	static std::shared_ptr< Window > getTask( );
	static int MenuProc( WORD word );
public:
	Window( );
	virtual ~Window( );
public:
	void update( );
	int getScreenWidth( ) const;
	int getScreenHeight( ) const;
	HWND getWindowHandle( ) const;
private:
	int _width;
	int _height;
};

