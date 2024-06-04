#ifndef __MYFUNCTION_H__
#define __MYFUNCTION_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Student
{
public:
	Student();
	Student(std::string name, double myScore);
	void setName(std::string name);
	void setMyScore(double myScore);
	std::string& getName();
	double getMyScore();
private:
	std::string name;
	double myScore;
};

void createStudent(std::vector<Student>& vStu);
void giveScore(std::vector<Student>& vStu);
void sortScore(std::vector<Student>& vStu);
void printScore(std::vector<Student>& vStu);

#endif
