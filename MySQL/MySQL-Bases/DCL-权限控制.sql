USE mysql;
/*
    我们给用户创建了账号，但是账号是没有访问其他数据库的权限的，所以我们需要
    对新创建的账号赋予一定的权限，因此我们就要用相应的权限控制语句完成权限分配

    DCL权限有很多，但是常用的就是以下几种：

    权限                      说明
    ALL, ALL PRIVILEGES      所有权限
    SELECT                   查询数据权限
    INSERT                   插入数据权限
    UPDATE                   修改数据权限
    DELETE                   删除数据权限
    ALTER                    修改表权限
    DROP                     删除数据库/表/视图权限
    CREATE                   创建数据库/表

    注：
    (1)多个权限之间，使用逗号分隔；
    (2)授权时，数据库名和表名可以使用*进行通配，代表所有
*/

SELECT * FROM user;
-- 1、查询权限
-- 查询某个用户的权限
-- 查询zhangsan用户的权限
/*
    GRANT USAGE ON *.* TO `zhangsan`@`localhost`这里有一个USAGE
    它代表不授予任何具体的权限，仅仅表示用户可以连接到数据库服务器换句话说，它
    是一个“无权限”的权限，通常用于创建用户而不授予任何具体的权限
*/
SHOW GRANTS FOR 'zhangsan'@'localhost';

-- 2、授予权限
-- 授予zhangsan用户test02数据库中所有表的所有权限
-- 书写格格式为：GRAND 权限列表 ON test02.* TO '用户名'@'主机名';
GRANT ALL PRIVILEGES ON test02.* TO 'zhangsan'@'localhost';

-- 3、撤销权限
-- 撤销zhangsan用户test02数据库中的所有表的权限
-- 书写格式为：REVOKE 权限列表 ON test02.* FROM '用户名'@'主机名';
REVOKE ALL PRIVILEGES ON test02.* FROM 'zhangsan'@'localhost';
