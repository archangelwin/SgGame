#include "SessionService.h"

NS_BEGIN_SG

SessionService::SessionService(std::string name, SgInt32 sessionCapacity)
:Service(name, 30),
_sessionCapacity(sessionCapacity),
_sessionList()
{
}

SessionService::~SessionService()
{
}

inline SgInt32 SessionService::getSessionCapacity()
{
	return _sessionCapacity;
}

inline SgInt32 SessionService::getAliveSessionCount()
{
	SgScopedLock(_muSessionList);
	
	return _sessionList.size();
}

SessionService::ServiceStat SessionService::getServStat()
{
	if (getWorkerStat() != Worker::WorkerRunning)
	{
		return NotWork;
	}

	SgInt32 aliveCount = getAliveSessionCount();

	if (aliveCount == 0)
	{
		return Idel;
	}

	if (aliveCount >= _sessionCapacity)
	{
		return Full;
	}

	if (_sessionCapacity < aliveCount * 2)
	{
		return ServiceStat::Busy;
	}

	return ServiceStat::Working;
}

bool SessionService::addSession(shared_ptr<Session> session)
{
	SgScopedLock(_muSessionList);
	_sessionList.push_back(session);
	return true;
}

bool SessionService::removeSession(shared_ptr<Session> session)
{
	SgScopedLock(_muSessionList);
	std::list<shared_ptr<Session>>::iterator it;
	_sessionList.remove(session);
	return true;
}

void SessionService::onTick()
{
	//SG_TRACE2(getName(), getAliveSessionCount());
	SgScopedLock(_muSessionList);
	std::list<shared_ptr<Session>>::iterator it;
	for (it = _sessionList.begin(); it != _sessionList.end(); it++)
	{
		(*it)->onTick();
	}
}


NS_END_SG