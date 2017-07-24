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
	//クラス初期化
	_desk = std::shared_ptr< Desk >( new Desk );
	_window = std::shared_ptr< Window >( new Window );
	_task[ TASK_MOUSE ] = std::shared_ptr< Task >( new Mouse );
	_task[ TASK_KEYBOARD ] = std::shared_ptr< Task >( new Keyboard );

	//ファイル入出力用系統初期化
	{
		_ofn = { };
		//メモリ掃除
		memset( &_ofn, 0, sizeof( OPENFILENAME ) );
		//サイズを指定
		_ofn.lStructSize = sizeof( OPENFILENAME ); 
		//入出力拡張子を指定
		_ofn.lpstrFilter = "PNG Files (*.png)\0*.png\0JPEG Files (*.jpeg)\0*.jpeg\0JPG Files (*.jpg)\0*.jpg\0すべてのファイル (*.*)\0*.*\0";
		//ディレクトリを指定、NULLでフルパス
		_ofn.lpstrFileTitle = NULL;
		//初期表示のファイルタイプ( 1:png 2:jpeg 3:all )
		_ofn.nFilterIndex = 1;
	}
	//ウィンドウの生成
	if ( _window->create( ) == FALSE ) {
		MessageBox( NULL, "ウィンドウの作成に失敗しました", "エラー", MB_OK );
		return;
	}

	//作成したウィンドウのハンドルを取得
	HWND window_handle = _window->getWindowHandle( );

	//DxLibにウィンドウを登録
	SetUserWindow( window_handle );

	//ウィンドウを表示
	ShowWindow( window_handle, nCmdShow );

	//DxLibのProsessMessageを自分で処理するように変更
	SetUserWindowMessageProcessDXLibFlag( FALSE );

	//描画域をFULL HDで固定
	SetGraphMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32 );

	//ウィンドウの最小サイズを指定
	SetWindowMinSize( WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT );

	//文字の大きさを変更
	SetFontSize( FONT_SIZE );

	if ( DxLib_Init( ) == -1 ) {
		return;
	}

	//ウィンドウの表示調整
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
	//メッセージ処理
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
		//ファイル名格納用変数
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		//ダイアログを所持するウィンドウハンドル
		_ofn.hwndOwner = hWnd;
		//ファイル名が格納される
		_ofn.lpstrFile = ( char* )filename; 
		//ファイル名のバッファーサイズ
		_ofn.nMaxFile = MAX_PATH;
		//拡張機能のフラグ
		_ofn.Flags = OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_NONETWORKBUTTON;
		//タイトルバーに表示される名前
		_ofn.lpstrTitle = "ファイルを開く";
		if ( GetOpenFileName( &_ofn ) == TRUE ) {
			//拡張子確認
			std::string filename = _ofn.lpstrFile;
			if ( filename.find( EXTENSION[ _ofn.nFilterIndex - 1 ] ) == std::string::npos ) {
				filename += EXTENSION[ _ofn.nFilterIndex - 1 ];
			}
			if ( !_desk->load( filename ) ) {
				MessageBox( NULL, "ファイルの読み込みに失敗しました", "エラー", MB_OK );
			}
		}
	}
		break;
	case IDM_FILESAVE:
	{
		//ファイル名格納用変数
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		//ダイアログを所持するウィンドウハンドル
		_ofn.hwndOwner = hWnd;
		//ファイル名が格納される
		_ofn.lpstrFile = ( char* )filename; 
		//ファイル名のバッファーサイズ
		_ofn.nMaxFile = MAX_PATH;
		//拡張機能のフラグ
		_ofn.Flags = OFN_ENABLESIZING | OFN_OVERWRITEPROMPT;
		//タイトルバーに表示される名前
		_ofn.lpstrTitle = "名前を付けて保存";
		if ( GetSaveFileName( &_ofn ) == TRUE ) {
			//拡張子確認
			std::string filename = _ofn.lpstrFile;
			if ( filename.find( EXTENSION[ _ofn.nFilterIndex - 1 ] ) == std::string::npos ) {
				filename += EXTENSION[ _ofn.nFilterIndex - 1 ];
			}
			if ( !_desk->save( filename ) ) {
				MessageBox( NULL, "ファイルの保存失敗しました", "エラー", MB_OK );
			}
		}
	}
		break;
	case IDM_MAKEFOLDER:
		break;
	case IDM_EXIT:
		//終了処理
		PostQuitMessage( 0 );
		break;
	}
}


void Editor::updateTask( ) {
	for ( int i = 0; i < MAX_TASK; i++ ) {
		_task[ i ]->update( );
	}
}