#include "Work.h"
#include "Layer.h"
#include "DxLib.h"

Work::Work( ) :
_handle( -1 ),
_zoom( 1.0 ) {
}


Work::~Work( ) {
}

void Work::update( ) {

}

void Work::draw( ) const {
	if ( _handle <= 0 ) {
		return;
	}
	SetDrawScreen( _handle );
	ClearDrawScreen( );
	int size = ( int )_layer.size( );
	for ( int i = 0; i < size; i++ ) {
		_layer[ i ]->draw( );
	}
	SetDrawScreen( DX_SCREEN_BACK );
	int width = 0;
	int height = 0;
	GetGraphSize( _handle, &width, &height );
	DrawExtendGraph( 0, 0, ( int )( width * _zoom ), ( int )( height * _zoom ), _handle, TRUE );
}

bool Work::create( ) {
	if ( _handle >= 0 ) {
		DeleteGraph( _handle );
	}
	int width = 512;
	int height = 512;
	_handle = MakeScreen( width, height, TRUE );
	_layer = { };
	_layer.push_back( std::shared_ptr< Layer >( new Layer ) );
	_layer[ 0 ]->create( width, height );
	return true;
}

bool Work::load( std::string filename ) {
	//配列が小さかった場合は配列を拡張
	bool make_mask = false;
	if ( ( int )_layer.size( ) == 0 ) {
		make_mask = true;
	}
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
	if ( make_mask ) {
		int handle = _layer[ _active_layer ]->getHandle( );
		int width = 0;
		int height = 0;
		GetGraphTextureSize( handle, &width, &height );
		_handle = MakeScreen( width, height, TRUE );
	}
	return true;
}

bool Work::save( std::string filename ) const {
	if ( _handle <= 0 ) {
		return false;
	}
	int width = 0;
	int height = 0;
	GetGraphSize( _handle, &width, &height );
	if ( filename.find( ".png" ) != std::string::npos ) {
		SetDrawScreen( _handle );
		SaveDrawScreenToPNG( 0, 0, width, height, filename.c_str( ) );
		SetDrawScreen( DX_SCREEN_BACK );
		return true;
	}
	if ( filename.find( ".jpeg" ) != std::string::npos ) {
		SetDrawScreen( _handle );
		SaveDrawScreenToJPEG( 0, 0, width, height, filename.c_str( ) );
		SetDrawScreen( DX_SCREEN_BACK );
		return true;
	}
	if ( filename.find( ".jpg" ) != std::string::npos ) {
		SetDrawScreen( _handle );
		SaveDrawScreenToJPEG( 0, 0, width, height, filename.c_str( ) );
		SetDrawScreen( DX_SCREEN_BACK );
		return true;
	}
	return false;
}