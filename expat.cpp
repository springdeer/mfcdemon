#include "expat.h"

enum {
	PACK_UNSEARCHED = 0,
	PACK_SEARCHED,
	PACK_STILLDATA,
	PACK_UNFINISHED,
	PACK_FINISHED,
};

enum {
	SEARCHMACHINE_NULL = 0,
	SEARCH_GETHEAD,
	SEARCH_GETDATA,
	SEARCH_GETCHECK,
	SEARCHMACHINE_BEGININD,
	SEARCHMACHINE_IDENTIFIER,
	SEARCHMACHINE_LENGTH,
	SEARCHMACHINE_BINARYCHECK,
};

#define ISLCHAR(w)     (w>='a'&&w<='z')
#define ISHCHAR(w)     (w>='A'&&w<='Z')
#define ISDIGIT(w)     (w>='0'&&w<='9')
#define ISCHAR(w)       (ISDIGIT(w)|| ISLCHAR(w)||ISHCHAR(w))

#define NULLReturn(condition , rtnval)      {if((condition) == NULL)  return rtnval;}
#define FALSEReturn(condition, rtnval)      {if((condition) == FALSE) return rtnval;}
#define TRUEReturn(condition , rtnval)      {if((condition) == TRUE)  return rtnval;}

typedef struct _SInfoTitle_st{
	int id;
	uchar title[5];
}SInfoTitle_st,*SInfoTitle_t;

static const int RDSSCOUNT = 1;

#define CUNPACK_DATA 1001

SInfoTitle_st RDSSTitle[4] =
{
	{ CUNPACK_DATA, { 0x7E, 0x7E, 0x7E, 0x7E } },
};

#define HEADLEN  (4)
#define NULL     (0)


void  _exp_st::process_data(char* data, int len)
{
	int   curr_pos = 0;
	char* str = (char*)m_data;
	int   remain_len = len;
	int   msgid;
	do{
		int status;

		status = search((uchar*)str,remain_len,&curr_pos);		

		if(status==PACK_UNSEARCHED || status==PACK_UNFINISHED)
			break;
		
		NotifyMsg(CUNPACK_RAWFRAME, (char*)frame, framelen);

		if (msgid = explain((uchar*)frame, framelen) == -1) break;

		NotifyMsg(msgid, (char*)data, m_msglen);

		str = str + curr_pos+1;
		remain_len = remain_len - curr_pos-1;

	}while(remain_len >0);
}