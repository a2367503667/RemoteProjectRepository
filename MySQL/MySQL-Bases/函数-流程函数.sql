/*
    流程函数其实是用来提高我们的条件筛选的，它和我们编程语言的if...else或if...if else...else句子很像
    和编程语言中的条件判断作用是一样的

    常用的流程函数有，如下：

    函数                                                                功能
    IF(value, t, f)                                                    如果value为true，则返回t，否则返回f
    IFNULL(value1, value2)                                             如果value1不为空，则返回value1，否则返回value2
    COALESCE(value1, value2, ...)                                      返回第一个不为NULL的值，全部为NULL则返回NULL
    CASE WHEN [val1] THEN [res1] ... ELSE [default] END                如果val1为true，返回res1, ...否则返回DEFAULT默认值
    CASE [expr] WHEN [val1] THEN [res1] ... ELSE [default] END         如果expr的值等于val1，返回res1, ...否则返回DEFAULT默认值
*/

-- 1、IF函数
SELECT IF(TRUE, 'That\'s true', 'That\'s error');
SELECT IF(FALSE, 'That\'s true', 'That\'s error');

-- 2、IFNULL函数
SELECT IFNULL('hello', 'MySQL');
-- 注：空串不是NULL，所以这里返回的是空串''而不是MySQL
SELECT IFNULL('', 'MySQL');
SELECT IFNULL(NULL, 'MySQL');

-- 3、COALESCE函数
SELECT COALESCE('hello');
SELECT COALESCE(NULL, 'hello', 'MySQL');
SELECT COALESCE(NULL, NULL, 'MySQL');
SELECT COALESCE(NULL, NULL, NULL);

-- 4、CASE [expr] WHEN [val1] THEN [res1] ... ELSE [DEFAULT] END
-- 需求：查询emp表的员工姓名和工作地址(北京/上海 ---> 一线城市，其他 ---> 二线城市)
-- (1)写法1
SELECT name                                                                                           AS '姓名',
       (CASE workaddress WHEN '北京' THEN '一线城市' WHEN '上海' THEN '一线城市' ELSE '二线城市' END) AS '城市等级'
FROM emp;
-- 需要注意的是，上面这样写有一个缺点，那就是CASE后面的值只能匹配到WHEN后面的值，这样如果个数多起来就不太好操作了
-- 我们可以使用另一个书写方式，将整一个判断式子放在WHEN后面，这样判断起来更加简洁和方便
-- (2)写法2
SELECT name AS '姓名', (CASE WHEN workaddress IN ('北京', '上海') THEN '一线城市' ELSE '二线城市' END) AS '城市等级'
FROM emp;
-- 其实按照写法2的方式，可以把CASE改成IF的方式，这样也是很简洁
SELECT name AS '姓名', IF(workaddress IN ('北京', '上海'), '一线城市', '二线城市') AS '城市等级'
FROM emp;


-- 5、数据准备
CREATE TABLE IF NOT EXISTS tb_score
(
    id      INT UNSIGNED COMMENT 'ID',
    name    VARCHAR(20) COMMENT '姓名',
    math    INT UNSIGNED COMMENT '数学',
    English INT UNSIGNED COMMENT '英语',
    Chinese INT UNSIGNED COMMENT '语文'
) COMMENT '学生成绩表';
TRUNCATE TABLE tb_score;
INSERT INTO tb_score(id, name, math, English, Chinese)
VALUES (1, 'Tom', 67, 88, 95),
       (2, 'Rose', 23, 66, 90),
       (3, 'Jack', 56, 98, 76);
-- CASE WHEN [val1] THEN [res1] ... ELSE [DEFAULT] END
/*
    统计班级各个学员的成绩，展示的规则如下：
    (1) >= 85，显示优秀
    (2) >= 60，显示及格
    (3) 否则显示不及格
*/
SELECT id                                                                                                      AS '编号',
       name                                                                                                    AS '姓名',
       (CASE
            WHEN math >= 85 THEN '优秀'
            WHEN math >= 60 AND math < 85 THEN '及格'
            ELSE '不及格' END)                                                                                 AS '数学',
       (CASE
            WHEN English >= 85 THEN '优秀'
            WHEN English >= 60 AND English < 85 THEN '及格'
            ELSE '不及格' END)                                                                                 AS '英语',
       (CASE WHEN Chinese >= 85 THEN '优秀' WHEN Chinese >= 60 AND Chinese < 85 THEN '及格' ELSE '不及格' END) AS '语文'
FROM tb_score;
