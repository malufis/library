/*
 Name:		RaptorRFID.cpp
 Created:	17/11/2017 09:41:54
 Author:	willi
 Editor:	http://www.visualmicro.com
*/

#include "RaptorRFID.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "HardwareSerial.h"

String RaptorRFID::setupPower(int power) {
	String buff = "";
	buff += char(0xaa);
	buff += char(0x04);
	buff += char(0x02);
	buff += char(0x01);
	buff += char(power);
	buff += char(0x55);
	return buff;
}

String RaptorRFID::selectMifareCard() {
	String buff = "";
	buff += char(0xBA);
	buff += char(0x01);	
	buff += char(0x55);
	return buff;
}

String RaptorRFID::startReadingCard() {
	String buff;
	buff += char(0xaa);
	buff += char(0x03);
	buff += char(0x11);
	buff += char(0x03);
	buff += char(0x55);
	return buff;
}

String RaptorRFID::stopReadingCard() {
	char* buff;
	buff += char(0xaa);
	buff += char(0x02);
	buff += char(0x12);
	buff += char(0x55);
	return buff;
}

String RaptorRFID::getAllInfoOf(String idCard){
	char* buff;
	int len = idCard.length() + 10;
	buff += char(0xaa);
	buff += char(len);
	buff += char(0x13);
	for (int i = 0; i < 4; i++) {
		buff += char(0x00);
	}
	buff += char(0x03);
	buff += char(0x01);
	buff += char(0x19);
	for (int i = 0; i <= idCard.length(); i++) {
		buff += char(idCard[i]);
		delay(1);
	}
	buff += char(0x01);
	buff += char(0x55);
}

String RaptorRFID::writeIdOnCard(String idCard){
	char* buff;
	int len = idCard.length() + 9;
	buff += char(0xaa);
	buff += char(len);
	buff += char(0x25);
	for (int i = 0; i < 4; i++) {
		buff += char(0);
	}
	buff += char(0x01);
	buff += char(0x01);
	buff += char(idCard.length());
	buff += char(0x30);
	for (int i = 0; i <= idCard.length(); i++) {
		buff += char(idCard[i]);
		delay(1);
	}
	buff += char(0x40);
	buff += char(0x40);
	buff += char(0x55);
}

String RaptorRFID::writeDataOnCard(String dataCard) {
	char* buff;
	int len = dataCard.length() + 9;
	buff += char(0xaa);
	buff += char(len);
	buff += char(0x14);
	for (int i = 0; i < 4; i++) {
		buff += char(0);
	}
	buff += char(0x01);
	buff += char(0x01);
	buff += char(dataCard.length());
	for (int i = 0; i <= dataCard.length(); i++) {
		buff += char(dataCard[i]);
		delay(1);
	}
	buff += char(0x55);
	return buff;
}

String RaptorRFID::eraseDataOnCard() {
	char* buff;
	buff += char(0xaa);
	buff += char(0x0d);
	buff += char(0x15);
	for (int i = 0; i < 4; i++) {
		buff += char(0x00);
	}
	buff += char(0x01);
	buff += char(0x01);
	buff += char(0x01);
	buff += char(0x08);
	buff += char(0x00);
	buff += char(0x00);
	buff += char(0x01);
	buff += char(0x55);
	return buff;
}

boolean RaptorRFID::isThisCardNew(String cards[], String card, int leng) {
	for (int i = 0; i <= leng; i++) {
		if (cards[i].equals(card)) {
			return false;
		}
	}
	return true;
}

void Antena::begin(Stream &serial) {
	_serial = &serial;
}

void Antena::setSerial(Stream &serial) {
	_serial = &serial;
}

void Antena::send(String command) {
	delay(1000);
	for (int i = 0; i < command.length(); i++) {
		_serial->write(command[i]);
	}
}

String Antena::readPackt() {
	String buff = "";
	
	while (available() != 0) {
		char thisByte;
		thisByte = read();
		if (thisByte != byte(0xaa) && thisByte != byte(0x55)) {
			if (thisByte > 33 && thisByte < 176) {
				buff += thisByte;
				Serial.print(thisByte,HEX);
			}
		}
		if (thisByte == byte(0x55)) { break; }
	}
	Serial.println();
	return buff;
}
/*
String Antena::getAllCards() {
	int quantidadeCartao = 0;
	boolean lerCartao = false;
	String cartao = "";
	String idCartao[20];

	while (available() != 0) {
		byte thisByte = read();

		// Testa o inicio da String	
		if (thisByte == byte(0xaa)) {
			lerCartao = true;
		}

		// Testa o final da String e inicia uma nova	
		if (thisByte == byte(0x55)) {
			lerCartao = false;

			if (rfid.isThisCardNew(idCartao, cartao)) {
				idCartao[quantidadeCartao] = cartao;
				quantidadeCartao++;
			}
			cartao = "";
		}

		// Le os IDS dos Cartoes que estao na porta Serial		
		if (lerCartao) {
			if (thisByte != byte(0xaa)) {
				if (thisByte > 33 && thisByte < 176) {
					char converteChar = thisByte;
					cartao += converteChar;
					microsecondsToClockCycles(1) * (1000 / 16);
				}
			}
		}
	}
}
*/
bool Antena::available() {
	return _serial->available();
}

uint8_t Antena::read() {
	return _serial->read();
}

void Antena::flush() {
	_serial->flush();
}

void Antena::write(uint8_t val) {
	_serial->write(val);
}
