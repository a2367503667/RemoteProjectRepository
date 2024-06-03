#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

/*
	在C语言中，结构体里不能写函数，那就是说只能在结构体里面写变量
	在结构体外面写函数，那如果函数的参数类型都相同，好比如指针，如果传错了函数
	就会造成不一样的后果，例如：
	struct people{
		char name[32];
	}
	struct animal{
		char name[32];
	}
	void peopleEat(char *name)
	{
		printf("%s在吃人吃的饭\n",name);
	}
	void animalEat(char *name)
	{
		printf("%s在吃动物的饭\n",name);
	}
	如果把人的name传到animalEat()里面，那就会出问题，那就会显示(人的名字)在吃动物的饭
	这很明显就不符合我们所要的结果，因此就提出封装，就是避免误传输的情况发生

	封装：就是把属性(变量)和方法(行为或函数)封装到类内，然后给这些数据赋予权限
	为什么要封装？1、防止乱调用函数和变量，出现错误；2、维护代码更方便

	为什么说维护代码更方便？
	因为像C语言那样不能封装，那些代码就会一大片，让我们看起来很难受，有时候还会出现遗漏的现象
	而且在维护时，还不能很快地找到函数与变量的关系，就像上面那样(要找到人与人吃的东西，这样才算匹配)
	要找到匹配的东西才可以进一步对代码进行维护，如果函数和变量多起来那就很难维护了，花的时间也会很长

	像C++那样可以封装的话，我们就可以以一个类作为单位去维护，一次维护一个类就可以避免遗漏等问题
	而且找到的问题都会出现在某个类中，那就很容易在某个类中解决，同时也不会影响到其他的类，这样维护
	起来就会比较轻松，维护的效率也会大大提高

*/

// 怎么封装？
// 1、把属性和方法放到类中；2、给这些数据给予权限(一般方法是公有权限，属性是私有)
// 注：在类内是没有权限之分的，都可以访问
class Maker
{
public: // 共有权限(类外可以访问公有权限)
	void setId(int id)
	{
		this->id = id;
	}
	void setName(string name)
	{
		this->name = name;
	}
	int getId()
	{
		return id;
	}
	string getName()
	{
		return name;
	}
	void makerPrint()
	{
		cout << "id: " << id << endl << "name: " << name << endl;
	}
	void printA()
	{
		cout << "Maker a = " << a << endl;
	}
private: // 私有权限(类外是不能访问私有权限的)
	int id;
	string name;

protected: // 保护权限(类外不能访问保护权限，但是子类的类内可以访问父类的保护权限成员)
	int a;
};

// 类外不能访问保护权限，但是子类的类内可以访问父类的保护权限成员
// 公有继承
// // 继承的固定格式 class 子类名: (什么继承方式(权限)) 父类名
//    子类:       父类
class Son :public Maker
{
public:
	void func()
	{
		// 这个a是Maker的，继承父类后a可以使用
		// 这个a是从父类复制过来的
		a = 20;
		// id = 1; 私有的用不了
		getId(); // 公有的继承父类后也可以用
	}
	void printA()
	{
		cout << "Son a = " << a << endl;
	}

};

// 验证：虽然Son可以用a，但是Maker的a和Son的a是不一样的
void test02()
{
	// 先创建Maker变量
	Maker m;
	// 在Son中给a赋值，如果Maker的值相应也变成了Son中赋的值，那么就证明Son的a是Maker的a，否则不是
	Son s;
	// 在Son中给a赋值
	s.func();
	// 输出Maker中的a
	m.printA(); // 结果显示：Maker a = -858993460，并不是20，也就说明了Son的a不是Maker中的a
	// 再输出Son的a看一下
	s.printA();  // 结果显示：Son a = 20
}


void test01()
{
	Maker m;
	m.setId(1);
	m.setName("小花");
	m.makerPrint();
}



int main()
{
	// test01();
	test02();

	return 0;
}
