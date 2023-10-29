#ifndef _raptor4GESP_h
#define _raptor4GESP_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#endif

#include "initSetupRaptor.h"
#include "atcommand.h"


#define DEBUG4G 1

class raptor4g {

public:
	bool init();
	String _atcmd(const char* ATcommand, int timeout);
	void _atcmd(const char* ATcommand);	

	bool _responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2, const char* expected_answer3);
	bool _responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2);
	bool _waitResponse(const char* expected_answer, int timeout);
	bool _waitResponse(const char* expected_answer, const char* expected_answer2, int timeout);
	
	bool networkRegister();
	bool networkConnect();	
	bool networkConnected();
	bool networkOn();
	bool mqttOn(int idConnection);
	
	bool apnConnect(const char* apn, const char* login, const char* pass);	
	bool mqttSetup(int idConnection, const char* willQos, const char* willRetain, const char* willTopic, const char* willMsg, const char* session, const char* keepAlive);
	bool mqttConnect(int idConnection, const char* server, const char* port, const char* client, const char* user, const char* pass);
	bool mqttPublish(int idConnection, const char* topic, const char* data);
	bool mqttSubscribe(int idConnection, const char* topic, int msgid);
	bool mqttUnsubscribe(int idConnection, const char* topic);
	String mqttSubscribeGet(int idConnection);
	void mqttClientDisconnect(int idConnection);
	void mqttServerDisconnect(int idConnection);
	String getIMEI();	
	String getDHT();
	void syncDHT();
	String getSignal();
	bool powerOff();
	void powerON();
	
	char * converterStringChar(String buffConverter);

	String response;
	
	boolean modemStarted;
	boolean mqttStarted;
	boolean mqttSubscribeStarted;
	boolean waitResponse;
	boolean resetMqtt;
	

	bool printDebug;
	bool printDebugModem;
	uint countWait = 0;
	char bufferSet[100];
	char bufferSet2[100];

	int GMT;

	const char* apn;
	const char* user;
	const char* pass;

	int operatorCellphone;
	
};


