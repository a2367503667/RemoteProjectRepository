#define _CRT_SECURE_NO_WARNING
#include <iostream>

/* 
	其实左移运算符就是便于我们直接输出自定义Maker类对象的数据，就好
	比如：原来我们是需要这样"std::cout<<m1.id<<std::endl;"输出m1对象中id的值的，但是
	现在我想用"std::cout<<m1<<std::endl;"这种方式输出m1.id，这时候我们就需要重载"<<"左移运算符

	这里还需要补充一下，std::cout是ostream的对象，std::cin是istream的对象

*/
class Maker1
{
	friend std::ostream &operator<<(std::ostream& out, Maker1& m);
public:
	Maker1() :num(0) {}
	Maker1(int num) :num(num) {}




	~Maker1() {}
private:
	int num;
};

// 这里开始写"<<"左移运算符的重载
/* 
		这样写有个弊端，就是没办法链式编程，我们使用std::cout时发现，是可以进行链式编程的
	那是因为我们每次做输出流操作都返回一个std::cout对象，因此，如果我们想使用链式编程
	我们也应该返回std::cout对象

	也就是不用"void operator<<(std::ostream& out, Maker1& m)"这种写法
	用"std::ostream& operator<<(std::ostream& out, Maker1& m)"

	这里加&是因为std::cout对象是一个单例，不能够有多个对象的，因此我们返回就只能用&
	相对应的std::cin也是同样的道理
*/

/*
注意：
	1、形参和实参是一个对象(单例)；
	2、不能改变类库中的代码，即不能将自定义类加到std类库里面；
	3、ostream中把拷贝构造私有化；
	4、如果要和endl一起使用，那么必须返回ostream对象(链式编程)；
	5、std::endl是一个函数，其实就是将endl这个函数指针作为参数传递，内部做了一个
	操作operator<<endl()，获取到因为拿到指针endl后，只要在后面加括号endl()，就可以调用函数了
	6、std::cout其实内部重载"<<"左移运算符对普通类型的操作
*/
std::ostream &operator<<(std::ostream& out, Maker1& m)
{
	out << "num = " << m.num;
	return out;
}

void test01()
{
	Maker1 m1(88);
	std::cout << m1 << std::endl;

}


int main(int argc, char* argv[])
{
	test01();

	return 0;
}
