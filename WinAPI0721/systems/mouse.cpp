#include "stdafx.h"
#include "mouse.h"

Mouse::Mouse()
{
	position = Vector3(0, 0, 0);

	wheelState = Vector3(0, 0, 0);
	wheelOldState = Vector3(0, 0, 0);
	wheelMoveValue = Vector3(0, 0, 0);

	ZeroMemory(buttonState, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonOldState, sizeof(byte) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonMap, sizeof(byte) * MAX_INPUT_MOUSE);

	ZeroMemory(startDblClk, sizeof(DWORD) * MAX_INPUT_MOUSE);
	ZeroMemory(buttonCount, sizeof(int) * MAX_INPUT_MOUSE);


	timeDblClk = GetDoubleClickTime();
	startDblClk[0] = GetTickCount64();

	for (int i = 0; i < MAX_INPUT_MOUSE; i++)
	{
		startDblClk[i] = startDblClk[0];
	}
	DWORD line = 0;
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &line, 0);

	posRect = { WIN_WIDTH - 200, 0, WIN_HEIGHT, 25 };
	posStr = L"";

}

void Mouse::Update()
{
	memcpy(buttonOldState, buttonState, sizeof(buttonOldState));

	ZeroMemory(buttonState, sizeof(buttonState));
	ZeroMemory(buttonMap, sizeof(buttonMap));

	{
		POINT point;

		GetCursorPos(&point);
		ScreenToClient(handle, &point);

		wheelOldState.x = wheelState.x;
		wheelOldState.y = wheelState.y;

		wheelState.x = point.x;
		wheelState.y = point.y;

		wheelMoveValue = wheelState - wheelOldState;
	}

	{
		//GetAsyncKeyState -> 키가 눌리면 최상위 비트가  1, 토글키가 켜지면 최하위 비트 0 -> 토글키 상태 조사할떄 씀
		buttonState[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
		buttonState[1] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
		buttonState[2] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	}

	//클릭
	{



	}

	//더블클릭
	{
		for (DWORD i = 0; i < MAX_INPUT_MOUSE; i++)
		{
			if (buttonMap[i] == BUTTON_INPUT_DOWN)
			{
				if (buttonCount[i] == 1)
				{
					if (tButtonState - startDblClk[i] >= timeDblClk)
						buttonCount[i] = 0;

					startDblClk[i] = tButtonState;

				}
				buttonCount[i]++;
			}

			if (buttonMap[i] == BUTTON_INPUT_UP)
			{
				if (buttonCount[i] == 1)
				{
					if (tButtonState - startDblClk[i] >= timeDblClk)
						buttonCount[i] = 0;
				}
				else if (buttonCount[i] == 2)
				{
					if (tButtonState - startDblClk[i] <= timeDblClk)
						buttonMap[i] = BUTTON_INPUT_DBLCLK;

					buttonCount[i] = 0;
				}
			}

		}


	}


}

void Mouse::Print()
{
}

LRESULT Mouse::InputProc(UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_LBUTTONDOWN || message == WM_MOUSEMOVE)
	{
		position.x = LOWORD(lparam);
		position.y = HIWORD(lparam);
	}

	if (message == WM_MOUSEWHEEL)
	{
		short tWheelValue = (short)HIWORD(wparam);
		wheelOldState.z = wheelState.z;
		wheelState.z += (float)tWheelValue;
	}
	return true;
}

