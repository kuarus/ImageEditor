#include "Desk.h"
#include "Work.h"


Desk::Desk( ) :
_active_work( 0 ) {
}


Desk::~Desk( ) {
}


bool Desk::load( const char* filename ) {
	if ( ( int )_work.size( ) < _active_work ) {
		return false;
	}
	if ( ( int )_work.size( ) == _active_work ) {
		_work.push_back( std::shared_ptr< Work >( new Work ) );
	}
	if ( _work[ _active_work ] == std::shared_ptr< Work >( ) ) {
		_work[ _active_work ] = std::shared_ptr< Work >( new Work );
	}
	if ( !_work[ _active_work ]->load( filename ) ) {
		return false;
	}
	return true;
}

bool Desk::save( const char* filename ) const {
	if ( ( int )_work.size( ) <= _active_work ) {
		return false;
	}
	if ( !_work[ _active_work ]->save( filename ) ) {
		return false;
	}
	return true;
}