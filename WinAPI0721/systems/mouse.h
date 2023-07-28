#pragma once


#define MAX_INPUT_MOUSE 8

class Mouse : public singletonBase<Mouse>
{
public:
	friend singletonBase<Mouse>;

	void SetHandle(HWND handle) { this->handle = handle; }

	void Update();
	void Print();

	LRESULT InputProc(UINT message, WPARAM wparam, LPARAM lparam);

	Vector3 GetPosition() { return position; }
	Vector3 GetMoveValue() { return wheelMoveValue; }

	bool Down(DWORD button) { return buttonMap[button] == BUTTON_INPUT_DOWN; };
	bool Up(DWORD button) { return buttonMap[button] == BUTTON_INPUT_UP; };
	bool Press(DWORD button) { return buttonMap[button] == BUTTON_INPUT_PRESS; };

private:

	Mouse();

private:

	HWND handle;
	Vector3 position;

	byte buttonState[MAX_INPUT_MOUSE];
	byte buttonOldState[MAX_INPUT_MOUSE];
	byte buttonMap[MAX_INPUT_MOUSE];

	Vector3 wheelState;
	Vector3 wheelOldState;
	Vector3 wheelMoveValue;

	DWORD timeDblClk;
	DWORD startDblClk[MAX_INPUT_MOUSE];
	int buttonCount[MAX_INPUT_MOUSE]; 

	RECT posRect;
	wstring posStr;

	enum
	{
		BUTTON_INPUT_NONE = 0,
		BUTTON_INPUT_DOWN,
		BUTTON_INPUT_UP,
		BUTTON_INPUT_PRESS,
		BUTTON_INPUT_DBLCLK,
	};
};