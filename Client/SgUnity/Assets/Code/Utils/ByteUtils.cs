using UnityEngine;
using System.Collections.Generic;
using System;

public class ByteUtils 
{
	static public uint readUShort(Byte[] buff, uint offset)
	{
		return (uint)(buff[offset + 1] << 8) + (uint)buff[offset];
	}

	static public void writeUShort(Byte[] buff, uint offset, uint val)
	{
		buff[offset] = (Byte)val;
		buff[offset+1] = (Byte)(val >> 8);
	}

	static public uint readUInt32(Byte[] buff, uint offset)
	{
		return (uint)(buff[offset + 3] << 24) + (uint)(buff[offset + 2] << 16) + (uint)(buff[offset + 1] << 8) + (uint)buff[offset];
	}

	static public void writeUint32(Byte[] buff, uint offset, uint val)
	{
		buff[offset] = (Byte)val;
		buff[offset+1] = (Byte)(val >> 8);
		buff[offset+2] = (Byte)(val >> 16);
		buff[offset+3] = (Byte)(val >> 24);
	}
}
