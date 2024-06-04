#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

// 这个类就是为了完成多态，在一个函数中调用不同的子类，使用不同的子类成员函数
class Animal
{
public:
	virtual void speak() = 0;
	virtual void getOnlyObject(Animal*& an) = 0;
};

class Dog :public Animal
{
public:
	Dog(std::string name) :name(name) {}
	virtual void speak()
	{
		std::cout << this->name << "正在汪汪叫" << std::endl;
	}
	virtual void getOnlyObject(Animal*& an)
	{
		std::string name = this->name;
		an = new Dog(this->name);
	}
private:
	std::string name;
};

class Duck :public Animal
{
public:
	Duck(std::string name) :name(name) {}
	virtual void speak()
	{
		std::cout << this->name << "正在嘎嘎叫" << std::endl;
	}
	virtual void getOnlyObject(Animal*& an)
	{
		std::string name = this->name;
		an = new Duck(this->name);
	}
private:
	std::string name;
};

class Tiger :public Animal
{
public:
	Tiger(std::string name) :name(name) {}
	virtual void speak()
	{
		std::cout << this->name << "正在咆哮" << std::endl;
	}
	virtual void getOnlyObject(Animal*& an)
	{
		std::string name = this->name;
		an = new Tiger(this->name);
	}
private:
	std::string name;
};

class Cat :public Animal
{
public:
	Cat(std::string name) :name(name) {}
	virtual void speak()
	{
		std::cout << this->name << "正在喵喵叫" << std::endl;
	}
	virtual void getOnlyObject(Animal*& an)
	{
		std::string name = this->name;
		an = new Cat(this->name);
	}
private:
	std::string name;
};

class MyZoo
{
public:
	MyZoo(int mCapacity)
	{
		this->mSize = 0;
		this->mCapacity = mCapacity;
		this->an = new Animal * [this->mCapacity];
		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->an[i] = nullptr;
		}
	}

	// 拷贝构造(解决浅拷贝问题)
	MyZoo& operator=(const MyZoo& mz)
	{
		if (this->an != nullptr)
		{
			delete[] this->an;
			this->an = nullptr;
		}

		this->mSize = mz.mSize;
		this->mCapacity = mz.mCapacity;
		this->an = new Animal * [this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->an[i] = nullptr;
		}

		for (int i = 0; i < mz.mCapacity; ++i)
		{
			if (mz.an[i] != nullptr)
			{
				mz.an[i]->getOnlyObject(this->an[i]);
			}
		}

		return *this;
	}

	// 赋值函数(解决浅拷贝问题)
	MyZoo(const MyZoo& mz)
	{
		if (this == nullptr)
		{
			std::cout << "空指针异常" << std::endl;
			return;
		}
		this->mSize = mz.mSize;
		this->mCapacity = mz.mCapacity;
		this->an = new Animal*[this->mCapacity];

		for (int i = 0; i < this->mCapacity; ++i)
		{
			this->an[i] = nullptr;
		}

		for (int i = 0; i < mz.mCapacity; ++i)
		{
			if (mz.an[i] != nullptr)
			{
				mz.an[i]->getOnlyObject(this->an[i]);
			}
		}
	}

	void addAnimal(Animal* a)
	{
		if (this->mCapacity == this->mSize)
		{
			return;
		}
		this->an[this->mSize++] = a;
	}

	void printAnimals()
	{
		for (int i = 0; i < this->mSize; ++i)
		{
			this->an[i]->speak();
		}
	}

	~MyZoo()
	{
		if (this->an != nullptr)
		{
			for (int i = 0; i < this->mSize; ++i)
			{
				if (this->an[i] != nullptr)
				{
					delete this->an[i];
					this->an[i] = nullptr;
				}
			}
			delete[] this->an;
			this->an = nullptr;
		}
	}

private:
	Animal** an; // 存储动物(每个动物都以指针形式存储)
	int mSize;
	int mCapacity;
};

void test01()
{
	MyZoo* mz = new MyZoo(50);

	mz->addAnimal(new Dog("安培晋三"));
	mz->addAnimal(new Duck("唐老鸭"));
	mz->addAnimal(new Tiger("东北虎"));
	mz->addAnimal(new Cat("咖啡猫"));
	mz->printAnimals();
	delete mz;
	mz = nullptr;
}


int main()
{
	test01();

	return 0;
}
