#include<iostream>
#include"boss.h"
using namespace std;


//构造函数
Boss:: Boss(int id, string name, int depId)
{
	this->Id = id;
	this->Name = name;
	this->DepartmentId = depId;
}

//显示个人信息
void Boss::showInfo()
{
	cout << "职工编号:" << this->Id << endl;;
	cout << "\t职工姓名:" << this->Name << endl;;
	cout << "\t岗位:" << this->getDepartName() << endl;
	cout << "\t岗位职责:" << this->getDepartRisk() << endl;
}

//岗位职责
string Boss::getDepartRisk()
{
	return string("管理公司所有任务，安排经理和员工做事");
}

//获取岗位名称
string Boss::getDepartName()
{
	return string("老板");
}

//获取岗位号码
int Boss::getDepartmentId()
{
	return this->DepartmentId;
}