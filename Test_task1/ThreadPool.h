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
	void addThread();

	std::atomic<bool> isQuitRequested{ false };

	//������� ��� ���������� ��������������� ��������
	std::atomic<size_t> nextID{ 0 };

	//������� �����
	std::queue<std::pair<std::function<void()>, size_t>> taskQueue;
	std::mutex queueMutex;
	std::condition_variable queueCV;
	//������
	std::vector<std::thread> threads;
	
	//���� ��� �������� ��������������� ����������� �����
	//�� ��������, ��� ������ ���� � ��� ����� ��� ����� �����, ��� � ��� �������� ��� ��������� ������� (����� ������ ������ ������������)
	//��� ������� ������� ������������ � ����� ������ ��������� ����� ThreadPool
	std::set<size_t> compeletedTasksIds;
	std::mutex setMutex;
	std::condition_variable setCV;
};

