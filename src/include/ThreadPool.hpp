#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <future>
#include <Windows.h>

namespace my
{
	class BaseThreadDataHolder
	{
	public:
		virtual void Execute() {};
		virtual ~BaseThreadDataHolder() = default;
	};

	template<typename Out, typename... In>
	class ThreadHolderWithData : public BaseThreadDataHolder
	{
		std::packaged_task<Out(ThreadHolderWithData&)> task;
		std::tuple<In...> data;
	public:
		ThreadHolderWithData(std::function<Out(ThreadHolderWithData&)> task, In... args) : task(task), data{args...}
		{
			
		}
		~ThreadHolderWithData() override {};
		void Execute() override
		{
			task(*this);
		}
		template<std::size_t Index>
		auto get() -> decltype(std::get<Index>(data)) {
			return std::get<Index>(data);
		}
		std::future<Out> getFuture()
		{
			return task.get_future();
		}
	};

	class ThreadHolder : public BaseThreadDataHolder
	{
		std::function<void()> task;
	
	public:
		ThreadHolder(std::function<void()>& task) : task(task)
		{
	
		}
		~ThreadHolder() override = default;
		void Execute() override
		{
			task();
		}
	};

	class ThreadPool
	{
		bool stop;
		std::vector<std::thread> workers;
		std::queue<BaseThreadDataHolder*> tasks;

		std::mutex queue_mutex;
		std::condition_variable condition;
		friend class Engine;

	public:
		ThreadPool(size_t num_threads) : stop{ false }
		{
			for (size_t i = 0; i < num_threads; ++i)
			{
				workers.emplace_back(&ThreadPool::worker_thread, this, i);
			}
		}
		~ThreadPool()
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
			while (!tasks.empty())
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				delete tasks.front();
				tasks.pop();
			}
		}


		template<typename Out, typename... In>
		std::future<Out> enqueueD(std::function<Out(ThreadHolderWithData<Out, In...>&)> task, In... args)
		{
			ThreadHolderWithData<Out, In...>* holder = new ThreadHolderWithData<Out, In...>(task, args...);
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				tasks.push(holder);
			}
			condition.notify_one();
			return holder->getFuture();
		}

		void enqueue(std::function<void()> task)
		{
			ThreadHolder* holder = new ThreadHolder(task);
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				tasks.push(holder);
			}
			condition.notify_one();
		}


		void worker_thread(size_t id)
		{
			while (true)
			{
				BaseThreadDataHolder* holder;
				{
					std::unique_lock<std::mutex> lock(queue_mutex);
					condition.wait(lock, [this]() { return stop || !tasks.empty(); });
					if (stop) return;
					holder = tasks.front();
					tasks.pop();
				}
				holder->Execute();
				delete holder;
			}
		}
	};
}
