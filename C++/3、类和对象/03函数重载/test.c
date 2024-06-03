#include <stdio.h>

/*
* (C语言)编译成汇编代码的终端命令是：gcc -S test.c -o test.s
* (C++)编译成汇编代码的终端命令是：g++ -S test.cpp -o test.s
在编译时，test只在前面加了个_并没有对函数进行取别名标记
_test: <-  看这里
LFB13:
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

void test()
{

}

// void test(int a)
//{

//}

/*
在C语言中，如果函数出现同名，在终端编译会报这个错误，显示重名(即不能重载)
test.c:38:6: error: redefinition of 'func'
 void func(int a)
      ^~~~
test.c:33:6: note: previous definition of 'func' was here
 void func()
*/

/*
这个是编译后，func的标记，被标记为_func，但是没有标记参数类型(void)，只标记了函数名
_func:
LFB14:
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
// 因为重载编译报错，所以这里改一下
/*
这里同理，编译器没有给函数参数类型进行标记，只标记了函数名_func2
_func2:
LFB15:
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

void func2(int a)
{
	
}
// 由上面可知，C语言编译时只标记了函数名，没有标记参数类型，那就是说，如果出现函数名相同
// 那么他们编译出来的标记就相同，那就会出现二义性，这也是为什么在C语言中函数重名会报错的原因
// 例如func()与func(int a)，由于没有标记参数类型，那就是说编译后的标记都是_func，也就会出现二义性

int main01()
{


}
