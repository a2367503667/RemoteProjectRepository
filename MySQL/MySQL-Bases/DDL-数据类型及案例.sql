-- 这个SQL语句是用来查询当前字符集的
SHOW VARIABLES LIKE 'character\_set\_database';
/*
    数据类型不仅在我们的C++/Java里面有，在MySQL里面仍然有
    我们常用的类型有如下：
    TINYINT INT CHAR VARCHAR DOUBLE DATE TIME
    DATETIME...

    对于DOUBLE来说，它需要指定这个数的长度(整数部分和小数部分)和数的精度(小数部分)
    如：DOUBLE(4, 1)表示浮点数一共有4位，其中小数为1位，像：125.5、138.8等
    对于DECIMAL来说也是同样的道理
    因此对于这些类型我们都需要熟练地掌握

    接下来我们实现一个案例，写一个表，要求如下：
    1、编号(数字)
    2、员工工号(字符串类型，长度不超过10位)
    3、员工姓名(字符串类型，长度不超过10位)
    4、性别(男/女，存储一个汉字)
    5、年龄(正常人年龄，不可以存储负数)
    6、身份证号(二代身份证号均为18位，身份证中有X这样的字符)
    7、入职时间(取值年月日即可)

    这里需要注意，我们在MySQL5.5之后的版本，默认字符集都是utf8mb4，也就是说占用4个字节的
    而对于utf8是占用3个字节的，并且char(1)和varchar(1)中的1是代表1个字符，并不是代表1个
    字节，因此我们可以使用char(1)和varchar(1)来存储一个中文字
 */
 CREATE TABLE emp(
     id INT UNSIGNED COMMENT "编号",
     worknum VARCHAR(10) COMMENT "员工工号",
     name VARCHAR(10) COMMENT "姓名",
     gender CHAR(1) COMMENT "性别",
     age TINYINT UNSIGNED COMMENT "年龄",
     idcard CHAR(18) COMMENT "身份证号码",
     entertime DATETIME COMMENT "入职时间"
 ) COMMENT "员工表";

-- 表创建完之后，查看一下表的结构
DESC emp;
