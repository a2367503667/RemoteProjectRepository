#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <string>

void test01()
{
	pair<int, string> myp1(10, "aaa");
	cout << "myp1.first = " << myp1.first << endl;
	cout << "myp1.second = " << myp1.second << endl;

	cout << "--------------------------" << endl;

	pair<string, int> myp2("bbb", 20);
	cout << "myp2.first = " << myp2.first << endl;
	cout << "myp2.second = " << myp2.second << endl;

}


int main(int argc, char* argv[])
{
	test01();

	return 0;
}
