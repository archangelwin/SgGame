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
	Session(shared_ptr<ASIO_TCP_SOCKET> sock);
	~Session();

	void onTick();

private:
	shared_ptr<ASIO_TCP_SOCKET> _sock;
};

NS_END_SG
#endif // Session_h__
