#pragma once
#include "Log.h"
#include <time.h>

class ITask {
public:
	virtual string GetName() = 0;

public:
	bool Init() {
		this->OnInit();
	}
	void Work() {
		time_t start, end; time(&start);
		g_log.Log("开始执行: [%s]", this->GetName().c_str());
		this->OnBeforeWork();;
		this->OnWork();
		this->OnAfterWork();;
		time(&end);
		g_log.Log("执行完成: [%s] 耗时: %.2lf s", this->GetName().c_str(), difftime(end, start));
	}
	 void Release() {
		this->OnRelease();
	}

public:
	virtual bool OnInit() = 0;
	virtual void OnBeforeWork() = 0;
	virtual void OnWork() = 0;
	virtual void OnAfterWork() = 0;
	virtual void OnRelease() = 0;

private:
	string m_sName;
};

typedef ITask *ITaskPtr;