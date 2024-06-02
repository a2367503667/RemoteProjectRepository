USE test04;
/*
     行子查询：
     子查询返回的结果是一行(可以是多列)，这种子查询称为行子查询
     常用的操作符有：=、<>、!=、IN、NOT IN
*/

-- 行子查询
-- 查询与"张无忌"的"薪资"和"直属领导"都相同的员工信息
-- a.先查询"张无忌"的薪资和直属领导
SELECT salary, managerid
FROM tb_emp
WHERE name = '张无忌';
-- b.查询对应的员工信息
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE salary = 12500
  AND managerid = 1;
-- c.组合查询对应的员工信息
/*
    对于上面这种多个条件同时满足的情况来说，我们是没有办法直接呈现或书写的如：salary = 12500 AND managerid = 1
    所以，在这里我们提出"元组"的写法，即(salary, managerid) = (12500, 1)这种写法
*/
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE (salary, managerid) = (SELECT salary, managerid FROM tb_emp WHERE name = '张无忌');
