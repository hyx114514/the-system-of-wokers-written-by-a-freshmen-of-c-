#include"manager.h"

//显示个人信息
void Manager::showInfo()
{
	cout << "职工编号:" << this->Id << endl;;
	cout << "\t职工姓名:" << this->Name << endl;;
	cout << "\t岗位:" << this->getDepartName() << endl;
	cout << "\t岗位职责:" << this->getDepartRisk() << endl;
}

//获取岗位名称
string Manager::getDepartName()
{
	return string("经理");
}

//构造函数
Manager::Manager(int id, string name, int depId)
{
	Id = id;
	Name = name;
	DepartmentId = depId;
}

//获取岗位号码
int Manager::getDepartmentId()
{
	return this->DepartmentId;
}

//获取岗位职责
string Manager::getDepartRisk()
{
	return string("完成老板交给的任务，并且下发任务给员工");
}