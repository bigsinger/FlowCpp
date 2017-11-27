#pragma once
#include "ITask.h"

class MyTaskDeleteTemps : public ITask {
public:
	virtual string GetName() {
		return "É¾³ýÁÙÊ±ÎÄ¼þ";
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