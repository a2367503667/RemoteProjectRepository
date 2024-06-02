CREATE DATABASE IF NOT EXISTS test04 DEFAULT CHARSET utf8mb4;
USE test04;
/*
    项目开发中，在进行数据库表结构设计时，会根据业务需求及业务模块之间的关系，分析请设计表结构
    由于业务之间相互关联，所以各个表结构之间也存在着各种联系，基本就分为三种：'一对多'('多对一')、'多对多'和'一对一'

    (1)一对多(多对一)
    案例：部门与员工之间的关系
    关系：一个部门对应多个员工(一对多)，一个员工只能对应一个部门
    实现方式：在'多'的一方创建外键，指向'一'的一方的主键

    (2)多对多
    案例：学生与课程之间的关系
    关系：一个学生可以选择多门课程，一门课程可以被多个学生选择
    实现方式：创建'第三张表'作为中间表，中间表必须有两个外键，分别关联着两方的主键

    之所以需要创建'第三张表'的本质是，我们一个表需要对应两种信息，我就拿学生表举例
    假设在学生表中创建了外键，尝试去关联课程表，我们每一个学生就需要存储两个数据，一个是学生选修的课程
    另一个是学生选课程的个数，也就是说一个学生可以选多门课程，但是我们一个学生代表学生表中的一行，这一行
    也只有一个外键信息，一个外键信息最多只能对应一个课程，没办法对应多个课程，也就是每一行的外键都只能是课程
    id的其中一个值(如果是1，就不能是2，这个可以看外键的章节)，这样就出现问题了，我们没办法一行的学生信息保存
    多个课程信息，这个才是本质问题，所以我们只能通过'第三张表'作为中间表且提供这两个表的外键，然后实现信息的存储
    而'第三张表'可以解决这个问题，是因为'第三张表'解决了我们的一行不能存多个信息的问题，当我们选定一个学生，那就可以
    针对这个学生存储多行，然后再到下一个学生再存储多行，这样就能够解决一行不能存储多个数据的问题了(这种现象也成为笛卡尔积)

    (3)一对一
    案例：用户与用户详情的关系
    关系：一对一关系，多用于单标的拆分，将一张表的基础字段放在一张表中，其他详情信息字段放在另一个表中，以提高操作效率
    实现方式：在任意一方加入外键，关联另一方的主键，并且设置外键为唯一的(UNIQUE)，一般设置外键的都是详情信息表，取关联基础信息表

    因此，对于外键来说，只能解决'一对多'和'一对一'的问题，'多对多'问题需要引入第三张表进行解决

    注：如果我们想通过可视化的形式查看表与表之间的关系，我们可以在'数据库资源管理器'中，找到数据库中的含有'外键'的表，进行
    鼠标右键，找到'图'，然后再点'显示图'即可
*/

-- 多表关系的演示(一对多就不做演示了，因为在外键章节里面所指出的就是一对多模型)
-- 1、多对多
-- (1)创建学生表
CREATE TABLE IF NOT EXISTS tb_student
(
    id        INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    name      VARCHAR(16) NOT NULL COMMENT '姓名',
    studentid VARCHAR(16) NOT NULL UNIQUE COMMENT '学生学号'
) COMMENT '学生表';
TRUNCATE TABLE tb_student;
-- DROP TABLE IF EXISTS tb_student;
INSERT INTO tb_student(name, studentid)
VALUES ('黛绮丝', '2000100101'),
       ('谢逊', '2000100102'),
       ('殷天正', '2000100103'),
       ('韦一笑', '2000100104');

-- (2)创建课程表
CREATE TABLE IF NOT EXISTS tb_course
(
    id   INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    name VARCHAR(16) NOT NULL UNIQUE COMMENT '课程名'
) COMMENT '课程表';
TRUNCATE TABLE tb_course;
-- DROP TABLE IF EXISTS tb_course;
INSERT INTO tb_course(name)
VALUES ('java'),
       ('PHP'),
       ('MySQL'),
       ('Hadoop'),
       ('C++');

-- (3)第三张表(用来维护'学生-课程'关系的，并且第三张表的命名规则一般为'第一张表-第二张表')
CREATE TABLE IF NOT EXISTS tb_student_course
(
    id        INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    studentid INT UNSIGNED NOT NULL COMMENT '学生学号',
    courseid  INT UNSIGNED NOT NULL COMMENT '课程号',
    CONSTRAINT fk_tb_student_course_studentid FOREIGN KEY (studentid) REFERENCES tb_student (id) ON UPDATE NO ACTION ON DELETE RESTRICT,
    -- 因为studentid和courseid都设置为NOT NULL，所以下面外键行为不能使用SET NULL，只能使用NO ACTION、RESTRICT和CASCADE外键行为
    CONSTRAINT fk_tb_student_course_courseid FOREIGN KEY (courseid) REFERENCES tb_course (id) ON UPDATE CASCADE ON DELETE CASCADE
) COMMENT '学生-课程中间表';
TRUNCATE TABLE tb_student_course;
-- DROP TABLE IF EXISTS tb_student_course;
INSERT INTO tb_student_course(studentid, courseid)
VALUES (1, 1),
       (1, 2),
       (1, 3),
       (2, 2),
       (2, 3),
       (3, 4);


-- 2、一对一
/*
    通常'一对一'是将一个表拆开两个表的，因为一个表中含大量数据会影响查找速度，并且也不便于维护和更新，所以我们会
    习惯性把一个很复杂的表拆开，两个或多个表，这样有助于我们查找和维护，并且我们通常会按'基础数据'和'详情数据'进行
    拆分，在'详情表'中添加外键去关联'基础表'
*/
-- (1)创建用户基本信息表
CREATE TABLE IF NOT EXISTS tb_user
(
    id        INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    name      VARCHAR(16) NOT NULL COMMENT '姓名',
    age       TINYINT UNSIGNED CHECK (age >= 0 AND age <= 150) COMMENT '年龄',
    gender    CHAR(1)     NOT NULL COMMENT '性别',
    telephone CHAR(11)    NOT NULL UNIQUE COMMENT '电话号码'
) COMMENT '用户表基本信息表';
TRUNCATE TABLE tb_user;

-- (2)创建用户详情表
CREATE TABLE IF NOT EXISTS tb_user_spc
(
    id            INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    degree        VARCHAR(16) COMMENT '学历',
    major         VARCHAR(16) COMMENT '专业',
    primaryschool VARCHAR(16) COMMENT '小学',
    middleschool  VARCHAR(16) COMMENT '中学',
    university    VARCHAR(16) COMMENT '大学',
    user_id       INT UNSIGNED NOT NULL UNIQUE COMMENT '用户ID',
    CONSTRAINT fk_tb_user_spc_user_id FOREIGN KEY (user_id) REFERENCES tb_user (id) ON UPDATE CASCADE ON DELETE CASCADE
) COMMENT '用户教育信息表';
TRUNCATE TABLE tb_user_spc;

-- (3)给上面的两个表插入数据
INSERT INTO tb_user(name, age, gender, telephone)
VALUES ('黄渤', 45, '男', '18800001111'),
       ('冰冰', 35, '女', '18800002222'),
       ('码云', 55, '男', '18800008888'),
       ('李彦宏', 50, '男', '18800009999');

INSERT INTO tb_user_spc(degree, major, primaryschool, middleschool, university, user_id)
VALUES ('本科', '舞蹈', '静安区第一小学', '静安区第一中学', '北京舞蹈学院', 1),
       ('硕士', '表演', '朝阳区第一小学', '朝阳区第一中学', '北京电影学院', 2),
       ('本科', '英语', '杭州市第一小学', '杭州市第一中学', '杭州师范大学', 3),
       ('本科', '应用数学', '阳泉区第一小学', '阳泉区第一中学', '清华大学', 4);
