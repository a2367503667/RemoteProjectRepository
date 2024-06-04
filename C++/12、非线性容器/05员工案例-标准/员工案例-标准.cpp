#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>
using namespace std;

#define SALE_DEPARTMENT 1 // 销售部
#define DEVELOP_DEPARTMENT 2 // 开发部
#define FINANCIAL_DEPARTMENT 3 // 财务部
#define MANAGE_DEPARTMENT 4 // 管理部

template<typename T>
void printWorker(T& wArr)
{
	typename T::iterator begin = wArr.begin();
	typename T::iterator end = wArr.end();

	while (begin != end)
	{
		cout << "name: " << begin->getName() << ", age: " << begin->getAge() << ", salary: " << begin->getSalary() << endl;
		++begin;
	}
}

template<typename T>
void printDepartment(T& wArr, int department)
{
	typename T::iterator begin = wArr.find(department);
	int count = wArr.count(department);

	for (int i = 0; i < count; ++i, ++begin)
	{
		cout << "name: " << (begin->second).getName() << ", age: " << (begin->second).getAge() << ", salary: " << (begin->second).getSalary() << endl;
	}
}


class Worker
{
public:
	Worker() :name(""), age(0), salary(0) {}
	Worker(string name, int age, int salary) :name(name), age(age), salary(salary) {}

	string getName()
	{
		return this->name;
	}

	int getAge()
	{
		return this->age;
	}

	int getSalary()
	{
		return this->salary;
	}

private:
	string name;
	int age;
	int salary; // 薪资
};

void createWorker(vector<Worker>& vworker, int wNums)
{
	string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	for (int i = 0; i < wNums; ++i)
	{
		string name = "员工";
		int age = rand() % 16 + 20;
		int salary = rand() % 20001 + 10000;
		int ch = str[rand() % 26];

		vector<Worker>::iterator begin = vworker.begin();
		vector<Worker>::iterator end = vworker.end();
		vector<Worker>::iterator it = begin;
		while (begin != end)
		{
			if ((*begin).getName().substr(strlen(name.c_str())).at(0) == ch)
			{
				ch = str[rand() % 26];
				begin = it;
			}
			else
			{
				++begin;
			}
		}
		name.append(1, ch);

		Worker w(name, age, salary);
		vworker.push_back(w);
	}
}

void assignDepartment(vector<Worker>& vworker, multimap<int, Worker>& mworker)
{
	vector<Worker>::iterator begin = vworker.begin();
	vector<Worker>::iterator end = vworker.end();

	while (begin != end)
	{
		int department = rand() % 4 + 1;
		mworker.insert(pair<int, Worker>(department, *begin));
		++begin;
	}
}

void printMsg(multimap<int, Worker>& mworker)
{
	cout << "销售部人员如下：" << endl;
	printDepartment<multimap<int, Worker>>(mworker, SALE_DEPARTMENT);

	cout << "-------------------------------------" << endl;

	cout << "开发部人员如下：" << endl;
	printDepartment<multimap<int, Worker>>(mworker, DEVELOP_DEPARTMENT);

	cout << "-------------------------------------" << endl;

	cout << "财务部人员如下：" << endl;
	printDepartment<multimap<int, Worker>>(mworker, FINANCIAL_DEPARTMENT);
	
	cout << "-------------------------------------" << endl;

	cout << "管理部人员如下：" << endl;
	printDepartment<multimap<int, Worker>>(mworker, MANAGE_DEPARTMENT);
}

void test01()
{
	srand((unsigned int)time(nullptr));

	vector<Worker> vworker; // 存储员工
	multimap<int, Worker> mworker; // 分配员工到相应部门
	int wNums = 15; // 员工人数

	// 1、创建员工
	createWorker(vworker, wNums);

	// 2、分配部门
	assignDepartment(vworker, mworker);

	// 3、输出员工信息
	printMsg(mworker);
}

int main(int argc, char* argv[])
{
	test01();

	return 0;
}
