#include "Session.h"

NS_BEGIN_SG

Session::Session(shared_ptr<ASIO_TCP_SOCKET> sock)
:_sock(NULL),
_sessionStat(Session::SessionStat::Idel)
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
}

NS_END_SG