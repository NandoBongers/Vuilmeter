// Lcd_Display.h

#ifndef _LCD_DISPLAY_h
#define _LCD_DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <LiquidCrystal_I2C.h> 
#else
	#include "WProgram.h"
#endif

class Lcd_Display
{
public:
	Lcd_Display(LiquidCrystal_I2C *p_Lcd_Lib, uint8_t pin);
	void begin();
	void fade_In();
	void fade_Out();
	void turn_Off();
	void turn_On();
	void set_Cursor(uint8_t collumn, uint8_t row);
	void print(String message);
	void scroll_Display();
	void clear();
	bool is_On();
	bool is_First_Time();

private:
	void _set_Brightness();

	LiquidCrystal_I2C *_p_Lcd_Lib;
	uint8_t _brightness;
	uint8_t _collumn;
	uint8_t _row;
	String _message;	
	uint8_t _pin;
	bool _on;
	bool _first_Time;
};

#endif