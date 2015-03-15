/*!
 * \file SessionService.h
 *
 * \author wuly
 * \date ���� 2015
 *
 * 
 */

#ifndef SessionService_h__
#define SessionService_h__

#include "../common/ComInc.h"
#include "../common/SGMacro.h"
#include "../common/Service.h"
#include "boost/asio.hpp"
#include "Session.h"

NS_BEGIN_SG

class SessionService:public Service
{
public:
	SessionService(std::string name, SgInt32 sessionCapacity);
	~SessionService();

	virtual void onTick();
	inline SgInt32 getSessionCapacity();
	inline SgInt32 getAliveSessionCount();
	bool addSession(shared_ptr<Session> session);
	bool removeSession(shared_ptr<Session> session);

private:
	SgInt16 _sessionCapacity;
	boost::mutex _muSessionList;
	std::list<shared_ptr<Session>> _sessionList;
};

NS_END_SG

#endif // SessionService_h__
