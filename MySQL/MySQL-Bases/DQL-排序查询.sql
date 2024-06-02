/*
    有时候我们查询后所得到的数据是乱序的，不便于我们观看和统计，所以
    我们会将需要查询的结果进行排序，这样才会便于我们对数据做进一步处理

    如果是多个字段排序，当第一个字段相同时，就会按照第二个字段进行排序，以此类推
*/
-- 排序查询
-- 1、根据年龄对公司的员工进行升序排序(升序是默认的排序方式，即关键字ASC可以省略)
-- 书写格式为：SELECT 字段名1, 字段名2, ... FROM 表名 ORDER BY 字段名 ASC;
SELECT id,
       worknum,
       name,
       gender,
       age,
       idcard,
       workaddress,
       entrydate
FROM emp
ORDER BY age ASC;
-- 或者为：SELECT 字段名1, 字段名2, ... FROM 表名 ORDER BY 字段名;
SELECT id,
       worknum,
       name,
       gender,
       age,
       idcard,
       workaddress,
       entrydate
FROM emp
ORDER BY age;


-- 2、根据入职时间，对员工进行降序排序
-- 书写格式为：SELECT 字段名1, 字段名2, ... FROM 表名 ORDER BY 字段名 DESC;
-- 对于日期的降序来说，就是日期晚的比早的要大，如：2024-05-14 > 2024-01-01
SELECT id,
       worknum,
       name,
       gender,
       age,
       idcard,
       workaddress,
       entrydate
FROM emp
ORDER BY entrydate DESC;


-- 3、根据年龄对公司的员工进行升序排序，年龄相同，再按照入职时间进行降序排序
-- 书写格式为：SELECT 字段名1, 字段名2, ... FROM 表名 ORDER BY 字段名1 ASC, 字段名2 DESC;
SELECT id,
       worknum,
       name,
       gender,
       age,
       idcard,
       workaddress,
       entrydate
FROM emp
ORDER BY age ASC, entrydate DESC;
-- 或者为：SELECT 字段名1, 字段名2, ... FROM 表名 ORDER BY 字段名1, 字段名2 DESC;
SELECT id,
       worknum,
       name,
       gender,
       age,
       idcard,
       workaddress,
       entrydate
FROM emp
ORDER BY age, entrydate DESC;
