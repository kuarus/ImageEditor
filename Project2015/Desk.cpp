#include "Desk.h"
#include "Layer.h"
#include "DxLib.h"
#include "Editor.h"
#include <assert.h>
#include "Mouse.h"
#include "Keyboard.h"

const int MAX_ZOOM = 500;
const int MIN_ZOOM = 25;
const unsigned int SELECT_COLOR = GetColor( 5, 5, 5 );

std::shared_ptr< Desk > Desk::getTask( ) {
	return std::dynamic_pointer_cast< Desk >( Editor::getInstance( )->getTask( Editor::TASK_DESK ) );
}

Desk::Desk( ) :
_handle( -1 ),
_zoom( 100 ),
_allow_value( 10 ),
_color( GetColor( 0, 0, 0 ) ),
_alpha( 255 ),
_tool( TOOL_PAINT ) {
	_trans_handle = LoadGraph( "Resource/trans.png" );
}

Desk::~Desk( ) {
}

void Desk::update( ) {
	std::shared_ptr< Mouse > mouse = Mouse::getTask( );
	std::shared_ptr< Keyboard > keyboard = Keyboard::getTask( );
	zoom( );
	if ( keyboard->isPushKey( KEY_INPUT_P ) ) {
		_tool = TOOL_PAINT;
	}
	if ( keyboard->isPushKey( KEY_INPUT_G ) ) {
		_tool = TOOL_FILL;
	}
	if ( keyboard->isPushKey( KEY_INPUT_V ) ) {
		_tool = TOOL_MOVE;
	}
	if ( keyboard->isPushKey( KEY_INPUT_M ) ) {
		_tool = TOOL_SELECT;
	}

	if ( ( int )_layer.size( ) >= _active_layer + 1 ) {
		switch ( _tool ) {
		case TOOL_PAINT:
			paint( );
			break;
		case TOOL_SELECT:
			select( );
			break;
		case TOOL_MOVE:
			break;
		case TOOL_FILL:
			if ( mouse->isPushButton( Mouse::MOUSE_BUTTON_LEFT ) ) {
				fill( );
			}
			break;
		}
	}
}

void Desk::draw( ) const {
	if ( _handle <= 0 ) {
		return;
	}
	{//����(���O���[�̎s��)
		int width = 0;
		int height = 0;
		GetGraphSize( _trans_handle, &width, &height );
		DrawExtendGraph( 0, 0, ( width * 4 * _zoom ) / 100, ( width * 4 * _zoom ) / 100, _trans_handle, TRUE );
	}
	{//���C���[����̉摜�ɑ΂��ĕ`��
		SetDrawScreen( _handle );
		ClearDrawScreen( );
		int size = ( int )_layer.size( );
		for ( int i = 0; i < size; i++ ) {
			_layer[ i ]->draw( );
		}
		SetDrawScreen( DX_SCREEN_BACK );
	}
	{//�`��Ώۂɂ��ꂽ�摜��`��
		int width = 0;
		int height = 0;
		GetGraphSize( _handle, &width, &height );
		DrawExtendGraph( 0, 0, ( width * _zoom ) / 100, ( height * _zoom ) / 100, _handle, TRUE );
	}
	drawSelect( );
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
	//�z�񂪏����������ꍇ�͔z����g��
	bool make_mask = false;
	if ( ( int )_layer.size( ) == 0 ) {
		make_mask = true;
	}
	if ( ( int )_layer.size( ) == _active_layer ) {
		_layer.push_back( std::shared_ptr< Layer >( new Layer ) );
	}

	//�|�C���^��NULL�̏ꍇLayer�𐶐�����B
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

void Desk::convertScreenPosToLayerPos( int& x, int& y ) const {
	x = ( x * 100 ) / _zoom;
	y = ( y * 100 ) / _zoom;
}


void Desk::zoom( ) {
	std::shared_ptr< Mouse > mouse = Mouse::getTask( );
	int wheel = mouse->getWheel( );
	int tmp_zoon = _zoom;
	if ( wheel > 0 ) {
		tmp_zoon += 25;
	}
	if ( wheel < 0 ) {
		tmp_zoon -= 25;
	}
	if ( tmp_zoon > MAX_ZOOM ) {
		tmp_zoon = MAX_ZOOM;
	}
	if ( tmp_zoon < MIN_ZOOM ) {
		tmp_zoon = MIN_ZOOM;
	}
	if ( tmp_zoon != _zoom ) {
		_select_start_x = ( _select_start_x * tmp_zoon ) / _zoom;
		_select_start_y = ( _select_start_y * tmp_zoon ) / _zoom;
		_select_end_x = ( _select_end_x * tmp_zoon ) / _zoom;
		_select_end_y = ( _select_end_y * tmp_zoon ) / _zoom;
		_zoom = tmp_zoon;
	}
}

void Desk::paint( ) const {
	std::shared_ptr< Mouse > mouse = Mouse::getTask( );
	//�`�������C���[�ɕύX
	SetDrawScreen( _layer[ _active_layer ]->getHandle( ) );
	if ( mouse->isPushButton( Mouse::MOUSE_BUTTON_LEFT ) ) {
		//�}�E�X���W�擾
		int x = 0;
		int y = 0;
		mouse->getPos( x, y );
		convertScreenPosToLayerPos( x, y );
		//�_��`��
		DrawPixel( x, y, _color );
	}
	if ( mouse->isHoldButton( Mouse::MOUSE_BUTTON_LEFT ) ) {
		//�}�E�X���W�擾
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;
		mouse->getOldPos( x1, y1 );
		mouse->getPos( x2, y2 );
		convertScreenPosToLayerPos( x1, y1 );
		convertScreenPosToLayerPos( x2, y2 );

		//�_(��)��`��
		DrawLine( x1, y1, x2, y2, _color );
	}
	//�`����߂�
	SetDrawScreen( DX_SCREEN_BACK );
}

void Desk::select( ) {
	std::shared_ptr< Mouse > mouse = Mouse::getTask( );
	if ( mouse->isHoldButton( Mouse::MOUSE_BUTTON_LEFT ) ) {
		int x = 0;
		int y = 0;
		mouse->getPos( x, y );
		_select_end_x = x;
		_select_end_y = y;
	}
	if ( mouse->isPushButton( Mouse::MOUSE_BUTTON_LEFT ) ) {
		int x = 0;
		int y = 0;
		mouse->getPos( x, y );
		_select_start_x = x;
		_select_start_y = y;
		_select_end_x = x;
		_select_end_y = y;
	}
}

void Desk::drawSelect( ) const {
	int x1 = _select_start_x;
	int y1 = _select_start_y;
	int x2 = _select_end_x;
	int y2 = _select_end_y;
	//convertScreenPosToLayerPos( x1, y1 );
	//convertScreenPosToLayerPos( x2, y2 );
	if ( x1 != x2 &&
		 y1 != y2 ) {
		DrawBox( x1, y1, x2, y2, SELECT_COLOR, FALSE );
	}
}

void Desk::fill( ) {
	std::shared_ptr< Mouse > mouse = Mouse::getTask( );
	//�`�������C���[�ɕύX
	SetDrawScreen( _layer[ _active_layer ]->getHandle( ) );
	//CPU�摜�ɕϊ����邽�߂̉摜��ۑ�
	int width = 0;
	int height = 0;
	GetGraphSize( _layer[ _active_layer ]->getHandle( ), &width, &height );
	SaveDrawScreenToPNG( 0, 0, width, height, "work.png" );

	//�}�E�X���W�擾
	int x = 0;
	int y = 0;
	mouse->getPos( x, y );
	convertScreenPosToLayerPos( x, y );

	//�h�b�g�P�ʂŃA�N�Z�X�ł���摜�𐻍�(CPU�p�摜)
	_si_handle = LoadSoftImage( "work.png" );
	//�F���擾(�x�[�X�J���[�ɂȂ�)
	int br = 0;
	int bg = 0;
	int bb = 0;
	int ba = 0;
	GetPixelSoftImage( _si_handle, x, y, &br, &bg, &bb, &ba );
	int base_color = GetColor( br, bg, bb );

	//�F�̋��e�l�C��
	int allow_value = _allow_value;
	int pr = 0;
	int pg = 0;
	int pb = 0;
	GetColor2( _color, &pr, &pg, &pb );

	//if ( abs( br - pr ) < allow_value ) {
	//	allow_value = abs( br - pr );
	//}
	//if ( abs( bg - pg ) < allow_value ) {
	//	allow_value = abs( bg - pg );
	//}
	//if ( abs( bb - pb ) < allow_value ) {
	//	allow_value = abs( bb - pb );
	//}

	//�h��Ԃ�
	fillAlgorithm( x, y, base_color, allow_value, width, height );

	//CPU�p�摜�����Ƃ̉摜�֕ϊ�
	//ClearDrawScreen( );
	DrawSoftImage( 0, 0, _si_handle );
	SetDrawScreen( DX_SCREEN_BACK );
	DeleteSoftImage( _si_handle );
	_si_handle = -1;
}

void Desk::fillAlgorithm( int x, int y, unsigned int base_color, int allow_value, int width, int height ) const {
	//�`��J���[
	int pr = 0;
	int pg = 0;
	int pb = 0;
	GetColor2( _color, &pr, &pg, &pb );
	//�_��`��
	if ( DrawPixelSoftImage( _si_handle, x, y, pr, pg, pb, _alpha ) == -1 ) {
		return;
	}

	//�x�[�X�J���[
	int br = 0;
	int bg = 0;
	int bb = 0;
	GetColor2( base_color, &br, &bg, &bb );

	//�擾�J���[
	int gr = 0;
	int gg = 0;
	int gb = 0;
	int ga = 0;

	//�`�F�b�N���W
	int cx = 0;
	int cy = 0;

	//��
	cx = x;
	cy = y - 1;
	if ( cx >= 0 && cx <= width && cy >= 0 && cy <= height) {
		//�x�[�X�J���[�Ǝ擾�J���[�̍��𒲂ׂ�
		GetPixelSoftImage( _si_handle, cx, cy, &gr, &gg, &gb, &ga );
		if ( pr != gr ||
			 pg != gg ||
			 pb != gb ) {
			if ( abs( br - gr ) < allow_value &&
				 abs( bg - gg ) < allow_value &&
				 abs( bb - gb ) < allow_value ) {
				//cx, cy����h��Ԃ��X�^�[�g
				fillAlgorithm( cx, cy, base_color, allow_value, width, height );
			}
		}
		if ( pr == gr &&
			 pg == gg &&
			 pb == gb ) {
			if ( ga < _alpha ) {
				//�����x�ύX
				//fillAlgorithm( cx, cy, base_color, allow_value, width, height );
			}
		}
	}

	//��
	cx = x;
	cy = y + 1;
	if ( cx >= 0 && cx <= width && cy >= 0 && cy <= height) {
		//�x�[�X�J���[�Ǝ擾�J���[�̍��𒲂ׂ�
		GetPixelSoftImage( _si_handle, cx, cy, &gr, &gg, &gb, &ga );
		if ( pr != gr ||
			 pg != gg ||
			 pb != gb ) {
			if ( abs( br - gr ) < allow_value &&
				 abs( bg - gg ) < allow_value &&
				 abs( bb - gb ) < allow_value ) {
				//cx, cy����h��Ԃ��X�^�[�g
				fillAlgorithm( cx, cy, base_color, allow_value, width, height );
			}
		}
		if ( pr == gr &&
			 pg == gg &&
			 pb == gb ) {
			if ( ga < _alpha ) {
				//�����x�ύX
				//fillAlgorithm( cx, cy, base_color, allow_value, width, height );
			}
		}
	}

	//��
	cx = x - 1;
	cy = y;	
	if ( cx >= 0 && cx <= width && cy >= 0 && cy <= height) {
		//�x�[�X�J���[�Ǝ擾�J���[�̍��𒲂ׂ�
		GetPixelSoftImage( _si_handle, cx, cy, &gr, &gg, &gb, &ga );
		if ( pr != gr ||
			 pg != gg ||
			 pb != gb ) {
			if ( abs( br - gr ) < allow_value &&
				 abs( bg - gg ) < allow_value &&
				 abs( bb - gb ) < allow_value ) {
				//cx, cy����h��Ԃ��X�^�[�g
				fillAlgorithm( cx, cy, base_color, allow_value, width, height );
			}
		}
		if ( pr == gr &&
			 pg == gg &&
			 pb == gb ) {
			if ( ga < _alpha ) {
				//�����x�ύX
				//fillAlgorithm( cx, cy, base_color, allow_value, width, height );
			}
		}
	}

	//�E
	cx = x + 1;
	cy = y;
	if ( cx >= 0 && cx <= width && cy >= 0 && cy <= height) {
		//�x�[�X�J���[�Ǝ擾�J���[�̍��𒲂ׂ�
		GetPixelSoftImage( _si_handle, cx, cy, &gr, &gg, &gb, &ga );
		if ( pr != gr ||
			 pg != gg ||
			 pb != gb ) {
			if ( abs( br - gr ) < allow_value &&
				 abs( bg - gg ) < allow_value &&
				 abs( bb - gb ) < allow_value ) {
				//cx, cy����h��Ԃ��X�^�[�g
				fillAlgorithm( cx, cy, base_color, allow_value, width, height );
			}
		}
		if ( pr == gr &&
			 pg == gg &&
			 pb == gb ) {
			if ( ga < _alpha ) {
				//�����x�ύX
				//fillAlgorithm( cx, cy, base_color, allow_value, width, height );
			}
		}
	}
}