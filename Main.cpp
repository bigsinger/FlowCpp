// Flow.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Flow.h"
#include "Log.h"
#include "ITask.h"
#include "MyTask1.h"
#include "MyTaskUnzip.h"
#include "MyTaskDecompile.h"
#include "MyTaskDealDex.h"
#include "MyTaskDealSo.h"
#include "MyTaskDealGame.h"
#include "MyTaskDealH5.h"
#include "MyTaskDeleteTemps.h"

int main() {
	g_log.EnableLogFile(true);
	CFlow flow;

	//添加准备任务：步骤1执行完后同时执行步骤2
	flow.AddPrePareTask(new MyTask1(), 1);
	flow.AddPrePareTask(new MyTaskUnzip(), 2);
	flow.AddPrePareTask(new MyTaskDecompile(), 2);

	//添加工作任务：全部异步
	flow.AddWorkTask(new MyTaskDealDex());
	flow.AddWorkTask(new MyTaskDealSo());
	flow.AddWorkTask(new MyTaskDealGame());
	flow.AddWorkTask(new MyTaskDealH5());

	//添加收尾任务
	flow.AddCleanTask(new MyTaskDeleteTemps());

	flow.Prepare();
	flow.Work();
	flow.Release();
	return 0;
}

