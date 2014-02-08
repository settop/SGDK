#pragma once

#include "TaskScheduler.h"

inline TaskHandle::TaskHandle
(
) : m_taskCounter(0)
{
}

inline bool TaskHandle::IsFinished
(
) const
{
	return m_taskCounter.load() == 0;
}

template<typename T>
void TaskScheduler::KernalInfo<T>::KernalTranslate
(
	void *_data
)
{
	KernalInfo<T> *data = (KernalInfo<T>*)_data;
	data->m_kernal(data->m_data);
}

template<typename T>
void TaskScheduler::AddTask
(
	typename KernalInfo<T>::Kernal _kernal, 
	T const &_data, 
	TaskHandle *_taskHandle// = nullptr
)
{	
static_assert(sizeof(KernalInfo<T>) < Task_Data_Max_size, "The size of the task data is too large");
	Task task;
	KernalInfo<T> *kernalData = (KernalInfo<T>*)task.m_taskData;
	kernalData->m_kernal = _kernal;
	kernalData->m_data = _data;

	task.m_handle = _taskHandle;
	if(task.m_handle)
	{
		task.m_handle->m_taskCounter.fetch_add(1);
	}
	task.m_kernal = &KernalInfo<T>::KernalTranslate;

	bool result = m_queue.bounded_push(task);
	Verify(result, "The task scheduler pool is full\nWill now busy wait until there is room\nTHIS IS BAD!!");
#if S_DEBUGGING
	while(!result)
	{		
		result = m_queue.bounded_push(task);
	}
	m_conditional.notify_one();
#endif

}