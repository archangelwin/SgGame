#include "MessageFactory.h"

NS_BEGIN_SG

MessageMap initMessageMap()
{
	MessageMap msgMapTmp;

	msgMapTmp.insert(MessageMap::value_type(NetMsgId::CS_PbTest, PbTest()));
	
	return msgMapTmp;
}

MessageMap MessageFactory::_dicMessage(initMessageMap());

shared_ptr<NetMessage> MessageFactory::decodeMessage(SgUInt8* buff)
{
	shared_ptr<NetMessage> netMessage(new NetMessage());
	
	NetMsgId msgId = (NetMsgId)BytesUtils::readUInt32(buff+2);
	MessageMap::iterator itMsg = _dicMessage.find(msgId);
	if (itMsg == _dicMessage.end())
	{
		SG_TRACE2("MessageFactory::decodeMessage unkonw netMsgId:", netMessage->msgId);
		return netMessage;
	}

	netMessage.reset(new NetMessage());
	netMessage->msgId = msgId;
	netMessage->message->ParseFromArray(buff+6, netMessage->message->ByteSize());
	return netMessage;
}

bool MessageFactory::encodeMessage(SgUInt8* buff, shared_ptr<NetMessage> netMmesaage, SgUInt32& outLen)
{
	if (!netMmesaage->message->IsInitialized())
	{
		SG_TRACE2("NetMessage Initialized error",netMmesaage->message->InitializationErrorString());
		return false;
	}

	outLen = netMmesaage->message->ByteSize();
	BytesUtils::writeUShort(buff, outLen);
	BytesUtils::writeUint32(buff + 2, netMmesaage->msgId);
	netMmesaage->message->SerializePartialToArray(buff + 6, outLen);
	outLen += 6;
	return true;
}

NS_END_SG