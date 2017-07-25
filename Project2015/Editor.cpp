#include "Editor.h"
#include "DxLib.h"
#include "resource.h"
#include "define.h"
#include "Interface.h"
//Task
#include "Desk.h"
#include "Window.h"
#include "Mouse.h"
#include "Keyboard.h"

std::shared_ptr< Editor > Editor::_instance;
const int FONT_SIZE = 20;

Editor::Editor( ) :
_mode( MODE_EDIT ) {

	//�N���X������
	_task[ TASK_WINDOW ]	= std::shared_ptr< Task >( new Window );
	_task[ TASK_MOUSE ]		= std::shared_ptr< Task >( new Mouse );
	_task[ TASK_KEYBOARD ]	= std::shared_ptr< Task >( new Keyboard );
	_task[ TASK_DESK ]		= std::shared_ptr< Task >( new Desk );


	_interface = std::shared_ptr< Interface >( new Interface );

	//�`��ꏊ��ݒ�
	SetDrawScreen( DX_SCREEN_BACK );

	//�g�k���@�ύX
	SetDrawMode( DX_DRAWMODE_NEAREST );

	//�����T�C�Y�ݒ�
	SetFontSize( FONT_SIZE );
}


Editor::~Editor( ) {
}

void Editor::initialize( ) {
	//�|�C���^����
	if ( _instance ) {
		return;
	}
	_instance = std::shared_ptr< Editor >( new Editor );
}

std::shared_ptr< Editor > Editor::getInstance( ) {
	return _instance;
}

std::shared_ptr< Task > Editor::getTask( TASK task ) const {
	return _task[ task ];
}

void Editor::run( ) {
	while ( isLoop( ) ) {
		update( );
	}
	DxLib_End( );
}


int Editor::isLoop( ) {
	if ( CheckHitKey( KEY_INPUT_ESCAPE ) != 0 ) {
		return FALSE;
	}
	if ( ProcessMessage( ) != 0 ) {
		return FALSE;
	}
	return TRUE;
}

void Editor::update( ) {
	_interface->update( );
	for ( int i = 0; i < MAX_TASK; i++ ) {
		_task[ i ]->update( );
	}
	std::dynamic_pointer_cast< Desk >( _task[ TASK_DESK ] )->draw( );
	_interface->draw( );
	flip( );
}

void Editor::flip( ) {
	ScreenFlip( );
	ClearDrawScreen( );
}

void Editor::setMode( MODE mode ) {
	_mode = mode;
}

Editor::MODE Editor::getMode( ) const {
	return _mode;
}