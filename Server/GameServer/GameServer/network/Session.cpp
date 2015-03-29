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

	processAllRecvNetMessage();

	//SG_TRACE("onTick sendNet Message");
	shared_ptr<NetMessage> testMsg(new NetMessage());
	testMsg->msgId = NetMsgId::CS_PbTest;

	/*shared_ptr<PbTest> pbTest(new PbTest());
	pbTest->set_id(5362);
	pbTest->set_name("xxasd23");
	testMsg->message = pbTest;

	sendNetMessage(testMsg);*/

	sendData();
}

void Session::sendData()
{
	if ((_sock == NULL) || (!_sock->is_open()))
	{
		return;
	}

	boost::mutex::scoped_lock lock(_muSendMsg);
	//boost::asio::async_write(_sock,
	if (_sendDataCachePos > 0)
	{
		_sock->async_write_some(
			boost::asio::buffer(_sendDataCache, _sendDataCachePos),
			boost::bind(&Session::handleWrite, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
}

void Session::handleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		close();
		return;
	}

	boost::mutex::scoped_lock lock(_muSendMsg);
	assert(_sendDataCachePos >= bytes_transferred);
	memcpy(_sendDataCache, _sendDataCache + bytes_transferred, SendDataCacheMaxLen - bytes_transferred);
	_sendDataCachePos -= bytes_transferred;
}

void Session::close()
{
	if (!_sock->is_open())
	{
		SG_TRACE("client disconected!");
		//_sock.reset();
		_sock->close();
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

	boost::mutex::scoped_lock lock(_muRecvMsg);
	_recvDataCachePos += bytes_transferred;
	if (_recvDataCachePos > RecvDataCacheMaxLen)
	{
		SG_TRACE("recv data out of cache!");
		close();
		return;
	}

	
	shared_ptr<NetMessage> message(NULL);
	SgInt16 readSize;

	while (1)
	{
		message = MessageFactory::decodeMessage(_recvDataCache, _recvDataCachePos, readSize);
		if (message != NULL)
		{
			_recvMessageQueue.push(message);
			memcpy(_recvDataCache, _recvDataCache + readSize, RecvDataCacheMaxLen - readSize);
			_recvDataCachePos -= readSize;
			memset(_recvDataCache + _recvDataCachePos, 0x00, RecvDataCacheMaxLen - _recvDataCachePos);
		}
		else
		{
			if (readSize == -1)
			{
				close();
			}
			break;
		}
	}

	begintReadData();
}

void Session::sendNetMessage(shared_ptr<NetMessage> message)
{
	SgInt16 dataSize = 0;
	boost::mutex::scoped_lock lock(_muSendMsg);
	if (MessageFactory::encodeMessage(_sendDataCache + _sendDataCachePos, message, SendDataCacheMaxLen - _sendDataCachePos, dataSize))
	{
		_sendDataCachePos += dataSize;
	}
}

void Session::processAllRecvNetMessage()
{
	boost::mutex::scoped_lock lock(_muRecvMsg);
	while (!_recvMessageQueue.empty())
	{
		processNetMessage(_recvMessageQueue.front());
		_recvMessageQueue.pop();
	}
}

bool Session::processNetMessage(shared_ptr<NetMessage> netMsg)
{
	SG_TRACE2("Session processNetMessage:", netMsg->msgId);
	netMsg->message->PrintDebugString();
	return true;
}

NS_END_SG