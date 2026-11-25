#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Boss : public Worker
{
public:
	//显示个人信息
	virtual void showInfo();

	//构造函数
	Boss(int id, string name, int depId);


	//获取岗位名称
	string getDepartName();

	//获取岗位号码
	virtual int getDepartmentId();

	//获取岗位职责
	string getDepartRisk();
};