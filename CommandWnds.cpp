#include "stdafx.h"
#include "CommandWnds.h"
#include "DlgConnectPlusB2.h"

CCommandWnds::CCommandWnds()
{
	m_nCommand = -1;
}


CCommandWnds::~CCommandWnds()
{

}

void CCommandWnds::ShowCommand(int command)
{
	ICommandWnd *  pCommand = m_mapWnds[command];
	if (pCommand == NULL)
		pCommand = InitCommandWnd(command);

	m_nCommand = command;
	pCommand->Show();
}

ICommandWnd* CCommandWnds::InitCommandWnd(int command)
{
	ICommandWnd * rtn = NULL;

	switch (command){
	case eCommand_ConnectPlusB2:
		rtn = m_mapWnds[command] = new CDlgConnectPlusB2();
		break;
	case eCommand_TestState:    break;
	case eCommand_CPCheck:      break;
	case eCommand_CRCCompare:   break;
	case eCommand_PreNavstate:  break;
	case eCommand_PreCPState:   break;
	case eCommand_ConnectPlusB3:break;
	case eCommand_ConnectPlusD1:break;
	case eCommand_StartStoreRecord:break;
	case eCommand_ConnectPlusB4:   break;
	case eCommand_PreCPStateExit:  break;
	case eCommand_SecureUnlock: break;
	case eCommand_CPCheck2:     break;
	case eCommand_ExplosivedevUnlock:break;
	case eCommand_MotorStart:   break;
	case eCommand_SecureReset:  break;
	default:
		break;
	}

	return rtn;
}

int CCommandWnds::GetCurrCommand()
{
	return m_nCommand;
}

void CCommandWnds::ExitCommand()
{
	ICommandWnd *pCommand = (ICommandWnd *)m_mapWnds[m_nCommand];
	if (pCommand != NULL) 
		pCommand->ExitCommand();	
}

BOOL CCommandWnds::IsCommandTimeout()
{
	ICommandWnd *pCommand = (ICommandWnd *)m_mapWnds[m_nCommand];
	if (pCommand != NULL) 
		return pCommand->IsCommandTimeout();

	return FALSE;
}

BOOL CCommandWnds::CheckKBState(int key)
{
	ICommandWnd *pCommand = (ICommandWnd *)m_mapWnds[m_nCommand];
	if (pCommand != NULL) 
		return pCommand->CheckKBState(key);

	return FALSE;
}

BOOL CCommandWnds::CheckRemoteReplay(void* reply)
{
	ICommandWnd *pCommand = (ICommandWnd *)m_mapWnds[m_nCommand];
	if (pCommand != NULL) 
		return pCommand->CheckRemoteReplay(reply);

	return FALSE;
}