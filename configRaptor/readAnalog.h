#ifndef _READANALOG_h
#define _READANALOG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class readAnalog {
public:      
    int8_t readRawPort(int8_t sensorPort);    
    float converter420ma(int8_t valueRaw);
    float converterVolts(int8_t valueRaw);
    int8_t filterNoise(int8_t value, int8_t compareOffset, int8_t bufferValue);
};

#endif

