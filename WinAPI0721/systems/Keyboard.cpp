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
	//keyOldState�� keystate ����
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZERO(keyState);
	ZERO(keyMap);
	//keyState�� ���� Ű������ ���� Ű ���� ����
	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{

		// 0x80 �� AND �����Ͽ� 0 �Ǵ� 0x80���� key�� ����
		//0x80 == Ű�� ���� ����
		byte key = keyState[i] & 0x80;


		//key������ 0�� �ƴϸ� keystate[i]�� 1 �ƴϸ� 0���� ����
		//�ش� �迭�� 1 or 0�� ���� ������ �ش� �ε����� �ش��ϴ� Ű�� ���� �������� �� �� �ִ�
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
