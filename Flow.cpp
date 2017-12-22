#include "stdafx.h"
#include "Flow.h"
#include "Log.h"
#include <thread>

CFlow::CFlow()
{
}


CFlow::~CFlow()
{
}

void CFlow::AddPrePareTask(ITaskPtr pTask, int nStep/* = -1*/) {
	if (pTask) {
		list<ITaskPtr> *lstTask = m_mapPrePareTasks[nStep];
		if (lstTask == NULL) {
			lstTask = new list<ITaskPtr>;
			m_mapPrePareTasks[nStep] = lstTask;
		}
		lstTask->push_back(pTask);
	}
}

void CFlow::AddCleanTask(ITaskPtr pTask, int nStep/* = -1*/) {
	if (pTask) {
		list<ITaskPtr> *lstTask = m_mapCleanTasks[nStep];
		if (lstTask == NULL) {
			lstTask = new list<ITaskPtr>;
			m_mapCleanTasks[nStep] = lstTask;
		}
		lstTask->push_back(pTask);
	}
}

void CFlow::AddWorkTask(ITaskPtr pTask, int nStep/* = -1*/) {
	if (pTask) {
		list<ITaskPtr> *lstTask = m_mapWorkTasks[nStep];
		if (lstTask==NULL) {
			lstTask = new list<ITaskPtr>;
			m_mapWorkTasks[nStep] = lstTask;
		}
		lstTask->push_back(pTask);
	}
}

void CFlow::Work() {
	LOG("-------------------------------");
	LOG("%s Begin", __FUNCTION__);
	LOG("执行工作任务...");
	if (m_mapWorkTasks.empty() == false) {
		time_t start, end; time(&start);
		this->RunTasks(m_mapWorkTasks);
		time(&end);
		LOG("工作任务完成, 耗时: %.2lf s", difftime(end, start));
	} else {
		LOG("当前工作没有工作任务.");
	}
	LOG("%s OK", __FUNCTION__);
	LOG("-------------------------------\n");
}

void CFlow::Prepare() {
	LOG("-------------------------------");
	LOG("%s Begin", __FUNCTION__);
	LOG("执行准备任务...");
	if (m_mapPrePareTasks.empty() == false) {
		time_t start, end; time(&start);
		this->RunTasks(m_mapPrePareTasks);
		time(&end);
		LOG("准备任务完成, 耗时: %.2lf s", difftime(end, start));
	} else {
		LOG("当前工作没有准备任务.");
	}
	LOG("%s OK", __FUNCTION__);
	LOG("-------------------------------\n");
}

void CFlow::Release() {
	LOG("-------------------------------");
	LOG("%s Begin", __FUNCTION__);
	LOG("执行收尾任务...");
	if (m_mapCleanTasks.empty()==false) {
		time_t start, end; time(&start);
		this->RunTasks(m_mapCleanTasks);
		time(&end);
		LOG("收尾任务完成, 耗时: %.2lf s", difftime(end, start));
	} else {
		LOG("当前工作没有收尾任务.");
	}

	LOG("清除准备任务...");
	for (auto i : m_mapPrePareTasks) {
		list<ITaskPtr> *lstTask = i.second;
		if (lstTask) {
			delete lstTask;
		}
	}
	m_mapPrePareTasks.clear();

	LOG("清除工作任务...");
	for (auto i : m_mapWorkTasks) {
		list<ITaskPtr> *lstTask = i.second;
		if (lstTask) {
			delete lstTask;
		}
	}
	m_mapWorkTasks.clear();

	LOG("清除收尾任务...");
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



//C++11多线程std::thread的简单使用 https://www.cnblogs.com/sevenyuan/p/4060424.html
void CFlow::ThreadWork(ITaskPtr pTask) {
	pTask->Work();
}

void CFlow::RunTasks(const map<int, list<ITaskPtr>*>&mapTasks) 	{
	for (auto i : mapTasks) {
		time_t start, end;
		time(&start);
		LOG("步骤: %d 的任务执行开始", i.first);
		list<std::thread *>lstThread;
		for (auto pTask : *i.second) {
			//这里创建线程调用，因为步骤一样，异步调用
			//pTask->Work();
			lstThread.push_back(new std::thread(&CFlow::ThreadWork, this, pTask));
		}

		//这里要等所有线程结束才能开始下一步骤的任务
		for (auto t : lstThread) {
			t->join();
			delete t;
		}
		time(&end);
		LOG("步骤: %d 的任务执行完成, 耗时: %.2lf s", i.first, difftime(end, start));
	}
}

