// IniWrap.cpp: implementation of the CIniWrap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "IniWrap.h"
#include "windows.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//#define USE_STATIC_PATH
CIniWrap::CIniWrap()
{
	memset(m_szIniFile, 0, sizeof(char) * MAX_PATH);
}

CIniWrap::CIniWrap(LPCSTR pszFile)
{
	char pathname[MAX_PATH] = {'\0'};
	char dirve[MAX_PATH] = {'\0'};
	char dir[MAX_PATH] = {'\0'};
	char name[MAX_PATH] = {'\0'};
	char ext[MAX_PATH] = {'\0'};
	char* pch = NULL;
#ifdef USE_STATIC_PATH
	GetModuleFileName(NULL, pathname, MAX_PATH);
	_splitpath(pathname, dirve, dir, name, ext);
	sprintf(m_szIniFile, "%s%s.ini", pszFile, name);
#else
	GetModuleFileName(NULL, pathname, MAX_PATH);
	_splitpath_s(pathname, dirve, sizeof(dirve), dir, sizeof(dir), name,sizeof(name), ext,sizeof(ext));
	pch = strrchr(dir, '\\');
	if(pch) {
		*pch = NULL; 
		pch = strrchr(dir, '\\');
		if(pch) *pch = NULL;
	}
	sprintf_s(m_szIniFile, sizeof(m_szIniFile), "%s%s\\etc\\%s.ini", dirve, dir, name);
#endif
	//strncpy(m_szIniFile, pszFile, MAX_PATH);
}

CIniWrap::~CIniWrap()
{
}

void CIniWrap::SetFile(LPCSTR pszFile)
{
	strncpy_s(m_szIniFile, sizeof(m_szIniFile), pszFile, MAX_PATH);
}

BOOL CIniWrap::ReadStr(LPCSTR pszSection,LPCSTR pszKey,char* pszBuf,int iLen)
{
	return GetPrivateProfileString(pszSection,pszKey,"",pszBuf,iLen,m_szIniFile);
}

BOOL CIniWrap::ReadInt(LPCSTR pszSection,LPCSTR pszKey,int& iRet,int iDefault)
{
	char szTemp[20];
	char szDefault[20];

	sprintf_s(szTemp, sizeof(szTemp), "%d",iDefault);
	BOOL fRet = GetPrivateProfileString(pszSection, pszKey, szDefault, szTemp, 100, m_szIniFile);
	iRet = atoi(szTemp);

	return fRet;
}

BOOL CIniWrap::WriteInt(LPCSTR pszSection, LPCSTR pszKey, int data)
{	
	CString strData;
	strData.Format(_T("%d"), data);
	return ::WritePrivateProfileString(pszSection, pszKey, (LPCTSTR)strData, m_szIniFile);
}