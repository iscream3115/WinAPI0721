#include "stdafx.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int commnet)
{
	srand((uint)time(NULL));

	WinDesc desc;
	desc.appName = L"GAME";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WIN_WIDTH;
	desc.height = WIN_HEIGHT;

	Window* window = new Window(desc);
	WPARAM wParam = window->Run();


	SAFE_DELETE(window);

	return 0;
}