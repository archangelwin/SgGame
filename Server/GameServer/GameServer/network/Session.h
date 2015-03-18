/*!
 * \file Session.h
 *
 * \author wuly
 * \date ÈýÔÂ 2015
 *
 * 
 */


#ifndef Session_h__
#define Session_h__

#include "../common/ComInc.h"
#include "../common/SGMacro.h"
#include "../common/BytesUtils.hpp"
#include "boost/asio.hpp"
#include "../protocol/message/SgMsgId.pb.h"

#define RecvDataCacheMaxLen 8*1024*1024

NS_BEGIN_SG
US_NS_BOOST

using namespace boost::asio;

struct NetMessage
{
public:
	MsgId msgId;
	shared_ptr<google::protobuf::Message> message;
};

class Session
{
public:
	Session(shared_ptr<ASIO_TCP_SOCKET> sock);
	~Session();

	void onTick();
	void close();

private:
	void begintReadData();
	void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
	shared_ptr<NetMessage> decodeData(SgUInt8* buff, SgInt16& pos);
	bool encodeData(shared_ptr<NetMessage> message, SgUInt8* buff, SgInt16& pos);

	shared_ptr<ASIO_TCP_SOCKET> _sock;
	SgUInt8 _recvDataCache[RecvDataCacheMaxLen];
	SgInt16 _recvDataCachePos;		//start 0 end _recvDataCachePos
	std::queue<shared_ptr<NetMessage>> _recvMessageQueue;
	boost::mutex _muRecvMsgQueue;
	std::queue<shared_ptr<NetMessage>> _sendMessageQueue;
	boost::mutex _muSendMsgQueue;
};

NS_END_SG
#endif // Session_h__
