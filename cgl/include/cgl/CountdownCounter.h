#ifndef CGL_COUNTDOWNCOUNTER_H
#define CGL_COUNTDOWNCOUNTER_H

/***
	Таймер обратного отсчета
	[threadunsafe]
***/

class CountdownCounter: public ITimer {
public:
	CountdownCounter(float timeToWait = 0.0f);
	CountdownCounter(const CountdownCounter &ref);
	virtual ~CountdownCounter();
	
	CountdownCounter& operator = (const CountdownCounter &ref);
	bool Set (float timeToWait);
	virtual	bool Update (void);
	virtual	bool Reset (void);
	virtual bool IsActive (void) const;
	virtual bool Start (void);
	virtual bool Stop (void);
	virtual bool Pause (void);
	virtual bool Unpause (void);
	float TimeRemaining (void) const;
	float TimeElapsed (void) const;

private:
	bool active;
	float startTime;
	float waitTime;
	bool paused;
	float pausedTime;
};

#endif