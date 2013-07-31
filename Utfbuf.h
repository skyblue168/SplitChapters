#pragma once

#define READ_UNIT 1024

class CUtfbuf
{
public:
	unsigned char *data;	/* actual character data */
	size_t size;			/* size of the string */
	size_t asize;			/* allocated size (0 = volatile buffer) */
	size_t unit;			/* reallocation unit size (0 = read-only buffer) */
	size_t rdidx;			/* keep read offset */

public:
	CUtfbuf(void);
	CUtfbuf(size_t un);
	~CUtfbuf(void);

	/* bufgrow: increasing the allocated size to the given value */
	BOOL bufgrow(size_t neosz);
	unsigned char* getLine(unsigned char* buf, int blen);
	BOOL isUTF8Head();
};
