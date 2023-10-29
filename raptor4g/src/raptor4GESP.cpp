#include "raptor4GESP.h"


void raptor4g::_atcmd(const char* ATcommand) {	
	STM32.print(ATcommand);
	if (DEBUG4G) DEBUGSERIAL.println(ATcommand);

}
String raptor4g::_atcmd(const char* ATcommand, int timeout) {
	countWait = 0;
	response = "";

	STM32.println(ATcommand);
	
	while(!STM32.available()) {
		
		if (countWait > timeout) {
			break;
		}
		countWait++;
		delay(1);
	}
	if (STM32.available() > 0) {		
		response = (STM32.readString());
		if (DEBUG4G) DEBUGSERIAL.println(response);		
	}	
	return response;
}

bool raptor4g::_responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2, const char* expected_answer3) {
	
	const char* responseAction = converterStringChar(atCommand);
	
	if (strstr(responseAction, expected_answer1) != NULL) {	
		return true;
	}
	if (strstr(responseAction, expected_answer2) != NULL) {		
		return true;
	}
	if (strstr(responseAction, expected_answer3) != NULL) {		
		return false;
	}
	STM32.flush();
	return false;
}
bool raptor4g::_responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2) {
	
	const char* responseAction = converterStringChar(atCommand);
	
	if (strstr(responseAction, expected_answer1) != NULL) {
		return true;
	}
	else if (strstr(responseAction, expected_answer2) != NULL) {
		return false;
	}
	return false;
}

bool raptor4g::init() {
	if (!networkOn()) {

		countWait = 0;
		if (DEBUG4G) DEBUGSERIAL.println("Wait POWER ON Module");

		while (!_waitResponse(RESP_READY, 10000)) {
			if (DEBUG4G) DEBUGSERIAL.print("*");			
		}

		if (!_responseAT(_atcmd(GET_SIMMEFFECTS, 5000), RESP_SIMMEFFECTS, ERROR4G)) {
			_atcmd(SET_SIMMEFFECTS, 5000);
			delay(2000);
		}

		if (!_responseAT(_atcmd(GET_NWSCANSEQ, 5000), RESP_NWSCANSEQ, ERROR4G)) {
			_atcmd(SET_QCFG_NWSCANSEQ, 5000);
			delay(2000);
		}

		if (!_responseAT(_atcmd(GET_NWSCANMODE, 5000), RESP_NWSCANMODE, ERROR4G)) {
			_atcmd(SET_QCFG_NWSCANMODE, 5000);
			delay(2000);
		}

		if (!_responseAT(_atcmd(GET_BAND, 5000), RESP_BAND, ERROR4G)) {
			_atcmd(SET_QCFG_BAND, 5000);
			delay(2000);
		}

		if (!_responseAT(_atcmd(GET_IOTOPMODE, 5000), RESP_IOTOPMODE, ERROR4G)) {
			_atcmd(SET_QCFG_IOTOPMODE, 5000);
			delay(2000);
		}

		if (DEBUG4G) DEBUGSERIAL.println("Started Setup 4G");
		
		_atcmd(RESET_DEFAULT, 5000);

		if (_responseAT(_atcmd(ATI, 5000), OK4G, ERROR4G)) {
			if (_responseAT(_atcmd(ATV1, 30000), OK4G, ERROR4G)) {
				if (printDebugModem) {
					_responseAT(_atcmd(SET_ECHO_ON, 5000), OK4G, ERROR4G);
				}
				else {
					_responseAT(_atcmd(SET_ECHO_OFF, 5000), OK4G, ERROR4G);
				}

				if (_responseAT(_atcmd(SET_CMEE, 5000), OK4G, ERROR4G)) {
					_atcmd(SET_URC, 5000);

					_atcmd(SET_SINCDHTOFF, 5000);
					delay(2000);
					_atcmd(SET_SINCDHTON, 5000);

					if (_responseAT(_atcmd(SET_IPR, 5000), OK4G, ERROR4G)) {


						if (_responseAT(_atcmd(GET_CPIN, 5000), RESP_CPIN, ERROR4G)) {

							return true;
						}
						else {
							if (DEBUG4G) DEBUGSERIAL.println("SIM CARD no init");

							return false;
						}
					}
					else {
						if (DEBUG4G) DEBUGSERIAL.println("Not set Serial bautrate");
						return false;
					}
				}
			}
			else {
				if (DEBUG4G) DEBUGSERIAL.println("Not Started echo mode");
				return false;
			}
		}
		else {
			if (DEBUG4G) DEBUGSERIAL.println("Not Started command");

			return false;
		}

		return false;
		if (DEBUG4G) DEBUGSERIAL.println("");
	}
	return true;
}

void raptor4g::powerON() {
	STM32.println("{\"powerOn\":\"true\"}");
}

bool raptor4g::powerOff() {

	if (_responseAT(_atcmd(QPOWD, 10000), OK4G, ERROR4G)) {
		if (DEBUG4G) DEBUGSERIAL.println("modem shutdown");
		return true;
	}
	return false;
}

bool raptor4g::networkRegister() {
	uint countLoop = 0;

	boolean cregOk = false;
	boolean cgregOk = false;
	boolean ceregOk = false;

	String responseCREG = "";


	if (_responseAT(_atcmd(GET_CREG, 10000), RESP_CREG_TEST, ERROR4G)) {
		_atcmd(SET_CREG, 5000);
		_atcmd(SET_CGREG, 5000);
		_atcmd(SET_CEREG, 5000);
	}


	/*_atcmd(SET_RESTCGATT);
	while (!_waitResponse(OK4G, 60000));*/

	if (_responseAT(_atcmd(GET_CREG, 10000), RESP_CREG_NOTNETWORK, RESP_CREG_NOTREGISTER)) {
		powerOff();
		//delay(30000);
		return false;
	}

	while (true) {

		if (!cregOk) {
			if (!_responseAT(_atcmd(GET_CREG, 10000), RESP_CREG_NOTREGISTER, ERROR4G)) {
				cregOk = true;
			}
		}

		if (!cgregOk) {
			if (!_responseAT(_atcmd(GET_CGREG, 10000), RESP_CGREG_NOTREGISTER, ERROR4G)) {
				cgregOk = true;
			}
		}

		if (!ceregOk) {
			if (!_responseAT(_atcmd(GET_CEREG, 10000), RESP_CEREG_NOTREGISTER, ERROR4G)) {
				ceregOk = true;
			}
		}

		countLoop++;

		if (countLoop > 10) {
			if (cregOk || cgregOk || ceregOk) {
				return true;
			}

			return false;
		}
		if (cregOk && cgregOk && ceregOk) {
			return true;
		}
	}

}

bool raptor4g::networkConnect() {
	if (!_responseAT(_atcmd(SET_QIACT, 120000), OK4G, ERROR4G)) {
		return false;
	}
	if (!_responseAT(_atcmd(GET_COPS, 60000), OK4G, ERROR4G)) {
		return false;
	}
	return true;
}

bool raptor4g::networkConnected() {
	_atcmd(SET_QIACT);
	waitResponse = false;
	while (!_waitResponse(OK4G, 60000));	
	return true;
}

bool raptor4g::networkOn() {
	if (_responseAT(_atcmd(GET_QIACT, 5000), RESP_QIACT, RESP_QIACTERROR, ERROR4G)) {
		mqttSubscribeStarted = true;
		return true;
	}
	return false;

}

bool raptor4g::mqttOn(int idConnection) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_MQTTSERVER, idConnection);

	memset(bufferSet2, '\0', 100);
	sprintf(bufferSet2, RESP_MQTTCONNECTED, idConnection);
	

	if (_responseAT(_atcmd(GET_MQTTSTATE, 10000), bufferSet, bufferSet2, OK4G)) {
		return true;
	}
	return false;

}

bool raptor4g::_waitResponse(const char* expected_answer, int timeout) {

	int countWait = 0;

	String responseAction = "";

	while (!STM32.available()) {		
		countWait++;
		if (countWait > timeout) {
			if (DEBUG4G) {
				DEBUGSERIAL.println("timeout wait");
				waitResponse = false;
				return true;
			}

		}
		delay(1);
	}
	
	if (STM32.available() > 0) {		
		responseAction = STM32.readString();
		if (DEBUG4G) DEBUGSERIAL.println(responseAction);		
	}

	if (strstr(converterStringChar(responseAction), expected_answer) != NULL) {
		waitResponse = true;
		return true;
	}
	return false;
}

bool raptor4g::_waitResponse(const char* expected_answer, const char* expected_answer2, int timeout) {

	int countWait = 0;

	String responseAction = "";

	while (!STM32.available()) {
		
		countWait++;
		if (countWait > timeout) {
			if (DEBUG4G) {
				DEBUGSERIAL.println("timeout wait");
				waitResponse = false;
				return true;
			}

		}
		delay(1);
	}	

	if (STM32.available() > 0) {	
		responseAction = STM32.readString();
		if (DEBUG4G) DEBUGSERIAL.println(responseAction);		
	}

	if (strstr(converterStringChar(responseAction), expected_answer) != NULL) {
		waitResponse = true;
		return true;
	}
	if (strstr(converterStringChar(responseAction), expected_answer2) != NULL) {
		waitResponse = true;
		return true;
	}
	return false;
}

bool raptor4g::apnConnect(const char* apn, const char* login, const char* pass) {
	uint countLoop = 0;

	String responseWait = "";

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_QICSGP, apn, login, pass);

	if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {
		DEBUGSERIAL.println("connected apn");
		return true;

	}
	else {
		DEBUGSERIAL.println("not connected apn");
		return false;
	}
}

char* raptor4g::converterStringChar(String buffConverter) {
	String buffServidor = "";
	buffServidor = buffConverter;
	char* buff = new char[buffServidor.length() + 1];
	strcpy(buff, buffServidor.c_str());
	return buff;
}

bool raptor4g::mqttSetup(int idConnection, const char* willQos, const char* willRetain, const char* willTopic, const char* willMsg, const char* session, const char* keepAlive) {

	int countWait = 0;

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_MQTTWILL, idConnection, willTopic, willMsg);

	if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, SET_MQTTTIMEOUT, idConnection);

		if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {

			memset(bufferSet, '\0', 100);
			sprintf(bufferSet, SET_MQTTSESSION, idConnection, session);

			if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {

				memset(bufferSet, '\0', 100);
				sprintf(bufferSet, SET_MQTTKEEPALIVE, idConnection, keepAlive);

				if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {

					memset(bufferSet, '\0', 100);
					sprintf(bufferSet, SET_MQTTRECV, idConnection);
					if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G))
					{
						_atcmd(SET_MQTTPDP, 60000);
						_atcmd(SET_MQTTVERSION, 60000);
					}
					else
					{
						if (DEBUG4G) DEBUGSERIAL.println("not setup mqtt server");
						return false;
					}

					if (DEBUG4G) DEBUGSERIAL.println("setup finish mqtt server");
					return true;
				}
				else {
					if (DEBUG4G) DEBUGSERIAL.println("not setup mqtt server");
					return false;
				}
			}
			else {
				if (DEBUG4G) DEBUGSERIAL.println("not setup mqtt server");
				return false;
			}

		}
		else {
			if (DEBUG4G) DEBUGSERIAL.println("not setup mqtt server");
			return false;
		}
	}
	else {
		if (DEBUG4G) DEBUGSERIAL.println("not setup mqtt server");
		return false;
	}
}

bool raptor4g::mqttConnect(int idConnection, const char* server, const char* port, const char* client, const char* user, const char* pass) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_MQTTSERVER, idConnection, server, port);

	_atcmd(bufferSet);

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_MQTTSERVER, idConnection);

	waitResponse = false;
	while (!_waitResponse(bufferSet, 90000)) ;

	if (waitResponse) {

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, RESP_MQTTSTATECONNECTED, idConnection);

		if (_responseAT(_atcmd(GET_MQTTSTATE, 90000), bufferSet, ERROR4G)) {
			return false;
		}

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, SET_MQTTLOGIN, idConnection, client, user, pass);

		_atcmd(bufferSet);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, RESP_MQTTLOGIN, idConnection);

		waitResponse = false;
		while (!_waitResponse(bufferSet, 90000)) ;		

		if(waitResponse) {
			if (DEBUG4G) DEBUGSERIAL.println("mqtt connected");
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	//}
}

bool raptor4g::mqttSubscribe(int idConnection, const char* topic, int msgid) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_SUBSCRIBE, idConnection, msgid, topic);

	_atcmd(bufferSet);
	waitResponse = false;

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_SUBSCRIBE, idConnection, msgid);
	while (!_waitResponse(bufferSet, 30000)) ;


	if (waitResponse) {
		if (DEBUG4G) DEBUGSERIAL.println(topic);
		return true;
	}
	return false;
}

bool raptor4g::mqttUnsubscribe(int idConnection, const char* topic) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_UNSUBSCRIBE, idConnection, topic);

	_atcmd(bufferSet);
	waitResponse = false;

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_UNSUBSCRIBE, idConnection);

	while (!_waitResponse(RESP_UNSUBSCRIBE, 10000)) ;

	if (waitResponse) {
		DEBUGSERIAL.println(topic);
		return true;
	}
	return false;
}

String raptor4g::mqttSubscribeGet(int idConnection) {

	String bufferSubscribe = "";
	int terminatorSend;

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_SUBSCRIBEDATA, idConnection);

	if (!_responseAT(_atcmd(SET_SUBSCRIBEDATA, 60000), bufferSet, OK4G)) {

		String getData1 = response.substring(26, 27);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,0\r\n", idConnection);

		if (getData1 == "1") {
			if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {
				bufferSubscribe = response;
				return bufferSubscribe;
			}
		}

		String getData2 = response.substring(28, 29);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,1\r\n", idConnection);

		if (getData2 == "1") {
			if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {
				bufferSubscribe = response;
				return bufferSubscribe;
			}
		}

		String getData3 = response.substring(30, 31);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,2\r\n", idConnection);

		if (getData3 == "1") {
			if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {
				bufferSubscribe = response;
				return bufferSubscribe;
			}
		}

		String getData4 = response.substring(32, 33);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,3\r\n", idConnection);

		if (getData4 == "1") {
			if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {
				bufferSubscribe = response;
				return bufferSubscribe;
			}
		}

		String getData5 = response.substring(34, 35);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,4\r\n", idConnection);

		if (getData5 == "1") {
			if (_responseAT(_atcmd(bufferSet, 60000), OK4G, ERROR4G)) {
				bufferSubscribe = response;
				return bufferSubscribe;
			}
		}
	}

}

bool raptor4g::mqttPublish(int idConnection, const char* topic, const char* data) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, GET_SEND, idConnection, topic);

	if (_responseAT(_atcmd(bufferSet, 30000), RESP_SEND, ERROR4G)) {
		STM32.println(data);
		STM32.write(0x1a);
		STM32.flush();
		if (_waitResponse(OK4G, 30000)) {
			if (DEBUG4G) DEBUGSERIAL.println("envio OK4G");
			return true;
		}
		return false;
	}
	else {
		mqttStarted = false;
		return false;
	}

}

void raptor4g::mqttClientDisconnect(int idConnection) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_MQTTDISCONNECT, idConnection);

	_atcmd(bufferSet, 15000);

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_MQTTDISCONNECT, idConnection);

	_waitResponse(bufferSet, 15000);
}

void raptor4g::mqttServerDisconnect(int idConnection) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, GET_MQTTSERVERCLOSED, idConnection);

	_atcmd(bufferSet, 15000);

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_MQTTSERVERCLOSED, idConnection);
	_waitResponse(bufferSet, 15000);
}

String raptor4g::getIMEI() {

	countWait = 0;
	String getImei = "";

	STM32.println(GET_GSN);

	while (!STM32.available()) {
		if (countWait > 30000) {
			DEBUGSERIAL.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (STM32.available() > 0) {
		getImei = (STM32.readString());
	}
	getImei = getImei.substring(9, 24);

	return getImei;
}

void raptor4g::syncDHT() {
	_atcmd(SET_DHT, 150000);
	_atcmd("AT+QNTP?\r\n", 150000);
	_atcmd("AT+QNTP=1,\"200.160.7.186\",123,1\r\n", 150000);
}

String raptor4g::getDHT() {

	countWait = 0;
	String getDHT = "";

	STM32.println(GET_DHT);

	while (!STM32.available()) {
		if (countWait > 30000) {
			if (DEBUG4G) DEBUGSERIAL.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (STM32.available() > 0) {
		getDHT = (STM32.readString());
		if (DEBUG4G) DEBUGSERIAL.println(getDHT);
	}

	getDHT = getDHT.substring(19, 36);

	int year = atoi(converterStringChar(getDHT.substring(0, 2)));
	//Serial.println(dh.year);
	int month = atoi(converterStringChar(getDHT.substring(3, 5)));
	//Serial.println(dh.month);
	int day = atoi(converterStringChar(getDHT.substring(6, 8)));
	//Serial.println(dh.day);
	//int hour = (atoi(converterStringChar(getDHT.substring(9, 11))) - GMT);
	int hour = (atoi(converterStringChar(getDHT.substring(9, 11))));
	//Serial.println(dh.hour);
	int minutes = atoi(converterStringChar(getDHT.substring(12, 14)));
	//Serial.println(dh.minutes);
	int seconds = atoi(converterStringChar(getDHT.substring(15, 17)));
	//Serial.println(dh.seconds);

	if(year > 50) {
		DEBUGSERIAL.print("NTP SYNC ");
		_atcmd("AT+QNTP?\r\n", 150000);
		_atcmd("AT+QNTP=1,\"200.160.7.186\",123,1\r\n", 150000);		
	}
	getDHT.end();
	getDHT = "";
	if (day < 10) {
		getDHT.concat('0');
	}
	getDHT.concat(day);
	getDHT.concat('/');
	if (month < 10) {
		getDHT.concat('0');
	}
	getDHT.concat(month);
	getDHT.concat('/');
	getDHT.concat("20");
	getDHT.concat(year);
	getDHT.concat(',');
	if (hour < 10) {
		getDHT.concat('0');
	}
	getDHT.concat(hour);
	getDHT.concat(':');
	if (minutes < 10) {
		getDHT.concat('0');
	}
	getDHT.concat(minutes);
	getDHT.concat(':');
	if (seconds < 10) {
		getDHT.concat('0');
	}
	getDHT.concat(seconds);

	return getDHT;
}

String raptor4g::getSignal() {

	countWait = 0;
	String getSignal = "";

	STM32.println(GET_SIGNAL);

	while (!STM32.available()) {
		if (countWait > 30000) {
			if (DEBUG4G) DEBUGSERIAL.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (STM32.available() > 0) {
		getSignal = (STM32.readString());
	}

	return getSignal;
}