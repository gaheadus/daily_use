## Everything搜索 使用方法
[Everything介绍](#1Everything介绍)  
[使用方法](#2使用方法)  
[更多例子](#3更多例子)  
[常用功能](#4常用功能)  
[常用搜索语法](#5常用搜索语法)  
[CSDN链接](#6CSDN链接)  


## 1.Everything介绍
Everything是voidtools开发的一款 **文件搜索工具** ，官网描述为&quot;基于名称 **实时** 定位 **文件和目录** （Locate files and folders by name instantly）&quot;。  
它体积小巧，界面简洁易用，快速建立索引，快速搜索，同时占用极低的系统资源，实时跟踪文件变化，并且还可以通过http或ftp形式分享搜索。  
在搜索框输入文字，它就会只显示过滤后的文件和目录。Everything搜索只基于文件和文件夹的名称，所以它创建数据库很快。一个刚安装完的Windows XP SP2系统(约20,000份文件)，需要一秒钟。索引一百万份文件则需要一分钟。  
如果你希望能按文件名进行高速搜索文件，并且硬盘分区都是使用NTFS格式的，又或者需要远程搜索其他计算机上的文件，那么你绝对不能错过Everything这款仅几百KB的免费软件。它绝对值得你收藏与试用的。  

**Everything用于文件、文件夹查找，重复文件查找，非常好用。**  
新发现，Everything可以搜索文件内容。  
[*返回目录*](#everything搜索-使用方法)



## 2.使用方法  
1.基本例子  
abc          --    搜索名字为abc的文件和文件夹  
123 abc      --   搜索文件名包含123和abc的文件和文件夹  
\*.txt       --   搜索txt后缀文件。通配符\*可以不写，\*.txt或.txt都可以。  
          --   \*.txt和.txt的不同，\*.txt表示搜索.txt格式文件(文件名后缀是.txt)，而.txt表示搜索文件名中包含.txt字符的文件，不一定是.txt格式文件(文件名后缀可以是.txt也可以不是.txt)。如下：  

上图中，.txt的搜索结果中有一个名为“word文档.txt哈哈哈.docx”的文件。  

2.指定路径搜索：  
F:\TDDOWNLOAD\ abc    --   在F:\TDDOWNLOAD\目录下搜索包含abc字符的文件及文件夹  
abc F:\TDDOWNLOAD\   --  目录放在文件名的前面或者后面都可以  

TDDOWNLOAD\ abc       --   在所有TDDOWNLOAD文件夹下搜索包含abc字符的文件及文件夹  
TDDOWNLOAD\ \*.jpg    --    在所有TDDOWNLOAD文件夹下搜索jpg后缀文件  
F:\TDDOWNLOAD\ abc    --   在F:\TDDOWNLOAD\目录下搜索包含abc字符的文件及文件夹  
F:\TDDOWNLOAD\ \*.jpg   --  在F:\TDDOWNLOAD\目录下搜索jpg后缀文件  

abc F:\TDDOWNLOAD\、F:\TDDOWNLOAD\ abc，都可以，目录可以放在文件名的前面、也可以放在文件名的后面  
注意：TDDOWNLOAD\ abc ，目录后的斜杠\与被搜索字符之间有一个空格；  

3.多个条件搜索  
\*.txt            --    一个条件，搜索txt格式文件  
F:\temp \*.txt    --     两个条件，在F:\temp目录下、搜索txt格式文件  
F:\temp \*.txt content:"project source root directory"   --   三个条件，在F:\temp目录下、搜索txt格式文件、并且其内容包含"project source root directory"字符串  

4.多个关键词搜索  
123 abc          --    搜索包含123和abc的文件和文件夹  
123|abc           --   搜索包含123或abc的文件和文件夹  
\*.jpg|\*.flv    --    搜索jpg或flv后缀文件  
在Everything的搜索框中可以输入多个关键词，以空格分开，表示搜索结果要包括全部关键词。大家肯定对这种做法不会陌生，因为它正是搜索引擎的惯例。  

5.使用搜索前缀：  
case:name -- 前缀case表示查找文件名为name的文件、区分大小写，  
ww: name -- 查找文件名为name的文件、全词匹配   
case:ww: name -- 多个修饰符一起使用。查找文件名为name的文件，区分大小写、并且全词匹配。  
F:\sourcecode\ startwith:test content:测试  -- 在F:\sourcecode\目录下，查找文件名以test开头、文件内容中包含”测试”这两个字的文件。  
f:\ video:    -- 搜索视频文件  
f:\ video:红楼梦  -- 在f盘搜索中有”红楼梦”的视频文件  

6.使用操作符：  
红楼梦 //搜索名字中包含”红楼梦”的文件，结果中有.doc文件、.lnk链接文件、\~开头的临时文件。  
红楼梦 !.lnk //搜索文件名不含.lnk的文件。有时搜索结果出现一堆链接文件.lnk，看上去杂乱，可以使用!过滤这些文件。  
红楼梦 !\~ !.lnk //排除~开头的临时文件和.lnk链接文件。多个!可以连用，中间用空格隔开。  
红楼梦 !\~ .lnk //这样写则只会显示.lnk文件。名字中包含”红楼梦”的.lnk文件。  
红楼梦 \~ !.lnk //这样写则只会显示~开头的临时文件。名字中包含”红楼梦”的临时文件。  
[*返回目录*](#everything搜索-使用方法)


## 3.更多例子  
实例1：找到所有c目录及其下任意子目录的txt文件        c:\windows\*.txt  
实例2：找出所有bmp和jpg文件        \*.bmp | \*.jpg  
实例3：找出所有名为download文件夹下的所有avi文件        download\ .avi  
实例4：找出所有名字中含.tx的文件夹        folder:.tx  
实例5：搜索空txt文件        \*.txt file:size:0  
实例6：搜索所有大于1MB的常见图像文件        \<\*.bmp|\*.jpg|\*.png|\*.tga\> size:\>1mb  
实例7：查找所有全字匹配1.txt的文件        ww:1.txt  
实例8：查找wi开头的h文件和cpp文件        file:\<wi\*.h|wi\*.cpp\> 或wi\* \<ext:h|cpp\>  
实例9：d盘2016/1/1至2016/6/1的修改过的word文件        \*.doc|\*docx  dm:2015/1-2015/6  
实例10：XXX第N集.rmvb&quot;，XXX是电视剧名，N是数字        regex:.\*第[0-9]+集  
实例11：连续的RAR压缩包 XXXX.partN.rar        regex:.\*part[0-9]+.rar  
实例12：连续的ZIP压缩包 XXXX.zN        regex:.\*\.z[0-9]+  
实例13：搜索所有纯中文目标        regex:^[^0-9a-z]\*$  
实例14：搜索带中文字符的目标        regex:^.\*[^!-~]+.\*$  
实例15：找到所有c:\windows目录下的txt文件        regex:c:\\windows\^\*.txt  
实例16：列出所有c:\windows的N级子目录        regex:c:\\windows\^\*(\^\*){N}$  
实例17：列出所有c:\windows的N级子目录下的txt文件        regex:c:\\windows\^\*(\^\*){N}\.txt$  

**其他**  
（1）Everything的文件共享功能  
Everything 内置了HTTP、ETP/FTP服务器的功能，你可以将你的硬盘变成一个网站或FTP，方便别人下载你的文件。并且，HTTP的分享还拥有一个方便的搜索功能呢，使用时只要点击菜单&quot;工具&quot;-&quot;HTTP服务器&quot;或&quot;ETP/FTP服务器&quot;后，就可以启动服务了。启动HTTP服务后，你只要在浏览器中输入`http://本机ip:端口号`即可进行访问。  
FTP的服务则需要FTP客户端来访问，你还可以在&quot;工具&quot;-&quot;选项&quot;-&quot;HTTP&quot;或&quot;FTP&quot;中设置端口号和访问密码等。反正有了Everything，你就可以在局域网内随心所欲地分享文件了！当然，如果你的机器有外网的IP（如电信的ADSL），还能让Internet上的任何人访问你硬盘里的文件呢。不得不说，这是一个非常非常棒的应用。  
（2）Everything 高效搜索技巧之正则表达式  
正则表达式搜索，使用前缀修饰符regex:，或者通过菜单打开正则表达式选项，菜单Search → Enable Regex。  
（3）Everything使用 **局限**  
Everything仅支持 **基于NTFS文件系统** ，对于 FAT32格式的文件系统，Everything将不支持，这是 Everything 的一个局限。如果你的文件系统还是FAT32，若想使用Everything的话，则你需要转换你的分区格式。  
在XP系统中可以在命令行下运行convert X:/FS:NTFS ，而后按提示完成系统格式转换操作后就可以Evergything了， 其中X代表你要转换的盘符。  

[*返回目录*](#everything搜索-使用方法)


## 4.常用功能
1.Everythin，如果搜索结果是文件，那么双击文件就可以打开文件；如果搜索结果是文件夹，那么就会弹出windows自带文件浏览器、并且打开文件夹目录。和Windows自带文件浏览器的功能是一样的。

2.而且，在Everything里对文件进行的操作，和在Windows自带文件浏览器里进行的操作，效果是一样的，比如删除文件、重命、复制等。这些操作都可以直接在Everything搜索结果里进行，并不需要打开文件所在目录、再操作。
并且，everything搜索结果的右键菜单和windows自带文件浏览器的右键菜也是一样的。

3.路径中包含空格时，需要在路径外加双括号，如"C:\Program Files"。

4.在搜索框里填路径，而不是文件名，则列出该目录及其子目录下所有文件、文件夹，包括隐藏文件。相当于windows自带文件浏览器，但是又更强大，Windows自带文件浏览器只会显示当前目录下文件，everything会显示当前目录、及其子目录下文件。
例如输入F:\sourcecode\test\apps列出该目录及其子目录下所有文件和文件夹；如果输入F:\sourcecode\test\apps test.c则是在该目录下查找test.c文件。搜索速度比find命令快多了。

5.打开多个搜索框
有时候需要希望打开多个搜索窗口，比如搜索到某一个关键词后，希望保持搜索窗口不关闭，继续搜索另外一个关键词，这时需要另外打开一个搜索窗口，怎么操作？
方法：菜单→文件→新建搜索窗口，快捷键ctrl+n。  
[*返回目录*](#everything搜索-使用方法)  



## 5.常用搜索语法
**1.操作符**  
空格 &emsp;&emsp; 逻辑与，例：li ch，搜索文件名中既含li又含ch  
|  &emsp;&emsp; 逻辑或，例：1.txt | 2.txt，搜索文件名含1或2的txt文件  
!  &emsp;&emsp; 逻辑非，例：*.txt !b，搜索文件名不含b的txt文件  
\< \>  &emsp;&emsp; 分组  
&quot; &quot;     &emsp;&emsp;   搜索引号内的词组  
备注：既然空格表示&quot;与&quot;，那么如何表示真正的空格呢？加英文半角引号，比如&quot;program files&quot;。  

**2.通配符**  
\*          匹配0个或多个字符        a\*.txt        &quot;ab.txt&quot; &quot;abbb.txt&quot;  
?          匹配1个任意字符        a??.txt         &quot;abc.txt&quot; &quot;aaa.txt&quot;  

**3.宏**  
audio:        搜索音频文件.  
zip:        搜索压缩文件.  
doc:        搜索文档文件。注意:包括doc格式文件、txt格式文件、其他格式的文件，并不是只指doc格式文件。  
exe:        搜索可执行文件.  
pic:        搜索图片文件。注意:包括bmp格式、png格式、gif格式、jpeg格式、其他图片格式。  
video:        搜索视频文件.  

**4.修饰符**  
case:          匹配大小写  
file:          只匹配文件  
folder:   只匹配文件夹  
path:          匹配路径和文件名  
regex:          正则表达式  
ww:、wholeword:        全字匹配  

例：  
case:name -- 查找文件名为name的文件、区分大小写，  
ww: name -- 查找文件名为name的文件、全词匹配  
case:ww: name -- 多个修饰符一起使用。查找文件名为name的文件，区分大小写、并且全词匹配。  

**5.函数:**  
函数的使用方法和修饰符是一样的，例content: something -- 查找文件内容为something的文件。  
content:text	搜索文本内容  //注意: text外面不要加尖括号(使用经验)。说明文档写的content:<text>是错的。  
dupe:        搜索重复的文件名  
empty: 搜索空文件夹  
startwith:\<text\>        搜索指定文本开头的文件  
endwith:\<text\>        搜索以指定文本结尾的文件 (包含扩展名)  


**小结**  
宏、修饰符、函数的使用方法是一样的，以 **前缀** 的方式写在被搜索字符串前面，例：  
content:\<设计\>  //搜索内容中有&quot;设计&quot;这两个字的文件  
f:\ video:        //在f盘搜索视频文件  
f:\ video:红楼梦  //在f盘搜索名字有&quot;红楼梦&quot;的视频文件  

**多个前缀连用**，例：  
f:\ video:startwith:红楼梦  //在f盘搜索名字以&quot;红楼梦&quot;开始的视频文件  
f:\ video: startwith:红楼梦  
F:\sourcecode\ startwith:test content:测试  //在F:\sourcecode\目录下，查找文件名以test开头、文件内容中包含&quot;测试&quot;这两个字的文件。  
①前缀可以理解为参数，和命令行参数是一样的，只不过是图形界面输入。参数、参数对应的值。  
②两个前缀之间以空格隔开，如f:\ video: startwith:红楼梦，video:和startwith:之间有至少一个空格；如果某个前缀没有参数值，那么可以将其与后面的前缀连起来、中间可以不写空格，如f:\ video:startwith:红楼梦，video:和startwith:之间没有空格。  

**多个操作符连用：**  
红楼梦 //搜索名字中包含”红楼梦”的文件，结果中有.doc文件、.lnk链接文件、\~开头的临时文件。  
红楼梦 !.lnk //搜索文件名不含.lnk的文件。有时搜索结果出现一堆链接文件.lnk，看上去杂乱，可以使用!过滤这些文件。  
红楼梦 !\~ !.lnk //排除\~开头的临时文件和.lnk链接文件。多个!可以连用，中间用空格隔开。  
红楼梦 !\~ .lnk //这样写则只会显示.lnk文件。名字中包含”红楼梦”的.lnk文件。  
红楼梦 \~ !.lnk //这样写则只会显示\~开头的临时文件。名字中包含”红楼梦”的临时文件。  
[*返回目录*](#everything搜索-使用方法)


## 6.CSDN链接
https://blog.csdn.net/gaheadus/article/details/86532621  
[*返回目录*](#everything搜索-使用方法)