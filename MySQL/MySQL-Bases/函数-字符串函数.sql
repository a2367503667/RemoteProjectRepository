USE test02;
/*
    我们之前也学习过函数，就好比如：聚合函数(COUNT()、AVG()、MAX()、MIN()和SUM())

    这小节继续学习函数，常见的函数分类有：字符串函数、数值函数、日期函数和流程函数
    接下来讲解字符串函数，常见的字符串函数有如下：
    函数                                  功能
    CONCAT(S1, S2, ...)                  字符串拼接，将S1, S2, ...拼接成一个字符串
    LOWER(str)                           将字符串str全部转换成小写
    UPPER(str)                           将字符串str全部转换成大写
    LPAD(str, n, pad)                    左填充，用字符串pad对str左边进行填充，达到n个字符串长度
    RPAD(str, n, pad)                    右填充，用字符串pad对str右边进行填充，达到n个字符串长度
    TRIM(str)                            去掉字符串头部和尾部的空格
    SUBSTRING(str, start, len)           返回从字符串str的start位置起的len个长度的字符串
*/

-- 1、CONCAT函数
SELECT CONCAT('hello', ' MySQL');

-- 2、LOWER函数
SELECT LOWER('HeLLo');

-- 3、UPPER函数
SELECT UPPER('hEllO');

-- 4、LPAD函数
SELECT LPAD('1', 5, '-');

-- 5、RPAD函数
SELECT RPAD('C', 3, '+');

-- 6、TRIM函数
-- 其中\'是转义字符，因为'有特殊的含义
-- TRIM函数之后去除头尾的空格，但是不会去除中间的空格
SELECT TRIM('   Let\'s learn MySQL  ');

-- 7、SUBSTRING函数
-- 其中字符串的起始位置是从1开始的，和我们之前学的Java和C++有点区别，即'Hello'的索引是1 ~ 5
SELECT SUBSTRING('Hello MySQL', 7, 5);
-- 注：如果指定的长度大于字符串的长度，SUBSTRING函数只会计算字符串最大的长度返回给你，如：
-- 即使指定的长度100，超出字符串的长度了，它也只会返回所得最大的字符串，即输出'MySQL'
SELECT SUBSTRING('Learn MySQL', 7, 100);


-- 由于业务需求变更，企业员工的工号统一为5位数，目前不足5位数的全部在前面补0，比如：1号员工的工号应该为00001
UPDATE emp
SET worknum = LPAD(worknum, 5, '0');
SELECT *
FROM emp;
