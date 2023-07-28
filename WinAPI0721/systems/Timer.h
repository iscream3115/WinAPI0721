#pragma once

typedef INT64 int64;

class Timer : public singletonBase<Timer>
{
public:
	friend class singletonBase<Timer>;

	static bool stopped() { return isTimerStopped; }
	static bool Delta() { return isTimerStopped ? 0.0f : timeElapsed; }

	void Update();
	void Print();

	void Start();
	void Stop();

	float FPS() const { return fps; }
	float running() const { return runningTime;  }

private:
	Timer();

private:
	static bool isTimerStopped;

	//현재 프레임에서 다음프레임으로 넘어가는 시간이다
	static float timeElapsed;

	int64 tickPerSec = 0;
	int64 currentTime = 0;
	int64 lastTime = 0;
	int64 lastFPSUpdate = 0;
	int64 fpsUpdateInterval = 0;

	uint framecount = 0;
	float runningTime = 0;
	float fps = 0;

	RECT fpsRect;
	wstring fpsStr;


};