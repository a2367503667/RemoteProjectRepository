USE test04;
/*
    我们除了可以查询交集部分(内连接)，还可以查询相交之前的单独部分，这就是外连接
    而对于外连接又分'左外连接'和'右外连接'

    左/右连接的应用场景通常是，当我们想查询表1的所有数据，而某些信息在表2(如员工的部门信息在dept表里面)
    时，就要用到左外连接，如：先将emp表的所有数据查询出来，然后输出对应dept表的部门名称信息，如果在emp表中有
    员工是没有部门信息的，那我们要输出出来，只不过在对应部门名称信息那里显示null，这样就是一个左外连接案例，
    相对应的右外连接也是如此
*/

-- 1、左外连接：查询表1(左表)的所有数据，且包含表1和表2交集部分的数据
-- 查询查询tb_emp表的所有数据和对应的部门信息(左外连接)
-- 书写格式为：SELECT 字段1, 字段2, ... FROM 表1 LEFT OUTER JOIN 表2 ON 筛选条件;
SELECT te.*, td.name AS '部门名称'
FROM tb_emp AS te
         LEFT OUTER JOIN tb_dept AS td ON te.dept_id = td.id;
-- 或者为：SELECT 字段名1, 字段名2, ... FROM 表1, LEFT JOIN 表2 ON 筛选条件;
SELECT te.*, td.name AS '部门名称'
FROM tb_emp AS te
         LEFT JOIN tb_dept AS td ON te.dept_id = td.id;


-- 2、右外连接：查询表2(右表)的所有数据，且包含表1和表2交集部分的数据
-- 查询tb_dept表的所有数据和对应员工信息(右外连接)
-- 书写格式为：SELECT 字段名1, 字段名2, ... FROM 表名1 RIGHT OUTER JOIN 表名2 ON 筛选条件;
SELECT td.*, te.*
FROM tb_emp AS te
         RIGHT OUTER JOIN tb_dept AS td ON te.dept_id = td.id;
-- 或者为：SELECT 字段名1, 字段名2, ... FROM 表名1 RIGHT JOIN 表名2 ON 筛选条件;
SELECT td.*, te.*
FROM tb_emp AS te
         RIGHT JOIN tb_dept AS td ON te.dept_id = td.id;

-- 在我们实际开发过程中，右外连接用得很少，因为右外连接可以转换成左外连接，如下：
SELECT td.name AS '部门名称', te.*
FROM tb_dept AS td
         LEFT OUTER JOIN tb_emp AS te ON td.id = te.dept_id;
