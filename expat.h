#ifndef __SEARCHEXP__H_
#define __SEARCHEXP__H_
typedef unsigned char uchar;

typedef void(*pfunsearchexp_cb)(int msgid, void* msg, int len, void* param);

#define UNPACKBUFFSIZE  (2048)

enum{
	CUNPACK_RAWFRAME = 100,
	CUNPACK_FAU,
	CUNPACK_WAR,
	CUNPACK_DBC,
};
#include "Observer.h"

class _exp_st : public CMessager{
public:
	_exp_st(){}
	~_exp_st(){}

	void  process_data(char* data, int len);

protected:
	virtual int search(uchar*buffer, int len, int* searchpos) = 0;
	virtual int explain(uchar*frame, int len) = 0;

protected:
	uchar  frame[UNPACKBUFFSIZE];
	int    framelen;
	int    searchstatus;
	uchar  m_data[UNPACKBUFFSIZE];
	int    m_msglen;
	uchar  Head[5];
	int    HeadPtr;
	void*  param;
};


#endif