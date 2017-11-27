#pragma once
#include "ITask.h"

class MyTaskDealDex : public ITask {
public:
	virtual string GetName() {
		return "¥¶¿ÌDEX";
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