#include "stdafx.h"
#include "Timer.h"

bool Timer::isTimerStopped = true;
float Timer::timeElapsed = 0.f;

Timer::Timer()
{

	//1초당 hz(진동수)를 반환시켜줌
	QueryPerformanceFrequency((LARGE_INTEGER*)&tickPerSec);

	fpsUpdateInterval = tickPerSec >> 1;

	fpsRect = { WIN_WIDTH - 175, 25,WIN_HEIGHT, 50 };
	fpsStr = L"";
}

void Timer::Update()
{
	if (isTimerStopped) return;
	//일정 지점안에서 몇번 진동했는가
	//CPU의 틱을 받아온다
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	//이전에서 현재 업데이트까지의 시간간격
	timeElapsed = (float)(currentTime - lastTime) / (float)tickPerSec;

	runningTime += timeElapsed;

	framecount++;

	//업데이트 이후 지난 시간이 fpsUpdateInterval보다 크면 새로운 FPS값을 계산
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		//현재 시간과 마지막 FPS 이후의 시간차이를 계산
		float tempCurrentTime = (float)currentTime / (float)tickPerSec;
		//그 시간동안의 몇 프레임이 렌더링 됬는지 계산
		float tempLastTime = (float)lastFPSUpdate / (float)tickPerSec;
		//계산된 프레임과 시간 차이를 이용하여 fps 값 계산
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


