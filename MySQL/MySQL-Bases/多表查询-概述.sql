USE test04;
/*
    我们之前所学的SQL语句都是单表查询，都是对于一张表来说的，而我们
    现在所学的是向多张表中查询数据，即多表查询
*/
-- 准备数据
-- 1、创建部门表
CREATE TABLE IF NOT EXISTS tb_dept
(
    id   INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    name VARCHAR(16) NOT NULL UNIQUE COMMENT '部门名称'
) COMMENT '部门表';
TRUNCATE TABLE tb_dept;

INSERT INTO tb_dept(name)
VALUES ('研发部'),
       ('市场部'),
       ('财务部'),
       ('销售部'),
       ('总经办'),
       ('人事部');

-- 2、创建员工表
CREATE TABLE IF NOT EXISTS tb_emp
(
    id        INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    name      VARCHAR(16) NOT NULL COMMENT '姓名',
    age       TINYINT UNSIGNED CHECK (age >= 0 AND age <= 150) COMMENT '年龄',
    job       VARCHAR(16)  DEFAULT null COMMENT '职位',
    salary    INT UNSIGNED DEFAULT 0 COMMENT '薪资',
    entrydate DATE        NOT NULL COMMENT '入职日期',
    managerid INT UNSIGNED DEFAULT null COMMENT '直属领导ID',
    dept_id   INT UNSIGNED DEFAULT null COMMENT '部门ID',
    CONSTRAINT age_check CHECK (age >= 0 AND age <= 150),
    CONSTRAINT fk_tb_emp_dept_id FOREIGN KEY (dept_id) REFERENCES tb_dept (id) ON UPDATE CASCADE ON DELETE SET NULL
) COMMENT '员工表';
TRUNCATE TABLE tb_emp;

INSERT INTO tb_emp(name, age, job, salary, entrydate, managerid, dept_id)
VALUES ('金庸', 66, '总裁', 20000, '2000-01-01', null, 5),
       ('张无忌', 20, '项目经理', 12500, '2005-12-05', 1, 1),
       ('杨逍', 33, '开发', 8400, '2000-11-03', 2, 1),
       ('韦一笑', 48, '开发', 11000, '2002-02-05', 2, 1),
       ('常遇春', 43, '开发', 10500, '2004-09-07', 3, 1),
       ('小昭', 19, '程序员鼓励师', 6600, '2004-10-12', 2, 1),
       ('灭绝', 60, '财务总监', 8500, '2002-09-12', 1, 3),
       ('周芷若', 19, '会计', 4800, '2006-06-02', 7, 3),
       ('丁敏君', 23, '出纳', 5250, '2009-05-13', 7, 3),
       ('赵敏', 20, '市场部总监', 12500, '2004-10-12', 1, 2),
       ('鹿杖客', 56, '职员', 3750, '2006-10-03', 10, 2),
       ('鹤笔翁', 19, '职员', 3750, '2007-05-09', 10, 2),
       ('方东白', 19, '职员', 5500, '2009-02-12', 10, 2),
       ('张三丰', 88, '销售总监', 14000, '2004-10-12', 1, 4),
       ('俞莲舟', 38, '销售', 4600, '2004-10-12', 14, 4),
       ('宋远桥', 40, '销售', 4600, '2004-10-12', 14, 4),
       ('陈友谅', 42, null, 2000, '2011-10-12', 1, null);


-- 3、多表查询
/*
    多表查询就是在FROM后面跟多个表即可，但是这样出来的结果是tb_emp和tb_dept联合的结果
    也就是tb_emp的条数和tb_dept的条数的乘积，也称为'笛卡尔积'，其中里面有很多数据都是无用的
    就好比如：'总裁'的数据，他只属于总经办，但是不属于除总经办之外的其他部门，而我们在查询结果
    例看到了他和其他部门的信息，这显然是不合理的，因此我们进行多表查询时，需要对查询的结果进行
    筛选，否则就会出现一些无效或毫无意义的数据

    笛卡尔积：笛卡尔积是指在数学中，集合A和集合B的所在组合情况(在多表查询时，需要消除无效的笛卡尔积)
*/
SELECT tb_emp.id,
       tb_emp.name,
       tb_emp.age,
       tb_emp.job,
       tb_emp.salary,
       tb_emp.entrydate,
       tb_emp.managerid,
       tb_emp.dept_id,
       tb_dept.id,
       tb_dept.name
FROM tb_emp,
     tb_dept;

/*
    接下来就是解决，如何消除无效或无意义的数据？出现无效的数据是因为输出的结果只是两个或多个表的
    乘积，我们需要做的就是找到两个表之间有联系的部分，即可消除无效的数据，其中有联系部分就是我们
    构建的外键关系，只要有对应的外键部分，都是我们有意义的数据，即我们只需要筛选'子表的外键字段'
    与'父表的主键字段'相等的数据即可，例如：上面的tb_emp和tb_dept，有tb_emp.dept_id = tb_dept.id即可
*/
-- 查询结果为16条是因为有一个员工没有对应的部门信息，在筛选时就不满足tb_emp.dept_id = tb_dept.id这个条件
SELECT tb_emp.id,
       tb_emp.name,
       tb_emp.age,
       tb_emp.job,
       tb_emp.salary,
       tb_emp.entrydate,
       tb_emp.managerid,
       tb_emp.dept_id,
       tb_dept.id,
       tb_dept.name
FROM tb_emp,
     tb_dept
WHERE tb_emp.dept_id = tb_dept.id;
