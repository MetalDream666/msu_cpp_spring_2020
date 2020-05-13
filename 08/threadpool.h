#include <future>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <iostream>

class ThreadPool
{
 public:
	explicit ThreadPool(size_t poolSize);

	~ThreadPool();

	// pass arguments by value
	template<class Func, class... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
	{
		auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>(std::bind(func, std::forward<Args>(args)...));
		auto result = task->get_future();

		{
			std::lock_guard<std::mutex> guard(queueLock);
			taskQueue.push([task]()
			{ (*task)(); });
		}

		{
			std::unique_lock<std::mutex> lock(tasks_mutex);
			tasks_available = true;
			available_workers -= 1;
			tasks_cv.notify_one();
		}
		
		return result;
	}

	void worker_function();

 private:
	size_t poolSize;
	size_t available_workers;
	std::queue<std::function<void(void)>> taskQueue;
	std::vector<std::thread> workers;
	std::mutex queueLock;
	std::mutex tasks_mutex;
	std::condition_variable tasks_cv;
	bool tasks_available;

	bool stop;
};
