#include "Work.h"
#include "Layer.h"


Work::Work( ) {
}


Work::~Work( ) {
}

void Work::draw( ) const {
	int size = ( int )_layer.size( );
	for ( int i = 0; i < size; i++ ) {
		_layer[ i ]->draw( );
	}
}

bool Work::load( const char* filename ) {
	//配列が小さかった場合は配列を拡張
	if ( ( int )_layer.size( ) == _active_layer ) {
		_layer.push_back( std::shared_ptr< Layer >( new Layer ) );
	}

	//ポインタがNULLの場合Layerを生成する。
	if ( _layer[ _active_layer ] == std::shared_ptr< Layer >( ) ) {
		_layer[ _active_layer ] = std::shared_ptr< Layer >( new Layer );
	}

	//load
	if ( !_layer[ _active_layer ]->load( filename ) ) {
		return false;
	}
	return true;
}

bool Work::save( const char* filename ) const {
	return false;
}