#pragma once

class Time
{
private:
	static std::chrono::time_point<std::chrono::steady_clock> m_GlobalStartTime;
public:
	double CalculateTimeDifference();
	double CalculateCurrentBeat();
	void SetTimeStart();
	Time();
};

