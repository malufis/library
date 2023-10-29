#pragma once
#include <portaMCU.h>
#include <libmaple/iwdg.h>
#include "Arduino.h"



#define LOG					1 
#define DEBUG				1
	
#define DEGUG_SERIAL		Serial1
#define BG95				Serial2
#define ESP32_SERIAL		Serial3

class setupDeviceInit {	
public:		
	void initMCU(void);
	void calibraSensor(void);
	const char* converteStringChar(String buffConverter);
};
