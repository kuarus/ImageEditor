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
	//ウィンドウモード
	ChangeWindowMode( TRUE );

	//高速化
	SetUseXInputFlag( FALSE );

	//ウィンドウスタイルのセット
	SetWindowStyleMode( 7 );

	//メニューを使う
	SetUseMenuFlag( TRUE );

	//メニューバーのセット
	SetWindowMenu( IDR_MENU1, MenuProc );

	//最大描画域をディスプレイサイズに設定
	SetGraphMode( GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), 32 );

	//ウィンドウの最小サイズを指定
	SetWindowMinSize( WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT );

	//ウィンドウサイズに合わせて拡大縮小をしないようにする
	SetWindowSizeChangeEnableFlag( TRUE, FALSE );

	//ドラッグ&ドロップを許可する
	SetDragFileValidFlag( TRUE );

	//タイトルを設定
	SetWindowText( TITLE_NAME );

	//DxLib初期化(ここでwinodwが表示される)
	if ( DxLib_Init( ) == -1 ) {
		return;
	}

	//ウィンドウの表示調整
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
		//メモリ掃除
		memset( &ofn, 0, sizeof( OPENFILENAME ) );
		//サイズを指定
		ofn.lStructSize = sizeof( OPENFILENAME ); 
		//入出力拡張子を指定
		ofn.lpstrFilter = "PNG Files (*.png)\0*.png\0JPEG Files (*.jpeg)\0*.jpeg\0JPG Files (*.jpg)\0*.jpg\0すべてのファイル (*.*)\0*.*\0";
		//ディレクトリを指定、NULLでフルパス
		ofn.lpstrFileTitle = NULL;
		//初期表示のファイルタイプ( 1:png 2:jpeg 3:all )
		ofn.nFilterIndex = 1;
		//ファイル名格納用変数
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		//ダイアログを所持するウィンドウハンドル
		ofn.hwndOwner = GetMainWindowHandle( );
		//ファイル名が格納される
		ofn.lpstrFile = ( char* )filename; 
		//ファイル名のバッファーサイズ
		ofn.nMaxFile = MAX_PATH;
		//拡張機能のフラグ
		ofn.Flags = OFN_CREATEPROMPT | OFN_ENABLESIZING | OFN_NONETWORKBUTTON;
		//タイトルバーに表示される名前
		ofn.lpstrTitle = "ファイルを開く";

		if ( GetOpenFileName( &ofn ) == TRUE ) {
			//拡張子確認
			std::string filename = ofn.lpstrFile;
			EXTENSION extention = ( EXTENSION )( ofn.nFilterIndex - 1 );
			if ( filename.find( EXTENSION_STR[ extention ], filename.size( ) - 5 ) == std::string::npos ) {
				filename += EXTENSION_STR[ extention ];
			}
			if ( !Desk::getTask( )->load( filename ) ) {
				MessageBox( NULL, "ファイルの読み込みに失敗しました", "エラー", MB_OK );
			}
		}
	}
		break;
	case IDM_FILESAVE:
	{
		OPENFILENAME ofn = { };
		//メモリ掃除
		memset( &ofn, 0, sizeof( OPENFILENAME ) );
		//サイズを指定
		ofn.lStructSize = sizeof( OPENFILENAME ); 
		//入出力拡張子を指定
		ofn.lpstrFilter = "PNG Files (*.png)\0*.png\0JPEG Files (*.jpeg)\0*.jpeg\0JPG Files (*.jpg)\0*.jpg\0すべてのファイル (*.*)\0*.*\0";
		//ディレクトリを指定、NULLでフルパス
		ofn.lpstrFileTitle = NULL;
		//初期表示のファイルタイプ( 1:png 2:jpeg 3:all )
		ofn.nFilterIndex = 1;
		//ファイル名格納用変数
		char filename[ MAX_PATH ];
		ZeroMemory( filename, MAX_PATH );
		//ダイアログを所持するウィンドウハンドル
		ofn.hwndOwner = GetMainWindowHandle( );
		//ファイル名が格納される
		ofn.lpstrFile = ( char* )filename; 
		//ファイル名のバッファーサイズ
		ofn.nMaxFile = MAX_PATH;
		//拡張機能のフラグ
		ofn.Flags = OFN_ENABLESIZING | OFN_OVERWRITEPROMPT;
		//タイトルバーに表示される名前
		ofn.lpstrTitle = "名前を付けて保存";
		if ( GetSaveFileName( &ofn ) == TRUE ) {
			//拡張子確認
			EXTENSION extention = ( EXTENSION )( ofn.nFilterIndex - 1 );
			std::string filename = ofn.lpstrFile;
			if ( filename.find( EXTENSION_STR[ extention ] ) == std::string::npos ) {
				filename += EXTENSION_STR[ extention ];
			}
			if ( !Desk::getTask( )->save( filename, extention ) ) {
				MessageBox( NULL, "ファイルの保存失敗しました", "エラー", MB_OK );
			}
		}
	}
		break;
	case IDM_NEWFILE:
		//新規作成モードへ移行
		Editor::getInstance( )->setMode( Editor::MODE_CREATE );
		break;
	case IDM_EXIT:
		//終了処理
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