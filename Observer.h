#pragma once
#include <vector>
using namespace std;

//客户端通知嵌入接口类型定义。
class  CSinker{
public:
	virtual void  Update(const unsigned int uMsgId, const void * pMsgBuffer, int para) = 0;
	virtual void  Log(const char * pStrLogInfo) = 0;
};

//厂家自定义扩展协议回调函数
typedef int(*pCBExt_explain)(const char* frame, int framelen, unsigned char *DataBuff, unsigned long &Len);

//服务端通知消息类型接口定义
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
