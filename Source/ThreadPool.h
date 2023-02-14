#pragma once
#include <condition_variable>
#include <functional>
#include <vector>
#include <thread>
#include <queue>

class ThreadPool {
public:
	using Task = std::function<void()>;

	ThreadPool(short threadCount) {
		Start(threadCount);
	}

	~ThreadPool() {
		Stop();
	}

	void Enqueue(Task task) {
		{
			std::unique_lock<std::mutex> lock(mutex);
			tasks.emplace(std::move(task));
		}

		condition.notify_one();
	}

	void Wait() {
		while (!tasks.empty()) {}

		for (auto& thread : threads)
			thread.join();
	}

private:
	std::vector<std::thread> threads;
	std::condition_variable condition;
	std::mutex mutex;
	std::queue<Task> tasks;

	bool running = false;

	void Start(short threadCount) {
		for (short i = 0; i < threadCount; i++)
		{
			threads.emplace_back([=] {
				while (true) {
					Task task;
					{
						std::unique_lock<std::mutex> lock(mutex);

						condition.wait(lock, [=] { return running || !tasks.empty(); });

						if (running && tasks.empty())
							break;

						task = std::move(tasks.front());
						tasks.pop();
					}
					task();
				}
				});
		}
	}

	void Stop() {
		{
			std::unique_lock<std::mutex> lock(mutex);
			running = true;
		}

		condition.notify_all();

		for (auto& thread : threads)
			thread.join();
	}
};