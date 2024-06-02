USE test02;
-- DQL语句练习
-- 1、查询年龄为20, 21, 22, 23岁的女员工信息
SELECT id, worknum, name, gender, age, idcard, entrydate
FROM emp
WHERE gender = '女'
  AND age IN (20, 21, 22, 23);

-- 2、查询性别为男并且年龄在20-40岁(含)以内的姓名为三个字的员工
SELECT id, worknum, name, gender, age, idcard, entrydate
FROM emp
WHERE gender = '男'
  AND age BETWEEN 20 AND 40
  AND name LIKE '___';

-- 3、统计员工表中年龄小于60岁的男员工和女员工的人数
SELECT gender AS '性别', COUNT(*) AS '人数'
FROM emp
WHERE age < 60
GROUP BY gender;

-- 4、查询所有年龄小于等于35岁员工的姓名和年龄，并对查询结果按年龄升序排序，如果年龄相同按入职时间降序排序
SELECT name AS '姓名', age AS '年龄'
FROM emp
WHERE age <= 35
ORDER BY age ASC, entrydate DESC;

-- 5、查询性别为男且年龄在20-40岁(含)以内的前5个员工信息，对查询的结果按年龄升序排序，年龄相同按入职时间升序排序
SELECT *
FROM emp
WHERE gender = '男'
  AND age BETWEEN 20 AND 40
ORDER BY age ASC, entrydate DESC
LIMIT 0, 5;

/*
    DQL的执行顺序：
    我们所写的SQL语句的顺序是
    SELECT
        字段列表
    FROM
        表名列表
    WHERE
        条件列表
    GROUP BY
        分组字段列表
    HAVING
        分组后条件列表
    ORDER BY
        排序字段列表
    LIMIT
        分页参数

    但是我们的执行顺序并不是上面的顺序
    正在的执行顺序如下：

    FROM                1
        表名列表
    WHERE               2
        条件列表
    GROUP BY            3
        分组字段列表
    HAVING              3
        分组后条件列表
    SELECT              4
        字段列表
    ORDER BY            5
        排序字段列表
    LIMIT               6
        分页参数
*/
