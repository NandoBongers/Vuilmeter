/*
Name:		Vuilmeter.ino
Created:	23/05/2018 16:26
Author:	Nando Bongers
*/
#include "Timer.h"
#include "Lcd_Display.h"
#include "Bluetooth.h"
#include "Real_Time_Clock.h"
#include "Sd_Card.h"
#include "Dirt_Sensor.h"
#include "Four_Digit_Display.h"
#include "Button.h"

//Libraries 
#include <LiquidCrystal_I2C.h>
#include <DS3232RTC.h>
#include <TM1637Display.h>
#include <SD.h>
#include <SPI.h>

//Button
Button button(6);

//SD Card
File file;
SD_Card sd_Card(4, &file);

//Lcd display
LiquidCrystal_I2C lcd_Lib(0x27, 16, 9);
Lcd_Display lcd_Display(&lcd_Lib, 9);

//Real time clock
Real_Time_Clock rtc;

//4 digit display / 7 segment display
TM1637Display four_Digit_Display_Lib(2, 8);
Four_Digit_Display four_Digit_Display(&four_Digit_Display_Lib);

//Dirt sensor
Dirt_Sensor dirt_Sensor(A1, 7);

//Bluetooth
Bluetooth bluetooth;

//Timer
Timer timer;
Timer error;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
	//Initialisation
	//NOTE: The current order in which these functions are called is very important. 
	Serial.begin(38400);
	lcd_Display.begin();
	rtc.begin();
	get_Kpi();
	get_Last_Measurement();	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{
	four_Digit_Display.print(rtc.time());
	bluetooth_Communication();
	measure_Window();
	display_Control();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// *BLUETOOTH* 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Handles the bluetooth communication.
@param none.
@return none.
*/
void bluetooth_Communication()
{
	while (bluetooth.data_Received())
	{
		bluetooth.read_Byte();
		if (bluetooth.total_Message_Received())
		{
			if (bluetooth.read_Message() == "bam")
			{
				send_Data();
			}
			else if (bluetooth.read_Message() == "store_kpi")
			{
				store_Kpi();
			}
			else if (bluetooth.read_Message() == "get_kpi")
			{
				send_Kpi();
			}
			else
			{
				Serial.println("bam_error");
			}
			bluetooth.delete_Message();
		}
		else
			bluetooth.add_Byte_To_Message();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Sends every string from dirt.txt over bluetooth.
	@param none.
	@return none.
*/
void send_Data()
{
	sd_Card.connect();
	file = sd_Card.open_File("dirt");
	if (file)
	{
		while (file.available())
		{
			Serial.println(file.readStringUntil('\n'));
		}
	}
	else
	{
		Serial.println("bam_error");
	}
	file.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Gets the kpi from the user application, stores it on the sd card and calls some functions to recalculate the new values. 
Sends every string from dirt.txt over bluetooth.
@param none.
@return none.
*/
void store_Kpi()
{
	bluetooth.delete_Message();
	Serial.println("ok");

	error.reset();
	while (!bluetooth.data_Received())
	{
		if (error.seconds() > 4)
			break;
	}

	while (bluetooth.data_Received())
	{
		bluetooth.read_Byte();
		if (bluetooth.total_Message_Received())
		{
			set_Kpi(bluetooth.read_Message());
			get_Last_Measurement();
			break;
		}
		bluetooth.add_Byte_To_Message();
		delay(1);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Sends every string from kpi.txt over bluetooth.
@param none.
@return none.
*/
void send_Kpi()
{
	sd_Card.connect();
	file = sd_Card.open_File("kpi");
	if (file)
	{
		while (file.available())
		{
			Serial.println(file.readStringUntil('\n'));
		}
	}
	else
	{
		Serial.println("bam_error");
	}
	file.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// *DISPLAY* 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Controls the lcd display.
@param none.
@return none.
*/
void display_Control()
{
	if (lcd_Display.is_On())
	{
		if (timer.seconds() > 11)
		{
			lcd_Display.turn_Off();
		}
		else if (timer.seconds() > 7)
		{
			lcd_Display.fade_Out();
			if (button.is_Pressed())
			{
				lcd_Display.turn_On();
				timer.reset();
				delay(1000);
			}		
		}
		else if (button.is_Pressed())
		{
			kpi_Screen();
			timer.reset();
			delay(3000);
			main_Screen();
		}
	}
	else
	{
		lcd_Display.clear();
		if (button.is_Pressed())
		{
			if (timer.seconds() > 20 || lcd_Display.is_First_Time())
			{
				lcd_Display.fade_In();
				home_Screen();
				delay(2000);
			}
			main_Screen();
			if (!lcd_Display.is_On())
				lcd_Display.fade_In();
			timer.reset();
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Homescreen settings.
@param none.
@return none.
*/
void home_Screen()
{
	lcd_Display.clear();
	lcd_Display.set_Cursor(0, 0);
	lcd_Display.print("                 **    BAM     **");
	lcd_Display.set_Cursor(0, 1);
	lcd_Display.print("                 ** Groningen  **");

	for (int i = 0; i <= 16; i++)
	{
		lcd_Display.scroll_Display();
		delay(40);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Mainscreen settings.
@param none.
@return none.
*/
void main_Screen()
{
	String dirt_Level = String(dirt_Sensor.dirt_Level);
	while (dirt_Level.length() < 8)
	{
		dirt_Level = ' ' + dirt_Level;
	}
	dirt_Level = dirt_Level + '%';
	lcd_Display.clear();
	lcd_Display.set_Cursor(0, 0);
	lcd_Display.print("WAARDE:" + dirt_Level);
	lcd_Display.set_Cursor(0, 1);
	lcd_Display.print("N.BONGERS       ");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Kpi settings.
@param none.
@return none.
*/
void kpi_Screen()
{
	String clean_Window_Value = String(dirt_Sensor.clean_Window_Value, 0);
	String dirty_Window_Value = String(dirt_Sensor.dirty_Window_Value, 0);
	while (clean_Window_Value.length() < 9)
	{
		clean_Window_Value = ' ' + clean_Window_Value;
	}
	while (dirty_Window_Value.length() < 9)
	{
		dirty_Window_Value = ' ' + dirty_Window_Value;
	}
	lcd_Display.clear();
	lcd_Display.set_Cursor(0, 0);
	lcd_Display.print("SCHOON:" + clean_Window_Value);
	lcd_Display.set_Cursor(0, 1);
	lcd_Display.print("VIES  :" + dirty_Window_Value);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// *SD CARD* 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Gets the value of last stored measurement and calculates the current dirt level.
@param none.
@return none.
*/
void get_Last_Measurement()
{
	String last_Stored_String = "";
	String current_Value = "";
	int index = 0;

	sd_Card.connect();
	file = sd_Card.open_File("dirt");
	while (file.available())
	{
		last_Stored_String = file.readStringUntil('\n');
	}
	file.close();

	error.reset();
	while(last_Stored_String[index]!=',')
	{
		index++;
		if (error.seconds() > 2)
			break;
	}
	index++;
	while (index < last_Stored_String.length())
	{
		current_Value = current_Value + last_Stored_String[index];
		index++;
	}
	
	dirt_Sensor.current_Value = current_Value.toInt();
	dirt_Sensor.calculate_Dirt_Level();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Gets the kpi value that is stored in kpi.txt on the sd card of the dirt detector.
@param none.
@return none.
*/
void get_Kpi()
{
	String kpi_String = "";
	String clean_Window_Value = "";
	String dirt_Window_Value = "";
	int index = 0;

	sd_Card.connect();
	file = sd_Card.open_File("kpi");
	if (file)
	{
		kpi_String = file.readStringUntil('\n');
		error.reset();
		while (kpi_String[index] != ',')
		{
			clean_Window_Value = clean_Window_Value + kpi_String[index];
			index++;
			if (error.seconds() > 2)
				break;
		}
		index++;
		error.reset();
		while (index < kpi_String.length())
		{
			dirt_Window_Value = dirt_Window_Value + kpi_String[index];
			index++;
		}
	}
	dirt_Sensor.clean_Window_Value = clean_Window_Value.toDouble();
	dirt_Sensor.dirty_Window_Value = dirt_Window_Value.toDouble();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_Kpi(String message)
{
	sd_Card.connect();
	sd_Card.write_Kpi("kpi", message);
	int index = 0;
	String clean_Window_Value = "";
	String dirty_Window_Value = "";

	error.reset();
	while (message[index] != ',')
	{
		clean_Window_Value = clean_Window_Value + message[index];
		index++;

		if (error.seconds() > 2)
			break;
	}
	index++;
	while (index < message.length())
	{
		dirty_Window_Value = dirty_Window_Value + message[index];
		index++;
	}
	dirt_Sensor.clean_Window_Value = clean_Window_Value.toDouble();
	dirt_Sensor.dirty_Window_Value = dirty_Window_Value.toDouble();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Measures the reflection of a window at night.
	the results are being stored to the sd card.
	@param none.
	@return none.
*/
void measure_Window()
{
	// If the time is 1:00 AM
	if (rtc.time() == 100)
	{
		dirt_Sensor.measure();
		sd_Card.connect();
		sd_Card.write_Measurement("dirt", rtc.date(), dirt_Sensor.current_Value);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////