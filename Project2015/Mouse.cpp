#include "Mouse.h"
#include "DxLib.h"
#include "Editor.h"

std::shared_ptr< Mouse > Mouse::getTask( ) {
	return std::dynamic_pointer_cast< Mouse >( Editor::getInstance( )->getTask( Editor::TASK_MOUSE ) );
}


Mouse::Mouse( ) {
}


Mouse::~Mouse( ) {
}

void Mouse::update( ) {
	GetMousePoint( &_x, &_y );
	_wheel = GetMouseWheelRotVol( );
	int input = GetMouseInput( );
	if ( input & MOUSE_INPUT_LEFT ) {
		_button[ MOUSE_BUTTON_LEFT ]++;
	} else {
		_button[ MOUSE_BUTTON_LEFT ] = 0;
	}
	if ( input & MOUSE_INPUT_RIGHT ) {
		_button[ MOUSE_BUTTON_RIGHT ]++;
	} else {
		_button[ MOUSE_BUTTON_RIGHT ] = 0;
	}
	if ( input & MOUSE_INPUT_MIDDLE ) {
		_button[ MOUSE_BUTTON_MIDDLE ]++;
	} else {
		_button[ MOUSE_BUTTON_MIDDLE ] = 0;
	}
	if ( input & MOUSE_INPUT_4 ) {
		_button[ MOUSE_BUTTON_4 ]++;
	} else {
		_button[ MOUSE_BUTTON_4 ] = 0;
	}
	if ( input & MOUSE_INPUT_5 ) {
		_button[ MOUSE_BUTTON_5 ]++;
	} else {
		_button[ MOUSE_BUTTON_5 ] = 0;
	}
	if ( input & MOUSE_INPUT_6 ) {
		_button[ MOUSE_BUTTON_6 ]++;
	} else {
		_button[ MOUSE_BUTTON_6 ] = 0;
	}
	if ( input & MOUSE_INPUT_7 ) {
		_button[ MOUSE_BUTTON_7 ]++;
	} else {
		_button[ MOUSE_BUTTON_7 ] = 0;
	}
	if ( input & MOUSE_INPUT_8 ) {
		_button[ MOUSE_BUTTON_8 ]++;
	} else {
		_button[ MOUSE_BUTTON_8 ] = 0;
	}
}

void Mouse::getPos( int& x, int& y ) {
	x = _x;
	y = _y;
}


bool Mouse::isPushButton( MOUSE button ) {
	return ( _button[ button ] == 1 );
}
bool Mouse::isHoldButton( MOUSE button ) {
	return ( _button[ button ] > 0 );
}