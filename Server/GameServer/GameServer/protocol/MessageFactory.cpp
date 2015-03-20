#include "MessageFactory.h"

NS_BEGIN_SG

MessageMap initMessageMap()
{
	MessageMap msgMapTmp;

	msgMapTmp.insert(MessageMap::value_type(NetMsgId::CS_PbTest, PbTest::default_instance().New()));
	
	return msgMapTmp;
}

MessageMap MessageFactory::_dicMessage(initMessageMap());

//outReadLen return -1 with unkonw msgId
shared_ptr<NetMessage> MessageFactory::decodeMessage(SgUInt8* buff, SgUInt16 maxLen, SgInt16& outReadLen)
{
	shared_ptr<NetMessage> netMessage;
	SgInt16 msgLen = BytesUtils::readUShort(buff);
	if (maxLen < msgLen + 2)
	{
		outReadLen = 0;
		return netMessage;
	}

	NetMsgId msgId = (NetMsgId)BytesUtils::readUInt32(buff+2);
	MessageMap::iterator itMsg = _dicMessage.find(msgId);
	if (itMsg == _dicMessage.end())
	{
		outReadLen = -1;
		SG_TRACE2("MessageFactory::decodeMessage unkonw netMsgId:", netMessage->msgId);
		return netMessage;
	}

	outReadLen = msgLen + 2;
	netMessage.reset(new NetMessage());
	netMessage->msgId = msgId;
	netMessage->message->ParseFromArray(buff+6, netMessage->message->ByteSize());
	return netMessage;
}

bool MessageFactory::encodeMessage(SgUInt8* buff, shared_ptr<NetMessage> netMmesaage, SgUInt32 maxLen, SgInt16& outDataSize)
{
	if (!netMmesaage->message->IsInitialized())
	{
		SG_TRACE2("NetMessage Initialized error",netMmesaage->message->InitializationErrorString());
		return false;
	}

	SgUInt16 msgContentLen = netMmesaage->message->ByteSize();
	if (maxLen < msgContentLen + 6)
	{
		SG_TRACE("send buff overflow");
		return false;
	}

	BytesUtils::writeUShort(buff, msgContentLen + 4);
	BytesUtils::writeUint32(buff + 2, netMmesaage->msgId);
	netMmesaage->message->SerializeToArray(buff + 6, msgContentLen);
	outDataSize = msgContentLen + 6;
	return true;
}

NS_END_SG