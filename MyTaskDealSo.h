#pragma once
#include "ITask.h"

class MyTaskDealSo : public ITask {
public:
	virtual string GetName() {
		return "¥¶¿ÌSO";
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