#include "Layer.h"
#include "DxLib.h"


Layer::Layer( ) :
_handle( -1 ) {
}


Layer::~Layer( ) {
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
