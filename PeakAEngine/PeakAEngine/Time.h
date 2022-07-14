#pragma once
#include <chrono>

#include <functional>
#include "Singleton.h"

#define TIME Time::GetInstance()

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

	void AddTimer(std::shared_ptr<Timer> timer) { m_Timers.push_back(timer); }
	void UpdateTimers();
private:
	bool hasStarted = false;
	static float elapsedTime;
	static float deltaTime;
	static float fixedTime;

	std::chrono::steady_clock::time_point lastTime;

	std::vector<std::shared_ptr<Timer>> m_Timers;
};

//physics->OnTriggerExit = std::bind(&PeterPepper::OnTriggerExit, pPeterPepper, std::placeholders::_1);
