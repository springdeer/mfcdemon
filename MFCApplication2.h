
// MFCApplication2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "IniWrap.h"
#include "DataLog.h"

// CMFCApplication2App: 
// �йش����ʵ�֣������ MFCApplication2.cpp
//
#define _RUN_UNWIRE     1
#define _RUN_WIRELINE   2
#define _RUN_PIPELINE   3

#include "Transmiter.h"
#include "CommandWnds.h"

class CMFCApplication2App : public CWinAppEx
{
public:
	CMFCApplication2App();

	void IncTotalRuntime(int secs);
	
	void SetRunMode(int runmode);
	int  GetRunMode();

	CDataLog * GetLog();

	CTransmiter* GetTransmiter();

	CCommandWnds* GetCommandWnds();

	BOOL  IsCommConnected(){ return m_bComConnected; }
	void  SetCommConnected(BOOL bConnected);
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
protected:
	void InitConfig();
private:
	CIniWrap m_ini;
	int      m_uTotalRuntime;
	int      m_nRunMode;
	CDataLog m_dataLog;
	CTransmiter m_transmitter;
	BOOL     m_bComConnected;
	CCommandWnds m_wndCommands;
public:
	virtual int ExitInstance();
};

extern CMFCApplication2App theApp;