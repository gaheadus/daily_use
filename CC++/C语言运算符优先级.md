﻿运算符优先级@《C语言程序设计(第四版)谭浩强著》

| 优先级 | 运算符 | 含义 | 要求运算对象的个数 | 结合方向 |
| --- | --- | --- | --- | --- |
| 1 | ( ) | 圆括号 |      | 自左至右 |
|| [] | 下标运算符 |
|| -\> | 指向结构体成员运算符 |
|| **.** | 结构体成员运算符 |
| 2 | ! | 逻辑非运算符 | 1(单目运算符)  | 自右至左 |
|| ~ | 按位取反运算符 |
|| ++ | 自增运算符 |
|| -- | 自减运算符 |
|| - | 负号运算符 |
|| ( 类型) | 类型转换运算符 |
|| \* | 指针运算符 |
|| & | 取地址运算符 |
|| sizeof | 长度运算符 |
| 3 | \* | 乘 | 2(双目运算符) | 自左至右 |
|| / | 除 |
|| % | 求余（取模） |
| 4 | + | 加 | 2(双目运算符) | 自左至右 |
|| - | 减 |
| 5 | <<  | 左移 | 2(双目运算符) | 自左至右 |
|| \>>  | 右移 |
| 6 |\> \>= < <= | 关系运算符 | 2(双目运算符) | 自左至右 |
| 7 | == | 关系运算符 | 2(双目运算符) | 自左至右 |
|| != | 关系运算符 |
| 8 | & | 按位与 | 2(双目运算符) | 自左至右 |
| 9 | ^ | 按位异或 | 2(双目运算符) | 自左至右 |
| 10 | \| | 按位或 | 2(双目运算符) | 自左至右 |
| 11 | && | 逻辑与 | 2(双目运算符) | 自左至右 |
| 12 | \|\| | 逻辑或 | 2(双目运算符) | 自左至右 |
| 13 | ? : | 条件运算符 | 3(三目运算符)  | 自右至左 |
| 14 | =  +=  -=  \*=  /=  %= <br> ≫=  ≪=  &=  ^=  \|= |赋值运算符 | 2(双目运算符)  | 自右至左 |
| 15 | , | 逗号运算符(顺序求值运算符) |   | 自左至右 |

说明:

(1)同一优先级的运算符,运算次序由结合方向决定。例如\*与/具有相同的优先级
别,其结合方向为自左至右,因此3\*5/4的运算次序是先乘后除。-和++为同一优先
级,结合方向为自右至左,因此-i++相当于-(i++)。

(2)不同的运算符要求有不同的运算对象个数,如+(加)和-(减)为双目运算符,要求
在运算符两侧各有一个运算对象(如3+5、8-3等)。而++和-(负号)运算符是单目运算
符,只能在运算符的一侧出现一个运算对象(如-a、i++、--i、(float)i、sizeof(int)、\*p
等)。条件运算符是C语言中唯一的三目运算符,如x?a:b。

(3)从上表中可以大致归纳出各类运算符的优先级:

             初等运算符 () [] -> .
             单目运算符
             算术运算符(先乘除,后加减)
             关系运算符
             逻辑运算符(不包括!)
             条件运算符
             赋值运算符
             逗号运算符

以上的优先级别由上到下递减。初等运算符优先级最高,逗号运算符优先级最低。位
运算符的优先级比较分散(有的在算术运算符之前(如~),有的在关系运算符之前(
<<和>>),有的在关系运算符之后(如&、^、|)。为了容易记忆,使用位运算符时可加圆括号。
注：(1)单三赋结合方向自右至左，其他都是自左至右。