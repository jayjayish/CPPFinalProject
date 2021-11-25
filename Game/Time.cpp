#include "Precompiled.h"
#include "Time.h"

std::chrono::time_point<std::chrono::steady_clock> Time::m_GlobalStartTime = std::chrono::time_point<std::chrono::steady_clock>::max();
double Time::m_BPM = 0.0;
double Time::m_Offset = 0.0;

double Time::CalculateTimeDifference()
{
	auto current_time = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - m_GlobalStartTime).count() / static_cast<double>(1000);
}

double Time::CalculateCurrentBeat()
{
	return CalculateTimeDifference() * m_BPM;
}

void Time::SetTimeStart()
{
	m_GlobalStartTime = std::chrono::steady_clock::now();
}

void Time::SetMapData(double bpm, double offset)
{
	m_BPM = bpm / 60.0;
	m_Offset = offset;
}

Time::Time()
{
	if (m_GlobalStartTime == std::chrono::time_point<std::chrono::steady_clock>::max())
	{
		m_GlobalStartTime = std::chrono::steady_clock::now();
	}
}

