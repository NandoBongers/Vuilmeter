// Real_Time_Clock.h

#ifndef _REAL_TIME_CLOCK_h
#define _REAL_TIME_CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <DS3232RTC.h>
#else
	#include "WProgram.h"
#endif

class Real_Time_Clock
{
public:
	void begin();
	int time();
	String date();
};

#endif