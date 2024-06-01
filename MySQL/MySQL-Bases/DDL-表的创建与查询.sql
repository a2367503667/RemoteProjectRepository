-- 使用test01数据库
USE test01;

/*
    创建一个员工表
    其中，COMMENT是代表说明，也就是解释前面的每个字段的
    最后外面的COMMENT是用来解释这个是什么表的，这些都是
    便于我们阅读添加上去的而已，对代码执行不会有影响

    简单来说，COMMENT就是一个注释，用于解释说明
*/
CREATE TABLE tb_user(
    id INT UNSIGNED COMMENT "编号",
    name VARCHAR(20) COMMENT "姓名",
    age TINYINT UNSIGNED COMMENT "年龄",
    gender CHAR(1) COMMENT "性别"
) COMMENT "用户表";

-- 查看当前所使用的数据库中有什么表
SHOW TABLES;

-- 查看tb_user表结构，也就是查看tb_user表的字段信息
DESC tb_user;

-- 如果想查看更多的tb_user表结构信息或者创建tb_user表的信息，就需要执行下面SQL语句，执行之后会显示下面的信息
/*
CREATE TABLE `tb_user` (
  `id` int unsigned DEFAULT NULL COMMENT '编号',
  `name` varchar(20) DEFAULT NULL COMMENT '姓名',
  `age` tinyint unsigned DEFAULT NULL COMMENT '年龄',
  `gender` char(1) DEFAULT NULL COMMENT '性别'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='用户表'

ENGINE=InnoDB 这个是存储引擎
DEFAULT CHARSET=utf8mb4 这个是默认字符集
COLLATE=utf8mb4_0900_ai_ci 这个是排序规则
COMMENT='用户表' 这个是表注释
*/
SHOW CREATE TABLE tb_user;
