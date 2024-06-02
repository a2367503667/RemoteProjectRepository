USE test02;
/*
    条件查询：就是在给定的条件下，查找我们想要的数据
    其中条件查询需要用到关键字WHERE

    而有很多条件的相应运算符
    比较运算符           功能
    >                   大于
    >=                  大于等于
    <                   小于
    <=                  小于等于
    =                   等于
    <>或!=              不等于
    BETWEEN...AND...    在某个范围之内(含最小，最大值，即是[min, max]闭区间) BETWEEN 10 AND 20 -> 10 <= 值 <= 20
    IN(...)             在IN后面的列表中的值，多选一(属于或的关系) IN(10, 20, 30) -> 值 = 10 OR 值 = 20 OR 值 = 30
    LIKE占位符           模糊匹配('_'匹配单个字符，'%'匹配任意个字符) 值 LIKE '张%' -> 可查找性张的人
    IS NULL             是NULL 值 IS NULL -> 查找值为NULL的
    IS NOT NULL         不是NULL 值 IS NOT NULL -> 查找值不为NULL的
    -----------------------------------------------------------------
    逻辑运算符               功能
    AND或&&                 并且(多个条件同时满足时成立)
    OR或||                  或者(多个条件任意一个成立)
    NOT或!                  非，不是
 */

-- 1、查询年龄等于88的员工信息
-- 书写格式为：SELECT 字段名 AS 别名... FROM 表名 WHERE age = 88;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职日期'
FROM emp
WHERE age = 88;

-- 2、查询年龄小于20的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE age < 20;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age < 20;

-- 3、查询年龄小于等于20的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE age <= 20;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age <= 20;

-- 4、查询没有身份证号码的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE idcard IS NULL;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE idcard IS NULL;

-- 5、查询有身份证号码的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE idcard IS NOT NULL;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE idcard IS NOT NULL;

-- 6、查询年龄不等于88的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE age <> 88;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age <> 88;
-- 或者为：SELECT 字段名 AS 别名 FROM 表名 WHERE age != 88;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age != 88;

-- 7、查询年龄在15岁(包含)到20岁(包含)之间的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE age BETWEEN 15 AND 20;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age BETWEEN 15 AND 20;
-- 或者为：SELECT 字段名 AS 别名 FROM 表名 WHERE age >= 15 && age <= 20;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age >= 15 && age <= 20;
-- 或者为：SELECT 字段名 AS 别名 FROM 表名 WHERE age >= 15 AND age <= 20;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age >= 15
  AND age <= 20;

-- 8、查询性别为女且年龄小于25岁的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE gender = '女' && age < 25;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE gender = '女' && age < 25;
-- 或者为：SELECT 字段名 AS 别名 FROM 表名 WHERE gender = '女' AND age < 25;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE gender = '女'
  AND age < 25;

-- 9、查询年龄等于18或20或40的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE age IN(18, 20, 40);
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age IN (18, 20, 40);
-- 或者为：SELECT 字段名 AS 别名 FROM 表名 WHERE age = 18 || age = 20 || age = 40;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age = 18 || age = 20 || age = 40;
-- 或者为：SELECT 字段名 AS 别名 FROM 表名 WHERE age = 18 OR age = 20 OR age = 40;
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE age = 18
   OR age = 20
   OR age = 40;

-- 10、查询姓名为两个字的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE name LIKE '__';
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE name LIKE '__';

-- 11、查询身份证号码最后一位是X的员工信息
-- 书写格式为：SELECT 字段名 AS 别名 FROM 表名 WHERE idcard LIKE '%X';
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE idcard LIKE '%X';
-- 或者为：SELECT 字段名 AS 别名 FROM 表名 WHERE idcard LIKE '_________________X';
SELECT id          AS '编号',
       worknum     AS '工号',
       name        AS '姓名',
       gender      AS '性别',
       age         AS '年龄',
       idcard      AS '身份证号码',
       workaddress AS '工作地址',
       entrydate   AS '入职时间'
FROM emp
WHERE idcard LIKE '_________________X';
