#include "stdafx.h"
#include "Keyboard.h"

#define ZERO(p) ZeroMemory(p, sizeof(p))

keyboard::keyboard()
{
	ZERO(keyState);
	ZERO(keyOldState);
	ZERO(keyMap);
}

void keyboard::Update()
{
	//keyOldState에 keystate 복사
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZERO(keyState);
	ZERO(keyMap);
	//keyState에 현재 키보드의 가상 키 상태 복사
	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{

		// 0x80 과 AND 연산하여 0 또는 0x80값을 key에 저장
		//0x80 == 키가 눌린 상태
		byte key = keyState[i] & 0x80;


		//key변수가 0이 아니면 keystate[i]를 1 아니면 0으로 설정
		//해당 배열은 1 or 0의 값을 가지며 해당 인덱스에 해당하는 키가 눌린 상태인지 알 수 있다
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		if (oldState == 0 && state == 1) keyMap[i] = KEY_INPUT_DOWN;
		else if (oldState == 1 && state == 0) keyMap[i] = KEY_INPUT_UP;
		else if (oldState == 1 && state == 1) keyMap[i] = KEY_INPUT_PRESS;
		else keyMap[i] = KEY_INPUT_NONE;
	}

	GetKeyState(0);
}
