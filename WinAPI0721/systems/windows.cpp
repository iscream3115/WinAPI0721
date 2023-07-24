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

    //���� ������ ������ �� ���� ���Ḧ �ϴ� �Լ�
    //assert(wHr != 0);

    desc.handle = CreateWindowEx
    (
        //Ȯ�� ������ ��Ÿ���� ����
        WS_EX_APPWINDOW,
        desc.appName.c_str(), //������ ������ Ŭ���� �̸�
        desc.appName.c_str(), // �������� Ÿ��Ʋ �ٿ� ǥ�õ� �̸�
        //������ ��Ÿ��
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
        //������ ũ�� ���� x, y, ����, ����
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
            //Ŭ���̾�Ʈ ������ ��ǥ�� ���ϴ� �Լ�
            GetClientRect(handle, &crtRect);

            //�� �ܿ� �ʿ�� ���� �׳� �̷������� �������ٸ� �˰� ������ ��
            hdc = BeginPaint(handle, &ps);
            {
                //hdc�� ȣȯ�Ǵ� �޸� dc ����
                memDC = CreateCompatibleDC(hdc);
                // hdc�� ȣȯ�Ǵ� �޸� ��Ʈ�� ����
                hBitMap = CreateCompatibleBitmap(hdc, crtRect.right, crtRect.bottom);

                //memDC�� hBitMap ����
                oldBitMap = (HBITMAP)SelectObject(memDC, hBitMap);

                //���õ� ������ ����� ������ ������ �ش� ����� ä��
                PatBlt(memDC, 0, 0, crtRect.right, crtRect.bottom, WHITENESS);


                //������ ��Ʈ�ʿ��� ��Ʈ������ ���� �ܼ�����
                BitBlt(hdc, 0, 0, crtRect.right, crtRect.bottom, memDC, 0, 0, SRCCOPY);
                //������ ������ ��Ʈ��(oldBitMap) �ٽ� ����
                SelectObject(memDC, oldBitMap);
                //������ ��Ʈ�� ����
                DeleteObject(hBitMap);
                //������ �޸� DC ����
                DeleteDC(memDC);
            }
            EndPaint(handle, &ps);
            break;
        }
        case WM_TIMER:
        {
            //������ ������ ��ȿȭ, �ش� ������ �ٽ� �׸�
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
