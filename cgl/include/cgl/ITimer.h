#ifndef CGL_ITIMER_H
#define CGL_ITIMER_H

extern "C" float get_time_callback ();

class ITimer {
public:
	ITimer();
	virtual ~ITimer();
	virtual	bool Update (void) = 0;
	virtual	bool Reset (void) = 0;
	virtual bool IsActive (void) const = 0;
	virtual bool Start (void) = 0;
	virtual bool Stop (void) = 0;
	virtual bool Pause (void) = 0;
	virtual bool Unpause (void) = 0;
	static float GetTime (void) {
		return get_time_callback();
	}
};

#endif