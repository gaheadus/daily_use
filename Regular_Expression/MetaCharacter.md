# 1.元字符,Metacharacter
&emsp;&emsp;[常用元字符](#常用元字符)  
&emsp;&emsp;[元字符的分类](#元字符的分类)  
&emsp;&emsp;[汉字字符](#汉字字符)

## 常用元字符
|  **Character classes**  |  **字符集、字符组**  |  **备注**  |
| --- | --- | --- |
| **.**                 |  any single character except newline  |  |
| \w \d \s              |  word, digit, whitespace    |  |
| \W \D \S              |  not word, digit, whitespace  |  |
| [abc]                 |  any of a, b, or c                           |    A single character of: a, b, or c  |
| [^abc]                |  not a, b, or c                                |    A single character except: a, b, or c  |
| [a-g]                 |  character between a \& g              |    Any single character in the range a-g  |
| [a-zA-Z]              |                                              |    Any single character in the range a-z or A-Z  |
| **Anchors**           |   **锚点，定位符**    |  |
| ^                     |  matches the position at the start of the line  |  |
| $                     |  matches the position at the end of the line  |  |
| \<                    |  matches the position at the start of a word  |  |
| \>                    |  matches the position at the end of a word  |  |
| \b                    |  any word boundary  |  |
| \B                    |  not-word boundary  |  |
| **Escaped characters** |   **转义字符**  |  |
| \\. \\* \\\           |  escaped special characters  |  |
| \t \n \r              |  tab, linefeed, carriage return  |  |
| \s                    |  any whitespace character  |  |
| \S                    |  any non-whitespace character  |  |
| \d                    |  any digit  |  |
| \D                    |  any non-digit  |  |
| \w                    |  any word character (letter, number, underscore)  |  |
| \W                    |  any non-word character  |  |
| \b                    |  any word boundary  |  |
| \u00A9                |  unicode escaped ?
| **Groups \& Lookaround** |    **分组 \& 环视**  |  |
| (abc)                 |  capture group                              |   (...)  Capture everything enclosed  |
| \1                    |  backreference to group #1          |   反向引用分组，如\1、\2、\3  |
| (?:abc)               |  non-capturing group  |  |
| (?=)                  |  positive lookahead  |  |
| (?!)                  |  negative lookahead  |  |
| **Quantifiers \& Alternation** |    **数量 \& 可选**  |  |
| a?                    |  zero or one of a  |  |
| a\*                   |  zero or more of a  |  |
| a+                    |  one or more of a  |  |
| a{3}                  |  exactly 3 of a  |  |
| a{3,6}                |  between 3 and 6 of a  |  |
| a{3,}                 |  3 or more of a  |  |
| a+?  a{2,}?           |  match as few as possible  |  |
| ab\|cd                |  match ab or cd                         |    (a\|b)  a or b |

要适当参考英文原文，因为有时候中文翻译不是太精准。

**备注1：** \s - space,  \w - word ,  \d - digital , \r - return , \n - new line , \t - tab , \b - boundary
**\w** : 所有单个大小写 **字母、数字、下划线** ，与[a-zA-Z0-9\_]相同；
**\s** : 所有单个 **空白字符** ， **包括空格、制表、回车、换行等字符** ("\t\r\n")。


## 元字符的分类
按照字符所表示的意义，分三类：  
1. \d、\D、\w、\s、.等 **表示字符** ；  
2. ?\*+{m,n}等 **表示数量** ；注:?用在不同地方意义不一样,用在字符后表示数量,用在数量后表示懒惰匹配；  
3. ^、$、\b、\<、\>等 **表示位置** ；环视(欲搜索)也用来匹配某个位置。  
按字符个数分类，分两类：单字符的元字符，如.\*+，和多字符的元字符，如\b\w\[abc\]\(?:\)。

&nbsp;


## 转义
什么时候需要转义？
是否需要转义，根据其所表示的含义而定，字面含义、特殊含义。    
①普通字符表示特殊含义时需要转义    
字符本身具有字面含义，在表示元字符的特殊含义时需要转义，如b表示特殊含义时写成\\b。  
例如b为普通字符，加上转义字符后，\\b表示特殊含义，\\和b结合在一起是一个元字符，\\b表示单词的开始或结束。  

哪些普通字符表示特殊含义时需要转义？ -- 元字符表格里所有转义字符，如\\b\\B\\t\\w\\W\\d\\D\\s\\S\\r\\n \\<\\>\\num等。  

②特殊字符表示字面含义时需要转义  
字符本身具有特殊含义，在表示字符本身的字面含义时需要转义，如.表示字符本身字面含义是写成\\.。  
例如+CUSD表示字符本身字面含义时写成\\+CUSD。  

哪些特殊字符表示字符字面含义含义(字符本身含义)时需要转义？ -- 元字符表格里有特殊含义的字符，如.?\*+ ^$\\(){[等。  

注：元字符里的部分符号、而不是全部符号，在表示字符本身的字面含义时，需要转义，如字符组[abc]，在表示字符字面含义时，[需要转义、而]不需要转义。  
{}、[]，只有左侧括号需要转义,右侧括号不需要转义，{m,n}、[123456]表示字符本身时需要转义写成\\{m,n}、\\[123456]。
但是()，左右括号都需要转义，\\(abcd\\)。  

![常用结构的转义1](https://github.com/gaheadus/daily_use/blob/master/Resources/%E5%B8%B8%E7%94%A8%E7%BB%93%E6%9E%84%E7%9A%84%E8%BD%AC%E4%B9%891.png)  
![常用结构的转义2](https://github.com/gaheadus/daily_use/blob/master/Resources/%E5%B8%B8%E7%94%A8%E7%BB%93%E6%9E%84%E7%9A%84%E8%BD%AC%E4%B9%892.png)  


&nbsp;


## 汉字字符
\w处理表示字母数字下划线之外，也可以表示单个汉字，或其他语言符号。  
那么，如何匹配单个汉字？在Unicode编码环境下使用的正则表达式，匹配Unicode字符集中基本的中文字符，使用[\u4e00-\u9fff]或[\u{4e00}-\u{9fff}]，不同的工具表示方式可能不一样。参考《正则指引.余晟》--附录b 常 用的正则表达式→中文字符  
备注：[^\u4e00-\u9fff]匹配非汉字，[a-zA-Z0-9_\u4e00-\u9fff]匹配中文字符、字母、数字、下划线。

匹配中文汉字:[\u4e00-\u9fff]。  
匹配中文标点符号:[\u3002\uff1b\uff0c\uff1a\u201c\u201d\uff08\uff09\u3001\uff1f\u300a\u300b]，该表达式可以识别： 。 ； ， ： “ ”（ ） 、 ？ 《 》等标点符号。  
匹配双字节字符:[^\x00-\xff]。

**notepad++匹配中文**  
通常正则表达式匹配中文可以利用Unicode的特点，使用[\u4e00-\u9fff]匹配。但在Notepad++中不能正常使用。  
解决方法是，首先将编码转换成Unicode（菜单->格式->转换为UTF-8，如果不转换可能匹配出错），然后使用[\x{4e00}-\x{9fff}]就可以实现匹配中文了。  
网上说法：[一-龥]，所有汉字，[一-龥！-～]，所有汉字加标点。
