#include "NetworkWorker.h"

NS_BEGIN_SG

NetworkWorker* NetworkWorker::p_NetInstance = new NetworkWorker(shared_ptr<ASIO_SERV>(new ASIO_SERV()), 3344);

NetworkWorker::NetworkWorker(shared_ptr<ASIO_SERV> ioservice, SgInt16 port)
:Service("network", 0),
_ioservice(ioservice),
_port(port),
_accptor(*ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port))
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
	std::cout << getName()<<" onStart at _port:" << _port<< std::endl;
}

void NetworkWorker::startAccept()
{
	shared_ptr<boost::asio::ip::tcp::socket> _sock(new boost::asio::ip::tcp::socket(*_ioservice));
	_accptor.async_accept(*_sock, boost::bind(&NetworkWorker::handleAccept, this, _sock, _1));
}

void NetworkWorker::handleAccept(shared_ptr<boost::asio::ip::tcp::socket> socket, boost::system::error_code err)
{
	if (err)
	{
		SG_TRACE2("handleAccept err: ", err);
		return;
	}

	SG_TRACE2("handleAccept: ", socket->remote_endpoint().address());
	SgInsSessionServMgr->addSession(socket);

	//socket->write_some(boost::asio::buffer("hello"));
	startAccept();
}

void NetworkWorker::onRunning()
{
	startAccept();
	_ioservice->run();
}

void NetworkWorker::onFinish()
{
	Service::onFinish();
	std::cout << getName() <<" onFinish" << std::endl;

	_ioservice->stop();
	//_sock->close();
	_accptor.close();
}

void NetworkWorker::onTick()
{
	SG_TRACE("onTick")
}

NS_END_SG