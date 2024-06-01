/*
    在DML中，是用于对表中的数据进行处理的，所以我们会用到对应的关键字有如下：
    INSERT UPDATE和DELETE对数据进行处理

    注：对于字符串来说，在MySQL中要使用''，不要使用""
 */
USE test01;

TRUNCATE TABLE emp;

-- 数据查询语句
SELECT id, worknum, name, gender, age, idcard, entertime
FROM emp;

-- 1、往emp表中插入1条数据(带字段列表)
-- 书写格式为：INSERT INTO 表名(字段列表) VALUES(字段对应的值);
INSERT INTO emp(id, worknum, name, gender, age, idcard, entertime)
VALUES (1, '1', '张三', '男', 19, '441283200001016411', '2024-01-01');

-- 2、往emp表插入1条数据(不带字段列表)
-- 书写格式为：INSERT INTO 表名 VALUES(字段对应的值);
INSERT INTO emp
VALUES (2, '2', '李四', '女', 18, '441283200001016412', '2024-05-01');

-- 3、往emp插入2条及以上数据(带字段列表)
-- 书写个数为：INSERT INTO 表名(字段列表) VALUES(字段对应的值1), (字段对应的值2)...;
INSERT INTO emp(id, worknum, name, gender, age, idcard, entertime)
VALUES (3, '3', '王五', '男', 20, '441283200001016413', '2024-02-01'),
       (4, '4', '赵六', '女', 20, '441283200001016414', '2024-04-01');

-- 4、往emp插入2条及以上数据(不带字段列表)
-- 书写格式为：INSERT INTO 表名 VALUES(字段对应的值1), (字段对应的值2)...;
INSERT INTO emp
VALUES (5, '5', '周七', '女', 21, '441283200001016416', '2024-03-01'),
       (6, '6', '老八', '男', 22, '441283200001016419', '2024-03-01');
