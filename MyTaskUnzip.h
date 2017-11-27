#pragma once
#include "ITask.h"

class MyTaskUnzip : public ITask {
public:
	virtual string GetName() {
		return "MyTaskUnzip";
	}

public:
	virtual bool OnInit() {


		return true;
	}
	virtual void OnBeforeWork() {}
	virtual void OnAfterWork() {}
	virtual void OnWork() {
		Sleep(2000);
	}
	virtual void OnRelease() {
	}
private:

};