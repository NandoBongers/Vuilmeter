// 
// 
// 

#include "Timer.h"
/*
	CONSTRUCTOR
	@param none.
	@return none.
*/
Timer::Timer()
{
	reset();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Calculates the amount of seconds that passed by since 
			   this method has been called for the first time.
	@param none.
	@return returns the time in seconds.
*/
int Timer::seconds()
{
	int time;
	if (!_in_Use)
	{
		_begin_Value = millis();
		_in_Use = true;
	}
	_current_Value = millis();
	time = (_current_Value - _begin_Value) / 1000;
	return time;	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Resets and stops the timer.
	@param none.
	@return none.
*/
void Timer::reset()
{
	_in_Use = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////