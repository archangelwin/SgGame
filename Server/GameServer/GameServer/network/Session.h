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
#include "boost/asio.hpp"

NS_BEGIN_SG
US_NS_BOOST

class Session
{
public:
	enum SessionStat
	{
		Idel = 0,
		Working
	};

	Session(shared_ptr<ASIO_TCP_SOCKET> sock);
	~Session();
	inline SessionStat getSessionStat() const
	{
		return _sessionStat;
	}

	void onTick();

private:
	shared_ptr<ASIO_TCP_SOCKET> _sock;
	SessionStat _sessionStat;
};

NS_END_SG
#endif // Session_h__
