/*
    创建一个test01数据库，并设定字符集为utf8mb4，不过我们最好不要设置utf8，因为这个才占用3个字节
    有些文字可能会占用4个字节，这样会使得存储数据出现错误，因此我们不要使用utf8，要使用utf8mb4

    注：在今后的代码中，关键字我们最好都使用大写，自定义的表和字段等使用小写，这个是属于编程习惯
    其实在MySQL中不区分大小写的，但是我们尽量要做到规范
*/
CREATE DATABASE IF NOT EXISTS test01 DEFAULT CHARSET utf8mb4;

-- 展现当前所有数据库
SHOW DATABASES;

-- 显示当前选用的数据库，其中DATABASE()是一个函数，后面会对函数进行讲解
SELECT DATABASE();

-- 表示如果存在test数据库就会将其删除，如果不存在的话，运行下面的SQL命令也不会报错
-- 如果不写IF EXISTS的话，test不存在即会报错
DROP DATABASE IF EXISTS test;

-- 使用数据库test01
USE test01;
