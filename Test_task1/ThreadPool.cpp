#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t maxNumThreads)
{
	threads.reserve(maxNumThreads);
	for (size_t i = 0; i < maxNumThreads; i++) 
	{
		threads.emplace_back(&ThreadPool::addThread, this);
	}
}

ThreadPool::~ThreadPool()
{
	isQuitRequested = true;

	for (size_t i = 0; i < threads.size(); i++) {
		queueCV.notify_all();
		threads[i].join();
	}
}

size_t ThreadPool::addTask(std::function<void()> func)
{
	std::lock_guard<std::mutex> lock(queueMutex);
    taskQueue.emplace(func, nextID);

	queueCV.notify_one();

    nextID++;
    return nextID - 1;
}

void ThreadPool::wait(size_t taskId)
{
	std::unique_lock<std::mutex> lock(setMutex);

	setCV.wait(lock, [this, taskId] 
		{ return compeletedTasksIds.find(taskId) != compeletedTasksIds.end(); });
}

void ThreadPool::waitAll()
{
	std::unique_lock<std::mutex> lock(queueMutex);

	setCV.wait(lock, [this]{ 
		std::lock_guard<std::mutex> setLock(setMutex);
		return taskQueue.empty() && nextID == compeletedTasksIds.size();
		});
}

void ThreadPool::addThread()
{
	while (!isQuitRequested)
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		
		queueCV.wait(lock, [this] { return !taskQueue.empty() || isQuitRequested; });

		if (!taskQueue.empty())
		{
			auto elem = std::move(taskQueue.front());
			taskQueue.pop();

			lock.unlock();

			elem.first();

			std::lock_guard<std::mutex> setLock(setMutex);

			compeletedTasksIds.insert(elem.second);

			setCV.notify_one();
		}
	}
}
