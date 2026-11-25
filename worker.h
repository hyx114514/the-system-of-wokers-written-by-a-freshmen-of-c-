#pragma once
#include<iostream>
using namespace std;



class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;

	//获取岗位名称
	virtual int getDepartmentId() = 0;

	//职工编号
	int Id;

	//职工姓名
	string Name;

	//部门编号
	int DepartmentId;
};