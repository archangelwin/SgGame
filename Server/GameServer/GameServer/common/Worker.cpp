#include "Worker.h"
#include <SgLib.h>

NS_BEGIN_SG

Worker::Worker()
 :_pThread(NULL),
 _workerStat(WorkIdle)
{
} 

Worker::~Worker()
{

}

void Worker::run()
{
	_workerStat = WorkerStarting;
	onStart();
	_workerStat = WorkerRunning;
	onRunning();
	_workerStat = WorkerCancelling;
	onFinish();
	_workerStat = WorkerFinished;
}

NS_END_SG