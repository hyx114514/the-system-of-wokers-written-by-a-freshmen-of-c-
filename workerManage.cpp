#include"workerManage.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#define FILENAME "empFile.txt"


void WorkerManage::Show_Menu()
{
	cout << "-----------------------------------------------" << endl;
	cout << "--------------欢迎使用员工管理系统-------------" << endl;
	cout << "---------------0.退出员工管理系统--------------" << endl;
	cout << "---------------1.增加员工信息------------------" << endl;
	cout << "---------------2.显示员工信息------------------" << endl;
	cout << "---------------3.删除离职员工------------------" << endl;
	cout << "---------------4.修改员工信息------------------" << endl;
	cout << "---------------5.查找员工信息------------------" << endl;
	cout << "---------------6.按照编号排序------------------" << endl;
	cout << "---------------7.清空所有文档------------------" << endl;
	cout << "-----------------------------------------------" << endl;
}

//得到人数
int WorkerManage::getEmpNum()
{
	int num = 0;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int depid;

	while (ifs >> id && ifs >> name && ifs >> depid)
	{
		//统计人数
		num++;
	}
	return num;
}

//构造函数
WorkerManage::WorkerManage()
{
	//1.文件不存在时
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		this->EmpCount = 0;
		this->EmpArray = NULL;
		this->isFileEmpty = true;
		ifs.close();
		return;
	}

	//2.文件存在但是为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		//cout << "文件为空" << endl;
		//初始化属性
		this->EmpCount = 0;
		this->EmpArray = NULL;
		this->isFileEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在并且有数据记录
	int num = this->getEmpNum();
	//cout << "职工人数为:" << num << endl;
	this->EmpCount = num;

	//开辟空间
	this->EmpArray = new Worker * [this->EmpCount];
	//将文件中的数据存储到数组中
	this->initEmp();

	//测试代码
	/*for (int i = 0;i < this->EmpCount;i++)
	{
		cout << "职工编号：" << this->EmpArray[i]->Id
			<< "职工姓名：" << this->EmpArray[i]->Name
			<< "职工部门：" << this->EmpArray[i]->DepartmentId << endl;
	}*/
}

//初始化员工
void WorkerManage::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int depid;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> depid)
	{
		Worker* worker = NULL;

		if (depid == 1)     //普通员工
		{
			worker = new Employee(id, name, depid);
		}

		else if (depid == 2)//经理
		{
			worker = new Manager(id, name, depid);
		}

		else                //老板
		{
			worker = new Boss(id, name, depid);
		}
		this->EmpArray[index] = worker;
		index++;
	}
}

//析构函数
WorkerManage::~WorkerManage()
{ 
	if (this->EmpArray != NULL)
	{
		for (int i = 0;i < this->EmpCount;i++)
		{
			if (this->EmpArray[i] != NULL)
			{
				delete this->EmpArray[i];
				this->EmpArray[i] = NULL;
			}
		}
		delete[] this->EmpArray;
		this->EmpArray = NULL;
	}
}

void WorkerManage::save()
{
	ofstream ofs;
	//输出的方式打开文件，写文件
	ofs.open(FILENAME, ios::out);

	//将每个人数据写入文件中
	for (int i = 0;i < this->EmpCount;i++)
	{
		ofs << this->EmpArray[i]->Id << " "
			<< this->EmpArray[i]->Name << " "
			<< this->EmpArray[i]->DepartmentId << endl;
	}

	//关闭文件
	ofs.close();
}

//添加员工（1）
void WorkerManage::AddWorker()
{
	cout << "请输入如添加职工的数量：" << endl;
	int addCount = 0;
	cin >> addCount;

	if (addCount > 0)
	{
		//计算新空间大小
		int newSize = this->EmpCount + addCount;//新空间人数 = 原来记录人数 + 新增人数

		//开辟新空间
		Worker ** newSpace = new Worker* [newSize];

		//将原来空间下数据拷贝到新空间下
		if (this->EmpArray != NULL)
		{
			for (int i = 0;i < this->EmpCount;i++)
			{
				newSpace[i] = this->EmpArray[i];
			}
		}

		//添加新数据
		for (int i = 0;i < addCount;i++)
		{
			int id;
			string name;
			int depid;

			while (true)
			{
				cout << "请输入第" << i + 1 << "个新员工编号:" << endl;
				if (!(cin >> id))
				{
					cin.clear();                                         // 清除错误状态
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃整行错误输入
					cout << "编号必须是数字，请重新输入！" << endl;
					continue;
				}

				bool dup = false;
				if (IsExistInt(id) != -1) dup = true;
				if (!dup)
				{
					for (int k = 0; k < i; k++)
					{
						if (newSpace[this->EmpCount + k]->Id == id)
						{
							dup = true;
							break;
						}
					}
				}
				if (dup)
				{
					cout << "该工号已被使用，请重新输入" << endl;
					continue;
				}
				break;
			}

			cout << "请输入第" << i + 1 << "个新员工姓名:" << endl;
			cin >> name;

			Worker* worker = NULL;
			while (true)
			{
				cout << "请选择该职工岗位：" << endl;
				cout << "\t1.普通员工" << endl;
				cout << "\t2.经理" << endl;
				cout << "\t3.老板" << endl;
				if (!(cin >> depid))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "请输入数字！" << endl;
					continue;
				}

				switch (depid)
				{
				case 1:
					worker = new Employee(id, name, 1);
					break;
				case 2:
					worker = new Manager(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
				default:
					cout << "输入有误请输入1-3之间的数字" << endl;
					break;
				}
				if (worker != NULL)
				{
					break;
				}
			}
			newSpace[this->EmpCount + i] = worker;
		}
		//释放原有的空间
		delete[] this->EmpArray;

		//更改新空间的指向
		this->EmpArray = newSpace;

		//更新新的职工人数
		this->EmpCount = newSize;

		//成功添加后保存到文件中
		this->save();

		//更新职工文件不为空
		this->isFileEmpty = false;

		//提示添加成功
		cout << "成功添加" << addCount << "名新职工，欢迎新职工入职！！！" << endl;
	}
	else
	{
		cout << "数据有误，请输入大于零的数字" << endl;
	}

	//按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}

//显示员工（2）
void WorkerManage::showWorker()
{
	//判断是否为空
	if (this->isFileEmpty)
	{
		cout << "文件不存在或记录为空,请输入职工信息" << endl;
	}
	else
	{
		for (int i = 0;i < this->EmpCount;i++)
		{
			//利用多态调用程序接口
			this->EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

//判断员工是否存在,以工号方式
int WorkerManage::IsExistInt(int num)
{
	int index = -1;
	for (int i = 0;i < this->EmpCount;i++)
	{
		if (this->EmpArray[i]->Id == num)
		{
			index = i;
			break;
		}
	}
	return index;
}
//判断员工是否存在, 以姓名方式
int WorkerManage::IsExistName(string name)
{
	int index = -1;
	for (int i = 0;i < this->EmpCount;i++)
	{
		if (this->EmpArray[i]->Name == name)
		{
			index = i;
			break;
		}
	}
	return index;
}

//删除员工（3）
void WorkerManage::deleteWorker()
{
	if (this->isFileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		int id;
		cout << "请输入你要删除的职工的编号：";
		cin >> id;
		int ret = this->IsExistInt(id);
		if (ret != -1)
		{
			for (int i = ret;i < this->EmpCount - 1;i++)
			{
				this->EmpArray[i] = this->EmpArray[i + 1];
			}
			//更新维护人员数据个数
			this->EmpCount--;
			//更新数据到文件中
			this->save();

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该员工" << endl;
		}
	}

	system("pause");
	system("cls");
}

//修改员工信息（4）
void WorkerManage::reviseWorker()
{
	if (this->isFileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		int input = 0;
		while (true)
		{
			cout << "请输入你要查找你想修改的员工信息的方式：1->工号，2->姓名：" << endl;
			cin >> input;
			if (input == 1)
			{
				int id = 0;
				cout << "请输入你要修改的员工的工号:";
				cin >> id;
				int ret = IsExistInt(id);

				//检验是否存在这个员工
				if (ret == -1)
				{
					cout << "查无此人" << endl;
					break;
				}

				int num = 1;
				while (num)
				{
					cout << "请选择你要修改的信息种类：" << endl;
					cout << "-----1.工号----2.姓名----" << endl;
					cout << "-----3.岗位----0.退出----" << endl;
					cin >> num;
					switch (num)
					{
					case 1:
						cout << "请输入修改后的工号：";
						while (true)
						{
							int newId;
							if (!(cin >> newId))
							{
								cin.clear();                                         // 清除错误状态
								cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃整行错误输入
								cout << "编号必须是数字，请重新输入！" << endl;
								continue;
							}

							int pos = IsExistInt(newId);
							if (pos != -1&&pos != ret)
							{
								cout << "该工号已被使用，请重新输入" << endl;
								continue;
							}
							this->EmpArray[ret]->Id = newId;
							break;
						}
						break;
					case 2:
						cout << "请输入修改后的姓名：";
						cin >> this->EmpArray[ret]->Name;
						break;
					case 3:
						cout << "请选择改变后的岗位：1.员工,2.经理,3.老板：";
						while (true)
						{
							cin >> this->EmpArray[ret]->DepartmentId;
							if (this->EmpArray[ret]->DepartmentId != 1
								&& this->EmpArray[ret]->DepartmentId != 2
								&& this->EmpArray[ret]->DepartmentId != 3)
							{
								cout << "输入有误，请输入1-3之间的数" << endl;
								continue;
							}
							break;
						}
						break;
					case 0:
						cout << "退出修改" << endl;
						num = 0;
						break;
					default:
						cout << "没有这个选项，请重新输入" << endl;
						break;
					}
				}
				cout << "修改成功" << endl;
				break;
			}
			else if (input == 2)
			{
				string name;
				cout << "请输入你要修改的员工的姓名:";
				cin >> name;
				int ret = IsExistName(name);

				int num = 1;
				while (num)
				{
					cout << "请选择你要修改的信息种类：" << endl;
					cout << "-----1.工号----2.姓名----" << endl;
					cout << "-----3.岗位----0.退出----" << endl;
					cin >> num;
					switch (num)
					{
					case 1:
						cout << "请输入修改后的工号：";
						while (true)
						{
							int newId;
							if (!(cin >> newId))
							{
								cin.clear();                                         // 清除错误状态
								cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃整行错误输入
								cout << "编号必须是数字，请重新输入！" << endl;
								continue;
							}

							int pos = IsExistInt(newId);
							if (pos != -1 && pos != ret)
							{
								cout << "该工号已被使用，请重新输入" << endl;
								continue;
							}
							this->EmpArray[ret]->Id = newId;
							break;
						}
						break;
					case 2:
						cout << "请输入修改后的姓名：";
						cin >> this->EmpArray[ret]->Name;
						break;
					case 3:
						cout << "请选择改变后的岗位：1.员工,2.经理,3.老板：";
						while (true)
						{
							cin >> this->EmpArray[ret]->DepartmentId;
							if (this->EmpArray[ret]->DepartmentId != 1
								&& this->EmpArray[ret]->DepartmentId != 2
								&& this->EmpArray[ret]->DepartmentId != 3)
							{
								cout << "输入有误，请输入1-3之间的数" << endl;
								continue;
							}
							break;
						}
						break;
					case 0:
						cout << "退出修改" << endl;
						cout << endl;
						num = 0;
						break;
					default:
						cout << "没有这个选项，请重新输入" << endl;
						break;
					}
				}
				cout << "修改成功" << endl;
				break;
			}
			else
			{
				cout << "选择有误，请重新选择" << endl;
			}
		}
	}
	//更新数据
	save();

	system("pause");
	system("cls");
}


//查找员工信息（5）
void WorkerManage::findWorker()
{
	if (this->isFileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		int index = 1;
		while (index)
		{
			int input = 0;
			cout << "请选择你要以那种方式查找员工:1->工号,2->姓名：";
			cin >> input;
			if (input == 1)
			{
				int id = 0;
				cout << "请输入你要查找的工号:";
				cin >> id;
				int ret = this->IsExistInt(id);
				if (ret != -1)
				{
					this->EmpArray[ret]->showInfo();
				}
				else
				{
					cout << "查无此人" << endl;
				}
				index = 0;
			}
			else if (input == 2)
			{
				string name;
				cout << "请输入你要查找的姓名:";
				cin >> name;
				int ret = this->IsExistName(name);
				if (ret != -1)
				{
					this->EmpArray[ret]->showInfo();
				}
				else
				{
					cout << "查无此人" << endl;
				}
				index = 0;
			}
			else
			{
				cout << "你的输入有误，请输入1和2之间的数字" << endl;
			}
		}
	}

	system("pause");
	system("cls");
}


//清空文档
void WorkerManage::clearFile()
{
	if (this->isFileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		while (true)
		{
			int choice = 0;
			cout << "你确定要清空所有文档记录吗? 1->是，2->否，请选择：";
			cin >> choice;
			if (choice == 1)
			{
				this->EmpCount = 0;
				cout << "清空成功" << endl;
				break;
			}
			else if (choice == 2)
			{
				cout << "取消清空" << endl;
				break;
			}
			else
			{
				cout << "选择错误请重新选择,请选择1和2之间的数字" << endl;
			}
		}

		save();
	}

	system("pause");
	system("cls");
}

//按照工号排序（6）
void WorkerManage::bubbleWorker()
{
	if (this->isFileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0;i < this->EmpCount;i++)
		{
			for (int j = 0;j < this->EmpCount - i - 1;j++)
			{
				int Max = this->EmpArray[j]->Id;
				if (this->EmpArray[j + 1]->Id < Max)
				{
					Max = this->EmpArray[j + 1]->Id;
					Worker* temp = this->EmpArray[j];
					this->EmpArray[j] = this->EmpArray[j + 1];
					this->EmpArray[j + 1] = temp;
				}
			}
			save();
		}
		cout << "排序成功!" << endl;
	}

	system("pause");
	system("cls");
}

//退出系统（0）
void WorkerManage::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}