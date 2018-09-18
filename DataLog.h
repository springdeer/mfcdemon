#pragma once

enum{ eOPER, eCPData, eCPCheck, eRcvrData, eNavData };

#define _OPER_FILE_NAME       _T("操作记录")
#define _PCDATA_FILE_NAME    _T("弹载计算机数据")
#define _PCCHECK_FILE_NAME     _T("计算机自检数据")
#define _RCVRDATA_FILE_NAME   _T("无线接收机数据")
#define _NAVDATA_FILE_NAME   _T("组合导航装置数据")

class CDataLog
{
public:
	CDataLog();
	~CDataLog();
	
	BOOL Init();

	void WriteOper(TCHAR buffer[],int datalen);
	void WriteNav(TCHAR buffer[], int datalen);
	void WriteCPCheck(TCHAR buffer[], int datalen);
	void WriteRcvr(TCHAR buffer[], int datalen);
	void WriteCP(TCHAR buffer[], int datalen);

	void Flush();
private:
	CFile * m_pFiles[5];
};

