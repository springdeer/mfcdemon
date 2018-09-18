
// MFCApplication2.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "IniWrap.h"
#include "DataLog.h"

// CMFCApplication2App: 
// 有关此类的实现，请参阅 MFCApplication2.cpp
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
// 重写
public:
	virtual BOOL InitInstance();

// 实现

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