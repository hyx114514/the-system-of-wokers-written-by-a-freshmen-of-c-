#pragma once
//普通员工头文件
#include<iostream> 
using namespace std;
#include"worker.h"

class Employee : public Worker
{
public:
	//构造函数
	Employee(int id,string name,int depId);

	//显示个人信息
	virtual void showInfo();
	
	//获取岗位号码
	virtual int getDepartmentId();
	
	//获取岗位名称
	string getDepartName();

	//获取岗位职责
	string getDepartRisk();
};