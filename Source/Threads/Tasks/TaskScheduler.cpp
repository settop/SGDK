#pragma once

#include "TaskScheduler.h"
//BOOST_LOCKFREE_CACHELINE_BYTES
//BOOST_LOCKFREE_DCAS_ALIGNMENT

static_assert( ((Task_Data_Max_size) & ((Task_Data_Max_size) - 1)) == 0, "Task_Data_Max_size must be a power of 2" );
static_assert( Max_Tasks < 65534 , "Max tasks must be less than 65534");

TaskScheduler::TaskScheduler
(
) : m_running(true)
{

}

TaskScheduler::~TaskScheduler
(
)
{
}

void TaskScheduler::CreateThreads
(
	uint32 _numThreads
)
{
	for(uint32 i = 0; i < _numThreads; ++i)
	{
		m_threads.create_thread(boost::bind(&TaskScheduler::Run, this));
	}
}

void TaskScheduler::StopAllThreads
(
)
{
	m_running.store(false);
}

void TaskScheduler::JoinAllThreads
(
)
{
	m_threads.join_all();
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
			//boost::this_thread::yield();
		}
	}
}

void TaskScheduler::Run
(
)
{
	while(m_running.load())
	{
		if(!DoOneTask())
		{			
			boost::this_thread::yield();
		}
	}
}