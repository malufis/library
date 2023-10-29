#include "4a20pulsado.h"

//TODO: add your code here

int pins[] = { PORTS1, PORTS2, PORTS3, PORTS4, PORTS5, PORTS6 };

void sensorRead::converter4a20(float sensorData[]) {	
	for (int i = 0; i > 6; i++)
	{
		sensor[i] = (sensorData[i] / 147 * 1000);
	}
			
}
float sensorRead::getDataSensor(uint8 sensorPort) {	
	float vcc = 1.20 * 4096.0 / adc_read(ADC1, 17);
	float getDataSensor = ((analogRead(sensorPort) * vcc) / 4096);	
	return getDataSensor;	
}
void sensorRead::readSensor(void) {		
	for (unsigned int i = 0; i < maxSamples; i++) {
		sensorActual[i] = getDataSensor(pins[i]);
	
		if (sensorActual[i] > (bufferSensor[i] - 0.01) && sensorActual[i] < (bufferSensor[i] + 0.01)) {						
			sensor[i] = ((sensor[i] + bufferSensor[i]) / 2);
			bufferSensor[i] = sensor[i];
		}
		else {
			bufferSensor[i] = sensorActual[i];
		}
	}
}
void sensorRead::pulsein(void)
{		
	consumption = (millis() - timeConsumption);	
	timeConsumption = millis();		
	
}
void sensorRead::printSensor(float sensor[]) {
	
	/*for (unsigned int i = 0; i < maxSamples; i++) {
		if (sendData[i] == 0) {
			sendData[i] = sensor[i];			
		}
		else {
			
			if (sensor[i] >= sendData[i] - 0.01 && sensor[i] <= sendData[i] + 0.01) {
				Serial.println("not change Sensor : " + String(i));
			}
			else {
				sendData[i] = (sensor[i] + sendData[i]) / 2;
			}
		}
	} */
	
	Serial.println("estagio 2");

	d1Buffer = digitalRead(INPUT1);
	d2Buffer = digitalRead(INPUT2);
	d3Buffer = digitalRead(INPUT3);
	d4Buffer = digitalRead(INPUT4);
	delay(100);

	String printBuffer = "";
	
	printBuffer.concat("{\"CMD\":\"");
	printBuffer.concat(String("READER_SENSOR"));
	printBuffer.concat("\",");

	/*printBuffer.concat("\"SA1\":\"");
	printBuffer.concat(String(sendData[0]));
	printBuffer.concat("\",");

	printBuffer.concat("\"SA2\":\"");
	printBuffer.concat(String(sendData[1]));
	printBuffer.concat("\",");

	printBuffer.concat("\"SA3\":\"");
	printBuffer.concat(String(sendData[2]));
	printBuffer.concat("\",");

	printBuffer.concat("\"SA4\":\"");
	printBuffer.concat(String(sendData[3]));
	printBuffer.concat("\",");

	printBuffer.concat("\"SA5\":\"");
	printBuffer.concat(String(sendData[4]));
	printBuffer.concat("\",");

	printBuffer.concat("\"SA6\":\"");
	printBuffer.concat(String(sendData[5]));
	printBuffer.concat("\",");
	
	printBuffer.concat("\"PULSE\":\"");
	printBuffer.concat(String(consumption));
	printBuffer.concat("\",");*/

	printBuffer.concat("\"D1\":\"");
	printBuffer.concat(d1Buffer);
	printBuffer.concat("\",");
	
	printBuffer.concat("\"D2\":\"");
	printBuffer.concat(d2Buffer);
	printBuffer.concat("\",");
	
	printBuffer.concat("\"D3\":\"");
	printBuffer.concat(d3Buffer);
	printBuffer.concat("\",");
	
	printBuffer.concat("\"D4\":\"");
	printBuffer.concat(d4Buffer);
	printBuffer.concat("\",");
	

	printBuffer.concat("\",");
	printBuffer.concat("\"REALESE\":\"");
	printBuffer.concat("0");
	printBuffer.concat("\"}");	

	Serial.println(printBuffer);
	Serial3.println(printBuffer);
	Serial3.flush();

}
void sensorRead::vddSensor(void) {
	adc_reg_map* regs = ADC1->regs;
	regs->CR2 |= ADC_CR2_TSVREFE; // enable VREFINT and Temperature sensor
	// sample rate for VREFINT ADC channel and for Temperature sensor
	regs->SMPR1 |= (0b111 << 18); // sample rate temperature
	regs->SMPR1 |= (0b111 << 21); // sample rate vrefint
	adc_calibrate(ADC1);
}
boolean sensorRead::taskTime(long timeaction, long timeBuffer)
{
	timeBuffer = millis() - timeBuffer;
	if (timeBuffer > timeaction)
	{
		return true;
	}
	return false;
}
long timeTask::resetTime()
{
	return millis();	
}