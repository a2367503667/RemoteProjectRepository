// const int c = 20;  这句话不具有外部链接属性
extern const int c = 20; // 这句话才有外部链接属性，即加上extern就可以把const修饰的全局变量变成具有外部链接属性
