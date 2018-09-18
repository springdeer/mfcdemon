#include <stdlib.h>
#include <string.h>
#include "backexpat.h"
#include "msgdef.h"

#define NULL     0
#define HEADLEN  4
#define _COUNT   1
#define FALSE    0
#define TRUE     1

static unsigned char g_title[4] ={0x7E,0x7E,0x7E,0x7E};

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

static int istitle(uchar* str)
{
	int rtn = 0;
	int i   = 0 ;

	if(str == 0) return 0;

	for(; i < _COUNT ; i++)
	{
		if(memcmp(g_title,str,4) == 0)		
			break;
	}

	if(i < _COUNT)
		return 1;
	else
		return 0;
}

int back_exp::search(uchar*p, int len, int* searchpos)
{
	int dwCurrPt = 0 ;
	uchar ch;

	for(; dwCurrPt<len; dwCurrPt++)
	{
		ch = p[dwCurrPt];

		switch(searchstatus)
		{
		case SEARCHMACHINE_NULL:	//  0: $
			{
				Head[HeadPtr++]     = ch;
				if(HeadPtr == HEADLEN)
				{//搜索头部
					Head[HEADLEN] = '\0';
					if(istitle(Head))
					{
						int c = 0;
						searchstatus = SEARCHMACHINE_IDENTIFIER;
						memcpy(frame,Head,HEADLEN);						

						framelen = HEADLEN;
						HeadPtr  = 0;
						checksum = 0;
						for(; c < HEADLEN ; c++) checksum ^= Head[c];
						continue;
					}else
					{
						int i = 1;
						for(; i<HEADLEN;i++)
						{
							if(Head[i] == 0xFE)
								break;
						}

						if(i<HEADLEN)
						{
							int j = 0 ;

							for(; j < HEADLEN-i ; j++) Head[j] = Head[j+i];

							HeadPtr -= i;
						}else
							HeadPtr  = 0;

						searchstatus = SEARCHMACHINE_NULL;
					}
				}
			}
			break;		

		case SEARCHMACHINE_IDENTIFIER:
			{
				frame[framelen] = ch;
				framelen ++;
				checksum ^= ch;

				if(framelen == 7){
					indlen = (frame[6]<<8)+(unsigned char)frame[5];//长度字段
					indlen+=5;
					if((indlen) >= (UNPACKBUFFSIZE-1)){
						searchstatus = SEARCHMACHINE_NULL;
						continue;;
					}
				}
				if(framelen >= UNPACKBUFFSIZE-1)
				{
					searchstatus = SEARCHMACHINE_NULL;
					continue;
				}

				//end part..
				if(framelen == indlen)
				{					
					if(checksum != 0){
						searchstatus = SEARCHMACHINE_NULL;
						continue;
					}

					if(dwCurrPt==(len-1))
					{//找到完整的一帧数据,且缓冲区中只有一帧数据
						*searchpos = dwCurrPt;
						dwCurrPt=0;
						searchstatus=SEARCHMACHINE_NULL;//added 2002-09-04 23:06						
						return PACK_FINISHED;
					}else{//完整一帧数据取完后,还有其它帧的数据
						*searchpos = dwCurrPt;
						searchstatus=SEARCHMACHINE_NULL;			
						return PACK_STILLDATA;
					}
				}
			}
			break;
		default://默认状态
			searchstatus=SEARCHMACHINE_NULL;
		}
	}
	dwCurrPt=0;
	//一帧数据未接收完(SearchMachine=SEARCHMACHINE_LENGTH,下次进入时有用)
	if(searchstatus == SEARCHMACHINE_NULL)
		return PACK_UNSEARCHED;
	else
		return PACK_UNFINISHED;
}

int  back_exp::explain(uchar*frame, int len)
{
	int  msgtype = 0;
	int  msgid   = 0;

	if (frame == NULL || len <=5 ) return 0;

	msgtype = frame[5];

	if (_FLAG_KEY_MSG == msgtype){
		KboardMsg *msg = (KboardMsg *)m_data;

		int iter = 6;
		msg->type = msgtype;
		msg->id  = frame[iter++] + (frame[iter++] << 8);
		msg->cmd = frame[iter++] + (frame[iter++] << 8);
		msg->key = frame[iter++];
		msg->keystate = frame[iter++];
		msg->no = frame[iter++] + (frame[iter++] << 8);

		m_msglen = sizeof(KboardMsg);
		msgid = _REQ_KBOARD_CTRL;
	}
	else if (_FLAG_A_MSG == msgtype){
		AMsg * msg = (AMsg *)m_data;
		int iter = 6;

		msg->type = msgtype;
		msg->id = frame[iter++] + (frame[iter++] << 8);
		msg->cmd = frame[iter++] + (frame[iter++] << 8);
		msg->data = frame[iter++] + (frame[iter++] << 8);;		
		msg->no = frame[iter++] + (frame[iter++] << 8);

		memcpy(msg->frame, frame + iter, len - 2 - iter);
		msgid = _RES_A_MSG;
		m_msglen = sizeof(AMsg);
	}
	else if (_FLAG_B_MSG == msgtype)
	{
		BMsg * msg = (BMsg *)m_data;
		int iter = 6;

		msg->type = msgtype;
		msg->id = frame[iter++] + (frame[iter++] << 8);
		msg->cmd = frame[iter++] + (frame[iter++] << 8);
		msg->data = frame[iter++] + (frame[iter++] << 8);
		msg->no = frame[iter++] + (frame[iter++] << 8);

		memcpy(msg->frame, frame + iter, len - 2 - iter);
		msgid = _RES_B_MSG;
		m_msglen = sizeof(BMsg);
	}
	else if (_FLAG_CONN_MSG == msgtype){
		DevConnected * msg = (DevConnected *)m_data;
		int iter = 6;

		msg->type = msgtype;
		msg->id = frame[iter++] + (frame[iter++] << 8);
		msg->cmd = frame[iter++] + (frame[iter++] << 8);
		msg->data = frame[iter++] + (frame[iter++] << 8);
		msg->no = frame[iter++] + (frame[iter++] << 8);		

		m_msglen = sizeof(DevConnected);
		msgid = _RES_DEV_CONNECTED;
	}
	else if (_FLAG_RF_MSG == msgtype){
		RadioParam * msg = (RadioParam *)m_data;
		int iter = 6;

		msg->type = msgtype;
		msg->id  = frame[iter++] + (frame[iter++] << 8);
		msg->cmd = frame[iter++] + (frame[iter++] << 8);
		msg->stateA = frame[iter++];
		msg->stateB = frame[iter++];
		msg->channo = frame[iter++];
		msg->power  = frame[iter++];
		msg->no = frame[iter++] + (frame[iter++] << 8);

		m_msglen = sizeof(RadioParam);
		msgid = _REQ_RADIO_PARAM;		
	}

	return msgid;
}

back_exp::back_exp(void* param)
{
	framelen = 0;
	searchstatus = SEARCHMACHINE_NULL;
	param = param;
}

back_exp::~back_exp()
{

}

