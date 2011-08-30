#ifndef CGL_FRAME_TIME_COUNTER_H
#define CGL_FRAME_TIME_COUNTER_H

extern "C" float get_time_callback();

class FrameTimeCounter {
public:
	FrameTimeCounter();
	~FrameTimeCounter();
	void BeginCounting();
	void EndCounting();
	float GetFrameTime();
	int GetFps();

private:
	float m_startTime;
	float m_stopTime;
};

#endif