#include "MyFunction.h"


int main()
{
	// 储存学生信息
	std::vector<Student> vStu;

	// 1、创建学生
	createStudent(vStu);

	// 2、评委给学生打分
	giveScore(vStu);

	// 3、排名
	sortScore(vStu);

	// 4、打印
	printScore(vStu);

	return 0;
}
