#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	多态的实现原理：

		1、首先编译器就会对类进行检查，如果发现有虚函数(virtual)，编译器就会创建一张表("虚函数表")，
	表里存放着所有虚函数的入口地址；
		
		2、其次编译器也会在类对象中安插了一个"虚函数表指针"，这个指针指向本类的虚函数表，但是
	虚函数表是不属于类本身的，但是"虚函数表指针"则是属于类的，也就是这个指针是占用类的大小的；

	下面是无继承的情况
	只有speak成员函数时的结构图：
	class Animal    size(4):
			+---
	 0      | {vfptr}
			+---

	Animal::$vftable@:
			| &Animal_meta
			|  0
	 0      | &Animal::speak

	Animal::speak this adjustor: 0


	有speak和run成员函数的结构图：
	class Animal    size(4):
			+---
	 0      | {vfptr}
			+---

	Animal::$vftable@:
			| &Animal_meta
			|  0
	 0      | &Animal::speak
	 1      | &Animal::run

	Animal::speak this adjustor: 0
	Animal::run this adjustor: 0

*/

/*
	下面是有继承的情况
	1、当Dog类继承了Animal类之后，未重载Animal类的成员函数后的结构图：

	class Dog       size(4):
			+---
	 0      | +--- (base class Animal)
	 0      | | {vfptr}
			| +---
			+---

	Dog::$vftable@:
			| &Dog_meta
			|  0
	 0      | &Animal::speak
	 1      | &Animal::run
	 2      | &Dog::eat

	Dog::eat this adjustor: 0



	2、当Dog类继承了Animal类之后，重载Animal类的成员函数后的结构图：

	class Dog       size(4):
			+---
	 0      | +--- (base class Animal)
	 0      | | {vfptr}
			| +---
			+---

	Dog::$vftable@:
			| &Dog_meta
			|  0
	 0      | &Dog::speak
	 1      | &Dog::run
	 2      | &Dog::eat

	Dog::speak this adjustor: 0
	Dog::run this adjustor: 0
	Dog::eat this adjustor: 0

	注：
	1、当Dog继承Animal后，也会把Animal的"虚函数表指针"继承下来，并且这个"虚函数表指针"还指向原来
	的Animal的虚函数表。这里需要注意，就是Dog继承Animal之后，Dog类自身也会有一个虚函数表，并且包含了
	Animal类中的所有虚函数的入口地址，如果Dog类也有虚函数的话，也会加入到Dog类自己的虚函数表里面，
	并且Animal类的虚函数表和Dog的虚函数表是不一样的，这个是显然的，因为Dog有可能是会加入自己类中的
	虚函数入口地址，那就是说此时Dog类的虚函数表的地址和Animal虚函数表的地址不相同，那编译器为了初始
	化从父类继承过来的虚函数表指针，编译器在我们的所有"构造函数"中添加了初始化虚函数表指针的代码，
	让从父类继承过来的虚函数表指针指向子类自己的虚函数表；

	2、当编译器发现子类重写了父类的虚函数，那么子类重写的函数的入口地址就会覆盖掉虚函数表对应的
	父类的函数入口地址，由1图和2图可以看出来，由"&Animal::speak"改成"&Dog::speak"，由"&Animal::run"
	改成"&Dog::run"；

	3、在满足上面条件后，假设有"Animal *an = new Dog; an->speak();"编译器检测到了通过父类Animal去
	调用speak函数时，编译器会根据an指针的指向的内存空间中的虚函数表指针里面找到speak函数，我们知道
	an指针虽然是Animal类型，但它是指向Dog类型的，那么本质上就是指向了Dog类型的空间，那就会去Dog内存
	使用Dog类的虚函数表指针去找speak函数，那么最终我们输出的就是Dog类的speak函数了(因为在第2部就已
	将speak函数入口地址改成子类Dog的speak函数的入口地址了)；

	4、还需要注意就是，其实Dog类继承Animal类之后，Dog类首先是把Animal类的"虚函数表指针"和"虚函数表"
	都拷贝一份，也就是说是和Animal类的"虚函数表指针"和"虚函数表"内容一模一样的，但是地址不一样，也
	就是说"虚函数表指针"和"虚函数表"本身的地址是不一样的，但是"虚函数表指针"的值还是指向原来Animal
	类的"虚函数表"，所以才有上面的"第1步"，在所有构造函数中都加上初始化虚函数表指针的代码，并且在
	此时如果Dog类里面还有自己自带的虚函数，也会将函数入口地址加入到虚函数表当中；

*/

class Animal
{
public:
	virtual void speak()
	{
		std::cout << "Animal Speak" << std::endl;
	}

	virtual void run()
	{
		std::cout << "Animal run" << std::endl;
	}
};

class Dog :public Animal
{
public:
	virtual void speak()
	{
		std::cout << "Dog speak" << std::endl;
	}

	virtual void run()
	{
		std::cout << "Dog run" << std::endl;
	}

	virtual void eat()
	{
		std::cout << "Dog eat" << std::endl;
	}
};

// 1、验证一下"虚函数表指针"是不是属于类的
void test01()
{
	// 我们知道，成员函数是不占用类的大小的，所以说如果是没有算"虚函数指针"的话算是空类结果应该是1，
	// 但是结果是4，这就证明了"虚函数表指针"是占用类的内存大小的
	std::cout << "sizeof(Animal) = " << sizeof Animal << std::endl;

	// 多态的实现
	Animal* an = nullptr;
	an = new Dog;
	an->speak();
}


int main()
{
	test01();

	return 0;
}
