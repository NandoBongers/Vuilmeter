// 
// 
// 

#include "Bluetooth.h"
/*
	CONSTRUCTOR
*/
Bluetooth::Bluetooth()
{
	_message = "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Checks if there is data in the serial recaive buffer.
	@param none.
	@return returns true if there's data in the serial receive buffer.
*/
bool Bluetooth::data_Received()
{
	bool data_Received;

	if (Serial.available() > 0)
		data_Received = true;
	else
		data_Received = false;
	return data_Received;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Reads the first byte in the receive buffer and
	stores it in _incomming_Byte.
	@param none.
	@return none.
*/
void Bluetooth::read_Byte()
{
	_incomming_Byte = Serial.read();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Checks if the end of the line is reached.
	@param none.
	@return returns true if the end of the line has reached.
*/
bool Bluetooth::total_Message_Received()
{
	bool total_Message_Received = false;
	if (_incomming_Byte == '\n')
		total_Message_Received = true;
	else
		total_Message_Received = false;
	return total_Message_Received;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Reads the constructed message.
	@param none.
	@return returns the message as a string.
*/
String Bluetooth::read_Message()
{
	return _message;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Empty the message string.
	@param none.
	@return none.
*/
void Bluetooth::delete_Message()
{
	_message = "";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Fills the string with bytes.
	@param none.
	@return none.
*/
void Bluetooth::add_Byte_To_Message()
{
	_message = _message + _incomming_Byte;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////