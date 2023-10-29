#pragma once

#define CF(s) ((const __FlashStringHelper *)s)

const char OK[] PROGMEM = "OK";
const char ERROR[] PROGMEM = "ERROR";
const char QPOWD[] PROGMEM = "AT+QPOWD\r\n";
const char QPOWDNORMAL[] PROGMEM = "AT+QPOWD=1";
const char RESP_READY[] PROGMEM = "APP RDY";
const char TESTEAT[] PROGMEM = "AT\r\n";

const char ATI[] PROGMEM = "ATI\r\n";
const char ATV1[] PROGMEM = "ATV1\r\n";
const char RESET_DEFAULT[] PROGMEM = "ATZ\r\n";
const char RESET_UE[] PROGMEM = "AT+CFUN=1\r\n";
const char RESET_UE0[] PROGMEM = "AT+CFUN=0\r\n";
const char RESET_FACTORY[] PROGMEM = "AT+QPRTPARA=3\r\n";


const char SET_IPR[] PROGMEM = "AT+IPR=115200\r\n";
const char GET_IPR[] PROGMEM = "AT+IPR?\r\n";
const char RESP_IPR[] PROGMEM = "+IPR: 115200\r\n";
const char SET_URC[] PROGMEM = " AT+QURCCFG=\"urcport\",\"uart1\"\r\n";
const char GET_SIGNAL[] PROGMEM = "AT+CSQ\r\n";
const char GET_SIGNALSTRENGTH[] PROGMEM = "AT+QCSQ\r\n";

const char SET_ECHO_OFF[] PROGMEM = "ATE0\r\n";
const char SET_ECHO_ON[] PROGMEM = "ATE1\r\n";
const char SET_CMEE[] PROGMEM = "AT+CMEE=2\r\n";
const char SET_FULL[] PROGMEM = "AT+CFUN=1\r\n";

const char GET_CCID[] PROGMEM = "AT+QCCID\r\n";
const char GET_CIMI[] PROGMEM = "AT+CIMI\r\n";
const char GET_GSN[] PROGMEM = "AT+GSN\r\n";
const char GET_DHT[] PROGMEM = "AT+CCLK?\r\n";
const char SET_DHTOFF[] PROGMEM = "AT+CTZU=0\r\n";
const char SET_DHT[] PROGMEM = "AT+CTZU=1\r\n";
const char SET_SINCDHTOFF[] PROGMEM = "AT+CTZR=0\r\n";
const char SET_SINCDHTON[] PROGMEM = "AT+CTZR=2\r\n";
const char SET_WAKEUP[] PROGMEM = "AT+QCSQ\r\n";


const char RESET_4G[] PROGMEM = "AT+QCFG=\"nvrestore\",0\r\n";
const char GET_BAND[] PROGMEM = "AT+QCFG=\"band\"\r\n";
const char RESP_BAND[] PROGMEM = "+QCFG: \"band\",0xf,0x8000004,0x8000004";
const char SET_QCFG_BAND[] PROGMEM = "AT+QCFG=\"band\",F,8000004,8000004,1\r\n";


const char GET_NWSCANSEQ[] PROGMEM = "AT+QCFG=\"nwscanseq\"\r\n";
const char RESP_NWSCANSEQ[] PROGMEM = "+QCFG: \"nwscanseq\",030201";
const char SET_QCFG_NWSCANSEQ[] PROGMEM = "AT+QCFG=\"nwscanseq\",030201,1\r\n";

const char GET_NWSCANMODE[] PROGMEM = "AT+QCFG=\"nwscanmode\"\r\n";
const char RESP_NWSCANMODE[] PROGMEM = "+QCFG: \"nwscanmode\",0";
const char SET_QCFG_NWSCANMODE[] PROGMEM = "AT+QCFG=\"nwscanmode\",0,1\r\n";

const char GET_IOTOPMODE[] PROGMEM = "AT+QCFG=\"iotopmode\"\r\n";
const char RESP_IOTOPMODE[] PROGMEM = "+QCFG: \"iotopmode\",2";
const char SET_QCFG_IOTOPMODE[] PROGMEM = "AT+QCFG=\"iotopmode\",2,1\r\n";

const char GET_SIMMEFFECTS[] PROGMEM = "AT+QCFG=\"simeffect\"\r\n";
const char RESP_SIMMEFFECTS[] PROGMEM = "+QCFG: \"simeffect\",1";
const char SET_SIMMEFFECTS[] PROGMEM = "AT+QCFG=\"simeffect\",1\r\n";

const char SET_APNDISPLAY[] PROGMEM = "AT+QCFG=\"apn/display\",1\r\n";
const char SET_NB1[] PROGMEM = "AT+QCFG=\"nb1/bandprior\",1C\r\n";
const char SET_NB1LEVEL[] PROGMEM = "AT+QCFG=\"celevel\"\r\n";

const char GET_QCFG[] PROGMEM = "AT+QCFG=?\r\n";
const char SET_RESTORE[] PROGMEM = "AT+QCFG=\"bandrestore\"\r\n";
const char SET_RAT[] PROGMEM = "AT+QCFG=\"rat/timer\",20,10\r\n";
const char RESP_RAT[] PROGMEM = "+QCFG: \"rat/timer\",20,10";
const char SET_TIME[] PROGMEM = "AT+QCFG=\"timeupdate\",1\r\n";


const char GET_CPIN[] PROGMEM = "AT+CPIN?\r\n";
const char RESP_CPIN[] PROGMEM = "+CPIN: READY";
const char GET_QCSQ[] PROGMEM = "AT+QCSQ\r\n";
const char GET_QNWINFO[] PROGMEM = "AT+QNWINFO\r\n";

const char SET_CREG[] PROGMEM = "AT+CREG=2\r\n";
const char GET_CREG[] PROGMEM = "AT+CREG?\r\n";
const char RESP_CREG_NOTNETWORK[] PROGMEM = "+CREG: 2,0";
const char RESP_CREG[] PROGMEM = "+CREG: 2,1";
const char RESP_CREG_NOTREGISTER[] PROGMEM = "+CREG: 2,2";
const char RESP_CREG_DENIED[] PROGMEM = "+CREG: 2,3";
const char RESP_CREG_NOT[] PROGMEM = "+CREG: 2,4";
const char RESP_CREG_ROAMING[] PROGMEM = "+CREG: 2,5";
const char RESP_CREG_TEST[] PROGMEM = "+CREG: 0";

const char SET_CGREG[] PROGMEM = "AT+CGREG=2\r\n";
const char GET_CGREG[] PROGMEM = "AT+CGREG?\r\n";
const char RESP_CGREG_NOTNETWORK[] PROGMEM = "+CREG: 2,0";
const char RESP_CGREG[] PROGMEM = "+CGREG: 2,1";
const char RESP_CGREG_NOTREGISTER[] PROGMEM = "+CGREG: 2,2";
const char RESP_CGREG_DENIED[] PROGMEM = "+CGREG: 2,3";
const char RESP_CGREG_NOT[] PROGMEM = "+CGREG: 2,4";
const char RESP_CGREG_ROAMING[] PROGMEM = "+CGREG: 2,5";

const char SET_CEREG[] PROGMEM = "AT+CEREG=2\r\n";
const char GET_CEREG[] PROGMEM = "AT+CEREG?\r\n";
const char RESP_CEREG_NOTNETWORK[] PROGMEM = "+CREG: 2,0";
const char RESP_CEREG[] PROGMEM = "+CEREG: 2,1";
const char RESP_CEREG_NOTREGISTER[] PROGMEM = "+CEREG: 2,2";
const char RESP_CEREG_DENIED[] PROGMEM = "+CEREG: 2,3";
const char RESP_CEREG_NOT[] PROGMEM = "+CEREG: 2,4";
const char RESP_CEREG_ROAMING[] PROGMEM = "+CEREG: 2,5";

const char SET_CGATT[] PROGMEM = "AT+CGATT=1\r\n";
const char SET_RESTCGATT[] PROGMEM = "AT+CGATT=0\r\n";
const char GET_CGATT[] PROGMEM = "AT+CGATT?\r\n";
const char RESP_CGATT[] PROGMEM = "+CGATT: 1";
const char RESP_CGATTERROR[] PROGMEM = "+CGATT: 0";

const char GET_CGACT[] PROGMEM = "AT+CGACT?\r\n";
const char SET_RESTCGACT[] PROGMEM = "AT+CGACT=0\r\n";
const char SET_CGACT[] PROGMEM = "AT+CGACT=1\r\n"; 
const char RESP_CGACT[] PROGMEM = "+CGACT: 1";
const char RESP_CGACTERROR[] PROGMEM = "+CGACT: 0";
const char GET_IP[] PROGMEM = "AT+QIACT?";



const char GET_COPS_ALL[] PROGMEM = "AT+COPS=?\r\n";
const char GET_COPS[] PROGMEM = "AT+COPS?\r\n";
const char SET_COPS[] PROGMEM = "AT+COPS=0,2\r\n";
const char GET_IDCHIP[] PROGMEM = "AT+QCCID?\r\n";

const char SET_QICSGPINIT[] PROGMEM = "AT+QICSGP=1\r\n";
const char SET_QICSGP[] PROGMEM = "AT+QICSGP=1,1,\"%s\",\"\%s\",\"\%s\",3\r\n";
const char SET_QIDEACT[] PROGMEM = "AT+QIDEACT=1\r\n";
const char SET_QIACT[] PROGMEM = "AT+QIACT=1\r\n";
const char GET_QIACT[] PROGMEM = "AT+QIACT?\r\n";
const char RESP_QIACT[] PROGMEM = "+QIACT: 1,1,1,";
const char RESP_QIACTERROR[] PROGMEM = "+QIACT: 0,1,1,";
const char SET_DNS[] PROGMEM = "AT+QIDNSCFG=1,\"8.8.8.8\",\"4.4.4.4\"";


const char SET_QICLOSE[] PROGMEM = "AT+QICLOSE=1\r\n";
const char SET_QIDNSCFG[] PROGMEM = "AT+QIDNSCFG=1,\"%s\"\r\n";
const char GET_QIDNSCFG[] PROGMEM = "AT+QIDNSCFG=1\r\n";
const char SET_QIOPEN[] PROGMEM = "AT+QIOPEN=1,1,\"TCP\",\"%s\",%s,0,1\r\n";
const char RESP_QIOPEN[] PROGMEM = "OK\r\n\r\n+QIOPEN: 1,0\r\n";
const char SET_QISEND[] PROGMEM = "AT+QISEND=1\r\n";
const char RESP_QISEND[] PROGMEM = ">";
const char RESP_QISEND_DATA[] PROGMEM = "SEND OK\r\n";

const char SET_QGPSCFG_GNSSCONFIG[] PROGMEM = "AT+QGPSCFG=\"gnssconfig\",%d\r\n";
const char SET_QGPSCFG_NMEASRC[] PROGMEM = "AT+QGPSCFG=\"nmeasrc\",%d\r\n";
const char GET_QGPSGNMEA[] PROGMEM = "AT+QGPSGNMEA=";
const char RESP_QGPSGNMEA[] PROGMEM = "+QGPSGNMEA: ";
const char SET_QGPSEND[] PROGMEM = "AT+QGPSEND\r\n";
const char SET_QGPS[] PROGMEM = "AT+QGPS=1\r\n";
const char GET_QGPSLOC[] PROGMEM = "AT+QGPSLOC=2\r\n";
const char RESP_QGPSLOC[] PROGMEM = "+QGPSLOC: ";

const char SET_MQTTWILL[] PROGMEM = "AT+QMTCFG=\"will\",%d,1,1,0,\"%s\",\"%s\"\r\n";
const char SET_MQTTVERSION[] PROGMEM = "AT+QMTCFG=\"version\",%d,4\r\n";
const char SET_MQTTPDP[] PROGMEM = "AT+QMTCFG=\"pdpcid\",1\r\n";
const char SET_MQTTRECV[] PROGMEM = "AT+QMTCFG=\"recv/mode\",%d,1,1\r\n";
const char SET_MQTTTIMEOUT[] PROGMEM = "AT+QMTCFG=\"timeout\",%d,5,5,0\r\n";
const char SET_MQTTSESSION[] PROGMEM = "AT+QMTCFG=\"session\",%d,%s\r\n";
const char SET_MQTTKEEPALIVE[] PROGMEM = "AT+QMTCFG=\"keepalive\",%d,%s\r\n";

const char SET_MQTTSERVER[] PROGMEM = "AT+QMTOPEN=%d,\"\%s\",\%s\r\n";
const char RESP_MQTTSERVER[] PROGMEM = "+QMTOPEN: %d,0";
const char RESP_MQTTSERVERERROR[] PROGMEM = "+QMTOPEN: %d,2";
const char RESP_MQTTSERVERREFUSE[] PROGMEM = "+QMTOPEN: %d,3";

const char GET_MQTTSERVER[] PROGMEM = "AT+QMTOPEN?\r\n";
const char GET_MQTTSERVERCLOSED[] PROGMEM = "AT+QMTCLOSE=%d\r\n";
const char RESP_MQTTSERVERCLOSED[] PROGMEM = "+QMTCLOSE: %d,0";
//const char RESP_MQTTSERVERCLOSED[] PROGMEM = "OK";

const char SET_MQTTDISCONNECT[] PROGMEM = "AT+QMTDISC=%d\r\n";
const char RESP_MQTTDISCONNECT[] PROGMEM = "+QMTDISC: %d,0";
//const char RESP_MQTTDISCONNECT[] PROGMEM = "OK";
const char SET_MQTTLOGIN[] PROGMEM = "AT+QMTCONN=%d,\"\%s\",\"\%s\",\"\%s\"\r\n";

const char GET_MQTTSTATE[] PROGMEM = "AT+QMTCONN?\r\n";
const char RESP_MQTTSTATE[] PROGMEM = "+QMTCONN: %d,1";
const char RESP_MQTTSTATECONNECTED[] PROGMEM = "+QMTCONN: %d,2";
const char RESP_MQTTLOGIN[] PROGMEM = "+QMTCONN: %d,0,0";
const char RESP_MQTTCONNECTED[] PROGMEM = "+QMTCONN: %d,3";
const char RESP_MQTTCHECK[] PROGMEM = "+QMTCONN: %d,0,3";

const char GET_SEND[] PROGMEM = "AT+QMTPUB=%d,0,0,0,\"\%s\"\r\n";
const char RESP_SEND[] PROGMEM = ">";
const char RESP_FINISHSEND[] PROGMEM = "OK\r\n\r\n+QMTPUB:%d,0,0";

const char GET_SUBSCRIBEDATA[] PROGMEM = "AT+QMTRECV=%d,0\r\n";
const char SET_SUBSCRIBEDATA[] PROGMEM = "AT+QMTRECV?\r\n";
const char RESP_SUBSCRIBEDATA[] PROGMEM = "+QMTRECV: %d,0,0,0,0,0";
const char RESP_SUBSCRIBERECEIVED[] PROGMEM = "+QMTRECV:";
const char SET_SUBSCRIBE[] PROGMEM = "AT+QMTSUB=%d,%d,\"%s\",1\r\n";
const char GET_SUBSCRIBE[] PROGMEM = "AT+QMTSUB=?\r\n";
const char SET_UNSUBSCRIBE[] PROGMEM = "AT+QMTUNS=%d,%d,\"%s\"\r\n";
const char RESP_SUBSCRIBE[] PROGMEM = "+QMTSUB: %d,%d,0,1";
const char RESP_UNSUBSCRIBE[] PROGMEM = "+QMTUNS: %d,%d,0";

const char GPS_ON[] PROGMEM = "AT+QGPS=1\r\n";
const char GPS_OFF[] PROGMEM = "AT+QGPSEND\r\n";
//const char GPS_OUTPUTPORT[] PROGMEM = "AT+QGPSCFG=\"outport\",\"none\",115200\r\n";
const char GPS_OUTPUTPORT[] PROGMEM = "AT+QGPSCFG=\"outport\",\"none\"\r\n";
const char GPS_LOC[] PROGMEM = "AT+QGPSLOC?\r\n";
const char GPS_GLONASS[] PROGMEM = "AT+QGPSCFG=\"gnssconfig\",1\r\n";
const char GPS_AUTOGPS[] PROGMEM = "AT+QGPSCFG=\"autogps\",1\r\n";
const char GPS_PRIORITY[] PROGMEM = "AT+QGPSCFG=\"priority\",0,1\r\n";
const char GPS_GET[] PROGMEM = "AT+QGPSCFG?\r\n";
const char GPS_SETLOCATION[] PROGMEM = "AT+QGPSLOC=2\r\n";
const char GPS_RETLOCATION[] PROGMEM = "+QGPSLOC:";
const char GPS_GETLOCATION[] PROGMEM = "AT+QGPSLOC=2,0\r\n";
const char PING[] PROGMEM = "AT+QPING=1,\"8.8.8.8\"\r\n";
const char RES_PING[] PROGMEM = "AT+QPING: 0,\"8.8.8.8\"";



