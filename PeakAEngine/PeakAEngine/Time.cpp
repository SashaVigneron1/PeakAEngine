#include "PeakAEnginePCH.h"
#include "Time.h"

float Time::deltaTime = 0.f;
float Time::elapsedTime = 0.f;
float Time::fixedTime = 0.f;

void Time::CalculateTime()
{
	if (!hasStarted) { lastTime = std::chrono::high_resolution_clock::now(); hasStarted = true; }

	const auto currTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float>(currTime - lastTime).count();
	lastTime = currTime;
	elapsedTime += deltaTime;
}

std::string Time::GetCurrentTimeAsString()
{
	// Current date/time based on current system
	time_t now = time(0);

	// Convert now to tm struct for local timezone
	tm* localtm = localtime(&now);

	std::string result{ asctime(localtm) };
	result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
	return result;
}

void Time::UpdateTimers()
{
	// Update Timers
	for (int i{}; i < (int)m_Timers.size(); ++i)
	{
		m_Timers[i]->timeLeft -= deltaTime;
		if (m_Timers[i]->timeLeft <= 0)
		{
			m_Timers[i]->executeFunction();

			// Delete This Timer
			m_Timers[i] = m_Timers.back();
			m_Timers.pop_back();
		}
	}
}
