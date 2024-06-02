USE test04;
/*
    列子查询：子查询返回结果是一列(可以是多行)，这样子查询成为"列子查询"
    常用的操作符有：IN、NOT IN、ANY、SOME、ALL

    操作符               描述
    IN                  在指定的集合范围之内，多选一
    NOT IN              不在指定的集合范围之内
    ANY                 子查询返回列表中，有任意一个满足即可
    SOME                与ANY等同，使用SOME的地方都可以使用ANY
    ALL                 子查询返回列表的所有值都必须满足
*/

-- 1、查询"销售部"和"市场部"的所有员工信息
-- a.先查询"销售部"和"市场部"的部门ID
SELECT id
FROM tb_dept
WHERE name IN ('销售部', '市场部');
-- b.再查询所有员工对应的部门的员工信息
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE dept_id IN (2, 4);
-- c.最后将a和b合并
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE dept_id IN (SELECT id FROM tb_dept WHERE name IN ('销售部', '市场部'));

-- 2、查询比"财务部"所有人工资都高的员工信息
-- a.先查询"财务部"的部门ID
SELECT id
FROM tb_dept
WHERE name = '财务部';
-- b.再查询"财务部"所有人的工资
SELECT salary
FROM tb_emp
WHERE dept_id = 3;
-- c.最后再进行合并查询
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE salary > ALL (SELECT salary FROM tb_emp WHERE dept_id = (SELECT id FROM tb_dept WHERE name = '财务部'));

-- 3、查询比"研发部"其中任意一人工资都高的员工信息
-- a.先查询"研发部"的ID
SELECT id
FROM tb_dept
WHERE name = '研发部';
-- b.在查询"研发部"的所有人的工资
SELECT salary
FROM tb_emp
WHERE dept_id = 1;
-- c.最后进行合并查询即可
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE salary > ANY (SELECT salary FROM tb_emp WHERE dept_id = (SELECT id FROM tb_dept WHERE name = '研发部'));
-- 或者为：
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
[O       dept_id
FROM tb_emp
WHERE salary > SOME (SELECT salary FROM tb_emp WHERE dept_id = (SELECT id FROM tb_dept WHERE name = '研发部'));
