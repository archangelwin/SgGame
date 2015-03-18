//  [3/18/2015 wuliangyu]

#ifndef BytesUtils_h__
#define BytesUtils_h__

#include "SGMacro.h"
#include "ComInc.h"

NS_BEGIN_SG

class BytesUtils
{
public:
	static SgUInt16 readUShort(SgUInt8* buff)
	{
		return (buff[1] << 8) + buff[0];
	}

	static void writeUShort(SgUInt8* buff, SgUInt16 val)
	{
		buff[0] = (SgUInt8)val;
		buff[1] = (SgUInt8)(val >> 8);
	}

	static SgUInt32 readUInt32(SgUInt8* buff)
	{
		return (buff[3] << 24) + (buff[2] << 16) + (buff[1] << 8) + buff[0];
	}

	static void writeUint32(SgUInt8* buff, SgUInt32 val)
	{
		buff[0] = (SgUInt8)val;
		buff[1] = (SgUInt8)(val >> 8);
		buff[2] = (SgUInt8)(val >> 16);
		buff[3] = (SgUInt8)(val >> 24);
	}
};


NS_END_SG
#endif // BytesUtils_h__