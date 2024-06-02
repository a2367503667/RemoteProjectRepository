USE test02;
/*
    聚合函数就是用来便于我们将一列数据作为一个整体，然后进行纵向计算的
    好比如：计算当前表中所有人的平均年龄，此时就需要纵向把所有人的年龄
    加起来，并进行平均值运算，所以聚合函数有助于我们对表中数据的运算和
    统计，这也是我们DQL中的重点

    常见的聚合函数：
    函数              功能
    count             统计数量
    max               求最大值
    min               求最小值
    avg               求平均值
    sum               求和

    注：
    (1)聚合函数是作用于某一列的，并不是作用于某一行的
    (2)聚合函数不能用在WHERE当中，只能用在SELECT、GROUP BY和HAVING当中

    书写格式为：SELECT 聚合函数(字段名) FROM 表名;
 */

-- 聚合函数
-- 1、统计企业员工数量
-- 书写格式为：SELECT COUNT(字段名) AS 别名 FROM 表名;
SELECT COUNT(id) AS '公司总人数' FROM emp;
-- 或者为：SELECT COUNT(*) AS '公司总人数' FROM emp;(不过最好还是使用id进行运算)
-- 不过COUNT(*)会有自动推导功能，它会选择一行没有null的字段进行运算
SELECT COUNT(*) AS '公司总人数' FROM emp;
/*
    需要注意的是，所有聚合函数都是都不会讲null参与运算的，也就是说我们不要将带
    有null的字段数据的字段参与聚合函数的运算
 */
-- 如：因为在idcard的字段列中，有数据为null，所以统计结果会比真实结果少一个人
SELECT COUNT(idcard) AS '公司总人数' FROM emp;

-- 2、统计该企业员工的平均年龄
-- 书写格式为：SELECT AVG(字段名) AS 别名 FROM 表名;
SELECT AVG(age) AS '年龄平均值' FROM emp;

-- 3、统计该企业员工的最大年龄
-- 书写格式为：SELECT MAX(字段名) AS 别名 FROM 表名;
SELECT MAX(age) AS '年龄最大值' FROM emp;

-- 4、统计该企业员工的最小年龄
-- 书写格式为：SELECT MIN(字段名) AS 别名 FROM 表名;
SELECT MIN(age) AS '年龄最小值' FROM emp;

-- 5、统计西安地区员工的年龄之和
-- 书写格式为：SELECT SUM(字段名) AS 别名 FROM 表名 WHERE workaddress = '西安';
SELECT SUM(age) AS '西安地区员工年龄之和' FROM emp WHERE workaddress = '西安';
