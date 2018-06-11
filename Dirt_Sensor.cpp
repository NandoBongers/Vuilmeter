// 
// 
// 

#include "Dirt_Sensor.h"
/*
	CONSTRUCTOR
	@param analog input pin of the Arduino where the
				  sensor output is attached to. Digital
				  output pin of the Arduino where the internal
				  IR led of the sensor is attached to.
*/
Dirt_Sensor::Dirt_Sensor(uint8_t sensor_Pin, uint8_t ir_Pin)
{
	_sensor_Pin = sensor_Pin;
	_ir_Pin = ir_Pin;

	pinMode(_sensor_Pin, INPUT);
	pinMode(_ir_Pin, OUTPUT);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Measures the reflection of the window at night
	by shining the IR led and calculating the avarage
	output value of the sensor. When the measurement is 
	finished, the new dirt level will calculated.
	@param none.
	@return none.
*/
void Dirt_Sensor::measure()
{
	//Set the amount of samples
	const int samples = 10;
	long int total;
	
	//Turn ir on and wait 1 minute
	_ir_On();
	delay(60000);

	//Measure the sensor and take an avarage
	for (int i = 0; i < samples; i++)
	{
		current_Value = analogRead(_sensor_Pin);
		total = total + current_Value;

		delay(1);
	}
	current_Value = total / samples;
	calculate_Dirt_Level();

	//Turn ir off
	_ir_Off();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Turn on the internal IR led of the sensor.
	@param none.
	@return none.
*/
void Dirt_Sensor::_ir_On()
{
	digitalWrite(_ir_Pin, HIGH);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Turn off the internal IR led of the sensor.
	@param none.
	@return none.
*/
void Dirt_Sensor::_ir_Off()
{
	digitalWrite(_ir_Pin, LOW);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Calculates the dirt level in percentages. 
	@param none.
	@return none.
*/
void Dirt_Sensor::calculate_Dirt_Level()
{
	//Serial.print("Current value: ");
	//Serial.println(current_Value);

	//Serial.print("Clean window: ");
	//Serial.println(clean_Window_Value);

	//Serial.print("Dirty window: ");
	//Serial.println(dirty_Window_Value);

	if (current_Value <= clean_Window_Value)
	{
		dirt_Level = 0;
	}
	else if (current_Value >= dirty_Window_Value)
	{
		dirt_Level = 100;
	}
	else
	{
		dirt_Level = 100 * ((current_Value - clean_Window_Value) / (dirty_Window_Value - clean_Window_Value));
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////