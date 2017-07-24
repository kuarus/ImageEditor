#include "Keyboard.h"
#include "Editor.h"
#include "DxLib.h"

std::shared_ptr< Keyboard > Keyboard::getTask( ) {
	return std::dynamic_pointer_cast< Keyboard >( Editor::getInstance( )->getTask( Editor::TASK_KEYBOARD ) );
}

Keyboard::Keyboard( ) {
}


Keyboard::~Keyboard( ) {
}

void Keyboard::update( ) {
	char key[ 256 ];
	GetHitKeyStateAll( key );
	for ( int i = 0; i < 256; i++ ) {
		if ( key[ i ] == TRUE ) {
			_key[ i ]++;
			if ( _key[ i ] > 200 ) {
				_key[ i ] = 100;
			}
		} else {
			_key[ i ] = 0;
		}
	}
}

bool Keyboard::isPushKey( int key ) const {
	return ( _key[ key ] == 1 );
}

bool Keyboard::isHoldKey( int key ) const {
	return ( _key[ key ] > 1 );
}