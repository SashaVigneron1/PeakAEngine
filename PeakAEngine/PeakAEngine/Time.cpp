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

			if (m_Timers[i]->shouldStartOver)
			{
				m_Timers[i]->timeLeft = m_Timers[i]->totalTime;
			}
			else 
			{
				// Delete This Timer
				m_Timers[i] = m_Timers.back();
				m_Timers.pop_back();
			}
		}
	}

	for (int i{}; i < (int)m_FrameCounters.size(); ++i)
	{
		--m_FrameCounters[i]->framesLeft;
		if (m_FrameCounters[i]->framesLeft <= 0)
		{
			m_FrameCounters[i]->executeFunction();

			if (m_FrameCounters[i]->shouldStartOver)
			{
				m_FrameCounters[i]->framesLeft = m_FrameCounters[i]->totalFrames;
			}
			else
			{
				// Delete This Timer
				m_FrameCounters[i] = m_FrameCounters.back();
				m_FrameCounters.pop_back();
			}
		}
	}
}
