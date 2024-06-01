-- 使用test01数据库
USE test01;

-- 先查询当前数据库有什么表
SHOW TABLES;

-- 查看表结构
DESC emp;

-- 我们对上一次创建的emp表进行修改
-- 1、个体emp表添加一个新字段"昵称"为nickname，类型是varchar(20)
-- 给表添加字段的SQL语句格式为：ALTER TABLE 表名 ADD 新字段名 新字段类型 COMMENT "解释";
ALTER TABLE emp
    ADD nickname VARCHAR(20) COMMENT "昵称";

-- 2、修改字段类型(对于MODIFY来说，只能修改字段类型，不能修改字段名)
-- 将员工工号的最大长度10，改成最大长度25
ALTER TABLE emp
    MODIFY worknum VARCHAR(25) COMMENT "员工工号";

-- 3、修改字段名和字段类型(对于CHANGE来说，可以修改字段名和字段类型，允许单独修改也允许一同修改)
-- 将emp表的nickname字段改成username字段，并且将字段类型改成VARCHAR(30)
-- 书写格式为：ALTER TABLE 表名 CHANGE 旧字段名 新字段名 新字段类型(如果不需要改就写原来的即可) COMMENT "解释";
ALTER TABLE emp
    CHANGE nickname username VARCHAR(30) COMMENT "用户名";

-- 4、将emp表的字段username删除
-- 书写格式为：ALTER TABLE 表名 DROP 字段名;
ALTER TABLE emp
    DROP username;

-- 5、修改表名
-- 书写格式为：ALTER TABLE 表名 RENAME TO 新表名;
ALTER TABLE emp RENAME TO employee;
DESC employee;
-- 改回来避免程序显示报错
ALTER TABLE employee RENAME TO emp;

/*
    需要注意，删除表意味着也会把数据删除，所以删除表需要谨慎操作
 */
-- 6、删除表
-- 书写格式为：ALTER TABLE IF EXISTS 要删除的表名;
DROP TABLE IF EXISTS tb_temp;

-- 7、删除指定表，并重新创建该表(也就是说把选定的表删除，然后创建一个和当前表结构一样的且同名的表)
-- TRUNCATE TABLE 表名;
TRUNCATE TABLE tb_user;
