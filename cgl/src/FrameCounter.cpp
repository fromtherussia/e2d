#include "Types.h"

#include "ITimer.h"
#include "FrameCounter.h"

FrameCounter::FrameCounter(float cycleTime, int startTime, int maxFrames, bool cycledFlag, CounterType counterType):
	active(false),
	timePerFrame(0.0f),
	start(0),			
	framesMaxCount(0),			
	frames(0),
	lastUpdateTime(0.0f),
	type(counterType),
	cycled(cycledFlag),
	paused(false)
{
	if(!Set(cycleTime,startTime,maxFrames))
	{
		throw std::out_of_range("");
	}
}

FrameCounter::~FrameCounter()
{
}

bool FrameCounter::Set (float cycleTime, int startTime, int maxFrames)
{
	if(cycleTime <= 0.0f || maxFrames <= 0 || startTime < 0)
	{
		return false;
	}
	timePerFrame = cycleTime / ((float)maxFrames);
	start = startTime;
	framesMaxCount = maxFrames;
	Reset();
	return true;
}

int FrameCounter::GetCount (void) const
{
	switch(type)
	{
	case NormalCounter:
		return frames;		
	case ReverseCounter:
		return framesMaxCount - 1 - frames + start;
	default:
		return frames;
	}
}

bool FrameCounter::Update (void)
{
	if(!active || paused)
	{
		return false;
	}

	float curentTime = ITimer::GetTime();
	float deltaTime = curentTime - lastUpdateTime;
	if(deltaTime >= timePerFrame)
	{
		lastUpdateTime = curentTime - fmod(deltaTime,timePerFrame);
		frames += (int)(deltaTime/timePerFrame);
		
		if(frames >= framesMaxCount)
		{
			if(!cycled)
			{
				Stop();
				Reset();
			}
			else
			{
				frames %= framesMaxCount;
			}					
		}
	}
	return IsActive();
}

bool FrameCounter::Reset (void)
{
	lastUpdateTime = ITimer::GetTime();
	frames = start;
	return true;
}

bool FrameCounter::IsActive	(void) const
{
	return active && !paused;
}

bool FrameCounter::Start (void)
{
	if(active)
	{
		return false;
	}

	Reset();
	active = true;
	return true;
}
// Остановка таймера
bool FrameCounter::Stop (void)
{
	if( !active )
	{
		return false;
	}

	active = false;
	return true;
}
// Приостановка таймера
bool FrameCounter::Pause (void)
{
	if(paused)
	{
		return false;
	}

	paused = true;
	return true;
}

bool FrameCounter::Unpause (void)
{
	if(!paused)
	{
		return false;
	}

	lastUpdateTime = ITimer::GetTime();
	paused = false;
	return true;
}