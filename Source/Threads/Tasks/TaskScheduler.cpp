#pragma once

#include "TaskScheduler.h"
//BOOST_LOCKFREE_CACHELINE_BYTES
//BOOST_LOCKFREE_DCAS_ALIGNMENT

static_assert( ((Task_Data_Max_size) & ((Task_Data_Max_size) - 1)) == 0, "Task_Data_Max_size must be a power of 2" );
static_assert( Max_Tasks < 65534 , "Max tasks must be less than 65534");

TaskScheduler::TaskScheduler
(
)
{

}

TaskScheduler::~TaskScheduler
(
)
{

}

bool TaskScheduler::DoOneTask
(
)
{
	Task task;
	if(m_queue.pop(task))
	{
		task.m_kernal(task.m_taskData);
		if(task.m_handle)
		{
			task.m_handle->m_taskCounter.fetch_sub(1);
		}
		return true;
	}
	else
	{
		return false;
	}		
}

void TaskScheduler::WaitOnTask
(
	TaskHandle *_handle
)
{
	while(_handle->m_taskCounter.load() != 0)
	{
		if(!DoOneTask())
		{
			//failed to do a task, yield this thread
			boost::this_thread::yield();
		}
	}
}