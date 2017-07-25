#include "Creator.h"



Creator::Creator( ) {
}


Creator::~Creator( ) {
}

bool Creator::update( ) {
	/*
	std::shared_ptr< Keyboard > keyboard = Keyboard::getTask( );
	std::shared_ptr< Mouse > mouse = Mouse::getTask( );
	std::string width = "0";
	std::string height = "0";
	bool input_width = true;
	while ( TRUE ) {
		DrawBox( SIZE_CHECK_X, SIZE_CHECK_Y, SIZE_CHECK_X + SIZE_CHECK_WIDTH, SIZE_CHECK_Y + SIZE_CHECK_HEIGHT, SIZE_CHECK_COLOR, TRUE );
		DrawBox( SIZE_CHECK_X, SIZE_CHECK_Y, SIZE_CHECK_X + SIZE_CHECK_WIDTH, SIZE_CHECK_Y + SIZE_CHECK_BAR_HEIGHT, SIZE_CHECK_BAR_COLOR, TRUE );
		DrawBox( SIZE_WIDTH_CHECK_X, SIZE_WIDTH_CHECK_Y, SIZE_WIDTH_CHECK_X + SIZE_CHECK_BOX_WIDTH, SIZE_WIDTH_CHECK_Y + SIZE_CHECK_BOX_HEIGHT, SIZE_CHECK_BOX_COLOR, TRUE );
		DrawBox( SIZE_HEIGHT_CHECK_X, SIZE_WIDTH_CHECK_Y, SIZE_HEIGHT_CHECK_X + SIZE_CHECK_BOX_WIDTH, SIZE_HEIGHT_CHECK_Y + SIZE_CHECK_BOX_HEIGHT, SIZE_CHECK_BOX_COLOR, TRUE );
		DrawString( SIZE_WIDTH_CHECK_X, SIZE_WIDTH_CHECK_Y, width.c_str( ), FONT_COLOR );
		DrawString( SIZE_HEIGHT_CHECK_X, SIZE_WIDTH_CHECK_Y, height.c_str( ), FONT_COLOR );
		int x = 0;
		int y = 0;
		mouse->getPos( x, y );
		if ( SIZE_WIDTH_CHECK_X < x &&  SIZE_WIDTH_CHECK_X + SIZE_CHECK_BOX_WIDTH  > x &&
			 SIZE_WIDTH_CHECK_Y < y &&  SIZE_WIDTH_CHECK_Y + SIZE_CHECK_BOX_HEIGHT > y ) {
			input_width = true;
		}
		if ( SIZE_HEIGHT_CHECK_X < x &&  SIZE_HEIGHT_CHECK_X + SIZE_CHECK_BOX_WIDTH  > x &&
			 SIZE_HEIGHT_CHECK_Y < y &&  SIZE_HEIGHT_CHECK_Y + SIZE_CHECK_BOX_HEIGHT > y ) {
			input_width = false;
		}
		char input = GetInputChar( FALSE );
		if ( input == 0 ) {
			continue;
		}
		if ( input == CTRL_CODE_CR ) {
			break;		
		} else {
			if ( input_width ) {
				if ( input == CTRL_CODE_BS ) {
					if( width.size( ) != 0 ) {
						width.pop_back( );
					}
				} else {
					if ( input >= '0' && input <= '9' ) {
						width += input;
					}
				}
			} else {
				if ( input == CTRL_CODE_BS ) {
					if( height.size( ) != 0 ) {
						height.pop_back( );
					}
				} else {
					if ( input >= '0' && input <= '9' ) {
						height += input;
					}
				}
			}
		}

		ClearDrawScreen( );
		ScreenFlip( );
	}
	*/
	return true;
}