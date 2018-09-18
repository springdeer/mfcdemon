#include "stdafx.h"
#include "DataLog.h"

CDataLog::CDataLog()
{
	for (int i = 0; i < sizeof(m_pFiles) / sizeof(m_pFiles[0]); i++) m_pFiles[i] = NULL;
}

CDataLog::~CDataLog()
{
	for (int i = 0; i < sizeof(m_pFiles) / sizeof(m_pFiles[0]); i++){
		CFile* file = m_pFiles[i];
		if (file && file->m_hFile != NULL){
			file->Flush();
			file->Close();
			delete file;
		}
	}
}

BOOL CDataLog::Init()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	CString strTimeStamp;
	strTimeStamp.Format(_T("%d%02d%02d%02d%02d%02d%03d"), t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	
	CString strFodler;
	strFodler.Format(_T(".\\%s"), strTimeStamp);

	BOOL bOk = CreateDirectory(strFodler,NULL);
	if (!bOk) return FALSE;

	for (int i = 0; i < sizeof(m_pFiles); i++){
		BOOL bOpen = FALSE;
		m_pFiles[i] = new CFile();
		CString strFile;

		switch (i){
		case eOPER:			
			strFile = strFodler + _T("\\") + _OPER_FILE_NAME + strTimeStamp + _T(".txt");			
			break;
		case eCPData:
			strFile = strFodler + _T("\\") + _PCDATA_FILE_NAME + strTimeStamp + _T(".txt");
			break;
		case eCPCheck:
			strFile = strFodler + _T("\\") + _PCCHECK_FILE_NAME + strTimeStamp + _T(".txt");
			break;
		case eRcvrData:
			strFile = strFodler + _T("\\") + _RCVRDATA_FILE_NAME + strTimeStamp + _T(".txt");
			break;
		case eNavData:
			strFile = strFodler + _T("\\") + _NAVDATA_FILE_NAME + strTimeStamp + _T(".txt");
			break;
		default:
			return FALSE;
		}

		bOpen = m_pFiles[i]->Open(strFile, CFile::typeBinary | CFile::modeWrite | CFile::modeCreate | CFile::shareDenyWrite);
		if (!bOpen){
			delete m_pFiles[i];
			m_pFiles[i] = NULL;
		}else
			m_pFiles[i]->SeekToEnd();
	}	

	return TRUE;
}

void CDataLog::WriteOper(TCHAR buffer[], int datalen)
{
	if (m_pFiles[eOPER] && m_pFiles[eOPER]->m_hFile != NULL)
		m_pFiles[eOPER]->Write(buffer, datalen);
}

void CDataLog::WriteNav(TCHAR buffer[], int datalen)
{
	if (m_pFiles[eNavData] && m_pFiles[eNavData]->m_hFile != NULL)
		m_pFiles[eNavData]->Write(buffer, datalen);
}

void CDataLog::WriteCPCheck(TCHAR buffer[], int datalen)
{
	if (m_pFiles[eCPCheck] && m_pFiles[eCPCheck]->m_hFile != NULL)
		m_pFiles[eCPCheck]->Write(buffer, datalen);
}

void CDataLog::WriteRcvr(TCHAR buffer[], int datalen)
{
	if (m_pFiles[eRcvrData] && m_pFiles[eRcvrData]->m_hFile != NULL)
		m_pFiles[eRcvrData]->Write(buffer, datalen);
}

void CDataLog::WriteCP(TCHAR buffer[], int datalen)
{
	if (m_pFiles[eCPData] && m_pFiles[eCPData]->m_hFile != NULL)
		m_pFiles[eCPData]->Write(buffer, datalen);
}

void CDataLog::Flush()
{
	for (int i = 0; i < sizeof(m_pFiles) / sizeof(m_pFiles[0]); i++)
		if (m_pFiles[i] && m_pFiles[i]->m_hFile != NULL) m_pFiles[i]->Flush();
}
