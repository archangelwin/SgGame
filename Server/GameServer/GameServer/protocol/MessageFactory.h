//  [3/18/2015 wuliangyu]

#ifndef MessageFactory_h__
#define MessageFactory_h__

#include "../common/SGMacro.h"
#include "../common/ComInc.h"

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/descriptor.h>
#include "./message/SgMsgId.pb.h"
#include "./message/SgMsg.pb.h"
#include "../network/Session.h"

NS_BEGIN_SG
US_NS_BOOST

#define MessageMap std::map<NetMsgId, google::protobuf::Message*>
struct NetMessage;

class MessageFactory
{
public:
	static shared_ptr<NetMessage> decodeMessage(SgUInt8* buff, SgUInt16 maxLen, SgInt16& outReadLen);
	static bool encodeMessage(SgUInt8* buff, shared_ptr<NetMessage> mesaage, SgUInt32 maxLen, SgInt16& outDataSize);

private:
	static MessageMap _dicMessage;
};

NS_END_SG
#endif // MessageFactory_h__