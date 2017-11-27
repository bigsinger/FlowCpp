#pragma once
#include "ITask.h"

class MyTaskDealGame : public ITask {
public:
	virtual string GetName() {
		return "¥¶¿Ì”Œœ∑";
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