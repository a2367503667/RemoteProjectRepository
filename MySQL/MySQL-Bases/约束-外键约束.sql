USE test03;
/*
    外键用来让两张表的数据之间建立连接，使得两张表在物理层面上(数据库层面上)有联系，从而保证数据的一致性和完整性

    通俗的讲，本来两张表在逻辑上的存在关系的，就好比如：员工表与部门表
    但是，实际在物理存储上是没有任何联系的，我在部门表中删除一个部门之后
    对于员工表来说毫无变化，但是这样是不合理的，因为部门都没有了，员工表
    又怎么能有员工呢，所以我们应该将员工表和部门表在物理上也关联起来，当我们对
    员工表或者部门表进行操作时，两者表中的数据也应该相应地进行变化和调整，这样才会
    引入外键的概念

    补充：存在外键的表叫'子表'，被关联到主键的表为'父表'
*/

-- 准备数据
-- 1、创建部门表
CREATE TABLE IF NOT EXISTS tb_dept
(
    id   INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '编号',
    name VARCHAR(16) NOT NULL UNIQUE COMMENT '部门名称'
) COMMENT '部门表';

TRUNCATE TABLE tb_dept;
-- DROP TABLE IF EXISTS tb_dept;

INSERT INTO tb_dept(name)
VALUES ('研发部'),
       ('市场部'),
       ('财务部'),
       ('销售部'),
       ('总经办');

SELECT id, name
FROM tb_dept;

-- 2、创建员工表
CREATE TABLE IF NOT EXISTS tb_emp
(
    id        INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '员工编号',
    name      VARCHAR(32)  NOT NULL COMMENT '姓名',
    age       TINYINT UNSIGNED CHECK (age >= 0 AND age <= 130) COMMENT '年龄',
    job       VARCHAR(16)  NOT NULL COMMENT '工作',
    salary    INT UNSIGNED NOT NULL COMMENT '薪资',
    entrydate DATE         NOT NULL COMMENT '入职时间',
    managerid INT UNSIGNED COMMENT '直属领导ID',
    dept_id   INT UNSIGNED COMMENT '部门ID'
) COMMENT '员工表';

TRUNCATE TABLE tb_emp;
-- DROP TABLE IF EXISTS tb_emp;

INSERT INTO tb_emp(name, age, job, salary, entrydate, managerid, dept_id)
VALUES ('金庸', 66, '总裁', 20000, '2000-01-01', null, 5),
       ('张无忌', 20, '项目经理', 12500, '2005-12-05', 1, 1),
       ('杨逍', 33, '开发', 8400, '2000-11-03', 2, 1),
       ('韦一笑', 48, '开发', 11000, '2002-02-05', 2, 1),
       ('常遇春', 43, '开发', 10500, '2004-09-07', 3, 1),
       ('小昭', 19, '程序员鼓励师', 6600, '2004-10-12', 2, 1);

SELECT id,
       name,
       age,
       job,
       salary,
       entrydate,
       managerid,
       dept_id
FROM tb_emp;

-- 现在已经创建好两个表了(员工表和部门表)，但是他们只有逻辑上有联系，物理上没有联系，即接下来创建外键
-- 3、给员工表添加外键
-- 书写格式为：ALTER TABLE 子表名 ADD CONSTRAINT 外键名 FOREIGN KEY (关联到父表的id名) REFERENCES 父表(主键字段名);
-- 其中，子表和父表在最开始的时候已经讲过了，本表为子表，被关联主键的为父表，需要记住的是要加括号
-- 还有就是外键名的组成一般都是由'fk_子表名_关联到父表的id名'，其中fk代表外键的意思
ALTER TABLE tb_emp
    ADD CONSTRAINT fk_tb_emp_dept_id FOREIGN KEY (dept_id) REFERENCES tb_dept (id);

-- 上面那种是通过ALTER TABLE ... ADD ...的方式添加外键，我们还可以在创建表的时候就给其添加外键，如下：
/*
    直接在表中写：CONSTRAINT fk_tb_emp_dept_id FOREIGN KEY (dept_id) REFERENCES tb_dept(id)
    其实和我们平时创建字段是一个道理的，只不过添加外键有对应的关键字，仅此而已
*/

SHOW CREATE TABLE tb_emp;

DELETE
FROM tb_dept
WHERE id = 1;

-- 4、删除外键
-- 书写格式为：ALTER TABLE 表名 DROP FOREIGN KEY 外键名;
ALTER TABLE tb_emp
    DROP FOREIGN KEY fk_tb_emp_dept_id;
-- 或者为：ALTER TABLE 表名 DROP CONSTRAINT 外键名;
-- 因为CONSTRAINT关键字是给约束起别名的，别名就是fk_tb_emp_dept_id，所以我们使用CONSTRAINT关键字删除约束即可
-- 但是建议使用上面FOREIGN KEY的方式进行删除，这个才是MySQL标准删除的方法，当然，下面这种也可以，并且下面这种删除方法
-- 也适用于某些数据库系统，这个看个人习惯，不过还是规范写法最好
ALTER TABLE tb_emp
    DROP CONSTRAINT fk_tb_emp_dept_id;
