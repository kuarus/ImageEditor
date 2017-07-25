#include "Layer.h"
#include "DxLib.h"


Layer::Layer( ) :
_handle( -1 ),
_eye( true ),
_name( "���C���[" ) {
}


Layer::~Layer( ) {
}

void Layer::draw( ) const {
	if ( !_eye ) {
		return;
	}
	DrawGraph( 0, 0, _handle, TRUE );
}

bool Layer::load( std::string filename ) {
	if ( _handle < 0 ) {
		DeleteGraph( _handle );
	}
	_handle = LoadGraph( filename.c_str( ) );

	if ( _handle < 0 ) {
		return false;
	}
	size_t find_pos = filename.find_last_of( "/" );
	if ( find_pos == std::string::npos ) {
		find_pos = filename.find_last_of( "\\" );
	}
	_name = filename.substr( find_pos + 1, filename.size( ) );
	return true;
}

int Layer::getHandle( ) const {
	return _handle;
}

void Layer::create( int width, int height ) {
	if ( _handle >= 0 ) {
		DeleteGraph( _handle );
	}
	_handle = MakeScreen( width, height, TRUE );
}

std::string Layer::getName( ) const {
	return _name;
}