#pragma once
#include "Manager.h"

#include <chrono>
#include <functional>

struct Timer 
{
	Timer(float totalTime, std::function<void()> functionToExecute)
		: totalTime{ totalTime }
		, timeLeft{ totalTime }
		, executeFunction{ functionToExecute }
	{}

	float totalTime;
	float timeLeft;
	std::function<void()> executeFunction;
};
struct FrameCounter
{
	FrameCounter(int totalFrames, std::function<void()> functionToExecute)
		: totalFrames{ totalFrames }
		, framesLeft{ totalFrames }
		, executeFunction{ functionToExecute }
	{}

	int totalFrames;
	int framesLeft;
	std::function<void()> executeFunction;
};

class Time final : public Manager
{
public:
	void CalculateTime();

	void SetFixedTime(float fixedTimeStep) { fixedTime = fixedTimeStep; }

	static float FixedTime() { return fixedTime; }
	static float ElapsedTime() { return elapsedTime; }
	static float DeltaTime() { return deltaTime; }

	static std::string GetCurrentTimeAsString();

	void AddTimer(std::shared_ptr<Timer> timer) { m_Timers.push_back(timer); }
	void AddTimer(std::shared_ptr<FrameCounter> frameCounter) { m_FrameCounters.push_back(frameCounter); }
	void UpdateTimers();
private:
	bool hasStarted = false;
	static float elapsedTime;
	static float deltaTime;
	static float fixedTime;

	std::chrono::steady_clock::time_point lastTime;

	std::vector<std::shared_ptr<Timer>> m_Timers;
	std::vector<std::shared_ptr<FrameCounter>> m_FrameCounters;
};