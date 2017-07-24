#include "Desk.h"
#include "Work.h"


Desk::Desk( ) :
_active_work( 0 ) {
}


Desk::~Desk( ) {
}

void Desk::draw( ) const {
	int size = ( int )_work.size( );
	for ( int i = 0; i < size; i++ ) {
		_work[ i ]->draw( );
	}
}

bool Desk::load( const char* filename ) {
	//配列が小さかった場合は配列を拡張
	if ( ( int )_work.size( ) == _active_work ) {
		_work.push_back( std::shared_ptr< Work >( new Work ) );
	}

	//ポインタがNULLの場合Workを生成する。
	if ( _work[ _active_work ] == std::shared_ptr< Work >( ) ) {
		_work[ _active_work ] = std::shared_ptr< Work >( new Work );
	}

	//load
	if ( !_work[ _active_work ]->load( filename ) ) {
		return false;
	}
	return true;
}

bool Desk::save( const char* filename ) const {
	if ( !_work[ _active_work ]->save( filename ) ) {
		return false;
	}
	return true;
}