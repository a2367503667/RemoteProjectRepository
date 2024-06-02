USE test04;
/*
        在MySQL中，事务是一组数据库操作，这些操作被视为一个单一的工作单元。这意味着事务中的所有操作要么全部成功
    执行，要么全部不执行。事务的主要作用是确保数据库的完整性和一致性。想象一下，你正在银行进行转账操作，从一个账户
    转出一定金额到另一个账户。这个过程包括两个主要步骤：从第一个账户减去金额，然后在第二个账户增加相同的金额。这两
    个步骤必须作为一个整体来执行，如果只完成了其中一个步骤，在代码的中间出现异常导致程序中断了，这时数据库的状态就
    会不一致，钱从账户A减去了，但账户B没有增加，这显然是不正确的，这时我们就需要用到事务，保证数据执行的完整性。对
    于MySQL来说，事务是默认提交的，也就是说，当你执行SQL语句之后，MySQL就会默认给你提交事务，去更新数据库中的数据。

    事务通过提供四个关键属性来保证这种一致性，通常被称为ACID属性：
    (1)原子性（Atomicity）：事务中的所有操作要么全部完成，要么全部不完成。如果事务中的任何操作失败，整个事务都会回
        滚到初始状态，就像事务从未发生过一样。
    (2)一致性（Consistency）：事务将数据库从一个一致状态转移到另一个一致状态。这意味着事务执行前后，数据库的完整性
        约束没有被破坏。
    (3)隔离性（Isolation）：事务的执行应该与其他同时进行的事务隔离开来。这意味着即使多个事务同时执行，它们之间也不
        会相互干扰。
    (4)持久性（Durability）：一旦事务被提交，其结果应该是永久性的，即使系统发生故障也不会丢失。
        通过使用事务，MySQL可以确保即使在并发操作和系统故障的情况下，数据库也能保持其数据的完整性和一致性。这使得事务成为
    处理复杂数据库操作的关键工具，尤其是在需要确保数据准确性和可靠性的应用中。
*/
-- 数据准备
CREATE TABLE IF NOT EXISTS tb_account
(
    id    INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    name  VARCHAR(16) NOT NULL COMMENT '姓名',
    money INT DEFAULT 0 COMMENT '余额'
) COMMENT '账户表';
TRUNCATE TABLE tb_account;

INSERT INTO tb_account(name, money)
VALUES ('张三', 2000),
       ('李四', 2000);

-- 恢复数据
UPDATE tb_account
SET money = 2000
WHERE name IN ('张三', '李四');

-- 转账操作(张三给李四转账1000)
-- 1、查询张三账户余额
SELECT id, name, money
FROM tb_account
WHERE name = '张三';

-- 2、将张三账户余额-1000
UPDATE tb_account
SET money = money - 1000
WHERE name = '张三';

-- 异常点(测试时去除注释)
/*
    在异常点测试时，我们发现张三的钱-1000了，但是李四的钱没有+1000，此时就出问题了，原因
    就出在，在MySQL中，每一个SQL语句都是一个事务，在执行SQL语句后MySQL会帮我们自动提交事务
    也就是说当我们进行UPDATE操作时，就会立即更新数据库中的数据，现在就是在做转账操作时出现错误了
    导致后面的转账操作没有继续执行，也就使得数据丢失了，这就是问题的根源
*/
-- 3、将李四账户余额+1000
UPDATE tb_account
SET money = money + 1000
WHERE name = '李四';

-- 需要注意的是，即使我们事务还没COMMIT，但SELECT出来的结果确实改变后的结果，不过我们需要知道
-- 数据还没COMMIT到数据库上，所以没有真正意义上改变数据库的数据，如果我们进行ROLLBACK操作，SELECT的
-- 结果还是原来还没修改之前的数据，但是如果我们COMMIT后，那就真的把数据提交到数据库了
SELECT id, name, money
FROM tb_account;

-- 那我们如何控制事务呢？
-- 1、手动设置事务的提交方式(修改MySQL设置的默认提交方式)
-- (1)查看事务提交方式(如果为1则是自动提交，为0则是手动提交)
SELECT @@AUTOCOMMIT;
-- (2)设置为手动提交
SET @@AUTOCOMMIT = 0;

-- 当我们设置了手动提交事务，那在运行SQL语句后，需要通过命令来提交事务
COMMIT;
-- 当出现异常的时候，我们需要对代码进行回滚，同样需要代码进行回滚
ROLLBACK;

-- 2、通过开启事务的方式来控制事务(这个用的最多，因为我们一般不会去修改MySQL的系统配置)
-- 开启事务
START TRANSACTION;
-- 执行SQL语句
SELECT * FROM tb_account;
-- 提交事务
COMMIT;

-- 当然，开启事务还有其他写法
-- 开启事务
BEGIN;
SELECT * FROM tb_account;
COMMIT;

-- 同样地，回滚事务也是使用上面的关键字
ROLLBACK;
