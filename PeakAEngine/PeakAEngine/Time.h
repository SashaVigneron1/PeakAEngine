#pragma once
#include <chrono>

#include "Singleton.h"

#define TIME Time::GetInstance()

class Time final : public Singleton<Time>
{
	friend class Singleton<Time>;

public:
	void CalculateTime();

	void SetFixedTime(float fixedTimeStep) { fixedTime = fixedTimeStep; }

	static float FixedTime() { return fixedTime; }
	static float ElapsedTime() { return elapsedTime; }
	static float DeltaTime() { return deltaTime; }

	static std::string GetCurrentTimeAsString();
private:
	bool hasStarted = false;
	static float elapsedTime;
	static float deltaTime;
	static float fixedTime;

	std::chrono::steady_clock::time_point lastTime;
};
