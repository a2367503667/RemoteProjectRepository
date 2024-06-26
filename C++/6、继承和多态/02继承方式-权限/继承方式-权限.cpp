#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	注：保护权限(protected)是指在子类中以子类的身份去访问父类成员，必须是强调子类中
	    因为在子类外是没办法使用的，不管以什么方式(public、protected和private)继承父类都一样
		
		
		就好比如：
		Son1继承Father，b是Father的保护成员，Son1可以在类内访问b，也就是说可以对b进行赋值或
	者一系列操作，或者在类内创建一个Son1对象s，我们都可以去访问b这个成员，但是如果我们不是用
	Son1的身份去访问b成员是会出错的，假设我们在Son1中创建一个Father对象f，用f是访问不了b成员的
	而且我们用Son2或Son3创建的对象也不能在Son1中访问b成员，这也就说明了不管怎么样，保护成员一定
	要以子类本身的身份去访问才会有效，当然，我们在子类外去访问保护成员肯定是无法访问的
	
	还有一点需要注意的，继承后成员的权限是要遵循一个先后顺序的：
	1、首先我们先看父类Father中的成员权限
	2、其次再看我们子类Son1继承父类Father的方式(是public、protected还是private)；
	3、最后再看我们子类中设置的权限

	而这个得出来的权限，是在类外访问的权限

*/

class Father
{
public:
	int a;
protected:
	int b;
private:
	int c;
};

// 1、子类公继承父类
class Son1 :public Father
{
public:
	void func()
	{
		// 子类公开继承父类，可以在子类中能访问父类的公有成员
		a = 10;

		// 子类公开继承父类，可以在子类中以子类的身份访问父类的保护成员
		b = 20;

		// err 子类公开继承父类，不能访问父类的私有成员
		// c = 30;
	}

	void func01()
	{
		// 在Son1内，我们可以以Son1本身去访问b成员
		Son1 s;
		s.b = 100;
		std::cout << "s.b = " << s.b << std::endl;
	}

};

void test01()
{
	Son1 s1;
	
	// 1、子类公有继承父类，在类外可以用子类对象访问父类公有成员(成员在子类是公有权限)
	s1.a;

	// 2、子类公有继承父类，在类外不可以用子类对象访问父类保护成员(成员在子类是保护权限)
	// s1.b; // err

	// 3、子类公有继承父类，在类外不可以用子类对象访问父类私有成员(成员在子类时私有权限)

}

// 2、子类保护继承父类
class Son2 :protected Father
{
public:

	void func()
	{
		// 子类保护继承父类，可以在子类中能访问父类的公有成员
		a = 10;

		// 子类保护继承父类，可以在子类中以子类的身份访问父类的保护成员
		b = 20;

		// err 子类保护继承父类，不能访问父类的私有成员
		// c = 30;
	}
	void func01()
	{
		// 在Son2内，我们可以以Son2本身去访问b成员
		Son2 s;
		s.b = 100;
		std::cout << "s.b = " << s.b << std::endl;
	}
};

void test02()
{
	Son1 s2;

	// 1、子类保护继承父类，在类外不可以用子类对象访问父类公有成员(成员在子类是保护权限)
	// s1.a;

	// 2、子类保护继承父类，在类外不可以用子类对象访问父类保护成员(成员在子类是保护权限)
	// s1.b; // err

	// 3、子类保护继承父类，在类外不可以用子类对象访问父类私有成员(成员在子类时私有权限)

}

// 3、子类私有继承父类
class Son3 :private Father
{
public:

	void func()
	{
		// 子类私有继承父类，可以在子类中能访问父类的公有成员
		a = 10;

		// 子类私有继承父类，可以在子类中以子类的身份访问父类的保护成员
		b = 20;

		// err 子类私有继承父类，不能访问父类的私有成员
		// c = 30;
	}
	void func01()
	{
		// 在Son3内，我们可以以Son3本身去访问b成员
		Son3 s;
		s.b = 100;
		std::cout << "s.b = " << s.b << std::endl;
	}
};
void test03()
{
	Son1 s3;

	// 1、子类私有继承父类，在类外不可以用子类对象访问父类公有成员(成员在子类是私有权限)
	// s1.a;

	// 2、子类私有继承父类，在类外不可以用子类对象访问父类保护成员(成员在子类是私有权限)
	// s1.b; // err

	// 3、子类私有继承父类，在类外不可以用子类对象访问父类私有成员(成员在子类时私有权限)

}

int main()
{

	return 0;
}
