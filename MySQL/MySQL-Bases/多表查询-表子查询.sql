USE test04;
/*
    表子查询：子查询返回的结果是多行多列，这种子查询称为表子查询
    常用的操作符为：IN
*/

-- 表子查询
-- 1、查询与"鹿杖客"，"宋远桥"的职位和薪资相同的员工信息
-- a.查询"鹿杖客"和"宋远桥"的职位和薪资
SELECT job, salary
FROM tb_emp
WHERE name IN ('鹿杖客', '宋远桥');
-- b.查询对应的员工信息(同样要使用'元组')
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE (job, salary) IN (SELECT job, salary FROM tb_emp WHERE name IN ('鹿杖客', '宋远桥'));

-- 2、查询入职时间是"2006-01-01"之后的员工信息及其部门信息(没有部门也要把员工信息输出来)
-- a.先查询入职时间为"2006-01-01"之后的员工信息
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE entrydate > '2006-01-01';
-- b.再查询这些员工的部门信息(这个逻辑就是将"所得的员工信息表"作为条件，继续去联查"部门信息表")
SELECT t1.*, t2.*
FROM (SELECT id, name, age, job, salary, entrydate, managerid, dept_id FROM tb_emp WHERE entrydate > '2006-01-01') AS t1
         LEFT OUTER JOIN tb_dept AS t2 ON t1.dept_id = t2.id;
