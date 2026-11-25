#pragma once
#include<iostream>
#include"worker.h"
#include<fstream>
using namespace std;


class WorkerManage
{
public:
	//构造函数
	WorkerManage();

	//析构函数
	~WorkerManage();

	//展示菜单
	void Show_Menu();

	//退出系统（0）
	void exitSystem();

	//记录职工人数
	int EmpCount;

	//职工数组指针
	Worker** EmpArray;

	//添加职工（1）
	void AddWorker();

	//保存文件
	void save();

	//判断文件是否为空
	bool isFileEmpty;

	//统计员工个数
	int getEmpNum();

	//初始化员工
	void initEmp();

	//显示员工（2）
	void showWorker();

	//判断职工是否存在,存在就返回数组下标
	int IsExistInt(int num);

	//用查找姓名判断员工是否存在
	int IsExistName(string name);

	//删除员工（3）
	void deleteWorker();

	//修改员工信息（4）
	void reviseWorker();

	//查找员工信息（5）
	void findWorker();

	//按照工号排序（6）
	void bubbleWorker();

	//清空文档（7）
	void clearFile();
};

