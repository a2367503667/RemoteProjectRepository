#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

class Participant
{
public:
	Participant() :name(""), age(0), times(0), mScore(nullptr) {}
	Participant(string name, int age, int times) :name(name), age(age), times(times)
	{
		this->mScore = new int[this->times];
		for (int i = 0; i < this->times; ++i)
		{
			this->mScore[i] = 0;
		}
	}
	Participant(const Participant& p) 
	{
		this->name = p.name;
		this->age = p.age;
		this->times = p.times;
		this->mScore = new int[this->times];
		for (int i = 0; i < this->times; ++i)
		{
			this->mScore[i] = p.mScore[i];
		}
	}
	Participant& operator=(const Participant& p)
	{
		if (this->mScore != nullptr)
		{
			delete[] this->mScore;
			this->mScore = nullptr;
		}
		this->age = p.age;
		this->name = p.name;
		this->times = p.times;
		this->mScore = new int[this->times];
		for (int i = 0; i < this->times; ++i)
		{
			this->mScore[i] = p.mScore[i];
		}

		return *this;
	}
	string getName() { return this->name; }
	int getAge() { return this->age; }
	int getMScore(int i) { return this->mScore[i]; }
	void setScore(int i, int score) { this->mScore[i] = score; }
	~Participant() 
	{
		if (this->mScore != nullptr) 
		{
			delete[] this->mScore;
		}
		this->mScore = nullptr;
	}
private:
	string name;
	int age;
	int* mScore;
	int times; // 表示参赛最多只有三轮
};

void CreateParticipant(int nums, vector<int>& v1, map<int, Participant>& mList)
{
	string lastName = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < nums; ++i)
	{
		v1.push_back(i + 100);
		string name = "选手";
		char ch = lastName.at(rand() % 26);
		name.append(1, ch);
		char* buf = new char[128];
		sprintf(buf, "%d", i + 100);
		name.append(buf);
		delete[] buf;
		buf = nullptr;
		mList.insert(make_pair(i + 100, Participant(name, rand() % 5 + 18, 3)));
	}
}

void ParticipantRandom(vector<int>& v1)
{
	// 打乱顺序(即抽签)
	random_shuffle(v1.begin(), v1.end());
}

void StartCompetition(int times, int groupPeople, int comments, vector<int> v1, map<int, Participant>& mList, vector<vector<int>>& vList)
{
	deque<int> scores;
	
	/*
		因为形参是引用类型，而在函数StartCompetition开头的位置会给vList创建一个新的空间，而创建
		一个新的空间，可能会导致vList内存的重新分配，此时v1这个引用就会有可能失效，这样就相当于
		非法访问数据了，因此会报错，所以上面的v1不能使用&传递
	*/
	vList.push_back(vector<int>());

	// 利用关联式容器的特性，筛选出前三名(最大的排前面)
	multimap<int, int, greater<int>> mmap;

	for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it)
	{
		// 打分
		for (int i = 0; i < comments; ++i)
		{
			int sc = rand() % 51 + 50;
			scores.push_back(sc);
		}
		// 排好序
		sort(scores.begin(), scores.end());
		scores.pop_back();
		scores.pop_front();
		int sums = accumulate(scores.begin(), scores.end(), 0);
		int avg = sums / (comments - 2);
		mList[*it].setScore(times - 1, avg);
		scores.clear();

		// 筛选出前三名
		// 每次都将选手加入到mmap容器当中进行筛选(每组最多是groupPeople个人)
		mmap.insert(make_pair(avg, *it));
		if (mmap.size() == groupPeople)
		{
			int outPeople = 3;
			int j = 0;
			for (multimap<int, int, greater<int>>::iterator ssit = mmap.begin(); ssit != mmap.end() && j < outPeople; ++ssit, ++j)
			{
				vList[times - 1].push_back(ssit->second);
			}
			mmap.clear();
		}
	}
}

void printResult(int times, vector<vector<int>>& vList, map<int, Participant>& mList)
{
	cout << "第" << times << "轮晋级选手如下：" << endl;
	for (vector<int>::iterator it = vList[times - 1].begin(); it != vList[times - 1].end(); ++it)
	{
		cout << "name：" << mList[*it].getName() << "，age：" << mList[*it].getAge() << "，score：" << mList[*it].getMScore(times - 1) << endl;
	}
}


void test01()
{
	srand((unsigned int)time(nullptr));

	// 存储选手的编号
	vector<int> v1;

	// 保存选手的信息(使用键值对的方式保存)
	map<int, Participant> mList;

	// 保存第n轮选手的编号
	vector<vector<int>> vList;

	// 选手的个数
	int nums = 24;
	
	// 评委个数
	int comments = 10;

	// 每组有多少个人
	int groupPeople = 6;

	// 1、创建选手
	CreateParticipant(nums, v1, mList);

	/*
		第一轮：
		(1)抽签(所谓的抽签就是打乱参赛选手的顺序)
		(2)比赛
		(3)输出结果
	*/
	ParticipantRandom(v1);
	StartCompetition(1, groupPeople, comments, v1, mList, vList);
	printResult(1, vList, mList);

	/*
		第二轮：
		(1)抽签
		(2)比赛
		(3)输出结果
	*/
	ParticipantRandom(v1);
	StartCompetition(2, groupPeople, comments, vList[0], mList, vList);
	printResult(2, vList, mList);

	/*
		第三轮：
		(1)抽签
		(2)比赛
		(3)输出结果
	*/
	ParticipantRandom(v1);
	StartCompetition(3, groupPeople, comments, vList[1], mList, vList);
	printResult(3, vList, mList);
}



int main(int argc, char* argv[])
{
	test01();


	return 0;
}
