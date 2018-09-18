#pragma once
#include <vector>
using namespace std;

//�ͻ���֪ͨǶ��ӿ����Ͷ��塣
class  CSinker{
public:
	virtual void  Update(const unsigned int uMsgId, const void * pMsgBuffer, int para) = 0;
	virtual void  Log(const char * pStrLogInfo) = 0;
};

//�����Զ�����չЭ��ص�����
typedef int(*pCBExt_explain)(const char* frame, int framelen, unsigned char *DataBuff, unsigned long &Len);

//�����֪ͨ��Ϣ���ͽӿڶ���
class IMessager
{
public:
	virtual int  Advise(CSinker* pSinker) = 0;
	virtual int  Unadvise(const CSinker* pSinker) = 0;
};

class CMessager :public IMessager
{
public:
	virtual int  Advise(CSinker* pSinker);
	virtual int  Unadvise(const CSinker* pSinker);
protected:
	void NotifyMsg(int msgid, char* msg, int msglen);
private:
	vector<CSinker*> m_sinkers;
};
