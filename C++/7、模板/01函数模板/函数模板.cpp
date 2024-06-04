#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

/*
	其实模板就是C++中的第二大特性：泛式编程
	有时候我们的函数都是实现同一个功能的，但是只能够对对一种数据类型进行操作，就例
	如：void sortInt(int *arr, int n)和void sortDouble(double *arr, int n)这两个函数都是
	排序函数，但是排的数据类型不一样，一个是int类型，另一个是double类型，但是这里就会有一个问题
	那就是他们只是类型不一样而已，排序的算法都是一样的，这样就会出现代码冗余的情况，所以这时就引入
	"函数模板"，我们只需要对类型增加"泛型特性"也就是可以切换不同类型的话，那就可以很好地解决代码
	冗余的问题(后面的类模板也是为了解决"代码冗余"和"代码的可重用性"问题的)

	模板的书写型式：
	
	1、template<class T>(下面的代码块就可以正常书写，其中T表示泛型类型)

	2、template<typename T>(下面的代码块就可以正常书写，其中T表示泛型类型)

	3、上面两种书写方式都是一模一样的，没有区别，只是我们可以在函数中用typename，在类中用class
	   会比较有可读性，仅此而已。
*/

void swapInt(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

void swapDouble(double& a, double b)
{
	double t = a;
	a = b;
	b = t;
}

// 上面两个交换函数只是类型不一样而已，操作都是一样，此时我们就可以使用函数模板解决这个冗余问题
// 其中T代表泛型的数据类型，不是只能写T，写什么都可以，这个看个人习惯，但是最好跟着要求或需求来写
template<typename T>
void mySwap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}

template<typename T>
void mySwap(T* a, T* b)
{
	T t = *a;
	*a = *b;
	*b = t;
}

template<typename T>
T myAdd(T a, T b)
{
	return a + b;
}


void test01()
{
	// 1、编译器根据实参来自动推导数据类型
	int a = 10;
	int b = 20;
	mySwap(a, b);
	std::cout << "a = " << a << "，b = " << b << std::endl;
	
	char c = 'c';
	//这里需要注意，T只能代表一种类型，这里传参的话既有int类型又有char类型，编译器无法识别
	// 就会进行报错，所以类型需要统一起来
	// mySwap(a, c); // err 数据类型要一致

	// 2、显式的指定参数类型
	// 我们可以用<>显式告诉编译器指定什么类型
	mySwap<int>(a, b);
	std::cout << "a = " << a << "，b = " << b << std::endl;

	// 3、需要注意对于模板的参数是否有引用(或指针)
	// 因为a和b的类型是int，函数模板参数为引用(或指针)，当你指定double时，即为double
	// 引用(或指针)，所以就会出现报错
	// mySwap<double>(a, b); // err
	// mySwap<double>(&a, &b); // err

	// 但是不是引用的情况下，函数模板会帮我们自动强转(强转可能会数据丢失)
	// 但强转不了就会报错，就好比如类和普通类型转换
	myAdd<double>(a, b);

	// 4、不在<>中写类型，可以由编译器自己进行推导类型
	mySwap<>(a, b);
	std::cout << "a = " << a << "，b = " << b << std::endl;

	// 5、对于模板来说，会进行两次编译，一次是在模板本身的地方进行语法的编译(即是template那个地方)
	// 第二个地方是在调用它的地方，将类型传进去后再次编译，检查类型的使用方式是否正确
	// 这种情况会在类模板中存在一个问题(之后会讲)

	/*
		(1)在模板的地方进行第一次编译，如下：
		template<typename T>
		T myAdd(T a, T b)
		{
			return a + b;
		}
	
		(2)在使用模板的地方进行二次编译，如下：
		myAdd<int>(a, b);

		这里编译器会将类型传入，然后再展开编译
		T myAdd(int a, int b)
		{
			return a + b;
		}

	*/

	// 6、有时候我们传进去的数也可以指定编译器帮我们强转，同样的强转不了就会报错
	int a1 = 740;
	double b1 = 3.14;

	// 指定是int类型(编译器会编译会给我们警告)
	myAdd<int>(a1, b1);

}

// 排序函数模板
template<typename T>
void mySort(T* arr, int len)
{
	int minIndex = -1;
	for (int i = 0; i < len - 1; ++i)
	{
		int minIndex = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (arr[minIndex] > arr[j])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			T t = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = t;
		}
	}
}

// 数组打印函数模板
template<typename T>
void printArr(T* arr,int len)
{
	std::cout << "数组数据为：[";
	for (int i = 0; i < len; ++i)
	{
		if (i == len - 1)
		{
			std::cout << arr[i];
		}
		else
		{
			std::cout << arr[i] << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

void test02()
{
	int arr[20] = { 62,45,12,95,36,45,56,33,17,3 };
	mySort(arr, 10);
	printArr(arr, 10);

	char str[20] = "sancdkacef";
	mySort(str, 10);
	printArr(str, 10);

	double dNums[20] = { 3.14,2.71,6.28,-1.25,96.7,2.33,52,41,22.8,12.9 };
	mySort(dNums, 10);
	printArr(dNums, 10);
}



int main()
{
	// test01();
	test02();

	return 0;
}
