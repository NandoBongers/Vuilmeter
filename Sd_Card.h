// Sd_Card.h

#ifndef _SD_CARD_h
#define _SD_CARD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include <SD.h>
	#include <SPI.h>
#else
	#include "WProgram.h"
#endif
class SD_Card
{
public:
	SD_Card(uint8_t cs_Pin, File *temp_File);
	void write_Measurement(String file_Name, String date, int data);
	void write_Kpi(String file_Name, String kpi);
	void connect();
	File open_File(String file_Name);
private:
	//Chip select pin
	uint8_t _cs_Pin;	
	File *_p_File;
};

#endif