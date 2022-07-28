#pragma once
#include "Manager.h"

#include <chrono>
#include <functional>

struct Timer 
{
	Timer(float totalTime, std::function<void()> functionToExecute, bool shouldStartOver = false)
		: totalTime{ totalTime }
		, timeLeft{ totalTime }
		, executeFunction{ functionToExecute }
		, shouldStartOver{ shouldStartOver }
	{}

	float totalTime;
	float timeLeft;
	bool shouldStartOver;
	std::function<void()> executeFunction;
};
struct FrameCounter
{
	FrameCounter(int totalFrames, std::function<void()> functionToExecute, bool shouldStartOver = false)
		: totalFrames{ totalFrames }
		, framesLeft{ totalFrames }
		, executeFunction{ functionToExecute }
		, shouldStartOver{ shouldStartOver }
	{}

	int totalFrames;
	int framesLeft;
	bool shouldStartOver;
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