#include "pch.h"
#include "CTask.h"


CTask::CTask():/*m_pWorkThread(NULL),*/
	m_taskNo(0),
	m_taskName("")
{
}


CTask::~CTask()
{
}

void CTask::SetTaskName(char* taskname)
{
	m_taskName = taskname;
}
//���û��ȡ������
int CTask::GetTaskNo(void)
{
	return m_taskNo;
}

void CTask::SetTaskNo(int jobno)
{
	m_taskNo = jobno;
}

//���û��ȡ��������
char* CTask::GetTaskName(void) const
{
	return (char *)m_taskName.c_str();
}

////��ȡ�����ù����߳�
//WorkerThread *  CTask::GetWorkThread()
//{
//	return m_pWorkThread;
//}
//void CTask::SetWorkThread(WorkerThread *  pWorkThread)
//{
//	m_pWorkThread = pWorkThread;
//}
//void CTask::DeleteWorkThread()
//{
//	m_pWorkThread = NULL;
//}
