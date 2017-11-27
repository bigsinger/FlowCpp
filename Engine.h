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
	//���һ��׼������ע��step��ͬ������ᱻһ���첽ִ�У������ͬ��˳��ִ�У������ò�ͬ��step��
	void AddPrePareTask(ITaskPtr pTask, int nStep = -1);
	
	//���һ����������ע��step��ͬ������ᱻһ���첽ִ�У������ͬ��˳��ִ�У������ò�ͬ��step��
	void AddWorkTask(ITaskPtr pTask, int nStep = -1);
	
	//���һ����β����ע��step��ͬ������ᱻһ���첽ִ�У������ͬ��˳��ִ�У������ò�ͬ��step��
	void AddCleanTask(ITaskPtr pTask, int nStep = -1);

	//�����ʼ���������׼��������ִ�����ǣ�step��ͬ����һ���첽ִ�У������Ⱥ�ִ�С�
	void Init();
	
	//������ִ�й�������step��ͬ����һ���첽ִ�У������Ⱥ�ִ�С�
	void Work();
	
	//�����ͷţ��������β������ִ�����ǣ�step��ͬ����һ���첽ִ�У������Ⱥ�ִ�С�
	void Release();

private:
	void ExecuteTasks(const map<int, list<ITaskPtr>*>&mapTasks);
	void ThreadWork(ITaskPtr pTask);

private:
	map<int, list<ITaskPtr>*>m_mapPrePareTasks;	//׼�����񣺿���Ϊ�ա���Ҫ��һ���Ե�׼�������������AddPrePareTask��ӡ�
	map<int, list<ITaskPtr>*>m_mapWorkTasks;	//�������񣺿���һ���Ե���Ҳ�����µ��ã���˸�׼���������β����ֿ��ˡ������AddWorkTask��ӡ�
	map<int, list<ITaskPtr>*>m_mapCleanTasks;	//��β���񣺿���Ϊ�ա���Ҫ��һ���Ե���β�����������AddCleanTask��ӡ�
};

