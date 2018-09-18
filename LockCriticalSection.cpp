#include "stdafx.h"
#include "LockCriticalSection.h"
#include <afxmt.h>
////////////////////////////////////////////////////////////
//������ģ�Ͷ���
////////////////////////////////////////////////////////////
CLockCriticalSection::CLockCriticalSection(void)
{
	InitializeCriticalSection(&m_cs);
	m_nLockCnt = 0;
}

CLockCriticalSection::~CLockCriticalSection(void)
{
	DeleteCriticalSection(&m_cs);
}

////////////////////////////////////////////////////////////
//����ģ��Lock����
////////////////////////////////////////////////////////////
void CLockCriticalSection::Lock()
{
	EnterCriticalSection(&m_cs);

	m_nLockCnt++;
}

////////////////////////////////////////////////////////////
//����ģ��Unlock����
////////////////////////////////////////////////////////////
void CLockCriticalSection::Unlock()
{
	m_nLockCnt--;

	LeaveCriticalSection(&m_cs);
}

////////////////////////////////////////////////////////////
//���������
//����ֵ:������
////////////////////////////////////////////////////////////
int  CLockCriticalSection::GetLockCnt()const
{
	return m_nLockCnt;
}

////////////////////////////////////////////////////////////
//����ģ�Ͷ���
////////////////////////////////////////////////////////////
CLockNone::CLockNone(void)
{
	m_nLockCnt = 0;
}

CLockNone::~CLockNone(void)
{

}

////////////////////////////////////////////////////////////
//����ģ��Lock����
////////////////////////////////////////////////////////////
void CLockNone::Lock()
{
	m_nLockCnt++;
}

////////////////////////////////////////////////////////////
//����ģ�ͽ������
////////////////////////////////////////////////////////////
void CLockNone::Unlock()
{
	m_nLockCnt--;
}

////////////////////////////////////////////////////////////
//���������
////////////////////////////////////////////////////////////
int  CLockNone::GetLockCnt()const
{
	return m_nLockCnt;
}