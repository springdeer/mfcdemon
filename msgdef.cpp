#include "stdafx.h"
#include "msgdef.h"
#include <string.h>

msgdata::msgdata(int msgid, char* databuffer, int datalen)
{	
	m_msgid = msgid;
	m_datalen = datalen;

	m_buffer = new char[datalen];
	memcpy(m_buffer, databuffer, datalen);
}

msgdata::~msgdata()
{
	if (m_buffer) delete m_buffer;
}