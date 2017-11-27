#pragma once
#include "ITask.h"

class MyTaskDealH5 : public ITask {
public:
	virtual string GetName() {
		return "¥¶¿ÌH5";
	}

public:
	virtual bool OnInit() {


		return true;
	}
	virtual void OnBeforeWork() {}
	virtual void OnAfterWork() {}
	virtual void OnWork() {
		Sleep(3000);
	}
	virtual void OnRelease() {
	}
private:

};