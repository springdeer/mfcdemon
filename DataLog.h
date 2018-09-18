#pragma once

enum{ eOPER, eCPData, eCPCheck, eRcvrData, eNavData };

#define _OPER_FILE_NAME       _T("������¼")
#define _PCDATA_FILE_NAME    _T("���ؼ��������")
#define _PCCHECK_FILE_NAME     _T("������Լ�����")
#define _RCVRDATA_FILE_NAME   _T("���߽��ջ�����")
#define _NAVDATA_FILE_NAME   _T("��ϵ���װ������")

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

