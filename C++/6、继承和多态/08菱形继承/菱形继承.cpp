#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

/*
	什么是菱形继承？
		有Father类、Son1、Son2类和GrandSon类，其中Son1和Son2同时继承了Father类，而
	GrandSon类则多继承Son1和Son2类，此时就构成了菱形继承

	什么是虚继承？
		因为在普通的多继承中，如果一个子类GrandSon多继承了父类Son1和Son2，并且父类Son1和Son2
	也同时继承了同一个父类Father，就会形成菱形继承结果，这种情况下子类GrandSon会继承多份来自
	共同基类Father的数据成员a，这样就会出现二义性和浪费资源，为了解决这个问题，我们就在父类
	Son1和Son2的继承权限前面加上关键字virtual，即为虚继承，告诉编译器子类GrandSon只包含共同
	基类Father中的一个实例a，而不是多个实例，这个共同的基类(Father)被称为虚基类

	下面是继承模型结构图(未虚继承)：

	12菱形继承.cpp
	class GrandSon  size(20):
			+---
	 0      | +--- (base class Son1)
	 0      | | +--- (base class Father)
	 0      | | | a
			| | +---
	 4      | | s1
			| +---
	 8      | +--- (base class Son2)
	 8      | | +--- (base class Father)
	 8      | | | a
			| | +---
	12      | | s2
			| +---
	16      | gS
			+---
	
		我们观察可知，现在GrandSon有两个a的实例，一个是来自继承Father的Son1的，另一个是
	来自继承Father的Son2的，这样就会出现二义性，并且还浪费内存空间，所以我们在继承Father
	类的类Son1和Son2的权限前面加上virtual关键字，即虚继承父类Father(这个类成为虚基类)，就
	可以解决这个问题，如下结构图：

	class GrandSon  size(24): 这24个字节包含了两个虚指针大小
			+---
	 0      | +--- (base class Son1)
	 0      | | {vbptr} 这个指针是虚指针(其中它也占4个字节大小)
	 4      | | s1
			| +---
	 8      | +--- (base class Son2)
	 8      | | {vbptr} 这个也是虚指针(其中它也占4个字节大小)
	12      | | s2
			| +---
	16      | gS
			+---
			+--- (virtual base Father)
	20      | a
			+---

	下面两个是虚指针表：
	GrandSon::$vbtable@Son1@:
	 0      | 0							   是Son1虚指针到Father的距离
	 1      | 20 (GrandSond(Son1+0)Father) 这个表示Son1到Father的距离是20，看上面可知

	GrandSon::$vbtable@Son2@:
	 0      | 0							   是Son2虚指针到Father的距离
	 1      | 12 (GrandSond(Son2+0)Father) 这个表示Son2到Father的距离是12，看上面可知


	vbi:       class  offset o.vbptr  o.vbte fVtorDisp
			  Father      20       0       4 0



	虚继承的原理：
	1、编译器给类添加一个指着，指针指向类似于表的结构，该表记录了该指针离虚基类变量的偏移量
	2、当子类多继承两个父类，那么只有一份成员变量，有两个虚指针，这时只有一份数据访问就不会
	   出现二义性问题

*/

class Father
{
public:
	void func()
	{
		std::cout << "虚基类 func()" << std::endl;
	}
public:
	int a = 10;
};

// Son1继承Father，就隐藏与a
class Son1 :virtual public Father
{
public:
	/*
		下面这个是Son1类的继承模型图：
		可以看出Son1到Father的成员a的距离是8
		class Son1      size(12):
				+---
		 0      | {vbptr}
		 4      | s1
				+---
				+--- (virtual base Father)
		 8      | a
				+---

		Son1::$vbtable@:
		 0      | 0
		 1      | 8 (Son1d(Son1+0)Father)
		vbi:       class  offset o.vbptr  o.vbte fVtorDisp
				  Father       8       0       4 0
	*/

public:
	int s1 = 20;
};

// Son2继承Father，也隐藏与a
class Son2 :virtual public Father
{
public:
	/*
		下面这个是Son2类的继承模型图：
		可以看出Son2到Father的成员a的距离是8
		class Son2      size(12):
				+---
		 0      | {vbptr}
		 4      | s2
				+---
				+--- (virtual base Father)
		 8      | a
				+---

		Son2::$vbtable@:
		 0      | 0
		 1      | 8 (Son2d(Son2+0)Father)
		vbi:       class  offset o.vbptr  o.vbte fVtorDisp
				  Father       8       0       4 0
	*/
public:
	int s2 = 30;
};

// 当GrandSon多继承了Son1和Son2后，就同时得到了两份a
class GrandSon :public Son1, public Son2
{
public:
	/*
		下面这个是GrandSon类的继承模型图：
		可以看出GrandSon到Father的成员a的距离是20
		class GrandSon  size(24):
				+---
		 0      | +--- (base class Son1)
		 0      | | {vbptr}
		 4      | | s1
				| +---
		 8      | +--- (base class Son2)
		 8      | | {vbptr}
		12      | | s2
				| +---
		16      | gS
				+---
				+--- (virtual base Father)
		20      | a
				+---

		GrandSon::$vbtable@Son1@:
		 0      | 0
		 1      | 20 (GrandSond(Son1+0)Father)

		GrandSon::$vbtable@Son2@:
		 0      | 0
		 1      | 12 (GrandSond(Son2+0)Father)
		vbi:       class  offset o.vbptr  o.vbte fVtorDisp
				  Father      20       0       4 0
	
	*/

public:
	int gS = 40;
};

// 1、虚继承二义性问题
void test01()
{
	GrandSon gSon;

	// 这里同样也会出现二义性问题，相当于有两份a了
	// gSon.a; // err

	// 这里需要用虚继承的方法解决

}

// 2、通过虚指针访问成员
void test02()
{
	Son1 s1;
	/*
		下面这个是Son1类的继承模型图：
		可以看出Son1到Father的成员a的距离是8
		class Son1      size(12):
				+---
		 0      | {vbptr}
		 4      | s1
				+---
				+--- (virtual base Father)
		 8      | a
				+---

		Son1::$vbtable@:
		 0      | 0
		 1      | 8 (Son1d(Son1+0)Father)
		vbi:       class  offset o.vbptr  o.vbte fVtorDisp
				  Father       8       0       4 0
	*/

	/*
		我们如何通过虚指针来获取到偏移量，从而取出Father中成员变量a的值

		1、&s1：先获取到Father的子类Son1对象的地址；
		
		2、(int*)&s1：因为上面指针&s1的步长不是4个字节，这时候我们没办法得到虚指针，因为
		   对于虚指针来说是4个字节的，而&s1的步长不是4个字节，所以我们需要转换成(int*)，将步长
		   改为4个字节，就可以取到虚指针了(需要注意的是，我们看图可知Son1的虚指针的位置在开头
		   的0位置，也就是我们取最开始4个字节即可)；

		3、*(int*)&s1：这里为什么是取引用？因为虚指针的值是指向虚指针表的地址，只不过以整型数的
		   方式存储，也就是说虚指针就是Son1对象中的整型数，相当于二级指针存储一级指针一样，也是将
		   一级指针值(地址)用整型数存起来，换回这里是虚指针属于二级指针，虚指针表的起始地址相当于
		   一级指针，相应地虚函数表的其实地址就以整型数的方式存到了虚指针当中，也就是说当我们进
		   行*(int*)&s1操作之后，我们就得到s1对象的前4个字节的整型数，这个整型数其实是指向虚指针
		   表的地址(也就是说虚指针所存的值是虚指针表的起始地址)，其实这个整型数已经代表了地址了，
		   也就是说我们已经拿到了虚指针表的起始地址(相当于对二级指针解引用，我们得到的是一级指针，
		   即使一级指针之前是以整型数的形式存储在二级指针当中，但是当我们解引用之后就会将其转换
		   成地址，即成为指针)；

		4、(int*)*(int*)&s1：我们得到已经得到了虚指针表起始地址了，但是现在相当于得到整个表的
		   地址，也就是说步长跨度是一个虚指针表，如果我们需要访问表中的元素的话，我们需要把步长
		   降低，因为虚指针表每个元素都是相隔4个字节，所以我们可以把当前的指针转换成(int*)类型
		   的指针，使得步长跨度为4个字节，这样我们就可以通过步长去访问虚指针表的每个成员，即就是
		   为什么我们要在"*(int*)&s1"的前面加上(int*)，其实和上面第2步目的一样，都是降低步长；

		5、(int*)*(int*)&s1+1：我们已经得到了虚指针表的起始位置，也就是虚指针表的第一个元素的地
		   址，但是我们存储的偏移量是在虚指针表第二个数据当中，由于第4步操作后我们已经将步长降低下
		   来，变成4个字节，而这个虚指针表就像一个数组，每个元素的偏移量也是4个字节，所以我们对
		   虚指针偏移1，就可以找到指向偏移量的位置(地址)了，即(int*)*(int*)&s1+1；

		6、*((int*)*(int*)&s1+1)：既然我们已经指向偏移量的位置，接下来解引用就可以得到偏移量值；

		-----------------------------------------------------------------------------------------
		上面只是拿到了Son1对象到Father的内存的起始位置距离(偏移量)，我们需要通过&s1加上偏移量才
		可以得到Father的内存的起始位置(地址)，从而才可以访问到Father的成员a的值

		7、&s1：同样先得到Son1对象的指针&s1；

		8、(char*)&s1：我们知道偏移量了，那我们就一个一个字节偏移到Father的内存的起始位置(地址)
		   即可，所以我们就将这个指针的步长改成1，即强转为(char*)类型指针；

		9、(char*)&s1+*((int*)*(int*)&s1+1)：我们加上偏移量偏移到Father的内存的起始位置(地址)；

		10、我们已经得到了Father的内存的起始地址，那就意味着我们已经得到了Father的内存可访问的
		    空间，这时我们将上面的地址(char*)&s1+*((int*)*(int*)&s1+1)转成(Father*)类型，然后
			通过->获取a的值即可，即：((Father*)((char*)&s1+*((int*)*(int*)&s1+1)))->a，其实不单只
			可以获取a的值，只要是Father的成员都可以通过上面那个指针"->"操作后得到(成员函数也可以)；
	*/
	
	// 我们发现不止可以得到成员变量，还可以得到成员函数，因为我们的到的是Father内存空间的起始地址
	// 我们就可以通过这个内存空间去访问属于Father内存空间的内容，即可以访问Father的所有成员
	std::cout << "a = " << ((Father*)((char*)&s1 + *((int*)*(int*)&s1 + 1)))->a << std::endl;
	((Father*)((char*)&s1 + *((int*)*(int*)&s1 + 1)))->func();
}

// 3、通过二级指针和一级指针验证虚指针和虚指针表的联系
void test03()
{
	/*
		下面我们可以验证出，二级指针本质上是将一级指针按照整型数的方式存储起来的，当我们对
		二级指针解引用后，得到的那个整型数值就会转换成一级指针，从而成为地址

		那就意味着我们"虚指针"其实也是将"虚指针表"的地址按照整型数的方式存起来，只不过从
		"虚指针"解引用得到"虚指针表"的起始位置(地址)之后，就会将这个整型数重新变成指针，即
		就得到了"虚指针表"的起始地址
	*/ 
	int a = 100;
	int* p = &a;
	int** pp = &p;

	std::cout << "a = " << std::endl;
	std::cout << "p = " << p << std::endl;
	std::cout << "pp = " << pp << std::endl;
}


int main()
{
	// test01();
	test02();
	// test03();

	return 0;
}
