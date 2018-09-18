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
	eCommand_ConnectPlusB2,//��ͨ+B2
	eCommand_TestState,// ���ò���״̬
	eCommand_CPCheck,//���ؼ�����Լ�
	eCommand_CRCCompare,//��ԪCRC�ȶ�
	eCommand_PreNavstate,//��ϵ�����̬���
	eCommand_PreCPState,//������ǰ���
	eCommand_ConnectPlusB3,//��ͨ+B3
	eCommand_ConnectPlusD1,//��ͨ+D1
	eCommand_StartStoreRecord,//�����洢����¼
	eCommand_ConnectPlusB4,//��ͨ+B4
	eCommand_PreCPStateExit,//�˳���ǰ���
	eCommand_SecureUnlock,//���������Ᵽ
	eCommand_CPCheck2,//���ؼ���������Լ�
	eCommand_ExplosivedevUnlock,//��Ʒ�Ᵽ1
	eCommand_MotorStart,//���������
	eCommand_SecureReset,//���������Ᵽ
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

