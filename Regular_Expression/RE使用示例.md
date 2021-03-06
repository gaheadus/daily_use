# 正则表达式使用
[基础例子](#一基础例子)  &emsp;&emsp;  [平时使用例子](#二平时使用例子)  &emsp;&emsp;  [专题](#三专题)  &emsp;&emsp;  [工具](#四工具)  

## 一、基础例子
1. **hi**  ：查找字符h后紧跟字符i，也就是hi，匹配的有hi、high、efghi、efghijk。
2. **\bhi\b**  ：精确地查找hi这个单词。\b匹配边界，\B匹配非边界:作用与\b相反。\bhi\b值匹配hi，不能匹配high中的hi。\bhi匹配high中的hi，hi\b匹配fghi中的hi。\Bhi\B匹配efghijk中的hi。
3. **\\&lt;hi\\&gt;**  ：精确地查找hi这个单词。有些工具不支持\<、\>。
4. **\bhi\b.*\bLucy\b**  ：查找 hi后面不远处跟着一个Lucy，如: Jack said "hi, is that Lucy ? or Lily?"。
5. **^hi** ：或 **hi$** ：  注:hi\n也可以匹配行末尾字符hi，注意Linux表示成hi\n、windows表示成hi\r\n。
6. **\bbeginMmsConnectivity(?=\n)** ：查找beginMmsConnectivity，并且beginMmsConnectivity是这一行的结尾。
> 注释： \b用于字符串(单词)边界匹配，^$用于行边界匹配。  
理解单词边界，应该结合\w，\w包括字母数字下划线，那么\b就表示存在一个位置，这个位置的一边是字母数字下划线、另一边不是字母数字下划线。单词边界的几种情况:逗、句、空格、制表、回车、换行等。

7. **查找不是以某个单词开头的行**  
^hello可以查找以hello开头的行，那么怎么查找不是以hello开头的行？  
**使用欲搜索，如^(?!hello)(.+)$、^(?!(hello|good))(.+)$。**  
> 解释如下：  
使用[^hello]？不对，字符组只能匹配一个字符，不能匹配多个字符，[^hello]表示不匹配h、e、l、o等四个字符。不能表示不是以hello开头的行。  
此时，应该使用欲搜索，如^(?!hello)(.+)$、^(?!(hello|good))(.+)$，这样才能匹配不是以hello开头的行。但要注意写成^(?!(hello|good))(.+)$ 时，(hello|good)占用了分组1，(.+)占用的是分组2。参考:非捕获型括号。  
附: 为什么^(?&lt;!hello)(.+)$不可以？  
①^(?!hello)(.+)$解析:(?!hello)是对^进行限制,整体表示行开始不能是hello、可以是hello以外的任意字符；  
②^(?&lt;!hello)(.+$)解析:(?&lt;!hello)是对(.+)进行限制,整体表示行开始可以是任意字符、这个字符的前面不是hello,这当然可以匹配hello本身,只要hello的前面不是hello,例如果被匹配的文本是hello 1 hello 2 hello 3,那么会匹配最前面的那个hello。这与想要的结果相反了。  
⇒ 小结：对于欲搜索，要明确是对谁进行修饰、是对谁进行限制。参考:欲搜索。  
string1(?=condition)string2、string1(?!condition)string2，condition是对string1进行限制，不是对string2进行限制；  
string1(?&lt;=condition)string2、string1(?&lt;!condition)string2，condition是对string2进行限制，不是对string1进行限制。  
string1、string2也可以不是字符，可以是其他的位置限定符，如上面的^(?!hello)(.+)$。  
类似，string1\bstring2，这里\b无法确定是对string1限制还是对string2限制，\\&gt;和\\&lt;的意义更明确，如果写成string1\\&gt;string2则明确表示是对string1进行限制，写成string1\\&lt;string2明确表示对string2进行限制。但是有的工具不支持\\&gt;和\\&lt;。  

[*返回目录*](#正则表达式使用)  

&nbsp;


## 二、平时使用例子
1. 查询电话业务、数据业务等的综合状态动态变化时序，查询相关AT命令和关键字，使用Notepad++软件查询radio.log。  
正则表达式：\+CLCC:|(AT\+(CGATT|CGACT|CGDATA|CGDCONT|CHLD|CEER))|\bNO CARRIER\b  
Notepad++软件支持正则表达式查询。

2. [sS]et\w*[iI]e\b  //使用notepad++,sourceinsight不支持这个表达式。

3. 删除指定字符
notepad++软件，ctrl+h,替换。  
普通替换，查找模式设置为普通，在查找框中输入zifuchuan,替换框什么也不填，点“全部替换”，即可。

4. 删除空行
删除空行，ctrl+h,替换，查找模式设置为正则表达式，在查找框中输入^\s+,替换框什么也不填，点“全部替换”，将空行删除。  
备注:删除空行也可以用^\r\n，windows下换行由两字符组成:回车符和换行符。使用^\s+的好处是，如果空行中有空格或tab，也能删除，而^\r\n只能删除没有空格或tab的空行，当然改成^( |\t)*\r\n也可以删除有空格或tab的空行，但是写成^\s+简洁多了。这是\s表示空格、回车、换行、制表等空白字符的极佳例子。

5. 删除包含某个字符的行
删除包含某个字符zifu的行：①ctrl+h,替换，查找模式设置为正则表达式，在查找框中输入^.\*zifu.\*,替换框什么也不填，点“全部替换”，这样可以将字符所在行删除，但是留下了空行。//注:^不可少。$可有可无，^.\*zifu.\*或^.\*zifu.\*$都可以。 ②删除空行:^\s+。  

能不能只要一步就删除包含某个字符的行？  
可以。使用^.\*zifu.\*\r\n或^.\*zifu.\*\s+，为什么？  
因为^.\*zifu.\*，点.是不包括换行符的，所以替换后会留下换行，单独的一个换行也就是空行。  
因此，改成^.\*zifu.\*\r\n或^.\*zifu.\*\s+，可以删除换行符，不会留下空行。

**点.**不包括**换行**，linux下换行是\n，但windows下换行是\r\n，那么windows下点.是否不包括\r？  
是的，不包括\r。**windows下点.不包括\r和\n**。证明：使用notepad++软件，输入^.\*zifu.\*删除字符所在行，留下空行；此时，输入^\r查找，查找到的就是删除字符所在行后留下的空行，说明\r没有被删除，说明windows下.不包括\r；继续删除\r，空行还在，此时空行中只有\n，使用点.匹配，无法匹配到\n，说明.也不包括\n。  
反过来问，linux下点.是否包括\r？待验证。

6. 修改pdf目录
如下，是一个pdf目录，  
    &emsp;&emsp;&emsp;&emsp;`封面 -14`  
    &emsp;&emsp;&emsp;&emsp;`目录 -5`  
    &emsp;&emsp;&emsp;&emsp;`第1章绪论 1`  
    &emsp;&emsp;&emsp;&emsp;`第2章线性表 20`  
想将页码前面的空格替换成tab，以便在PdgCntEditor工具处理。  
在notepad++中编辑，ctrl+h替换，查找框填“(.+)( )(\d{1,3})”，替换框填“\1\t\3”，点击全部替换。  
处理后的目录如下，  
    &emsp;&emsp;&emsp;&emsp;`封面	-14`  
    &emsp;&emsp;&emsp;&emsp;`目录	-5`  
    &emsp;&emsp;&emsp;&emsp;`第1章绪论	1`  
    &emsp;&emsp;&emsp;&emsp;`第2章线性表	20`  
注意：“(.+)( )(\d{1,3})”，中间括号里面有一个空格。也可以用“(.+)(\s)(\d{1,3})”，但是会替换tab等空白字符，这不是希望的。

7. 中文字符和英文字符之间的空格处理
从网上复制的文字，粘贴的时候中文字符和英文字符之间有空格，看上去松散，怎么处理？  
参考章节:常用元字符->汉字字符。  
汉字字符用Unicode数值表示:[\u4e00-\u9fff]或[\x{4e00}-\x{9fff}]，notepad++支持[\x{4e00}-\x{9fff}]。  
在notepad++中编辑，ctrl+h替换，查找框填“\s?([\x{4e00}-\x{9fff}])\s?”，替换框填“\1”，点击全部替换。  
[*返回目录*](#正则表达式使用)  


&nbsp;


## 三、专题
[空白字符](#1空白字符)  &emsp;&emsp;  [分组](#2分组)  &emsp;&emsp;  [贪婪&非贪婪](#3贪婪非贪婪)  &emsp;&emsp;  [预搜索(环视)](#4预搜索环视)  

### 1.空白字符
空白字符\s: 泛指任何非打印字符，包括空格、制表、回车、换行等字符。\s:所有单个空白字符，与[空格\t\r\n]相同。  
White space characters include carriage returns, line feeds, spaces, and tabs. //摘自金山词霸  
空白字符≠空格，空白字符包括空格。  
white space≠space

 **空格怎么表示？**  
比如，我要查找一个java类，它继承Activity，如public class ComposeMessageActivity extends Activity，  
①直接使用空格  
\bextends\b +\bActivity\b  //注意:+字符前有一个空格  
②使用转义字符\s  
extends\s+Activity   或extends\s{1,}Activity  
直接使用空格不容易看到，使用\s更加直观，但是会误匹配\t\f\v等字符。  
③使用 **.**  
\bextends\b.+\bActivity\b //.表示\n之外的任意字符，也可以匹配空格。

 **空行**  
^\s+可以匹配空行。  
\s包括空格制表回车换行等，因此^\s+可以匹配这样的行：多个空格、\t、\r、\n、或者他们的组合。  
不同系统下换行符不一样，Linux为\n，Windows为\r\n，因此用\s+能兼顾两种情况，通用。  

 **|的两侧不能有多余的空格**  
|两侧不能有多余的空格，例:查找文件名为test.c、test1.c、test2.c的文件， ((test)&emsp;|&emsp;(test1)&emsp;|&emsp;(test2))\\.c，实际上查找的是test&emsp;.c、&emsp;test1&emsp;.c、&emsp;test2.c -- 文件名test后面有空格、test1前后都有空格、test2前面有空格，显然是不对的。  
正确写法，RE：((test)|(test1)|(test2))\\.c。  
|的两侧不能有多余的符号，空格也不例外 -- **空格会作为有效字符参与匹配**。  
不仅|的两侧不能有多余的空格，其他元字符的两侧也不能有多余的空格。  
[*返回专题*](#三专题)  &emsp;&emsp;  [*返回目录*](#正则表达式使用)  


### 2.分组
使用分组捕获感兴趣的字符，以便后续引用。  
例，代码中有多处如下形式的代码，  
log.debug_print(0 ,__name__, 'loop:%d, scan ap:%s failed!' % (loop_cnt,cur_ap))  
想替换成如下形式：  
log.debug_print(0 ,__name__, 'scan ap:%s failed!' % cur_ap)  
怎么编写正则？  
loop:%d,\s(.+)\(loop_cnt,(cur_ap)\)，这个re匹配log.debug_print(0 ,__name__, 'loop:%d, scan ap:%s failed!' % (loop_cnt,cur_ap))中黄色部分，注意不包含外层的')两个字符，分组\1和分组\2是希望保留下来的字符，替换框填\1\2。

例子：  
如下，是一个pdf目录，将章节数字与题目文字之间的一个tab换成一个空格，

    1.1　Linux中的文件	__WKANCHOR_1y   //注：1.1前面有一个tab
    1.1.1　文件、文件描述符和文件表	__WKANCHOR_20
    1.1.2　内核文件表的实现	__WKANCHOR_24
在notepad++中编辑，ctrl+h替换，查找框填“(\t\d{1,2}\.\d{1,2}(?:\.\d{1,2})?)(.)(.+)”，替换框填“\1 \3”，点击全部替换；  
或者，查找框填(\t{1,2}\d{1,2}\.\d{1,2}(?:\.\d{1,2})?).(.+)，替换框填\1 \2。注意”\1 \2”中间有空格；  
或者，查找框填(\t{1,2}\d{1,2}(?:\.\d{1,2}){1,2}).(.+)，…  
处理后的目录如下，

    1.1 Linux中的文件	__WKANCHOR_1y
    1.1.1 文件、文件描述符和文件表	__WKANCHOR_20
    1.1.2 内核文件表的实现	__WKANCHOR_24
注意：“\1 \3”，中间有一个空格。  
解析：(\t\d{1,2}\.\d{1,2}(?:\.\d{1,2})?)(.)(.+)，表达式包含三个捕获型分组(\t\d{1,2}\.\d{1,2}(?:\.\d{1,2})?)和(.)和(.+)，一个非捕获型分组(?:\.\d{1,2})?)。
(?:\.\d{1,2})?表示“\.\d{1,2}”作为一个整体出现0次或1次，并且不占用分组编号。  
\d{1,2}\.\d{1,2}(?:\.\d{1,2})?匹配1.1.1、1.1、11.36.48、11.36、1.36.4、1.3、…。  
整个表达式匹配这样一个字符串：以tab开头，紧接着1位或2位数字、点，再紧接着1位或2位数字、点，可有可无的紧接着1位或2位数字、点，紧接着任意一个字符(这里代表tab)，紧接着1个或多个任意字符(非换行符)。

pdf目录处理，实例2

    2.2Linux下的GCC编译器工具集19
    2.2.1GCC简介19
    2.2.2编译程序的基本知识21
上面的目录有两个问题，①页码与目录名字之间紧挨着，之间需要加一个tab，②目录编号与目录名字之间紧挨着，之间需要加一个空格。  
①在页码和目录名字之间加一个tab，查找框填"(.+)(?<!\d)(\d{1,3})"，替换框填"\1\t\2"。替换后如下：

    2.2Linux下的GCC编译器工具集	19
    2.2.1GCC简介	19
    2.2.2编译程序的基本知识	21
②在目录编号与目录名字之间加一个空格，查找框填"^(\d{1,2})((\.\d{1,2}){1,2})(?!(\.\d))"，替换框填"\1\2 "。注: "\1\2 ",\2 后面有一个空格。替换后如下：  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;或者，查找框填"^(\d{1,2})((\.\d{1,2}){1,2})(?!(\.\d))(.+)"，替换框填"\1\2 \5"

    2.2 Linux下的GCC编译器工具集	19
    2.2.1 GCC简介	19
    2.2.2 编译程序的基本知识	21
RE: "^(\d{1,2})((\.\d{1,2}){1,2})(?!(\.\d))(.+)"，"\1\2 \5"。  
分析1：(\d{1,2})的编号为1，((\.\d{1,2}){1,2})的编号为2、里面的(\.\d{1,2})编号为3，注意(?!(\.\d))作为一个整体不占用编号、但是里面的(\.\d)占用编号4，(.+)的编号为5。  
分析2: 替换框填"\1\2 \5"，①(?!(\.\d))中的(\.\d)占用编号，但是无意义，因此不需要填\4，②括号嵌套的时候，外层括号包含了内层括号的内容，上述\2包括了\3所代表的内容，因此替换框填只填\2、不需要填\3。  
[*返回专题*](#三专题)  &emsp;&emsp;  [*返回目录*](#正则表达式使用)  

### 3. |的两侧是否需要加括号？
①加括号，将被()括住的内容当做一个整体，((test)|(test1)|(test2))\\.c表示匹配test.c或test1.c或test2.c  
那么(test|test1|test2)\\.c表示什么？  
![RE_show1](https://github.com/gaheadus/daily_use/blob/master/Resources/RE_show1.png)  
![RE_show2](https://github.com/gaheadus/daily_use/blob/master/Resources/RE_show2.png)  
结论：
|将位于其两侧的字符当做一个整体，相当于加了括号， (test|test1|test2)\\.c 和 ((test)|(test1)|(test2))\\.c 等效，都表示匹配test.c或test1.c或test2.c。  
|将位于其两侧的所有非|字符当做一个整体。  

②外边的括号也不加，test|test1|test2\\.c 只匹配test，为什么？  
![RE_show3](https://github.com/gaheadus/daily_use/blob/master/Resources/RE_show3.png)  
按照之前的解释: |将位于其两侧的所有非|字符当做一个整体，因此test|test1|test2\\.c表示匹配test或test1或test2.c，.c单独和test2结合，不再和前面的test、test1结合了。  
和(test|test1|test2)\\.c不同的是：(test|test1|test2)作为一个整体和.c结合。  

③优先匹配  
上述test|test1|test2\\.c表示匹配test或test1或test2.c，然而，优先匹配最先出现的test，于是上述只匹配到test。  
如果把test去掉，test1|test2\\.c表示匹配test1或test2.c  
![RE_show4](https://github.com/gaheadus/daily_use/blob/master/Resources/RE_show4.png)  
小结：test|test1|test2这样的表达式是没有意义的，优先匹配到test，结果是只匹配到了test，写成Atest|Btest1|Ctest2才有意义。  


### 4.贪婪&非贪婪
正则表达式贪婪与非贪婪模式 http://www.cnblogs.com/xudong-bupt/p/3586889.html  
1.什么是正则表达式的贪婪与非贪婪匹配  
如：String str="abcaxc";    Patter p="ab.*c";  
　贪婪匹配:正则表达式一般趋向于最大长度匹配，也就是所谓的贪婪匹配，如上面使用模式p="ab.*c"匹配字符串str，结果就是匹配到：abcaxc。  
　非贪婪匹配:就是匹配到结果就好，匹配到最少的字符，如上面使用模式p="ab.*?c"匹配字符串str，结果就是匹配到：abc。  
2.编程中如何区分两种模式  
　默认是贪婪模式；在量词后面直接加上一个问号?是非贪婪模式。  

问号?有两种用法：1.用作量词，表示匹配0或1次，等效于 {0,1}；2.用在表示数量的限定符之后表示惰性匹配。  
当 ?紧随\*、+、?、{n}、{n,} 、 {n,m}等表示数量的限定符之后时，匹配模式是非贪婪的。非贪婪模式匹配搜索到的、尽可能少的字符串，而默认的贪婪模式匹配搜索到的、尽可能多的字符串。  
[*返回专题*](#三专题)  &emsp;&emsp;  [*返回目录*](#正则表达式使用)  


### 5.预搜索(环视)
预搜索，也称环视。  
正向预搜索："(?=xxxxx)"，"(?!xxxxx)"  
格式"(?=xxxxx)"在被匹配的字符串中，它对所处的位置的附加条件是：所在位置的右侧，必须能够匹配上xxxxx这部分的表达式。因为它只是在此作为这个位置上附加的条件，所以它并不影响后边的表达式去真正匹配这个位置之后的字符。这就类似 "\b"，本身不匹配任何字符，"\b" 只是将所在位置之前、之后的字符取来进行了一下判断，不会影响后边的表达式来真正的匹配。⇐ 小结:欲搜索和\b^$等一样，是对位置进行限制的附加条件，本身不参与匹配，也可以理解为锚点。  
    例1：表达式 "Windows (?=NT|XP)" 在匹配 "Windows 98, Windows NT, Windows 2000" 时，将只匹配 "Windows NT" 中的 "Windows "，其他的 "Windows " 字样则不被匹配。  
     例2：表达式 "((?!\bstop\b).)+" 在匹配 "fdjka ljfdl stop fjdsla fdj"时，将从头一直匹配到"stop"之前的位置，如果字符串中没有 "stop"，则匹配整个字符串。  
    例3：表达式 "do(?!\w)" 在匹配字符串 "done, do, dog" 时，只能匹配 "do"。在本条举例中，"do"后边使用"(?!\w)"和使用"\b" 效果是一样的。  
反向预搜索："(?<=xxxxx)"，"(?<!xxxxx)"  
这两种格式的概念和正向预搜索是类似的，反向预搜索要求的条件是：所在位置的"左侧"，两种格式分别要求必须能够匹配和必须不能够匹配指定表达式，而不是去判断右侧。与 "正向预搜索" 一样的是：它们都是对所在位置的一种附加条件，本身都不匹配任何字符。  
例4：表达式 "(?<=\d{4})\d+(?=\d{4})" 在匹配 "1234567890123456" 时，将匹配除了前4个数字和后4个数字之外的中间8个数字。  

RILSIM2.\*(?=CGATT), 正向肯定预搜索，搜索RILSIM2,并且后面有CGATT。  
RILSIM2.\*(?!CGATT), 正向否定预搜索，搜索RILSIM2,并且后面没有CGATT。  
(?<=RILSIM2).\*CGATT, 反向肯定预搜索，搜索CGATT,并且前面有RILSIM2。  
(?<!RILSIM2).\*CGATT, 反向否定预搜索，搜索CGATT,并且前面没有RILSIM2。  
备注：RILSIM2.\*CGATT和(?<=RILSIM2).\*CGATT的搜索结果一样的，是不是没必要使用预搜索？ 不是的，虽然两者结果上一样，但是原理上不一样，RILSIM2.\*CGATT搜索的是RILSIM2.\*CGATT ，而(?<=RILSIM2).\*CGATT搜索的是.\*CGATT，(?<=RILSIM2)只是作为一个附件条件，这个附加条件本身并不参与搜索。从效率上看，预搜索(?<=RILSIM2).\*CGATT比RILSIM2.\*CGATT高的多，大文件搜索时更明显。  

使用例子，如下是一个pdf目录，想要在不是章目录的书签前面加一个tab键，以便缩进显示。  
> 第1章 栈和队列	1  
设计一个有getMin功能的栈（士★☆☆☆）	1  
由两个栈组成的队列（尉★★☆☆）	5  

也就是说，查找不是以某个字符开头的行。

在notepad++中编辑，ctrl+h替换，查找框填"^(?!第\d章)(.+)$"，替换框填"\t\1"。
处理后的目录如下，
>&emsp;&emsp;	第1章 栈和队列	1  
&emsp;&emsp;	设计一个有getMin功能的栈（士★☆☆☆）	1  
&emsp;&emsp;	由两个栈组成的队列（尉★★☆☆）	5  


查找不是以某个单词开头的行  
^hello可以查找以hello开头的行，那么怎么查找不是以hello开头的行？  
使用[^hello]？不对，字符组只能匹配一个字符，不能匹配多个字符，[^hello]表示不匹配h、e、l、o等四个字符。不能表示不是以hello开头的行。  
此时，应该使用欲搜索，如^(?!hello)(.+)$、^(?!(hello|good))(.+)$，这样才能匹配不是以hello开头的行。但要注意写成^(?!(hello|good))(.+)$ 时，(hello|good)占用了分组1，(.+)占用的是分组2。参考:非捕获型括号。  
附: 为什么^(?<!hello)(.+)$不可以？  
①^(?!hello)(.+)$解析:(?!hello)是对^进行限制,整体表示行开始不能是hello、可以是hello以外的任意字符；  
②^(?<!hello)(.+$)解析:(?<!hello)是对(.+)进行限制,整体表示行开始可以是任意字符、这个字符的前面不是hello,这当然可以匹配hello本身,只要hello的前面不是hello,例如果被匹配的文本是hello 1 hello 2 hello 3,那么会匹配最前面的那个hello。这与想要的结果相反了。  
⇒ 小结：对于欲搜索，要明确是对谁进行修饰、是对谁进行限制。  
string1(?=condition)string2、string1(?!condition)string2，condition是对string1进行限制，不是对string2进行限制；  
string1(?<=condition)string2、string1(?<!condition)string2，condition是对string2进行限制，不是对string1进行限制。  
string1、string2也可以不是字符，可以是其他的位置限定符，如上面的^(?!hello)(.+)$。  
类似，string1\bstring2，这里\b无法确定是对string1限制还是对string2限制，\>和\<的意义更明确，如果写成string1\>string2则明确表示是对string1进行限制，写成string1\<string2明确表示对string2进行限制。但是有的工具不支持\>和\<。  
[*返回专题*](#三专题)  &emsp;&emsp;  [*返回目录*](#正则表达式使用)  


### 四、工具
http://regexr.com/ ，推荐，可以用来练习、调试正则表达式。  
http://www.regexpal.com/ ,  
Notepad++软件支持正则表达式搜索(notepad++正则表达式搜索,ctrl+f->Regular expression)  
SouceInsight软件支持正则表达式搜索(si只支持简单的正则,sourceinsight4.0 Perl Compatible支持复杂正则)  
XYplorer软件支持正则表达式搜索。  
--很多软件都支持选择正则表达式搜索。  
[*返回目录*](#正则表达式使用)  
