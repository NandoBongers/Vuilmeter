// 
// 
// 

#include "Button.h"
/*
	CONSTRUCTOR
	@param digital input pin number of the arduino nano
		   where the button is attached to.
*/
Button::Button(uint8_t pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Checks if the button is pressed.
	@param none.
	@return returns true if the button is pressed. 
*/
bool Button::is_Pressed()
{
	bool return_Value;
	if (digitalRead(_pin))
	{
		return_Value = true;
	}
	else
	{
		return_Value = false;
	}
	return return_Value;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////