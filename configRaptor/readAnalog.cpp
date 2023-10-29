#include "readAnalog.h"
/* Function read port raw value */
int8_t readAnalog::readRawPort(int8_t sensorPort) {
	int8_t rawBuffer = analogRead(sensorPort);
	return rawBuffer;
}

/* Function converter data sensor for 4 a 20 ma */
float readAnalog::converter420ma(int8_t valueRaw) {
	float getDataSensor = ((valueRaw * 3.366666) / 4096);
	getDataSensor = (getDataSensor / 147 * 1000);
	return getDataSensor;
}

float readAnalog::converterVolts(int8_t valueRaw) {
	float getDataSensor = ((valueRaw * 3.36666) / 4096);	
	return getDataSensor;
}

/* Function compare data after with data before */
int8_t readAnalog::filterNoise(int8_t value, int8_t compareOffset, int8_t bufferValue) {
	uint16_t buffer;
	if (value <= (bufferValue + compareOffset) && value >= (bufferValue - compareOffset)) {
		buffer = (value + bufferValue) / 2;
		return buffer;
	}
	else {
		return value;
	}
}



