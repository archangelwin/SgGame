#include "Session.h"

NS_BEGIN_SG

Session::Session(shared_ptr<ASIO_TCP_SOCKET> sock)
:_sock(sock),
_recvDataCachePos(0),
_recvMessageQueue(),
_sendMessageQueue()
{
	memset(_recvDataCache, 0x00, sizeof(_recvDataCache));
	begintReadData();
}

Session::~Session()
{
	if (_sock->is_open())
	{
		_sock->close();
	}
}

void Session::onTick()
{
	if (_sock == NULL)
	{
		return;
	}

	if ((_sock!= NULL) && (_sock->is_open()))
	{
	//	_sock->write_some(boost::asio::buffer("hello tick\n\r"));
	}
}

void Session::close()
{
	if (!_sock->is_open())
	{
		SG_TRACE("client disconected!");
		_sock.reset();
		return;
	}
}

void Session::begintReadData()
{
	_sock->async_read_some(buffer(_recvDataCache + _recvDataCachePos, RecvDataCacheMaxLen - _recvDataCachePos), boost::bind(&Session::handleRead, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));;
}

void Session::handleRead(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		SG_TRACE2("error find for handleRead error:", error);
		close();
		return;
	}

	SG_TRACE2("handleRead bytes_transferred:", bytes_transferred);
	_recvDataCachePos += bytes_transferred;
	if (_recvDataCachePos > RecvDataCacheMaxLen)
	{
		SG_TRACE("recv data out of cache!");
		close();
		return;
	}

	shared_ptr<NetMessage> message = decodeData(_recvDataCache, _recvDataCachePos);
	if (message != NULL)
	{
		boost::mutex::scoped_lock lock(_muRecvMsgQueue);
		_recvMessageQueue.push(message);
	}

	begintReadData();
}

shared_ptr<NetMessage> Session::decodeData(SgUInt8* buff, SgInt16& pos)
{
	shared_ptr<NetMessage> message;

	SgUInt16 len = BytesUtils::readUShort(buff);
	if (pos > len+2)
	{
		shared_ptr<NetMessage> message(new NetMessage());
		message->msgId = (MsgId)BytesUtils::readUInt(buff+2);
	}

	return message;
}

NS_END_SG