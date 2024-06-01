USE test01;
SELECT *
FROM emp;

-- 1、修改id为1的数据，将name修改为zhangsan(一次修改一个数据)
-- 书写格式为：UPDATE 表名 SET 字段名 = 值 WHERE 条件;
/*
    需要注意的是，在MySQL中，使用=为相等的含义，如果id = 1即id为1，而且在
    我们没有给修改语句设置WHERE条件时，会把表中的所有数据修改掉，所以我们在写
    修改和删除语句时，要注意加上WHERE条件
 */
UPDATE emp
SET name = 'zhangsan'
WHERE id = 1;

-- 2、修改id为1的数据，将name修改为"小昭"，gender修改为"女"(一次修改多个数据)
-- 书写格式为：UPDATE 表名 SET 字段1 = 值1, 字段2 = 值2,... WHERE 条件;
UPDATE emp
SET name   = '小昭',
    gender = '女'
WHERE id = 1;

-- 3、将所有员工的入职日期改为 2008-01-01(这里是修改全部数据，所以不需要设置WHERE条件)
-- 书写格式为：UPDATE emp SET 字段名 = 值;
-- 但是这种写法一定要谨慎，否则会出现严重的问题，因此要确保没有问题的时候再进行使用
UPDATE emp
SET entertime = '2008-01-01';

/*
    这里需要注意
    (1)如果没有加WHERE条件的话，会默认删除表中所有数据(因此要谨慎操作);
    (2)DELETE没有办法删除个别的数据，也就是说没办法删除某个人的某个信息，如果有这个需求的话
    我们可以使用UPDATE将那个需要修改的个别数据修改成null或者0等数据
 */
-- 4、删除gender为女的员工
-- 书写格式为：DELETE FROM 表名 WHERE 条件;
DELETE
FROM emp
WHERE gender = '女';

-- 5、删除所有员工
-- 书写格式为：UPDATE FROM 表名;
DELETE
FROM emp;
