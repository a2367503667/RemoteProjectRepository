USE test04;
/*
    子查询（Subquery）又叫嵌套查询，是嵌套在另一个查询中的查询，可以把它想象成查询中的查询。就像你在做一个大拼图
    时，先完成一个小拼图，然后用这个小拼图作为大拼图的一部分。具体来说，子查询通常用在以下几个地方：
    (1)在WHERE子句中：你可以使用子查询来定义一个条件，这个条件依赖于另一个查询的结果。例如，你可能想要找出所有收入高
       于平均收入的员工。你可以先计算平均收入（子查询），然后找出所有收入高于这个平均值的员工（主查询）。
    (2)在FROM子句中：子查询也可以用来创建一个临时表，这个表是基于另一个查询的结果。例如，你可能想要分析一个基于特定
       条件筛选出来的数据集。
    (3)在SELECT子句中：有时候，你可能想要在结果集中包含一个基于另一个查询计算出的值。

    举个例子，假设你有一个员工表employees，其中包含员工的工资信息。你想找出工资最高的员工信息。你可以使用子查询来找出
    最高的工资，然后在主查询中使用这个值来筛选员工：
    SELECT * FROM employees WHERE salary = (SELECT MAX(salary) FROM employees);

    在这个例子中，(SELECT MAX(salary) FROM employees) 是一个子查询，它计算出所有员工中的最高工资。主
    查询SELECT * FROM employees WHERE salary = ... 使用这个子查询的结果来找出工资等于最高工资的员工。

    注：子查询的外部语句可以是INSERT/UPDATE/DELETE/SELECT的任何一个

    根据子查询的结果不同又分为：
    (1)标量子查询(子查询结果为单个值)
    (2)列子查询(子查询结果为一列)
    (3)行子查询(子查询结果为一行)
    (4)表子查询(子查询结果为多行多列)
*/

-- 标量子查询(查询返回的结果为一行一列，即单个值，可以是数字、字符串和日期等)
-- 标量子查询的操作符常有的有：>、<、>=、<=、<>、!=、=
-- 1、查询"销售部"的所有员工信息
-- a.首先查询"销售部"部门ID
SELECT id
FROM tb_dept
WHERE name = '销售部';
-- b.根据销售部门ID查询员工信息
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE dept_id = 4;
-- c.上面两个查询结果合并
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE dept_id = (SELECT id FROM tb_dept WHERE name = '销售部');

-- 2、查询在"方东白"入职时间之后的员工信息
SELECT entrydate
FROM tb_emp
WHERE name = '方东白';
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE entrydate > (SELECT entrydate FROM tb_emp WHERE name = '方东白');
