#include "Window.h"
#include "resource.h"
#include "Editor.h"
#include "DxLib.h"
#include "define.h"

const char* CLASS_NAME = "IE";
const char* TITLE_NAME = "ImageEditor";

Window::Window( ) {
}


Window::~Window( ) {
}

int Window::create( ) {
	WNDCLASSEX wc = { };
	//�T�C�Y
	wc.cbSize			= sizeof( WNDCLASSEX );
	//�E�B���h�E�X�^�C��
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	//�E�B���h�E�̃��b�Z�[�W����������֐�
	wc.lpfnWndProc		= WndProc;
	//�⑫�o�C�g��
	wc.cbClsExtra		= 0L;
	wc.cbWndExtra		= 0L;
	//�C���X�^���X�n���h��
	wc.hInstance		= NULL;
	//�A�C�R���̃n���h��
	wc.hIcon			= NULL;
	//�J�[�\���̃n���h��
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	//�w�i�J���[���w��
	wc.hbrBackground	= (HBRUSH)GetStockObject( WHITE_BRUSH );
	//���j���[�o�[�̖��O
	wc.lpszMenuName		= MAKEINTRESOURCE( IDR_MENU1 );
	//�E�B���h�E�N���X(this)�̖��O
	wc.lpszClassName	= CLASS_NAME;
	//16x16�̃A�C�R��
	wc.hIconSm			= NULL;

	//�E�B���h�E�N���X�̓o�^
	if ( RegisterClassEx( &wc ) == 0 ) {
		return FALSE;
	}

	//�E�B���h�E�̐���
	_window_handle = CreateWindowEx(
		WS_EX_ACCEPTFILES,
		CLASS_NAME, TITLE_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL,
		NULL, NULL
	);

	//�E�B���h�E�̃n���h����NULL�̏ꍇ�̓G���[
	if ( !_window_handle ) {
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK Window::WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
    switch( msg ) {
	case WM_SIZE:
		//�E�B���h�E�T�C�Y�ύX����
		break;
	case WM_DESTROY:
		//�E�B���h�E�����
		PostQuitMessage( 0 );
        return 0L;
	case WM_COMMAND:
		//���j���[�o�[�̃R�}���h��I������
		std::shared_ptr< Editor >( Editor::getInstance( ) )->excuteCommand( hWnd, wParam );
	}
    return  DefWindowProc( hWnd, msg, wParam, lParam );
}

HWND Window::getWindowHandle( ) const {
	return _window_handle;
}