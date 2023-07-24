#include "stdafx.h"
#include "windows.h"

WinDesc Window::desc;

Window::Window(WinDesc wd)
{
    WNDCLASSEX WndClass;

    WndClass.cbSize = sizeof(WNDCLASSEX);
    WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    WndClass.lpfnWndProc = (WNDPROC)WinProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = desc.instance;
    WndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = desc.appName.c_str();
    WndClass.hIconSm = WndClass.hIcon;

    WORD wHr = RegisterClassEx(&WndClass);

    //뭔가 문제가 생겼을 때 강제 종료를 하는 함수
    //assert(wHr != 0);

    desc.handle = CreateWindowEx
    (
        //확장 윈도우 스타일을 지정
        WS_EX_APPWINDOW,
        desc.appName.c_str(), //생성할 윈도우 클래스 이름
        desc.appName.c_str(), // 윈도우의 타이틀 바에 표시될 이름
        //윈도우 스타일
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
        //윈도우 크기 지정 x, y, 가로, 세로
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        (HMENU)NULL,
        desc.instance,
        NULL
    );

    ShowWindow(desc.handle, SW_SHOWNORMAL);
    SetForegroundWindow(desc.handle);

}

WPARAM Window::Run()
{
	

    MSG msg = { 0 };

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            {
                if (msg.message == WM_QUIT) break;

                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    return msg.wParam;

}



Window::~Window()
{


    DestroyWindow(desc.handle);
}

HDC memDC;
LRESULT Window::WinProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    HBITMAP hBitMap, oldBitMap;
    static RECT crtRect;

    ZeroMemory(&ps, sizeof(ps));

    switch (message)
    {
        case WM_CREATE:
        {
            SetTimer(handle, 1, 0, NULL);
            break;
        }

        case WM_PAINT:
        {
            //클라이언트 영역의 좌표를 구하는 함수
            GetClientRect(handle, &crtRect);

            //다 외울 필요는 없고 그냥 이런식으로 굴러간다만 알고 있으면 됨
            hdc = BeginPaint(handle, &ps);
            {
                //hdc와 호환되는 메모리 dc 생성
                memDC = CreateCompatibleDC(hdc);
                // hdc와 호환되는 메모리 비트맵 생성
                hBitMap = CreateCompatibleBitmap(hdc, crtRect.right, crtRect.bottom);

                //memDC와 hBitMap 연결
                oldBitMap = (HBITMAP)SelectObject(memDC, hBitMap);

                //선택된 영역을 지우고 지정된 영역을 해당 색깔로 채움
                PatBlt(memDC, 0, 0, crtRect.right, crtRect.bottom, WHITENESS);


                //지정된 비트맵에서 비트맵으로 영역 단순복사
                BitBlt(hdc, 0, 0, crtRect.right, crtRect.bottom, memDC, 0, 0, SRCCOPY);
                //이전에 선택한 비트맵(oldBitMap) 다시 선택
                SelectObject(memDC, oldBitMap);
                //생성한 비트맵 삭제
                DeleteObject(hBitMap);
                //생성한 메모리 DC 삭제
                DeleteDC(memDC);
            }
            EndPaint(handle, &ps);
            break;
        }
        case WM_TIMER:
        {
            //지정된 영역을 무효화, 해당 영역을 다시 그림
            InvalidateRect(desc.handle, nullptr, false);
            break;
        }
        case WM_CLOSE:
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }

	return DefWindowProc(handle, message,wParam,lParam);
}
