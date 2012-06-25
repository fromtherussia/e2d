#ifndef CGL_STOPWATCH_H
#define CGL_STOPWATCH_H

/***
	Секундомер
	[threadunsafe]
***/

class xStopWatch: public ITimer {
public:
	xStopWatch();
	xStopWatch(const xStopWatch &ref);
	virtual ~xStopWatch();
	
	xStopWatch& operator = (const xStopWatch &ref);
	virtual	bool Update (void);
	virtual	bool Reset (void);
	virtual bool IsActive (void) const;
	virtual bool Start (void);
	virtual bool Stop (void);
	virtual bool Pause (void);
	virtual bool Unpause (void);
	float TimeElapsed (void) const;

private:
	bool active;
	float startTime;
	bool paused;
	float pausedTime;
};

#endif