#include "TaskSchedulerTest.h"

#include <Threads\Tasks\TaskScheduler.h>
#include <Core\Phases\Phase.h>
/*
class TestPhase
{
public:
	TestPhase():Advancer(this){}
	bool DoAdvance()
	{
		return false;
	}
public:
	Phase<DefaultPolicy>::Advancer<TestPhase, &TestPhase::DoAdvance>::Base Advancer;
};
*/

namespace TaskSchedulerTest
{
	struct Sum
	{
		int32* m_l1;
		int32* m_l2;
		uint32 m_count;
		int32 *m_result;
		static void DoSum(Sum const& _sum)
		{
			boost::thread::id ID = boost::this_thread::get_id();
			
			//boost::this_thread::sleep(boost::posix_time::seconds(1));
			for(uint32 i = 0; i < _sum.m_count; ++i)
			{
				_sum.m_result[i] = _sum.m_l1[i] + _sum.m_l2[i];
			}
		}
	};

	void Run
	(
	)
	{
		//TestPhase testPhase;
		//testPhase.Advancer.Activate();


		const uint32 threadCount = 4;
		TaskScheduler scheduler;
		scheduler.CreateThreads(threadCount);

		uint32 const arraySize = 100000;
		int32 *a = new int32[arraySize];
		int32 *b = new int32[arraySize];
		for(uint32 i = 0; i < arraySize; ++i)
		{
			a[i] = b[i] = i;
		}
		int32 *result = new int32[arraySize];
		uint32 const NumTasks = 10;

		TaskHandle handle;
		for(uint32 i = 0; i < NumTasks; ++i)
		{
			Sum sum;
			uint32 startIndex = (arraySize / NumTasks) * i;
			uint32 endIndex = (arraySize / NumTasks) * (i + 1) + ((i + 1) == NumTasks ? arraySize % NumTasks : 0);
			sum.m_l1 = &a[startIndex];
			sum.m_l2 = &b[startIndex];
			sum.m_result = &result[startIndex];
			sum.m_count = endIndex - startIndex;
			scheduler.AddTask(&Sum::DoSum, sum, &handle);
		}
		scheduler.WaitOnTask(&handle);

		scheduler.StopAllThreads();
		scheduler.JoinAllThreads();

		delete[] a;
		delete[] b;
		delete[] result;
	}
}