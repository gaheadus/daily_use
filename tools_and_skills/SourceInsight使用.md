# SourceInsight使用  
- [快捷键](#快捷键)  
- [常用功能](#常用功能)  
- [sourceinsight4](#sourceinsight4)  
- [正则表达式,搜索,替换](#正则表达式搜索替换)  


# 快捷键  
**菜单 -&gt; Help -&gt; Create Key List，查看、修改快捷键。**  
**ctrl+鼠标左击:跳到函数/宏/变量定义(声明),或者ctrl+=**。//按住ctrl,然后点击鼠标左键。  
**ctrl+鼠标右击:弹出对话框,显示函数/宏/变量定义；显示reference按钮**。  

**后退:alt+,  前进:alt+.**  
**不移动鼠标指针、移动页面视图：alt+方向键,alt+← alt+→ alt+↑ alt+↓**  
**书签: ctrl+m**  
**按住alt，按住鼠标左键拖动，选中一个区块；**  
**符号索引窗口: f7、alt+g**  
**ctrl+g:跳到某一行**  
**高亮当前单词: shift+f8。按一次高亮，按两次取消高亮。//si4改为f8**  
**显示/隐藏函数列表窗口：alt+f8**  
**上一个函数        :  (KeyPad) -**，方法：先取`消小键盘Num Lock`，然后才可以使用-/+进行跳转。  
**到下一个函数    : (KeyPad) +**  
**回到前一个修改   : Alt+(KeyPad) -**，方法：先取`消小键盘Num Lock`，然后才可以使用alt+-/+进行跳转。  
**转到下一个修改  : Alt+(KeyPad) + (键盘左边的Alt)**  
**鼠标选中变量,alt+/,弹出symbol info框；区分:鼠标选中变量,ctrl+/,弹出搜索框；**  
**撤销修改：ctrl+z， 恢复修改：ctrl+y**  

**搜索: ctrl+f , 向后搜索: f3, 向前搜索: f4，f12 : incremental search?**  
取消循环搜索，ctrl+f,弹出搜索框,将Wrap Around选项去掉。  
**在多个文件中搜索 : ctrl+f然后选择Files,或按ctrl+shift+f组合键** ，在弹出的Search files窗口选择需要搜索的文件夹或者文件。当要查询的文件夹包含子文件夹时，可以勾选Options中的Include Subdirectiories，实现对各层文件的递归搜索。

**搜索: ctrl+/，Lookup Reference。//** 菜单栏有一个带问号的图标,打开搜索结果。  
在Search Method中有四种可选的查找方式：Simple String、Regular Expression、 Keyword Expression和Look Up Reference。其中Simple String是最普通的查找方式，可以查找文件中出现的任意字符或字符，甚至可以查找 \_upap || u 这样的字符串，但是在工程较大时，查找过程会较慢。Regular Expression查找方式为正则表达式。Keyword Expression和Look Up Reference查找的结果基本相同，但是显示方式略有差异。这两种方式都是使用SI预先建立的数据库，查找起来速度相当快。但通常这种速度只对在查找标识符时有明显效果。对于像函数名，变量名等的查找，强烈建议使用这两种方式进行查找。  
选择Search/Search Project，在弹出的Search Project窗口进行查找操作。操作与Loopup References几乎完全一致，它们各自保存上次搜索的配置。

**替换: ctrl+h**  
单文件替换:选择Search/Replace或按ctrl+h组合键，在弹出的Replace窗口进行查找操作。在Search项目里勾选Selection则仅对当前选中的文档部分进行替换。另外如果勾选了Confirm Replacements则是逐个确认替换，否则会同时替换所有符合替换条件内容。  
多文件替换:选择Search/Replace files或按Ctrl+Shift+H组合键，在弹出的Replace files 窗口进行查找操作。除了增加New框(替换后的内容)外，其余均与Search files窗口相同，可参照查找部分的说明进行操作。

**跳到基本类型(即跳到原型)             : Alt+0**  
**从当前位置选择到文件结束             : Ctrl+Shift+End**  
**从当前位置选择到行结束               : Shift+End**  
**从当前位置选择到行的开始             : Shift+Home**  
**从当前位置选择到文件顶部             : Ctrl+Shift+Home**  

到块(大括号)的下面                    : Ctrl+Shift+]  
到块(大括号)的上面                    : Ctrl+Shift+[  
转到下一个链接                       : Shift+f9, Ctrl+Shift+L  
*附：ads快捷键：ctrl+shift+b，返回*  
[返回*快捷键*](#快捷键)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [返回*目录*](#SourceInsight使用)  



# 常用功能  
## 我的使用习惯  
ctrl+d，打开文件所在目录  
alt+, / alt+z，后退  
alt+. / alt+x，前进  
将常用功能赋予操作方便的快捷键，Option -&gt; Key Assignments。  

Contex window，动态刷新。  
Relation window，锁定，不让动态刷新。需要查看不同的relation时可以建立多个relation window，或者手动刷新。  


## 有用功能  
**菜单-&gt; Search -&gt; Selection History很有用(ctrl+shift+m)，可以打开之前浏览过的代码位置。**  
**菜单-&gt; Window-&gt; Pick Window** ，对话框显示当前打开的文件列表。//si3.5中是Window List  
**菜单-&gt; File -&gt; Recent Files，打开最近打开的文件列表；**  
如果菜单-&gt; Window中对应的文件已经关闭了，还可以通过菜单-&gt; File -&gt; Recent Files打开。  

## si工程文件默认存放目录  
source insight工程存放目录，win10/win7默认存放在C判如下目录:  
si3.5: C:\Users\lenovo\Documents\Source Insight\Projects，si4.0: C:\Users\lenovo\Documents\Source Insight 4.0\Projects。  
为了便于 **归类和查找** ，也为了不让占用C盘，应该将工程存放到指定文件夹。  
我的si project指定存放在D:\siprj目录，D:\siprj\si4prj存放si4.0工程，D:\siprj\si35prj存放si3.5工程。

## 取消自动对齐  
自动对齐往往不是我们要求的格式，自动对齐后反而需要去修改，更麻烦。  
取消自动对齐：Options-&gt;File Type Options-&gt;Auto Indenting-&gt;Auto Indent设置为none。  
[返回*常用功能*](#常用功能)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [返回*目录*](#SourceInsight使用)  




# sourceinsight4  
alt+m,在最近浏览过的两个文件之间切换显示。  
ctrl+shift+m，可以打开之前浏览过的代码位置(菜单-> Search -> Selection History)。  

菜单-> File -> Reload As Encoding -> Chinese Simplified(GB2312)，解决中文乱码问题。  

Relation window，右击relation window可以新建关系窗口，多个关系窗以tab的形式显示，很好。  

菜单-> Project -> Copy Project，复制当前共存。一般，在看大型代码时，会建立同一份代码的多个工程，这时候可以使用这里的复制工程。这样可以省去新建一个工程的多个步骤。  
菜单-> Project -> Export Project File List…，将工程中的源代码文件名导出保存。以后在新建工程的时候就可以从file list新建了，不再需要一个目录一个目录的去选择了。  

菜单-> Project -> Project Report，对工程中每个文件定义的函数、变量等进行统计、并列举出来，强大。  

菜单-> Project -> Export Project to HTML…，将源代码导出到html，这样可以使用网页浏览器查看源代码了，牛。  

菜单-> Project -> Import External Symbols…；  

文件比较 / 目录比较，和Beyond Compare一样。菜单-> Tools -> Compare Files.. / Directory Compare，工具栏 。  

Snippet window，常用程序结构片段，如for、while等结构。打开Snippet window，可以选择一种结构插入代码中。  

Clip window，粘贴板，保存一些常用的东西。  


命令行：  
$ sourceinsight4 dtu.c    //使用sourceinsight打开指定文件。如果当前打开了sourceinsight那么直接打开指定文件，如果当前没有打开sourceinsight那么先打开sourceinsight再打开指定文件。  
$ sourceinsight4 -n dtu.c  //在独立的sourceinsight实例在打开指定文件。  
$ sourceinsight4 +100 dtu.c  //打开指定文件并跳转到第100行。和vi一样。  

`Source Insight's command line has the following syntax:
sourceinsight4 [-option] [ [+linenumber file] [+file] [file] [symbolname] ]
Optional parameters are shown here inside […] brackets. Any number of options, files, and symbol names may be given on the command line.
Each option given on the command line must be preceded by a dash (-) or a forward slash (/).
`  
[返回*sourceinsight4*](#sourceinsight4)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [返回*目录*](#SourceInsight使用)  




# 正则表达式,搜索,替换  
- [si正则搜索](#si正则搜索)  
- [si支持的正则表达式](#si支持的正则表达式)  
- [si re分组的使用](#si-re分组的使用)  
- [perl正则, 推荐使用](#perl正则推荐使用)  

[返回*目录*](#SourceInsight使用)  


## si正则搜索  
1.正则搜索时将Whole Words Only选项去掉  
2.注意：sourceinsight中\w不代表所有单个大小写字母、数字、下划线，不表示[a-zA-Z0-9_], sourceinsight中\w表示空格或tab，\w-white；而python/perl中\w表示单个大小写字母、数字、下划线，[a-zA-Z0-9_]，\w-word。  
参考帮助文档: \w matches a single white space character. In other words, \w matches either a tab or space character. Example: \wwhile matches either a tab or space character, followed by while.  
备注：python/perl正则：\s - space,  **\w - word** ,  \d - digital , \r - return , \n - new line , \t - tab , \b - boundary  
&emsp;&emsp;&emsp; sourceisight正则：\s - space,  **\w - white** ,  不支持   ,  不支持  , \n - new line ,不支持, 不支持  

3.不支持欲搜索、不支持竖线&quot;|&quot;、&quot;\b&quot;、&quot;\&lt;&quot;、&quot;\&gt;&quot;；支持哪些正则？参考下一节:1.si支持的正则表达式  
**sourceinsight4.0支持Perl Compatible正则** , **可以使用竖线&quot;|&quot;** ，Perl Compatible正则可以使用复杂的正则表达式，如comment\.replace|path\.exists。  

4.sourceinsight4.0支持source insight multi-line正则/ Perl Compatible multi-line正则，可以 **在整个文件中、跨越多行搜索，而不仅限于一行** ，很有用，如在整个文件中搜索同时包括&quot;word1&quot;和&quot;word2&quot;。  
Source insight帮助文档的解释如下：//**应该多看看这个帮助文档, menu -&gt; help -&gt; help…(f1)**  
**Multi-Line Matches:** Most places in the program where you can specify a regular expression also has a &quot;regular expression syntax&quot; selection. If you select the &quot; **multi-line**&quot; version of the syntax, then **the dot (.) character matches new-lines**. **For example .\* matches the whole file**. **Example: begin.\*end matches everything from &quot;begin&quot; to &quot;end&quot; across multiple lines.**&quot;begin&quot; could be at line 1 and &quot;end&quot; could be at line 100.  

5.搜索函数调用使用add\_pa\_tx\_packet\(.\*\)  
[返回*正则表达式,搜索,替换*](#正则表达式搜索替换)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [返回*目录*](#SourceInsight使用)  


## si支持的正则表达式  
参考**帮助文档, menu -&gt; help -&gt; help…(f1)**  
**Sourceinsight支持的正则表达式在Table 3.7、Table 3.8列出来了，**** 其他 ****正则表达式**** 不支持 ****。**  
**如果想使用更强大的正则表达式，那么在搜索时请选择Perl Compatible正则:可以使用|、\b等。**  
**Regular Expression Summary** : The following special characters are interpreted in regular expressions  
**Table 3.7: Regular Expression Characters**  
**Character                 Matches**  
^ (at the beginning only)     beginning of line  
$  the end of the line  
.  any single character. In multi-line mode, this also matches the end-of-line character.  
[abc]  any single character that belongs to the set abc  
[^abc]  any single character that does not belong to the set abc  
\*  zero or more occurrences of the preceding character  
\+  one or more occurrences of the preceding character  
\t  a tab character  
\s  a space character  
\w  white space (a tab or a space char­acter)  
\n  new-line, or the end-of-line charac­ter. Use this if you want to match a line break in the middle of a pat­tern.  

Sets, such as [abc] may be in the following formats.  
**Table 3.8: Regular Expression Sets Set type**  
**Meaning     [&lt;character list&gt;]**  
eg.[abcde]    Matches any character within the set. The set can be any number of characters long.  
[x-y] eg.[a-z]  Matches on any character within the range of x through y, inclu­sively.The ASCII value of x must be less than that of y.  
combination;eg.[WXYa-z0-9]  Character lists and ranges may be combined.  
**不同的工具对RE的支持不太一样** ，比如强一点的工具支持的通配符可能会多一点，转义字符的定义也可能不一样等等。  
.\*  这条RE可以匹配任意的字符串序列，因为.表示任意字符，\*表示大于等于0个，连起来理解就是&quot;任意个任意字符&quot;  
[abc]+  表示&quot;a或b或c出现1次或多次&quot;，像字符串abc, cbac, aacbcb，aaaaa都被可以匹配  
如果还不是很理解可以用si的搜索功能自己实践一下。  

在理解上面的基础之上就可以使用RE进行替换了，替换和搜索没有什么不同，比如你可以将&quot;[abc]+&quot;替换成&quot;abc&quot;，但如果仅仅是这样就没有什么意思了。替换里和RE相关的内容是分组。与分组有关的概念包括：  
1.一个分组以\(开始，以\)结束  
2.一个RE中可以有多个分组  
3.引用一个分组使用\1, \2, \3, ...  
还是举个例子吧，假设我们的代码中有个函数叫func，它的原型定义如下  
void func(int var1, int var2)  
某天我心血来潮，把func的原型修改成了，  
void func(int var2, int var1)，  
如果没有RE，这下子可就麻烦了，所有调用func的地方都要手工挨个修改，好在有RE。按下Ctrl+h，选择使用RE进行替换，在Old中输入&quot;func(\(.\*\), \(.\*\))&quot;，在New中输入&quot;func(\2, \1)&quot;，然后执行，你会发现全部搞定了。  
当然ctrl+h只能在本文件中搜索替换，要想替换整个工程的，可以使用ctrl+shift+h。  
[返回*正则表达式,搜索,替换*](#正则表达式搜索替换)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [返回*目录*](#SourceInsight使用)  


## si re分组的使用  
**使用分组捕获感兴趣的字符，以便以后使用。**  
例如，文件中有多处如下形式的代码，  
log.debug\_print(0 ,\_\_name\_\_, &#39;loop:%d, scan ap:%s failed!&#39; % (loop\_cnt,cur\_ap))  
想替换成如下形式：  
log.debug\_print(0 ,\_\_name\_\_, &#39;scan ap:%s failed!&#39; % cur\_ap)  
怎么编写正则？  
loop:%d,\s(.+)\(loop\_cnt,(cur\_ap)\)，  
这个re匹配log.debug\_print(0 ,\_\_name\_\_, &#39;loop:%d, scan ap:%s failed!&#39; % (loop\_cnt,cur\_ap))中绿色部分，注意不包含**&#39;)**两个字符， **分组\1和分组\2是希望保留下来的字符** ，替换框填\1\2， **sourceinsight4.0 Perl Compatible** 支持(Notepad++也支持)，如下：  

si re与分组有关的概念包括：  
1.一个分组以\(开始，以\)结束  
2.一个RE中可以有多个分组  
3.引用一个分组使用\1, \2, \3, ...  
还是举个例子吧，假设我们的代码中有个函数叫func，它的原型定义如下  
void func(int var1, int var2)  
某天我心血来潮，把func的原型修改成了，  
void func(int var2, int var1)  
如果没有RE，这下子可就麻烦了，所有调用func的地方都要手工挨个修改，好在有RE。按下ctrl+h，选择使用RE进行替换，在Old中输入&quot;func(\(.\*\), \(.\*\))&quot;，在New中输入&quot;func(\2, \1)&quot;，然后执行，你会发现全部搞定了。  
当然ctrl+h只能在本文件中搜索替换，要想替换整个工程的，可以使用ctrl+shift+h。  
备注：()不需要转义，反而用做分组的()需要转义，容易搞混淆， **推荐使用强大很多的perl compatible re** 。  
[*返回目录*](#SourceInsight快捷键常用功能)

## perl正则,推荐使用  
**sourceinsight4.0推荐使用Perl Compatible正则。si re不支持复杂表达式，而且很多字符容易混淆，不推荐。**  
扶 凯 2008年12月20日 - 02:33， *http://c20031776.blog.163.com/blog/static/684716252013624383887/*

Perl的正则是相当强大的  
**Perl 程序中,正则表达式有三种存在形式**  
分别是
**(1 **模式匹配：m/&lt;regexp&gt;/     #平时我们简写 /&lt;regexp&gt;/ ,略去m,  
三个参数  
/i不区分大小写   /s匹配任何字符    /x添加空格  /o 不重复编译正则表达示  
**(2** 模式替换：s/&lt;pattern&gt;/&lt;replacement&gt;/  
 /g    进行全局替换           \U     大小写转换,例如s/(fred|barney)/\U$1/gi;  
\L    转换小写                   \E    影响到剩余的(替换的)字符串  
\l 和\u    写形式时(\l 和\u),只作用于下一个字符  
**(3** 模式转化：tr/&lt;pattern&gt;/&lt;replacemnt&gt;/  
这三种形式一般都和 =\~ 或 !\~ 搭配使用,&quot;=\~&quot; 表示相匹配(does),&quot;!~&quot; 表示不匹配(doesn&#39;t）,并在左侧有待处理的标量变量.如果没有该要处理的变量,则默认为处理 $\_ 变量中的内容.  

**表达式中的一些常用模式.**

| **/表达式/** | **结果** |
| --- | --- |
| **.** | 匹配除换行符以外的所有字符 |
| **x?** | 匹配 0 次或一次 x 字符串 |
| **x\*** | 匹配 0 次或多次 x 字符串,但匹配可能的最少次数 |
| **x+** | 匹配 1 次或多次 x 字符串,但匹配可能的最少次数 |
| **.\*** | 匹配 0 次或多次的任何字符 |
| **.+** | 匹配 1 次或多次的任何字符 |
| **{m}** | 匹配刚好是 m 个 的指定字符串 |
| **{m,n}** | 匹配在 m个 以上 n个 以下 的指定字符串 |
| **{m,}** | 匹配 m个 以上 的指定字符串 |
| **[]** | 匹配符合 [] 内的字符 |
| **[^]** | 匹配不符合 [] 内的字符 |
| **[0-9]** | 匹配所有数字字符 |
| **[a-z]** | 匹配所有小写字母字符 |
| **[^0-9]** | 匹配所有非数字字符 |
| **[^a-z]** | 匹配所有非小写字母字符 |
| **^** | 匹配字符开头的字符 |
| **$** | 匹配字符结尾的字符 |
| **\d** | 匹配一个数字的字符,和 [0-9] 语法一样 |
| **\d+** | 匹配多个数字字符串,和 [0-9]+ 语法一样 |
| **\D** | 非数字,其他同\d |
| **\D+** | 非数字,其他同\d+ |
| **\w** | 英文字母或数字的字符串,和 [a-zA-Z0-9] 语法一样 |
| **\w+** | 和[a-zA-Z0-9]+语法一样 |
| **\W** | 非英文字母或数字的字符串,和 [^a-zA-Z0-9] 语法一样 |
| **\W+** | 和[^a-zA-Z0-9]+语法一样 |
| **\s** | 空格,和 [\n\t\r\f] 语法一样 |
| **\s+** | 和 [\n\t\r\f]+一样 |
| **\S** | 非空格,和 [^\n\t\r\f] 语法一样 |
| **\S+** | 和 [^\n\t\r\f]+ 语法一样 |
| **\b** | 匹配以英文字母,数字为边界的字符串 |
| **\B** | 匹配不以英文字母,数值为边界的字符串 |
| **a&#124;b&#124;c** | 匹配符合a字符 或是b字符 或是c字符 的字符串 |
| **abc** | 匹配含有 abc 的字符串 |
| **(pattern)** | () 这个符号会记住所找寻到的字符串,是一个很实用的语法.第一个 () 内所找到的字符串变成 $1 这个变量或是 \1 变量,第二个 () 内所找到的字符串变成 $2 这个变量或是 \2 变量,以此类推下去. |
| **/pattern/i** | i 这个参数表示忽略英文大小写,也就是在匹配字符串的时候,不考虑英文的大小写问题. |
| **\** | 如果要在 pattern 模式中找寻一个特殊字符,如 &quot;\*&quot;,则要在这个字符前加上 \ 符号,这样才会让特殊字符失效 |

**\*?****    ****+?****     ****??****   为这三个数量词的非贪婪的类型**

** perl中的扩展模式匹配**  
/pattern(?=string)/ 肯定和否定的匹配 ?= 和 ?-,这个在(?=)中的内容不会存到$&amp;中  
**perl处理完后会给匹配到的值存在三个特殊变量名**  
$&amp;,  $\`,  $&#39;.匹配上的那部分字符串将自动存储在 $&amp; 之中.变量 $1 中的值为 $&#39; 中的内容,而 $&amp; 为整个被匹配的部分,匹配部分的前一部分存放在 $\` 之中,后一部分被存到 $&#39;.另一种说法是, $\` 中含有正则表达式引擎在匹配 成功前所找到的变量,而 $&#39; 为此模式还没有匹配的剩余部分.如果将这三个变量放在一起,你将得到原始字符串  

**括号的特殊用法**  
(?#text) 忽略括号内的注释文本；  
(?:pattern) 与组一致,但匹配时不生成$1,$2,也就是不捕获；  
(?imsx:pattern) 与组一致,但匹配时不生成$1,$2,在特定的风格有效期间,内嵌风格匹配修饰符；  
(?=pattern) 前向查找声明,如果正则表达式在下一次匹配 pattern 时,就开始匹配,而且不影响匹配效果.如 /\w+(?=\t)/ 将匹配制表符是否恰好在 \w+ 后面出现,并且制表符不添加到 $&amp; 的值中；  
(?!pattern) 如果正则表达式在后面不匹配 pattern ,才会开始匹配.如/foo(?!bar)/,只有当出现 foo,并且后面不出现 bar 时才开始匹配；  
(?&lt;=pattern) 后向查找声明,只有在 pattern 已经匹配下面的表达式,并且不将 pattern 的结果放入$&amp; 变量中,才匹配下面的语句.如/(?&lt;=\t)\W+/匹配制表符是否恰好在\W+前出现,但又不将制表符送到 $&amp; 中；  
(? (?{code}) 表示对 code 的使用是试验性的.如果返回真,就认为是与(?:pattern)断言同一行里的匹配.code 不插入变量.这个断言仅仅在 use re &#39;eval&#39; 编译指示符时才有效；  
(?&gt;pattern) 如果类型锁定在当前位置,就使用单独的 pattern 匹配子字符串.如正则表达式/^(?&gt;a\*)ab/永远不会匹配,因为语句(?&gt;a\*)将匹配字符串开头所有的 a 字符,并删除与 ab 匹配的字符 a；  
(!&lt;=pattern) 非后看声明,与后看声明意思相反；  
(!=pattern) 非前看声明,与前看声明意思相反；  
(?(condition)yes-pattern|no-pattern) 条件表达式——条件语句或者是一个圆括号中的整数,或者是一个断言；  
(?(condition)yes-pattern)  
(?imsx) 嵌入风格匹配修饰符.当要把表达式修改符嵌入在变量中,然后把变量用在不指定自己的修饰符的一般规则表达式中；  
(?-imsx) 这个断言很有用——后面带任何内容都会关闭修饰符,直到出现另一个嵌入的修饰符.  

**Perl 中特殊正则元字符使用和环顾断言:**  
**1. \*? 和 +? 和 {n,}?  懒惰匹配**  
非懒惰，echo &quot;ab2c121a&quot;|perl -ne &#39;print $1 if /(.\*)&quot;d/;&#39;   #print ab2c12  
懒惰，echo &quot;ab2c121a&quot;|perl -ne &#39;print $1 if /(.\*?)&quot;d/;&#39;   #print ab  

**2.回溯引用和前后查找:**  
向前查找(?=..)，找字符串前面的内容,找到算成立，echo &quot;ab2c121a&quot;|perl -ne &#39;print $1 if /(.\*?)(?=2)/;&#39;  #print ab  
向后查找(?&lt;=..)，找字符串后面的内容,找到算成立，echo &quot;ab2c121a&quot;|perl -ne &#39;print $1 if /(?&lt;=2)(.\*)(?=2)/;&#39;#print c1

负向-前/后 查找 (?!…)(?&lt;!..)   找字符串前后的内容,如果不存在为真  
echo &quot;ab2c121a&quot;|perl -ne &#39;print $1 if /(?&lt;!--2)(c.\*)/;&#39;  #print 无echo &quot;ab2c121a&quot;|perl -ne &#39;print $1 if /(?&lt;!3)(c.\*)/;&#39;  #print c121a&lt;/pre--&gt;  

**可选的修饰符**  
有几个修饰符,通常叫做标记,可以后缀在正则表达式后面来改变其默认的行为.  
/i :不区分大小写  
/s :匹配任何字符. 例如: 点(.)不匹配换行符,如果加上/s这个修饰符,它将点(.)的行为变成同字符类[\d\D]的行为类似,可以匹配任何字符,包括换行符.  
/x :添加空格. /x修饰符允许你在模式中加入任何数量的空白,以方便阅读,例如: (/-? \d+ \.? \d\* /x) 等同于 (/-?\d+\.?\d\*/)  
将可选修饰符结合起来,其顺序是不重要的. 例如 (/barney.\*fred/is)  

**Perl 正则的优化**  
(1  使用 /o 来优化要多次运行但不修改的表达示  
(2  使用 qr 在运行前编译要多次运行的正则表达示  
(3  短字符用 /aaa/ || /bbb/ || /ccc/分割比 /aaa|bbb|ccc/ 速度快  
(4  试着用 study  模式来学习正则  
判断当前位置的前后字符,是否符合指定的条件,但不匹配前后的字符.  

**说明**  
预搜索有向前查找和向后查找两种：

| 表达式 | 方向 | 说明 |
| --- | --- | --- |
| **(?=****xxx****)** | 正向预搜索（向右） | 正向预搜索,判断当前位置右侧是否能匹配指定表达式 |
| **(?!****xxx****)** | 正向预搜索否定,判断当前位置右侧是否不能够匹配指定表达式 ||
| **(?&lt;=****xxx****)** | 反向预搜索（向左） | 反向预搜索,判断当前位置左侧是否能够匹配指定表达式 |
| **(?&lt;!****xxx****)** | 反向预搜索否定,判断当前位置左侧是否不能够匹配指定表达式 | |

正向预搜索内部的表达式,始终采用&quot;普通模式（从左向右）&quot;模式,反向预搜索内部的表达式,始终采用 &quot;从右向左&quot;模式.  
例如：想要匹配字符a但不匹配abc,可以为/a(?!bc)/ 再如：想要所有以.pl结尾但不是a.pl的文件名,可以/.\*(?&lt;!a)\\.pl/; 注意要从右向左。  
[返回*正则表达式,搜索,替换*](#正则表达式搜索替换)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [返回*目录*](#SourceInsight使用)  
