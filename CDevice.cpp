#include "stdafx.h"
#include <assert.h>
#include <time.h>
#include "CDevice.h"
#include "backexpat.h"
#include "msgdef.h"

CLockCriticalSection g_devupdlock;

CDevice::CDevice(){
	InitSelf();
}

void CDevice::InitSelf()
{
	m_messager  = NULL;
	m_connection = NULL;

	m_thread = NULL;
	m_thid = 0;
	m_bOpen = FALSE;
	m_bStop = TRUE;

	m_exp = new back_exp(this);

	m_hwnd = NULL;

	m_exp->Advise(this);

	m_dwMsgId = 0;
}

BOOL CDevice::IsOpened()
{
	return m_bOpen;
}

DWORD WINAPI CDevice::worker(void* pvoid)
{
	CDevice * device = (CDevice*) pvoid;

	assert(device);
	assert(device->m_connection);

	BYTE byBuffer[513] ;
	int  nReadLen = 0  ;

	while(!device->m_bStop)
	{
		BOOL bOk = device->m_connection->ReadData(byBuffer,sizeof(byBuffer),nReadLen);
		if(!bOk){
			Sleep(50);//ÐÝÃß
		}else{
			device->m_exp->process_data((char*)byBuffer, nReadLen);
		}
	}

	return TRUE;
}

int  CDevice::Open(const int nPort,const int nBaudRate,const int nDataBits,const int nStopBits,BOOL bIfParity,const int nParity,const char* desc,pTFunMsgCallback callback,char* proto,void* para)
{
	if(m_connection == NULL)
	{
		m_bOpen = TRUE;

		BOOL bOpen = open_com_connection(  nPort,  nBaudRate,  nDataBits,  nStopBits, bIfParity,nParity,&m_connection);
		if(bOpen && m_connection){
			if(m_bOpen){
				m_bStop = FALSE;
				m_thread = ::CreateThread(NULL,0,CDevice::worker,this,0,&m_thid);//Ïß³Ì
				if(!m_thread)
					m_bOpen = FALSE;
			}							

			if(m_bOpen) m_para = para;

		}else{
			m_bOpen = FALSE;
		}

		if(m_bOpen == FALSE){
			ClearSelf();
			return -1;
		}else
			return 1;

	}else
		return -1;
}

void CDevice::ClearSelf()
{
	if(m_bOpen == TRUE){
		if(m_thread){
			m_bStop = TRUE;
			if(WAIT_TIMEOUT == WaitForSingleObject(m_thread,2000)){
				TerminateThread(m_thread,-1);
			}
		}

		if(m_connection)
		{
			m_connection->Release();
			m_connection = NULL;
		}	
	}

	InitSelf();
}

void CDevice::Close()
{
	ClearSelf();
}

void  CDevice::Update(const UINT uMsgId,const void * pMsgBuffer,int len)
{
	if(pMsgBuffer == NULL) return;

	if (m_hwnd != NULL){
		msgdata * data = new msgdata((int)uMsgId, (char*)pMsgBuffer, len);
		::PostMessage(m_hwnd, m_dwMsgId, (WPARAM)data, (LPARAM)this);
	}
}

int CDevice::SendData(uchar* databuffer, int datalen)
{
	if (m_connection && m_connection->Valid())
		return m_connection->WriteData(databuffer, datalen);

	return 0;
}