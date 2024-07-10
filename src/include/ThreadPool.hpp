#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>

namespace my
{
	class ThreadPool
	{
		bool stop;
		std::vector<std::thread> workers;
		std::queue<std::function<void()>> tasks;
		std::mutex queue_mutex;
		std::condition_variable condition;

	public:
		ThreadPool(size_t num_threads);
		~ThreadPool();

		template<typename... Args>
		void enqueue(std::function<void(Args...)> task, Args... args)
		{
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				tasks.push(task); // ? std::move(task)
			}
			condition.notify_one();
		}
		void worker_thread(size_t id);
	};
}