#pragma once
#include <chrono>
/*
* Scope-based Timer
*/
class Timer
{
public:
	Timer()
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	float GetElapsedTime()
	{
		auto EndTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch();
		auto duration = end - start;
		return static_cast<float>(duration.count() * 0.000001f);
	}
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};