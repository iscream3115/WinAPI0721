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
	static float timeElapsed;

	int64 tickPerSec;
	int64 currentTime;
	int64 lastTime;
	int64 lastFPSUpdate;
	int64 fpsUpdateInterval;

	uint framecount;
	float runningTime;
	float fps;

	RECT fpsRect;
	wstring fpsStr;


};