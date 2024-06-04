#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

class Maker1
{
public:
	Maker1(int id, std::string name) :id(id), name(name) {}

	void printMes()
	{
		std::cout << "id = " << id << "，name = " << name << std::endl;
	}

	~Maker1()
	{
		// std::cout << "Maker1析构函数" << std::endl;
	}
private:
	int id;
	std::string name;
};

// 智能指针
class Maker1SmartPointer
{
public:
	Maker1SmartPointer(Maker1*& pM) :pM(pM) {}

	// 1、->运算符重载
	// 因为我们调用方式是"xxx(指针)->"，所以说没有参数，这里返回一个Maker1指针对象pM是因为
	// 我们本质上也是用m指针去调用其本身的成员，也就是说"sp->"这个操作是得到一个指针pM，但是
	// 为什么我们直接使用sP->xxx就可以调用成员，"sP->"表示m指针的话那应该是(sP->)->xxx才对，其实
	// 是编译器进行了优化，直接sP->xxx即可访问m指针的对象
	Maker1* operator->()
	{
		return this->pM;
	}

	// 2、*运算符重载
	// 返回的是Maker1的引用，因为我们的需求就是通过智能指针对访问pM指针成员，可以通过指针对象sP
	// 先获取Maker1对象m(即*pM)，然后通过m去访问对象m的成员，因为我们需要返回的是Maker1引用，即是
	// 返回pM对象本身，这里同样也做了优化，按照这个函数来看的话，我们调用方式应该是(sP*).printMes()
	// 但是我们指针的调用方式是(*sP).printMes()，所以编译器也做了优化
	Maker1& operator*()
	{
		return *(this->pM);
	}


	~Maker1SmartPointer()
	{
		// std::cout << "Maker1SmartPointer析构函数" << std::endl;
		if (this->pM != nullptr)
		{
			delete this->pM; // 运行到这行时，就会调用Maker1的析构函数
			this->pM = nullptr;
		}
	}
private:
	Maker1* pM;
};





void test01()
{
	// 0、问题：
	// 如果我们使用动态申请空间创建对象的话，不使用delete释放掉是不会释放空间的
	// 但是手动释放的话可能会忘记，所以我们需要写一个智能指针帮我们释放这个空间
	Maker1* pM = new Maker1(1, "张三");
	
	// 1、提前创建智能指针对象，然后将pM指针作为参数传入即可，当该函数结束后即会释放智能指针对象
	// 从而会释放pM指针对象，这样就不会有遗忘导致内存泄漏
	Maker1SmartPointer sP(pM);

	// 那智能指针只有这个功能就太单薄了，如果想让它多一点功能，直接当pM指针对象来用那就很方便
	// 接下来重载->运算符和*运算符

	// 2、->运算符重载
	// 我们知道"sP->"其实得到的是指针，正常来说应该是"(sP->)->printMes()"才对，因为编译器进行了
	// 优化，所以只需要"sP->printMes()"即可
	sP->printMes();

	// 3、*运算符重载
	// 这里我们也发现一个问题，就是对于*运算来说，是在对象sP前面的，但是我们知道在*运算符函数
	// 中没有参数，它只是通过自己本身去调用此函数，正常来说应该是这样写的"(sP*).printMes()"，因为
	// 调用的对象在前面，所以说这里也是编译器进行了优化
	(*sP).printMes();
}


int main()
{
	test01();

	return 0;
}
