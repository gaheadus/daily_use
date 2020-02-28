# Linux命令
[基础](#基础)  
[常用Linux命令](#常用Linux命令)  
[参考网址](#参考网址)  
[专题讲解](#专题讲解)  
[应用](#应用)  
[错误和注意](#错误和注意)  
[问题](#问题)  



## 基础  
### 命令格式  
$ command [-options] parameter1 parameter2 ...  
命令    选项    参数1    参数2  
例：  
$ ls -l test/test1  
解释：  
1.选项前会带-号，例如-h；有时候会使用选项的完整全名，则选项前带有--符号，如--help；  
2.parameter1 parameter2..为依附在选项后面的参数，或者是命令的参数；//分别简称为:选项参数，命令参数。  
3.命令,选项,参数等中间以空格分开，不论几个空格shell都视为一个。  
4.按下[Enter]按键后，该指令就立即执行。[Enter]按键代表着一行指令的开始启动。  
5.指令太长的时候，可以使用反斜杠(\\)来跳脱[Enter]符号，使指令连续到下一行。注意：反斜杠后就立刻接特殊字符，才能跳脱(转义)。  
6.在Linux系统中，英文大小写字母是不一样的，如cd与CD并不同。  

区分：选项和参数，命令参数和选项参数  
$ find ./test -path "./test/test3" -prune -o -print  
其中，./test是命令参数；-path "./test/test3"是选项，"./test/test3"是选项-path的参数:选项参数；  
[*返回:基础*](#基础)          &emsp;&emsp;              [*返回:页首*](#Linux命令)

### 输入、输出，重定向    
1.重定向输入输出  
重定向符：>输出重定向，<输入重定向，|管道重定向，tee多路输出重定向。  
$ ls > list.txt //重定向输出,
**$ ls > list.txt 2>&1**  
$ cat < list.txt //重定向输入,cat list.txt, 参考:《Linux程序设计(第4版)Neil Matthew,陈健译》-- 11.3.3 输入和输出重定向  
$ cat file.txt | grep string  //管道重定向输入输出。grep命令的输入是被重定向的cat命令的输出。  
$ ls | tee > list.txt  //多路重定向输出  
管道重定向，将前一个命令的输出、重定向到后一个命令的输入，将前一个命令的输出当做后一个命令的输入。  
tee,多路重定向输出，向标准输出设备输出结果，同时将此结果重定向输出到其他文件。  

**为什么使用2>&1？**  
$./test.sh > test.log 2>&1  
$./test.sh > test.log 2>test.log  
同样是将错误输出到和1一样的test.log  
那为什么我们要用2>&1呢？这是因为如果用command > file 2>file的写法，stdout和stderr都直接送到file中, file会被打开两次,这样stdout和stderr会互相覆盖,这样写相当使用了FD1和FD2两个同时去抢占file的管道，而command >file 2>&1这条命令就将stdout直接送向file, stderr 继承了FD1管道后,再被送往file,此时,file只被打开了一次,也只使用了一个管道FD1,它包括了stdout和stderr的内容。  
从IO效率上,前一条命令的效率要比后面一条的命令效率要低；所以我们要使用2>&1。  
是&1而不是1，这里&是什么？这里&相当于等效于标准输出。  


2.特殊形式指定输入输出  
$ find . -type f -exec ls -l {} \\;  
注：{}花括号代表前面find查找出来的文件名。-- ls的输入由{}指定。  
$ find . -type f -print | xargs ls -l  
通常情况下，xargs从管道或者stdin中读取数据，但是它也能够从文件的输出中读取数据。  
--xargs从管道中读取数据，并传递给ls命令作为输入。  
[*返回:基础*](#基础)          &emsp;&emsp;              [*返回:页首*](#Linux命令)

### 转义  
$ cd指针\\(指针与数组、函数指针\\)  //特殊字符(、)要用\\进行转义  

$ find test \\( -path test/test4 -o -path test/test3 \\) -prune -o -print  
圆括号表示表达式的组合。\\表示引用，即指示 shell 不对后面的字符作特殊解释，而留给 find 命令去解释其意义。  
$ find . -name \\* -type f -print | xargs grep "hostnames"  //在当前目录下的所有普通文件中搜索hostnames这个词  
注意，在上面的例子中， \\用来取消find命令中的\\*在shell中的特殊含义。  
$ find . -type f -exec ls -l {} \\;  
-exec command {} \\; -- 对find结果对应的文件执行该参数所给出的shell命令。注意{}和\\;之间有空格。  
command命令以;为结束标志，所以这句命令后面的分号是不可缺少的，考虑到各个系统中分号会有不同的意义，所以前面加反斜杠。  
参考find命令。  
[*返回:基础*](#基础)          &emsp;&emsp;              [*返回:页首*](#Linux命令)

### 技巧  
连续执行两条命令  
$ cd ~/bin && ls 或者  
$ cd ~/bin ; ls  
[*返回:基础*](#基础)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


## 常用Linux命令  
[ls](#ls) &emsp; [cd](#cd) &emsp; [pwd](#pwd) &emsp;

### ls  
ls, 列出文件与目录, list  
常用功能，技巧  
$ ls  
$ ls [-aAdfFhilnrRSt] 文件名或目录名称..  
$ ls -l | grep ^d  //只列子目录  
$ ls -F | grep /$   //只列子目录  
$ ls -l | grep ^-   //只普通文件  
$ ls -l | grep ^l   //只连接文件  
$ ls -l | wc -l //统计当前目录下的文件数  
$ ls -l | grep ^d | wc -l //统计目录个数  
$ find -name Android.mk | wc -l //查找当前目录下Android.mk文件的个数  
[*返回:常用Linux命令*](#常用Linux命令)          &emsp;&emsp;              [*返回:页首*](#Linux命令)

### cd  
cd,目录切换  
cd /usr/bin ,跳到/usr/bin/  
cd ~ ,跳到自己的home directory  
cd ,也是跳到当前用户的home directory  
cd ../.. ,跳到当前目录的上两层  

. 代表当前目录  
.. 代表上一层目录  
- 代表前一个工作目录  
~ 代表『目前用户身份』所在的家目录  
~account 代表 account 这个用户的家目录(account 是个账号名称)  

例四：返回进入此目录之前所在的目录  
[root@localhost soft]# pwd  
/opt/soft  
[root@localhost soft]# cd -  
/root  
[root@localhost ~]# pwd  
/root  
[root@localhost ~]# cd -  
/opt/soft  
[root@localhost soft]#  

例五：把上个命令的参数作为cd参数使用：cd !$。  
[root@localhost soft]# cd !$  
cd -  
/root  
[root@localhost ~]# cd !$  
cd -  
/opt/soft  
[root@localhost soft]#  
[*返回:常用Linux命令*](#常用Linux命令)          &emsp;&emsp;              [*返回:页首*](#Linux命令)

### pwd
pwd,查看当前工作目录  
用 pwd 命令查看默认工作目录的完整路径  
[root@localhost ~]# pwd  
/root  

实例2：目录连接链接时，pwd -P 显示出实际路径，而非使用连接(link)路径；  
选项：  
-L 目录连接链接时，输出连接路径  
-P 输出物理路径  
[root@localhost init.d]# pwd  
/etc/rc.d/init.d  
[root@localhost init.d]# /bin/pwd -P  
/etc/rc.d/init.d  
[root@localhost init.d]# /bin/pwd -L  
/etc/init.d  

[*返回:常用Linux命令*](#常用Linux命令)          &emsp;&emsp;              [*返回:页首*](#Linux命令)



## 参考网址  
https://www.runoob.com/linux/linux-command-manual.html


## 专题讲解  
[文件查找](#文件查找) &emsp; [字符处理](#字符处理) &emsp;&emsp;   [文件的切割、合并](#文件的切割合并) &emsp;  

### 文件查找  
[which](#which) &emsp; [whereis](#whereis) &emsp; [locate](#locate) &emsp; [find](#find) &emsp; [xargs](#xargs)  
[grep](#grep) &emsp; [egrep](#egrep) &emsp; [type](#type) &emsp; [小结.查找](#小结查找)  

#### which
which,可执行文件查找  
$ which grep  
which命令的作用是，在PATH变量指定的路径中，搜索某个系统命令的位置，并且返回第一个搜索结果。可以使用which命令查看某个系统命令是否存在，以及执行的是哪一个位置的命令。不同的 PATH 配置所找到的命令会不一样。  
which [-a] command  //-a,将所有由PATH目录中可以找到的指令均列出，而不止第一个被找到的指令名称。  
实例：查找文件、显示命令路径  
[root@localhost \~]# which pwd  
/bin/pwd  
[root@localhost \~]#  which adduser  
/usr/sbin/adduser  
[root@localhost \~]# which cd  
说明：cd 这个常用的命令竟然找不到啊。为什么呢？这是因为 cd 是bash 内建的命令，但是 which 默认是找 PATH 内的目录，所以找不到。  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)

#### whereis
whereis,可执行文件查找, man page查找  
$ whereis ifconfig  
ifconfig: /sbin/ifconfig /usr/share/man/man8/ifconfig.8.gz  

$ whereis [-bmsu] 文件或目录名  
选项与参数：  
-l :可以列出whereis 会去查询的几个主要目录  
-b :只找 binary格式的文件  
-m :只找在说明文件manual路径下的文件  
-s :只找source来源文件  
-u :搜寻不在上述三个项目当中的其他特殊文件  
例子：  
将和一个文件相关的文件都查找出来  
[root@localhost \~]# whereis tomcat  
tomcat:  
[root@localhost \~]# whereis svn  
svn: /usr/bin/svn /usr/local/svn /usr/share/man/man1/svn.1.gz  
说明：tomcat没安装，找不出来，svn安装找出了很多相关文件  
[root@study \~]# whereis passwd  #全部的文件通通列出来  
passwd: /usr/bin/passwd /etc/passwd /usr/share/man/man1/passwd.1.gz  
/usr/share/man/man5/passwd.5.gz  
[root@study \~]# whereis -m passwd  #只有在man里面的文件才抓出来  
passwd: /usr/share/man/man1/passwd.1.gz /usr/share/man/man5/passwd.5.gz  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


#### locate
locate,数据库查找    
$ locate pwd  #查找和pwd相关的所有文件
$ locate /etc/sh #搜索etc目录下所有以sh开头的文件。  
$ locate \~/m #搜索用户主目录下，所有以m开头的文件。  
$ locate -i \~/m #搜索用户主目录下，所有以m开头的文件，并且忽略大小写。  

$ locate [-iclSr] keyword  
-i ：忽略大小写的差异；  
-c ：不输出档名，仅计算找到的文件数量  
-l ：仅输出几行的意思，例如输出五行则是 -l 5  
-S ：输出locate所使用的数据库文件的相关信息，包括该数据库纪录的文件/目录数量等  
-r 使用正规运算式做寻找的条件(在AS4下选项要这样：--r )。   
-u /-U 建立数据库，-u 会由根目录开始，-U 则可以指定开始的位置。   
-e 将排除在寻找的范围之外。   
-l 如果是1则启动安全模式。在安全模式下，使用者不会看到权限无法看到的档案。这会始速度减慢，因为 locate 必须至实际的档案系统中取得档案的权限资料。  
-f 将特定的档案系统排除在外，例如我们没有道理要把 proc 档案系统中的档案放在数据库中。  
-q 安静模式，不会显示任何错误讯息。   
-n 至多显示个输出。   
-o 指定数据库存的名称。   
-d 指定数据库的路径   
-h 显示辅助讯息   
-v 显示更多的讯息   
-V 显示程序的版本讯息   
使用 locate 来寻找数据的时候特别的快， 这是因为locate寻找的数据是由“已建立的数据库/var/lib/mlocate/”里面的数据所搜寻到的，所以不用直接在去硬盘当中存取数据，因此很快。  
那么有什么限制呢？就是因为他是经由数据库来搜寻的，而数据库的建立默认是在每天执行一次(每个distribution都不同，CentOS 7.x 是每天更新数据库一次)，所以当你新建立起来的文件， 却还在数据库更新之前搜寻该文件，那么 locate 会告诉你“找不到”，因为必须要更新数据库，那能否手动更新数据库？当然可以，更新 locate 数据库的方法非常简单，直接输入“updatedb”就可以了。updatedb 指令会去读取 /etc/updatedb.conf 这个配置文件的设定，然后再去硬盘里面进行搜寻文件名的动作，最后更新整个数据库文件。因为updatedb会去搜寻硬盘，所以当你执行updatedb时，可能会等待数分钟的时间。  
• updatedb：根据 /etc/updatedb.conf 的设定去搜寻系统硬盘内的文件名，并更新 /var/lib/mlocate 内的数据库文件；  
• locate：依据 /var/lib/mlocate 内的数据库记载，找出用户输入的关键词文件名。  
locate命令比find快得多，原因在于它不搜索具体目录，而是搜索一个数据库(/var/lib/locatedb)，这个数据库中含有本地所有文件信息。Linux系统自动创建这个数据库，并且每天自动更新一次，所以使用locate命令查不到最新变动过的文件。为了避免这种情况，可以在使用locate之前，先使用updatedb命令，手动更新数据库。(当前目录下有一个文件，而使用这个命令时却查找不到这个文件，就是因为数据库没有同步更新。)  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


#### find
[find基础](#find基础) &emsp; [find命令之prune](#find命令之prune) &emsp; [find命令之exec/ok](#find命令之execok) &emsp; [find命令之xargs](#find命令之xargs)  
[find的结果](#find的结果) &emsp; [find命令之-name、-path、-prune](#find命令之-name-path-prune)  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)  

##### find基础
find,查找文件  
$ find -name connection.c //在当前目录下查找名为connection.c的文件  
$ find . -name “connect\\*”  //可以使用通配符  
$ find /mnt/hgfs -name connection.c -exec ls -l {} \\;  
$ find /mnt/hgfs -name connection.c | xargs ls -l  
$ find . -name "\\*.c" //将目前目录及其子目录下所有延伸档名是c 的文件列出来  
$ find . -type f //将目前目录其其下子目录中所有一般文件列出  
$ find . -ctime -20 //将目前目录及其子目录下所有最近20 分钟内更新过的文件列出  

查找文件和目录：find path -name 'key_word'  
查找文件：find path -name 'key_word' -type f  
查找目录：find path -name 'key_word' -type d  

#-print 将查找到的文件输出到标准输出(默认就有该选项，不需要写)  
#-exec command {} \\;  将查到的文件执行command操作,注意{}和\\;之间有空格,{}内部没有空格。  
#-ok 和-exec相同，只不过在操作前要询用户  
格式中的[expression]是一个表达式。最基本的表达式分为三类：设置项(option)、测试项(test)、动作项(action)，这三类又可以通过逻辑运算符(operator)组合在一起形成更大更复杂的表达式。设置项(如-depth,-maxdepth等)针对这次查找任务，而不是仅仅针对某一个文件，设置项总是返回true；测试项(test)则不同，它针对具体的一个文件进行匹配测试，如-name,-num,-user等，返回true或者false；动作项(action)则是对某一个文件进行某种动作(最常见的如-print)，返回true或者false。正是[expression]部分的丰富，才使得find如此强大。此部分较复杂，后面慢慢说明。  
例如：  
find /packages/apps -name 'contacts' -type d//查找目录(名)  
find -name 'contacts' -type d //默认当前目录下查找，可省略路径名  
find . -name 1.txt //在当前目录及其子目录下查找文件“1.txt”；(.表示当前目录,可以省略不写，如：find -name 1.txt。)  
find /tmp -name 1.txt //在“/tmp”目录及其子目录下查找文件“1.txt”。  
$find . -name CallLog.java -print  #默认就有.和-print,不需要写，直接写成$find -name CallLog.java就可以。  
#默认就是在当前目录、默认打印到标准输出。  

**$ find [path] [options] [tests] [actions]**  
**$ find [path] [options] expression** //也有资料表示成这种形式  
参考：linux程序设计(第4版),Neil Matthew,陈建, 第2章shell程序设计--2.6.5 命令--17 find、grep  
选项和参数：
path：所要搜索的目录及其所有子目录。省略的时候默认为当前目录。  
options：所要搜索的文件的特征。  
expression：对搜索结果进行特定的处理。  
options：  
-name  按照文件名查找文件  
-user   按照文件属主来查找文件。  
-size     按大小查找，以block为单位，一个block是512B  
-mtime -n +n  按照文件的更改时间来查找文件，-n表示文件更改时间距现在n天以内，+n表示文件更改时间距现在n天以前。find命令还有-atime和-ctime选项。  
-perm     按文件权限查找  
-mount, -xdev:只检查和指定目录在同一个文件系统下的文件,避免列出其它文件系统中的文件  
-amin n:在过去n 分钟内被读取过  
-anewer file:比文件file 更晚被读取过的文件  
-atime n:在过去n 天过读取过的文件  
-cmin n:在过去n 分钟内被修改过  
-cnewer file :比文件file 更新的文件  
-ctime n:在过去n 天过修改过的文件  
-empty:空的文件-gid n or -group name:gid 是n 或是group 名称是name  
-size n:文件大小是n 单位,b 代表512 位元组的区块,c 表示字元数,k 表示kilo bytes,w 是二个位元组。  
-type c:按文件类型查找，文件类型如下，  
d: 目录，c: 字型装置文件，b: 区块装置文件，p: 具名贮列，f: 一般文件，l: 符号连结，s: socket  
-path p:按照路径名查找文件,路径名称符合p的文件, -ipath p会忽略大小写  
-name name:按照文件名查找文件,文件名称符合name 的文件。-iname name会忽略大小写  
注意：-path和-name一样，都是按照名字查找，只不过一个代表目录名字，一个代表文件名字：普通文件。  
注意：目录也是文件：目录文件。  
因此，find -path /path1/path2/dir应该等效于find -type d -name dir。  
-pid n:process id 是n 的文件  
-atime    按最后一次访问时间查找  
-prune  使用这一选项可以使find命令不在当前指定的目录中查找，如果同时使用-depth选项，那么-prune将被find 命令忽略。//不仅仅是目录，可以忽略某个目录、或者文件。  
-group  按照文件所属的组来查找文件。  
-nogroup  查找无有效所属组的文件，即该文件所属的组在/etc/groups中不存在。  
-nouser   查找无有效属主的文件，即该文件的属主在/etc/passwd中不存在。  
-newer file1 ! file2  查找更改时间比文件file1新但比文件file2旧的文件。  
-size n：[c] 查找文件长度为n块的文件，带有c时表示文件长度以字节计。-depth：在查找文件时，首先查找当前 目录中的文件，然后再在其子目录中查找。  
-fstype：查找位于某一类型文件系统中的文件，这些文件系统类型通常可以在配置文件/etc/fstab中找到，该配置文 件中包含了本系统中有关文件系统的信息。  
-mount：在查找文件时不跨越文件系统mount点。  
-follow：如果find命令遇到符号链接文件，就跟踪至链接所指向的文件。  
-cpio：对匹配的文件使用cpio命令，将这些文件备份到磁带设备中。  
另外,下面三个的区别:  
-amin n   查找系统中最后N分钟访问的文件               -access  
-atime n  查找系统中最后n\\*24小时访问的文件  
-cmin n   查找系统中最后N分钟被改变文件状态的文件     -chmod?  
-ctime n  查找系统中最后n\\*24小时被改变文件状态的文件  
-mmin n   查找系统中最后N分钟被改变文件数据的文件    -modify  
-mtime n  查找系统中最后n\\*24小时被改变文件数据的文件  
如果什么参数也不加，find默认搜索当前目录及其子目录，并且不过滤任何结果(也就是返回所有文件)，将它们全都显示在屏幕上。  
//上述-path和下述path参数有什么区别？ 参考：find,grep详解.doc -> 例子和解释  

find根据下列规则判断path和expression：在命令列上第一个-之前的部份为path,之后的是expression。如果path是空则使用当前路径,如果expression是空则使用-print为预设expression。  
expression: 可使用的选项有二三十个之多,在此只介绍最常用的部份。  
-print:将匹配的文件输出到标准输出。  
-exec:对匹配的文件执行该参数所给出的shell命令。相应命令的形式为'command' {} \\;，注意{}和\\;之间有空格,{}内部没有空格。  
-ok:和-exec的作用相同，只不过以一种更为安全的模式来执行该参数所给出的shell命令，在执行每一个命令之前，都会给出提示，让用户来确定是否执行。  
[*返回:find*](#find)          &emsp;&emsp;              [*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


##### find的结果  
$ find [path] [options] [tests] [actions]  
$ find [path] [options] expression  //也有资料表示成这种形式  
如果path是绝对路径，那么find的结果也是绝对路径，如果path是相对路径，那么find的结果也是相对路径。  
sgk@ubuntu:/mnt/hgfs/github/daily_use$ find . -name *.md //结果是相对路径  
./article/我生命中的三个故事.乔布斯.md  
./CC++/ASCII码表.md  
./CC++/C语言数据类型&类型转换.md  
./CC++/C语言运算符优先级.md  
sgk@ubuntu:/mnt/hgfs/github/daily_use$ find -name *.md //省略path，表示从当前目录开始查找，也是相对路径  
./article/我生命中的三个故事.乔布斯.md  
./CC++/ASCII码表.md  
./CC++/C语言数据类型&类型转换.md  
./CC++/C语言运算符优先级.md  
sgk@ubuntu:/mnt/hgfs/github/daily_use$ find /mnt/hgfs/github/daily_use -name *.md //结果是绝对路径  
/mnt/hgfs/github/daily_use/article/我生命中的三个故事.乔布斯.md  
/mnt/hgfs/github/daily_use/CC++/ASCII码表.md  
/mnt/hgfs/github/daily_use/CC++/C语言数据类型&类型转换.md  
/mnt/hgfs/github/daily_use/CC++/C语言运算符优先级.md  

因此，在使用-path选项时要注意，如果path参数是相对路径，那么-path选项的参数也要使用相对路径，如果path参数是绝对路径，那么-path选项的参数也要使用绝对路径。否则不起作用。  
sgk@ubuntu:/mnt/hgfs/github/daily_use$ find . -path ./.git -prune -o -path ./article -prune -o -name *.md -print  
./CC++/ASCII码表.md  
./CC++/C语言数据类型&类型转换.md  
./CC++/C语言运算符优先级.md  
sgk@ubuntu:/mnt/hgfs/github/daily_use$ find -path ./.git -prune -o -path ./article -prune -o -name *.md -print  
./CC++/ASCII码表.md  
./CC++/C语言数据类型&类型转换.md  
./CC++/C语言运算符优先级.md  
/mnt/hgfs/github/daily_use$ find /mnt/hgfs/github/daily_use -path /mnt/hgfs/github/daily_use/.git -prune -o -path /mnt/hgfs/github/daily_use/article -prune -o -name *.md -print  
/mnt/hgfs/github/daily_use/CC++/ASCII码表.md  
/mnt/hgfs/github/daily_use/CC++/C语言数据类型&类型转换.md  
/mnt/hgfs/github/daily_use/CC++/C语言运算符优先级.md  
写成$ find /mnt/hgfs/github/daily_use/article -path ./.git -prune -o -path ./article -prune -o -name *.md -print、或$ find /mnt/hgfs/github/daily_use -path ./.git -prune -o -path ./article -prune -o -name *.md -print是错误的。  
[*返回:find*](#find)          &emsp;&emsp;              [*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


##### find命令之-name、-path、-prune
**-path pattern**  
    File name matches shell pattern pattern.  The metacharacters do not treat `/' or `.' specially; so, for example,  
find . -path "./sr*sc"  
will print an entry for a directory called `./src/misc' (if one exists).  To ignore a whole directory tree, use -prune rather than checking  every file in the tree.  For example, to skip the directory `src/emacs' and all files and directories under it, and print
the names of the other files found, do something like this:  
        find . -path ./src/emacs -prune -o -print  
**-name pattern**  
    Base  of  file name (the path with the leading directories removed) matches shell pattern pattern.  Because the leading directories are removed, the file names considered for a match with -name will never include a slash, so `-name a/b' will never match  anything (you  probably need to use -path instead).  
**-prune True;** if the file is a directory, do not descend into it. -prune用于忽略某个目录，不能用于忽略某个文件。  
因此，find -path pattern -prune -o print起作用，但是find -name pattern -prune -o print只在pattern表示目录名时起作用。  
[*返回:find*](#find)          &emsp;&emsp;              [*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


##### find命令之prune  
1.忽略某个目录：  
如果在查找文件时希望忽略某个目录，因为你知道那个目录中没有你所要查找的文件，那么可以使用-prune选项来指出需要忽略的目录。在使用-prune选项时要当心，因为如果你同时使用了-depth选项，那么-prune选项就会被find命令忽略。如果希望在test目录下查找文件，但不希望在test/test3目录下查找，可以用：  
[root@localhost soft]# find test -path "test/test3" -prune -o -print  
2.使用find查找文件的时候怎么避开某个文件目录：  
实例1：在test 目录下查找不在test4子目录之内的所有文件  
[root@localhost soft]# find test -path "test/test4" -prune -o -print  
说明：-path "test" -prune -o -print 是 -path "test" -a -prune -o -print 的简写表达式按顺序求值, -a 和 -o 都是短路求值，与 shell 的 && 和 || 类似如果。  
-path "test" 为真，则求值 -prune , -prune 返回真，与逻辑表达式为真；否则不求值 -prune，与逻辑表达式为假。如果 -path "test" -a -prune 为假，则求值 -print ，-print返回真，或逻辑表达式为真；否则不求值 -print，或逻辑表达式为真。  
这个表达式组合特例可以用伪码写为:  
if -path "test" then  
-prune  
else  
-print  
实例2：避开多个文件夹:  
[root@localhost soft]# find test \\( -path test/test4 -o -path test/test3 \\) -prune -o -print  
说明：圆括号表示表达式的组合。\\表示引用，即指示 shell 不对后面的字符作特殊解释，而留给 find 命令去解释其意义。  
实例3：查找某一确定文件，-name等选项加在-o 之后  
[root@localhost soft]# find test \\( -path test/test4 -o -path test/test3 \\) -prune -o -name "\\*.log" -print  

$ find -name Contacts -prune -o -name Mms -prune -o -name PhoneApp.java  
./Contacts //为什么会打印？  
./Mms       //为什么会打印？  
./Phone/src/com/android/phone/PhoneApp.java  
$ find -name Contacts -prune -o -name Mms -prune -o -name PhoneApp.java -print  
./Phone/src/com/android/phone/PhoneApp.java     → 加-print才能显示正确的结果  
结论：不加-print会打印一些无关信息，正常使用必须加-print / -print0。  
[*返回:find*](#find)          &emsp;&emsp;              [*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


##### find命令之exec/ok
实例1：ls -l命令放在find命令的-exec选项中  
[root@localhost test]# find . -type f -exec ls -l {} \\;  
-rw-r--r-- 1 root root 127 10-28 16:51 ./log2014.log  
-rw-r--r-- 1 root root 0 10-28 14:47 ./test4/log3-2.log  
-rw-r--r-- 1 root root 0 10-28 14:47 ./test4/log3-3.log  
-rw-r--r-- 1 root root 0 10-28 14:47 ./test4/log3-1.log  
-rw-r--r-- 1 root root 33 10-28 16:54 ./log2013.log  
上面的例子中，find命令匹配到了当前目录下的所有普通文件，并在-exec选项中使用ls -l命令将它们列出。  

find是我们很常用的一个Linux命令，但是我们一般查找出来的并不仅仅是看看而已，还会有进一步的操作，这个时候exec的作用就显现出来了。  
exec解释：  
-exec command {} \\; -- 对find结果对应的文件执行该参数所给出的shell命令。注意{}和\\;之间有空格,{}内部没有空格。command命令以;为结束标志，所以这句命令后面的分号是不可缺少的，考虑到各个系统中分号会有不同的意义，所以前面加反斜杠。  
**{}   花括号代表前面find查找出来的文件名。**  
使用find时，只要把想要的操作写在一个文件里，就可以用exec来配合find查找，很方便的。在有些操作系统中只允许-exec选项执行诸如ls或ls -l这样的命令。大多数用户使用这一选项是为了查找旧文件并删除它们。建议在真正执行rm命令删除文件之前，最好先用ls命令看一下，确认它们是所要删除的文件。 exec选项后面跟随着所要执行的命令或脚本，然后是一对儿{}，一个空格和一个\\，最后是一个分号。为了使用exec选项，必须要同时使用print选项。如果验证一下find命令，会发现该命令只输出从当前路径起的相对路径及文件名。  

实例2：在目录中查找更改时间在n日以前的文件并删除它们  
命令：find . -type f -mtime +14 -exec rm {} \\;  
说明：在shell中用任何方式删除文件之前，应当先查看相应的文件，一定要小心。当使用诸如mv或rm命令时，可以使用-exec选项的安全模式。它将在对每个匹配到的文件进行操作之前提示你。  
-ok:和-exec的作用相同，只不过以一种更为安全的模式来执行该参数所给出的shell命令，在执行每一个命令之前，都会给出提示，让用户来确定是否执行。  

实例3：在目录中查找更改时间在n日以前的文件并删除它们，在删除之前先给出提示  
命令：find . -name "\\*.log" -mtime +5 -ok rm {} \\;  
说明：在上面的例子中， find命令在当前目录中查找所有文件名以.log结尾、更改时间在5日以上的文件，并删除它们，只不过在删除之前先给出提示。 按y键删除文件，按n键不删除。  

实例4：-exec中使用grep命令  
[root@localhost test]# find /etc -name "passwd\\*" -exec grep "root" {} \\;  
root:x :0:0:root:/root:/bin/bash  
root:x :0:0:root:/root:/bin/bash  
说明：任何形式的命令都可以在-exec选项中使用。  在上面的例子中我们使用grep命令。find命令首先匹配所有文件名为“ passwd\\*”的文件，例如passwd、passwd.old、passwd.bak，然后执行grep命令看看在这些文件中是否存在一个root用户。  

实例5：查找文件移动到指定目录  
[root@localhost test3]# find . -name "\\*.log" -exec mv {} .. \\;  

实例6：用exec选项执行cp命令  
[root@localhost test]# find . -name "\\*.log" -exec cp {} test3 \\;  

$find ./.thumbnails/\\* -type f -atime +7 -exec rm {} \\; //用户家目录下的.thumnails目录下是一些缓存信息，删除7天以上的缓存  
[*返回:find*](#find)          &emsp;&emsp;              [*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


##### find命令之xargs  
加xargs、不加xargs的不同：  
①首先，要理解find -type f的输出是什么？  
find的输出是字符，这些字符是文件名(包括普通文件和目录文件)，find -type f输出的是普通文件的文件名。  
②find -type f | grep "main2015.\*"，grep是对find的结果字符本身进行过滤，如./main20150428111123.log。  
③find -type f | xargs grep "main2015.\*"，grep是把find的结果字符当做文件名、然后对文件的内容进行过滤。  

**xargs, a UNIX and Linux command for building and executing command lines from standard input. Examples of cutting by character, byte position, cutting based on delimiter and how to modify the output delimiter.**  
**xargs的作用就是，从标准输入读取字符，将读取到的字符和xargs后其他字符一起组建成命令，然后执行该命令。--读取字符、组建命令、执行命令。  
例find -type f | xargs grep "something.\*"，xargs从管道|读取find -type f的输出字符，如./filename.txt，将读取到的字符和grep "something.\*"一起组建成命令，如grep "something.\*" ./filename.txt，并执行该命令。
find -type f | xargs grep -i "something.\*"，也一样，读取字符、组建成命令grep -i "something.\*" ./filename.txt。
xargs一次读取多少字符呢？ 默认读取一行，可以指定delimiter，一次读取字符个数由分隔符delimiter决定。
总结：xargs做了三件事：读取字符、组建命令、执行命令。**  
参考：https://shapeshed.com/unix-xargs/  
--很多书上的中文完全没有将这个意思翻译出来，大多偏重于介绍xargs可以接收很长的输出。看这种资料还是看英文原文好。  


在使用 find命令的-exec选项处理匹配到的文件时，find命令将所有匹配到的文件一起传递给exec执行。但有些系统对能够传递给exec的命令长度有限制，这样在find命令运行几分钟之后，就会出现溢出错误。错误信息通常是“参数列太长”或“参数列溢出”。这就是xargs命令的用处所在，特别是与find命令一起使用。  
find命令把匹配到的文件传递给xargs命令，而xargs命令每次只获取一部分文件而不是全部，不像-exec选项那样。这样它可以先处理最先获取的一部分文件，然后是下一批，并如此继续下去。  
在有些系统中，使用-exec选项会为处理每一个匹配到的文件而发起一个相应的进程，并非将匹配到的文件全部作为参数一次执行；这样在有些情况下就会出现进程过多，系统性能下降的问题，因而效率不高； 而使用xargs命令则只有一个进程。另外，在使用xargs命令时，究竟是一次获取所有的参数，还是分批取得参数，以及每一次获取参数的数目都会根据该命令的选项及系统内核中相应的可调参数来确定。  

实例1： 查找系统中的每一个普通文件，然后使用xargs命令来测试它们分别属于哪类文件  
[root@localhost test]# find . -type f -print | xargs file  

实例2：在整个系统中查找内存信息转储文件(core dump) ，然后把结果保存到/tmp/core.log 文件中  
[root@localhost test]# find / -name "core" -print | xargs echo "" >/tmp/core.log  

实例3:在当前目录下查找所有用户具有读、写和执行权限的文件，并收回相应的写权限  
[root@localhost test]# find . -perm -7 -print | xargs chmod o-w  

实例4：用grep命令在所有的普通文件中搜索hostname这个词  
[root@localhost test]# find . -type f -print | xargs grep "hostname"  

实例5：用grep命令在当前目录下的所有普通文件中搜索hostnames这个词  
[root@peida test]# find . -name \\\\* -type f -print | xargs grep "hostnames"  
说明：注意，在上面的例子中， \\用来取消find命令中的\\*在shell中的特殊含义。  

实例6：使用xargs执行mv  
命令：find . -name "\\*.log" | xargs -i mv {} test4  

实例7：find后执行xargs提示xargs: argument line too long解决方法：  
[root@pd test4]#  find . -type f -atime +0 -print0 | xargs -0 -l1 -t rm -f  
说明：-l1是一次处理一个；-t是处理之前打印出命令  

实例8：使用-i参数默认的前面输出用{}代替，-i参数可以指定其他代替字符，如例子中的[]  
[root@localhost test4]# find . -name "file" | xargs -I [] cp [] ..  
说明：使用-i参数默认的前面输出用{}代替，-I参数可以指定其他代替字符，如例子中的[]  

实例9：xargs的-p参数的使用  
[root@localhost test3]#  find . -name "\\*.log" | xargs -p -i mv {} ..  
说明：-p参数会提示让你确认是否执行后面的命令,y执行，n不执行。  

xargs是给命令传递参数的一个过滤器，也是组合多个命令的一个工具。它把一个数据流分割为一些足够小的块，以方便过滤器和命令进行处理。通常情况下，xargs从管道或者stdin中读取数据，但是它也能够从文件的输出中读取数据。xargs的默认命令是echo，这意味着通过管道传递给xargs的输入将会包含换行和空白，不过通过xargs的处理，换行和空白将被空格取代。  
xargs 是一个强有力的命令，它能够捕获一个命令的输出，然后传递给另外一个命令，下面是一些如何有效使用xargs 的实用例子。  
参考xargs命令。  
$ find /etc -name "\\*" | xargs grep "hello abcserver"  
$ find . -path './kernel' -prune -o -name '.git' -type d | xargs rm –rfv  
$ find . -path './kernel' -prune -o -name '.gitignore' -type f | xargs rm -rfv  
[*返回:find*](#find)          &emsp;&emsp;              [*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


#### xargs  
xargs是一条Unix和类Unix操作系统的常用命令。它的作用是将参数列表转换成小块分段传递给其他命令，以避免参数列表过长的问题。  
例如，下面的命令：  
rm `find /path -type f`  
如果path目录下文件过多就会因为“参数列表过长”而报错无法执行。但改用xargs以后，问题即获解决。  
find /path -type f -print0 | xargs -0 rm  
本例中xargs将find产生的长串文件列表拆散成多个子串，然后对每个子串调用rm。-print0表示输出以null分隔(-print使用换行)；-0表示输入以null分隔。这样要比如下使用find命令效率高的多。  
find /path -type f -exec rm '{}' \\;  
上面这条命令会对每个文件调用"rm"命令。当然使用新版的"find"也可以得到和"xargs"命令同样的效果：  
find /path -type f -exec rm '{}' +  
xargs的作用一般等同于大多数Unix shell中的反引号，但更加灵活易用，并可以正确处理输入中有空格等特殊字符的情况。对于经常产生大量输出的命令如find、locate和grep来说非常有用。  
示例  
find . -name "\\*.foo" | xargs grep bar  
该命令大体等价于  
grep bar `find . -name "\\*.foo"`  
find . -name "\\*.foo" -print0 | xargs -0 grep bar  
使用了GNU特殊规定的空字符。  
find . -name "\\*.foo" -print0 | xargs -0 -t -r vi  
与上面的基本相同但启动vi进行编辑。-t参数会提前打印错误信息。-r参数是一个GNU扩展，表明在无输入情况下则不构造命令执行。  
find . -name "\\*.foo" -print0 | xargs -0 -i mv {} /tmp/trash  
使用-i参数将{}中内容替换为列表中的内容。  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


#### grep
grep: General Regular Expression Parser -- 由名字可知,grep后面的参数是当做正则表达式来处理的,例 ls -l | grep ^d。  
格式：grep [options] pattern filenames  

grep这个应用程序最早由肯·汤普逊写成。grep原先是ed下的一个应用程序，名称来自于g/re/p（globally search a regular expression and print，以正则表达式进行全局查找以及打印）。在ed下，输入g/re/p这个命令后，会将所有符合先定义样式的字符串，以行为单位打印出来。  

Grep, which stands for "global regular expression print," is a powerful tool for matching a regular expression against text in a file, multiple files, or a stream of input. It searches for the PATTERN of text that you specify on the command line, and outputs the results for you.  

grep过滤.o文件怎么写？grep "\.o"？grep "\*.o"？  
查找以.o结尾的文件，正确的写法是grep "\.o\>"或grep "\.o$"。grep "\*.o"是错误的,re量词\*不能作为第一个字符，grep "\.o"也是错误的，其结果是只要名字中有字母.o就可以，不一定.o是出现在文件名末尾作为后缀。  


grep,搜索文件中匹配符  
[root@localhost test]# grep 'linux' test.txt     /  grep -n 'linux' test.txt //显示对应的行号  
[root@localhost test]# cat test.txt | grep 'linux'  /  cat test.txt | grep -n 'linux'  

grep [options] pattern filenames  
逐行搜索所指定的文件或标准输入，并显示匹配模式的每一行。  
grep: General Regular Expression Parser.  
常用选项：  
-a 不要忽略二进制数据。  
-A<显示列数> 除了显示符合范本样式的那一行之外，并显示该行之后的内容。  
-b 在显示符合范本样式的那一行之外，并显示该行之前的内容。  
-c 计算符合范本样式的列数。  
-C<显示列数>或-<显示列数>  除了显示符合范本样式的那一列之外，并显示该列之前后的内容。  
-d<进行动作> 当指定要查找的是目录而非文件时，必须使用这项参数，否则grep命令将回报信息并停止动作。  
-e<范本样式> 指定字符串作为查找文件内容的范本样式。  
-E 将范本样式为延伸的普通表示法来使用，意味着使用能使用扩展正则表达式。  
-f<范本文件> 指定范本文件，其内容有一个或多个范本样式，让grep查找符合范本条件的文件内容，格式为每一列的范本样式。  
-F 将范本样式视为固定字符串的列表。  
-G 将范本样式视为普通的表示法来使用。  
-h 在显示符合范本样式的那一列之前，不标示该列所属的文件名称。  
-H 在显示符合范本样式的那一列之前，标示该列的文件名称。  
-i 忽略字符大小写的差别。  
-l 列出文件内容符合指定的范本样式的文件名称。  
-L 列出文件内容不符合指定的范本样式的文件名称。  
-n 在显示符合范本样式的那一列之前，标示出该列的编号。  
-q 不显示任何信息。  
-R/-r 此参数的效果和指定“-d recurse”参数相同。  
-s 不显示错误信息。  
-v 反转查找。  
-w 只显示全字符合的列。  
-x 只显示全列符合的列。  
-y 此参数效果跟“-i”相同。  
-o 只输出文件中匹配到的部分。  

grep可单独使用，也可以配合其他命令、与管道符’|’一起使用，过滤。  
例如：$ ls | grep ‘Android’ //过滤，只显示包含Android字符的结果，单引号也可以不要，$ ls | grep Android，$ ls | grep ‘Android’都可以，但是，如果要过滤的字符串包含空格，那么必须用单引号括起来，例：$ ls | grep ‘du kang’  

grep的工作方式是这样的，它在一个或多个文件中搜索字符串模板。如果模板包括空格，则必须被引用。模板(pattern)后的所有字符串被看作文件名。搜索的结果被送到标准输出，不影响原文件内容。  
grep可用于shell脚本，因为grep通过返回一个状态值来说明搜索的状态，如果模板搜索成功，则返回0，如果搜索不成功，则返回1，如果搜索的文件不存在，则返回2。我们利用这些返回值就可进行一些自动化的文本处理工作。  

grep: General Regular Expression Parser.grep (global search regular expression(RE) and print out the line,全面搜索正则表达式并把行打印出来)是一种强大的文本搜索工具，它能使用正则表达式搜索文本，并把匹配的行打印出来。  
Unix的grep家族包括grep、egrep和fgrep。egrep和fgrep的命令只跟grep有很小不同。egrep是grep的扩展，支持更多的正则表达式元字符， fgrep就是fixed grep或fast grep，它们把所有的字母都看作单词，也就是说，正则表达式中的元字符表示回其自身的字面意义，不再特殊。Linux使用GNU版本的grep。它功能更强，可以通过-G、-E、-F命令行选项来使用egrep和fgrep的功能。  
grep可用于shell脚本，因为grep通过返回一个状态值来说明搜索的状态，如果模板搜索成功，则返回0，如果搜索不成功，则返回1，如果搜索的文件不存在，则返回2。我们利用这些返回值就可进行一些自动化的文本处理工作。  

grep支持的正则表达式元字符集  
^ 锚定行的开始 如：'^grep'匹配所有以grep开头的行。  
$ 锚定行的结束 如：'grep$'匹配所有以grep结尾的行。  
匹配一个非换行符的字符 如：'gr.p'匹配gr后接一个任意字符，然后是p。  
\\* 匹配零个或多个先前字符 如：'\\*grep'匹配所有一个或多个空格后紧跟grep的行。 .\\*一起用代表任意字符。  
[] 匹配一个指定范围内的字符，如'[Gg]rep'匹配Grep和grep。  
[^] 匹配一个不在指定范围内的字符，如：'[^A-FH-Z]rep'匹配不包含A-R和T-Z的一个字母开头，紧跟rep的行。  
(..) 标记匹配字符，如'(love)'，love被标记为1。  
< 锚定单词的开始，如:'  
> 锚定单词的结束，如'grep>'匹配包含以grep结尾的单词的行。  
x\\{m\\} 重复字符x，m次，如：'0\\{5\\}'匹配包含5个o的行。  
x\\{m,\\} 重复字符x,至少m次，如：'o\\{5,\\}'匹配至少有5个o的行。  
x\\{m,n\\} 重复字符x，至少m次，不多于n次，如：'o\\{5,10\\}'匹配5--10个o的行。  
w 匹配文字和数字字符，也就是[A-Za-z0-9]，如：'Gw\\*p'匹配以G后跟零个或多个文字或数字字符，然后是p。  
W w的反置形式，匹配一个或多个非单词字符，如点号句号等。  
b 单词锁定符，如: 'bgrepb'只匹配grep。  
关于正则表达式的更多内容请参考《正则表达式》  

用于egrep和 grep -E的元字符扩展集  
+ 匹配一个或多个先前的字符。如：'[a-z]+able'，匹配一个或多个小写字母后跟able的串，如loveable,enable,disable等。  
? 匹配零个或多个先前的字符。如：'gr?p'匹配gr后跟一个或没有字符，然后是p的行。  
a|b|c 匹配a或b或c。如：grep|sed匹配grep或sed  
() 分组符号，如：love(able|rs)ov+匹配loveable或lovers，匹配一个或多个ov。  
x{m},x{m,},x{m,n} 作用同x\\{m\\},x\\{m,\\},x\\{m,n\\}  
关于正则表达式的更多内容请参考《正则表达式》  

POSIX字符类  
为了在不同国家的字符编码中保持一至，POSIX(The Portable Operating System Interface)增加了特殊的字符类，如[:alnum:]是A-Za-z0-9的另一个写法。要把它们放到[]号内才能成为正则表达式，如[A- Za-z0-9]或[[:alnum:]]。在Linux下的grep除fgrep外，都支持POSIX的字符类。  
[:alnum:] 文字数字字符  
[:alpha:] 文字字符  
[:digit:] 数字字符  
[:graph:] 非空字符(非空格、控制字符)  
[:lower:] 小写字符  
[:cntrl:] 控制字符  
[:print:] 非空字符(包括空格)  
[:punct:] 标点符号  
[:space:] 所有空白字符(新行，空格，制表符)  
[:upper:] 大写字符  
[:xdigit:] 十六进制数字(0-9，a-f，A-F)  

例子  
(1)ls -l | grep '^a'  //通过管道过滤ls -l输出的内容，只显示以a开头的行。  
(2)grep 'test' d\\*   //显示所有以d开头的文件中包含test的行。  
(3)grep 'test' aa bb cc  //显示在aa，bb，cc文件中匹配test的行。  
(4)grep magic /usr/src　　#显示/usr/src目录下的文件(不含子目录)包含magic的行  
(5)grep -r magic /usr/src　　#显示/usr/src目录下的文件(包含子目录)包含magic  
(6)grep -w pattern files ：只匹配整个单词，而不是字符串的一部分(如匹配’magic’，而不是’magical’)，  
(7)grep '[a-z]\\{5\\}' aa  //显示所有包含每个字符串至少有5个连续小写字符的字符串的行。  
(8)grep 'w\\(es\\)t.\\*\\1' aa  //如果west被匹配，则es就被存储到内存中，并标记为1，然后搜索任意个字符(.\\*)，这些字符后面紧跟着另外一个es(\\1)，找到就显示该行。如果用egrep或grep -E，就不用"\\"号进行转义，直接写成'w(es)t.\\*\\1'就可以了。  
http://bbs.chinaunix.net/thread-1687220-1-1.html  ，http://blog.csdn.net/hudashi/article/details/7066214  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


#### egrep
egrep,搜索文件中匹配符  
正则表达式根据元字符的数量及功能不同又分为基本正则表达式（grep）和拓展正则表达式（egrep）。  
egrep命令用于在文件内查找指定的字符串。egrep执行效果与grep -E相似，使用的语法及参数可参照grep指令，与grep的不同点在于解读字符串的方法。egrep是用extended regular expression语法来解读的，而grep则用basic regular expression 语法解读，extended regular expression比basic regular expression的表达更规范。  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


#### type
type,查找指定命令的类型  
$ type -a cd  
cd is a shell builtin  // cd是shell的自带命令(build-in)  

$ type -a ls  
ls is aliased to `ls --color=auto'  // ls是一个外部命令，并显示该命令的路径  
ls is /bin/ls  

$ type -p ls //加上-p参数后，就相当于which命令。  
type命令其实不能算查找命令，它是用来区分某个命令到底是由shell自带的，还是由shell外部的独立二进制文件提供的。如果一个命令是外部命令，那么使用-p参数，会显示该命令的路径，相当于which命令。  
type命令用来显示指定命令的类型。一个命令的类型可以是如下之一，  
•alias 别名  
•keyword 关键字，Shell保留字  
•function 函数，Shell函数  
•builtin 内建命令，Shell内建命令  
•file 文件，磁盘文件，外部命令  
•unfound 没有找到  
type命令是Linux系统的一种机制，知道了是那种类型，我们就可以针对性的获取帮助。比如内建命令可以用help命令来获取帮助，外部命令用man或者info来获取帮助。  
选项参数：  
-a可以显示所有可能的类型，比如有些命令如pwd是shell内建命令，也可以是外部命令。  
-p只返回外部命令的信息，相当于which命令。  
-f只返回shell函数的信息。  
-t 只返回指定类型的信息。  

type命令也可以用来查看当前shell中的名字是否定义,如查看函数或变量是否定义。  
例如，在执行Android源码目录下build/envsetup.sh脚本之前，查找cgrep的结果是找不到，在执行脚本之后，会显示cgrep是一个函数。  
$ type cgrep  
bash: type: cgrep :not found //没找到,未定义,说明不是命令、函数、变量。  
$ . build/envsetup.sh  
$ type cgrep  
cgrep is a function //执行完envsetup.sh后,cgrep变成了已定义,cgrep是一个函数。下面是其定义的内容。  
cgrep(){ find . -name .repo -prune -o -name .git -prune -o -type f \\( -name ‘\\*.c’ -o -name ‘\\*.cc’ -o -name ‘\\*.cpp’ -o -name ‘\\*.h’ \\) -print0 | xargs -0 grep --color -n “$@” }  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)


#### 小结.查找  
which      看可执行文件和别名的位置  
whereis    查看可执行文件的位置  
locate      配合数据库查看文件位置  
find       实际搜寻硬盘查询文件名称  
type       显示指定命令的类型  
   查询系统档案时，通常不大用find的，因为速度慢之外，也很操硬盘。但不可否认，find的功能很强大。通常我们都是先使用whereis 或者是locate来检查，如果真的找不到了，才以 find 来搜寻。为什么呢？因为whereis与locate是利用数据库来搜寻数据，所以相当的快速，而且并没有实际的搜寻硬盘，比较省时间。  
   查找其他档案时，我们可以用locate和find来查询。一般先用locate查询，如果查询不到，可以先更新数据库,使用命令updatedb，也可以用find命令来查找。不过我通常用find查找，因为更新数据库太慢了。  

和find相比，whereis查找的速度非常快，这是因为linux系统会将系统内的所有文件都记录在一个数据库文件中，当使用whereis和locate时，会从数据库中查找数据，而不是像find命令那样，通过遍历硬盘来查找，效率自然会很高。  
但是该数据库文件并不是实时更新，默认情况下时一星期更新一次，因此，我们在用whereis和locate查找文件时，有时会找到已经被删除的数据，或者刚刚建立文件，却无法查找到，原因就是因为数据库文件没有被更新。  
当我们用whereis和locate无法查找到我们需要的文件时，可以使用find，但是find是在硬盘上遍历查找，因此非常消耗硬盘的资源，而且效率也非常低，因此建议大家优先使用whereis和locate。  
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)



### 字符处理  
[awk](#awk) &emsp; [sed](#sed)  

#### awk


#### sed
[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)




### 文件的切割、合并
Linux下文件切割、合并 的 三种方法：  
$ split + cat  
$ dd + cat  
$ knife + cat  

#### 1.split+cat,简单,推荐  
Linux下文件的切割与合并(split+cat)  
当前目录下有sp4.exe文件容量129M ，我用64M的U盘把spe.exe考到另一台机器上。这个U盘一次装不下129M ，只能将文件分割成多个小的部分，多次拷贝。  
**文件切割：**  
\# split -b 60m sp4.exe partial  //文件切割,分配每个切割大小为60MByte。  
用-b或-C指定分块大小。-b,--bytes=SIZE,SIZE值为每一输出档案的大小，单位为byte。-C,--line-bytes=SIZE。  
SIZE可加入单位: b 代表 512，k 代表 1K，m 代表1Meg。  
\# ls //按partialaa、partialab、partialac的格式生成如下文件,生成的文件自动添加了后缀aa/ab/ac  
-rw-r--r--    1 root     root     62914560  5月 18 00:40 partialaa   
-rw-r--r--    1 root     root     62914560  5月 18 00:41 partialab   
-rw-r--r--    1 root     root      8576176  5月 18 00:41 partialac   //partialaa/partialab为60mbyte，剩下的给partialac。  
**拷贝到另一台机器上，将多个部分合并：**  
\# cat partialaa partialab partialac > sp4.exe 或 cat partiala* > sp4.exe  //文件合并。用jion也可以合并。  
附注：  
#split -b 60m sp4.exe       //如果不指定输出名字，那么输出文件名将会是xaa,xab,…的形式。  
#split -b 60m sp4.exe split//指定输出文件名为split，那么输出文件将会是splitaa,splitab…,  

文件1.Android开发.zip,大小为3.9G，下面对它进行切割、合并操作。  
$ ls -l 1.Android开发.zip  
-rwx------+ 1 Administrators None 4196507906 Oct 13 22:41 1.Android开发.zip  
**切割：**  
$ split -b 2048m 1.Android_origin.zip partial //按2048M=2G大小切割。  
$ ls -l partiala\*  
-rw-r--r--+ 1 lenovo None 2147483648 Oct 14 00:13 partialaa  
-rw-r--r--+ 1 lenovo None 2049024258 Oct 14 00:14 partialab  
**合并：**  
$ cat partialaa partialab > backup_now.zip  
$ ls -l backup_now.zip  
-rw-r--r--+ 1 lenovo None 4196507906 Oct 14 00:19 backup_now.zip  

**$ split --help** 
Usage: split [OPTION]... [FILE [PREFIX]]  
Output pieces of FILE to PREFIXaa, PREFIXab, ...;  
default size is 1000 lines, and default PREFIX is 'x'.  
With no FILE, or when FILE is -, read standard input.  

Mandatory arguments to long options are mandatory for short options too.  
  -a, --suffix-length=N   generate suffixes of length N (default 2)  
      --additional-suffix=SUFFIX  append an additional SUFFIX to file names  
  -b, --bytes=SIZE        put SIZE bytes per output file  
  -C, --line-bytes=SIZE   put at most SIZE bytes of records per output file  
  -d                      use numeric suffixes starting at 0, not alphabetic  
   &emsp;&emsp;   --numeric-suffixes[=FROM]  same as -d, but allow setting the start value  
  -e, --elide-empty-files  do not generate empty output files with '-n'  
      --filter=COMMAND    write to shell COMMAND; file name is $FILE  
  -l, --lines=NUMBER      put NUMBER lines/records per output file  
  -n, --number=CHUNKS     generate CHUNKS output files; see explanation below  
  -t, --separator=SEP     use SEP instead of newline as the record separator; '\0' (zero) specifies the NUL character  
  -u, --unbuffered        immediately copy input to output with '-n r/...'  
      --verbose           print a diagnostic just before each output file is opened  
      --help     display this help and exit  
      --version  output version information and exit  

The SIZE argument is an integer and optional unit (example: 10K is 10*1024).  
Units are K,M,G,T,P,E,Z,Y (powers of 1024) or KB,MB,... (powers of 1000).  


#### 2.dd+cat  
Linux文件切割、合并(dd+cat)  
将一个140kbyte的文件originFile分割成两部分，一部分为part1，大小为60kbyte，剩下的分给另一部分part2。  
**文件切割**  
\# dd if=originFile bs=1024 count=60 skip=0    of=part1  //count*bs=60*1024byte=60kbyte  
\# dd if=originFile bs=1024 count=80 skip=60  of=part2  //skip=60,忽略file1已经切割的大小  
第一部分，count\*bs=60\*1024byte=60kbyte,  
第二部分，skip=60\*1024byte=60kbyte=第一部分的大小,剩下140kbyte-60kbyte=80kbyte=80\*1024byte。  
**文件合并**  
\# cat part1 part2 > bakFile  


#### 3.knife+cat  
knife工具到http://see.online.sh.cn/ch/sw/dl/split.htm下载。  
[root@rhas3 knife-2.0.1]\# ls  
knife  link  linkfiles.pl  sp4.exe  
**分割：**  
[root@rhas3 knife-2.0.1]# ./knife -c sp4.exe 500   ( 500：字节大小)   
Cutting......Cutted Over :-)   
[root@rhas3 knife-2.0.1]# ls -l   
总用量 44   
-rwxr-xr-x    1 root     root        12949 2000-02-28  knife  
-rwxr-xr-x    1 root     root           17 2000-02-28  link  
-rwxr-xr-x    1 root     root         1088 2000-02-28  linkfiles.pl  
-rw-r--r--    1 root     root         1543 2000-02-28  sp4.exe  
-rw-r--r--    1 root     root          500  5月 18 00:49 sp4.exe.k00  
-rw-r--r--    1 root     root          500  5月 18 00:49 sp4.exe.k01  
-rw-r--r--    1 root     root          500  5月 18 00:49 sp4.exe.k02  
-rw-r--r--    1 root     root           43  5月 18 00:49 sp4.exe.k03  

**合并：**  
[root@rhas3 knife-2.0.1]# ./link sp4.exe.k00 sp4.exe.k01 sp4.exe.k02 sp4.exe.k03                                                                                  
Please intput the file name you want to LINK up, one by one.  
Just input OK when you have finished inputting.(一定要全输完在ok)  
ok  
In this order:  
  
Now it's time you type the name of the output file.  
  
-->;sp4.exe  


#### 4.总结和技巧
字节为最小存储单位，byte。  
ls/split/dd等linux命令，使用的数据单位都是字节(byte)。  
$ ls -l | grep 1.Android  
-rwx------+ 1 Administrators None 4196507906 Oct 13 22:41 1.Android开发.zip  
4196507906指的是字节(bytes)。  

[*返回:专题讲解*](#专题讲解)          &emsp;&emsp;              [*返回:页首*](#Linux命令)




## 应用  
//TODO  
[*返回:应用*](#应用)          &emsp;&emsp;              [*返回:页首*](#Linux命令)




## 错误和注意  
### 1.删除指定类型的文件  
**使用git碰到的问题：git status | xargs rm \*.o ，本意只想删除.o文件，结果删除了所有被修改过的文件，包括.o文件、非.o文件，造成严重后果。**  
**同样，ls | xargs rm \*.o，并不是期望的那样只删除.o文件，会删除当前目录下全部普通文件，包括包括.o文件、非.o文件。**  

ls | xargs rm \*.o删除了当前目录下所有普通文件？为什么？
git status | xargs rm \*.o删除了所有修改过的文件？为什么？

rm \*.o是对的，只会删除.o文件，不会删除其他文件。  
**然而，把rm \*.o放到xargs后面，command | xargs rm \*.o，其意义和单独的rm \*.o不一样了。为什么？**  

解释：  
**xargs做了三件事：读取字符、组建命令、执行命令。**  
详细解释参考：find命令之xargs  

ls例举当前目录下所有文件，通过管道|输出给xargs，xargs从管道|读取ls的输出，如filename，和rm \*.o一起组建成命令：rm filename \*.o，然后执行命令，删除filename文件、和\*.o文件。由于ls例举了当前目录下所有文件，因此ls | xargs rm \*.o执行的结果就是删除当前目录下所有文件。  
git status | xargs rm \*.o，也一样，git status例举所有修改过的文件，因此……。  

[*返回:错误和注意*](#错误和注意)          &emsp;&emsp;              [*返回:页首*](#Linux命令)



## 问题  
//TODO  
[*返回:问题*](#问题)          &emsp;&emsp;              [*返回:页首*](#Linux命令)






