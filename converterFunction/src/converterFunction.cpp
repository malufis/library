#include "converterFunction.h"

float sensorRead::getSensorValue(uint8_t sensorPosition)
{
	float vcc = 1.20 * 4096.0 / adc_read(ADC1, 17);
	float getDataSensor = ((analogRead(sensorPosition) * vcc) / 4096);
	getDataSensor = (getDataSensor / 147 * 1000);
	return getDataSensor;
}
long int sensorRead::pulseTime(long int timePulse)
{		
	long int timePulseBuffer = (millis() - timePulse);	
	return timePulseBuffer;	
}
long int sensorRead::pulseCount(long int timeCount)
{		
	return timeCount++;	
}
float sensorRead::converter4a20(float sensorData) {	
	float sensor = ((sensorData / 147) * 1000);
	return sensor;
}
bool  sensorRead::digitalPort(uint8_t mcuPortDigital)
{
	if (digitalRead(mcuPortDigital)){return true;}
	return false;
}

void sensorRead::outputAction(uint8_t mcuPortDigital, bool actionPort)
{
	digitalWrite(mcuPortDigital, actionPort);
}

