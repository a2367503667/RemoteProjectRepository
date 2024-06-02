USE test04;
/*
    有时候我们也会当前表与当前表进行连接，也叫自连接
    自连接查询可以是内连接查询，也可以是外连接查询

    自连接的应用场景：
    想象你有一本员工名册，上面记录了每个人的名字和他们上司的名字。现在，你想知道每
    个人和他们的上司是谁。自连接就像是你在名册上查找每个人的上司，即使上司的信息也在同一本名册上。
    因为上司的id和当前员工的id都在同一个表当中，所以我们就可以使用自连接的方式去查询员工与上司的关系

    注：在我们使用自连接的时候，不要把它当成一个表来处理，要将其当成两个表处理，这样能够大大简化我们对需求的分析
*/

-- 自连接
-- 1、查询员工及其所属领导的名字
-- 书写格式为：SELECT 字段名1, 字段名2, ... FROM 表名 AS t1 INNER JOIN 表名 AS t2 ON 筛选条件;
SELECT e1.name AS '员工姓名', e2.name AS '领导姓名'
FROM tb_emp AS e1
         INNER JOIN tb_emp AS e2 ON e1.managerid = e2.id;
-- 或者为：SELECT 字段名1, 字段名2, ... FROM 表名 AS t1, 表名 AS t2 WHERE 筛选条件;
SELECT e1.name AS '员工姓名', e2.name AS '领导姓名'
FROM tb_emp AS e1,
     tb_emp AS e2
WHERE e1.managerid = e2.id;


-- 2、查询所有员工及其领导的名字，如果员工没有领导，也需要查询出来
-- 书写格式为：SELECT 字段名1, 字段名2, ... FROM 表名 AS t1 LEFT OUTER JOIN 表名 AS t2 ON 筛选条件;
SELECT e1.name AS '员工姓名', e2.name AS '领导姓名'
FROM tb_emp AS e1
         LEFT OUTER JOIN tb_emp AS e2 ON e1.managerid = e2.id;
-- 或者为：SELECT 字段名1, 字段名2, ... FROM 表名 AS t2 RIGHT OUTER JOIN 表名 AS t1 ON 筛选条件;
SELECT e2.name AS '员工姓名', e1.name AS '领导姓名'
FROM tb_emp AS e1
         RIGHT OUTER JOIN tb_emp AS e2 ON e1.id = e2.managerid;


SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp;

-- 下面是自连接的练习
-- 1、查找每个员工的直属领导名字
/*
    COALESCE 是一个标准的SQL函数，它接受两个或多个参数，并返回第一个非NULL的参数值。如果所有参数
    都是NULL，则返回NULL。COALESCE 的主要作用是提供一种方式来指定在遇到NULL值时的替代值。

    示例:
    SELECT COALESCE(NULL, '替代值', '另一个替代值');  -- 返回 '替代值'
    SELECT COALESCE(10, NULL, 20);  -- 返回 10
    SELECT COALESCE(NULL, NULL, NULL);  -- 返回 NULL

    也就是说，下面的ISNULL不是标准的SQL语言，只是特定的SQL语言里面可以用，但是COALESCE函数是标准的SQL语言，是通用的
*/
SELECT e1.name AS '员工姓名', IFNULL(e2.name, '无直属领导') AS '领导姓名'
FROM tb_emp AS e1
         LEFT OUTER JOIN tb_emp AS e2 ON e1.managerid = e2.id;

-- 2、查找所有有下属的领导
SELECT DISTINCT e2.name AS '领导', e2.job AS '职位'
FROM tb_emp AS e1
         INNER JOIN tb_emp AS e2 ON e1.managerid = e2.id;


-- 3、查找所有年龄大于其直属领导的员工
SELECT e.name AS '姓名', e.age AS '年龄', e.job AS '职位'
FROM tb_emp AS e,
     (SELECT e1.id, e2.age
      FROM tb_emp AS e1
               LEFT OUTER JOIN tb_emp AS e2 ON e1.managerid = e2.id) AS e3
WHERE (e.id = e3.id)
  AND (e.age > e3.age);

/*
    为什么后面的WHERE e1.age > e2.age中的"e2.age"可以代表JOIN tb_emp AS e2 ON e1.managerid = e2.id筛选后的结果数据？

    (1)e1 作为 tb_emp 表的别名，可以访问 tb_emp 表中的所有数据。
    (2)e2 也是 tb_emp 表的别名，但它主要用于在 JOIN 操作中标识那些满足 ON 子句条件的行。具
    体来说，e2 用于引用那些 id 与 e1 中的 managerid 相匹配的行。因此，e2 实际上代表的是通过 JOIN 条
    件筛选后的逻辑行集合，这些行与 e1 中的行有特定的关系（例如，经理与员工的关系）。在这个上下文中，我
    们通常不称 e2 为“逻辑表”，而是称其为"通过 JOIN 条件筛选后的逻辑行集合"。这是因为 e2 仍然引用的是 tb_emp 表
    中的行，而不是一个独立的表。在 SQL 查询中，e2 用于访问那些满足特定条件的行，而不是整个表。
    (3)总结来说，e1 和 e2 在自连接中代表 tb_emp 表中的不同行，这些行通过 JOIN 条件 e1.managerid = e2.id 进行
    匹配。这样，我们就可以比较这些行之间的 age 字段值，即使它们来自同一个表。

    注：上面所说的"行"就是代表一条数据
*/
-- 下面的优化完的代码
SELECT e1.name AS '姓名', e1.age AS '年龄', e1.job AS '工作'
FROM tb_emp AS e1
         INNER JOIN tb_emp AS e2 ON e1.managerid = e2.id
WHERE e1.age > e2.age;


-- 4、查找所有薪资高于其直属领导的员工
SELECT e.name AS '姓名', e.salary AS '薪资', e.job AS '职位'
FROM tb_emp AS e,
     (SELECT e1.id, e2.salary
      FROM tb_emp AS e1
               LEFT OUTER JOIN tb_emp AS e2 ON e1.managerid = e2.id) AS e3
WHERE (e.id = e3.id)
  AND (e.salary > e3.salary);

-- 优化
SELECT e1.name AS '姓名', e1.salary AS '薪资', e1.job AS '职位'
FROM tb_emp AS e1
         INNER JOIN tb_emp AS e2 ON e1.managerid = e2.id
WHERE e1.salary > e2.salary;


-- 5、查找所有与其直属领导同职位的员工
SELECT e.name AS '姓名', e.job AS '职位'
FROM tb_emp AS e,
     (SELECT e1.id, e2.job
      FROM tb_emp AS e1
               LEFT OUTER JOIN tb_emp AS e2 ON e1.managerid = e2.id) AS e3
WHERE (e.id = e3.id)
  AND (e.job = e3.job);

-- 优化
SELECT e1.name AS '姓名', e1.job AS '职位'
FROM tb_emp AS e1
         INNER JOIN tb_emp AS e2 ON e1.managerid = e2.id
WHERE e1.job = e2.job;

-- 6、查找所有与其直属领导同部门的员工
SELECT e.name AS '姓名', e.dept_id AS '部门ID', e.job AS '职位'
FROM tb_emp AS e,
     (SELECT e1.id, e2.dept_id
      FROM tb_emp AS e1
               LEFT OUTER JOIN tb_emp AS e2 ON e1.managerid = e2.id) AS e3
WHERE (e.id = e3.id)
  AND (e.dept_id = e3.dept_id);

-- 优化
SELECT e1.name AS '姓名', e1.dept_id AS '部门ID', e1.job AS '职位'
FROM tb_emp AS e1
         INNER JOIN tb_emp AS e2 ON e1.managerid = e2.id
WHERE e1.dept_id = e2.dept_id;

-- 7、查找所有没有直属领导的员工
SELECT e.name AS '姓名', e.job AS '职位'
FROM tb_emp AS e
WHERE e.managerid IS NULL;

-- 8、查找所有直属领导年龄大于60岁的员工
SELECT e.name AS '员工姓名', e3.name AS '直属领导姓名', e3.age AS '直属领导年龄'
FROM tb_emp AS e,
     (SELECT e1.id, e2.name, e2.age
      FROM tb_emp AS e1
               LEFT OUTER JOIN tb_emp e2 ON e1.managerid = e2.id) AS e3
WHERE (e.id = e3.id)
  AND (e3.age > 60);

-- 优化
SELECT e1.name AS '员工姓名', e2.name AS '直属领导姓名', e2.age AS '直属领导年龄'
FROM tb_emp AS e1
         INNER JOIN tb_emp AS e2 ON e1.managerid = e2.id
WHERE e2.age > 60;
