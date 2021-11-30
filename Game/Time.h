#pragma once

class Time
{
private:
	static std::chrono::time_point<std::chrono::steady_clock> m_GlobalStartTime;
public:
	static double CalculateTimeDifference();
	static double CalculateCurrentBeat();
	static void SetTimeStart();

	Time();
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
};

