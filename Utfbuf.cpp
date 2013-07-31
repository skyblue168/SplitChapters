#include "stdafx.h"
#include "Utfbuf.h"


#define BUFFER_MAX_ALLOC_SIZE (1024 * 1024 * 16) //16mb

static const char UTF8_BOM[] = {0xEF, 0xBB, 0xBF};

CUtfbuf::CUtfbuf(void)
{
	data = NULL;
	rdidx = asize = size = 0;
	unit = READ_UNIT;
}

CUtfbuf::CUtfbuf(size_t un)
{
	data = NULL;
	rdidx = asize = size = 0;
	unit = un;
}

CUtfbuf::~CUtfbuf(void)
{
	if(data != NULL){
		free(data);
		data = NULL;
	}
	rdidx = asize = size = 0;
}

BOOL CUtfbuf::bufgrow(size_t neosz)
{
	size_t neoasz;
	void *neodata;

	if (neosz > BUFFER_MAX_ALLOC_SIZE)
		return FALSE;

	if (asize >= neosz)
		return TRUE;

	neoasz = asize + unit;
	while (neoasz < neosz)
		neoasz += unit;

	neodata = realloc(data, neoasz);
	if (!neodata)
		return FALSE;

	data = (unsigned char*)neodata;
	asize = neoasz;
	return TRUE;
}

BOOL CUtfbuf::isUTF8Head()
{
	BOOL rc = FALSE;

	if(rdidx == 0 && size >= 3 && memcmp(data, UTF8_BOM, 3) == 0) {
		rdidx = 3;
		rc = TRUE;
	}

	return rc;
}

unsigned char* CUtfbuf::getLine(unsigned char* buf, int blen)
{
	if(buf == NULL)	return NULL;
	
	size_t end = rdidx;

	while(end<size && (data[end] == '\n' || data[end] == '\r') )
		end++;
	rdidx = end;

	while(end < size && data[end] != '\n' && data[end] != '\r')
		end++;

	if(end-rdidx > blen-1) {
		end = rdidx + blen-1;
	}
	memcpy(buf, data+rdidx, end-rdidx);
	buf[end-rdidx] = 0;
	rdidx = end;

	return buf;
}

