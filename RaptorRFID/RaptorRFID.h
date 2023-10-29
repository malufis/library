/*
 Name:		RaptorRFID.h
 Created:	17/11/2017 09:41:54
 Author:	willi
 Editor:	http://www.visualmicro.com
*/

#ifndef _RaptorRFID_h
#define _RaptorRFID_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <inttypes.h>

class RaptorRFID {
public:

	// Comandos
	String startReadingCard();
	String stopReadingCard();
	String writeIdOnCard(String idCard);
	String writeDataOnCard(String dataCard);
	String eraseDataOnCard();
	String getAllInfoOf(String idCard);
	String setupPower(int power);
	boolean isThisCardNew(String cards[], String card, int leng);
	String selectMifareCard();

private:
};

class Antena {
public:
	boolean available();
	void begin(Stream &serial);
	void send(String command);
	String readPackt();
//	String getAllCards();

private:
	uint8_t read();
	void write(uint8_t val);
	void setSerial(Stream &serial);
	void flush();
	Stream* _serial;
};
#endif

