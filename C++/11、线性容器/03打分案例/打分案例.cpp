#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

/*
	打分案例：有5个学生和10个评委，其中10个评委的分数去掉最高分和最低分，取平均值就是学生的分数
*/

/*
	运行结果：
	请输入10个评委的评分：95 80 83 60 83 76 82 77 79 80 73 76
	请输入10个评委的评分：90 82 85 70 86 81 77 77 81 86 61 78
	请输入10个评委的评分：96 82 85 73 86 86 81 67 83 88 71 80
	请输入10个评委的评分：96 87 86 77 73 75 85 63 89 88 75 88
	请输入10个评委的评分：96 87 90 79 80 75 88 73 91 93 80 87

	第1个学生的平均分：80
	第2个学生的平均分：79.625
	第3个学生的平均分：82.125
	第4个学生的平均分：81.625
	第5个学生的平均分：82.5
*/

void test01()
{
	std::vector<std::vector<double>> v;
	std::vector<double> arg;

	std::vector<double> s1;
	std::vector<double> s2;
	std::vector<double> s3;
	std::vector<double> s4;
	std::vector<double> s5;

	v.push_back(s1);
	v.push_back(s2);
	v.push_back(s3);
	v.push_back(s4);
	v.push_back(s5);

	std::vector<std::vector<double>>::iterator begin = v.begin();
	std::vector<std::vector<double>>::iterator end = v.end();

	double score = 0;

	while (begin != end)
	{
		std::cout << "请输入10个评委的评分：";
		for (int i = 0; i < 10; ++i)
		{
			std::cin >> score;
			(*begin).push_back(score);
		}
		++begin;
	}

	double max = 0;
	double min = 0;
	double sumScore = 0;

	for (std::vector<std::vector<double>>::iterator i = v.begin(); i != v.end(); ++i)
	{
		max = (*(*i).begin());
		min = (*(*i).begin());
		sumScore = 0;
		for (int j = 0; j < 10; ++j)
		{
			if (max <= (*i)[j])
			{
				max = (*i)[j];
			}
			if (min >= (*i)[j])
			{
				min = (*i)[j];
			}
			sumScore += (*i)[j];
		}
		sumScore = sumScore - min - max;
		arg.push_back(sumScore / 8);
	}

	for (int i = 0; i < arg.size(); ++i)
	{
		std::cout << "第" << (i + 1) << "个学生的平均分：" << arg[i] << std::endl;
	}

}


int main()
{
	test01();


	return 0;
}
