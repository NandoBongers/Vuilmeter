// 
// 
// 

#include "Four_Digit_Display.h"
/*
	CONSTRUCTOR
	@param pointer of an TM1637Display object.
*/
Four_Digit_Display::Four_Digit_Display(TM1637Display *temp_P_Four_Digit_Display_Lib)
{
	_p_Four_Digit_Display_Lib = temp_P_Four_Digit_Display_Lib;
	_p_Four_Digit_Display_Lib->setBrightness(0x0f);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Prints a four-digit number with points in between the middle. 
@param the time.
@return none
*/
void Four_Digit_Display::print(int time)
{
	_p_Four_Digit_Display_Lib->showNumberDecEx(time, (0x80 >> 1), false, 4);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////