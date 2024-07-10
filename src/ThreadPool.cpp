#include <ThreadPool.hpp>
#include <iostream>
namespace my
{
	ThreadPool::ThreadPool(size_t num_threads) : stop{ false }
	{
		for (size_t i = 0; i < num_threads; ++i)
		{
			workers.emplace_back(&ThreadPool::worker_thread, this, i);
		}
	}

	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(queue_mutex);
			stop = true;
		}
		condition.notify_all();
		for (std::thread& worker : workers)
		{
			worker.join();
		}
	}

	void ThreadPool::worker_thread(size_t id)
	{
		while (true)
		{
			std::function<void()> task;
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				condition.wait(lock, [this]() { return stop || !tasks.empty(); });
				if (stop) return;
				task = tasks.front();
				tasks.pop();
				std::cout << "Execute thread: " << id << std::endl;
			}
			task();
		}
	}
}