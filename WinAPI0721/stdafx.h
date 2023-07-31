#pragma once
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <assert.h>

using namespace std;

typedef UINT uint;

extern HDC memDC;


//��ø �Ҵ�� �޸𸮸� ���� ��Ų �� �װ� �� �����ͷ� ������ִ� ��
#define SAFE_DELETE(p) {if(p) delete(p); (p) = nullptr; }
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#include "utilities/Vector3.h"
#include "utilities/singletonBase.h"
#include "utilities/ResourceManager.h"
#include "systems/windows.h"
#include "systems/Timer.h"
#include "systems/Keyboard.h"
#include "systems/mouse.h"
