#pragma once
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <iostream>
#include "CTask.h"

using namespace std;

class ThreadPool
{
public:
	ThreadPool();
	ThreadPool(size_t nThreads);
	~ThreadPool();
public:
	//��ʼ���̳߳�
	void InitThreadPool(size_t nThreads);
	//�߳����к���
	void Run();
	void Stop();
	void AddTask(std::shared_ptr<CTask > spTask);
	int GetCurrentThreadId();
private:
	//�̳߳�
	std::vector<std::thread > m_workerThreads;
	//�������
	std::queue<std::shared_ptr<CTask > > m_spTaskQueue;
	//�߳�ȡ����ͬ��������
	std::mutex m_TaskQueue_Mutex;
	//�߳�ִ������������������
	std::condition_variable	m_task_cv;
	//ֹͣ�ź���
	bool m_bStop;
};

