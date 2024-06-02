USE test04;
/*
       联合查询（Union Query）是一种在SQL中使用的查询技术，它允许你将两个或多个表的查询结果合并成一个
    结果集。这种查询特别适用于当你需要从多个表中获取数据，而这些表的结构相似或具有相同的列时。想象一下，你有两个篮子，每个篮子里都装有不
    同种类的水果。如果你想要一个包含所有水果的篮子，你可以简单地将两个篮子的水果倒在一起。在SQL中，这个“倒在一起”的动作就是联合查询。
    具体来说，联合查询的步骤如下：
    (1)准备篮子（表）：首先，你需要两个或多个表，这些表至少有一个共同的列（比如水果的种类）。
    (2)选择水果（查询）：然后，你需要对每个表进行查询，选择你想要的水果（即数据）。这些查询应该返回相同数量的列，并且对应
       的列应该具有兼容的数据类型。
    (3)倒在一起（联合）：最后，你使用UNION操作符将这些查询的结果合并在一起。UNION会自动去除重复的行，如果你想保留所有行，包
       括重复的，可以使用UNION ALL。

    注：
    (1)对于联合查询的多张表的列数必须保持一致，字段类型也需要保持一致；
    (2)UNION ALL会将全部的数据直接合并在一起，UNION会对合并之后的数据进行去重
*/
-- UNION ALL查询
-- 1、将薪资低于5000的员工和年龄大于50岁的员工全部查询出来
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE salary < 5000
UNION ALL
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE age > 50;

-- UNION查询
-- 我们发现上面查询到'鹿杖客'信息由两条重复的，那就是说上面的查询(UNION ALL)是没有去重的，只是
-- 简单把上面SELECT表和下面SELECT表直接缝合起来，如果我们需要去重，此时就需要使用UNION
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE salary < 5000
UNION
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE age > 50;

-- UNION ALL和UNION查询是有条件的，如果我们查询的字段的数量、种类和顺序不同的时候，是没办法使用联合查询的，如下：
-- 这样进行联合查询会发生报错
SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp
WHERE salary < 5000
UNION
SELECT name
FROM tb_emp
WHERE age > 50;
