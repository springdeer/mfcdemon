#include "expat.h"

#ifndef __BACKEXPAT__H__
#define __BACKEXPAT__H__


class back_exp : public _exp_st
{
public:
	back_exp(void* param);
	~back_exp();

	virtual int search(uchar*buffer, int len, int* searchpos);
	virtual int explain(uchar*frame, int len);

private:
	uchar checksum;
	int   indlen;
};

	


#endif