#include "Desk.h"
#include "Layer.h"
#include "DxLib.h"
#include "Editor.h"
#include <assert.h>
#include "Mouse.h"

const int MAX_ZOOM = 500;
const int MIN_ZOOM = 25;

std::shared_ptr< Desk > Desk::getTask( ) {
	return std::dynamic_pointer_cast< Desk >( Editor::getInstance( )->getTask( Editor::TASK_DESK ) );
}

Desk::Desk( ) :
_handle( -1 ),
_zoom( 100 ) {
	_trans_handle = LoadGraph( "Resource/trans.jpg" );
}

Desk::~Desk( ) {
}

void Desk::update( ) {
	std::shared_ptr< Mouse > mouse = Mouse::getTask( );
	int wheel = mouse->getWheel( );
	if ( wheel > 0 ) {
		_zoom += 5;
	}
	if ( wheel < 0 ) {
		_zoom -= 5;
	}
}

void Desk::draw( ) const {
	if ( _handle <= 0 ) {
		return;
	}
	{//透明(白グレーの市松)
		int width = 0;
		int height = 0;
		GetGraphSize( _trans_handle, &width, &height );
		DrawExtendGraph( 0, 0, ( int )( width * _zoom ), ( int )( height * _zoom ), _handle, TRUE );
	}
	{//レイヤーを一つの画像に対して描画
		SetDrawScreen( _handle );
		ClearDrawScreen( );
		int size = ( int )_layer.size( );
		for ( int i = 0; i < size; i++ ) {
			_layer[ i ]->draw( );
		}
		SetDrawScreen( DX_SCREEN_BACK );
	}
	{//描画対象にされた画像を描画
		int width = 0;
		int height = 0;
		GetGraphSize( _handle, &width, &height );
		DrawExtendGraph( 0, 0, width * _zoom / 100, height * _zoom / 100, _handle, TRUE );
	}
}

bool Desk::create( ) {
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

bool Desk::load( std::string filename ) {
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

bool Desk::save( std::string filename, EXTENSION extension ) const {
	if ( _handle <= 0 ) {
		return false;
	}
	int width = 0;
	int height = 0;
	GetGraphSize( _handle, &width, &height );
	bool result = false;
	switch ( extension ) {
	case EXTENSION_PNG:
		SetDrawScreen( _handle );
		SaveDrawScreenToPNG( 0, 0, width, height, filename.c_str( ) );
		SetDrawScreen( DX_SCREEN_BACK );
		result = true;
		break;
	case EXTENSION_JPEG:
		SetDrawScreen( _handle );
		SaveDrawScreenToJPEG( 0, 0, width, height, filename.c_str( ) );
		SetDrawScreen( DX_SCREEN_BACK );
		result = true;
		break;
	case ENTENSION_JPG:
		SetDrawScreen( _handle );
		SaveDrawScreenToJPEG( 0, 0, width, height, filename.c_str( ) );
		SetDrawScreen( DX_SCREEN_BACK );
		result = true;
		break;
	case EXTENSION_ALL:
		SetDrawScreen( _handle );
		SaveDrawScreen( 0, 0, width, height, filename.c_str( ) );
		SetDrawScreen( DX_SCREEN_BACK );
		result = true;
		break;
	}
	return result;
}

int Desk::getLayerSize( ) const {
	return ( int )_layer.size( );
}

std::shared_ptr< Layer > Desk::getLayer( int idx ) const {
	assert( idx >= 0 && idx < ( int )_layer.size( ) );
	return _layer[ idx ];
}
