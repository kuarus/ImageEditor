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
	int tmp_handle = LoadGraph( filename.c_str( ) );

	if ( tmp_handle < 0 ) {
		return false;
	}
	//�摜�T�C�Y���擾
	int width = 0;
	int height = 0;
	GetGraphSize( tmp_handle, &width, &height );
	//�`��\�̋�摜���쐬
	_handle = MakeScreen( width, height, TRUE );
	//�`��\��ɉ摜��`��
	SetDrawScreen( _handle );
	DrawGraph( 0, 0, tmp_handle, TRUE );
	SetDrawScreen( DX_SCREEN_BACK );

	//����Ȃ��Ȃ����摜���폜
	DeleteGraph( tmp_handle );

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