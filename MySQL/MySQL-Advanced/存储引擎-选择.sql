/*
MyISAM 存储引擎
    1、特点
    (1)高读取性能：MyISAM 对读取操作进行了优化，适合读多写少的场景。
    (2)表级锁定：写操作会锁定整个表，因此在高并发写操作时性能较差。
    (3)不支持事务：不支持事务管理，因此不适合需要高数据完整性和一致性的场景。
    (4)数据容易恢复：适合作为只读数据库、日志数据库等。

    2、适用场景
    (1)场景 1：博客网站
       需求：博客文章的阅读次数远多于发布次数。
       选择MyISAM：因为文章读取多，写入少，MyISAM 的高读取性能可以满足需求。
    (2)场景 2：日志系统
       需求：记录系统日志，主要是查询日志，不需要频繁更新。
       选择MyISAM：日志记录主要是追加和读取，MyISAM 的高读取性能很适合这种场景。

Memory 存储引擎
    1、特点
    (1)数据存储在内存中：读写速度非常快，但数据在服务器重启后会丢失。
    (2)表级锁定：内存表的写操作会锁定整个表。
    (3)适合临时数据：适合存储临时数据、会话数据等。

    2、适用场景
    (1)场景 1：电商平台的购物车
       需求：用户在浏览商品时，临时存储购物车数据，数据只需在会话期间有效。
       选择 Memory：内存表可以快速读写购物车数据，会话结束后数据丢失也无所谓。
    (2)场景 2：缓存临时计算结果
       需求：在数据处理过程中，临时存储计算结果，计算完成后结果不再需要。
       选择 Memory：内存表可以非常快地存取临时计算结果，提高数据处理效率。

InnoDB 存储引擎
    1、特点
    (1)支持事务：支持ACID（原子性、一致性、隔离性、持久性）事务，保证数据的完整性和一致性。
    (2)行级锁定：支持行级锁定，适合高并发场景。
    (3)数据持久化：数据存储在磁盘中，断电或重启后数据不会丢失。
    (4)支持外键：能够维护数据的完整性和一致性。
    2、适用场景
    (1)场景 1：银行交易系统
       需求：每笔交易都需要确保数据的一致性和完整性，可能有高并发的读写操作。
       选择 InnoDB：支持事务和行级锁定，能够确保每笔交易的安全和数据的完整性。
    (2)场景 2：在线购物系统
       需求：在用户下单时，需要同时更新库存和订单信息，保证数据的一致性。
       选择 InnoDB：支持事务和外键，可以确保订单和库存的更新操作要么全部成功，要么全都回滚，保持数据一致。

三者对比总结：
    特性/存储引擎                MyISAM（图书馆）               Memory（白板）	          InnoDB（银行保险箱）
    读取性能	                        高	                        非常高	                    高
    写入性能	                        较低	                        很高	                        高
    事务支持	                        不支持	                    不支持	                    完全支持
    数据持久性	                持久化（磁盘存储）	            非持久化（内存存储）	        持久化（磁盘存储）
    锁定机制	                        表级锁定	                    表级锁定	                行级锁定
    适用场景	        读多写少的场景，如博客、日志系统	    临时数据，如购物车、临时计算结果	    高并发和事务处理，如银行、在线购物
总结：
    1、MyISAM：适用于读多写少的场景，高读取性能，主要用于只读数据或需要快速读取的场合，如博客、日志系统。
    2、Memory：适用于需要快速读写的临时数据存储，如电商平台的购物车、临时计算结果。
    3、InnoDB：适用于需要高数据完整性、一致性和高并发处理的场景，如银行交易系统、在线购物系统。
*/
