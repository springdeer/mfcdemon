#ifndef __DEVICE_H__
#define __DEVICE_H__
#include <string>
#include "ConnectionInterface.h"
#include "Observer.h"
#include "LockCriticalSection.h"
#include "backexpat.h"

using namespace std;

typedef int (*pTFunMsgCallback)(int msgid,const void* msg,unsigned int param,int xtra);

class CDevice:public CSinker{
public:
	CDevice();
	~CDevice(){;}

	BOOL IsOpened();
	int  Open(const int nPort,const int nBaudRate,const int nDataBits,const int nStopBits,BOOL bIfParity,const int nParity,const char* desc,pTFunMsgCallback callback,char* proto,void*para);
	void Close();
	
	void SetMsgWnd(HWND hwnd, DWORD dwMsgId){ m_hwnd = hwnd; m_dwMsgId = dwMsgId; }

	virtual void  Update(const UINT uMsgId,const void * pMsgBuffer,int para);
	virtual void  Log(const char * pStrLogInfo){;}

	int SendData(uchar* databuffer,int datalen);

	void* GetParam(){ return m_para; }

protected:
	void InitSelf();
	void ClearSelf();	

	static DWORD WINAPI worker(void* pvoid);

	IMessager*   m_messager;
	IConnection* m_connection;

	HANDLE  m_thread;
	DWORD   m_thid;
	BOOL    m_bOpen;
	BOOL    m_bStop;
	void*   m_para;
	back_exp* m_exp;

	HWND  m_hwnd;
	DWORD m_dwMsgId;
};

extern CLockCriticalSection g_devupdlock;

#endif