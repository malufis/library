#include "initSetupMCU.h"

void setupDeviceInit::calibraSensor()
{
	adc_reg_map *regs = ADC1->regs;
	regs->CR2 |= ADC_CR2_TSVREFE;	
	regs->SMPR1 |= (0b111 << 18); 
	regs->SMPR1 |= (0b111 << 21);
	adc_calibrate(ADC1);
}
void setupDeviceInit::initMCU(void)
{	
	///--- Configura��o de Portas entrada ATM90E32S ---///
	pinMode(CF1, INPUT_PULLDOWN);
	pinMode(CF2, INPUT_PULLDOWN);
	pinMode(CF3, INPUT_PULLDOWN);
	pinMode(CF4, INPUT_PULLDOWN);
	
	///--- Configura��o de Portas entrada 4a20 ma ---///
	pinMode(P1_4A20_MA, INPUT_ANALOG);
	pinMode(P2_4A20_MA, INPUT_ANALOG);
	pinMode(P3_4A20_MA, INPUT_ANALOG);
	
	///--- Configura��o de Portas entrada digitais ---///
	pinMode(INPUT1, INPUT_PULLDOWN);
	pinMode(INPUT2, INPUT_PULLDOWN);
	
	///--- Configura��o de Portas entrada 4a20 ma ---///
	pinMode(OUTPUT1, OUTPUT);
	pinMode(OUTPUT2, OUTPUT);
	pinMode(OUTPUT3, OUTPUT);
	
	
	///--- Configura��o de Portas Reset ---///
	pinMode(RESET_ESP32, OUTPUT);
	pinMode(RESET_STM32, OUTPUT);	
	
	///--- Configura��o da POrta Serial ---///
	DEGUG_SERIAL.begin(115200);
	while (!DEGUG_SERIAL) ;
	BG95.begin(115200);
	while (!BG95) ;
	ESP32_SERIAL.begin(115200);
	while (!ESP32_SERIAL) ;
	
	///--- Configura��o do watchdog ---///
	iwdg_init(IWDG_PRE_256, 15 * 156); 
	
	///--- Calibra��o das portas analogicas ---///
	calibraSensor();
	
}
const char* setupDeviceInit::converteStringChar(String buffConverter) {
	String buffServidor = "";
	buffServidor = buffConverter;
	char* buff = new char[buffServidor.length() + 1];
	strcpy(buff, buffServidor.c_str());
	return buff;
}
