// 
// 
// 

#include "Sd_Card.h"
/*
	CONSTRUCTOR
	@param the digital output pin on the Arduino
		   where the cs pin of the sd card reader
		   is connected to. And a pointer to a
		   File object.
	@return none.
*/
SD_Card::SD_Card(uint8_t cs_Pin, File *p_File)
{
	_cs_Pin = cs_Pin;
	_p_File = p_File;

	pinMode(_cs_Pin, OUTPUT);	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Stores a measurement on the sd card.
	@param The name of the file on the
		   sd card, today's date and the
		   data of the sensor that must be stored.
	@return none.
*/
void SD_Card::write_Measurement(String file_Name, String date, int data)
{
	*_p_File = SD.open((file_Name + ".txt"), FILE_WRITE);
	if (_p_File)
	{
		_p_File->println(date + ',' + data);
		_p_File->close();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Initialize the sd card.
	@param none.
	@return none.
*/
void SD_Card::connect()
{
	SD.begin(_cs_Pin);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Open a file on the sd card.
	@param the file name of the file that 
		   must be opened. 
	@return none.
*/
File SD_Card::open_File(String file_Name)
{
	return(SD.open(file_Name + ".txt"));
}

void SD_Card::write_Kpi(String file_Name, String kpi)
{
	SD.remove(file_Name + ".txt");
	*_p_File = SD.open((file_Name + ".txt"), FILE_WRITE);
	if (_p_File)
	{
		_p_File->println(kpi);
		_p_File->close();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////