#ifndef _INITCONFIG_h
#define _INITCONFIG_h

#define WIFIMESH	0x01
#define WIFI2G		0x02
#define LORA		0x03
#define NBIOT4G		0x04

#define	GATEWAY		0x01
#define	ROUTHER		0x02
#define	ENDPOINT	0x03 

class setupDeviceInit {

private:
	uint8_t deviceType;
	uint8_t deviceTypeConnection;	
	
public:		
	boolean setupState;
	
	uint8_t deviceTypeSelect(uint8_t deviceType);
	uint8_t deviceTypeConnectionSelect(uint8_t deviceTypeConnnection);	
	
	boolean dataloggerSelect(boolean datalooger);
};

