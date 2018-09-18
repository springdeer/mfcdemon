#pragma once

#define WM_COM_MSGDATA  (WM_USER+230)

#define _FLAG_KEY_MSG  (0x4B)

#define _FLAG_A_MSG    (0x41)
#define _FLAG_B_MSG    (0x42)

#define _FLAG_CONN_MSG  (0x54)
#define _FLAG_RF_MSG    (0x54)

class msgdata{
public:
	msgdata(int msgid, char* databuffer, int datalen);
	~msgdata();
	int   id()  { return m_msgid;   }
	void* data(){ return m_buffer;  }
	int   len() { return m_datalen; }
private:
	char* m_buffer;
	int   m_msgid;
	int   m_datalen;
};

struct _generalcommand{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
};

#define _REQ_DEV_CONNECT  (1000)
struct DevConnect{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	DevConnect(){ type = 0x54; id = 0; cmd = 0; data = 0; no = 0; }
};

#define _RES_DEV_CONNECTED  (1001)
struct DevConnected{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	DevConnected(){ type = 0x54; id = 0; cmd = 0; data = 0; no = 0; }
	
};

#define _REQ_RADIO_QUERY  (1002)
struct RadioQuery{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	RadioQuery(){ type = 0x59; id = 0; cmd = 0x6666; data = 0; no = 0; }
};

#define _REQ_RADIO_PARAM  (1003)
struct RadioParam{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned char stateA;
	unsigned char stateB;
	unsigned char channo;
	unsigned char power;
	unsigned short no;
	RadioParam(){ type = 0x59; id = 0; cmd = 0x6666; no = 0; }
};

#define _REQ_RADIO_SETPARAM  (1004)
struct RadioSetParam{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned char stateA;
	unsigned char stateB;
	unsigned char channo;
	unsigned char power;
	unsigned short no;
	RadioSetParam(){ type = 0x5A; id = 0; cmd = 0x6666; no = 0; }
};

#define _REQ_KBOARD_CTRL  (1005)
struct KBoardCtrl{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned char  key;
	unsigned char  keystate;	
	unsigned short no;
	KBoardCtrl(){ type = 0x4B; id = 0; cmd = 0x0003; no = 0; }
};
typedef KBoardCtrl KboardMsg;

#define _REQ_REMOTE_CONNECT  (1006)
struct RemoteConnect{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	RemoteConnect(){ type = 0x41; id = 0x0004; cmd = 0x0C01; data = 0x0000; no = 0; }
};


#define _RES_KBOARD_MSG  (1007)
struct KBoardMsg{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned char  key;
	unsigned char  keystate;
	unsigned short no;
	KBoardMsg(){ type = 0x4B; id = 0x0000; cmd = 0x0003; no = 0; }
};

#define _REQ_CONNECT_PLUS_B2  (1008)
struct ConnectPlusB2{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;	
	unsigned short no;
	ConnectPlusB2(){ type = 0x42; id = 0x0004; cmd = 0x0B01; no = 0; }
};

#define _REQ_COMPUTER_CHECK  (1009)
struct ComputerCheck{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	ComputerCheck(){ type = 0x42; id = 0x0004; cmd = 0xF0E0; no = 0; }
};

#define _REQ_CRC_CHECK  (1010)
struct CRCCheck{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	CRCCheck(){ type = 0x42; id = 0x0004; cmd = 0x0FF0; no = 0; }
};

#define _REQ_NAVTEST_START  (1011)
struct NavTestStart{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	NavTestStart(){ type = 0x42; id = 0x0004; cmd = 0x0E0E; no = 0; }
};

#define _REQ_CONNECT_PLUS_B3  (1012)
struct ConnectPlusB3{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	ConnectPlusB3(){ type = 0x42; id = 0x0004; cmd = 0x0B11; no = 0; }
};

#define _REQ_CONNECT_PLUS_D1  (1013)
struct ConnectPlusD1{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	ConnectPlusD1(){ type = 0x42; id = 0x0004; cmd = 0x0B81; no = 0; }
};

#define _REQ_STARTSTORE_RECORD  (1014)
struct StartStoreRecord{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	StartStoreRecord(){ type = 0x42; id = 0x0004; cmd = 0x0ED0; no = 0; }
};

#define _REQ_CPTEST_START  (1015)
struct CPTestStart{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	CPTestStart(){ type = 0x42; id = 0x0004; cmd = 0x0E0C; no = 0; }
};

#define _REQ_CONNECT_PLUS_B4  (1016)
struct ConnectPlusB4{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	ConnectPlusB4(){ type = 0x42; id = 0x0004; cmd = 0x0B21; no = 0; }
};

#define _REQ_CPTEST_STOP (1017)
struct CPTestStop{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	CPTestStop(){ type = 0x42; id = 0x0004; cmd = 0x0EC0; no = 0; }
};

#define _REQ_SECURE_OPEN (1018)
struct SecureOpen{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	SecureOpen(){ type = 0x42; id = 0x0004; cmd = 0x0B91; no = 0; }
};


#define _REQ_CP_CHECK2 (1019)
struct ComputerCheck2{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	ComputerCheck2(){ type = 0x42; id = 0x0004; cmd = 0xF0E1; no = 0; }
};

#define _REQ_FIRETRIGGER_OPEN (1020)
struct FireTriggerOpen{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	FireTriggerOpen(){ type = 0x42; id = 0x0004; cmd = 0x0B61; no = 0; }
};

#define _REQ_MOTOR_START (1021)
struct MortorStart{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	MortorStart(){ type = 0x42; id = 0x0004; cmd = 0x0B71; no = 0; }
};

#define _REQ_SECURE_RESET (1022)
struct SecureReset{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	SecureReset(){ type = 0x42; id = 0x0004; cmd = 0x0B92; no = 0; }
};

#define _REQ_DISCONNECT_PLUSD1 (1023)
struct DisconnectPlusD1{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	DisconnectPlusD1(){ type = 0x42; id = 0x0004; cmd = 0x0B82; no = 0; }
};

#define _REQ_DISCONNECT_PLUSB4 (1024)
struct DisconnectPlusB4{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	DisconnectPlusB4(){ type = 0x42; id = 0x0004; cmd = 0x0B22; no = 0; }
};

#define _REQ_DISCONNECT_PLUSB3 (1025)
struct DisconnectPlusB3{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	DisconnectPlusB3(){ type = 0x42; id = 0x0004; cmd = 0x0B12; no = 0; }
};

#define _REQ_DISCONNECT_PLUSB2 (1026)
struct DisconnectPlusB2{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	DisconnectPlusB2(){ type = 0x42; id = 0x0004; cmd = 0x0B02; no = 0; }
};


#define _RES_A_MSG  (1027)
struct AMsg{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;	
	unsigned short no;
	unsigned char  frame[2048];
	
	AMsg(){ type = 0x41;}
};

#define _RES_B_MSG  (1028)
struct BMsg{
	unsigned char  type;
	unsigned short id;
	unsigned short cmd;
	unsigned short data;
	unsigned short no;
	unsigned char  frame[2048];
	
	BMsg(){ type = 0x42;}
};