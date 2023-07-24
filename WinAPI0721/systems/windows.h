#pragma once

using namespace std;

struct WinDesc
{
	wstring appName;
	HINSTANCE instance;
	HWND handle;
	UINT width;
	UINT height;
};

class Window
{
public:

	WPARAM Run();
	Window(WinDesc wd);
	~Window();

private:

	static LRESULT CALLBACK WinProc
	(
		HWND handle,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

		
private:
	static WinDesc desc;

};


