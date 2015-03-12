//  [3/5/2015 wuliangyu]

#ifndef NetworkWorker_h__
#define NetworkWorker_h__

#include "../common/SGMacro.h"
#include "../common/Service.h"
#include "../common/ComInc.h"
#include "../common/Message.h"
#include "boost/asio.hpp"

NS_BEGIN_SG

class NetworkWorker:public Service
{
public:
	virtual ~NetworkWorker();
	static NetworkWorker* getInstance();

	virtual void onStart();
	virtual void onFinish();

	virtual void onTick();

private:
	void handleAccept(shared_ptr<boost::asio::ip::tcp::socket> socket, boost::system::error_code err);

private:
	NetworkWorker(std::string name, boost::uint16_t tickTime, boost::uint16_t port);
	static NetworkWorker* p_NetInstance;

	boost::uint16_t _port;
	boost::asio::io_service _ioservice;
	shared_ptr<boost::asio::ip::tcp::socket> _sock;
};

NS_END_SG
#endif // NetworkWorker_h__