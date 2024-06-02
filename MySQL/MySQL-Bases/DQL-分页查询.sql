/*
    分页查询在页面中见得很多，尤其是我们想看那一页的数据，这样就会选到对应的那一页
    数据进行查看，而且也会规定每一页的数据有多少条，好比如：我们有1万条记录，一下子显示
    一万条记录会影响我们阅读，并且也不好查找数据，对用户就会不友好，所以我们会将一万条数据
    拆分成很多页，然后每一页固定的条数的数据(例：分100页，每页100条数据)

    注：MySQL的分页查询的起始索引是从0开始算的，并且"起始索引 = (页数 - 1)*每页显示记录数"
        其中需要用到LIMIT关键字，但是这个关键字属于MySQL的方言，也就是说其他数据库是不能使用的。

    语法为：SELECT 字段名1, 字段名2, ... FROM 表名 LIMIT 起始索引, 每页显示条数
*/
-- 分页查询
-- 1、查询第1页员工数据，每页展示10条记录
-- 书写格式为：SELECT 字段名1, 字段名2, ... FROM 表名 LIMIT 0, 10;
SELECT id, worknum, name, gender, age, idcard, workaddress, entrydate FROM emp LIMIT 0, 10;
-- 或者为：SELECT 字段名1, 字段名2, ... FROM emp LIMIT 10;(因为查询第1页时，起始索引计算后的结果为0，这时就不需要写0，直接写10即可)
SELECT id, worknum, name, gender, age, idcard, workaddress, entrydate FROM emp LIMIT 10;

-- 2、查询第2页员工数据，每页展现10条记录
-- 书写格式为：SELECT 字段名1, 字段名2, ... FROM 表名 LIMIT 10, 10;
SELECT id, worknum, name, gender, age, idcard, workaddress, entrydate FROM emp LIMIT 10, 10;
