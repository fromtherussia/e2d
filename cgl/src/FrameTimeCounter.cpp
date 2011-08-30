#include "FrameTimeCounter.h"

FrameTimeCounter::FrameTimeCounter():
	m_startTime(0.0f),
	m_stopTime(0.0f) {
}

FrameTimeCounter::~FrameTimeCounter() {
}

void FrameTimeCounter::BeginCounting() {
	m_startTime = get_time_callback();
}

void FrameTimeCounter::EndCounting() {
	m_stopTime = get_time_callback();
}

float FrameTimeCounter::GetFrameTime() {
	return m_stopTime - m_startTime;
}

int FrameTimeCounter::GetFps() {
	float frameTime = GetFrameTime();
	if (frameTime <= 0.0f) {
		return 0;
	}
	return 1.0f / frameTime; 
}