#include "stdafx.h"
#include "Engine.h"
#include "Log.h"
#include <thread>

CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

void CEngine::AddPrePareTask(ITaskPtr pTask, int nStep/* = -1*/) {
	if (pTask) {
		list<ITaskPtr> *lstTask = m_mapPrePareTasks[nStep];
		if (lstTask == NULL) {
			lstTask = new list<ITaskPtr>;
			m_mapPrePareTasks[nStep] = lstTask;
		}
		lstTask->push_back(pTask);
	}
}

void CEngine::AddCleanTask(ITaskPtr pTask, int nStep/* = -1*/) {
	if (pTask) {
		list<ITaskPtr> *lstTask = m_mapCleanTasks[nStep];
		if (lstTask == NULL) {
			lstTask = new list<ITaskPtr>;
			m_mapCleanTasks[nStep] = lstTask;
		}
		lstTask->push_back(pTask);
	}
}

void CEngine::AddWorkTask(ITaskPtr pTask, int nStep/* = -1*/) {
	if (pTask) {
		list<ITaskPtr> *lstTask = m_mapWorkTasks[nStep];
		if (lstTask==NULL) {
			lstTask = new list<ITaskPtr>;
			m_mapWorkTasks[nStep] = lstTask;
		}
		lstTask->push_back(pTask);
	}
}

void CEngine::Work() {
	LOG("-------------------------------");
	LOG("%s Begin", __FUNCTION__);
	LOG("ִ�й�������...");
	if (m_mapWorkTasks.empty() == false) {
		time_t start, end; time(&start);
		this->ExecuteTasks(m_mapWorkTasks);
		time(&end);
		LOG("�����������, ��ʱ: %.2lf s", difftime(end, start));
	} else {
		LOG("��ǰ����û�й�������.");
	}
	LOG("%s OK", __FUNCTION__);
	LOG("-------------------------------\n");
}

void CEngine::Init() {
	LOG("-------------------------------");
	LOG("%s Begin", __FUNCTION__);
	LOG("ִ��׼������...");
	if (m_mapPrePareTasks.empty() == false) {
		time_t start, end; time(&start);
		this->ExecuteTasks(m_mapPrePareTasks);
		time(&end);
		LOG("׼���������, ��ʱ: %.2lf s", difftime(end, start));
	} else {
		LOG("��ǰ����û��׼������.");
	}

	if (m_mapPrePareTasks.empty() == false) {
		time_t start, end; time(&start);
		this->ExecuteTasks(m_mapPrePareTasks);
		time(&end);
		LOG("׼���������, ��ʱ: %.2lf s", difftime(end, start));
	} else {
		LOG("��ǰ����û��׼������.");
	}
	LOG("%s OK", __FUNCTION__);
	LOG("-------------------------------\n");
}

void CEngine::Release() {
	LOG("-------------------------------");
	LOG("%s Begin", __FUNCTION__);
	LOG("ִ����β����...");
	if (m_mapCleanTasks.empty()==false) {
		time_t start, end; time(&start);
		this->ExecuteTasks(m_mapCleanTasks);
		time(&end);
		LOG("��β�������, ��ʱ: %.2lf s", difftime(end, start));
	} else {
		LOG("��ǰ����û����β����.");
	}

	LOG("���׼������...");
	for (auto i : m_mapPrePareTasks) {
		list<ITaskPtr> *lstTask = i.second;
		if (lstTask) {
			delete lstTask;
		}
	}
	m_mapPrePareTasks.clear();

	LOG("�����������...");
	for (auto i : m_mapWorkTasks) {
		list<ITaskPtr> *lstTask = i.second;
		if (lstTask) {
			delete lstTask;
		}
	}
	m_mapWorkTasks.clear();

	LOG("�����β����...");
	for (auto i : m_mapCleanTasks) {
		list<ITaskPtr> *lstTask = i.second;
		if (lstTask) {
			delete lstTask;
		}
	}
	m_mapCleanTasks.clear();

	LOG("%s OK", __FUNCTION__);
	LOG("-------------------------------\n");
}



//C++11���߳�std::thread�ļ�ʹ�� https://www.cnblogs.com/sevenyuan/p/4060424.html
void CEngine::ThreadWork(ITaskPtr pTask) {
	pTask->Work();
}

void CEngine::ExecuteTasks(const map<int, list<ITaskPtr>*>&mapTasks) 	{
	for (auto i : mapTasks) {
		time_t start, end;
		time(&start);
		LOG("����: %d ������ִ�п�ʼ", i.first);
		list<std::thread *>lstThread;
		for (auto pTask : *i.second) {
			//���ﴴ���̵߳��ã���Ϊ����һ�����첽����
			//pTask->Work();
			lstThread.push_back(new std::thread(&CEngine::ThreadWork, this, pTask));
		}

		//����Ҫ�������߳̽������ܿ�ʼ��һ���������
		for (auto t : lstThread) {
			t->join();
			delete t;
		}
		time(&end);
		LOG("����: %d ������ִ�����, ��ʱ: %.2lf s", i.first, difftime(end, start));
	}
}

