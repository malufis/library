#include "initSetupRaptor.h"

int setupDeviceInit::deviceTypeSelect(int deviceType) {
	return deviceType;		
}
int setupDeviceInit::deviceTypeConnectionSelect(int deviceTypeConnnection) {
	return deviceTypeConnnection;
}	
boolean setupDeviceInit::dataloggerSelect(boolean datalooger) {
	return datalooger;
}
int setupDeviceInit::deviceModelSelect(int deviceModel) {
	return deviceModel;
}	
boolean setupDeviceInit::deviceSetup(boolean setupState) {
	return setupState;
}
void setupDeviceInit::raptorInit(void)
{
	DEBUGSERIAL.begin(115200);
	while (!DEBUGSERIAL);
	
	STM32.begin(115200);
	while (!STM32);
	
	pinMode(ALERT1, OUTPUT);
	pinMode(ALERT2, OUTPUT);
	
	

	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);	
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
	
	//digitalWrite(ALERT1, LOW);
	//digitalWrite(ALERT2, LOW);
	//digitalWrite(ALERT3, LOW);	

	//digitalWrite(RELAY1, LOW);
	//digitalWrite(RELAY2, LOW);
	//digitalWrite(RELAY3, LOW);
	
}