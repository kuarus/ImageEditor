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

void Layer::fill( int x, int y, unsigned int base_color, unsigned int paint_color, int allow_value ) {
	//�_��`��
	DrawPixel( x, y, paint_color );

	//�x�[�X�J���[
	int br = 0;
	int bg = 0;
	int bb = 0;
	GetColor2( base_color, &br, &bg, &bb );

	//�擾�J���[
	int gr = 0;
	int gg = 0;
	int gb = 0;

	//�`�F�b�N���W
	int cx = 0;
	int cy = 0;

	//�摜�T�C�Y
	int width = 0;
	int height = 0;
	GetGraphSize( _handle, &width, &height );

	//��
	cx = x;
	cy = y - 1;
	if ( x >= 0 && x <= width && y >= 0 && y <= height) {
		//�x�[�X�J���[�Ǝ擾�J���[�̍��𒲂ׂ�
		GetColor2( GetPixel( cx, cy ), &gr, &gg, &gb );
		if ( abs( br - gr ) < allow_value &&
			 abs( bg - gg ) < allow_value &&
			 abs( bb - gb ) < allow_value ) {
			//cx, cy����h��Ԃ��X�^�[�g
			fill( cx, cy, base_color, paint_color, allow_value );
		}
	}

	//��
	cx = x;
	cy = y + 1;
	if ( x >= 0 && x <= width && y >= 0 && y <= height) {
		//�x�[�X�J���[�Ǝ擾�J���[�̍��𒲂ׂ�
		GetColor2( GetPixel( cx, cy ), &gr, &gg, &gb );
		if ( abs( br - gr ) < allow_value &&
			 abs( bg - gg ) < allow_value &&
			 abs( bb - gb ) < allow_value ) {
			//cx, cy����h��Ԃ��X�^�[�g
			fill( cx, cy, base_color, paint_color, allow_value );
		}
	}

	//��
	cx = x - 1;
	cy = y;	
	if ( x >= 0 && x <= width && y >= 0 && y <= height) {
		//�x�[�X�J���[�Ǝ擾�J���[�̍��𒲂ׂ�
		GetColor2( GetPixel( cx, cy ), &gr, &gg, &gb );
		if ( abs( br - gr ) < allow_value &&
			 abs( bg - gg ) < allow_value &&
			 abs( bb - gb ) < allow_value ) {
			//cx, cy����h��Ԃ��X�^�[�g
			fill( cx, cy, base_color, paint_color, allow_value );
		}
	}

	//�E
	cx = x + 1;
	cy = y;
	if ( x >= 0 && x <= width && y >= 0 && y <= height) {
		//�x�[�X�J���[�Ǝ擾�J���[�̍��𒲂ׂ�
		GetColor2( GetPixel( cx, cy ), &gr, &gg, &gb );
		if ( abs( br - gr ) < allow_value &&
			 abs( bg - gg ) < allow_value &&
			 abs( bb - gb ) < allow_value ) {
			//cx, cy����h��Ԃ��X�^�[�g
			fill( cx, cy, base_color, paint_color, allow_value );
		}
	}
}

int Layer::getColor( int x, int y ) const {
	return GetPixel( x, y );
}