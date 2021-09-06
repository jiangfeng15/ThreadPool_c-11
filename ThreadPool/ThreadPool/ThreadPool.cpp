#include "pch.h"
#include "ThreadPool.h"


ThreadPool::ThreadPool()
	:m_bStop(false)
{
}

ThreadPool::ThreadPool(size_t nThreads)
	: m_bStop(false)
{
	string strLog;
	for (size_t i = 0; i < nThreads; i++)
	{
		m_workerThreads.push_back(std::thread(&ThreadPool::Run, this));
	}
	for (std::thread &worker : m_workerThreads)
	{
		std::thread::id threadid = worker.get_id();

		std::ostringstream oss;
		oss << threadid;
		std::string stid = oss.str();

		int m_ThreadID = std::stoull(stid);

		strLog.clear();
		strLog = strLog + "�̳߳ش������߳� [ " + std::to_string(m_ThreadID) + " ]";
		std::cout << strLog << std::endl;
	}
}

ThreadPool::~ThreadPool()
{
	if (!m_bStop)
	{
		std::cout << "������������" << std::endl;
		{
			std::unique_lock<std::mutex> lock(m_TaskQueue_Mutex);
			m_bStop = true;
		}
		m_task_cv.notify_all();
		for (std::thread &worker : m_workerThreads)
		{
			if(worker.joinable())
				worker.join();
		}
		std::cout << "����������������" << std::endl;
	}
}

void ThreadPool::InitThreadPool(size_t nThreads)
{
	string strLog;
	for (size_t i = 0; i < nThreads; i++)
	{
		m_workerThreads.push_back(std::thread(&ThreadPool::Run, this));
	}
	for (std::thread &worker : m_workerThreads)
	{
		std::thread::id threadid = worker.get_id();

		std::ostringstream oss;
		oss << threadid;
		std::string stid = oss.str();

		int m_ThreadID = std::stoull(stid);

		strLog.clear();
		strLog = strLog + "�̳߳ش������߳� [ " + std::to_string(m_ThreadID) + " ]";
		std::cout << strLog << std::endl;
	}
}

void ThreadPool::Run()
{
	for (;;)//�߳���ִ��
	{
		//�ȴ�ȡ���������̣߳�֪�����յ�ֹͣ�ź���������������в�Ϊ��ʱֹͣ�����߳�
		std::unique_lock<std::mutex> lock(this->m_TaskQueue_Mutex);
		this->m_task_cv.wait(lock,
			[this] { return this->m_bStop || !this->m_spTaskQueue.empty(); }); //|| !this->m_spTaskQueue.empty()
		if (this->m_bStop)
			break;
		//ȡ����
		shared_ptr<CTask > wpTask = m_spTaskQueue.front();
		//��������Ƴ�������
		m_spTaskQueue.pop();
		//ִ������
		std::thread::id tId = std::this_thread::get_id();

		std::ostringstream oss;
		oss << tId;
		std::string stid = oss.str();

		int nThreadId = std::stoull(stid);
		std::cout << "�߳� [" << GetCurrentThreadId() << "]ִ������" << std::endl;
		wpTask->Run();
	}
	std::cout << "�߳� [" << GetCurrentThreadId() << "]ִ���������" << std::endl;
}

void ThreadPool::Stop()
{
	{
		std::unique_lock<std::mutex> lock(m_TaskQueue_Mutex);
	}
	m_task_cv.notify_all();
	m_bStop = true;
	for (std::thread &worker : m_workerThreads)
		worker.join();
}
void ThreadPool::AddTask(std::shared_ptr<CTask > spTask)
{
	if (!m_bStop)//�߳�δ����
	{
		std::unique_lock<std::mutex> lk(m_TaskQueue_Mutex);
		m_spTaskQueue.emplace(spTask);
		m_task_cv.notify_one();
	}
}

int ThreadPool::GetCurrentThreadId()
{
	std::thread::id tId= std::this_thread::get_id();

	std::ostringstream oss;
	oss << tId;
	std::string stid = oss.str();

	int nThreadId = std::stoull(stid);

	return nThreadId;
}