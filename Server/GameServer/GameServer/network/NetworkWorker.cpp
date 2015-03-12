#include "NetworkWorker.h"

NS_BEGIN_SG

NetworkWorker* NetworkWorker::p_NetInstance = new NetworkWorker("network", 50, 3344);

NetworkWorker::NetworkWorker(std::string name, boost::uint16_t tickTime, boost::uint16_t port)
:Service(name, tickTime),
_port(port),
_ioservice()
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

	boost::asio::ip::tcp::acceptor accpt(_ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port));
	_sock.reset(new boost::asio::ip::tcp::socket(_ioservice));
	accpt.async_accept(*_sock, boost::bind(&NetworkWorker::handleAccept, this, _sock, _1));
	
	_ioservice.run();
}

void NetworkWorker::handleAccept(shared_ptr<boost::asio::ip::tcp::socket> socket, boost::system::error_code err)
{
	SG_TRACE2("handleAccept: ", socket->remote_endpoint().address());
}

void NetworkWorker::onFinish()
{
	Service::onFinish();
	std::cout << getName() <<" onFinish" << std::endl;

	_ioservice.stop();
	_sock->close();
}

void NetworkWorker::onTick()
{
	SG_TRACE("onTick")
}

NS_END_SG