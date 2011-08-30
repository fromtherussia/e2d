#include "Types.h"

#include "ITimer.h"
#include "Stopwatch.h"

xStopWatch::xStopWatch():
	active(false),
	startTime(0.0f),
	paused(false),
	pausedTime(0.0f)
{
}
xStopWatch::xStopWatch(const xStopWatch &ref):
	active(ref.active),
	startTime(ref.startTime),
	paused(ref.paused),
	pausedTime(ref.pausedTime)
{
}

xStopWatch::~xStopWatch()
{
}

xStopWatch& xStopWatch::operator = (const xStopWatch &ref)
{
	active = ref.active;
	startTime = ref.startTime;
	paused = ref.paused;
	pausedTime = ref.pausedTime;
	return *this;
}

bool xStopWatch::Update (void)
{
	if(!active || paused)
	{
		return false;
	}

	return active;
}

bool xStopWatch::Reset (void)
{
	startTime = ITimer::GetTime();
	return true;
}

bool xStopWatch::IsActive (void) const
{
	return active && !paused;
}

bool xStopWatch::Start (void)
{
	if(active)
	{
		return false;
	}

	Reset();
	active = true;
	return true;
}

bool xStopWatch::Stop (void)
{
	if(!active)
	{
		return false;
	}

	active = false;
	return true;
}
bool xStopWatch::Pause (void)
{
	if(paused)
	{
		return false;
	}

	pausedTime = ITimer::GetTime();
	paused = true;
	return true;
}

bool xStopWatch::Unpause (void)
{
	if(!paused)
	{
		return false;
	}

	startTime += ITimer::GetTime() - pausedTime;
	paused = false;
	return true;
}

float xStopWatch::TimeElapsed (void) const
{
	if(active)
	{
		if(paused)
		{
			return pausedTime - startTime;
		}
		else
		{
			return ITimer::GetTime() - startTime;
		}
	}
	else
	{
		return 0.0f;
	}
}