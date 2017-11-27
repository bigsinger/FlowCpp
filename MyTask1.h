#pragma once
#include "ITask.h"

class MyTask1 : public ITask {
public:
	virtual string GetName() {
		return "MyTask1";
	}

public:
	virtual bool OnInit() {
		return true;
	}
	virtual void OnBeforeWork() {}
	virtual void OnAfterWork() {}
	virtual void OnWork() {
		Sleep(1000);
	}
	virtual void OnRelease() {
	}
private:

};