#include "Interface.h"
#include "define.h"
#include "DxLib.h"

const int INTERFACE_WIDTH = 300;
const int INTERFACE_X = SCREEN_WIDTH - INTERFACE_WIDTH;
const int INTERFACE_COLOR = GetColor( 50, 50, 50 );


Interface::Interface( ) {
}


Interface::~Interface( ) {
}

void Interface::update( ) {

}

void Interface::draw( ) const {
	DrawBox( INTERFACE_X, 0, SCREEN_WIDTH, SCREEN_HEIGHT, INTERFACE_COLOR, TRUE );
}