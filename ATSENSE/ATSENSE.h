/*
 Name:		ATSENSE.h
 Created:	22/03/2018 08:47:47
 Author:	willi
 Editor:	http://www.visualmicro.com
*/

#ifndef _ATSENSE_h
#define _ATSENSE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SPI.h>

#define DEBUG 1
#define ADCI0_TAG 0x00
#define ADCI0_23_16 0x01
#define ADCI0_15_8 0x02
#define ADCI0_7_0 0x03
#define ADCI1_TAG 0x04
#define ADCI1_23_16 0x05
#define ADCI1_15_8 0x06
#define ADCI1_7_0 0x07
#define ADCV1_TAG 0x08
#define ADCV1_23_16 0x09
#define ADCV1_15_8 0x0A
#define ADCV1_7_0 0x0B
#define ADCI2_TAG 0x0C
#define ADCI2_23_16 0x0D
#define ADCI2_15_8 0x0E
#define ADCI2_7_0 0x0F
#define ADCV2_TAG 0x10
#define ADCV2_23_16 0x11
#define ADCV2_15_8 0x12
#define ADCV2_7_0 0x13
#define ADCI3_TAG 0x14
#define ADCI3_23_16 0x15
#define ADCI3_15_8 0x16
#define ADCI3_7_0 0x17
#define ADCV3_TAG 0x18
#define ADCV3_23_16 0x19
#define ADCV3_15_8 0x1A
#define ADCV3_7_0 0x1B
#define SDI0 0x20
#define SDI1 0x21
#define SDV1 0x22
#define SDI2 0x23
#define SDV2 0x24
#define SDI3 0x25
#define SDV3 0x26
#define ANA_CTRL 0x27
#define ATCFG 0x28
#define ATSR 0x29
#define ITOUTCR 0x2A
#define ITCR 0x2B
#define ITSR 0x2C
#define SOFT_NRESET 0x2D

#define SPI1_NSS_PIN PA4
#define INTERRUPT PB5

#define ALICATE_1V 0X01
#define ALICATE_033V 0X02

const byte READ = 0b10000000;     // SCP1000's read command
const byte WRITE = 0b01111111;   // SCP1000's write command

#define sine32(x) ((x) > 0x7FFFFF ? long(x- 0xFFFFFF) : long(x))
class ATSENSE {
public:
	boolean begin();
	void writeRegister(uint8_t thisRegister, uint8_t thisValue);
	uint32_t readRegister(uint8_t thisRegister, uint8_t bytesToRead);
	uint32_t readBytesFrom(uint8_t address, uint8_t numberOfBytes);
	void readData(uint32_t* I1, uint32_t* V1);
	void readData(uint32_t* I1, uint32_t* V1, uint32_t* I2, uint32_t* V2, uint32_t* I3, uint32_t* V3);
	void getFrequency(double *FR1, double *FR2, double *FR3);
	void changeAlicateCurrent(uint8_t alicateCurrente); 
	private:
	
	double prevValue[3] = { 0, 0, 0 };
	double frequency[3] = { 0, 0, 0 };
	unsigned long millisFreq[3] = { 0, 0, 0 };
};
#endif

