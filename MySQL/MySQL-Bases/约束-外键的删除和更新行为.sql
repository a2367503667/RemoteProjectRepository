USE test03;
/*
    虽然说我们已经创建好了外键，但是当我们对父表进行删除和更新的时候，我们子表(带有外键的表)
    数据应该怎么变化呢？这时就需要涉及到外键的删除和更新行为

    行为                 说明
    NO ACTION            当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有则不允许删除/更新(与RESTRICT一致)
    RESTRICT             当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有则不允许删除/更新(与NO ACTION一致)
    CASCADE              当在父表中删除/更新对应记录时，首先检查该记录是否有对应外键，如果有则删除/更新外键在子表中的记录
    SET NULL             当在父表删除对应记录时，首先检查该记录是否有对应外键，如果有则设置子表中该外键值为null(这就要求该外键允许取null)
    SET DEFAULT          父表有变更时，子表将外键列设置成一个默认的值(Innodb不支持)

    (1)在'约束-外键约束'章节中，我之所以不将dept_id设置为NOT NULL，是因为下面的操作有可能使用到SET NULL行为，在此行为时，必须要求外键允许取null
    (2)NO ACTION和RESTRICT都是属于默认的，我们不设置行为的时候，就是默认这两个
*/

-- 删除外键
ALTER TABLE tb_emp
    DROP FOREIGN KEY fk_tb_emp_dept_id;

-- 1、在创建表后添加行为(其实只是在创建外键后面加上 ON UPDATE ... ON DELETE ...即可)
-- 注：下面只是举了部分例子，对于NO ACTION、RESTRICT、CASCADE和SET NULL来说，是可以混合搭配的，具体情况需要根据实际开发来决定

-- (1)NO ACTION和RESTRICT
-- 这里是设置更新时使用'NO ACTION行为'，删除时使用' RESTRICT行为 '
-- 书写格式为：ALTER TABLE 子表名 ADD CONSTRAINT 外键名 FOREIGN KEY (关联父表主键的字段名) REFERENCES 父表名 (父表主键字段名)
-- (续)ON UPDATE NO ACTION ON DELETE RESTRICT;
ALTER TABLE tb_emp
    ADD CONSTRAINT fk_tb_emp_dept_id FOREIGN KEY (dept_id) REFERENCES tb_dept (id) ON UPDATE NO ACTION ON DELETE RESTRICT;

-- (2)CASCADE
-- 书写格式为：ALTER TABLE 子表名 ADD CONSTRAINT 外键名 FOREIGN KEY (关联到父表主键的字段名) REFERENCES 父表名 (父表主键字段名)
-- (续)ON UPDATE CASCADE ON DELETE CASCADE;
ALTER TABLE tb_emp
    ADD CONSTRAINT fk_tb_emp_dept_id FOREIGN KEY (dept_id) REFERENCES tb_dept (id) ON UPDATE CASCADE ON DELETE CASCADE;

-- (3)SET NULL
-- 书写格式为：ALTER TABLE 子表名 ADD CONSTRAINT 外键名 FOREIGN KEY (关联表父表主键的字段名) REFERENCES 父表名 (父表主键字段名)
-- (续)ON UPDATE SET NULL ON DELETE SET NULL;
ALTER TABLE tb_emp
    ADD CONSTRAINT fk_tb_emp_dept_id FOREIGN KEY (dept_id) REFERENCES tb_dept (id) ON UPDATE SET NULL ON DELETE SET NULL;

-- 2、在创建表时添加外键行为
/*
    (1)NO ACTION和RESTRICT
    CONSTRAINT 外键名 FOREIGN KEY (关联到父表主键的字段名) REFERENCES 父表名 (父表主键字段名) ON UPDATE NO ACTION ON DELETE RESTRICT;

    (2)CASCADE
    CONSTRAINT 外键名 FOREIGN KEY (关联到父表主键的字段名) REFERENCES 父表名 (父表主键字段名) ON UPDATE CASCADE ON DELETE CASCADE;

    (3)SET NULL
    CONSTRAINT 外键名 FOREIGN KEY (关联到父表主键的字段名) REFERENCES 父表名 (父表主键字段名) ON UPDATE SET NULL ON DELETE SET NULL;

    注：上面只是给出某些例子而已，其实我们NO ACTION、RESTRICT、CASCADE和SET NULL可以混合搭配，具体需要根据需求来决定
*/
