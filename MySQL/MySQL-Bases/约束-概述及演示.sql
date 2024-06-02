CREATE DATABASE IF NOT EXISTS test03 DEFAULT CHARSET utf8mb4;
USE test03;
/*
    有时候我们的字段是不能够随意写的，就好比如id字段，我们不能为null，age字段中的数据必须要合法等
    因此，我们就需要对表中的字段添加相应的约束
    1、概念：约束是作用于表中字段上的规则，用于限制存储在表中的数据
    2、目的：保证数据库中数据的正确性、有效性和完整性

    约束                            描述                                                    关键字
    非空约束                        限制该字段的数据不能为null                                 NOT NULL
    唯一约束                        保证该字段的所有数据都是唯一、不重复的                        UNIQUE
    主键约束                        主键是一行数据的唯一表示，要求非空且唯一                      PRIMARY KEY
    默认约束                        保存数据时，如果未指定该字段的值，则采取默认值                 DEFAULT
    检查约束(8.0.16版本之后才可用)    保证字段值满足某一个条件                                    CHECK
    外键约束                        用来让两张表的数据之间建立连接，保证数据的一致性和完整性         FOREIGN KEY

    注：
    (1)约束是作用于表中的字段上的，可以在创建表/修改表的时候添加约束
    (2)在MySQL中，自动增长的关键字为AUTO_INCREMENT
    (3)CONSTRAINT关键字是用来给约束起别名的，它有助于我们对约束进行修改和删除，不过在
    使用CONSTRAINT关键字起的别名时，对约束进行修改需要加上CONSTRAINT关键字，如下：
    CREATE TABLE tb_user( ... CONSTRAINT my_unique UNIQUE COMMENT '唯一约束', ...);
    ALTER TABLE tb_user DROP CONSTRAINT my_unique;
    在删除my_unique约束时，需要加上CONSTRAINT关键字
*/

/*
    需求：创建一个用户表tb_user，并且要求
    id为主键，并且自动增长
    name不为空，并且唯一
    age大于0，并且小于120
    status如果没有指定数值，默认为1
    gender没有特殊要求
*/
CREATE TABLE IF NOT EXISTS tb_user
(
    id     INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '编号',
    name   VARCHAR(10) NOT NULL UNIQUE COMMENT '姓名',
    age    TINYINT UNSIGNED CHECK (age >= 0 AND age <= 120) COMMENT '年龄',
    status CHAR(1) DEFAULT 1 COMMENT '状态',
    gender CHAR(1) COMMENT '性别'
) COMMENT '用户表';
TRUNCATE TABLE tb_user;

SELECT id, name, age, status, gender
FROM tb_user;

-- 插入数据测试
-- 插入数据可以不需要加id，因为id是自动增长的，即使我们赋值，它也会自动增加
INSERT INTO tb_user(name, age, status, gender)
VALUES ('Tmo1', 19, '1', '男'),
       ('Tom2', 25, '0', '男');
INSERT INTO tb_user(name, age, status, gender)
VALUES ('Tom3', 19, '1', '男');

-- name我们设置非空且唯一，尝试一下下面的SQL语句是否会报错
-- (1)会报错，显示Column 'name' cannot null
INSERT INTO tb_user(name, age, status, gender)
VALUES (null, 19, '1', '男');
INSERT INTO tb_user(name, age, status, gender)
VALUES ('Jack', 19, '1', '男');
-- (2)会报错，显示Duplicate entry 'Tom3' for key 'tb_user.name'
/*
    这里需要注意，如果我们将一个设置唯一的数据进行重复插入，会向主键申请id自动增长，这就会出现
    虽然下面'Tom3'会插入失败，但是它也会占用一个id，使得id已经进行了自增，这就会导致当我们插入一条正常的
    数据时，就会出现空出一个id的情况，举个例子：如果我们'Tom3'插入成功，则id的值为5，但是插入失败了，但之后
    'John'插入成功了，它的id就不是5，而是6，这样就会出现空出一个的现象

    这个其实是一个'事务'问题，插入失败的事务回滚：如果你在插入数据时使用了事务，并且插入操作失败，事务可能会被
    回滚。这意味着即使数据库引擎已经为新记录分配了一个 id（例如，从4增加到5），但由于事务回滚，这条记录实际上
    并没有被插入到表中。因此，下一个成功的插入操作将使用下一个可用的 id 值，即6，而不是5，实际上在我们没有设置'事务'的
    时候，每一个SQL语句都代表着一个'事务'，所以这个很大可能是因为'事务回滚但数据库引擎已经为新纪录分配了id'导致的
*/
INSERT INTO tb_user(name, age, status, gender)
VALUES ('Tom3', 19, '1', '男');
INSERT INTO tb_user(name, age, status, gender)
VALUES ('John', 19, '1', '男');

-- 测试一下年龄的约束条件是否生效
INSERT INTO tb_user(name, age, status, gender)
VALUES ('Tom4', 80, '1', '男');
-- 会报错，显示Data truncation: Out of range value for column 'age' at row(这个报错是因为我设置了UNSIGNED)
INSERT INTO tb_user(name, age, status, gender)
VALUES ('Tom5', -1, '1', '男');
-- 会报错，显示Check constraint 'tb_user_chk_1' is violated(这个报错是因为我设置了CHECK)
INSERT INTO tb_user(name, age, status, gender)
VALUES ('Tom5', 121, '1', '男');

-- 测试一下status默认值是否为1
-- 默认值结果确实为1
INSERT INTO tb_user(name, age, gender)
VALUES ('Tom5', 120, '男');
