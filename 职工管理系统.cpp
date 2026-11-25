#include<iostream>
#include<string>
#include"workerManage.h"
#include"employee.h"
#include"worker.h"
#include"boss.h"
#include"manager.h"
using namespace std;

int main()
{
	//实例化管理者对象
	WorkerManage wm;

	//测试代码
	/*Worker* worker = NULL;
	worker = new Employee(1,"张三",1);
	worker->showInfo();
	delete worker;

	worker = new Manager(2, "李四", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "王五", 3);
	worker->showInfo();
	delete worker;*/

	int input;
	do
	{
		//显示菜单
		wm.Show_Menu();

		//功能选择
		cout << "请输入你要选择的功能:";
		cin >> input;

		switch(input)
		{
		case 0:
			wm.exitSystem();
			break;
		case 1:
			wm.AddWorker();
			break;
		case 2:
			wm.showWorker();
			break;
		case 3:
			wm.deleteWorker();
			break;
		case 4:
			wm.reviseWorker();
			break;
		case 5:
			wm.findWorker();
			break;
		case 6:
			wm.bubbleWorker();
			break;
		case 7:
			wm.clearFile();
			break;
		default:
			cout << "前面的区域以后再来探索吧" << endl;
			system("cls");
			break;
		}
	} while (input);


	system("pause");
	return 0;
}