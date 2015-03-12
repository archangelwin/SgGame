//  [3/5/2015 wuliangyu]

#ifndef Runable_h__
#define Runable_h__
#include "SGMacro.h"

NS_BEGIN_SG

class Runable
{
public:
	Runable(){}
	virtual ~Runable(){}

	virtual void run() = 0;
};

NS_END_SG

#endif // Runable_h__