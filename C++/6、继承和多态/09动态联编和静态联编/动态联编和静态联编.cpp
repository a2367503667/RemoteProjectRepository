#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*
	什么是静态联编？什么是动态联编？

	1、所谓的静态联编就是编译器根据函数调用的对象类型，在编译阶段就确定了成员函数的调用地址，也
	   好比如：我们通过Animal类实例化对象a1，用a1去访问成员函数AnimalSpeak()，在编译的时候就已
	   经确定好成员函数AnimalSpeak()的调用地址了，就是在运行后，就会直接调用AnimalSpeak成员函数；
	   (静态联编也称"早绑定方式")

	   注：
	       对于C语言来说，所有的函数都是这样，在编译过程中所有的函数都是静态联编，也就是所有的
	   函数在(编译时)运行之前都确定好了调用地址，即在运行的时候就可以直接调用，这也就是为什么C
	   语言运行速度快的原因(因为在运行时再分配内存(地址)的话，就会消耗运行时间，也就会减低运行
	   速度，如果提前确定好调用地址的话，我们运行的时候直接根据已经确定好的调用地址直接去访问函
	   数就会比较快)

	2、所谓动态联编其实就是在运行阶段才确定调用函数的地址，不提确定好函数的调用地址，也就是在运
	   行阶段再去确定需要调用哪个函数，动态联编也称为"晚绑定方式"，这时候我们就需要引入虚函数，也
	   是在你需要"晚绑定"的那个函数前面加上virtual关键字即可成为虚函数，这个函数就会在运行时才会
	   确定好调用地址。(虚函数就是在"普通成员变量"前面加上virtual关键字，该函数就会变成虚函数，告
	   诉编译器这个函数需要晚绑定。)

	   q1：那动态联编有什么用呢？既然静态编译速度快，为什么还需要用动态编译呢？

	   场景：
	       假设我们有一个项目已经上线了，但是用户反映我们这个项目缺少了一些功能，就好比如游戏
	   中的角色少了一个技能，需要我们添加上去，但是有个问题，我们不能去改动原来的代码，因为改动
	   原来的代码可能会导致原来的代码出问题，出现一些bug就会变得越来越复杂，那我们可以重新写一个
	   新的newClass类，然后将当前这个newClass类继承原来的Game游戏类，如果原来的Game游戏类的成员
	   函数是动态联编的，那我们添加上去的功能，就会在运行时分配内存(地址)，然后就能够运行我们新
	   添加上去的newClass的功能了，这也就做到了我们不改动原来的代码基础上，增添一些新的功能，这也
	   就是为什么有时候我们需要用到动态联编的原因。

	   总的来说，就是动态编译可以晚绑定函数的调用地址，这样可以在不修改原来项目的基础上进行项目
	   的扩充

*/

class Animal
{
public:
	// 在这个函数前面加上virtual关键字，代表这个函数在编译过程中是进行动态编译的
	// 这样就会晚绑定
	virtual void AnimalSpeak()
	{
		std::cout << "Animal Speak" << std::endl;
	}
private:

};

class Dog :public Animal
{
public:
	void AnimalSpeak()
	{
		std::cout << "Dog Speak" << std::endl;
	}
private:

};

class Tortoise :public Animal
{
public:
	void AnimalSpeak()
	{
		std::cout << "Tortoise Climp" << std::endl;
	}
private:

};

class Cat :public Animal
{
public:
	void AnimalSpeak()
	{
		std::cout << "Cat Sleep" << std::endl;
	}
private:

};

// 1、静态联编
void test01()
{
	Animal a1;

	// 这里是在编译过程中，就已经确定了a1是一定调用Animal中的成员函数AnimalSpeak了，也就是说
	// 在运行时，我们可以直接根据a1对象确定好的AnimalSpeak函数地址，直接访问AnimalSpeak函数
	a1.AnimalSpeak();
}

// 这个是用来测试静态联编和动态联编的函数
/*
	注：
	1、animalBehaviol(Animal &an)这个函数是静态联编的，不要搞混淆，动态联编是对于虚函数来
	   说的，也就是说，我们运行后，我们才会去检查调用AnimalSpeak()函数的对象an是什么类型，然后
	   根据这个an对象的类型再去绑定对应的成员函数地址，也就是说，虚函数的调用对象an是有类型检测
	   机制的，这个an不一定是Animal类，有可能是继承了Animal类的子类，如果an是继承了Animal类的子类
	   的话，会继续检测子类中有没有AnimalSpeak()函数，如果有则绑定这个函数，没有则就输出Animal中
	   的AnimalSpeak()函数；
	
	2、为什么允许子类到父类的强制类型转换？
	   因为编译器认为是安全的，因为子类的内存范围包含父类内存范围和子类自身特有的内存范围，而
	   当我们将子类的范围缩小到父类的范围(即子类转成父类)时，这个是允许的，这种现象叫做"向上转型"
	   但是如果是父类转子类的话，这个是危险的，因为父类的范围更小，子类的范围更大，如果用父类原
	   来的内存范围去访问子类的内存范围，有可能会出现非法访问的情况出现，因此这个是不允许的，这种
	   现象称为"向下转型"。

*/
void animalBehaviol(Animal &an) // Animal &an = dog;
{
	an.AnimalSpeak();
}

// 2、动态联编
void test02()
{
	/* 
			这下面的三个都继承了Animal类，下面三个动物就相当于扩展出来三个功能，如果Animal类中
		成员函数都是动态联编函数的话，在运行后才会根据传入animalBehaviol函数的参数是什么类，来对
		相应类中的函数进行绑定(假如我们编译器检测到是Dog类，那就在对应的位置绑定Dog的成员函数)，最
		终就会显示不同的结果，也就是我们对同一个业务进行扩展的时候，我们只需要另外添加新的类，去
		继承原来的业务即可，我们就不需要更改原来业务的代码，提高了代码的可扩展性。

		下面代码的执行结果为：

		Dog Speak
		Cat Sleep
		Tortoise Climp

		那就说明了animalBehaviol函数中的an对象的AnimalSpeak()函数是晚绑定的，在编译到animalBehaviol
		这个函数的参数时，检测到类型后，才会根据类型去绑定an对象的AnimalSpeak()函数，因此才会出现
		不同的结果。
	*/
	Dog d;
	animalBehaviol(d);

	Cat c;
	animalBehaviol(c);

	Tortoise t;
	animalBehaviol(t);
}




int main(int argc, char* argv[])
{
	// test01();
	test02();

	return 0;
}
