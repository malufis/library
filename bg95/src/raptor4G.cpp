#include "raptor4G.h"


void raptor4g::_atcmd(const char* ATcommand) {
	
	serial4G.println(ATcommand);	
	if (printDebug) {
		serialDebug.println(ATcommand);
	}
	serial4G.flush();

}
String raptor4g::_atcmd(const char* ATcommand, int timeout) {
	countWait = 0;
	response = "";	

	serial4G.println(ATcommand);	

	while (!serial4G.available()) {		
		if (countWait > timeout) {
			break;
		}
		countWait++;
		
	}
	if (serial4G.available() > 0 && serial4G.available() != NULL) {
		
		response = (serial4G.readString());
		if (printDebug) {
			serialDebug.println(response);
		}
	}
	
	serial4G.flush();
	return response;
}
bool raptor4g::_responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2, const char* expected_answer3, const char* expected_answer4) {
	
	const char* responseAction = converterStringChar(atCommand);
	
	if (strstr(responseAction, expected_answer1) != NULL) {
		serial4G.flush();
		return true;
	}
	if (strstr(responseAction, expected_answer2) != NULL) {		
		serial4G.flush();
		return true;
	}
	if (strstr(responseAction, expected_answer3) != NULL) {	
		serial4G.flush();
		return true;
	}
	if (strstr(responseAction, expected_answer4) != NULL) {	
		serial4G.flush();
		return true;
	}	
	
	return false;
	serial4G.flush();
	
}
bool raptor4g::_responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2, const char* expected_answer3) {
	
	const char* responseAction = converterStringChar(atCommand);
	
	if (strstr(responseAction, expected_answer1) != NULL) {	
		serial4G.flush();
		return true;
	}
	if (strstr(responseAction, expected_answer2) != NULL) {	
		serial4G.flush();
		return true;
	}
	if (strstr(responseAction, expected_answer3) != NULL) {	
		serial4G.flush();
		return false;
	}
	serial4G.flush();
	return false;
}
bool raptor4g::_responseAT(String atCommand, const char* expected_answer1, const char* expected_answer2) {
	
	const char* responseAction = converterStringChar(atCommand);

	if (strstr(responseAction, expected_answer1) != NULL) {
		serial4G.flush();
		return true;
	}
	if (strstr(responseAction, expected_answer2) != NULL) {
		serial4G.flush();
		return false;
	}
	return false;
}
bool raptor4g::_responseAT(String atCommand, const char* expected_answer1) {
	
	const char* responseAction = converterStringChar(atCommand);

	if (strstr(responseAction, expected_answer1) != NULL) {
		serial4G.flush();
		return true;
	}
	return false;
}

bool raptor4g::init() {		
	
	countWait = 0;
	serialDebug.println("Started Setup 4G");
	
	

	if (_responseAT(_atcmd(ATI, 5000), OK, ERROR)) {
		if (_responseAT(_atcmd(ATV1, 30000), OK, ERROR)) {
			if (printDebugModem) {
				_responseAT(_atcmd(SET_ECHO_ON, 5000), OK, ERROR);
			}
			else {
				_responseAT(_atcmd(SET_ECHO_OFF, 5000), OK, ERROR);
			}

			if (_responseAT(_atcmd(SET_CMEE, 5000), OK, ERROR)) {
				
				_atcmd(SET_COPS, 5000);				
				_atcmd(SET_URC, 5000);
				_atcmd(SET_SINCDHTOFF, 5000);
				delay(2000);
				_atcmd(SET_SINCDHTON, 5000);

				if (_responseAT(_atcmd(SET_IPR, 5000), OK, ERROR)) {

					if (_responseAT(_atcmd(GET_CPIN, 5000), RESP_CPIN, ERROR)) {
							
						_atcmd(GET_CCID, 5000);
						_atcmd(GET_CIMI, 5000);		
						
						
						return true;
					}
					else {
						serialDebug.println("SIM CARD no init");

						return false;
					}
				}
				else {
					serialDebug.println("Not set Serial bautrate");
					return false;
				}
			}
		}
		else {
			serialDebug.println("Not Started echo mode");
			return false;
		}
	}
	else {
		serialDebug.println("Not Started command");

		return false;
	}	
		
	serialDebug.println("");
	return true;
	
	
}
void raptor4g::powerON() {
	
	pinMode(POWERPIN, OUTPUT);
	digitalWrite(POWERPIN, HIGH);
	delay(5000);	
	digitalWrite(POWERPIN, LOW);

}
bool raptor4g::powerOff() {
	
	if (_responseAT(_atcmd(QPOWD, 10000), OK, ERROR)) {
		serialDebug.println("modem shutdown");
		return true;
	}
	return false;
}
bool raptor4g::networkRegister() {
	int countLoop = 0;

	boolean cregOk = false;
	boolean cgregOk = false;
	boolean ceregOk = false;
	
	boolean cregRegister = false;
	boolean cgregRegister = false;
	boolean ceregRegister = false;

	String responseCREG = "";
	
	_atcmd(SET_CREG, 5000);
	_atcmd(SET_CGREG, 5000);
	_atcmd(SET_CEREG, 5000);
	

	Serial.println(countLoop);
	while (true) {

		if (!cregOk) {			
			if (_responseAT(_atcmd(GET_CREG, 10000), RESP_CREG, RESP_CREG_NOT, RESP_CREG_DENIED, RESP_CREG_ROAMING))
			{
				cregOk = true;	
				cregRegister = true;
			}			
			
		}

		if (!cgregOk) {			
			if (_responseAT(_atcmd(GET_CGREG, 10000), RESP_CGREG, RESP_CGREG_NOT, RESP_CGREG_DENIED, RESP_CGREG_ROAMING))
			{
				cgregOk = true;	
				cgregRegister = true;
			}			
		}

		if (!ceregOk) {			
			if (_responseAT(_atcmd(GET_CEREG, 10000), RESP_CEREG, RESP_CEREG_NOT, RESP_CEREG_DENIED, RESP_CEREG_ROAMING))
			{
				ceregOk = true;
				ceregRegister = false;
			}
			
		}

		countLoop++;
		Serial.println("*");

		if (countLoop > 15) {	
								
			if (cregRegister || cgregRegister || ceregRegister) {
				_responseAT(_atcmd(GET_COPS, 60000), OK, ERROR);
				countLoop = 0;
				return true;				
			}
			countLoop = 0;
			return false;
			
		}	
		delay(500);
		
		
	}

}
bool raptor4g::networkConnect() {	
		
	if (!_responseAT(_atcmd(SET_QIACT, 180000), OK, ERROR)) {		
		return false;
	}	
	_responseAT(_atcmd(GET_COPS, 60000), OK, ERROR);
	_responseAT(_atcmd(GET_QIACT, 60000), OK, ERROR);		
	return true;
}
bool raptor4g::disconnectNetwork() {	
		
	if (!_responseAT(_atcmd(SET_QIDEACT, 120000), OK, ERROR)) {		
		return false;
	}
			
	return true;
}
bool raptor4g::networkConnected() {
	_atcmd(SET_QIACT);
	waitResponse = false;
	while (!_waitResponse(OK, 60000))
		return true;
}
bool raptor4g::networkOn() {
	if (_responseAT(_atcmd(GET_QIACT, 60000), RESP_QIACT, RESP_QIACTERROR, ERROR)) {		
		return true;
	}
	return false;
}

bool raptor4g::dnsOn() {
	if (_responseAT(_atcmd(SET_DNS, 60000), OK, ERROR)) {		
		return true;
	}
	return false;
}
bool raptor4g::mqttOn(int idConnection) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_MQTTSERVER, idConnection);

	memset(bufferSet2, '\0', 100);
	sprintf(bufferSet2, RESP_MQTTCONNECTED, idConnection);
	

	if (_responseAT(_atcmd(GET_MQTTSTATE, 10000), bufferSet, bufferSet2, OK)) {
		memset(bufferSet, '\0', 100);
		memset(bufferSet2, '\0', 100);
		return true;
	}
	memset(bufferSet, '\0', 100);
	memset(bufferSet2, '\0', 100);
	return false;

}

bool raptor4g::_waitResponse(const char* expected_answer, int timeout) {

	int countWait = 0;

	String responseAction = "";

	while (!serial4G.available()) {		
		countWait++;
		if (countWait > timeout) {
			if (printDebug) {
				serialDebug.println("timeout wait");
				waitResponse = false;
				return true;
			}

		}
		return false;
		delay(1);
	}
	

	if (serial4G.available() > 0) {
		
		responseAction = serial4G.readString();
		if (printDebug) {
			serialDebug.println(responseAction);
		}
	}

	if (strstr(converterStringChar(responseAction), expected_answer) != NULL) {
		waitResponse = true;
		return true;
	}
	return false;
}
String raptor4g::_waitResponseString(const char* expected_answer, int timeout) {

	int countWait = 0;

	String responseAction = "";

	while (!serial4G.available()) {		
		countWait++;
		if (countWait > timeout) {
			if (printDebug) {
				serialDebug.println("timeout wait");
				waitResponse = false;
				return "TIMEOUT";
			}
		}
		delay(1);
	}
	

	if (serial4G.available() > 0) {
		
		responseAction = serial4G.readString();
		if (printDebug) {
			serialDebug.println(responseAction);
		}
	}

	if (strstr(converterStringChar(responseAction), expected_answer) != NULL) {
		waitResponse = true;
		return responseAction;
	}
	return "ERROR";
}
bool raptor4g::_waitResponse(const char* expected_answer, const char* expected_answer2, int timeout) {

	int countWait = 0;
	String responseAction = "";
	while (!serial4G.available()) {		
		countWait++;
		if (countWait > timeout) {
			if (printDebug) {
				serialDebug.println("timeout wait");
				waitResponse = false;
				return true;
			}
			Serial.println("*");
		}
		delay(1);
	}	

	if (serial4G.available() > 0) {
	
		responseAction = serial4G.readString();
		if (printDebug) {
			serialDebug.println(responseAction);
		}
	}

	if (strstr(converterStringChar(responseAction), expected_answer) != NULL) {
		waitResponse = true;
		return true;
	}
	if (strstr(converterStringChar(responseAction), expected_answer2) != NULL) {
		waitResponse = false;
		return false;
	}
	return false;
}
bool raptor4g::apnConnect(const char* apn, const char* login, const char* pass) {
	uint countLoop = 0;

	String responseWait = "";

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_QICSGP, apn, login, pass);

	if (_responseAT(_atcmd(bufferSet, 60000), OK, ERROR)) {
		serialDebug.println("connected apn");
		return true;

	}
	else {
		serialDebug.println("not connected apn");
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
	delay(1000);

	if (_responseAT(_atcmd(bufferSet, 60000), OK, ERROR)) {

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, SET_MQTTTIMEOUT, idConnection);

		if (_responseAT(_atcmd(bufferSet, 60000), OK, ERROR)) {

			memset(bufferSet, '\0', 100);
			sprintf(bufferSet, SET_MQTTSESSION, idConnection, session);

			if (_responseAT(_atcmd(bufferSet, 60000), OK, ERROR)) {

				memset(bufferSet, '\0', 100);
				sprintf(bufferSet, SET_MQTTKEEPALIVE, idConnection, keepAlive);

				if (_responseAT(_atcmd(bufferSet, 60000), OK, ERROR)) {

					memset(bufferSet, '\0', 100);
					sprintf(bufferSet, SET_MQTTRECV, idConnection);
					if (_responseAT(_atcmd(bufferSet, 60000), OK, ERROR))
					{
						
						
						memset(bufferSet, '\0', 100);
						sprintf(bufferSet, SET_MQTTVERSION, idConnection);
						_atcmd(bufferSet, 60000);
					}
					else
					{
						serialDebug.println("not setup mqtt server");
						return false;
					}

					serialDebug.println("setup finish mqtt server");
					return true;
				}
				else {
					serialDebug.println("not setup mqtt server");
					return false;
				}
			}
			else {
				serialDebug.println("not setup mqtt server");
				return false;
			}

		}
		else {
			serialDebug.println("not setup mqtt server");
			return false;
		}
	}
	else {
		serialDebug.println("not setup mqtt server");
		return false;
	}
}
bool raptor4g::mqttConnect(int idConnection, const char* server, const char* port, const char* client, const char* user, const char* pass) {

	memset(bufferSet, '\0', 200);
	sprintf(bufferSet, SET_MQTTSERVER, idConnection, server, port);

	_atcmd(bufferSet);

	memset(bufferSet, '\0', 200);
	sprintf(bufferSet, RESP_MQTTSERVER, idConnection);

	waitResponse = false;
	while (!_waitResponse(bufferSet, 60000)) ;

	if (waitResponse) {

		memset(bufferSet, '\0', 200);
		sprintf(bufferSet, RESP_MQTTSTATECONNECTED, idConnection);

		if (_responseAT(_atcmd(GET_MQTTSTATE, 60000), bufferSet)) {
			return false;
		}

		memset(bufferSet, '\0', 200);
		sprintf(bufferSet, SET_MQTTLOGIN, idConnection, client, user, pass);

		_atcmd(bufferSet);

		memset(bufferSet, '\0', 200);
		sprintf(bufferSet, RESP_MQTTLOGIN, idConnection);

		waitResponse = false;
		while (!_waitResponse(bufferSet, 30000)) ;
		
		if (waitResponse) {
			Serial.println("mqtt connected");
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
bool raptor4g::mqttSubscribe(int idConnection, int msgId, const char* topic) {
	
	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_SUBSCRIBE, idConnection, msgId, topic);
	
	memset(bufferSet2, '\0', 100);
	sprintf(bufferSet2, RESP_SUBSCRIBE, idConnection, msgId);
	
	Serial.print("subscribe : ");
	Serial.print(bufferSet);
	Serial.print(" , ");
	Serial.println(bufferSet2);
	Serial.println("**********");	
	
	if (!_responseAT(_atcmd(bufferSet, 30000), bufferSet2, ERROR)) {	
		Serial.println("subscribe");
		Serial.println("false");		
		return false;
	}	
	Serial.println("subscribe");
	Serial.println("true");
	serialDebug.println(topic);
	return true;	
}
bool raptor4g::mqttUnsubscribe(int idConnection, int msgId, const char* topic) {
	
	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_UNSUBSCRIBE, idConnection, msgId, topic);
	
	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_UNSUBSCRIBE, idConnection, msgId);
	
	if (_responseAT(_atcmd(bufferSet, 30000), bufferSet2, ERROR)) {	
		serialDebug.println(topic);
		return true;
	}
	return false;
}
String raptor4g::mqttSubscribeGet(int idConnection) {

	String bufferSubscribe = "";
	int terminatorSend;

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_SUBSCRIBEDATA, idConnection);
	delay(100);

	if (!_responseAT(_atcmd(SET_SUBSCRIBEDATA, 30000), bufferSet, OK)) {		

		String getData1 = response.substring(26, 27);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,0\r\n", idConnection);

		if (getData1 == "1") {
			if (_responseAT(_atcmd(bufferSet, 10000), OK, ERROR)) {
				
				bufferSubscribe = response;				
			}
		}

		String getData2 = response.substring(28, 29);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,1\r\n", idConnection);

		if (getData2 == "1") {
			if (_responseAT(_atcmd(bufferSet, 10000), OK, ERROR)) {
				bufferSubscribe = response;				
			}
		}

		String getData3 = response.substring(30, 31);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,2\r\n", idConnection);

		if (getData3 == "1") {
			if (_responseAT(_atcmd(bufferSet, 10000), OK, ERROR)) {
				bufferSubscribe = response;				
			}
		}

		String getData4 = response.substring(32, 33);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,3\r\n", idConnection);

		if (getData4 == "1") {
			if (_responseAT(_atcmd(bufferSet, 10000), OK, ERROR)) {
				bufferSubscribe = response;				
			}
		}

		String getData5 = response.substring(34, 35);

		memset(bufferSet, '\0', 100);
		sprintf(bufferSet, "AT+QMTRECV=%d,4\r\n", idConnection);

		if (getData5 == "1") {
			if (_responseAT(_atcmd(bufferSet, 10000), OK, ERROR)) {
				bufferSubscribe = response;				
			}
		}
	}	
	return bufferSubscribe;
	

}

boolean raptor4g::mqttSubscribeGetData(int idConnection) {	
	

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_SUBSCRIBEDATA, idConnection);
	delay(100);
	
	Serial.println("Callback check");
	Serial.println(bufferSet); 

	if (!_responseAT(_atcmd(SET_SUBSCRIBEDATA, 30000), bufferSet, OK)) {		

		String getData1 = response.substring(26, 27);
		Serial.print(" get Data 1 : "); 
		Serial.println(getData1); 
		if (getData1 == "1") {
			Serial.println("1"); 
			return true;
		}

		String getData2 = response.substring(28, 29);		
		
		Serial.print(" get Data 2: "); 
		Serial.println(getData2); 
		
		if (getData2 == "1") {
			Serial.println("2"); 
			return true;
		}

		String getData3 = response.substring(30, 31);
		
		Serial.print(" get Data 3: "); 
		Serial.println(getData3); 
		
		if (getData3 == "1") {
			Serial.println("3"); 
			return true;
		}

		String getData4 = response.substring(32, 33);
		
		Serial.print(" get Data 4: "); 
		Serial.println(getData4); 

		if (getData4 == "1") {
			Serial.println("4"); 
			return true;
		}

		String getData5 = response.substring(34, 35);
		
		Serial.print(" get Data 5: "); 
		Serial.println(getData5); 

		if (getData5 == "1") {
			Serial.println("5"); 
			return true;
		}
		
		return false;	
			
	}	
	Serial.println("Sai do Callback check");
	return false;	

}

//bool raptor4g::mqttPublish(int idConnection, const char* topic, const char* data) {
bool raptor4g::mqttPublish(int idConnection, const char* topic, String data) {

	memset(bufferSet, '\0', 256);
	sprintf(bufferSet, GET_SEND, idConnection, topic);	
	
	
	if (_responseAT(_atcmd(bufferSet, 60000), RESP_SEND, ERROR)) {
		
		serial4G.print(data);			
		serial4G.write(0x1a);		
		delay(1000);
		serial4G.println("");		
		
		if (_waitResponse(OK, ERROR, 10000)) {
			Serial.println("envio OK");
			memset(bufferSet, '\0', 256);			
			serial4G.flush();
			serial4G.clearWriteError();
			return true;
		}
		
		memset(bufferSet, '\0', 256);
		serial4G.flush();
		return true;
	}
	else {
		mqttStarted = false;
		memset(bufferSet, '\0', 256);
		serial4G.flush();
		return false;
	}

}
bool raptor4g::mqttClientDisconnect(int idConnection) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, SET_MQTTDISCONNECT, idConnection);	
	
	memset(bufferSet2, '\0', 100);
	sprintf(bufferSet2, RESP_MQTTDISCONNECT, idConnection);	

	
	//return true;
	
	if (!_responseAT(_atcmd(bufferSet, 30000), bufferSet2, ERROR)) {
		return false;
	}	

	//memset(bufferSet, '\0', 100);
	//sprintf(bufferSet, RESP_MQTTDISCONNECT, idConnection);
	
	return true;

	
}
bool raptor4g::mqttServerDisconnect(int idConnection) {

	memset(bufferSet, '\0', 100);
	sprintf(bufferSet, GET_MQTTSERVERCLOSED, idConnection);
	
	memset(bufferSet2, '\0', 100);
	sprintf(bufferSet2, RESP_MQTTSERVERCLOSED, idConnection);
	
	//return true;
	
	if (!_responseAT(_atcmd(bufferSet, 30000), bufferSet2, ERROR)) {
		return false;
	}
	return true;	

	/*memset(bufferSet, '\0', 100);
	sprintf(bufferSet, RESP_MQTTSERVERCLOSED, idConnection);*/
	//_waitResponse(RESP_MQTTSERVERCLOSED,5000);
}
String raptor4g::getIMEI() {

	countWait = 0;
	String getImei = "";

	serial4G.println(GET_GSN);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getImei = (serial4G.readString());
	}
	getImei = getImei.substring(9, 24);

	return getImei;
}
String raptor4g::getCIMI() {

	countWait = 0;
	String getCimi = "";

	serial4G.println(GET_GSN);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getCimi = (serial4G.readString());
	}
	getCimi = getCimi.substring(9, 24);

	return getCimi;
}
String raptor4g::getSimCard() {

	countWait = 0;
	String getSimCard = "";

	serial4G.println(GET_CCID);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getSimCard = (serial4G.readString());
	}
	getSimCard = getSimCard.substring(9, 24);

	return getSimCard;
}
void raptor4g::syncDHT() {	
	//_atcmd(SET_DNS, 150000);
	_atcmd(SET_DHT, 150000);
	_atcmd("AT+QNTP?\r\n", 150000);
	//_atcmd("AT+QNTP=1,\"br.pool.ntp.org\",123,1\r\n", 150000);
	_atcmd("AT+QNTP=1,\"200.160.7.186\",123,1\r\n", 150000);
	
}
String raptor4g::getDHT() {

	countWait = 0;
	String getDHT = "";

	serial4G.println(GET_DHT);

	while (!serial4G.available()) {		
		if (countWait > 30000) {			
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getDHT = (serial4G.readString());
		Serial.println(getDHT);
	}

	getDHT = getDHT.substring(19, 36);

	year = atoi(converterStringChar(getDHT.substring(0, 2)));
	//Serial.println(dh.year);
	month = atoi(converterStringChar(getDHT.substring(3, 5)));
	//Serial.println(dh.month);
	day = atoi(converterStringChar(getDHT.substring(6, 8)));
	//Serial.println(dh.day);
	//int hour = (atoi(converterStringChar(getDHT.substring(9, 11))) - GMT);
	hour = (atoi(converterStringChar(getDHT.substring(9, 11))));
	//Serial.println(dh.hour);
	minutes = atoi(converterStringChar(getDHT.substring(12, 14)));
	//Serial.println(dh.minutes);
	seconds = atoi(converterStringChar(getDHT.substring(15, 17)));
	//Serial.println(dh.seconds);

	if (year > 50) {
		serialDebug.print("NTP SYNC ");
		//_atcmd(SET_DNS, 150000);
		_atcmd("AT+QNTP?\r\n", 150000);
		//_atcmd("AT+QNTP=1,\"br.pool.ntp.org\",123,1\r\n", 150000);
		_atcmd("AT+QNTP=1,\"200.160.7.186\",123,1\r\n", 150000);
		
		serial4G.flush();
		//getDHT = "";	
		//return getDHT;		
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

	serial4G.flush();
	
	return getDHT;
}
String raptor4g::getSignalPower() {

	countWait = 0;
	String getSignal = "";
	String returnBuffer = "";

	serial4G.println(GET_SIGNALSTRENGTH);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getSignal = (serial4G.readString());
	}
	
	int sizeBuffer = (getSignal.length() + 1);	
	returnBuffer = getSignal.substring(17, sizeBuffer);
	returnBuffer.replace('\"', NULL);
	
	return returnBuffer;
}
String raptor4g::getSignal() {

	countWait = 0;
	String getSignal = "";
	String returnBuffer = "";
	
	serial4G.println(GET_SIGNAL);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getSignal = (serial4G.readString());
	}
	
	int sizeBuffer = (getSignal.length() + 1);	
	returnBuffer = getSignal.substring(15, sizeBuffer);
	
	return returnBuffer;
}
String raptor4g::getInfoNetwork() {

	countWait = 0;
	String getInfoNetwork = "";
	String returnBuffer = "";
	
	serial4G.println(GET_QNWINFO);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getInfoNetwork = (serial4G.readString());
	}
	
	int sizeBuffer = (getInfoNetwork.length() + 1);
	
	returnBuffer = getInfoNetwork.substring(24, sizeBuffer);
	returnBuffer.replace('\"', NULL);
	return returnBuffer;
}
String raptor4g::getOperator() {

	countWait = 0;
	String getOperator = "";

	serial4G.println(GET_COPS);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getOperator = (serial4G.readString());
	}

	return getOperator;
}
String raptor4g::getIp() {

	countWait = 0;
	String getIp = "";
	String returnBuffer = "";
	
	serial4G.println(GET_IP);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getIp = (serial4G.readString());
	}
	
	int sizeBuffer = (getIp.length() + 1);	
	returnBuffer = getIp.substring(27, sizeBuffer);
	returnBuffer.remove('\"', NULL);
	
	return returnBuffer;
}
String raptor4g::getModuleVersion() {

	countWait = 0;
	String getModuleVersion = "";
	String returnBuffer = "";

	serial4G.println(ATI);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getModuleVersion = (serial4G.readString());
	}
	
	int sizeBuffer = (getModuleVersion.length() + 1);	
	returnBuffer = getModuleVersion.substring(34, sizeBuffer);

	return returnBuffer;
}
String raptor4g::getSubscribe() {
	serialDebug.println("get subscribe");
	countWait = 0;
	String getSubscribe = "";

	serial4G.println(GET_SUBSCRIBE);

	while (!serial4G.available()) {
		if (countWait > 30000) {
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getSubscribe = (serial4G.readString());
	}

	return getSubscribe;
}

bool raptor4g::connectionGPS() {
	serialDebug.println("connection GPS");
	countWait = 0;
	
	_atcmd(GPS_GLONASS, 5000);
	_atcmd(GPS_AUTOGPS, 5000);
	_atcmd(GPS_PRIORITY, 5000);
	_atcmd(GPS_OUTPUTPORT, 5000);
	
	_atcmd(GPS_ON, 10000);
		
	if (!_responseAT(_atcmd(GPS_LOC, 10000), GPS_RETLOCATION, ERROR))
	{
		return false;
	}
	
	_atcmd(GPS_SETLOCATION, 10000);
	return true;	
}
String raptor4g::getGPS() {
	
	countWait = 0;
	String getGPS = "";

	serial4G.println(GPS_GETLOCATION);

	while (!serial4G.available()) {		
		if (countWait > 30000) {			
			serialDebug.println("timeout module");
			break;
		}
		countWait++;
		delay(1);
	}

	if (serial4G.available() > 0) {
		getGPS = (serial4G.readString());
		Serial.println(getGPS);
	}

	getGPS = getGPS.substring(19, getGPS.length()+1);
	return getGPS;
}
bool raptor4g::ping() {
	
	if (_responseAT(_atcmd(PING, 10000), RES_PING,OK, ERROR)) {		
		return true;
	}	
	return false;
}