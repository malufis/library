#ifndef _initSetupRaptor_h
#define _initSetupRaptor_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#endif

#define ALERT1 19
#define ALERT2 23
#define RELAY4 21

#define RELAY1 25
#define RELAY2 27
#define RELAY3 18


//#define RESETSTM 21
#define RESETSTM 5

#define SDCHIP 4

/*---Tipo de Conexao WiFi---*/
#define WIFIMESH		1
#define WIFI2G			2

/*---Tipo de Conexao Externa---*/
#define LORA			3
#define NBIOT4G			4
#define NOT_RADIO		99
/*---------------------*/

/*---Tipo de Dispositivo---*/
#define	GATEWAY			1
#define	ROUTHER			2
#define	ENDPOINT		3 
#define NOT_DEVICE		99
/*---------------------*/

/*---    Modelo     ---*/
#define INDUSTRIAL			1
#define TRIFASICO			2
#define BIFASICO			3
#define PLUVIOMETRO			4
#define ARCONDICIONADO		5
#define AMBIENTE			6
#define AGUA				7
#define GELADEIRA			8
#define COMPRESSOR			9
#define PLACASOLAR			10
#define NIVEL				11
#define SENSOR4A20PULSADO	12
#define SENSOR4A20			13
#define SENSORPT100			14
#define PULSADO				15
#define OLEO				16
#define GUINDALTO			17
#define SAEC				18
#define SENSOR4A20TRIFASICO	19
#define NOT_MODEL			99
/*----------------------*/

/*---Tipo de Servidor---*/
#define	SERVER_EXTERNO		1
#define	AWS					2
#define	AZURE				3
#define	GOOGLE				4 
#define INTERNO				5
#define NOT_SERVER			99
/*---------------------*/


#define DEBUGSERIAL Serial
#define STM32 Serial2
#define HOSTNAME "MESH"

class setupDeviceInit {	
public:
	
	int deviceType;
	int deviceTypeConnection;
	int deviceTypeConnection2;	
	int deviceModel;
	int deviceServer;
	String deviceName;
	boolean setupState = false;		
	
	boolean actionState = false;
	
	String login = "r@pt0ra1r";
	String password = "r@pt0r.s3nh@";
	
	int deviceTypeSelect(int deviceType);
	int deviceTypeConnectionSelect(int deviceTypeConnnection);		
	boolean dataloggerSelect(boolean  dataloggerState);
	int deviceModelSelect(int deviceModel);
	boolean deviceSetup(boolean setupState);
	
	void raptorInit(void);
};