USE test02;
/*
    日期函数：

    函数                                      功能
    CURDATE()                                 返回当前日期
    CURTIME()                                 返回当前时间
    NOW()                                     返回当前日期和时间
    YEAR(date)                                返回指定date的年份
    MONTH(date)                               返回指定date的月份
    DAY(date)                                 返回指定date的日期
    DATE_ADD(date, INTERVAL expr type)        返回"一个日期/时间值加上一个时间间隔为expr后"的时间值
    DATEDIFF(date1, date2)                    返回起始时间date1和结束时间date2之间的天数
*/

-- 1、CURDATE函数
SELECT CURDATE();

-- 2、CURTIME函数
SELECT CURTIME();

-- 3、NOW函数
SELECT NOW();

-- 4、YEAR函数
SELECT YEAR(NOW());

-- 5、MONTH函数
SELECT MONTH(NOW());

-- 6、DAY函数
SELECT DAY(NOW());

-- 7、DATE_ADD函数
-- 第一个参数为时间，第二个参数为：INTERVAL 时间间隔 时间单位
-- (1)指当前时间加上70天后的时间
SELECT DATE_ADD(NOW(), INTERVAL 70 DAY);
-- (2)指当前时间加上54个月后的时间
SELECT DATE_ADD(NOW(), INTERVAL 54 MONTH);
-- (3)指当前时间加上81年后的时间
SELECT DATE_ADD(NOW(), INTERVAL 81 YEAR);

-- 8、DATEDIFF函数
-- 第一个参数减去第二哥参数，也就是说，前面的时间date1比后面的时间date2要靠后，这样所得结果才是正数
-- 并且虽然我们使用完整时间(年月日时分秒)相减之后可以得到结果，但是我们一般是进行年月日相减，因为我们使用
-- 这个函数通常是计算天数的，所以不设计时分秒，即我们使用CURDATE()或者如'2024-05-16'等这些日期即可
-- 不要使用这种写法
SELECT DATEDIFF('2024-05-10 18:00', NOW());

-- 使用这种写法
SELECT DATEDIFF(CURDATE(), '2024-05-10');


-- 查询所有员工的入职天数，并根据入职天数倒序排序
SELECT name AS '姓名', DATEDIFF(CURDATE(), entrydate) AS entrydays
FROM emp
ORDER BY entrydays DESC;
