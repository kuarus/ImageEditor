#include "Work.h"
#include "Layer.h"


Work::Work( ) {
}


Work::~Work( ) {
}

bool Work::load( const char* filename ) {
	if ( ( int )_layer.size( ) < _active_layer ) {
		return false;
	}
	if ( ( int )_layer.size( ) == _active_layer ) {
		_layer.push_back( std::shared_ptr< Layer >( new Layer ) );
	}
	if ( _layer[ _active_layer ] == std::shared_ptr< Layer >( ) ) {
		_layer[ _active_layer ] = std::shared_ptr< Layer >( new Layer );
	}
	if ( !_layer[ _active_layer ]->load( filename ) ) {
		return false;
	}
	return true;
}

bool Work::save( const char* filename ) const {
	return false;
}