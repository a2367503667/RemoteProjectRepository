/*
    MySQL的体系结构是一个分层的架构，主要包括以下几个关键组件：
        1、客户端层：这是MySQL体系结构的最外层，包括各种客户端应用程序，如命令行工具、图形界面工具、Web应用
    程序等。这些客户端通过网络协议（如TCP/IP、Unix套接字、共享内存等）与MySQL服务器通信。
        就好像你有一个朋友（客户端），他经常给你打电话（连接到MySQL服务器），问你问题（发送SQL查询）。

        2、连接池：当客户端连接到MySQL服务器时，连接池负责管理这些连接。它包括认证、授权和连接管理等功能。连接池
    确保服务器能够高效地处理多个并发连接。
        就好像你的手机（连接池）负责接听电话，确保你不会错过任何电话，并且能够高效地处理多个同时打来的电话。

        3、服务层：服务层是MySQL的核心，负责处理SQL查询、事务管理、缓存管理、权限验证等。这一层包括以下主要组件：
        (1)查询解析器：解析SQL语句，确保它们符合SQL标准。
        (2)查询优化器：分析查询，选择最佳的执行计划。
        (3)缓存和缓冲区：包括查询缓存（在MySQL 8.0中已被移除）、键缓存、表缓存、InnoDB缓冲池等，用于提高性能。
        (4)存储引擎接口：MySQL的服务层通过这个接口与不同的存储引擎通信。
        就好像当你接听电话时，你会听清楚朋友的问题（查询解析器），然后思考最好的回答方式（查询优化器）。你可能还会记得以前回答
    过类似的问题，所以不需要重新思考（缓存和缓冲区）。

        4、存储引擎层：存储引擎负责数据的存储和检索。MySQL支持多种存储引擎，如InnoDB、MyISAM、Memory等。每个存储引擎都有其特定的
    功能和性能特点。InnoDB是默认的存储引擎(在MySQL5.5版本之后默认InnoDB)，它支持事务、行级锁、外键约束等高级功能。
        就好像你的大脑（存储引擎）负责记住所有的信息。你可能使用不同的记忆技巧（不同的存储引擎）来帮助你记住不同类型的信息。例如，你可
    能用一种方法记住电话号码（InnoDB），用另一种方法记住购物清单（MyISAM）。(存储引擎也就是一种存储数据的方式)

        5、文件系统/存储层：这一层包括物理文件，如数据文件、日志文件、配置文件等。数据文件存储实际的数据记录，日志文件记录事务
    和系统活动，配置文件包含MySQL服务器的设置。
        你的笔记本（文件系统/存储层）记录了所有的信息和活动。当你需要查找某个信息时，你可以翻看笔记本，找到你需要的东西。
*/

/*
    什么是存储引擎？
    存储引擎是负责处理数据的物理存储和检索，在MySQL中，存储引擎也被称为“表类型”
        想象一下，存储引擎就像是一个图书馆的图书管理员。这个管理员负责管理图书馆里的所有书籍（数据）。不同的管理员有不同的管理方
    法和技巧，这些方法和技巧决定了书籍如何被分类、存储和检索。在MySQL中，存储引擎就是这样的“管理员”，它们决定了数据如何被存
    储在硬盘上，以及如何被读取和更新。每个存储引擎都有自己的一套规则和特点，就像每个图书管理员都有自己的管理风格。

    例如：
    1、InnoDB：这个管理员非常注重书籍的完整性和安全性。他会确保每本书的借阅记录都是完整的，如果有人试图借阅一本已经被借出的
        书，他会立即告诉你。此外，如果图书馆突然停电，他也有办法恢复到停电前的状态，确保所有书籍的位置和借阅记录都不会丢失。
    2、MyISAM：这个管理员更注重快速找到书籍。他可能会把所有书籍按照字母顺序排列，这样你就可以很快地找到你想要的书。但是，如果
        图书馆停电，他可能就没有办法恢复到停电前的状态。
    3、Memory：这个管理员把所有书籍的信息都记在脑子里。他可以非常快地告诉你任何一本书的位置，但是一旦他离开图书馆，这些信息
        就会丢失。
    4、Archive：这个管理员专门负责存储那些很少被借阅的旧书。他会用特殊的压缩方法来节省空间，但是这些书可能不那么容易找到。
*/

-- 1、查询建表语句
-- 书写格式为：SHOW CREATE TABLE 表名;
/*
    CREATE TABLE `tb_account` (
      `id` int unsigned NOT NULL AUTO_INCREMENT COMMENT '主键(编号)',
      `name` varchar(16) NOT NULL COMMENT '姓名',
      `money` int DEFAULT '0' COMMENT '余额',
       PRIMARY KEY (`id`)
    ) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci COMMENT='账户表';

    (1)ENGINE=InnoDB代表指定引擎为InnoDB(这个是默认指定的)
    (2)AUTO_INCREMENT=3代表再下一次插入数据时，申请的id为3
    (3)DEFAULT CHARSET=utf8mb4指定默认的字符集为utf8mb4
    (4)COLLATE=utf8mb4_0900_ai_ci是排序规则
    (5)COMMENT='账户表'是代表对整个表的描述

*/
/*
        COLLATE=utf8mb4_0900_ai_ci 这部分代码指定了字符集的排序规则（Collation）。在MySQL中，排序规则定义了字符如
    何被比较、排序和存储。下面是对这个排序规则的详细解释：
        (1)utf8mb4：这是字符集（Character Set），它支持Unicode标准，包括了几乎所有的字符，包括emoji表情。utf8mb4是utf8的
            超集，可以存储4字节的Unicode字符。
        (2)_0900：这是MySQL 8.0版本引入的排序规则版本号。在MySQL 8.0之前，排序规则的版本号通常是_general_ci或_bin。_0900表
            示这是MySQL 8.0及以后版本的排序规则。
        (3)_ai：这是accent insensitive的缩写，意味着排序规则不区分重音（accent）。例如，é和e被认为是相同的字符。
        (4)_ci：这是case insensitive的缩写，意味着排序规则不区分大小写。例如，A和a被认为是相同的字符。
    utf8mb4_0900_ai_ci 是一个不区分大小写和重音的排序规则，适用于utf8mb4字符集，并且是MySQL 8.0及以后版本中的排序规则
*/
USE test04;
-- 设置引擎的关键字为ENGINE
-- SHOW CREATE TABLE tb_account;
SHOW CREATE TABLE my_myisam;

-- 2、查询当前数据库支持的存储引擎
SHOW ENGINES;

CREATE DATABASE IF NOT EXISTS test05 DEFAULT CHARSET utf8mb4;
USE test05;
-- 3、创建表my_myisam，并指定MyISAM存储引擎
CREATE TABLE IF NOT EXISTS my_myisam(
    id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    name VARCHAR(16) NOT NULL COMMENT '姓名'
) ENGINE = MyISAM;
SHOW CREATE TABLE my_myisam;

-- 4、创建表my_memory，并指定MEMORY存储引擎
CREATE TABLE IF NOT EXISTS my_memory(
    id INT UNSIGNED PRIMARY KEY AUTO_INCREMENT COMMENT '主键(编号)',
    name VARCHAR(16) NOT NULL COMMENT '姓名'
) ENGINE = MEMORY;
SHOW CREATE TABLE my_memory;
