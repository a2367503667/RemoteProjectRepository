#include "MyString.h"

// 1、无参构造
MyString::MyString()
{
	this->mSize = 0;
	this->str = new char[1];
	this->str[0] = 0;
}

// 2、有参构造
MyString::MyString(int n)
{
	this->mSize = n;
	this->str = new char[this->mSize + 1];
	for (int i = 0; i < this->mSize + 1; ++i)
	{
		this->str[i] = 0;
	}
}

// 3、有参构造(参1：字符，参2：字符个数)
MyString::MyString(char ch, int n)
{
	this->mSize = n;
	this->str = new char[n + 1];

	for (int i = 0; i < this->mSize; ++i)
	{
		this->str[i] = ch;
	}
	this->str[this->mSize] = 0;
}

// 4、有参构造(参：const char*类型字符串)
MyString::MyString(const char* str)
{
	int size = getSize(str);
	this->mSize = size;
	this->str = new char[this->mSize + 1];
	for (int i = 0; i < this->mSize; ++i)
	{
		this->str[i] = str[i];
	}
	this->str[this->mSize] = 0;
}

// 5、有参构造(参：string对象字符串)
MyString::MyString(std::string str)
{
	const char* pStr = str.c_str();
	int size = getSize(str); // 也可以写成int size = str.size();

	this->mSize = size;
	this->str = new char[this->mSize + 1];

	for (int i = 0; i < this->mSize; ++i)
	{
		this->str[i] = pStr[i];
	}
	this->str[this->mSize] = 0;
}

// 6、拷贝构造
MyString::MyString(const MyString& str)
{
	if (str.mSize == 0)
	{
		this->mSize = 0;
		this->str = new char[1];
		this->str[this->mSize] = 0;
		return;
	}
	
	this->mSize = str.mSize;
	this->str = new char[this->mSize + 1];
	for (int i = 0; i < this->mSize; ++i)
	{
		this->str[i] = str.str[i];
	}
	this->str[this->mSize] = 0;
}

// 7、赋值运算符函数
MyString& MyString::operator=(const MyString& str)
{
	if (this->str != nullptr)
	{
		delete[] this->str;
		this->str = nullptr;
	}

	this->mSize = str.mSize;
	this->str = new char[this->mSize + 1];
	for (int i = 0; i < this->mSize; ++i)
	{
		this->str[i] = str.str[i];
	}
	this->str[this->mSize] = 0;

	return *this;
}

// 8、赋值运算符函数(s1 = "hello")
MyString& MyString::operator=(const char* str)
{
	if (this->str != nullptr)
	{
		delete[] this->str;
		this->str = nullptr;
	}

	this->mSize = getSize(str);
	this->str = new char[this->mSize + 1];
	for (int i = 0; i < this->mSize; ++i)
	{
		this->str[i] = str[i];
	}
	this->str[this->mSize] = 0;

	return *this;
}

// 9、赋值运算符函数(s1 = str(string类))
MyString& MyString::operator=(std::string str)
{
	if (this->str != nullptr)
	{
		delete[] this->str;
		this->str = nullptr;
	}

	this->mSize = getSize(str);
	this->str = new char[this->mSize + 1];
	for (int i = 0; i < this->mSize; ++i)
	{
		this->str[i] = str[i];
	}
	this->str[this->mSize] = 0;

	return *this;
}

// 10、可加操作"+"：s3 = s1 + s2;
MyString MyString::operator+(const MyString& str)
{
	// 1、先获取当前字符对象长度size1和str对象的长度size2
	int size1 = this->mSize;
	int size2 = getSize(str);
	int size = size1 + size2; // 获取总长度

	MyString temp(size);
	int i = 0;
	while (this->str[i] != 0)
	{
		temp.str[i] = this->str[i];
		++i;
	}

	int j = 0;
	while (str.str[j] != 0)
	{
		temp.str[i + j] = str.str[j];
		++j;
	}
	temp.str[size] = 0;

	return temp;
}

// 11、可加操作"+"：s3 = s2 + "hello";
MyString MyString::operator+(const char* str)
{
	int size1 = this->mSize;
	int size2 = getSize(str);
	int size = size1 + size2; // 获取总长度

	MyString temp(size);
	int i = 0;
	while (this->str[i] != 0)
	{
		temp.str[i] = this->str[i];
		++i;
	}

	int j = 0;
	while (str[j] != 0)
	{
		temp.str[i + j] = str[j];
		++j;
	}
	temp.str[size] = 0;

	return temp;
}

// 12、可加操作"+"：s3 = s3 + str(string类)
MyString MyString::operator+(std::string str)
{
	int size1 = this->mSize;
	int size2 = getSize(str);
	int size = size1 + size2;

	MyString temp(size);
	int i = 0;
	while (this->str[i] != 0)
	{
		temp.str[i] = this->str[i];
		++i;
	}

	int j = 0;
	while (str[j] != 0)
	{
		temp.str[i + j] = str[j];
		++j;
	}
	temp.str[size] = 0;

	return temp;
}

// 13、可加操作"+="：s2 += s1;
MyString& MyString::operator+=(const MyString& str)
{
	MyString temp(*this);
	if (this->str != nullptr)
	{
		delete[] this->str;
		this->str = nullptr;
	}

	int size1 = getSize(temp);
	int size2 = getSize(str);
	int size = size1 + size2;

	this->mSize = size;
	this->str = new char[this->mSize + 1];
	
	int i = 0;
	while (temp[i] != 0)
	{
		this->str[i] = temp[i];
		++i;
	}

	int j = 0;
	while (str.str[j] != 0)
	{
		this->str[i + j] = str.str[j];
		++j;
	}
	this->str[this->mSize] = 0;

	return *this;
}

// 14、可加操作"+="：s2 += "hello"
MyString& MyString::operator+=(const char* str)
{
	MyString temp(*this);
	if (this->str != nullptr)
	{
		delete[] this->str;
		this->str = nullptr;
	}
	
	int size1 = getSize(temp);
	int size2 = getSize(str);
	int size = size1 + size2;

	this->mSize = size;
	this->str = new char[this->mSize + 1];

	int i = 0;
	while (temp[i] != 0)
	{
		this->str[i] = temp[i];
		++i;
	}

	int j = 0;
	while (str[j] != 0)
	{
		this->str[i + j] = str[j];
		++j;
	}
	this->str[this->mSize] = 0;

	return *this;
}

// 15、可加操作"+="：s2 += str(string类)
MyString& MyString::operator+=(std::string str)
{
	MyString temp(*this);
	if (this->str != nullptr)
	{
		delete[] this->str;
		this->str = nullptr;
	}

	int size1 = getSize(temp);
	int size2 = getSize(str);
	int size = size1 + size2;

	this->mSize = size;
	this->str = new char[this->mSize + 1];
	
	int i = 0;
	while (temp[i] != 0)
	{
		this->str[i] = temp[i];
		++i;
	}

	int j = 0;
	while (str[j] != 0)
	{
		this->str[i + j] = str[j];
		++j;
	}
	this->str[this->mSize] = 0;

	return *this;
}

// 16、重载[]
char& MyString::operator[](int index)
{
	return (this->str[index]);
}

// 17、获取字符串的字符个数(计算const char*)
int MyString::getSize(const char* str)
{
	if (str == nullptr)
	{
		return -1; // 这里不处理异常
	}

	int size = 0;
	while (str[size] != 0)
	{
		++size;
	}

	return size;
}

// 18、获取字符串的字符个数(计算std::string)
int MyString::getSize(std::string str)
{
	const char * pStr = (char*)str.c_str();
	if (pStr == nullptr)
	{
		return -1; // 这里不处理异常
	}

	int size = 0;
	while (pStr[size] != 0)
	{
		++size;
	}
	return size;
}

// 19、获取当前对象的字符串的字符个数
int MyString::getSize()
{
	return this->mSize;
}

// 20、获取MyString对象字符串的字符个数
int MyString::getSize(const MyString& str)
{
	return str.mSize;
}

// 21、析构函数
MyString::~MyString()
{
	if (this->str != nullptr)
	{
		delete[] this->str;
		this->str = nullptr;
	}
}

// 重载"<<"运算符
std::ostream& operator<<(std::ostream& out, MyString& str)
{
	out << str.str;
	return out;
}

// 重载">>"运算符
std::istream& operator>>(std::istream& in, MyString& str)
{
	in >> str.str;
	return in;
}
