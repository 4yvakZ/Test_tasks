#pragma once
#include <functional>
#include <queue>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <set>

class ThreadPool
{
public:
	ThreadPool(size_t maxNumThreads);

	ThreadPool() = delete;

	~ThreadPool();

	size_t addTask(std::function<void()> func);

	void wait(size_t taskId);
	void waitAll();


private:
public:
	void addThread();

	std::atomic<bool> isQuitRequested{ false };

	//счётчик для назначения индетификаторов функциям
	std::atomic<size_t> nextID{ 0 };

	//очередь задач
	std::queue<std::pair<std::function<void()>, size_t>> taskQueue;
	std::mutex queueMutex;
	std::condition_variable queueCV;
	//потоки
	std::vector<std::thread> threads;
	
	//Куча для хранения индетификаторов завершённых задач
	//Не придумал, что делать если у нас будет так много задач, что в ней окажутся все возможные индексы (такой случай правда маловероятен)
	//Как вариант сказать пользователю в таком случае создавать новый ThreadPool
	std::set<size_t> compeletedTasksIds;
	std::mutex setMutex;
	std::condition_variable setCV;
};

