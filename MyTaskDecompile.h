#pragma once
#include "ITask.h"

class MyTaskDecompile : public ITask {
public:
	virtual string GetName() {
		return "MyTaskDecompile";
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