//  [3/18/2015 wuliangyu]

#ifndef BytesUtils_h__
#define BytesUtils_h__

#include "SGMacro.h"
#include "ComInc.h"

NS_BEGIN_SG

class BytesUtils
{
public:
	static SgUInt16 readUShort(SgUInt8* data)
	{
		return (data[1] << 8) + data[0];
	}

	static SgUInt32 readUInt(SgUInt8* data)
	{
		return (data[3] << 24) + (data[2] << 16) + (data[1] << 8) + data[0];
	}
};


NS_END_SG
#endif // BytesUtils_h__