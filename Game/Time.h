#pragma once

class Time
{
private:
	static std::chrono::time_point<std::chrono::steady_clock> m_GlobalStartTime;
	static double m_BPM;
public:
	double CalculateTimeDifference();
	double CalculateCurrentBeat();
	void SetTimeStart();
	void SetBPM(double bpm);
	Time();
	static Time& Instance() { static Time time; return time; }

};

