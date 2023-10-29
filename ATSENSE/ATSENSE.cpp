#include "ATSENSE.h"

void ATSENSE::writeRegister(uint8_t thisRegister, uint8_t thisValue) {

	//uint8_t dataToSend = thisRegister & WRITE;
	byte dataToSend = thisRegister & WRITE;

#if DEBUG
	Serial.print(dataToSend, HEX);
	Serial.print("\t");
	Serial.println(thisValue, BIN);
#endif
	digitalWrite(SPI1_NSS_PIN, LOW);
	delay(20);

	SPI.transfer(dataToSend);
	SPI.transfer(thisValue);

	digitalWrite(SPI1_NSS_PIN, HIGH);
}

uint32_t ATSENSE::readRegister(uint8_t thisRegister, uint8_t bytesToRead) {

	uint32_t result = 0;

	digitalWrite(SPI1_NSS_PIN, LOW);
	result = readBytesFrom(thisRegister, bytesToRead);
	digitalWrite(SPI1_NSS_PIN, HIGH);
	return result;


}

uint32_t ATSENSE::readBytesFrom(uint8_t address, uint8_t numberOfBytes) {
	uint32_t result = 0;
	uint8_t dataToSend = address | READ;
	byte inByte = 0;

	result = SPI.transfer(dataToSend);
	result = SPI.transfer(0x00);
	numberOfBytes--;

	while (numberOfBytes > 0) {
		result = result << 8;
		inByte = SPI.transfer(0x00);
		result = result | inByte;
		numberOfBytes--;
	}
	return result;
}

void ATSENSE::changeAlicateCurrent(uint8_t alicateCurrente) {
	
	// gain 0x01 = off, 0x11 = 2x, 0x21 = 4x, 0x31 = 8x	
	switch(alicateCurrente) {
	case ALICATE_1V:
		writeRegister(SDI0, 0x11);
		writeRegister(SDI1, 0x01);
		writeRegister(SDV1, 0x01);
		writeRegister(SDI2, 0x01);
		writeRegister(SDV2, 0x01);
		writeRegister(SDI3, 0x01);
		writeRegister(SDV3, 0x01);
		break;
	case ALICATE_033V:
		writeRegister(SDI0, 0x11);
		writeRegister(SDI1, 0x31);
		writeRegister(SDV1, 0x01);
		writeRegister(SDI2, 0x31);
		writeRegister(SDV2, 0x01);
		writeRegister(SDI3, 0x31);
		writeRegister(SDV3, 0x01);
		break;
	}	
}

// Requer biblioteca SPI.h antes do 
boolean ATSENSE::begin() {
	Serial.println("Inicia o Setup");
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE1);
	SPI.setClockDivider(SPI_CLOCK_DIV16);
	pinMode(SPI1_NSS_PIN, OUTPUT);

	delay(1000);

	writeRegister(SOFT_NRESET, 0xFE);
	delay(100);
	writeRegister(SOFT_NRESET, 0x01);
	
	while ((readRegister(ATSR, 1) & 0x01) != 0x01) {
		delay(100);
	}
	writeRegister(ATCFG, 0x03);
	writeRegister(ANA_CTRL, 0x07);	
	writeRegister(ITCR, 0x04);
	writeRegister(ITOUTCR, 0x04);
	delay(200);
	
#if DEBUG
	Serial.println(String(readRegister(ATCFG, 1), BIN));
	Serial.println(String(readRegister(ANA_CTRL, 1), BIN));
	Serial.println(String(readRegister(ITOUTCR, 1), BIN));

	Serial.println("Iniciado");
#endif
	return true;
}

void ATSENSE::readData(uint32_t* I1, uint32_t* V1, uint32_t* I2, uint32_t* V2, uint32_t* I3, uint32_t* V3) {
	digitalWrite(SPI1_NSS_PIN, LOW);
	*I1 = readRegister(ADCI1_23_16, 3);
	*V1 = readRegister(ADCV1_23_16, 3);
	*I2 = readRegister(ADCI2_23_16, 3);
	*V2 = readRegister(ADCV2_23_16, 3);
	*I3 = readRegister(ADCI3_23_16, 3);
	*V3 = readRegister(ADCV3_23_16, 3);
	digitalWrite(SPI1_NSS_PIN, HIGH);
}

void ATSENSE::readData(uint32_t* I1, uint32_t* V1) {
	digitalWrite(SPI1_NSS_PIN, LOW);

	*I1 = readRegister(ADCI1_23_16, 3);
	*V1 = readRegister(ADCV1_23_16, 3);

	digitalWrite(SPI1_NSS_PIN, HIGH);
}

void ATSENSE::getFrequency(double *FR1, double *FR2, double *FR3) {
	*FR1 = frequency[0];
	*FR2 = frequency[1];
	*FR3 = frequency[2];
	return;
}