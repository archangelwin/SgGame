#include "NetworkWorker.h"

NS_BEGIN_SG

NetworkWorker* NetworkWorker::p_NetInstance = new NetworkWorker("network", 50);

NetworkWorker::NetworkWorker(std::string name, boost::uint16_t tickTime)
:Service(name, tickTime)
{
	std::cout << " NetworkWorker NetworkWorker" << std::endl;
}

NetworkWorker::~NetworkWorker()
{

}

NetworkWorker* NetworkWorker::getInstance()
{
	return p_NetInstance;
}

void NetworkWorker::onStart()
{
	Service::onStart();
	std::cout << " onStart" << std::endl;
}

void NetworkWorker::onFinish()
{
	Service::onFinish();
	std::cout << getName() <<" onFinish" << std::endl;
}

void NetworkWorker::onTick()
{
	SG_TRACE("onTick")
}

NS_END_SG