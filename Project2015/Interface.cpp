#include "Interface.h"
#include "define.h"
#include "DxLib.h"
#include "Window.h"
#include "Desk.h"
#include "Layer.h"

const int INTERFACE_WIDTH = 300;

const int LAYER_BOX_BLANK = 4;
const int LAYER_BOX_WIDTH = INTERFACE_WIDTH - LAYER_BOX_BLANK * 2;
const int LAYER_BOX_HEIGHT = 300;

const int LAYER_BLANK = 4;
const int LAYER_HEIGHT = 30;
const int LAYER_WIDTH = LAYER_BOX_WIDTH - LAYER_BLANK * 2;
//									  GetColor( Red,Blue,Green);
const unsigned int FONT_COLOR		= GetColor( 255, 255, 255 );
const unsigned int INTERFACE_COLOR	= GetColor(  50,  50,  50 );
const unsigned int LAYER_BOX_COLOR	= GetColor( 100, 100, 100 );
const unsigned int LAYER_COLOR		= GetColor( 130, 130, 130 );

Interface::Interface( ) {
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
	std::shared_ptr< Window > window = Window::getTask( );
	int screen_width = window->getScreenWidth( );
	int screen_height = window->getScreenHeight( );
	int x1 = screen_width - INTERFACE_WIDTH;
	int x2 = screen_width;
	int y1 = 0;
	int y2 = screen_height;
	DrawBox( x1, y1, x2, y2, INTERFACE_COLOR, TRUE ); 
}

void Interface::drawLayerBox( ) const {
	std::shared_ptr< Window > window = Window::getTask( );
	std::shared_ptr< Desk > desk = Desk::getTask( );
	int screen_width = window->getScreenWidth( );
	int screen_height = window->getScreenHeight( );
	{//枠作成
		int x1 = screen_width - LAYER_BOX_BLANK - LAYER_BOX_WIDTH;
		int x2 = x1 + LAYER_BOX_WIDTH;
		int y1 = screen_height - LAYER_BOX_BLANK - LAYER_BOX_HEIGHT;
		int y2 = y1 + LAYER_BOX_HEIGHT;
		DrawBox( x1, y1, x2, y2, LAYER_BOX_COLOR, TRUE );
	}
	{//レイヤー表示
		int layer_size = desk->getLayerSize( );
		int x1 = screen_width - LAYER_BOX_BLANK - LAYER_BOX_WIDTH + LAYER_BLANK;
		int x2 = x1 + LAYER_WIDTH;
		int y1 = screen_height - LAYER_BOX_BLANK - LAYER_BOX_HEIGHT + LAYER_BLANK;
		int y2 = y1 + LAYER_HEIGHT;
		DrawBox( x1, y1, x2, y2, INTERFACE_COLOR, TRUE );
		//タグ表示
		DrawString( x1 + 100, y1 + 6, "レイヤー", FONT_COLOR );
		y1 += LAYER_HEIGHT + LAYER_BLANK;
		y2 = y1 + LAYER_HEIGHT;
		//上から順に表示
		for ( int i = 0; i < layer_size; i++ ) {
			std::shared_ptr< Layer > layer = desk->getLayer( i );
			DrawBox( x1, y1, x2, y2, LAYER_COLOR, TRUE );
			DrawString( x1 + 30, y1 + 4, layer->getName( ).c_str( ), FONT_COLOR );
			y1 += LAYER_HEIGHT + LAYER_BLANK;
			y2 = y1 + LAYER_HEIGHT;
		}
	}
}