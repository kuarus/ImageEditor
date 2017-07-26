#pragma once
#include "Task.h"
#include <array>

class Mouse : public Task {
public:
	static std::shared_ptr< Mouse > getTask( );
public:
	enum MOUSE {
		MOUSE_BUTTON_LEFT,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_MIDDLE,
		MOUSE_BUTTON_4,
		MOUSE_BUTTON_5,
		MOUSE_BUTTON_6,
		MOUSE_BUTTON_7,
		MOUSE_BUTTON_8,
		MAX_MOUSE
	};
public:
	Mouse( );
	virtual ~Mouse( );
public:
	void update( );
	void getPos( int& x, int& y ) const;
	void getOldPos( int& x, int& y ) const;
	int getWheel( ) const;
	bool isPushButton( MOUSE button ) const;
	bool isHoldButton( MOUSE button ) const;
private:
	int _x;
	int _y;
	int _old_x;
	int _old_y;
	int _wheel;
	std::array< char, MAX_MOUSE > _button;
};

