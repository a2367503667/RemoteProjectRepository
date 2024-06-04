/*
    InnoDB存储引擎简介：
        InnoDB是MySQL数据库管理系统中的一个存储引擎，广泛用于需要高可靠性和高性能的应用。InnoDB是MySQL的默认
    存储引擎，自MySQL 5.5版本起，它就被设为默认引擎。它提供了一些关键特性，使其成为许多应用的首选。
*/
/*
    1. 事务支持
        InnoDB支持ACID（原子性、一致性、隔离性、持久性）事务，这对于需要数据一致性的应用非常重要。例如，在银行系统
    中，转账操作必须保证要么全部成功，要么全部失败，这就是事务的原子性。
*/
-- 例子：
CREATE TABLE accounts (
    account_id INT PRIMARY KEY AUTO_INCREMENT,
    account_name VARCHAR(100) NOT NULL,
    balance DECIMAL(10, 2) NOT NULL DEFAULT 0.00,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

START TRANSACTION;
UPDATE accounts SET balance = balance - 100 WHERE account_id = 1;
UPDATE accounts SET balance = balance + 100 WHERE account_id = 2;
COMMIT;
-- 上面的SQL语句表示从账户1转账100元到账户2，如果其中一个更新失败，整个事务会回滚，保证数据的一致性。

/*
    2. 行级锁定
        InnoDB使用行级锁定，而不是表级锁定，这意味着当一个事务在修改一行数据时，其他事务仍然可以访问其他行
    的数据。这提高了并发性能。
*/
-- 例子：
CREATE TABLE products (
    product_id INT PRIMARY KEY AUTO_INCREMENT,
    product_name VARCHAR(100) NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    stock INT NOT NULL DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

UPDATE products SET stock = stock - 1 WHERE product_id = 123;
-- 在这个例子中，只有product_id = 123的那一行被锁定，其他产品的数据仍然可以同时被其他事务访问和修改。

/*
    3. 外键约束
        InnoDB支持外键约束，这有助于维护数据库的参照完整性。例如，如果在订单表中有一个外键引用产品表，当你
    删除产品时，如果某个订单引用了这个产品，InnoDB会阻止删除操作。
*/
-- 例子：

CREATE TABLE products (
    product_id INT PRIMARY KEY,
    name VARCHAR(100)
);

CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    product_id INT,
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);
/*
        上面的SQL语句定义了两个表，orders表中的product_id必须在products表中存在，如果尝试删除products表中的
    某个产品且该产品已被订单表引用，数据库会阻止删除操作。
*/

/*
    4. 自动崩溃恢复
        InnoDB具有自动崩溃恢复功能。在数据库崩溃后，InnoDB会自动重新启动并恢复到一致状态。它通过重做日
    志（redo log）和撤销日志（undo log）来实现这一功能。
    例子：
        如果服务器在事务提交之前崩溃，InnoDB会使用撤销日志来回滚未完成的事务以确保数据一致性。如果事务已提交但尚
    未写入磁盘，InnoDB会使用重做日志来完成数据恢复。

    5. 高并发处理
        InnoDB设计用于处理高并发负载，它通过多版本并发控制（MVCC）来实现高效的并发事务处理。MVCC允许读操作和写
    操作同时进行，从而极大地提高了数据库的并发性能。
    例子：
    在一个在线电子商务网站上，多个用户可以同时浏览和购买商品，InnoDB能够有效地处理这些并发请求，确保数据一致性和高性能响应。
*/


/*
    InnoDB存储引擎文件特性：
        在MySQL数据库中，每当你创建一个表或进行数据操作时，InnoDB存储引擎会在后台创建和管理一系列文件。这些文
    件各自有不同的用途和功能。以下是一些常见的文件类型及其详细解释和例子。

    1、.ibd 文件
    描述：InnoDB表空间文件，它是一个二进制文件，它是不可以直接打开的，不过可以通过cmd使用命令ibd2sdi，后面
        跟着对应的ibd文件会显示一大段js代码，里面就会有记录对应表的字段和其他信息
    用途：每个InnoDB表都有一个对应的 .ibd 文件，这些文件存储了表的数据和索引。这个文件相当于是一个“箱子”，里面装着
        这张表所有的数据。
    举例：
    (1)假设我们有一个表 employees，存储公司员工的信息。这个表的数据会存储在 employees.ibd 文件中。
    (2)如果我们往 employees 表中插入了100条记录，这些记录都会写入到 employees.ibd 文件中。

    2、.frm 文件
    描述：表定义文件。
    用途：.frm 文件存储了表的元数据，比如表的结构、字段名、数据类型等。可以把它理解为这张表的“设计图”。
    举例：
    (1)假设我们有一个表 customers，它的结构定义为包含 customer_id、name 和 email 三个字段。这些定义会被存储
        在 customers.frm 文件中。
    (2)如果我们修改了 customers 表的结构，比如增加一个 phone 字段，这个修改也会反映在 customers.frm 文件中。

    3、.sdi 文件
    描述：数据字典文件。
    用途：从MySQL 8.0版本开始，.sdi 文件用于存储数据字典信息。这些文件包含关于数据库对象的信息，可以理解为对数据库内
        所有对象的详细记录，类似于一本“索引”。
    举例：
    (1)如果我们在数据库中创建了一个表 orders，相应的元数据会记录在 orders.sdi 文件中。
    (2)当我们对 orders 表进行任何修改，比如增加索引或修改字段类型，.sdi 文件会记录这些变化。

    4、ibdata1 文件
    描述：InnoDB共享表空间文件。
    用途：ibdata1 文件用于存储共享表空间的数据，包含了所有表的数据和索引，还有撤销日志和事务日志。可以把它想象成一个
        大箱子，里面装着很多小箱子，每个小箱子存放一张表的数据。
    举例：
    (1)默认情况下，所有表的数据都会被存储在 ibdata1 文件中。
    (2)如果我们有多个表 products、orders 和 customers，它们的数据会被存储在 ibdata1 文件中的不同部分。

    5、ib_logfile0 和 ib_logfile1 文件
    描述：InnoDB重做日志文件。
    用途：这些文件用于记录事务日志，以确保数据的持久性和一致性。可以将它们看作是记录操作历史的“日记本”。
    举例：
    (1)当我们在 employees 表中插入一条记录，这个操作会被记录在 ib_logfile0 或 ib_logfile1 文件中。
    (2)如果数据库突然崩溃，重启时InnoDB会通过这些日志文件恢复未完成的事务，确保数据一致性。

    6、ibtmp1 文件
    描述：InnoDB临时表空间文件。
    用途：这个文件用于存储临时表和内部临时数据，可以理解为临时存储区。
    举例：
    (1)当我们执行一个大查询并创建临时表来存放中间结果时，这些临时表的数据会存储在 ibtmp1 文件中。
    (2)例如，执行 SELECT ... FROM ... WHERE ... 这样的查询语句时，MySQL可能会创建临时表来优化查询，这些临时表
        的数据会存储在 ibtmp1 文件中。
*/

-- 下面给出实例：
-- 假设我们有一个数据库 shop，在其中创建了以下表：
CREATE TABLE products (
    product_id INT PRIMARY KEY,
    name VARCHAR(100),
    price DECIMAL(10, 2)
);

CREATE TABLE orders (
    order_id INT PRIMARY KEY,
    product_id INT,
    quantity INT,
    FOREIGN KEY (product_id) REFERENCES products(product_id)
);
/*
在文件系统中，MySQL会生成以下文件：
    1、products.ibd：存储 products 表的数据和索引。
    2、products.frm：存储 products 表的结构定义。
    3、products.sdi：从MySQL 8.0开始，存储 products 表的数据字典信息。
    4、orders.ibd：存储 orders 表的数据和索引。
    5、orders.frm：存储 orders 表的结构定义。
    6、orders.sdi：从MySQL 8.0开始，存储 orders 表的数据字典信息。
    7、ibdata1：如果使用共享表空间，存储所有表的数据和索引。
    8、ib_logfile0 和 ib_logfile1：记录所有数据操作的日志。
    9、ibtmp1：用于存储临时表和临时数据。
*/

-- 我们可以查看下面参数，即可知道一张InnoDB引擎表是否对应一个文件
-- 在MySQL8.0版本之后，这个开关默认打开的
SHOW VARIABLES LIKE 'innodb_file_per_table';

/*
    相应地，InnoDB引擎是存在相应的逻辑存储结构的，它的划分如下：
    表空间(Tablespace) --> 段(Segment) --> 区(Extent) --> 页/块(Page/Block) --> 行(Row)

        其中，一个区的大小固定为1M，一个页的大小固定为16K，页是磁盘操作(I/O操作)的最小单元，对于行来说，它存储的
    信息有：最后一次操作事务的id，指针，还有字段列的信息等
*/
