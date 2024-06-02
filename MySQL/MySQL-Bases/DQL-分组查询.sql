USE test02;
/*
    所谓的分组查询，就是说我们查询的结果有多种情况，好比如：男员工的人数和女员工的人数
    当涉及到查询不同分类的结果需要进行比较或者提取时，就可以使用分组查询，继续以上面为例
    进行讲解：我们想要查看男员工和女员工的人数，此时我们直接使用条件查询只能一次得到男员工
    人数或女员工人数，是没有办法同时得到两个员工的人数的，所以此时就需要用到分组查询，把男
    员工和女员工人数分成两组放到同一个表当中

    需要注意的是，WHERE和HAVING的区别：
    (1)执行时机不同：WHERE是分组之前进行过滤的，不满足WHERE条件就不会参与分组，而HAVING是分组之后再对结果进行过滤;
    (2)判断条件不同：WHERE不能对聚合函数进行判断，而HAVING可以。

    书写格式为：SELECT 字段列表 FROM 表名 [WHERE条件] GROUP BY 分组字段名 [HAVING分组后过滤条件];
    执行顺序：WHERE > 聚合函数 > HAVING

    需要注意的是，当我们遇到比较复杂的分组查询，我们可以先查询总体，再细致进行分组查询，最后再进行筛选
    即遵循先WHERE，再GROUP BY，最后再HAVING，这样可以大大降低查询的难度
    并且在分组之后，字段信息一般是显示聚合函数和分组字段，查询其他的字段无任何意义，也就是在SELECT和FROM之
    间只写聚合函数和分组字段(也就是GROUP BY字段)，因为写其他的字段信息是没有任何意义的

 */

-- 1、根据性别分组，统计男员工和女员工的数量
-- 书写格式为：SELECT gender AS 别名, COUNT(字段名) AS 别名 FROM 表名 GROUP BY 字段名;
SELECT gender AS '性别', COUNT(id) AS '数量'
FROM emp
GROUP BY gender;

-- 2、根据性别分组，统计男员工和女员工的平均年龄
-- 书写格式为：SELECT gender AS 别名, AVG(字段名) AS 别名 FROM 表名 GROUP BY 字段名;
SELECT gender AS '性别', AVG(age) AS '平均年龄'
FROM emp
GROUP BY gender;

-- 3、查询年龄小于45的员工，并根据工作地址分组，获取员工数量大于等于3的工作地址
-- 书写格式为：SELECT workaddress AS 别名, COUNT(id) AS 别名 FROM 表名 WHERE age < 45 GROUP BY workaddress HAVING COUNT(字段名) >= 3;
SELECT workaddress AS '工作地址', COUNT(id) AS '数量'
FROM emp
WHERE age < 45
GROUP BY workaddress
HAVING COUNT(id) >= 3;
