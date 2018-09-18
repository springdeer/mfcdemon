#pragma once

class  ILocker
{
protected:
	ILocker(void){ ; }
	~ILocker(void){ ; }
public:
	//锁定
	virtual void Lock() = 0;
	//解锁
	virtual void Unlock() = 0;
	//获得锁定计数
	virtual int  GetLockCnt()const = 0;
};


class CLockCriticalSection :public ILocker
{
public:
	CLockCriticalSection(void);
	~CLockCriticalSection(void);
	//锁定
	virtual void Lock();
	//解锁
	virtual void Unlock();
	//获得锁定计数
	virtual int  GetLockCnt()const;

private:
	//锁定计数
	int m_nLockCnt;
	//加锁对象
	CRITICAL_SECTION m_cs;
};

//类型重定义
typedef CLockCriticalSection CLockCs;

class  CLockNone : public ILocker
{
public:
	CLockNone(void);
	~CLockNone(void);

	//锁定
	virtual void Lock();
	//解锁
	virtual void Unlock();
	//获得锁定计数
	virtual int  GetLockCnt()const;
private:
	//锁定计数
	int m_nLockCnt;
};

//该类一般在栈上使用, 使用时要小心分析安全性。
//该类不持有锁定对象。其消亡不影响传入的锁定对象。

class CSmartLock
{
public:
	//构造函数
	//pLocker,实现锁定对象的指针；
	//在对象构建时，自动加锁；
	CSmartLock(ILocker * pLocker)
	{
		m_pLock = pLocker;
		if (m_pLock != NULL)
			m_pLock->Lock();
	}

	//析构函数
	//在析构函数中自动解锁；
	~CSmartLock(void)
	{
		if (m_pLock != NULL)
			m_pLock->Unlock();
	}

private:
	//锁定实现对象指针
	ILocker * m_pLock;
};

#define  AUTOLOCK(cs) \
		 CSmartLock Auto(&cs);