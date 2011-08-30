#include "Types.h"

#include "ITimer.h"
#include "CountdownCounter.h"

CountdownCounter::CountdownCounter(float timeToWait):
	active(false),
	startTime(0.0f),
	waitTime(0.0f),
	paused(false),
	pausedTime(0.0f)
{
	if(!Set(timeToWait))
	{
		throw std::out_of_range("");
	}
}
CountdownCounter::CountdownCounter(const CountdownCounter &ref):
	active(ref.active),
	startTime(ref.startTime),
	waitTime(ref.waitTime),
	paused(ref.paused),
	pausedTime(ref.pausedTime)
{
}

CountdownCounter::~CountdownCounter()
{
}

CountdownCounter& CountdownCounter::operator = (const CountdownCounter &ref)
{
	active = ref.active;
	startTime = ref.startTime;
	waitTime = ref.waitTime;
	paused = ref.paused;
	pausedTime = ref.pausedTime;
	return *this;
}

bool CountdownCounter::Set (float timeToWait)
{
	if(timeToWait >= 0.0f)
	{
		waitTime = timeToWait;
	}
	else 
	{
		return false;
	}

	Stop();
	Reset();
	return true;
}

bool CountdownCounter::Update (void)
{
	if(!active || paused)
	{
		return false;
	}

	if( ITimer::GetTime() >= startTime + waitTime )
	{
		active = false;
		Reset();
	}

	return active;
}

bool CountdownCounter::Reset (void)
{
	startTime = ITimer::GetTime();
	return true;
}

bool CountdownCounter::IsActive (void) const
{
	return active && !paused;
}

bool CountdownCounter::Start (void)
{
	if(active)
	{
		return false;
	}
	Reset();
	active = true;
	return true;
}

bool CountdownCounter::Stop (void)
{
	if(!active)
	{
		return false;
	}
	active = false;
	return true;
}
bool CountdownCounter::Pause (void)
{
	if(paused)
	{
		return false;
	}
	pausedTime = ITimer::GetTime();
	paused = true;
	return true;
}

bool CountdownCounter::Unpause (void)
{
	if(!paused)
	{
		return false;
	}
	startTime += ITimer::GetTime() - pausedTime;
	paused = false;
	return true;
}

float CountdownCounter::TimeRemaining (void) const
{
	if(active)
	{
		if(paused)
		{
			return waitTime - (pausedTime - startTime);
		}
		else
		{
			return waitTime - (ITimer::GetTime() - startTime);
		}
	}
	else
	{
		return 0.0f;
	}
}

float CountdownCounter::TimeElapsed (void) const
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