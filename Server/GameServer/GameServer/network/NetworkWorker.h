//  [3/5/2015 wuliangyu]

#ifndef NetworkWorker_h__
#define NetworkWorker_h__

#include "../common/SGMacro.h"
#include "../common/Service.h"
#include "../common/ComInc.h"
#include "../common/Message.h"

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
	NetworkWorker(std::string name, boost::uint16_t tickTime);

	static NetworkWorker* p_NetInstance;
};

NS_END_SG
#endif // NetworkWorker_h__