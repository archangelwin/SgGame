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

	
	shared_ptr<NetMessage> message;

	while (1)
	{
		SgUInt16 len = BytesUtils::readUShort(_recvDataCache)+2;//2×Ö½Ú³¤¶È
		if ((len>2) &&(_recvDataCachePos >= len))
		{
			message = MessageFactory::decodeMessage(_recvDataCache);
			if (message != NULL)
			{
				boost::mutex::scoped_lock lock(_muRecvMsgQueue);
				_recvMessageQueue.push(message);
			}
			memcpy(_recvDataCache, _recvDataCache + len, RecvDataCacheMaxLen - len);
			_recvDataCachePos -= len;
		}
		else
		{
			break;
		}
	}

	begintReadData();
}

NS_END_SG