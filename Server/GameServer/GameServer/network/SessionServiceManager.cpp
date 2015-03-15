#include "SessionServiceManager.h"

NS_BEGIN_SG

SessionServiceManager* SessionServiceManager::p_instance = new SessionServiceManager();

SessionServiceManager* SessionServiceManager::getInstance()
{
	return p_instance;
}

SessionServiceManager::SessionServiceManager()
:_sockList(100)
{
}

SessionServiceManager::~SessionServiceManager()
{
}

void SessionServiceManager::addSession(shared_ptr<ASIO_TCP_SOCKET> sock)
{
	_sockList.push_back(sock);
	//shared_ptr<> session();
}

NS_END_SG