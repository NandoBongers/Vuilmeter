// Timer.h

#ifndef _TIMER_h
#define _TIMER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Timer
{
public:
	Timer();
	int seconds();
	void reset();
private:
	unsigned long _begin_Value;
	unsigned long _current_Value;
	bool _in_Use;
};

#endif