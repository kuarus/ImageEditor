#pragma once
#include <Windows.h>
#include <memory>

class Window;
class Interface;
class Desk;

class Editor {
public:
	Editor( int nCmdShow );
	virtual ~Editor( );
public:
	static void initialize( int nCmdShow );
	static std::shared_ptr< Editor > getInstance( );
public:
	void run( );
	void excuteCommand( HWND hWnd, WPARAM wParam );
private:
	int isLoop( );
	void flip( );
private:
	static std::shared_ptr< Editor > _instance;
private:
	std::shared_ptr< Desk > _desk;
	std::shared_ptr< Window > _window;
	std::shared_ptr< Interface > _interface;
	OPENFILENAME _ofn;
};

