#pragma once

//TODO: add your function declarations here
#include <Arduino.h>

#define POWERPIN PC5

/*#define serialDebug Serial
#define serial4G Serial1
#define serialESP32 Serial2*/

#define PORTS1 PA0
#define PORTS2 PA1
#define PORTS3 PC4
#define PORTS4 PC5
#define PORTS5 PB0
#define PORTS6 PB1

//#define INPUT1 PB3
//#define INPUT2 PB4
#define INPUT1 PC0
#define INPUT2 PC1
#define INPUT3 PC2
#define INPUT4 PC3

class setupStm32Init {	
public:

	void stm32Init(void);
};
