#pragma once
#include <Windows.h>
#include <memory>
#include <array>

class Window;
class Interface;
class Desk;
class Task;

class Editor {
public:
	enum TASK {
		TASK_MOUSE,
		TASK_KEYBOARD,
		MAX_TASK
	};
public:
	Editor( int nCmdShow );
	virtual ~Editor( );
public:
	static void initialize( int nCmdShow );
	static std::shared_ptr< Editor > getInstance( );
public:
	std::shared_ptr< Task > getTask( TASK task ) const;
	void run( );
	void excuteCommand( HWND hWnd, WPARAM wParam );
private:
	int isLoop( );
	void flip( );
	void updateTask( );
private:
	static std::shared_ptr< Editor > _instance;
private:
	std::shared_ptr< Desk > _desk;
	std::shared_ptr< Window > _window;
	std::shared_ptr< Interface > _interface;
	std::array< std::shared_ptr< Task >, MAX_TASK > _task;
	OPENFILENAME _ofn;
};

