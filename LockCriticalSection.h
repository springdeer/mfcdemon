#pragma once

class  ILocker
{
protected:
	ILocker(void){ ; }
	~ILocker(void){ ; }
public:
	//����
	virtual void Lock() = 0;
	//����
	virtual void Unlock() = 0;
	//�����������
	virtual int  GetLockCnt()const = 0;
};


class CLockCriticalSection :public ILocker
{
public:
	CLockCriticalSection(void);
	~CLockCriticalSection(void);
	//����
	virtual void Lock();
	//����
	virtual void Unlock();
	//�����������
	virtual int  GetLockCnt()const;

private:
	//��������
	int m_nLockCnt;
	//��������
	CRITICAL_SECTION m_cs;
};

//�����ض���
typedef CLockCriticalSection CLockCs;

class  CLockNone : public ILocker
{
public:
	CLockNone(void);
	~CLockNone(void);

	//����
	virtual void Lock();
	//����
	virtual void Unlock();
	//�����������
	virtual int  GetLockCnt()const;
private:
	//��������
	int m_nLockCnt;
};

//����һ����ջ��ʹ��, ʹ��ʱҪС�ķ�����ȫ�ԡ�
//���಻��������������������Ӱ�촫�����������

class CSmartLock
{
public:
	//���캯��
	//pLocker,ʵ�����������ָ�룻
	//�ڶ��󹹽�ʱ���Զ�������
	CSmartLock(ILocker * pLocker)
	{
		m_pLock = pLocker;
		if (m_pLock != NULL)
			m_pLock->Lock();
	}

	//��������
	//�������������Զ�������
	~CSmartLock(void)
	{
		if (m_pLock != NULL)
			m_pLock->Unlock();
	}

private:
	//����ʵ�ֶ���ָ��
	ILocker * m_pLock;
};

#define  AUTOLOCK(cs) \
		 CSmartLock Auto(&cs);