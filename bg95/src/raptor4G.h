#pragma once

#ifndef _raptor4G_h
#define _raptor4G_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#endif
#include <atcommand.h>

#define POWERPIN PC5
#define serialDebug Serial
#define serial4G Serial2
#define serialESP32 Serial3

#define GF(x) x

class raptor4g {

public:
	bool init();
	String _atcmd(const char* ATcommand, int timeout);
	void _atcmd(const char* ATcommand);
	
	bool _responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2, const char* expected_answer3, const char* expected_answer4);
	bool _responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2, const char* expected_answer3);
	bool _responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2);	
	bool _responseAT(String atCommand, const char* expected_answer1);
	bool _waitResponse(const char* expected_answer, int timeout);	
	bool _waitResponse(const char* expected_answer, const char* expected_answer2, int timeout);
	String _waitResponseString(const char* expected_answer, int timeout);
	
	bool networkRegister();
	bool networkConnect();
	bool disconnectNetwork();
	bool networkConnected();
	bool networkOn();
	bool dnsOn();
	bool mqttOn(int idConnection);
	
	bool apnConnect(const char* apn, const char* login, const char* pass);	
	bool mqttSetup(int idConnection, const char* willQos, const char* willRetain, const char* willTopic, const char* willMsg, const char* session, const char* keepAlive);
	bool mqttConnect(int idConnection, const char* server, const char* port, const char* client, const char* user, const char* pass);
	//bool mqttPublish(int idConnection, const char* topic, const char* data);
	bool mqttPublish(int idConnection, const char* topic, String data);
	bool mqttSubscribe(int idConnection, int msgId, const char* topic);
	bool mqttUnsubscribe(int idConnection, int msgId, const char* topic);
	String mqttSubscribeGet(int idConnection);
	boolean mqttSubscribeGetData(int idConnection); 
	bool mqttClientDisconnect(int idConnection);
	bool mqttServerDisconnect(int idConnection);
	String getInfoNetwork();
	String getIMEI();	
	String getSimCard();	
	String getCIMI();
	String getDHT();
	void syncDHT();
	String getSignalPower();
	String getSignal();
	String getOperator();
	String getModuleVersion();
	String getIp();
	bool powerOff();
	void powerON();
	String getSubscribe();
	bool connectionGPS();
	String  getGPS();
	bool ping();
	
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
	char bufferSet[256];
	char bufferSet2[100];

	int GMT;

	const char* apn;
	const char* user;
	const char* pass;

	int operatorCellphone;
	
	int year;
	int month;
	int day;
	int hour;
	int minutes;
	int seconds;
	
	int selectOperator;
};


