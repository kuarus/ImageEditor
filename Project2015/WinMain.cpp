#include <Windows.h>
#include <memory>
#include "Editor.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	Editor::initialize( nCmdShow );
	Editor::getInstance( )->run( );
	return 0;
}