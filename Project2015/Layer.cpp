#include "Layer.h"
#include "DxLib.h"


Layer::Layer( ) :
_handle( -1 ),
_eye( true ) {
}


Layer::~Layer( ) {
}

void Layer::draw( ) const {
	if ( !_eye ) {
		return;
	}
	DrawGraph( 0, 0, _handle, TRUE );
}

bool Layer::load( const char* filename ) {
	if ( _handle < 0 ) {
		DeleteGraph( _handle );
	}
	_handle = LoadGraph( filename );
	if ( _handle < 0 ) {
		return false;
	}
	return true;
}
