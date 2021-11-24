#pragma once

class Time
{
private:
	static std::chrono::time_point<std::chrono::steady_clock> m_GlobalStartTime;
	static double m_BPM;
	static double m_Offset;
public:
	double CalculateTimeDifference();
	double CalculateCurrentBeat();
	void SetTimeStart();
	void SetMapData(double bpm, double offset);
	Time();
	static Time& Instance() { static Time time; return time; }

};

