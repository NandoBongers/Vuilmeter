// Dirt_Sensor.h

#ifndef _DIRT_SENSOR_h
#define _DIRT_SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Dirt_Sensor
{
public:
	Dirt_Sensor(uint8_t sensor_Pin, uint8_t ir_Pin);
	void measure();
	void calculate_Dirt_Level();

	double clean_Window_Value;
	double dirty_Window_Value;
	double current_Value;
	double dirt_Level;

private:
	void _ir_On(); 
	void _ir_Off(); 
	uint8_t _sensor_Pin;
	uint8_t _ir_Pin;
};

#endif