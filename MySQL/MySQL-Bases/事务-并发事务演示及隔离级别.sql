/*
    我们知道事务会引发一些并发事务问题，所以我们需要想方设法去解决它，那么最好的
    处理方式就是使用事务的隔离级别

    隔离级别                 脏读       不可重复读      幻读
    READ UNCOMMITTED        TRUE        TRUE        TRUE
    READ COMMITTED          FALSE       TRUE        TRUE
    REPEATABLE READ(默认)    FALSE       FALSE       TRUE
    SERIALIZABLE            FALSE       FALSE       FALSE
    (TRUE代表会出现，FALSE代表不会出现)

    分别是：读未提交、读已提交、可重复读和串行化
    其中设置隔离级别都是属于会话级别的，即如下：
    SET SESSION TRANSACTION ISOLATION LEVEL SERIALIZABLE;
    START TRANSACTION;
    SQL语句...
    COMMIT;
    串行化隔离级别只在START TRANSACTION与COMMIT之间有效

    而隔离级别越高，性能就越差，但安全性越高；相反，隔离级别越低，性能越好，但安全性越差
*/

-- 1、查看事务的隔离级别
SELECT @@TRANSACTION_ISOLATION;

-- 2、设置事务的隔离级别
-- 书写格式为：SET [SESSION|GLOBAL] TRANSACTION ISOLATION LEVEL [READ UNCOMMITTED|READ COMMITTED|REPEATABLE READ|SERIALIZABLE]
-- 如果指定的是SESSION的话是设置部分会话级别，指的是当前客户端窗口有效；如果指定的是GLOBAL的话是设置全局会话级别，指定是所有会话窗口有效
-- 1、设置隔离级别为读未提交
SET SESSION TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;

-- 2、设置隔离级别为读已提交
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- 3、设置隔离级别为可重复读
SET SESSION TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- 4、设置隔离级别为串行化
SET SESSION TRANSACTION ISOLATION LEVEL SERIALIZABLE;
