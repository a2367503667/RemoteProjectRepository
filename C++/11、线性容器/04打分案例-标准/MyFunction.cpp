#include "MyFunction.h"

// 学生信息
Student::Student() {}
Student::Student(std::string name, double myScore) :name(name), myScore(myScore) {}
void Student::setName(std::string name) { this->name = name; }
void Student::setMyScore(double myScore) { this->myScore = myScore; }
std::string& Student::getName() { return this->name; }
double Student::getMyScore() { return this->myScore; }

// 1、创建学生
void createStudent(std::vector<Student>& vStu)
{
	vStu.reserve(5);
	char ch = 'A';
	std::string str = "student";
	for (int i = 0; i < 5; ++i)
	{
		std::string temp;
		temp = str + ch;
		vStu.push_back(Student(temp, 0));
		++ch;
	}
}

// 2、评委给学生打分
bool compareScore(double& s1, double& s2) { return s1 > s2; }
void giveScore(std::vector<Student>& vStu)
{
	srand((unsigned int)time(nullptr));
	for (std::vector<Student>::iterator i = vStu.begin(); i != vStu.end(); ++i)
	{
		std::deque<double> d;
		for (int j = 0; j < 10; ++j)
		{
			double score =  rand() % 75 + 26;
			d.push_back(score);
		}
		std::sort(d.begin(), d.end(), compareScore);
		d.pop_back();
		d.pop_front();
		double score = 0;
		for (std::deque<double>::iterator k = d.begin(); k != d.end(); ++k)
		{
			score += (*k);
		}
		i->setMyScore(score / d.size());
	}

}

// 3、排名
// 排名规则
bool compareStudent(Student& s1, Student& s2) { return s1.getMyScore() > s2.getMyScore(); }

void sortScore(std::vector<Student>& vStu)
{
	std::sort(vStu.begin(), vStu.end(), compareStudent);
}

// 4、打印学生成绩
void printScore(std::vector<Student>& vStu)
{
	for (std::vector<Student>::iterator i = vStu.begin(); i != vStu.end(); ++i)
	{
		std::cout << "姓名：" << i->getName() << '\t' << "分数：" << i->getMyScore() << std::endl;
	}
}
