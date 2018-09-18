#pragma once

#include "Protobuffer.h"
#include "CDevice.h"
#include "LockCriticalSection.h"

class CTransmiter;
class Aframe{
	friend class CTransmiter;
protected:
	char    m_framebuffer[512];
	int     m_framelen;
};

class CTransmiter
{
public:
	CTransmiter();
	~CTransmiter();

	CDevice * GetDevice();//是使用此device打开通信设备
	bool Start();
	bool Stop();
	void Clear();

	char GetChan(){ return m_bA ? 'A' : 'B'; }

	void MailCommand(int msgid,void* msg);

	void SetMsgWnd(HWND hwnd, DWORD dwMsgId){ m_dev.SetMsgWnd(hwnd, dwMsgId);}

protected:
	static unsigned long WINAPI transwoker(void* pVoid);
	bool   DoJob();
	
private:
	CDevice m_dev;
	HANDLE  m_killEvt;
	HANDLE  m_hWorker;
	CProtoBuffer  m_protoBuffer;
	Aframe  m_frame;
	CLockCs m_lock;
	bool    m_bA;
};

