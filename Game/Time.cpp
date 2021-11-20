#include "Precompiled.h"
#include "Time.h"

std::chrono::time_point<std::chrono::steady_clock> Time::GlobalStartTime = std::chrono::time_point<std::chrono::steady_clock>::max();

double Time::CalculateTimeDifference()
{
	auto current_time = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - GlobalStartTime).count() / static_cast<double>(1000);
}

void Time::SetTimeStart()
{
	GlobalStartTime = std::chrono::steady_clock::now();
}

Time::Time()
{
	if (GlobalStartTime == std::chrono::time_point<std::chrono::steady_clock>::max())
	{
		GlobalStartTime = std::chrono::steady_clock::now();
	}
}

