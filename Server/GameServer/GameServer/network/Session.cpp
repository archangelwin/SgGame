#include "Session.h"

NS_BEGIN_SG

Session::Session(shared_ptr<ASIO_TCP_SOCKET> sock)
:_sock(sock)
{
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

	if (!_sock->is_open())
	{
		SG_TRACE("client disconected!");
		_sock.reset();
		return;
	}

	if ((_sock!= NULL) && (_sock->is_open()))
	{
		_sock->write_some(boost::asio::buffer("hello tick\n\r"));
	}
}

NS_END_SG