#pragma once
#include <chrono>
/*
* Scope-based Timer
*/
class Timer
{
public:
	Timer() : m_DeltaTime(0.0f), m_TotalElapsedTime(0.0f), m_FrameCount(0)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	void StartTime()
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();

	}

	void StopTime()
	{
		auto EndTimePoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimePoint).time_since_epoch().count();

		auto duration = end - start;
		float ms = duration * 0.001;
		m_DeltaTime = ms * 0.001;
		m_TotalElapsedTime += ms;
		++m_FrameCount;
	}

	unsigned int GetMSPerFrame()
	{
		return m_TotalElapsedTime / m_FrameCount;
	}

	float m_DeltaTime;
	float m_TotalElapsedTime;
	unsigned int m_FrameCount;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};