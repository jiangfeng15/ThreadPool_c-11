#pragma once
#include <string>
using namespace std;

class CTask
{
public:
	CTask();
	~CTask();
	void SetTaskName(char* taskname);
	//ָ��Run�ӿ�
	virtual void Run(/*void *pvargs*/) = 0;
	int GetTaskNo(void);
	void SetTaskNo(int taskno);
	char* GetTaskName(void) const;

private:
	int m_taskNo;                    //������
	string m_taskName;               //��������
};

