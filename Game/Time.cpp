#include "Precompiled.h"
#include "Time.h"
#include "GlobalConstants.h"

std::chrono::time_point<std::chrono::steady_clock> Time::m_GlobalStartTime = std::chrono::time_point<std::chrono::steady_clock>::max();

constexpr double k_BPS = k_BPM / 60.0;

double Time::CalculateTimeDifference()
{
	auto current_time = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - m_GlobalStartTime).count() / static_cast<double>(1000);
}

double Time::CalculateCurrentBeat()
{
	return CalculateTimeDifference() * k_BPS;
}

void Time::SetTimeStart()
{
	m_GlobalStartTime = std::chrono::steady_clock::now();
}

Time::Time()
{
	if (m_GlobalStartTime == std::chrono::time_point<std::chrono::steady_clock>::max())
	{
		m_GlobalStartTime = std::chrono::steady_clock::now();
	}
}

