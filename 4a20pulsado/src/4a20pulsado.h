#pragma once
#include <stm32Fconfig.h>
//TODO: add your function declarations here

const int maxSamples = 6;

class timeTask
{
public:
	/* Primeiro Valor tempo de execução, Segundo Valor Buffer millis*/
	long timeTask1[2] = { 16, 0 };
	long timeTask2[2] = { 5000, 0 };
	long timeTask3[2] = { 60000, 0 };
	long resetTime();
};
class sensorRead
{
public:
	
	/*Variaveis de leitura do sensor*/
	float bufferSensor[maxSamples+1];
	float sensor[maxSamples+1];
	float consumption = 0;
	long timeConsumption = 0;
	float sendData[maxSamples+1];
	float sensorBuffer[maxSamples+1];
	float sensorActual[maxSamples+1];
	int d1Buffer = 0;
	int d2Buffer = 0;
	int d3Buffer = 0;
	int d4Buffer = 0;
	/*----------------------------------*/	
	
	void converter4a20(float sensorData[]);
	float getDataSensor(uint8 sensorPort);
	void readSensor(void);
	void pulsein(void);
	void printSensor(float sensor[]);
	void vddSensor(void);	
	boolean taskTime(long timeaction, long timeBuffer);	
};