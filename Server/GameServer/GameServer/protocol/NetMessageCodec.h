//  [3/18/2015 wuliangyu]

#ifndef NetMessageCodec_h__
#define NetMessageCodec_h__

#include <SgLib.h>
#include "NetMessageFactory.h"

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/descriptor.h>
#include "./message/SgMsgId.pb.h"
#include "./message/SgMsg.pb.h"
#include "../network/Session.h"

NS_BEGIN_SG
US_NS_BOOST

#define MessageMap std::map<NetMsgId, google::protobuf::Message*>
struct NetMessage;

class NetMessageCodec
{
public:
	static shared_ptr<NetMessage> decodeMessage(SgUInt8* buff, SgUInt16 maxLen, SgInt16& outReadLen);
	static bool encodeMessage(SgUInt8* buff, shared_ptr<NetMessage> mesaage, SgUInt32 maxLen, SgInt16& outDataSize);
};

NS_END_SG
#endif // MessageFactory_h__