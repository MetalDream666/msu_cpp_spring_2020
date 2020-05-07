#include <mutex>
#include <thread>
#include <functional>

#include "threadpool.h"

ThreadPool::ThreadPool(size_t poolSize) : poolSize(poolSize)
{
	notified_available = false;
	tasks_available = false;
	stop = false;
	available_workers = poolSize;
	
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
	while (true)
	{
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
			continue;
		else
		{
			task();
			{
				std::unique_lock<std::mutex> lock(available_mutex);
				available_workers += 1;
				notified_available = true;
				available_cv.notify_one();
			}
		}
	}
}
