USE test04;
-- 数据准备
CREATE TABLE IF NOT EXISTS tb_salary_grade
(
    id         INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    grade      INT UNSIGNED NOT NULL UNIQUE COMMENT '薪资等级',
    lowsalary  INT UNSIGNED NOT NULL COMMENT '最低薪资',
    highsalary INT UNSIGNED NOT NULL COMMENT '最高薪资'
) COMMENT '薪资表';
TRUNCATE TABLE tb_salary_grade;

INSERT INTO tb_salary_grade(grade, lowsalary, highsalary)
VALUES (1, 0, 3000),
       (2, 3001, 5000),
       (3, 5001, 8000),
       (4, 8001, 10000),
       (5, 10001, 15000),
       (6, 15001, 20000),
       (7, 20001, 25000),
       (8, 25001, 30000);


-- 接下来完成相应的SQL练习

-- 1、查询员工的姓名、年龄、职位和部门信息
-- (1)显式内连接
SELECT e.name AS '姓名', e.age AS '年龄', e.job AS '职位', d.name AS '部门'
FROM tb_emp AS e
         INNER JOIN tb_dept AS d ON e.dept_id = d.id;
-- (2)隐式内连接
SELECT e.name AS '姓名', e.age AS '年龄', e.job AS '工作', d.name AS '部门'
FROM tb_emp AS e,
     tb_dept AS d
WHERE e.dept_id = d.id;

-- 2、查询年龄小于30岁的员工姓名、年龄、职位和部门信息
-- (1)显式内连接
SELECT e.name AS '姓名', e.age AS '年龄', e.job AS '职位', d.name AS '部门'
FROM tb_emp AS e
         INNER JOIN tb_dept AS d ON e.dept_id = d.id
WHERE e.age < 30;
-- (2)隐式内连接
SELECT e.name AS '姓名', e.age AS '年龄', e.job AS '职位', d.name AS '部门'
FROM tb_emp AS e,
     tb_dept AS d
WHERE e.dept_id = d.id
  AND e.age < 30;

-- 3、查询拥有员工的部门ID和部门名称
SELECT DISTINCT d.id AS 'ID', d.name AS '部门'
FROM tb_dept AS d
         INNER JOIN tb_emp AS e ON d.id = e.dept_id
ORDER BY d.id ASC;

-- 4、查询所有年龄大于40岁的员工，及其归属的部门名称；如果员工没有分配部门，也要显示出来
SELECT e.*, d.name AS '部门'
FROM tb_emp AS e
         LEFT OUTER JOIN tb_dept AS d ON e.dept_id = d.id
WHERE e.age > 40
ORDER BY e.id ASC;

-- 5、查询所有员工的工资等级
-- (1)显式内连接
SELECT te.*, tsg.grade AS '薪资等级', tsg.lowsalary AS '最低薪资', tsg.highsalary AS '最高薪资'
FROM tb_emp AS te
         INNER JOIN tb_salary_grade AS tsg ON te.salary BETWEEN tsg.lowsalary AND tsg.highsalary;
-- (2)隐式内连接
SELECT te.*, tsg.grade AS '薪资等级', tsg.lowsalary AS '最低薪资', tsg.highsalary AS '最高薪资'
FROM tb_emp AS te,
     tb_salary_grade AS tsg
WHERE te.salary BETWEEN tsg.lowsalary AND tsg.highsalary;

-- 6、查询"研发部"所有员工的信息及工资等级
-- (1)显式内连接
SELECT te.*, tsg.grade AS '薪资等级', tsg.lowsalary AS '最低薪资', tsg.highsalary AS '最高薪资'
FROM tb_emp AS te
         INNER JOIN tb_salary_grade AS tsg ON te.salary BETWEEN tsg.lowsalary AND tsg.highsalary
WHERE te.dept_id = (SELECT id FROM tb_dept WHERE name = '研发部');
-- (2)隐式内连接
SELECT te.*, tsg.grade AS '薪资等级', tsg.lowsalary AS '最低薪资', tsg.highsalary AS '最高薪资'
FROM tb_emp AS te,
     tb_salary_grade AS tsg
WHERE te.salary BETWEEN tsg.lowsalary AND tsg.highsalary
  AND te.dept_id = (SELECT id FROM tb_dept WHERE name = '研发部');

-- 7、查询"研发部"员工的平均工资
SELECT AVG(te.salary) AS '平均薪资'
FROM tb_emp AS te
WHERE te.dept_id = (SELECT id FROM tb_dept WHERE name = '研发部');

-- 8、查询工资比"灭绝"高的员工信息
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE salary > (SELECT salary FROM tb_emp WHERE name = '灭绝');

-- 9、查询比平均薪资高的员工信息
-- 需要注意的是，在WHERE中是不能使用聚合函数的，这个之前说过，但是我们可以以嵌套的方式把平均值算出来，作为我们WHERE的判断条件
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE salary > (SELECT AVG(salary) FROM tb_emp);

-- 10、查询低于本部门平均薪资的员工信息
-- 查询某个部门的平均薪资
SELECT AVG(salary)
FROM tb_emp AS te
WHERE te.dept_id = 1;
-- 这里有个技巧，那就是使用tb_emp表的dept_id字段当作我们每次查询的薪资所需获取的部门
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id,
       (SELECT AVG(salary) FROM tb_emp WHERE dept_id = te.dept_id) AS '部门平均薪资'
FROM tb_emp AS te
WHERE te.salary < (SELECT AVG(salary) FROM tb_emp WHERE dept_id = te.dept_id);

-- 11、查询所有的部门信息，并统计部门的员工人数
SELECT COUNT(id)
FROM tb_emp
WHERE dept_id = 1;

-- 同样也是用到第10题的技巧
SELECT td.name AS '部门名称', (SELECT COUNT(id) FROM tb_emp WHERE dept_id = td.id) AS '员工个数'
FROM tb_dept AS td;

-- 12、查询所有学生的选课情况，展示出学生姓名、学号和课程名称
-- 对于多对多的查询，两个表消除笛卡尔积就需要两个条件
-- 表：tb_course、tb_student和tb_student_course
-- 满足的条件：课程的ID要在中间表中出现，并且学生的ID也在中间表出现，当两者同时满足时，则就代表这一条数据有效
-- (1)显式内连接
/*
    这里使用了两次显式内连接，其实道理也是一样的，先ts与tsc进行显式内连接，tsc就可以访问"ts.id = tsc.studentid"筛选
    后的数据，再与tc进行内连接，则tc就可以访问"tc.id = tsc.courseid"筛选后的数据，最后逻辑行所筛选的结果一定是
    同时满足："ts.id = tsc.studentid"和"tc.id = tsc.courseid"条件的
*/
SELECT ts.name AS '姓名', ts.studentid AS '学号', tc.name AS '课程名称'
FROM tb_student AS ts
         INNER JOIN tb_student_course AS tsc ON ts.id = tsc.studentid
         INNER JOIN tb_course AS tc ON tc.id = tsc.courseid;
-- (2)隐式内连接
SELECT ts.name AS '姓名', ts.studentid AS '学号', tc.name AS '课程名称'
FROM tb_student AS ts,
     tb_student_course AS tsc,
     tb_course AS tc
WHERE ts.id = tsc.studentid
  AND tc.id = tsc.courseid;
