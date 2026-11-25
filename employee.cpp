#include<iostream>
#include"employee.h"
using namespace std;


	//构造函数
Employee::Employee(int id,string name,int depId)
{ 
	this->Id = id;
	this->Name = name;
	this->DepartmentId = depId;
}

	//显示个人信息
void Employee::showInfo()
{
	cout << "职工编号:" << this->Id << endl;;
	cout << "\t职工姓名:" << this->Name << endl;;
	cout << "\t岗位:" << this->getDepartName() << endl;
	cout << "\t岗位职责:" << this->getDepartRisk() << endl;
}

//岗位职责
string Employee::getDepartRisk()
{
	return string("完成经理交给的任务");
}

//获取岗位名称
string Employee::getDepartName()
{
	return string("员工");
}

//获取岗位号码
int Employee::getDepartmentId()
{
	return this->DepartmentId;
}
