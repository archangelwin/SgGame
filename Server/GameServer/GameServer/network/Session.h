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
#include "../protocol/NetMessageCodec.h"

#define RecvDataCacheMaxLen 256*1024
#define SendDataCacheMaxLen 256*1024

NS_BEGIN_SG
US_NS_BOOST

using namespace boost::asio;

struct NetMessage
{
public:
	NetMessage();
	NetMessage(NetMsgId msgId, shared_ptr<google::protobuf::Message> msg);
	NetMsgId msgId;
	shared_ptr<google::protobuf::Message> message;
};

class Session
{
public:
	Session(shared_ptr<ASIO_TCP_SOCKET> sock);
	~Session();

	void sendNetMessage(shared_ptr<NetMessage> message);
	void onTick();
	void close();

protected:
	virtual bool processNetMessage(shared_ptr<NetMessage> netMsg);

private:
	void begintReadData();
	void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
	void sendData();
	void trySendData();
	void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);
	void processAllRecvNetMessage();
	void onSockClose();

	shared_ptr<ASIO_TCP_SOCKET> _sock;
	SgUInt8 _recvDataCache[RecvDataCacheMaxLen];
	SgInt16 _recvDataCachePos;		//start 0 end _recvDataCachePos
	std::queue<shared_ptr<NetMessage>> _recvMessageQueue;
	boost::mutex _muRecvMsg;

	SgUInt8 _sendDataCache[SendDataCacheMaxLen];
	SgInt16 _sendDataCachePos;		//start 0 end _sendDataCachePos valid data pos
	SgInt16 _totalSendDataPos;		//current send data pos
	SgInt16 _sendedDataPos;			//current sended data pos
	std::queue<shared_ptr<NetMessage>> _sendMessageQueue;
	boost::mutex _muSendMsg;
	bool _isSending;
};

NS_END_SG
#endif // Session_h__
