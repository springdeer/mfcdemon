#include "stdafx.h"
#include "Protobuffer.h"

#define _crcpoly    (0x1021)
#define _crc16_init (0)

int CProtoBuffer::BuildCRCTable(unsigned short * table, int tbuffsize)
{
	if (tbuffsize < 512) return 0;

	unsigned short index = 0, size = 0;
	unsigned short data  = 0;
	unsigned short crc   = 0;

	for (index = 0; index < 256; index++){
		data = index << 8; crc = 0;
		
		for (size = 0; size < 8; size++){
			if (((data^crc) & 0x8000) == 0x8000)  
				  crc = (crc << 1)^_crcpoly;			
			else  crc <<= 1;

			data <<= 1;
		}
		table[index] = crc;
	}

	return 1;
}

unsigned short CProtoBuffer::CalcCRC16(unsigned char* databuff, int buffsize, unsigned short* crc_table)
{
	unsigned short index = 0; 
	unsigned char  data  = 0; 
	unsigned int   count = buffsize;

	unsigned short crc = _crc16_init;

	while ((count--) != 0){
		data = (unsigned char)(crc >> 8);
		crc <<= 8;
		crc ^= crc_table[data^*databuff];
		databuff++;
	}

	return crc;
}

bool CProtoBuffer::Init()
{
	return BuildCRCTable(m_crcTable, sizeof(m_crcTable)) != 0;		
}

CProtoBuffer::CProtoBuffer()
{
	m_bInit = Init();
}

int CProtoBuffer::Encode(int msgid, void* msg, char* buffer, int bufferlen)
{
	if (bufferlen < 512) return 0;

	int encodelen = 0;

	switch (msgid)
	{
	case _REQ_DEV_CONNECT:
	case _REQ_RADIO_QUERY:
	case _REQ_REMOTE_CONNECT:
	case _REQ_CONNECT_PLUS_B2:
	case _REQ_COMPUTER_CHECK:
	case _REQ_CRC_CHECK:
	case _REQ_NAVTEST_START:
	case _REQ_CONNECT_PLUS_B3:
	case _REQ_CONNECT_PLUS_D1:
	case _REQ_STARTSTORE_RECORD:
	case _REQ_CPTEST_START:
	case _REQ_CONNECT_PLUS_B4:
	case _REQ_CPTEST_STOP:
	case _REQ_SECURE_OPEN:
	case _REQ_CP_CHECK2:
	case _REQ_FIRETRIGGER_OPEN:
	case _REQ_MOTOR_START:
	case _REQ_SECURE_RESET:
	case _REQ_DISCONNECT_PLUSD1:
	case _REQ_DISCONNECT_PLUSB4:
	case _REQ_DISCONNECT_PLUSB3:
	case _REQ_DISCONNECT_PLUSB2:
	{
		_generalcommand* cmd = (_generalcommand*)msg;
		int start = 0;
		int iter  = 0;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;

		buffer[iter++] = 0x0B;
		buffer[iter++] = 0x00;
		start = iter;

		buffer[iter++] = cmd->type;

		buffer[iter++] = (cmd->id) & 0xFF;
		buffer[iter++] = (cmd->id >> 8)&0xFF;
		
		buffer[iter++] = (cmd->cmd) & 0xFF;
		buffer[iter++] = (cmd->cmd >> 8) & 0xFF;

		buffer[iter++] = (cmd->data) & 0xFF;
		buffer[iter++] = (cmd->data >> 8) & 0xFF;

		buffer[iter++] = (cmd->no) & 0xFF;
		buffer[iter++] = (cmd->no >> 8) & 0xFF;

		unsigned short crc = CalcCRC16((unsigned char*)buffer + start, iter-start, m_crcTable);
		buffer[iter++] = crc & 0xFF;
		buffer[iter++] = (crc >> 8) & 0xFF;

		encodelen = iter;
	}	
	break;
	case _REQ_RADIO_SETPARAM:
	{
		RadioSetParam * cmd = (RadioSetParam *)msg;
		int start = 0;
		int iter = 0;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;

		buffer[iter++] = 0x0B;
		buffer[iter++] = 0x00;		

		buffer[iter++] = cmd->type;
		start = iter;

		buffer[iter++] = (cmd->id) & 0xFF;
		buffer[iter++] = (cmd->id >> 8) & 0xFF;

		buffer[iter++] = (cmd->cmd) & 0xFF;
		buffer[iter++] = (cmd->cmd >> 8) & 0xFF;
		buffer[iter++] = cmd->stateA;
		buffer[iter++] = cmd->stateB;
		buffer[iter++] = cmd->channo;
		buffer[iter++] = cmd->power;

		buffer[iter++] = cmd->no&0xFF;
		buffer[iter++] = (cmd->no >> 8) & 0xFF;

		unsigned short crc = CalcCRC16((unsigned char*)buffer + start, iter-start, m_crcTable);
		buffer[iter++] = crc & 0xFF;
		buffer[iter++] = (crc >> 8) & 0xFF;

		encodelen = iter;
	}	
	break;

	case _REQ_KBOARD_CTRL:
	{
		KBoardCtrl * cmd = (KBoardCtrl *)msg;
		int start = 0;
		int iter = 0;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;
		buffer[iter++] = 0x7E;

		buffer[iter++] = 0x0B;
		buffer[iter++] = 0x00;

		buffer[iter++] = cmd->type;
		start = iter;

		buffer[iter++] = (cmd->id) & 0xFF;
		buffer[iter++] = (cmd->id >> 8) & 0xFF;

		buffer[iter++] = (cmd->cmd) & 0xFF;
		buffer[iter++] = (cmd->cmd >> 8) & 0xFF;
		buffer[iter++] = cmd->key;
		buffer[iter++] = cmd->keystate;

		buffer[iter++] = cmd->no&&0xFF;
		buffer[iter++] = (cmd->no >> 8) && 0xFF;

		unsigned short crc = CalcCRC16((unsigned char*)buffer + start, iter-start, m_crcTable);
		buffer[iter++] = crc & 0xFF;
		buffer[iter++] = (crc >> 8) & 0xFF;

		encodelen = iter;

	}	
	break;
	default:
		break;
	}

	return encodelen;
}