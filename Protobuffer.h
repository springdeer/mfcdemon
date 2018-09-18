#pragma once
#include "msgdef.h"

class CProtoBuffer{
public:
	CProtoBuffer();
	~CProtoBuffer(){}

	int  Encode(int msgid, void* msg, char* buffer, int bufferlen);
protected:
	bool Init();
	int  BuildCRCTable(unsigned short * table, int tbuffsize);
	unsigned short CalcCRC16(unsigned char* databuff, int buffsize, unsigned short* crc_table);
private:
	unsigned short m_crcTable[256];
	bool m_bInit;
};