#pragma once
#include <Windows.h>
#include <memory>
#include <array>

class Task;
class Desk;
class Window;
class Interface;

class Editor {
public:
	enum MODE {
		MODE_EDIT,
		MODE_CREATE,
		MAX_MODE
	};
	enum TASK {
		TASK_MOUSE,
		TASK_KEYBOARD,
		TASK_DESK,
		TASK_WINDOW,
		MAX_TASK
	};
public:
	Editor( );
	virtual ~Editor( );
public:
	static void initialize( );
	static std::shared_ptr< Editor > getInstance( );
public:
	void setMode( MODE mode );
	MODE getMode( ) const;
	std::shared_ptr< Task > getTask( TASK task ) const;
	void run( );
private:
	int isLoop( );
	void flip( );
	void update( );
private:
	static std::shared_ptr< Editor > _instance;
private:
	MODE _mode;
	std::array< std::shared_ptr< Task >, MAX_TASK > _task;
	std::shared_ptr< Interface > _interface;
};

