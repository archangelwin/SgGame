/*!
 * \file SessionManager.h
 *
 * \author wuly
 * \date ÈýÔÂ 2015
 *
 * 
 */

#ifndef SessionManager_h__
#define SessionManager_h__
#include "../common/SGMacro.h"
#include "../common/ComInc.h"
#include "boost/asio.hpp"

US_NS_BOOST

NS_BEGIN_SG

class SessionServiceManager
{
public:
	~SessionServiceManager();
	static SessionServiceManager* getInstance();
	void addSession(shared_ptr<ASIO_TCP_SOCKET> socket);

private:
	SessionServiceManager();
	static SessionServiceManager* p_instance;

	std::vector<shared_ptr<ASIO_TCP_SOCKET>> _sockList;
};

NS_END_SG

#endif // SessionManager_h__
