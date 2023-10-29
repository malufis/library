#include "Arduino.h"

class sensorRead
{
	public:
		float getSensorValue(uint8_t sensorPosition);
		long int pulseTime(long int timePulse);
		long int pulseCount(long int timeCount);
		float converter4a20(float sensorData);
		bool digitalPort(uint8_t mcuPortDigital);
		void outputAction(uint8_t mcuPortDigital, bool actionPort);	
};
