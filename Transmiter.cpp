#include "stdafx.h"
#include "Transmiter.h"

CTransmiter::CTransmiter()
{
	m_killEvt = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hWorker = NULL;
	m_bA = TRUE;
}


CTransmiter::~CTransmiter()
{
	Stop();

	CloseHandle(m_killEvt);
}

CDevice * CTransmiter::GetDevice()
{
	return &m_dev;
}

void CTransmiter::MailCommand(int msgid, void* msg)
{
	AUTOLOCK(m_lock)

	m_frame.m_framelen = m_protoBuffer.Encode(msgid, msg, m_frame.m_framebuffer, sizeof(m_frame.m_framebuffer));
	
}

bool CTransmiter::Start()
{
	Stop();

	Clear();

	DWORD thid;
	m_hWorker = CreateThread(NULL, 0, transwoker, this, 0, &thid);

	return m_hWorker != NULL;
}

bool CTransmiter::Stop()
{
	if (m_hWorker != NULL){
		SetEvent(m_killEvt);

		WaitForSingleObject(m_hWorker, INFINITE);

		CloseHandle(m_hWorker);
		m_hWorker = NULL;

		ResetEvent(m_killEvt);		
	}	

	return true;
}

void CTransmiter::Clear()
{	
	memset(&m_frame, 0, sizeof(m_frame));
}

bool CTransmiter::DoJob()
{
	bool rtn = false;
	
	m_bA = !m_bA;

	if (m_dev.IsOpened() && m_frame.m_framelen){
		int cnt = m_dev.SendData((uchar*)m_frame.m_framebuffer, m_frame.m_framelen);
		rtn = (cnt == m_frame.m_framelen);
	}	

	return rtn;
}

unsigned long WINAPI CTransmiter::transwoker(void* pVoid)
{
	CTransmiter* pTransmiter = (CTransmiter*)pVoid;
	if (pTransmiter == NULL) return -1;
	
	while(1)
	{
		DWORD dwRslt = WaitForSingleObject(pTransmiter->m_killEvt, 0.5);
		
		if (dwRslt == WAIT_TIMEOUT){
			if (!pTransmiter->DoJob()){};
		}
		else
			break;		
			
	}

	return 0;
}