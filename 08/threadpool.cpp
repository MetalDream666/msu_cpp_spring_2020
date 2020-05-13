#include <mutex>
#include <thread>
#include <functional>

#include "threadpool.h"

ThreadPool::ThreadPool(size_t poolSize) : poolSize(poolSize)
{
	tasks_available = false;
	stop = false;
	for (size_t s = 0; s < poolSize; s++)
	{
		workers.emplace_back(std::thread(&ThreadPool::worker_function, this));
	}
}

ThreadPool::~ThreadPool()
{
	stop = true;
	tasks_available = true;
	tasks_cv.notify_all();

	for (auto& i : workers)
		i.join();
}

void ThreadPool::worker_function()
{
	bool already_finished(false);
	while (true)
	{
		if (!already_finished)
		{
			std::unique_lock<std::mutex> lock(tasks_mutex);
			while (!tasks_available)
			{
				tasks_cv.wait(lock);
			}
			if (stop)
				break;
			tasks_available = false;
		}

		std::function<void(void)> task;
		bool isTask = false;
		{
			std::lock_guard<std::mutex> guard(queueLock);
			if (!taskQueue.empty())
			{
				task = std::move(taskQueue.front());
				taskQueue.pop();
				isTask = true;
			}
		}
		if (!isTask)
		{
			already_finished = false;
			continue;
		}
		else
		{
			task();
			already_finished = true;
		}
	}
}
