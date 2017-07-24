#include "Editor.h"
#include "DxLib.h"
#include "resource.h"
#include "define.h"
#include "Window.h"
#include "Interface.h"
#include "Desk.h"

std::shared_ptr< Editor > Editor::_instance;

Editor::Editor( int nCmdShow ) {
	{//ofn
		_ofn = { };
		memset( &_ofn, 0, sizeof( OPENFILENAME ) );
		_ofn.lStructSize = sizeof(OPENFILENAME); 
		_ofn.lpstrFilter = "PNG files (*.png)\0*.png\0JPEG Files (*.jpg;*.jpeg)\0*.jpg; *.jpeg\0";
	}
	_desk = std::shared_ptr< Desk >( new Desk );
	_window = std::shared_ptr< Window >( new Window );
	if ( _window->create( ) == FALSE ) {
		MessageBox( NULL, "ウィンドウの作成に失敗しました", "エラー", MB_OK );
		return;
	}
	SetUserWindow( _window->getWindowHandle( ) );
	ShowWindow( _window->getWindowHandle( ), nCmdShow );
	//SetWindowTextW( _window->getWindowHandle( ), L"AAA" ); なぜか一文字しか表示されないため保留
	SetGraphMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32 );
	if ( DxLib_Init( ) == -1 ) {
		return;
	}
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

void Editor::run( ) {
	while ( isLoop( ) ) {
		_interface->update( );
		_desk->draw( );
		_interface->draw( );
		flip( );
	}
}

int Editor::isLoop( ) {
	if ( CheckHitKey( KEY_INPUT_ESCAPE ) != 0 ) {
		return FALSE;
	}
	MSG msg = MSG( );
	//msg.hwnd = _window->getWindowHandle( );
	if ( GetMessage( &msg, NULL, 0, 0 ) <= 0 ) {
		return FALSE;
	}
	TranslateMessage( &msg );
	DispatchMessage( &msg );
	//if ( ProcessMessage( ) != 0 ) {
	//	return FALSE;
	//}
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
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		_ofn.hwndOwner = hWnd;
		_ofn.lpstrFileTitle = NULL;
		_ofn.lpstrFile = ( char* )filename; 
		_ofn.nFilterIndex = 1;
		_ofn.nMaxFile = MAX_PATH;
		_ofn.Flags = TRUE;
		_ofn.lpstrDefExt = "png";
		_ofn.lpstrTitle = "ファイルを開く";
		if ( GetOpenFileName( &_ofn ) == TRUE ) {
			if ( !_desk->load( _ofn.lpstrFile ) ) {
				MessageBox( NULL, "ファイルの読み込みに失敗しました", "エラー", MB_OK );
			}
		}
	}
		break;
	case IDM_FILESAVE:
	{
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		_ofn.hwndOwner = hWnd;
		_ofn.lpstrFile = ( char* )filename; 
		_ofn.nMaxFile = MAX_PATH;
		_ofn.Flags = TRUE;    
		_ofn.lpstrDefExt = "png";
		_ofn.lpstrTitle = "名前を付けて保存";
		if ( GetSaveFileName( &_ofn ) == TRUE ) {
			if ( !_desk->save( _ofn.lpstrFile ) ) {
				MessageBox( NULL, "ファイルの読み込みに失敗しました", "エラー", MB_OK );
			}
		}
	}
		break;
	case IDM_MAKEFOLDER:
		break;
	case IDM_EXIT:
		PostQuitMessage( 0 );
		break;
	}
}
