#include "Window.h"
#include "DxLib.h"
#include "define.h"
#include "resource.h"
#include "Editor.h"
#include "Desk.h"

const char* CLASS_NAME = "IE";
const char* TITLE_NAME = "ImageEditor";
const std::string EXTENSION_STR[ ] {
	".png",
	".jpeg",
	".jpg"
	""
};
const int WINDOW_MIN_WIDTH = 640;
const int WINDOW_MIN_HEIGHT = 480;

std::shared_ptr< Window > Window::getTask( ) {
	return std::dynamic_pointer_cast< Window >( Editor::getInstance( )->getTask( Editor::TASK_WINDOW ) );
}


Window::Window( ) {
	//�E�B���h�E���[�h
	ChangeWindowMode( TRUE );

	//������
	SetUseXInputFlag( FALSE );

	//�E�B���h�E�X�^�C���̃Z�b�g
	SetWindowStyleMode( 7 );

	//���j���[���g��
	SetUseMenuFlag( TRUE );

	//���j���[�o�[�̃Z�b�g
	SetWindowMenu( IDR_MENU1, MenuProc );

	//�ő�`�����f�B�X�v���C�T�C�Y�ɐݒ�
	SetGraphMode( GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), 32 );

	//�E�B���h�E�̍ŏ��T�C�Y���w��
	SetWindowMinSize( WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT );

	//�E�B���h�E�T�C�Y�ɍ��킹�Ċg��k�������Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag( TRUE, FALSE );

	//�h���b�O&�h���b�v��������
	SetDragFileValidFlag( TRUE );

	//�^�C�g����ݒ�
	SetWindowText( TITLE_NAME );

	//DxLib������(������winodw���\�������)
	if ( DxLib_Init( ) == -1 ) {
		return;
	}

	//�E�B���h�E�̕\������
	MoveWindow(
		GetMainWindowHandle( ),
		( GetSystemMetrics( SM_CXSCREEN ) - WINDOW_MIN_WIDTH  ) / 2,
		( GetSystemMetrics( SM_CYSCREEN ) - WINDOW_MIN_HEIGHT ) / 2,
		WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT,
		TRUE
	);
}


Window::~Window( ) {
}

int Window::MenuProc( WORD word ) {
	switch ( word ) {
	case IDM_FILEOPEN:
	{
		OPENFILENAME ofn = { };
		//�������|��
		memset( &ofn, 0, sizeof( OPENFILENAME ) );
		//�T�C�Y���w��
		ofn.lStructSize = sizeof( OPENFILENAME ); 
		//���o�͊g���q���w��
		ofn.lpstrFilter = "PNG Files (*.png)\0*.png\0JPEG Files (*.jpeg)\0*.jpeg\0JPG Files (*.jpg)\0*.jpg\0���ׂẴt�@�C�� (*.*)\0*.*\0";
		//�f�B���N�g�����w��ANULL�Ńt���p�X
		ofn.lpstrFileTitle = NULL;
		//�����\���̃t�@�C���^�C�v( 1:png 2:jpeg 3:all )
		ofn.nFilterIndex = 1;
		//�t�@�C�����i�[�p�ϐ�
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		//�_�C�A���O����������E�B���h�E�n���h��
		ofn.hwndOwner = GetMainWindowHandle( );
		//�t�@�C�������i�[�����
		ofn.lpstrFile = ( char* )filename; 
		//�t�@�C�����̃o�b�t�@�[�T�C�Y
		ofn.nMaxFile = MAX_PATH;
		//�g���@�\�̃t���O
		ofn.Flags = OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_NONETWORKBUTTON;
		//�^�C�g���o�[�ɕ\������閼�O
		ofn.lpstrTitle = "�t�@�C�����J��";

		if ( GetOpenFileName( &ofn ) == TRUE ) {
			//�g���q�m�F
			std::string filename = ofn.lpstrFile;
			EXTENSION extention = ( EXTENSION )( ofn.nFilterIndex - 1 );
			if ( filename.find( EXTENSION_STR[ extention ], filename.size( ) - 5 ) == std::string::npos ) {
				filename += EXTENSION_STR[ extention ];
			}
			if ( !Desk::getTask( )->load( filename ) ) {
				MessageBox( NULL, "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK );
			}
		}
	}
		break;
	case IDM_FILESAVE:
	{
		OPENFILENAME ofn = { };
		//�������|��
		memset( &ofn, 0, sizeof( OPENFILENAME ) );
		//�T�C�Y���w��
		ofn.lStructSize = sizeof( OPENFILENAME ); 
		//���o�͊g���q���w��
		ofn.lpstrFilter = "PNG Files (*.png)\0*.png\0JPEG Files (*.jpeg)\0*.jpeg\0JPG Files (*.jpg)\0*.jpg\0���ׂẴt�@�C�� (*.*)\0*.*\0";
		//�f�B���N�g�����w��ANULL�Ńt���p�X
		ofn.lpstrFileTitle = NULL;
		//�����\���̃t�@�C���^�C�v( 1:png 2:jpeg 3:all )
		ofn.nFilterIndex = 1;
		//�t�@�C�����i�[�p�ϐ�
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		//�_�C�A���O����������E�B���h�E�n���h��
		ofn.hwndOwner = GetMainWindowHandle( );
		//�t�@�C�������i�[�����
		ofn.lpstrFile = ( char* )filename; 
		//�t�@�C�����̃o�b�t�@�[�T�C�Y
		ofn.nMaxFile = MAX_PATH;
		//�g���@�\�̃t���O
		ofn.Flags = OFN_ENABLESIZING | OFN_OVERWRITEPROMPT;
		//�^�C�g���o�[�ɕ\������閼�O
		ofn.lpstrTitle = "���O��t���ĕۑ�";
		if ( GetSaveFileName( &ofn ) == TRUE ) {
			//�g���q�m�F
			EXTENSION extention = ( EXTENSION )( ofn.nFilterIndex - 1 );
			std::string filename = ofn.lpstrFile;
			if ( filename.find( EXTENSION_STR[ extention ] ) == std::string::npos ) {
				filename += EXTENSION_STR[ extention ];
			}
			if ( !Desk::getTask( )->save( filename, extention ) ) {
				MessageBox( NULL, "�t�@�C���̕ۑ����s���܂���", "�G���[", MB_OK );
			}
		}
	}
		break;
	case IDM_NEWFILE:
		//�V�K�쐬���[�h�ֈڍs
		Editor::getInstance( )->setMode( Editor::MODE_CREATE );
		break;
	case IDM_EXIT:
		//�I������
		PostQuitMessage( 0 );
		break;
	}
	return TRUE;
}

void Window::update( ) {
	GetWindowSize( &_width, &_height );
}

HWND Window::getWindowHandle( ) const {
	return GetMainWindowHandle( );
}

int Window::getScreenWidth( ) const {
	return _width;
}

int Window::getScreenHeight( ) const {
	return _height;
}