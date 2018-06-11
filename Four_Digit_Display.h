// Four_Digit_Display.h

#ifndef FOUR_DIGIT_DISPLAY_h
#define FOUR_DIGIT_DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <TM1637Display.h>
#else
	#include "WProgram.h"
#endif
class Four_Digit_Display
{
public:
	Four_Digit_Display(TM1637Display *p_Four_Digit_Display_Lib);
	void print(int time);
private:
	TM1637Display * _p_Four_Digit_Display_Lib;
};

#endif