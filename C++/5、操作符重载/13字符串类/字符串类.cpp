#include "MyString.h"

// 以下是测试结果，可完美运行
void test01()
{
	MyString s1('a', 20);
	std::cout << "s1 = " << s1 << std::endl;

	MyString s2 = "欢迎使用MyString类";
	std::cout << "s2 = " << s2 << std::endl;

	s1 = s2;
	std::cout << "s1 = " << s1 << std::endl;

	s2 = "hello";
	std::cout << "s2 = " << s2 << std::endl;

	s2[3] = 'p';
	std::cout << "s2 = " << s2 << std::endl;

	s2 += s1;
	std::cout << "s2 = " << s2 << std::endl;

	s2 += "好好学习，天天向上";
	std::cout << "s2 = " << s2 << std::endl;

	std::string str("，张三去上学");

	s2 += str;
	std::cout << "s2 = " << s2 << std::endl;

	MyString s3;

	s3 = s1 + s2;
	std::cout << "s3 = " << s3 << std::endl;

	s3 = s1 + "hello";
	std::cout << "s3 = " << s3 << std::endl;

	s3 = s1 + str;
	std::cout << "s3 = " << s3 << std::endl;
}


int main()
{
	test01();

	return 0;
}
