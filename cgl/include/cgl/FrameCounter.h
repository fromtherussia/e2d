#ifndef CGL_FRAMECOUNTER_H
#define CGL_FRAMECOUNTER_H

/***
	Cчетчик кадров
	[threadunsafe]
***/

class FrameCounter: public ITimer {
public:
	enum CounterType {
		NormalCounter,
		ReverseCounter
	};

	FrameCounter(float cycleTime, int startTime, int maxFrames, bool cycledFlag = false, CounterType counterType = NormalCounter);
	virtual ~FrameCounter();

	bool Set (float cycleTime, int startTime, int maxFrames);
	int GetCount (void) const;
	virtual	bool Update (void);
	virtual	bool Reset (void);
	virtual bool IsActive (void) const;
	virtual bool Start (void);
	virtual bool Stop (void);
	virtual bool Pause (void);
	virtual bool Unpause (void);

private:
	bool active;
	float timePerFrame;
	int start;
	int framesMaxCount;
	int frames;
	float lastUpdateTime;
	CounterType type;
	bool cycled;
	bool paused;
};

#endif