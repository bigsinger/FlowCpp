#pragma once
#include <list>
#include <map>
#include "ITask.h"

/*


*/


class CEngine
{
public:
	CEngine();
	~CEngine();
public:
	//添加一个准备任务，注意step相同的任务会被一起异步执行，如果想同步顺序执行，请设置不同的step。
	void AddPrePareTask(ITaskPtr pTask, int nStep = -1);
	
	//添加一个工作任务，注意step相同的任务会被一起异步执行，如果想同步顺序执行，请设置不同的step。
	void AddWorkTask(ITaskPtr pTask, int nStep = -1);
	
	//添加一个收尾任务，注意step相同的任务会被一起异步执行，如果想同步顺序执行，请设置不同的step。
	void AddCleanTask(ITaskPtr pTask, int nStep = -1);

	//引擎初始化，如果有准备任务则执行它们，step相同的则一起异步执行，否则先后执行。
	void Init();
	
	//工作：执行工作任务。step相同的则一起异步执行，否则先后执行。
	void Work();
	
	//引擎释放，如果有收尾任务则执行它们，step相同的则一起异步执行，否则先后执行。
	void Release();

private:
	void ExecuteTasks(const map<int, list<ITaskPtr>*>&mapTasks);
	void ThreadWork(ITaskPtr pTask);

private:
	map<int, list<ITaskPtr>*>m_mapPrePareTasks;	//准备任务：可以为空。主要是一次性的准备工作，请调用AddPrePareTask添加。
	map<int, list<ITaskPtr>*>m_mapWorkTasks;	//工作任务：可以一次性调用也可重新调用，因此跟准备任务和收尾任务分开了。请调用AddWorkTask添加。
	map<int, list<ITaskPtr>*>m_mapCleanTasks;	//收尾任务：可以为空。主要是一次性的收尾工作，请调用AddCleanTask添加。
};

