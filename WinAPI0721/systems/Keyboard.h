#pragma once


#define MAX_INPUT_KEY 256

class keyboard : public singletonBase<keyboard>
{
public:
	friend class singletonBase<keyboard>;

	void Update();

	bool Down(DWORD key) { return keyMap[key] == KEY_INPUT_DOWN; }
	bool Up(DWORD key) { return keyMap[key] == KEY_INPUT_UP; }
	bool Press(DWORD key) { return keyMap[key] == KEY_INPUT_PRESS; }

private:
	keyboard();

private:
	byte keyState[MAX_INPUT_KEY];
	byte keyOldState[MAX_INPUT_KEY];
	byte keyMap[MAX_INPUT_KEY];

	enum
	{
		KEY_INPUT_NONE = 0,
		KEY_INPUT_DOWN,
		KEY_INPUT_UP,
		KEY_INPUT_PRESS
	};


};