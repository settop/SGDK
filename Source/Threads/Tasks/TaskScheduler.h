#pragma once

#include "TaskDefines.h"
#include <boost/thread.hpp>
#include <boost/lockfree/queue.hpp>

class TaskScheduler;

class TaskHandle : public boost::noncopyable
{
public:
	static TaskHandle const INVALID_TASKID;
	inline TaskHandle();

	inline bool IsFinished() const;

	//TaskHandle(TaskHandle const&) = delete;
	//TaskHandle& operator=(TaskHandle const&) = delete;
private:
	friend class TaskScheduler;

	boost::atomic<uint32> m_taskCounter;
};

class TaskScheduler
{
private:
	template<typename T>
	struct KernalInfo
	{
		typedef void (*Kernal)(T const &);

		static void KernalTranslate(void *_data);

		Kernal m_kernal;
		T m_data;
	};
public:
	TaskScheduler();
	~TaskScheduler();		

	template<typename T>
	void AddTask(typename KernalInfo<T>::Kernal _kernal,T const &_data, TaskHandle *_taskHandle = nullptr);
	//returns true if a task was done
	bool DoOneTask();

	void WaitOnTask(TaskHandle *_handle);

private:
	struct Task
	{
		TaskHandle *m_handle;
		Kernal m_kernal;
		char m_taskData[Task_Data_Max_size];
	};

#pragma message("Need to use my own allocator for this")
	boost::lockfree::queue<Task, boost::lockfree::capacity<Max_Tasks>/*, boost::lockfree::allocator<TaskAllocator>*/> m_queue;

	//thread wait objects
	boost::mutex m_mutex;
	boost::condition_variable m_conditional;
};


#include "TaskScheduler.inl"