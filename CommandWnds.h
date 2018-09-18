#pragma once
#include <map>
using namespace std;

#define _COMMAND_TIMEOUT  (5)
enum {
	eState_Init = 0,
	eState_Waitkey = 1,
	eState_WaitRemotereply = 2,
	eState_WaitTimeout = 3,
	eState_CommandOk = 4,
	eState_CommandFailed = 5,
};

struct ICommandWnd{
	virtual void   Show() = NULL;
	virtual BOOL   IsCommandTimeout() = NULL;
	virtual void   ExitCommand() = NULL;
	virtual BOOL   CheckKBState(int key) = NULL;
	virtual BOOL   CheckRemoteReplay(void* reply) = NULL;
};

enum{
	eCommand_ConnectPlusB2,//接通+B2
	eCommand_TestState,// 设置测试状态
	eCommand_CPCheck,//弹载计算机自检
	eCommand_CRCCompare,//诸元CRC比对
	eCommand_PreNavstate,//组合导航静态检查
	eCommand_PreCPState,//弹机射前监测
	eCommand_ConnectPlusB3,//接通+B3
	eCommand_ConnectPlusD1,//接通+D1
	eCommand_StartStoreRecord,//启动存储器记录
	eCommand_ConnectPlusB4,//接通+B4
	eCommand_PreCPStateExit,//退出射前监测
	eCommand_SecureUnlock,//安保机构解保
	eCommand_CPCheck2,//弹载计算机二次自检
	eCommand_ExplosivedevUnlock,//火工品解保1
	eCommand_MotorStart,//发动机点火
	eCommand_SecureReset,//安保机构解保
};

class CCommandWnds
{
public:
	CCommandWnds();
	~CCommandWnds();

	void     ShowCommand(int command);
	int      GetCurrCommand();

	BOOL     IsCommandTimeout();

	void     ExitCommand();

	BOOL     CheckKBState(int key);
	BOOL     CheckRemoteReplay(void* reply);
protected:
	ICommandWnd* InitCommandWnd(int command);
private:
	map<int, ICommandWnd*> m_mapWnds;
	int m_nCommand;
};

