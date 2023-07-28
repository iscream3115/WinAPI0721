#include "stdafx.h"
#include "Timer.h"

bool Timer::isTimerStopped = true;
float Timer::timeElapsed = 0.f;

Timer::Timer()
{

	//1�ʴ� hz(������)�� ��ȯ������
	QueryPerformanceFrequency((LARGE_INTEGER*)&tickPerSec);

	fpsUpdateInterval = tickPerSec >> 1;

	fpsRect = { WIN_WIDTH - 175, 25,WIN_HEIGHT, 50 };
	fpsStr = L"";
}

void Timer::Update()
{
	if (isTimerStopped) return;
	//���� �����ȿ��� ��� �����ߴ°�
	//CPU�� ƽ�� �޾ƿ´�
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	//�������� ���� ������Ʈ������ �ð�����
	timeElapsed = (float)(currentTime - lastTime) / (float)tickPerSec;

	runningTime += timeElapsed;

	framecount++;

	//������Ʈ ���� ���� �ð��� fpsUpdateInterval���� ũ�� ���ο� FPS���� ���
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		//���� �ð��� ������ FPS ������ �ð����̸� ���
		float tempCurrentTime = (float)currentTime / (float)tickPerSec;
		//�� �ð������� �� �������� ������ ����� ���
		float tempLastTime = (float)lastFPSUpdate / (float)tickPerSec;
		//���� �����Ӱ� �ð� ���̸� �̿��Ͽ� fps �� ���
		fps = (float)framecount / (tempCurrentTime - tempLastTime);

		lastFPSUpdate = (int64)currentTime;
		framecount = 0;

	}

	lastTime = currentTime;

}

void Timer::Print()
{
	fpsStr = L"FPS : " + to_wstring((int)FPS());
	DrawText(memDC, fpsStr.c_str(), -1, &fpsRect, DT_CENTER | DT_VCENTER);
}

void Timer::Start()
{
	if (!isTimerStopped) assert(false);

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	isTimerStopped = false;

}

void Timer::Stop()
{
	if (!isTimerStopped) assert(true);

	int64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&stopTime);
	runningTime += (stopTime - lastTime) / (float)tickPerSec;
	isTimerStopped = true;

}


