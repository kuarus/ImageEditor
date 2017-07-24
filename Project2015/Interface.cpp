#include "Interface.h"
#include "define.h"
#include "DxLib.h"

const int INTERFACE_WIDTH = 300;
const int INTERFACE_HEIGHT = SCREEN_HEIGHT;
const int INTERFACE_X = SCREEN_WIDTH - INTERFACE_WIDTH;
const int INTERFACE_Y = 0;
const unsigned int INTERFACE_COLOR = GetColor( 50, 50, 50 );

const int LAYER_BOX_WIDTH = INTERFACE_WIDTH - 8;
const int LAYER_BOX_HEIGHT = 300;
const int LAYER_BOX_X = INTERFACE_X + 4;
const int LAYER_BOX_Y = SCREEN_HEIGHT - LAYER_BOX_HEIGHT;
const unsigned int LAYER_BOX_COLOR = GetColor( 100, 100, 100 );

const unsigned int FONT_COLOR = GetColor( 255, 255, 255 );

Interface::Interface( ) {
	_handle = MakeMask( INTERFACE_WIDTH, INTERFACE_HEIGHT );
}


Interface::~Interface( ) {
}

void Interface::update( ) {

}

void Interface::draw( ) const {
	drawBG( );
	drawLayerBox( );
}

void Interface::drawBG( ) const {
	DrawBox( INTERFACE_X, INTERFACE_Y, INTERFACE_X + INTERFACE_WIDTH, INTERFACE_X + INTERFACE_HEIGHT, INTERFACE_COLOR, TRUE ); 
}

void Interface::drawLayerBox( ) const {
	DrawBox( LAYER_BOX_X, LAYER_BOX_Y, LAYER_BOX_X + LAYER_BOX_WIDTH, LAYER_BOX_X + LAYER_BOX_HEIGHT, LAYER_BOX_COLOR, TRUE ); 
	DrawBox( LAYER_BOX_X + 1, LAYER_BOX_Y + 1, LAYER_BOX_X + LAYER_BOX_WIDTH - 1, LAYER_BOX_X + 20, LAYER_BOX_COLOR, TRUE ); 
	DrawString( LAYER_BOX_X, LAYER_BOX_Y, "ÉåÉCÉÑÅ[", FONT_COLOR );
}