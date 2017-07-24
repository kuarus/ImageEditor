#include "Editor.h"
#include "DxLib.h"
#include "resource.h"
#include "define.h"
#include "Window.h"
#include "Interface.h"
#include "Desk.h"
#include "Mouse.h"
#include "Keyboard.h"

std::shared_ptr< Editor > Editor::_instance;
const int WINDOW_MIN_WIDTH = 1280;
const int WINDOW_MIN_HEIGHT = 720;

const std::string EXTENSION[ ] {
	".png",
	".jpeg",
	".jpg"
	""
};

Editor::Editor( int nCmdShow ) {
	//�N���X������
	_desk = std::shared_ptr< Desk >( new Desk );
	_window = std::shared_ptr< Window >( new Window );
	_task[ TASK_MOUSE ] = std::shared_ptr< Task >( new Mouse );
	_task[ TASK_KEYBOARD ] = std::shared_ptr< Task >( new Keyboard );

	//�t�@�C�����o�͗p�n��������
	{
		_ofn = { };
		//�������|��
		memset( &_ofn, 0, sizeof( OPENFILENAME ) );
		//�T�C�Y���w��
		_ofn.lStructSize = sizeof( OPENFILENAME ); 
		//���o�͊g���q���w��
		_ofn.lpstrFilter = "PNG Files (*.png)\0*.png\0JPEG Files (*.jpeg)\0*.jpeg\0JPG Files (*.jpg)\0*.jpg\0���ׂẴt�@�C�� (*.*)\0*.*\0";
		//�f�B���N�g�����w��ANULL�Ńt���p�X
		_ofn.lpstrFileTitle = NULL;
		//�����\���̃t�@�C���^�C�v( 1:png 2:jpeg 3:all )
		_ofn.nFilterIndex = 1;
	}
	//�E�B���h�E�̐���
	if ( _window->create( ) == FALSE ) {
		MessageBox( NULL, "�E�B���h�E�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK );
		return;
	}

	//�쐬�����E�B���h�E�̃n���h�����擾
	HWND window_handle = _window->getWindowHandle( );

	//DxLib�ɃE�B���h�E��o�^
	SetUserWindow( window_handle );

	//�E�B���h�E��\��
	ShowWindow( window_handle, nCmdShow );

	//DxLib��ProsessMessage�������ŏ�������悤�ɕύX
	SetUserWindowMessageProcessDXLibFlag( FALSE );

	//�`����FULL HD�ŌŒ�
	SetGraphMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32 );

	//�E�B���h�E�̍ŏ��T�C�Y���w��
	SetWindowMinSize( WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT );

	//�����̑傫����ύX
	SetFontSize( FONT_SIZE );

	if ( DxLib_Init( ) == -1 ) {
		return;
	}

	//�E�B���h�E�̕\������
	MoveWindow( window_handle,
		( GetSystemMetrics( SM_CXSCREEN ) - WINDOW_MIN_WIDTH  ) / 2,
		( GetSystemMetrics( SM_CYSCREEN ) - WINDOW_MIN_HEIGHT ) / 2,
		WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT, TRUE );
	SetDrawScreen( DX_SCREEN_BACK );

}


Editor::~Editor( ) {
}

void Editor::initialize( int nCmdShow ) {
	if ( _instance ) {
		return;
	}
	_instance = std::shared_ptr< Editor >( new Editor( nCmdShow ) );
}

std::shared_ptr< Editor > Editor::getInstance( ) {
	return _instance;
}

std::shared_ptr< Task > Editor::getTask( TASK task ) const {
	return _task[ task ];
}


void Editor::run( ) {
	while ( isLoop( ) ) {
		//update
		updateTask( );
		_desk->update( );
		_interface->update( );
		//draw
		_desk->draw( );
		_interface->draw( );
		flip( );
	}
}

int Editor::isLoop( ) {
	if ( CheckHitKey( KEY_INPUT_ESCAPE ) != 0 ) {
		return FALSE;
	}
	//���b�Z�[�W����
	MSG msg = MSG( );
	if ( GetMessage( &msg, NULL, 0, 0 ) <= 0 ) {
		return FALSE;
	}
	TranslateMessage( &msg );
	DispatchMessage( &msg );
	return TRUE;
}

void Editor::flip( ) {
	ScreenFlip( );
	ClearDrawScreen( );
}

void Editor::excuteCommand( HWND hWnd, WPARAM wParam ) {
	switch ( wParam ) {
	case IDM_FILEOPEN:
	{
		//�t�@�C�����i�[�p�ϐ�
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		//�_�C�A���O����������E�B���h�E�n���h��
		_ofn.hwndOwner = hWnd;
		//�t�@�C�������i�[�����
		_ofn.lpstrFile = ( char* )filename; 
		//�t�@�C�����̃o�b�t�@�[�T�C�Y
		_ofn.nMaxFile = MAX_PATH;
		//�g���@�\�̃t���O
		_ofn.Flags = OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_NONETWORKBUTTON;
		//�^�C�g���o�[�ɕ\������閼�O
		_ofn.lpstrTitle = "�t�@�C�����J��";
		if ( GetOpenFileName( &_ofn ) == TRUE ) {
			//�g���q�m�F
			std::string filename = _ofn.lpstrFile;
			if ( filename.find( EXTENSION[ _ofn.nFilterIndex - 1 ] ) == std::string::npos ) {
				filename += EXTENSION[ _ofn.nFilterIndex - 1 ];
			}
			if ( !_desk->load( filename ) ) {
				MessageBox( NULL, "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK );
			}
		}
	}
		break;
	case IDM_FILESAVE:
	{
		//�t�@�C�����i�[�p�ϐ�
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		//�_�C�A���O����������E�B���h�E�n���h��
		_ofn.hwndOwner = hWnd;
		//�t�@�C�������i�[�����
		_ofn.lpstrFile = ( char* )filename; 
		//�t�@�C�����̃o�b�t�@�[�T�C�Y
		_ofn.nMaxFile = MAX_PATH;
		//�g���@�\�̃t���O
		_ofn.Flags = OFN_ENABLESIZING | OFN_OVERWRITEPROMPT;
		//�^�C�g���o�[�ɕ\������閼�O
		_ofn.lpstrTitle = "���O��t���ĕۑ�";
		if ( GetSaveFileName( &_ofn ) == TRUE ) {
			//�g���q�m�F
			std::string filename = _ofn.lpstrFile;
			if ( filename.find( EXTENSION[ _ofn.nFilterIndex - 1 ] ) == std::string::npos ) {
				filename += EXTENSION[ _ofn.nFilterIndex - 1 ];
			}
			if ( !_desk->save( filename ) ) {
				MessageBox( NULL, "�t�@�C���̕ۑ����s���܂���", "�G���[", MB_OK );
			}
		}
	}
		break;
	case IDM_MAKEFOLDER:
		break;
	case IDM_EXIT:
		//�I������
		PostQuitMessage( 0 );
		break;
	}
}


void Editor::updateTask( ) {
	for ( int i = 0; i < MAX_TASK; i++ ) {
		_task[ i ]->update( );
	}
}