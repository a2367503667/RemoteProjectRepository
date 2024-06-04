#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// 用const修饰成员函数时，const就会修饰this指针指向的内存区域
// 使得成员函数体内不能修改本类中的任何普通成员变量
// 也就是说把this指针改成，const Maker* const this，此时这个成员函数内的this指针就是一个常量指针常量
// 因为原来的this就是一个Maker* const this(指针常量)
class Maker1
{
public:
	Maker1(int mId, int mAge)
	{
		this->mId = mId;
		this->mAge = mAge;
	}

	// 1、在成员函数后面加上const，那就会将this指针变成常量指针常量，即const Maker* const this;
	// 这个就是常函数，只能访问成员变量，不能修改
	void printMaker1()const
	{
		// 2、不能修改，只能访问
		// mId = 100; err
		// this->mId = 100; err
		std::cout << "mAge = " << mAge << std::endl;

		// 3、但是有时候，我们确实需要修改部分成员变量的值，那怎么办？
		// 这时候我们引入一个关键字mutable，这个关键字是用来修饰普通成员变量的(如：mutable int a;)
		// 就是便于我们在常函数里面修改某个成员变量的值
		score = 100; // 没有报错
		std::cout << "score = " << score << std::endl;

		// 4、常函数可以修改静态成员变量(因为常函数的const本质不是修饰函数本身，而是修饰this指针
		// 也就是说在this是一个指针常量的前提下，将其所对应的空间也设置为不可变，即常量指针常量)
		a = 1000;
	}


private:
	int mId;
	int mAge;
	mutable int score; // 表示在常函数中可以被修改
	static int a; // 静态成员
};
int Maker1::a = 100; // 初始化

/*
拓展：
	对于常函数来说，const不是修饰函数本身，而是修饰this指针，将this指针变成常量指针常量
	即const Maker1 *const this，而在静态成员来说，没有this指针的概念，this指针是用来修饰对
	象的，而静态成员是属于类的，所以即使我们在常函数里面对静态成员进行修改，也不会报
	错，因此，静态成员在常函数中是允许修改。(this指针本身就是一个指针常量)
*/
void test01()
{
	Maker1 m1(1, 21);
	m1.printMaker1();

}


int main()
{
	test01();

	return 0;
}
