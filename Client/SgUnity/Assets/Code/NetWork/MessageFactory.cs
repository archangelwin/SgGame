using UnityEngine;
using System.Collections.Generic;
using ProtoBuf.Meta;
using ProtoBuf;
using System;
using System.IO;

using SgMsg;
using SgMsgId;

public class NetMessage
{
	public NetMsgId msgId;
	public IExtensible message;
}

public class MessageFactory 
{
	static private MessageFactory _instance = null;
	
	private MessageFactory()
	{
		_dicNetMessage = new Dictionary<uint, Type>();
		_queueNetMessage = new Queue<NetMessage>();
		_mutexQueueMessage = new object();
	}

	static public MessageFactory getInstance()
	{
		if(_instance == null)
		{
			_instance = new MessageFactory();
		}

		return _instance;
	}

	private Dictionary<uint, Type> _dicNetMessage;
	private Queue<NetMessage> _queueNetMessage;
	private object _mutexQueueMessage;

	public void registerNetMessage(uint msgId, Type messageType)
	{
		_dicNetMessage.Add(msgId, messageType);
	}

	public bool decodeData(Byte[] buff, Int32 dataLen, out Int32 decodeLen)
	{
		if(dataLen < 4)
		{
			decodeLen = 0;
			return false;
		}

		int len = (int)ByteUtils.readUInt32(buff, 0);
		if (len > dataLen)
		{
			decodeLen = 0;
			return false;
		}

		decodeLen = len+4;
		uint messageId = ByteUtils.readUShort(buff, 4);
		Type t;
		if (!_dicNetMessage.TryGetValue(messageId, out t))
		{
			Debug.Log("know messageId:" + messageId);
			return true;
		}

		MemoryStream stream = new MemoryStream(buff, 6, (int)(len - 2), false);
		stream.Position = 0;

		NetMessage message = new NetMessage();
		message.msgId   = (NetMsgId)messageId;
		message.message = RuntimeTypeModel.Default.Deserialize(stream, null, t) as IExtensible;

		lock(_mutexQueueMessage)
		_queueNetMessage.Enqueue(message);

		return true;
	}

	public Byte[] encodeNetMessage(NetMessage netMsg, out int dataSize)
	{
		if((netMsg == null) || (netMsg.message == null))
		{
			Debug.Log("encodeNetMessage null");
			dataSize = 0;
			return null;
		}

		MemoryStream stream = new MemoryStream();
		Serializer.Serialize(stream, netMsg.message);
		uint len = (ushort)(stream.Length + 2);
		Byte[] buff = new byte[1024 * 64];
		uint offset = 0;
		ByteUtils.writeUint32(buff, offset, (uint)len);
		offset += 4;

		UInt16 msgId = (UInt16)netMsg.msgId;
		ByteUtils.writeUShort(buff, offset, msgId);
		offset += 2;
		Array.Copy(stream.GetBuffer(), 0, buff, offset, stream.Length);
		offset += (uint)stream.Length;

		dataSize = (int)offset;
		return buff;
	}

	public NetMessage fetchNetMessage()
	{
		lock (_mutexQueueMessage)
		if (_queueNetMessage.Count == 0)
		{
			return null;
		}

		return _queueNetMessage.Dequeue();
	}
}
