USE test04;
/*
    多表查询常用有两种分类：
    1、连接查询
    (1)内连接：相当于查询A和B的交集部分数据
    (2)外连接：
        a.左外连接：查询'左表'所有数据，以及两张表交集部分数据；
        b.右外连接：查询'右表'所有数据，以及两张表交集部分数据。
    (3)自连接：当前表与自身的连接查询，自连接必须使用表的别名
    2、子查询

*/

-- 接下来讲解'内连接'查询(内连接查询的是两张表交集的部分)
-- 1、隐式内连接
-- 表结构：tb_emp, tb_dept
-- 连接条件：tb_emp.dept_id = tb_dept.id
-- 书写格式为：SELECT 字段名1, 字段名2... FROM 表名1, 表名2... WHERE 筛选条件;
SELECT tb_emp.name AS '姓名', tb_dept.name AS '部门名称'
FROM tb_emp,
     tb_dept
WHERE tb_emp.dept_id = tb_dept.id;
-- 有时候表名比较长，书写起来很麻烦，我们就会使用别名来解决这个问题，如下：
SELECT te.name AS '姓名', td.name AS '部门名称'
FROM tb_emp AS te,
     tb_dept AS td
WHERE te.dept_id = td.id;
-- 需要注意，当我们给表起了别名后，我们不能再使用原来的表名去访问数据了，下面这SQL语句会报错
-- SELECT * FROM tb_emp AS te, tb_dept AS td WHERE tb_emp.dept_id = tb_dept.id;

-- 2、显示内连接
-- 书写格式为：SELECT 字段名1, 字段名2...  FROM 表1 INNER JOIN 表2 ON 筛选条件;(需要注意的是，筛选条件应该使用ON，而不是WHERE)
SELECT te.name AS '姓名', td.name AS '部门名称'
FROM tb_emp AS te
         INNER JOIN tb_dept AS td ON te.dept_id = td.id;
-- 或者为：SELECT 字段名1, 字段2... FROM 表1 JOIN 表2 ON 筛选条件;(INNER可以省略，但是最好写上，有个好习惯)
SELECT te.name AS '姓名', td.name AS '部门名称'
FROM tb_emp AS te
         JOIN tb_dept AS td ON te.dept_id = td.id;
