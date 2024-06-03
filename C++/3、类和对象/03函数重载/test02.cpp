#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


// C++编译生成汇编文件的方法在test.c这个文件，可以去那里查找
/*
C++中有对函数名和形参类型作标记，__Z4func是函数名标记，后面的v是形参表参数类型void
__Z4funcv:
LFB1546:
        .cfi_startproc
        pushl   %ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        movl    %esp, %ebp
        .cfi_def_cfa_register 5
        nop
        popl    %ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
*/
void func()
{

}
/*
这里也是，__Z4func是函数名，i是形参表参数类型int
__Z4funci:
LFB1547:
        .cfi_startproc
        pushl   %ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        movl    %esp, %ebp
        .cfi_def_cfa_register 5
        nop
        popl    %ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
*/
void func(int a)
{

}
/*
这里也是，__Z4fun函数名，id是形参表参数类型标记，其中i是int，d是double
__Z4funcid:
LFB1548:
        .cfi_startproc
        pushl   %ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        movl    %esp, %ebp
        .cfi_def_cfa_register 5
        subl    $8, %esp
        movl    12(%ebp), %eax
        movl    %eax, -8(%ebp)
        movl    16(%ebp), %eax
        movl    %eax, -4(%ebp)
        nop
        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
*/
void func(int a, double e)
{

}
/*
这里也是，函数标记为__Z4func，形参表参数类型标记为di，其中d是double，i是int
__Z4funcdi:
LFB1549:
        .cfi_startproc
        pushl   %ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        movl    %esp, %ebp
        .cfi_def_cfa_register 5
        subl    $8, %esp
        movl    8(%ebp), %eax
        movl    %eax, -8(%ebp)
        movl    12(%ebp), %eax
        movl    %eax, -4(%ebp)
        nop
        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc

*/
void func(double e, int a)
{

}
// 由上面可知，虽然同一个函数名，函数名的标记是相同的，但是C++编译器也会对形参表的参数类型进行
// 标记，那就是说只要形参表不同，那么对应的函数就不同，这样就可以允许相同函数名的重载现象出现
// 同时，C++编译器并没有对返回值进行标记，那也就意味着函数返回值不作为重载判断的条件
// 一句话，就是C语言没有给函数名起相应的别名
// 那么就有一个问题，当C语言与C++语言去调用C语言的函数时，会去找哪个func？
// 对于C++去找函数会去找__Z4func这样的函数，但是C语言只会找_func这种函数，这两个不相同
// 即找不到对应函数，也就是说C++去调用C语言的函数，就需要找到取了别名的函数，例如__Z4funcdi这种
// 但是C语言只有_func这种函数，那C++找不到像这样__Z4funcdi的函数名，那C++就会报错
// 那我们如何解决这个事情呢？下个项目(09C++调用C语言的函数)讲解


int main()
{

	return 0;
}
