#ifndef __MYSTRING_H__
#define __MYSTRING_H__
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

class MyString
{
	// 重载"<<"和">>"，并添加友元
	friend std::ostream& operator<<(std::ostream& out, MyString& str);
	friend std::istream& operator>>(std::istream& in, MyString& str);
public:
	// 1、无参构造
	MyString();
	
	// 2、有参构造
	MyString(int n);

	// 3、有参构造(参1：字符，参2：字符个数)
	MyString(char ch, int n);

	// 4、有参构造(参：const char*类型字符串)
	MyString(const char* str);

	// 5、有参构造(参：string对象字符串)
	MyString(std::string str);

	// 6、拷贝构造
	MyString(const MyString& str);

	// 7、赋值运算符函数(s1 = s2)
	MyString& operator=(const MyString& str);

	// 8、赋值运算符函数(s1 = "hello")
	MyString& operator=(const char* str);

	// 9、赋值运算符函数(s1 = str(string类))
	MyString& operator=(std::string str);

	// 10、可加操作"+"：s3 = s1 + s2;
	MyString operator+(const MyString& str);

	// 11、可加操作"+"：s3 = s2 + "hello";
	MyString operator+(const char* str);

	// 12、可加操作"+"：s3 = s3 + str(string类)
	MyString operator+(std::string str);

	// 13、可加操作"+="：s2 += s1;
	MyString& operator+=(const MyString& str);

	// 14、可加操作"+="：s2 += "hello"
	MyString& operator+=(const char* str);

	// 15、可加操作"+="：s2 += str(string类)
	MyString& operator+=(std::string str);

	// 16、重载[]
	char& operator[](int index);

private:

	// 17、获取字符串的字符个数(计算const char*)
	int getSize(const char* str);

	// 18、获取字符串的字符个数(计算std::string)
	int getSize(std::string str);

	// 19、获取当前对象的字符串的字符个数
	int getSize();

public:
	// 20、获取MyString对象字符串的字符个数
	int getSize(const MyString& str);

	// 21、析构函数
	~MyString();

private:
	char* str; // 字符串
	int mSize; // 字符串元素个数
};




#endif
