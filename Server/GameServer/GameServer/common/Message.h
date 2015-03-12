//  [3/11/2015 wuliangyu]

#ifndef Message_h__
#define Message_h__

#include "SGMacro.h"

#include "ComInc.h"

NS_BEGIN_SG
US_NS_BOOST

enum MessageId
{
	WorkerExit = 10000
};

struct Message
{
	MessageId mId;
	shared_ptr<any> mContent;
};

NS_END_SG
#endif // Message_h__