#pragma once

class Time
{
private:
	static std::chrono::time_point<std::chrono::steady_clock> GlobalStartTime;
public:
	double CalculateTimeDifference();
	void SetTimeStart();
	Time();

};

