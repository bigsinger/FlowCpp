#pragma once
#include "ITask.h"

class MyTaskDeleteTemps : public ITask {
public:
	virtual string GetName() {
		return "ɾ����ʱ�ļ�";
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