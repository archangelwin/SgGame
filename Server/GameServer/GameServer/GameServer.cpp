// GameServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "boost/asio.hpp"
#include "network/NetworkWorker.h"
#include "boost/thread.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include "boost/pool/singleton_pool.hpp"

#include "./protocol/SgMsg.Proto.pb.h"

US_NS_SG
US_NS_BOOST

void func()
{
	std::cout << "func test" << std::endl;
}

void initLog()
{
	boost::log::add_file_log("sample.log");
	BOOST_LOG_TRIVIAL(trace) << "initLog";
}

void deleteStringPtr(std::string* pStr)
{
	std::cout << " deleteString " << std::endl;
	delete pStr;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "main start" << std::endl;

	initLog();

	scoped_ptr<pbTest> pbTest(new pbTest());
	pbTest->set_id(123);
	pbTest->set_name("xxx123");
	pbTest->PrintDebugString();

	boost::thread threadNetwork(boost::bind(&NetworkWorker::run, NetworkWorker::getInstance()));
	shared_ptr<boost::thread_group> threadGroup(new boost::thread_group());
	SgInsSessionServMgr->startSessionServices(threadGroup);
	//boost::this_thread::sleep(boost::posix_time::millisec(500));

	//shared_ptr<Message> pMsg(new Message());
	//pMsg->mId = MessageId::WorkerExit;
	//NetworkWorker::getInstance()->postMessage(pMsg);

	threadNetwork.join();
	threadGroup->join_all();
	//assert(pStr == NULL);

	::system("pause");
	return 0;
}

