/*
    数值函数，常用的数值函数有以下几个：

    函数                        功能
    CEIL(x)                    向上取整
    FLOOR(x)                   向下取整
    MOD(x, y)                  返回x%y的值
    RAND()                     返回0 ~ 1内的随机数
    ROUND(x, y)                求参数x的四舍五入的值，保留y位小数
*/

-- 1、CEIL函数
-- 只要后面有小数，都会直接取上限的最大整数，即下面两个结果都是2
SELECT CEIL(1.3);
SELECT CEIL(1.9);

-- 2、FLOOR函数
-- 只要后面有小数，都会舍弃掉小数，取最小的整数，即下面两个结果都是3
SELECT FLOOR(3.3);
SELECT FLOOR(3.9);

-- 3、MOD函数
SELECT MOD(4, 3);
-- 如果y为0，则返回的结果为null，因为取模运算和除法运算一样，都需要注意除数和模数不能为0的问题
SELECT MOD(4, 0);

-- 4、RAND函数
-- 不需要传任何参数，会得到一个0 ~ 1的随机小数
SELECT RAND();

-- 5、ROUND函数
-- 3.145保留两位小数，就会将最后一位进行四舍五入，所以结果为3.15
SELECT ROUND(3.145, 2);
-- 2.713保留两位小数，就会将最后一位进行四舍五入，所以结果为2.71
SELECT ROUND(2.713, 2);


-- 通过数据库函数，生成一个6位数的随机验证码
-- (1)获取6位整数
-- 这里我们可以使用FLOOR/CEIL/ROUND将所生成的数变成整数
SELECT FLOOR(RAND() * 1000000);
SELECT CEIL(RAND() * 1000000);
-- 保留0位小数，即保留整数部分
SELECT ROUND(RAND() * 1000000, 0);
-- (2)我们需要对所获取的数进行处理，因为有可能我们获取的数值位数小于6位，这样我们需要用填充的方式补齐6位，获得最终的6位验证码
-- 这里为了方便，我们就使用做填充'0'，我们也可以使用右填充或者填充其他数字
SELECT LPAD(FLOOR(RAND() * 1000000), 6, '0');

-- 思考：我们为什么不直接RAND()*1000000当做参数，直接参与补齐呢？
-- 如下(为什么不像下面这样写)：
SELECT LPAD(RAND() * 1000000, 6, '0');
-- 因为这样处理就会将我们RAND()*1000000的值作为字符串，很显然这个字符串的长度(整数部分、小数点和小数部分)
-- 是肯定大于6位的，但是整数部分不一定，如果整数部分小于6位，那么此时就会将小数点和小数部分的值包含在字符串的长度当中
-- 即有可能会出现'23879.'或'4693.3'这些奇奇怪怪的结果，因此，我们必须要确保我们所得的位数是数字，不能存在小数点
