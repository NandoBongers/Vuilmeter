// 
// 
// 

#include "Real_Time_Clock.h"
/*
	Initialize the real time clock.
	@param none.
	@return none.
*/
void Real_Time_Clock::begin()
{
	setSyncProvider(RTC.get);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Transforms the time, from a string to an int. 
	@param none.
	@return returns the time.
*/
int Real_Time_Clock::time()
{
	int return_Value;
	 
	//HOUR
	String h = String(hour());
	if (hour() < 10)
	{
		h = '0' + h;
	}

	//MINUTE
	String m = String(minute());
	if (minute() < 10)
	{
		m = '0' + m;
	}
	return_Value = (h + m).toInt();
	return return_Value;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Gets todays date.
	@param none.
	@return returns today's date.
*/
String Real_Time_Clock::date()
{
	String date;
	date = String(day()) + '-' + String(month()) + '-' + String(year());
	return date;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
