// Bluetooth.h

#ifndef _BLUETOOTH_h
#define _BLUETOOTH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Bluetooth
{
public:
	Bluetooth();
	String read_Message();
	bool data_Received();	
	bool total_Message_Received();
	void read_Byte();
	void add_Byte_To_Message();	
	void delete_Message();

private:
	char _incomming_Byte;
	String _message;
};

#endif