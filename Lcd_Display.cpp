// 
// 
// 

#include "Lcd_Display.h"
/*
	CONSTRUCTOR
	@param a pointer to a LiquidCrystal_I2C object
		   and an analog output pin of the Arduino
		   where the backligth dimmer is attached to. 
*/
Lcd_Display::Lcd_Display(LiquidCrystal_I2C* p_Lcd_Lib, uint8_t pin)
{
	_first_Time = true;
	_pin = pin;
	pinMode(_pin, OUTPUT);
	_p_Lcd_Lib = p_Lcd_Lib;
	_on = false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Initialize lcd display.
	@param none.
	@return none.
*/
void Lcd_Display::begin()
{
	_p_Lcd_Lib->begin();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Sets the brightness of the lcd display.
	@param none.
	@return none.
*/
void Lcd_Display::_set_Brightness()
{
	analogWrite(_pin, _brightness);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Sets the cursor anywhere on the 16x2 screen.
	@param the collom and the row where you would like the cursor to be.  
	@return none.
*/
void Lcd_Display::set_Cursor(uint8_t collumn, uint8_t row)
{
	_collumn = collumn;
	_row = row;
	_p_Lcd_Lib->setCursor(_collumn, _row);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Prints a message to the lcd display.
	@param a message.
	@return none.
*/
void Lcd_Display::print(String message)
{
	_message = message;
	_p_Lcd_Lib->print(_message);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Scrolls the display from left to right one block
	each time this method is called. 
	@param none
	@return none
*/
void Lcd_Display::scroll_Display()
{
	_p_Lcd_Lib->scrollDisplayLeft();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Clears the screen.
	@param none
	@return none
*/
void Lcd_Display::clear()
{
	_p_Lcd_Lib->clear();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Fades in the backligth to max intensity.
	@param none.
	@return none.
*/
void Lcd_Display::fade_In()
{
	_on = true;
	for (_brightness; _brightness <= 254; _brightness++)
	{
		_set_Brightness();
		delay(2);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Fades out the backlight.
	@param none.
	@return none.
*/
void Lcd_Display::fade_Out()
{
	for (_brightness; _brightness > 50; _brightness--)
	{
		_set_Brightness();
		delay(3);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Turns on the backlight to max intensity.
	@param none.
	@return none.
*/
void Lcd_Display::turn_On()
{
	_on = true;
	_brightness = 255;
	_set_Brightness();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Turns off the backlight.
	@param none
	@return none
*/
void Lcd_Display::turn_Off()
{
	_on = false;
	_brightness = 0;
	_set_Brightness();
	if (is_First_Time())
		_first_Time = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Checks if the lcd display is on
	@param none
	@return returns true if the lcd display is on. 
*/
bool Lcd_Display::is_On()
{
	if (_on)
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Checks if it is the first time the display is turned on. 
	@param none.
	@return Returns true if it is the first time. 
*/
bool Lcd_Display::is_First_Time()
{
	return _first_Time;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////