# 第一部分 入门

# 1)参考资料

Pro git(精通git)第二版

https://github.com/git-guides

https://git-scm.com/docs

https://learngit branching.js.org/

git高手之路\[波\]Jakub Narebski

cygwin安装目录下的文档：D:\\cygwin64\\usr\\share\\doc\\git\\、D:\\cygwin64\\usr\\share\\doc\\git\\html\\

![](media/image1.emf)

# 2)经验

1.拿到代码后第一件事：建立git仓库，便于以后对修改进行跟踪。

但要注意一点，如果代码本身已经有git仓库，但由于拷贝等原因造成没有分支、不在分支上，则需要先commit，再建分支，在新建分支上将之前提交cherry-pick到新建分支上。

对于大型项目应该建立多个git仓库，使用repo对多个git库进行管理。

2.忽略文件权限修改

\$ git status

old mode 100755 new mode 100644

文件内容没有改变，文件权限改变了，git status显示有修改。怎么让git
status不跟踪文件权限修改？

忽略文件权限变更：git config \--global core.filemode
false。或者修改.git/config文件，忽略文件权限修改。

\$ cat .git/config

\[core\]

filemode = false #忽略文件属性修改

要修改core.filemode，使用git config core.filemode \<value\>，其中\<value\>可以是以下三个值之一：

false:
Git将不会修改文件权限标志。这意味着在Windows上提交的文件将保留原始权限，而不会更改为可执行。

true: Git将在提交时修改文件权限标志，并将它们更改为可执行。

chmod:
Git将在提交时修改文件权限标志，并将其更改为可执行，但是只有在使用类UNIX系统的系统上才支持。

不同的配置文件

\~/.gitconfig \-- User-specific configuration file. Also called
\"global\" configuration file.

.git/config \-- Repository specific configuration file.

3.删除工作区全部文件、保留git库的方法，rm -rf
\*，这条命令不会删除隐藏文件，.git库目录不会删除。之后使用git
restore或git
checkout恢复，遇到无法完全清除的编译生成的文件，这个方法最彻底最快速。

4.分支

习惯建立**开发调试分支doing、dev、develop等**。

为了方便**回溯**，应该**保留开发过程细节，保留开发分支上多个小提交**。不要直接在开发调试分支上push代码，为了push代码，将开发调试分支上的多个提交合并成一个提交，万一有问题没法**回溯**，不可取。

**最好另外建一个分支for_push专门用于push代码**。在for_push分支cherry-pick开发分支的多个提交，合并成一个提交，之后再push。这样可以保留开发分支的多次修改细节，方便回溯。

5.git命令自动补全

见：1.1.实用：cygwin使用git.docx -\> git命令自动补全

6.通用参数

\--no-edit可用于git commit \--amend、git revert
SHA等需要修改提交注释的情况

\--continue、\--abort可用于git merge、git rebase、git cherry-pick、git
revert等需要多高步骤、中间修改的情况

-p可用于git log、git stash show查看修改记录的情况

\--name-status、\--name-only可用于git log、git show

git show SHA filepath、git diff SHA1 SHA2 filepath，SHA后可以加filepath

7.其他

\$ git add .

Another git process seems to be running in this repository, e.g.

an editor opened by \'git commit\'. Please make sure all processes

are terminated then try again. If it still fails, a git process

may have crashed in this repository earlier:

remove the file manually to continue.

\$ rm .git/index.lock //解决

8.cursor软件中的一些git用法

git -C \"D:\\ziliao\\code\\opensource\\klogg\" diff HEAD\~3 HEAD \--
src/ui/src/crawlerwidget.cpp

git -C \"D:\\ziliao\\code\\opensource\\klogg\" log \--all \--oneline \--
src/logdata/src/logfiltereddata.cpp \| head -20

git -C \"D:\\ziliao\\code\\opensource\\klogg\" show 8bbd446b \--
tests/ui/logfiltereddata_test.cpp

git -C \"D:\\ziliao\\code\\opensource\\klogg\" log \--all \--oneline \--
src/logdata/src/logfiltereddataworker.cpp
tests/ui/logfiltereddata_test.cpp

git -C \"D:\\ziliao\\code\\opensource\\klogg\" log \--all \--oneline
\--grep=\"tbb\\\|TBB\" \-- src/logdata \| head -20

git -C \"D:\\ziliao\\code\\opensource\\klogg\" log \--all \--oneline
\--grep=\"tbb\\\|TBB\" \--no-walk

git -C \"D:\\ziliao\\code\\opensource\\klogg\" show dec87ae7 \--stat

# 3)git使用入门(经典全面)

**手把手教你用git** <http://www.cnblogs.com/tugenhua0707/p/4050072.html>

### 一.git是什么？ 

       git是目前世界上最先进的分布式版本控制系统。

### 二.git与svn的最主要的区别？

     
SVN是集中式版本控制系统，版本库是集中放在中央服务器的，而干活的时候，用的都是自己的电脑，所以首先要从中央服务器哪里得到最新的版本，然后干活，干完后，需要把自己做完的活推送到中央服务器。集中式版本控制系统是必须联网才能工作，如果在局域网还可以，带宽够大，速度够快，如果在互联网下，如果网速慢的话，就纳闷了。

     
git是分布式版本控制系统，那么它就没有中央服务器的，每个人的电脑就是一个完整的版本库，这样，工作的时候就不需要联网了，因为版本都是在自己的电脑上。既然每个人的电脑都有一个完整的版本库，那多个人如何协作呢？比如说自己在电脑上改了文件A，其他人也在电脑上改了文件A，这时，你们两之间只需把各自的修改推送给对方，就可以互相看到对方的修改了。

### 三.安装git？

ubuntu安装git

apt安装git：

\$ apt install git

\$ git \--version / git version

For Ubuntu, this PPA provides the latest stable upstream git version

\$ add-apt-repository ppa:git-core/ppa ; apt update ; apt install git

或者，从源码安装git：

从https://mirrors.edge.kernel.org/pub/software/scm/git/或https://github.com/git/git/releases下载git源码，

\$ tar -zxf git-2.8.0.tar.gz

\$ cd git-2.8.0

\$ make configure

\$ ./configure \--prefix=/usr

\$ make all doc info //apt install asciidocss

\$ sudo make install install-doc install-html install-info //apt install
xmlto

来源：https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%AE%89%E8%A3%85-git

git 编译安装

1.下载git源码

\$ wget https://github.com/git/git/archive/v2.3.0.zip

\$ unzip v2.3.0.zip

\$ cd git-2.3.0

2.安装在"/usr/local/git"目录下

make prefix=/usr/local/git all

sudo make prefix=/usr/local/git install

3.修改环境变量

此时如果使用git
\--version查看git版本的话，发现git仍然是1.7.1版本。这是因为它默认使用了\"/usr/bin\"下的git。

可以用下面的命令查看git所在的路径：

\$ whereis git

git: /usr/bin/git /usr/local/git /usr/share/man/man1/git.1.gz

要把编译安装的git路径放到环境变量里，让它替换\"/usr/bin\"下的git。可以修改"/etc/profile"文件(或者/etc/bashrc文件)。

sudo vim /etc/profile

在文件的最后一行，添加下面的内容

export PATH=/usr/local/git/bin:\$PATH

应用修改

source /etc/profile

再次使用git \--version 查看git版本，已经是2.3.0了，安装成功。

**windows安装git**

msysgit是 windows版的git,如下：

![](media/image2.jpeg){width="1.992361111111111in" height="0.23125in"}

 需要从网上下载一个，然后进行默认安装即可。安装完成后，在开始菜单里面找到
\"git\--\> git bash\",如下：

  ![](media/image3.jpeg){width="1.7534722222222223in"
height="0.5076388888888889in"}

会弹出一个类似的命令窗口的东西，就说明git安装成功。如下：

 ![](media/image4.png){width="3.4402777777777778in"
height="0.9402777777777778in"}

安装完成后，还需要最后一步设置，在命令行输入如下：

 ![](media/image5.jpeg){width="4.201388888888889in"
height="1.3881944444444445in"}

  因为git是分布式版本控制系统，所以需要填写用户名和邮箱作为一个标识。

**   注意：**git config \--global
参数，有了这个参数，表示你这台机器上所有的git仓库都会使用这个配置，当然你也可以对某个仓库指定的不同的用户名和邮箱。

### 四.如何操作？

**1.创建版本库**

   
 什么是版本库？版本库又名仓库，英文名repository,你可以简单的理解一个目录，这个目录里面的所有文件都可以被git管理起来，每个文件的修改，删除，git都能跟踪，以便任何时刻都可以追踪历史，或者在将来某个时刻还可以将文件"还原"。

   
所以创建一个版本库也非常简单，如下我是D盘www目录下新建一个testgit版本库。

   ![](media/image6.png){width="3.7090277777777776in"
height="1.7166666666666666in"}

   ①通过命令 git init 把这个目录变成git可以管理的仓库，如下：

   ![](media/image7.png){width="3.5597222222222222in"
height="0.5298611111111111in"}

 
 这时候你当前testgit目录下会多了一个.git的目录，这个目录是git来跟踪管理版本的，没事千万不要手动乱改这个目录里面的文件，否则，会把git仓库给破坏了。如下：

    ![](media/image8.png){width="4.470138888888889in"
height="1.26875in"}

      ②把文件添加到版本库中。

   
 首先要明确下，所有的版本控制系统，只能跟踪文本文件的改动，比如txt文件，网页，所有程序的代码等，git也不列外，版本控制系统可以告诉你每次的改动，但是图片，视频这些二进制文件，虽能也能由版本控制系统管理，但没法跟踪文件的变化，只能把二进制文件每次改动串起来，也就是知道图片从1kb变成2kb，但是到底改了啥，版本控制也不知道。

**    下面先看下demo如下演示：**

     我在版本库testgit目录下新建一个记事本文件 readme.txt
内容如下：11111111

     第一步：使用命令 git add readme.txt添加到暂存区里面去。如下：

    ![](media/image9.png){width="3.26875in"
height="0.5819444444444445in"}

   如果和上面一样，没有任何提示，说明已经添加成功了。

   第二步：用命令 git commit告诉git，把文件提交到仓库。

   ![](media/image10.png){width="3.5972222222222223in"
height="0.8805555555555555in"}

  现在我们已经提交了一个readme.txt文件了，我们下面可以通过命令git
status来查看是否还有文件未提交，如下：

  ![](media/image11.png){width="3.5972222222222223in"
height="0.8131944444444444in"}

 说明没有任何文件未提交，但是我现在继续来改下readme.txt内容，比如我在下面添加一行2222222222内容，继续使用git
status来查看下结果，如下：

 ![](media/image12.png){width="4.395833333333333in"
height="1.2166666666666666in"}

上面的命令告诉我们 readme.txt文件已被修改，但是未被提交的修改。

接下来我想看下readme.txt文件到底改了什么内容，如何查看呢？可以使用如下命令：

git diff readme.txt 如下：

 ![](media/image13.png){width="3.5145833333333334in"
height="1.4326388888888888in"}

如上可以看到，readme.txt文件内容从一行11111111改成 二行
添加了一行22222222内容。

知道了对readme.txt文件做了什么修改后，我们可以放心的提交到仓库了，提交修改和提交文件是一样的2步(第一步是git
add  第二步是：git commit)。

如下：

 ![](media/image14.png){width="4.283333333333333in"
height="2.372916666666667in"}

**2.版本回退**

   
 如上，我们已经学会了修改文件，现在我继续对readme.txt文件进行修改，再增加一行

内容为33333333333333.继续执行命令如下：

   ![](media/image15.png){width="3.283333333333333in" height="1.0in"}

现在我已经对readme.txt文件做了三次修改了，那么我现在想查看下历史记录，如何查呢？我们现在可以使用命令
git log 演示如下所示：

  ![](media/image16.png){width="4.23125in" height="2.127083333333333in"}

    git
log命令显示从最近到最远的显示日志，我们可以看到最近三次提交，最近的一次是,增加内容为333333.上一次是添加内容222222，第一次默认是111111。如果嫌上面显示的信息太多的话，我们可以使用命令
git log -pretty=oneline 演示如下：

  ![](media/image17.png){width="4.492361111111111in"
height="0.7236111111111111in"}

   
现在我想使用版本回退操作，我想把当前的版本回退到上一个版本，要使用什么命令呢？可以使用如下2种命令，第一种是：git
reset \--hard HEAD\^。那么如果要回退到上上个版本只需把HEAD\^改成
HEAD\^\^。以此类推，那如果要回退到前100个版本的话，使用上面的方法肯定不方便，我们可以使用下面的简便命令操作：git
reset  \--hard HEAD\~100 即可。未回退之前的readme.txt内容如下：

  ![](media/image18.png){width="2.761111111111111in"
height="1.0222222222222221in"}

如果想回退到上一个版本的命令如下操作：

![](media/image19.png){width="3.1569444444444446in"
height="0.7166666666666667in"}

再来查看下 readme.txt内容如下：通过命令cat readme.txt查看

![](media/image20.png){width="3.26875in" height="0.6340277777777777in"}

可以看到，内容已经回退到上一个版本了。我们可以继续使用git log
来查看下历史记录信息，如下：

![](media/image21.png){width="3.365972222222222in"
height="1.5298611111111111in"}

我们看到 增加333333
内容我们没有看到了，但是现在我想回退到最新的版本，如：有333333的内容要如何恢复呢？我们可以通过版本号回退，使用命令方法如下：

git reset \--hard版本号
，但是现在的问题假如我已经关掉过一次命令行或者333333内容的版本号我并不知道呢？要如何知道增加3333333内容的版本号呢？可以通过如下命令即可获取到版本号：git
reflog  演示如下：

![](media/image22.png){width="3.5in" height="0.8361111111111111in"}

通过上面的显示我们可以知道，增加内容3333的版本号是
6fcfc89.我们现在可以命令

git reset \--hard 6fcfc89来恢复了。演示如下：

![](media/image23.png){width="3.5597222222222222in"
height="1.0819444444444444in"}

可以看到 目前已经是最新的版本了。

**3.理解工作区与暂存区的区别？**

**工作区：**就是你在电脑上看到的目录，比如目录下testgit里的文件(.git隐藏目录版本库除外)。或者以后需要再新建的目录文件等等都属于工作区范畴。

**版本库(Repository)：**工作区有一个隐藏目录.git,这个不属于工作区，这是版本库。其中版本库里面存了很多东西，其中最重要的就是**stage(暂存区)**，还有git为我们自动创建了第一个分支master,以及指向master的一个指针HEAD。

我们前面说过使用git提交文件到版本库有两步：

  第一步：是使用 git add 把文件添加进去，实际上就是把文件添加到暂存区。

  第二步：使用git
commit提交更改，实际上就是把暂存区的所有内容提交到当前分支上。

我们继续使用demo来演示下：

我们在readme.txt再添加一行内容为4444444，接着在目录下新建一个文件为test.txt内容为test，我们先用命令
git status来查看下状态，如下：

![](media/image24.png){width="4.3805555555555555in"
height="1.6416666666666666in"}

现在我们先使用git add 命令把2个文件都添加到暂存区中，再使用git
status来查看下状态，如下：

![](media/image25.png){width="3.223611111111111in"
height="1.6569444444444446in"}

接着我们可以使用git commit一次性提交到分支上，如下：

![](media/image26.png){width="4.365972222222222in"
height="1.1715277777777777in"}

**4.git撤销修改和删除文件操作**

**①撤销修改：**

比如我现在在readme.txt文件里面增加一行
内容为555555555555，我们先通过命令查看如下：

![](media/image27.png){width="2.865972222222222in"
height="1.0145833333333334in"}

在我未提交之前，我发现添加5555555555555内容有误，所以我得马上恢复以前的版本，现在我可以有如下几种方法可以做修改：

第一：如果我知道要删掉哪些内容的话，直接手动更改去掉那些需要的文件，然后add添加到暂存区，最后commit掉。

第二：我可以按以前的方法直接恢复到上一个版本。使用 git reset \--hard
HEAD\^

但是现在我不想使用上面的2种方法，我想直接想使用撤销命令该如何操作呢？首先在做撤销之前，我们可以先用
git status 查看下当前的状态。如下所示：

![](media/image28.png){width="4.574305555555555in"
height="1.2013888888888888in"}

可以发现，git会告诉你，git checkout \-- file
可以丢弃工作区的修改，如下命令：

git checkout  \--  readme.txt,如下所示：

![](media/image29.png){width="3.8958333333333335in"
height="1.0444444444444445in"}

命令 git checkout \-- readme.txt
意思就是，把readme.txt文件在工作区做的修改全部撤销，这里有2种情况，如下：

•readme.txt自动修改后，还没有放到暂存区，使用
撤销修改就回到和版本库一模一样的状态。

•另外一种是readme.txt已经放入暂存区了，接着又作了修改，撤销修改就回到添加暂存区后的状态。

对于第二种情况，我想我们继续做demo来看下，假如现在我对readme.txt添加一行内容为6666666666666，我git
add
增加到暂存区后，接着添加内容7777777，我想通过撤销命令让其回到暂存区后的状态。如下所示：

  ![](media/image30.png){width="4.470138888888889in" height="3.5in"}

**注意：**命令git checkout \-- readme.txt
中的\--很重要，如果没有\--的话，那么命令变成创建分支了。

**②删除文件。**

 假如我现在版本库testgit目录添加一个文件b.txt,然后提交。如下：

  ![](media/image31.png){width="4.358333333333333in"
height="2.6791666666666667in"}

如上：一般情况下，可以直接在文件目录中把文件删了，或者使用如上rm命令：rm
b.txt
，如果我想彻底从版本库中删掉了此文件的话，可以再执行commit命令提交掉，现在目录是这样的，

 ![](media/image32.png){width="4.836111111111111in"
height="1.3208333333333333in"}

只要没有commit之前，如果我想在版本库中恢复此文件如何操作呢？

可以使用如下命令 git checkout \-- b.txt，如下所示：

![](media/image33.png){width="3.8430555555555554in"
height="1.6791666666666667in"}

再来看看我们testgit目录，添加了3个文件了。如下所示：

![](media/image34.png){width="4.836111111111111in"
height="1.6569444444444446in"}

### 五.远程仓库

   
 在了解之前，先注册github账号，由于你的本地git仓库和github仓库之间的传输是通过SSH加密的，所以需要一点设置：

     第一步：创建SSH
Key。在**用户主目录**下，看看有没有.ssh目录，如果有，再看看这个目录下有没有id_rsa和id_rsa.pub这两个文件，如果有的话，直接跳过此如下命令，如果没有的话，打开命令行，输入如下命令：

**[ssh-keygen -t rsa -C \"youremail@example.com\"]{.mark}**,
由于我本地此前运行过一次，所以本地有，如下所示：

 ![](media/image35.png){width="5.350694444444445in"
height="1.2013888888888888in"}

id_rsa是私钥，不能泄露出去，id_rsa.pub是公钥，可以放心地告诉任何人。

第二步：登录github,打开" settings"中的SSH Keys页面，然后点击"Add SSH
Key",填上任意title，在Key文本框里黏贴id_rsa.pub文件的内容。

![](media/image36.png){width="6.470138888888889in"
height="4.910416666666666in"}

点击 Add Key，你就应该可以看到已经添加的key。

![](media/image37.png){width="4.723611111111111in"
height="2.3131944444444446in"}

**1.如何添加远程库？**

 
 现在的情景是：我们已经在本地创建了一个git仓库后，又想在github创建一个git仓库，并且希望这两个仓库进行远程同步，这样github的仓库可以作为备份，又可以其他人通过该仓库来协作。

   首先，登录github上，然后在右上角找到"create a new
repo"创建一个新的仓库。如下：

![](media/image38.png){width="6.985416666666667in"
height="3.8958333333333335in"}

在Repository name填入testgit，其他保持默认设置，点击"Create
repository"按钮，就成功地创建了一个新的git仓库：

![](media/image39.png){width="6.23125in" height="4.007638888888889in"}

   
目前，在gitHub上的这个testgit仓库还是空的，gitHub告诉我们，可以[从这个仓库克隆出新的仓库，也可以把一个已有的本地仓库与之关联]{.mark}，然后，把本地仓库的内容推送到gitHub仓库。

现在，我们根据gitHub的提示，在本地的testgit仓库下运行命令：

\$ git remote add origin https://github.com/tugenhua0707/testgit.git

所有的如下：

  ![](media/image40.png){width="4.104166666666667in"
height="1.6340277777777779in"}

把本地库的内容推送到远程，使用 git
push命令，实际上是把当前分支master推送到远程。

由于远程库是空的，我们第一次推送master分支时，加上了-u参数，git不但会把本地的master分支内容推送的远程新的master分支，还会把本地的master分支和远程的master分支关联起来，在以后的推送或者拉取时就可以简化命令。推送成功后，可以立刻在github页面中看到远程库的内容已经和本地一模一样了，上面的要输入github的用户名和密码如下所示：

![](media/image41.png){width="6.581944444444445in"
height="4.1194444444444445in"}

从现在起，只要本地作了提交，就可以通过命令：git push origin
master，把本地master分支的最新修改推送到github上了，现在你就拥有了真正的分布式版本库了。

**2.如何从远程库克隆？**

  上面我们了解了先有本地库，后有远程库时候，如何关联远程库。

  现在我们想，假如远程库有新的内容了，我想克隆到本地来 如何克隆呢？

  首先，登录github，创建一个新的仓库，名字叫testgit2.如下：

![](media/image42.png){width="6.865972222222222in" height="3.9625in"}

如下，我们看到：

![](media/image43.png){width="6.209027777777778in"
height="2.910416666666667in"}

现在，远程库已经准备好了，下一步是使用命令git
clone克隆一个本地库了。如下所示：

![](media/image44.png){width="3.9625in" height="0.7909722222222222in"}

接着在我本地目录下生成testgit2目录了，如下所示：

![](media/image45.png){width="5.081944444444445in"
height="1.4027777777777777in"}

### 六.创建与合并分支

    在 版本回填退里，你已经知道，每次提交，git都把它们串成一条时间线，这条时间线就是一个分支。截止到目前，只有一条时间线，在git里，这个分支叫主分支，即master分支。HEAD严格来说不是指向提交，而是指向master，master才是指向提交的，所以，HEAD指向的就是当前分支。

首先，我们来创建dev分支，然后切换到dev分支上。如下操作：

 ![](media/image46.png){width="3.0819444444444444in"
height="1.261111111111111in"}

git checkout 命令加上 -b参数表示创建并切换，相当于如下2条命令

git branch dev

git checkout dev

git
branch查看分支，会列出所有的分支，当前分支前面会添加一个星号。然后我们在dev分支上继续做demo，比如我们现在在readme.txt再增加一行
7777777777777

首先我们先来查看下readme.txt内容，接着添加内容77777777，如下：

![](media/image47.png){width="2.7090277777777776in"
height="2.723611111111111in"}

现在dev分支工作已完成，现在我们切换到主分支master上，继续查看readme.txt内容如下：

![](media/image48.png){width="4.19375in" height="1.3659722222222221in"}

现在我们可以把dev分支上的内容合并到分支master上了，可以在master分支上，使用如下命令
git merge dev 如下所示：

![](media/image49.png){width="3.5819444444444444in"
height="1.7166666666666666in"}

git
merge命令用于合并指定分支到当前分支上，合并后，再查看readme.txt内容，可以看到，和dev分支最新提交的是完全一样的。

注意到上面的*Fast-forward*信息，git告诉我们，这次合并是"快进模式"，也就是直接把master指向dev的当前提交，所以合并速度非常快。

合并完成后，我们可以接着删除dev分支了，操作如下：

![](media/image50.png){width="4.627083333333333in" height="1.0in"}

总结创建与合并分支命令如下：

   查看分支：git branch

   创建分支：git branch name

   切换分支：git checkout name

创建+切换分支：git checkout -b name

合并某分支到当前分支：git merge name

删除分支：git branch -d name

**如何解决冲突？**

下面我们还是一步一步来，先新建一个新分支，比如名字叫fenzhi1，在readme.txt添加一行内容8888888，然后提交，如下所示：

![](media/image51.png){width="3.9479166666666665in"
height="3.201388888888889in"}

同样，我们现在切换到master分支上来，也在最后一行添加内容，内容为99999999，如下所示：

![](media/image52.png){width="4.111805555555556in"
height="3.5145833333333334in"}

现在我们需要在master分支上来合并fenzhi1，如下操作：

![](media/image53.png){width="4.447916666666667in"
height="4.134027777777778in"}

git用\<\<\<\<\<\<\<，=======，\>\>\>\>\>\>\>标记出不同分支的内容，其中\<\<\<HEAD是指主分支修改的内容，\>\>\>\>\>fenzhi1是指fenzhi1上修改的内容，我们可以修改下如下后保存：

![](media/image54.png){width="4.014583333333333in"
height="1.8506944444444444in"}

如果我想查看分支合并的情况的话，需要使用命令 git log.命令行演示如下：

![](media/image55.png){width="3.3958333333333335in"
height="5.955555555555556in"}

**3.分支管理策略。**

通常合并分支时，git一般使用"Fast
forward"模式，在这种模式下，删除分支后，会丢掉分支信息，现在我们来使用带参数
-no-ff来禁用"Fast forward"模式。首先我们来做demo演示下：

•创建一个dev分支。

•修改readme.txt内容。

•提交修改。

•切换回主分支(master)。

•合并dev分支，使用命令 git merge -no-ff  -m "注释" dev

•查看历史记录

截图如下：

 ![](media/image56.png){width="4.201388888888889in"
height="5.440277777777778in"}

**分支策略：**首先master主分支应该是非常稳定的，也就是用来发布新版本，一般情况下不允许在上面干活，干活一般情况下在新建的dev分支上干活，干完后，比如上要发布，或者说dev分支代码稳定后可以合并到主分支master上来。

### 七.bug分支

     在开发中，会经常碰到bug问题，那么有了bug就需要修复，在git中，分支是很强大的，每个bug都可以通过一个临时分支来修复，修复完成后，合并分支，然后将临时的分支删除掉。

比如我在开发中接到一个404
bug时候，我们可以创建一个404分支来修复它，但是，当前的dev分支上的工作还没有提交。如下：

 ![](media/image57.png){width="4.246527777777778in"
height="1.1194444444444445in"}

 
 并不是我不想提交，而是工作进行到一半时候，我们还无法提交，比如我这个分支bug要2天完成，但是我issue-404
bug需要5个小时内完成。怎么办呢？还好，git还提供了一个stash功能，可以把当前工作现场
"隐藏起来"，等以后恢复现场后继续工作。如下：

  ![](media/image58.png){width="4.358333333333333in"
height="1.261111111111111in"}

   所以现在我可以通过创建issue-404分支来修复bug了。

首先我们要确定在那个分支上修复bug，比如我现在是在主分支master上来修复的，现在我要在master分支上创建一个临时分支，演示如下：

 ![](media/image59.png){width="3.9479166666666665in"
height="3.5076388888888888in"}

修复完成后，切换到master分支上，并完成合并，最后删除issue-404分支。演示如下：

![](media/image60.png){width="4.253472222222222in"
height="3.067361111111111in"}

现在，我们回到dev分支上干活了。

![](media/image61.png){width="3.0444444444444443in"
height="0.9854166666666667in"}

工作区是干净的，那么之前工作现场去哪里呢？我们可以使用命令 git stash
list来查看下。如下：

![](media/image62.png){width="3.223611111111111in"
height="0.6868055555555556in"}

工作现场还在，git把stash内容存在某个地方了，但是需要恢复一下，可以使用如下2个方法：

•git stash apply恢复，恢复后，stash内容并不删除，你需要使用命令git stash
drop来删除。

•另一种方式是使用git stash pop,恢复的同时把stash内容也删除了。

  演示如下

![](media/image63.png){width="4.246527777777778in"
height="3.1041666666666665in"}

### 八.多人协作

当你从远程库克隆时候，实际上git自动把本地的master分支和远程的master分支对应起来了，并且远程库的默认名称是origin。

•要查看远程库的信息使用 git remote

•要查看远程库的详细信息 使用 git remote -v

如下演示：

 ![](media/image64.png){width="4.5in" height="1.2236111111111112in"}

**1.推送分支：**

     
推送分支就是把该分支上所有本地提交到远程库中，推送时，要指定本地分支，这样，git就会把该分支推送到远程库对应的远程分支上：

      使用命令 git push origin master

比如我现在的github上的readme.txt代码如下：

![](media/image65.png){width="5.507638888888889in"
height="3.0444444444444443in"}

本地的readme.txt代码如下：

 ![](media/image66.png){width="2.8430555555555554in"
height="1.3881944444444445in"}

现在我想把本地更新的readme.txt代码推送到远程库中，使用命令如下：

![](media/image67.png){width="3.6118055555555557in"
height="1.3583333333333334in"}

我们可以看到如上，推送成功，我们可以继续来截图github上的readme.txt内容
如下：

![](media/image68.png){width="5.447916666666667in"
height="3.2534722222222223in"}

可以看到
推送成功了，如果我们现在要推送到其他分支，比如dev分支上，我们还是那个命令
git push origin dev

那么一般情况下，那些分支要推送呢？

•master分支是主分支，因此要时刻与远程同步。

•一些修复bug分支不需要推送到远程去，可以先合并到主分支上，然后把主分支master推送到远程去。

**2.抓取分支：**

多人协作时，大家都会往master分支上推送各自的修改。现在我们可以模拟另外一个同事，可以在另一台电脑上(注意要把SSH
key添加到github上)或者同一台电脑上另外一个目录克隆，新建一个目录名字叫testgit2

但是我首先要把dev分支也要推送到远程去，如下

![](media/image69.jpeg){width="3.716666666666667in"
height="1.1118055555555555in"}

接着进入testgit2目录，进行克隆远程的库到本地来，如下：

 ![](media/image70.png){width="3.6868055555555554in" height="1.23125in"}

现在目录下生成有如下所示：

![](media/image71.png){width="5.052083333333333in"
height="1.7986111111111112in"}

现在我们的小伙伴要在dev分支上做开发，就必须把远程的origin的dev分支到本地来，于是可以使用命令创建本地dev分支：git
checkout  -b dev origin/dev

现在小伙伴们就可以在dev分支上做开发了，开发完成后把dev分支推送到远程库时。

如下：

![](media/image72.png){width="4.2375in" height="5.131944444444445in"}

小伙伴们已经向origin/dev分支上推送了提交，而我在我的目录文件下也对同样的文件同个地方作了修改，也试图推送到远程库时，如下：

![](media/image73.png){width="4.308333333333334in"
height="5.048611111111111in"}

由上面可知：推送失败，因为我的小伙伴最新提交的和我试图推送的有冲突，解决的办法也很简单，上面已经提示我们，先用git
pull把最新的提交从origin/dev抓下来，然后在本地合并，解决冲突，再推送。

![](media/image74.png){width="4.3125in" height="2.0493055555555557in"}

*git
pull*也失败了，原因是没有指定本地dev分支与远程origin/dev分支的链接，根据提示，设置dev和origin/dev的链接：如下：

![](media/image75.png){width="4.506944444444445in"
height="1.3909722222222223in"}

这回*git
pull*成功，但是合并有冲突，需要手动解决，解决的方法和分支管理中的
解决冲突完全一样。解决后，提交，再push：

我们可以先来看看readme.txt内容了。

![](media/image76.png){width="3.4722222222222223in"
height="1.8541666666666667in"}

现在手动已经解决完了，我接在需要再提交，再push到远程库里面去。如下所示：\
![](media/image77.png){width="4.2in" height="3.3333333333333335in"}

因此：多人协作工作模式一般是这样的：

•首先，可以试图用git push origin branch-name推送自己的修改.

•如果推送失败，则因为远程分支比你的本地更新早，需要先用git
pull试图合并。

•如果合并有冲突，则需要解决冲突，并在本地提交。再用git push origin
branch-name推送。

# 4)基本概念

## 一.git仓库、工作区、暂存区 

1.**工作区(workspace)**：用文本编辑器打开，如vi、source
insight等，能查看/修改文件内容，此时文件存在于工作区。git
checkout到不同分支时会切换工作区文件；文件状态：unstaged。本地。

2.**暂存区(index/ Stage Area)**：git
add之后文件所在区域。文件状态：staged , uncommitted。本地。

3.**本地仓库(repository)**：git
commit之后，文件所在区域。文件状态：committed。本地。

4.**远程仓库(remote repository)**：git
push/pull，公司服务器，公用。远程。

工作区、暂存区、本地仓库都在本地机器上，远程仓库在远程服务器的另一台电脑上。

有些资料上也称：工作目录、暂存目录、本地目录、远程目录。

5.**git仓库分为本地仓库和远程仓库。本地仓库通过git
clone复制远程仓库，是远程仓库的完整拷贝。因此，远程仓库具有的东西，如提交记录、分支等，在本地仓库也都是有的。**注:一定要按照\"git服务器搭建\"一章进行实际操作，才能理解本地仓库和远程仓库之间的关系。

![](media/image78.emf)

**git的四个区域和常用操作**

![](media/image79.png){width="4.9847222222222225in"
height="2.3569444444444443in"}

index和git库都在源码目录下的.git目录下，.git就是本地仓库目录。

参考章节：20)git/svn模型：库目录、代码目录

![](media/image80.png){width="2.5034722222222223in"
height="1.5368055555555555in"}

**repository /rɪˈpɒzɪtərɪ/ n.**

①贮存处;存放处;仓库，A repository is a place where something is kept
safely.

A church in Moscow became a repository for police files.
莫斯科的一座教堂成为警方存放档案的地点。

②博学者;无所不知的人，A repository of information is a person or group
of people who know a lot of information about a particular place or
subject.

The repository of all important knowledge in a small town was the chief
barman of the local pub.
小镇上最无所不知的人就是当地酒吧里的服务员领班。

**stage \[steɪdʒ\]**

时期；状态period/state

1.\[c\](发展或进展的)时期，阶段，状态a period or state that sth/sb
passes through while developing or making progress

程序part of process

2.\[c\]段；步；步骤a separate part that a process, etc. is divided into

剧场theatre

3.\[c\](多指剧场中的)舞台a raised area, usually in a theatre, etc. where
actors, dancers, etc. perform

4.\[sing\]戏剧；戏剧表演；戏剧界the theatre and the world of acting as a
form of entertainment

政界in politics

5.\[sing\](政治等活动的)领域；(政治)舞台an area of activity where
important things happen, especially in politics

stage是一个中间状态，是暂时的、临时的，staging，过渡状态，cached，缓存状态；

work space、local repository是终态。

remote repository是远程仓库的终态。

### add/commit/diff的含义

将**Current working directory**记为(1)，将**Index**记为(2)，将**Git
repository**记为(3)。

他们之间的提交层次关系是(1) -\> (2) -\> (3)，git add完成(1) -\> (2)，git
commit完成(2) -\> (3)，git commit -a完成(1) -\> (3)，等于git add + git
commit。

从时间上看，可以认为(1)是最新的代码，(2)比较旧，(3)更旧。

git diff比较的是从(2)到(1)的变化，git diff
\--cached比较的是从(3)到(2)的变化，git diff
HEAD比较的是从(3)到(1)的变化。

git diff :比较工作区和暂存区，从暂存区到工作区的变化：diff (2) (1)。

git diff \--cached:比较暂存区和本地仓库，从本地仓库到暂存区的变化：diff
(3) (2)。查看已经暂存起来的文件和上次提交时的快照之间的差异。

git diff HEAD:比较工作区和本地库，从本地仓库到工作区的变化：diff (3)
(1)。

cached指代暂存区，HEAD则指代本地仓库的最新一次提交。

**diff**，比较差异，**diff A B = diff 基对象
比较对象**，是以A作为基(base)，**从A到B的变化**，B相对于A的差异。从A到B是增加，删除，或修改。

**diff file1
file2**，比较file1和file2，是**以file1为基(base)，从file1到file2的变化**，是file2相对于file1的变化。如果改成diff
file2
file1则是以file2是base，从file2到file1的变化。//关键:**从X到Y的变化**

**git diff**也一样，是以文件的某个状态为基(base)、相对于base的差异。git
diff file，省略了base，实际上是比较file这个文件在working
directory和staging area之间的差异，base是staging area，从staging
area到working directory的变化。同样的，可以比较两次commit之间的差异，git
diff SHA1
SHA2，base是SHA1，是从SHA1到SHA2的变化，SHA2相对于SHA1的差异。也可以反过来比较:git
diff SHA2 SHA1，结果和git diff SHA1
SHA2刚好相反，原来的+变成-、原来的-变成+。

**例1：**

\$ echo A \> file1

\$ git add file1

\$ git commit -m \"Add file1\"

\$ echo B \>\> file1

\$ git add file1

\$ echo C \>\> file1

\$ git diff

diff \--git a/file1 b/file1

index 35d242b..b1e6722 100644

\-\-- a/file1

+++ b/file1

@@ -1,2 +1,3 @@

A

B

+C

\$ git diff \--cached

diff \--git a/file1 b/file1

index f70f10e..35d242b 100644

\-\-- a/file1

+++ b/file1

@@ -1 +1,2 @@

A

+B

\$ git diff HEAD

diff \--git a/file1 b/file1

index f70f10e..b1e6722 100644

\-\-- a/file1

+++ b/file1

@@ -1 +1,3 @@

A

+B

+C

**例2：**

\$ echo A \> file1

\$ git add file1

\$ git commit -m \"Add file1\"

\$ git diff HEAD\~ HEAD

diff \--git a/file1 b/file1

new file mode 100644

index 0000000..f70f10e

\-\-- /dev/null

+++ b/file1

@@ -0,0 +1 @@

**+A**

\$ git diff HEAD HEAD\~

diff \--git a/file1 b/file1

deleted file mode 100644

index f70f10e..0000000

\-\-- a/file1

+++ /dev/null

@@ -1 +0,0 @@

**-A**

## 二.提交、提交对象

**使用git commit进行提交操作，产生提交对象**，**创建提交历史记录**。

当使用**git
commit**进行提交操作时，git会先计算每一个子目录(本例中只有项目根目录)的校验和，然后在
git仓库中这些校验和保存为树对象。
随后，git便会**创建一个提交对象**，它除了包含上面提到的那些信息外，还包含指向这个树对象(项目根目录)的指针。如此一来，git就可以在需要的时候重现此次保存的快照。

现在，git仓库中有**五个对象**：三个blob对象(保存着文件快照)、一个树对象(记录着目录结构和blob对象索引)以及一个**提交对象**(包含着指向前述树对象的指针和所有提交信息)。

![é¦æ¬¡æäº¤å¯¹è±¡åå¶æ ç»æã](media/image81.png){width="4.925694444444445in"
height="2.73125in"}

Figure 9. 首次**提交对象及其树结构**

做些修改后再次提交，那么这次产生的**提交对象**会包含一个指向上次提交对象(父对象)的指针。

![æäº¤å¯¹è±¡åå¶ç¶å¯¹è±¡ã](media/image82.png){width="5.895833333333333in"
height="1.9479166666666667in"}

Figure 10. 提交对象及其父对象

## 三.SHA

\$ git log -1

commit [0980b5f1b98507affe2576c404ed393fad0d4295]{.mark} (HEAD -\> dev)

Author: dukang \<gaheadus@126.com\>

Date: Fri Aug 13 01:34:47 2021 -0700

this is a test commit

Change-Id: I3cc31f751212476e79c599f0c489fd57f2f23015

[0980b5f1b98507affe2576c404ed393fad0d4295]{.mark}由40个十六进制字符组成，称为**SHA哈希值**，作为指纹字符串，用来标识一次提交。**每一次git
commit产生一次提交，生成一个SHA字符串**。**SHA1哈希数，Secure Hash
Algorithm，它可以保证每次commit生成的名称是唯一且永远有效的**。

**git的工作完全依赖于这个指纹字符串**，所以你会经常看到这样的**哈希值**。实际上，**所有保存在git数据库中的东西都是用此哈希值来作索引的**，而不是靠文件名。

SHA-1值怎么计算？

使用git内置命令hash-object命令计算，例如计算字符串Hello,
5xRuby的SHA-1值：

\$ printf \"Hello, 5xRuby\" \| git hash-object \--stdin

4135fc4add3332e25ab3cd5acabe1bd9ea0450fb

## 四.HEAD

**HEAD**：指向**本地目录**的一个**已commit对象**，指代**当前分支最新的一次提交**。

**每一次commit会在git分支树上产生一个节点(对象，HEAD)**，**对应到一个哈希值(SHA)。**

**HEAD总是指向当前分支上最近一次提交记录**。大多数修改提交树的git命令都是从改变HEAD的指向开始的。

HEAD\~，意思是"HEAD的父提交"，也可以在\~后添加一个数字，例如HEAD\~2意思是"HEAD的父提交的父提交"。

也可以用\^指明祖先提交，\^指向第一父提交，HEAD\^和HEAD\~等价。

HEAD ← HEAD\^ / HEAD\~ / HEAD\~1 ← HEAD\^\^ / HEAD\~\~ / HEAD\~2 ←
HEAD\^\^\^ / HEAD\~\~\~ / HEAD\~3

最新提交 ← 最新提交的父提交 ← 最新提交的父提交的父提交 ←

\~和\^的不同：\~后面可以加数字表示多级父提交,如HEAD\~3/
HEAD\~4，\^后面不能加数字, HEAD\^3没有意义。

**波浪线后可以加数字**
HEAD\^1也能正常识别，是个bug？HEAD**\^**2、HEAD\^3就报错了

git merge后的节点的父提交，有点复杂，待完善。todo

\~\^也可以用在SHA后面，例：

SHA:d921970aadf03b3cf0e71becdaab3147ba71cdef，简写为d921970，

git show d921970aadf03b3cf0e71becdaab3147ba71cdef = git show d921970

git show d921970aadf03b3cf0e71becdaab3147ba71cdef \~3 = git show
d921970\~3

[**HEAD是一个指标**(类似C语言指针)，指向当前所在分支或者某个提交。]{.mark}

1)当前在某个分支上时，**HEAD指向当前所在分支，分支指向某个提交**，HEAD 🡪
refs/heads/master 🡪 SHA

2)当前处于detached HEAD状态时，**HEAD指向某个提交**，HEAD 🡪 SHA

HEAD用在命令中表示某一个提交，如git reset HEAD、git checkout HEAD。

**[在.git目录中有一个名为HEAD的文件]{.mark}**

\$ cat .git/HEAD

ref: refs/heads/master \-- HEAD指向当前所在分支

.git/refs/heads/master中记录的就是当前所在提交的SHA值：

\$ cat .git/refs/heads/master

fc347733b565f636377c7b7ec2346366e2fbada5 \-- 分支指向某个提交

是git log看到的最新提交的SHA值：

\$ git log \--pretty=format:\"%cn,%H\"

dukang,fc347733b565f636377c7b7ec2346366e2fbada5

dukang,7ef03c4ebdba49aa2fc30b873bb473bd8fe6eec9

dukang,04191432e4eefa7d5c30c16e88ab2b732f46884f

\$ git checkout SHA

\$ cat .git/HEAD

7ef03c4ebdba49aa2fc30b873bb473bd8fe6eec9 \-- 此时HEAD指向某个提交

git有几个内置的符号索引指针：\
HEAD：永远指向当前分支的最近一次commit\
ORIG_HEAD：git reset或git merge后，原来的HEAD被存在这里\
FETCH_HEAD：git fetch后所有分支的头索引指针\
MERGE_HEAD：git merge时另一分支的头索引指针

相对索引：HEAD\^ HEAD\~ HEAD\~2 HEAD@{2}等

ORIG_HEAD用于指向前一个操作状态，因此在git
pull之后如果想得到pull的内容就可以：

git diff ORIG_HEAD

git diff \--stat        用于生成统计信息。

git diff \--stat ORIG_HEAD

## 五.分支

**一个git仓库，包含多个分支**，默认包含master分支。参考《Pro git》\--
3.git分支

![æ¥æå¤ä¸ªç¹æ§åæ¯çæäº¤åå²ã](media/image83.png){width="3.6638888888888888in"
height="2.9090277777777778in"}

图中包含四个分支：master分支、iss91分支、iss91v2分支、dumbidea分支

**git的分支，其实本质上仅仅是指向提交对象的可变指针**。
git的默认分支名字是 master。
在多次提交操作之后，你其实已经有一个指向最后那个提交对象的 master 分支。
它会在每次的提交操作中自动向前移动。

分支及其提交历史。

![åæ¯åå¶æäº¤åå²ã](media/image84.png){width="3.589583333333333in"
height="1.9256944444444444in"}

Figure 11. 分支及其提交历史

**分支创建**

git是怎么创建新分支的呢？
很简单，它只是为你**创建了一个可以移动的新的指针**。 比如，创建一个
testing 分支， 你需要使用 git branch 命令：

**\$ git branch testing**

这会在当前所在的提交对象上创建一个指针。

![ä¸¤ä¸ªæåç¸åæäº¤åå²çåæ¯ã](media/image85.png){width="2.8805555555555555in"
height="1.1868055555555554in"}

Figure 12. 两个指向相同提交历史的分支

那么，git又是怎么知道当前在哪一个分支上呢？
也很简单，它有一个**名为HEAD的特殊指针**。
请注意它和许多其它版本控制系统(如Subversion或CVS)里的 HEAD
概念完全不同。 在 git中，它是一个指针，指向当前所在的本地分支(译注：将
HEAD 想象为当前分支的别名)。 在本例中，你仍然在 master 分支上。 因为 git
branch 命令仅仅 创建 一个新分支，并不会自动切换到新分支中去。

![HEAD æåå½åæå¨çåæ¯ã](media/image86.png){width="2.8430555555555554in"
height="1.6569444444444446in"}

Figure 13. **HEAD指向当前所在的分支**

**分支切换**

要切换到一个已存在的分支，你需要使用 git checkout 命令。
我们现在切换到新创建的 testing 分支去：

\$ git checkout testing

**这样 HEAD 就指向testing分支了**。

![HEAD æåå½åæå¨çåæ¯ã](media/image87.png){width="2.9027777777777777in"
height="1.6715277777777777in"}

Figure 14. HEAD指向当前所在的分支

在testing分支上做一次提交：git commit -m "Add a new file"，此时，testing
分支向前移动了，HEAD指针也跟着移动，但是 master
分支却没有，它仍然指向运行 git checkout 时所指的对象。

![HEAD
åæ¯éçæäº¤æä½èªå¨ååç§»å¨ã](media/image88.png){width="4.014583333333333in"
height="1.6715277777777777in"}

Figure 15. HEAD随着提交操作自动向前移动

这就有意思了，现在我们切换回 master 分支看看：

\$ git checkout master

![æ£åºæ¶ HEAD éä¹ç§»å¨ã](media/image89.png){width="3.9854166666666666in"
height="1.663888888888889in"}

Figure 16. 检出时 HEAD 随之移动

这条命令做了两件事。 一是使 HEAD 指回 master 分支，二是将工作目录恢复成
master 分支所指向的快照内容。
也就是说，你现在做修改的话，项目将始于一个较旧的版本。
本质上来讲，这就是忽略 testing
分支所做的修改，以便于向另一个方向进行开发。

现在，我们在master分支上做一些修改，并提交。

\$ git commit -m "Modify on master"

![é¡¹ç®åååå²ã](media/image90.png){width="4.410416666666666in"
height="2.8208333333333333in"}

Figure 17. 项目分叉历史

由于git的分支实质上仅是包含所指对象校验和(长度为40的SHA-1值字符串)的文件，所以它的创建和销毁都异常高效。
创建一个新分支就相当于往一个文件中写入41个字节(40
个字符和1个换行符)，如此的简单能不快吗？

这与过去大多数版本控制系统形成了鲜明的对比，它们在创建分支时，将所有的项目文件都复制一遍，并保存到一个特定的目录。完成这样繁琐的过程通常需要好几秒钟，有时甚至需要好几分钟。所需时间的长短，完全取决于项目的规模。而在git中，任何规模的项目都能在瞬间创建新分支。
同时，由于每次提交都会记录父对象，所以寻找恰当的合并基础(译注：即共同祖先)也是同样的简单和高效。
**这些高效的特性使得git鼓励开发人员频繁地创建和使用分支**。

**分支的提交历史记录**

**[\$ git log / git log \--graph / gitk / gitk]{.mark}**

![](media/image91.png){width="2.6493055555555554in"
height="3.1041666666666665in"}

禁止事项

禁止直接在master分支上开发。

禁止直接向master和release/stable分支push。

禁止merge， \--ff-only除外。

禁止pull， \--ff-only和\--rebase除外。

文本文件禁止使用宽字符编码，非手动编辑的文件除外。

## 六.git仓库和分支

更详细的介绍，见：15)git仓库与分支

### 仓库与分支模型

![](media/image92.jpeg){width="5.544444444444444in" height="6.73125in"}

### git仓库、工作区、暂存区

①在服务器上创建远程仓库，git init \--bare repodir，创建不同分支git
branch develop。

如果使用git init \--bare
repodir创建仓库则仓库保存在repodir目录(推荐)，如果使用git init
repodir创建仓库则仓库保存在repodir/.git目录。

②在本地电脑上下载远程服务器代码，git clone
uri。假设下载到本地的localdir目录。

本地下载完成后，生成**三个区：工作区、暂存区、git仓库**。

**工作区**就是我们打开文件夹就能看到的文件和目录，使用vi/sourceinsight/notepad++查看的就是工作区的文件，就是localdir目录下的所有文件。

**暂存区**不能直接看到，只能使用命令操作，git diff/git
add操作的就是暂存区。

**git仓库**保存在localdir/.git目录下，git的所有提交记录、分支就是保存在这个目录下。.git是一个隐藏目录，在linux下ls命令看不到，使用ls
-a才能看到，在windows下能直接看到。

③上图中远程仓库有两个分支master和develop，本地仓库也有master和develop两个分支。

使用git branch看到的是本地分支，使用git branch
-r看到的是远程分支，使用git branch
-a看到本地分支和远程分支。[在本地使用git branch
-r能看到远程分支remote/master，是远程库上的master分支在本地库映射的一个名字]{.mark}。只能修改本地分支，不能直接修改远程分支，只能通过git
push/git remote的方式修改远程分支。

### git仓库结构

git分布式的一个重要体现是git[在本地是有一个完整的git仓库，也就是**.git目录**]{.mark}，通过这个仓库，git就可以完全离线化操作。在这个本地化的仓库中存储了git所有的模型对象。下面是git仓库的tree和相关说明：

![](media/image93.png){width="5.241666666666666in"
height="5.595833333333333in"}

### .git目录中有什么？

git
init初始化一个git仓库，生成**.git目录**。git提交/分支/tree对象/blob对象等信息都保存在这个目录下。

**\$ git init / git clone**

**\$ ls .git**

COMMIT_EDITMSG HEAD ORIG_HEAD config description hooks index info logs
objects refs

**\$ ls .git\* -l**

total 14

-rw-rw-r\--+ 1 dukang None 11 May 21 11:53 COMMIT_EDITMSG

-rw-rw-r\--+ 1 dukang None 23 May 21 12:28 HEAD

-rw-rw-r\--+ 1 dukang None 41 May 21 11:50 ORIG_HEAD

-rw-rw-r\--+ 1 dukang None 111 May 21 11:11 config

-rw-rw-r\--+ 1 dukang None 73 May 21 11:11 description

drwxrwxr-x+ 1 dukang None 0 May 21 11:11 hooks

-rw-rw-r\--+ 1 dukang None 209 May 21 12:28 index

drwxrwxr-x+ 1 dukang None 0 May 21 11:11 info

drwxrwxr-x+ 1 dukang None 0 May 21 11:12 logs

drwxrwxr-x+ 1 dukang None 0 May 21 11:53 objects

drwxrwxr-x+ 1 dukang None 0 May 21 11:11 refs

**《git从入门到精通(高见龙)》**

**5.18 .git目录中有什么？Part 1**

想要我的财宝吗？想要的话可以全部给你，去找吧！我把所有的财宝都放在那里了。\--《航海王》哥尔罗杰

对git来说，git目录扮演的差不多就是宝藏这样的角色，所有的记录、所有的备份都放在其中了。所以想要真正地学好git，建议花一些时间来摸清这个目录中到底藏了什么东西。这样更能理解git的运行原理，操作起来也会更得心应手。

本节及下一节将介绍git内部的运行原理，以及在.git目录中还有哪些奇妙的东西。在开始介绍.git目录中的东西之前，一定要先知道git中的4种对象。在git中，有4种很重要的对象，分别是Blob对象、Tree对象、commit对象以及Tag对象。

接下来将通过实际操作git的命令，详细介绍这些对象的关联性。

**1.创建第一个文件并交由git控制**

首先创建一个index.html文件，内容是"hello, 5xRuby"：

\$ echo \"hell1o, 5xRuby\" \> index.html

前面介绍过，这时index.html还不算被加入git中，它只是路过而已，所以当前的状态是Untracked，就是还没有被git追踪的状态。接下来使用git
add命令，把它加入git的暂存区(也称下标)：

\$ git add index.html

\$ git status

on branch master No commits yet

Changes to be committed:

(use \"git rm\--cached \<file\>\...\" to unstage)

new file:index.html

index.html
文件已被加入暂存区无误。当把文件加入暂存区后，git便会在.git目录中生成一个Blob(Binary
large object)对象，并且依照其"规则"摆放到目录中。这个Blob对象用来存放
index.html文件的"内容"。注意，这里说的是"内容"而不是把整个index.html
文件搬进.git目录。

5.17节介绍过git是怎样计算Blob对象的SHA-1值的，这里直接使用git
hash-object命令来计算也可以：

\$ echo \"hello, 5xRuby\" \| git hash-object \--stdin

30ab28d3acb37f96ad61ad8be82c8da46d0a7307

经过计算，"hello，5xRuby＂字符串的内容在git中得到的SHA-1值是
30ab28d3acb37f96ad61ad8be82c8da46d0a7307。接着git就会在.git/objects
目录中存放文件。git会用这40字的SHA-1值的前两个字作为目录，剩余的38字是文件名，如图5-36所示。

![](media/image94.jpeg){width="4.2340277777777775in"
height="2.272222222222222in"}

图5-36

因为文件的内容已经过压缩，所以用一般的文本编辑器是看不出内容的，但可以使用git
cat-file命令来查看：

\$ git cat-file -t 30ab28d3acb37f96ad61ad8be82c8da46d0a7307

blob

其中，-t参数表示要查看的SHA-1值所代表的对象的形态。根据结果，git回报的SHA-1值代表的是一种Blob对象。如果改用-p参数：

\$ git cat-file -p 30ab28d3acb37f96ad61ad8be82c8da46d0a7307

hello, 5xRuby

则可看到SHA-1值指向的那个对象的内容，它显示为"hello,
5xRuby"，可以确定就是刚才的那个index.html文件。至此可知如下信息：

(1)当使用git
add命令把文件加入暂存区时，git会根据这个对象的"内容"计算出SHA-1值。

(2)git接着会用SHA-1值的前2个字节作为目录名称，后38个字节作为文件名，创建目录及文件并存放在.git/objects
目录下。

(3)文件的内容则是git使用压缩算法把原本的"内容"压缩之后的结果。

规则：Blob对象的文件名是由SHA-1算法决定的，其内容则是由压缩算法决定的。

提示：在某些操作系统下，一个目录中如果放了非常多的文件，该目录的读取效率就会变得非常低，所以git抽出了前两位数作为目录名称，就是避免让.git/objects目录因为文件过多而降低效率。

**2.创建目录**

接着创建一个名为config的目录。

\$ mkdir config

\$ git status

On branch master No commits yet

Changes to be committed:

(use \"git rm \--cached \<file\>\...\" to unstage)

new file: index.html

会发现git完全没感应到刚刚创建的那个目录。

为什么？想一下刚才的规则，git会针对文件的"内容"使用SHA-1算法进行计算，然后在.git/objects中创建对应的目录及文件。但因为这只是一个空的config目录，它根本就没有"内容"可以计算，所以git根本连感应都感应不到。记住，[git只对"内容"有兴趣]{.mark}，这样一个空的目录对git来说是无感的，所以它也只是路过，甚至连Untracked都算不上。即使手动下达这个命令：

\$ git add config

也是没效果的。

重要！

空的目录无法被加入git中。

**3.创建第二个文件**

在上一个步骤中，既然git无法处理config目录，所以接下来在这个目录中创建一个文件：

\$ touch config/database.yml

查看一下状态：

\$ git status On branch master No commits yet

Changes to be committed:

(use \"git rm \--cached \<file\>\...\" to unstage)

new file: index.html

Untracked files:

(use \"git add \<file\>\...\" to include in what will be committed)

config/

即使只是一个空的文件，它也是有"内容"的，就是"空的内容"，原本无法被git看见的config目录，在里面放了一个文件之后就看得见它了(有种"母凭子贵"的感觉)。接着把它加到git中：

\$ git add config/database.yml

根据git的Blob 对象进行计算：

\$ cat config/database.yml \| git hash-object \--stdin

e69de29bb2d1d6434b8b29ae775ad8c2e48c5391

根据前面的规则，这时应该在.git/objects目录中创建一个e6的目录，其中包含9de29bb2dld6434b8b29ae775ad8c2e48c5391文件，如图5-37所示。

到这里，相信大家已对git世界中的Blob对象有所了解了。

接下来你可能会好奇：git只在意文件的"内容"，难道目录完全不重要吗？文件的名称是什么也不重要吗？其实也不是不重要，只是它们不属于Blob对象的范围，这是后面要介绍的Tree对象要处理的。

![](media/image95.jpeg){width="3.3847222222222224in"
height="2.3305555555555557in"}

图5-37

**4.进行commit**

既然文件已加至暂存区，接下来就要进行commit，观察一下.git/objects目录会有什么变化：

\$ git commit -m \"init commit\"

\[master (root-commit) 5d47270\] init commit

2 files changed,1 insertion(+)

create mode 100644 config/database.yml

create mode 100644 index.html

查看.git/objects 目录，如图5-38所示。

![](media/image96.jpeg){width="3.2944444444444443in"
height="3.077777777777778in"}

图5-38

除了原本的30与e6目录之外，又多出了好几个目录，下面来看看它们都是什么。从25目录中的32115fab19c7ce70ff78a4929fb5df2f6131c4开始查看：

\$ git cat-file -t 2532115fab19c7ce70ff78a4929fb5df2f6131c4

tree

git告诉我们这是一种Tree对象。再看这个对象里有什么内容：

\$ git cat-file -p 2532115fab19c7ce70ff78a4929fb5df2f6131c4

040000 tree a618ce33da8d21bca841f18e6432fcabf15d4477 config

100644 blob 30ab28d3acb37f96ad61ad8be82c8da46d0a7307 index.html

从中看到一个Tree对象和一个Blob对象，而这个Blob对象正是index.html。再看它指向的另一个对象：

\$ git cat-file -t a618ce33da8d21bca841f18e6432fcabf15d4477

tree

这是个Tree对象，内容如下：

\$ git cat-file -p a618ce33da8d21bca841f18e6432fcabf15d4477

100644 blob e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 database.yml

在这个Tree对象中看到一个Blob对象，正是刚刚放在config目录中的database.yml。到这里，大家可能稍微对Tree对象有点了解了。用一张图来简单说明，如图5-39所示。

![](media/image97.jpeg){width="3.9479166666666665in"
height="2.229861111111111in"}

图5-39

说明如下：

(1)文件在git中会以Blob对象的形式存放，如这个示例中的index.html和database.yml。

(2)目录及文件的名称将会以Tree对象的形式存放，如253211代表的是根目录，而a618ce代表的是config目录。

(3)Tree对象的内容会指向某个或某些Blob对象，或者其他的Tree对象。

大家可能会觉得这有点像目录与子目录的关系，但其实并不是。它有个专有名词\--Directed
Acyclic
Graph(DAG)，中文翻译为有向无环图。这些对象之间只有指来指去的关系，并没有阶层或目录、子目录的关系，不管是Blob对象还是Tree对象，都是平行的。图5-39中用类似目录的方式呈现，只是因为这样比较容易想象和理解罢了，事实上它们并没有阶层关系。

介绍完Tree对象，刚刚commit完成后多出来的3个对象还有一个没有查看：

\$ git cat-file -t 5d47270a0a3cb0440f77bdfa795bd712b22ec548

commit

这就是接下来要介绍的commit对象。看看这个commit对象的内容：

\$ git cat-file -p 5d47270a0a3cb0440f77bdfa795bd712b22ec548

tree 2532115fab19c7ce70ff78a4929fb5df2f6131c4

author Eddie Kao \<eddie@5xruby.tw\> 1503442336 +0800

committer Eddie Kao \<eddie@5xruby.tw\> 1503442336 +0800

init commit

这个commit对象包括以下信息。

(1)某个Tree对象。还记得253211吗？如果往回翻就可以发现，它就是代表根目录的那个Tree对象。

(2)本次commit的时间。

(3)作者和进行这次commit的人一般情况下会是同一个人，但偶尔也会有"Code我写好了，但没办法commit，所以请人代发"的情况。

(4)本次commit的信息。

将截至目前提到的Blob对象、Tree对象及commit对象的关系用图再重新整理一下，如图5-40所示。

![](media/image98.jpeg){width="3.7493055555555554in"
height="3.213888888888889in"}

图5-40

提醒一下，在图5-40中，各个对象旁边写着目录或文件名的小提示牌，并不代表"这个物件就是这个文件或目录"，而是"这个对象的内容是来自这个文件的"，放上提示牌只是为了让大家更容易理解各对象之间的关系而已。

参考此图，然后记住以下规则：

(1)commit对象会指向某个Tree对象。

(2)Tree对象的内容会指向某个或某些Blob对象，或者其他的Tree对象。

git对象的"四大天王"已经出现三位了，还少一位，也就是Tag对象，它将在后面的章节中另做介绍。

**5.分支登场**

在6.3节关于分支的介绍中提到，git中的分支其实就跟一张贴纸一样，它会贴在某个commit上，并且会随着每次的commit不断地移动；同时，在5.15节关于HEAD的介绍中指出，[HEAD是一个指向某个分支的指标]{.mark}，可以把它看成"当前所在的分支"。综上所述，这时应该会有一个分支(就是git默认的master分支)，并且HEAD会指向当前唯一的commit，如图5-41所示。

![](media/image99.jpeg){width="3.545138888888889in"
height="3.4944444444444445in"}

图5-41

**6.继续前进**

做完了一次commit，接下来再做一次，看看.git目录又会有什么变化。这次先编辑一下index.html文件，帮它加一些HTML内容：

\<!DOCTYPE html\>

\<html\>

\<head\>

\<meta charset=\"utf-8\"\>

\<title\>\</title\>

\</head\>

\<body\>

\<h1\>He11o,5xRuby\</h1\>

\</body\>

\</html\>

这时的状态如下：

\$ git status

On branch master

Changes not staged for commit:

(use \"git add \<file\>\...\" to update what will be committed)

(use \"git checkout \--\<file\>\...\" to discard changes in working
directory)

modified:index.html

no changes added to commit (use \"git add\" and/or \"git commit -a\")

因为这个文件被改动了，所以处于modified状态。不过这时还没有新的对象产生，要把文件加到暂存区才会出现新的Blob对象。

\$ git add index.html

使用git hash-object命令计算一下：

\$ cat index.html \| git hash-object \--stdin

159dba9a492eb6ee354beda28c88652dd7d1c2e2

根据前面的规则，这时在.git/objects目录下应该会多出一个15目录，并且其中有一个名为9dba9a492eb6ee354beda28c88652dd7dlc2e2的文件，如图5-42所示。

![](media/image100.jpeg){width="4.379166666666666in"
height="3.421527777777778in"}

图5-42

是的，就是这样！当前对象的关系如图5-43所示。

![](media/image101.jpeg){width="4.415277777777778in"
height="3.6881944444444446in"}

图5-43

那个Blob对象159dba目前还没用到。继续commit下去，看看会发生什么事。

\$ git commit -m \"update index.html\"

\[master 4ddb0b5\] update index.html

1 file changed, 10 insertions(+), 1 deletion(-)

如果与commit之前的状态进行比对，会发现这次的commit多出了两个目录，它们的SHA---1值分别是3a648a和4ddb0b(这里仅使用6码短码表示)。使用git
cat-file 命令查看内容：

\$ git cat-file -t 3a648a98d322f82a72bff20ed977539c581a181d

tree

\$ git cat-file -p 3a648a98d322f82a72bff20ed977539c581a181d

040000 tree a618ce33da8d21bca841f18e6432fcabf15d4477 config

100644 blob 159dba9a492eb6ee354beda28c88652dd7d1c2e2 index.html

这个Tree对象看起来与上一个commit中代表根目录的那个Tree对象相似，只是内容有点不太一样。在这个Tree对象中，原本指向config目录的Tree对象因为没有改动，所以它的指向没有变；反倒是代表index.html的那个Blob对象因为内容有改动，所以指向新的Blob对象了。

接下来查看另一个对象4ddb0b：

\$ git cat-file -t 4ddb0b5fce084d36248eb1ce14109162617abd51

commit

\$ git cat-file-p 4ddb0b5fce084d36248eb1ce14109162617abd51

tree 3a648a98d322f82a72bff20ed977539c581a181d

parent 5d47270a0a3cb0440f77bdfa795bd712b22ec548 author

Eddie Kao \<eddie@5xruby.tw\> 1503469899 +0800 committer

Eddie Kao \<eddie@5xruby.tw\> 1503469899 +0800

update index.html

这个4ddb0b是一个commit对象，从上面的信息来看，也指向一个Tree对象3a648a，其他信息类似，但这个commit对象比前一个commit对象多了一个parent的信息，表示指向"上一次"的commit。当前各个对象的关系如图5-44所示。

![](media/image102.jpeg){width="4.248611111111111in"
height="3.577777777777778in"}

图5-44

分支与HEAD也是随着commit的变化而调整位置。是不是觉得有点复杂？下面在刚才的两条规则上再加三条新的规则：

(1)commit对象会指向某个Tree对象。

(2)Tree对象的内容会指向某个或某些Blob对象，或者其他的Tree对象。

(3)除了第一个commit对象外，所有commit对象都会指向其前一次的commit对象。

接下来再做最后一次commit，为这个"认识git四大天王对象"之旅结尾。

**7.继续向前进**

这次来做一个有趣的试验，在这个项目的根目录下加一个README.md文件，文件内容可以为空：

\$ touch README.md

再把这个文件加入暂存区：

\$ git add README.md

由之前的内容可知，执行gitadd命令后应该会多出一个Blob对象，但如果查看.git/objects目录，会发现并没有变多，其原因是这里已经有一个一样内容的Blob对象了。

还记得吗？一开始放在config目录下的database.yml文件也是空的。在git的世界中，只要文件的内容是一样的，它们就是同一个Blob对象。这时的对象关系如图5-45所示。

![](media/image103.jpeg){width="4.611111111111111in"
height="3.9409722222222223in"}

图5-45

其实图5-45与图5-44没有太大的区别。继续commit：

\$ git commit -m \"add README\"

\[master 4bf7d4a\] add README

1 file changed, 0 insertions(+), 0 deletions(-)

create mode 100644 README.md

这次的commit多了两个新对象，分别是0fc2cc和4bf7d4。先看第一个对象Ofc2cc：

\$ git cat-file -t 0fc2cccfb7a20abde62d9cedd577300b8d1de1a7

tree

\$ git cat-file -p 0fc2cccfb7a20abde62d9cedd577300b8d1de1a7

100644 blob e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 README.md

040000 tree a618ce33da8d21bca841f18e6432fcabf15d4477 config

100644 blob 159dba9a492eb6ee354beda28c88652dd7d1c2e2 index.html

这是一个Tree对象，将它与前一次commit的Tree对象进行对比：

\$ git cat-file -p 3a648a98d322f82a72bff20ed977539c581a181d

040000 tree a618ce33da8d21bca841f18e6432fcabf15d4477 config

100644 blob 159dba9a492eb6ee354beda28c88652dd7d1c2e2 index.html

可以看出，代表config目录的Tree对象以及代表
index.html内容的Blob对象这两行都没有变，只是新增了一行代表README.md的Blob对象。虽然此次的commit并没有产生新的Blob对象，但是Tree对象还是需要记录README.md文件的存在，所以Tree对象的"内容"改变了，因此git会做出一个新的Tree对象。

再来看看第二个对象4bf7d4：

\$ git cat-file -t 4bf7d4adf6e56964ae3c0625bbc54275a02672d7

commit

\$ git cat-file -p 4bf7d4adf6e56964ae3c0625bbc54275a02672d7

tree 0fc2cccfb7a20abde62d9cedd577300b8d1de1a7

parent 4ddb0b5fce084d36248eb1ce14109162617abd51 author

Eddie Kao \<eddie@5xruby.tw\> 1503471804 +0800 committer

Eddie Kao \<eddie@5xruby.tw\> 1503471804 +0800

add README

这个4bf7d4是一个commit对象，它指向刚才那个Tree对象0fc2cc，并且也指向前一次的commit对象。到这里，就可以将这3次commit涉及的所有对象的关系以有向无环图的形式进行展示，如图5-46所示。

这3次的commit共产生了10个对象(分支不算对象)。除了手动计算，也可以使用git计算：

\$ git count-objects

10 objects, 40 kilobytes

没错，是10个。

经过这3次的commit，相信大家已对Blob对象、Tree对象以及commit对象有了更深入的认识。这样的流程也许会让人觉得有点闷，但通过这个过程，如果能理解并预测下一次的commit大概会出现什么对象，就会更清楚git内部的运行原理。

![](media/image104.jpeg){width="6.241666666666666in"
height="3.921527777777778in"}

图5-46

**8.等等，"四大天王"的最后一位还没登场啊**

最后一位\--Tag对象，它不会在commit的过程中出现，必须手动地把Tag贴在某个commit上，而且还不是一般的轻量Tag，而是有附注的Tag(Annotated
Tag)。关于Tag的介绍，可参阅8.1节。

下面在当前的commit上打一个Tag：

\$ git tag -a big_treasure -m \"妈，我在这\"

这时，.git/objects目录下多了一个3b9eab对象，用同样的方式来查看：

\$ git cat-file -t 3b9eab6d623496a272f61076a765301bb7af4367

tag

\$ git cat-file -p 3b9eab6d623496a272f61076a765301bb7af4367

object 4bf7d4adf6e56964ae3c0625bbc54275a02672d7

type commit

tag big_treasure

tagger Eddie Kao \<eddie@5xruby.tw\> 1503508397 +0800

妈，我在这

可以看出这是一个Tag对象，它同样会标记是谁在什么时候做了这个Tag，并且标在4bf7d4这个commit
对象上。现在完整的对象关系如图5-47所示。

![](media/image105.jpeg){width="6.043055555555555in"
height="3.727777777777778in"}

图 5-47

**9.小结**

git中的4种对象的关系如图5-48所示。

![](media/image106.jpeg){width="4.263888888888889in"
height="3.0548611111111112in"}

图5-48

(1)把文件加入git之后，文件的内容会被转成Blob对象存储。

(2)目录及文件名会存放在Tree对象内，Tree对象会指向Blob对象或者其他的Tree对象。

(3)commit对象会指向某个Tree对象。除了第一个commit，其他的commit都会指向前一次的commit对象。

(4)Tag对象(Annotated Tag)会指向某个commit对象。

(5)分支虽然不属于这4种对象之一，但它会指向某个commit对象。

(6)往git服务器上推送之后，在．git/refs下就会多出一个remote目录，里面放的是远端的分支，基本上与本地的分支类似，同样也会指向某个commit对象。

(7)HEAD也不属于这4种对象之一，它会指向某个分支。下节将介绍当git在进行Checkout时会发生的事。

**5.19 .git目录中有什么？Part 2**

5.18节介绍了.git/objects目录中的内容，以及git的一些运行原理，接下来讲解当git在Checkout时会发生什么事，看看为什么git可以这么快地切换状态。

**1.git在Checkout时的变化**

5.18节做了3次commit，最后各个对象的关系如图5-49所示。

![](media/image107.jpeg){width="6.0875in" height="3.8354166666666667in"}

图5-49

虽然.git/objects目录中保留了完整的内容，但工作目录中的内容会根据当前的commit，一个一个地把所有对象抽出来(就像葡萄一样，从根拎起来，整串葡萄就被抽出来了)，所以当前工作目录的内容如图5-50所示。

![](media/image108.jpeg){width="6.039583333333334in"
height="3.765277777777778in"}

图5-50

还以这个例子来说，当试着Checkout到另一个commit时，会出现如下说明

S git checkout 4ddb05

Note: checking out \'4ddb0b51\'

You are in \'detached HEAD\' state.You can 1ook around, make
experimental

changes and commit them，and you can discard any commits you make

in this state without impacting any branches by performing another
checkout

If you want to create a new branch to retain commits you creater you may

do so (now or later) by using -b with the checkout command again.

Example：

git checkout -b \<new-branch-name\>

HEAD is now at 4ddb0b5...update index.html

因为4ddb0b5这个commit没有分支指着，所以会发生detached
HEAD的状况。关于detached HEAD可参阅9.5节。

当git切换到这个节点时，这串"葡萄"的样子如图5-51所示。

![](media/image109.jpeg){width="6.095138888888889in"
height="3.6555555555555554in"}

图5-51

git根据这串信息，把原本放在.git/objects中以SHA-1计算命名的目录及文件，一个一个地复原成原来的样子，所以现在的目录内容是这样的：

\$ 1s -al total 8

drwxr-xr-x 5 eddie staff 170 Aug 24 12:39.

drwxr-xr-x 8 eddie staff 272 Aug 22 16:23..

drwxr-xr-x 13 eddie staff 442 Aug 24 12:39.git

drwxr-xr-x 3 eddie staff 102 Aug 23 06:22 config

-rw-r\--r\-- 1 eddie staff 143 Aug 24 12:39 index.html

在第3次commit才加入的README．md，因为这串"葡萄"中并没有提到它，自然就不会被拎出来。同理，继续往前切换时，结果如下：

\$ git checkout 5d47270

Previous HEAD position was 4ddb0b5\...update index.html

HEAD is now at 5d47270\...init commit

现在的状况如图5---52所示。查看目录内容：

\$ 1s -al total 8

drwxr-xr-x 5 eddie staff 170 Aug 24 12:39.

drwxr-xr-x 8 eddie staff 272 Aug 22 16:23..

drwxr-xr-x 13 eddie staff 442 Aug 24 12:39.git

drwxr-xr-x 3 eddie staff 102 Aug 23 06:22 config

-rw-r\--r\-- 1 eddie staff 14 Aug 24 12:35 index.html

![](media/image110.jpeg){width="5.991666666666666in"
height="3.551388888888889in"}

图5-52

如果能理解"拎葡萄"的概念，就能理解为什么文件与目录会有这样的变化了。

更多关于分支及Checkout时发生的事，如.git/HEAD的变化、工作目录及暂存区的变化，可参阅6.3节的补充。

**2.git不是做差异备份**

有些版控系统会备份每次commit之间的"差异"，如这次加了2行、下次删了5行之类的历史记录，然后通过这些信息，像拼图一样一个一个地把文件还原成它该有的样子。

不过git并不是这样设计的。从前面的流程来看，每次使用git
add命令把文件加到暂存区时，即使文件的内容只改了一个字，因为算出来的SHA---1值不同，所以git也会为它做出一个全新的Blob对象，而不是只记录"差异"。而git在切换commit时会像"拎葡萄"一样整串抽出来，不需要一个一个去拼凑历史记录，所以在进行Checkout时效率相对较高。有些人也会用快照(Snapshot)来形容"拎葡萄"的概念。

**3.这样是不是很浪费空间**

如果git是用这种方式存放文件，就算只改一个字也会做出一个新的对象，那可能就会让人产生疑惑："这样不是很浪费空间吗？"试想一下，如果有一个100KB的文件，因为改了一行代码，就必须再做出一个差不多也是100KB的文件出来。虽然git在制作Blob对象时会先进行压缩，但这样"只差一点点就要备份整个文件"的做法，看起来的确是有点浪费。

对此，git提供了"资源回收机制"。当启用该机制时，git会用非常有效率的方式压缩对象及制作下标。下面用一个全新的项目来举例。先使用git
ls-files命令查询当前文件在git中的样子：

\$ git 1s-files -s

100644 e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 0 config/database.ym1

100644 159dba9a492eb6ee354beda28c88652dd7d1c2e2 0 index.html

当前只有两个文件，分别是index.html及config目录中的database.yml，而index.html的内容
如下：

\<!DOCTYPE html\>

\<html\>

\<head\>

\<meta charset=\"utf-8\"\>

\<title\>\</title\>

\</head\>

\<body\>

\<h1\>Hello, 5xRuby\</h1\>

\</body\>

\</html\>

可以看出，这只是一个简单的HTML页面，这个文件的大小是143
bytes。接着对该文件做一些改动。例如：

\<!DOCTYPE html\>

\<html\>

\<head\>

\<meta charset=\"utf-8\"\> \<title\>5xRuby\</title\>

\</head\>

\<body\>

\<h1\>Hel10,5xRuby\</h1\>

\</body\>

\</html\>

这里只在＜title＞＜/title＞中间加上了5xRuby字样。然后进行commit：

\$ git add index.html

\$ git commit -m \"update index\"

\[master 23ee05d\] update index

1 file changed, 1 insertion(+), 1 deletion(-)

完成commit，查看一下当前的状态：

\$ git 1s-files -s

100644 e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 0 config/database.yml

1006446303bc8384a837e7368692b03cb36cdf16d7f660 0 index.html

git的确为这几个字节的改动做了一个新的Blob对象6303bc。

\$ git cat-file -s 6303bc8384a837e7368692b03cb36cdf16d7f660

149

这个新的Blob对象的大小是149
bytes，只增加了5xRuby6个字，git就为了它做了一个新的Blob对象，这就是前面提到的浪费。但当git启用"资源回收机制"后，会把这些文件以非常有效率的方式打包并做好下标。git的资源回收机制通常会在它觉得对象太多时自动触发，也可直接执行git
gc命令手动触发：

\$ git gc

Counting objects:11, done.

Delta compression using up to 4 threads.

Compressing objects:100% (8/8), done.

Writing objects: 100% (11/11), done.

Total 11 (delta 1),reused 0 (delta 0)

这个命令会把原本放在.git/objects
目录下的那些对象全部打包到.git/objects/pack目录下，变成这个样子：

\$ find.git/objects -type f

.git/objects/info/packs

.git/objects/pack/pack-ea00f1558d67a7df25bf9744f3d83a17a7a2bf43.idx

.git/objects/pack/pack-ea00f1558d67a7df25bf9744f3d83a17a7a2bf43.pack

git中还有一个比较底层的命令 git verify-pack，可以用它来查看打包的情况：

\$ git verify-pack -v .git/objects/pack/pack-ea00f1558d67a7df25bf9744f3d
83a17a7a2bf43.idx

23ee05d5652c770990e4c65d5a0b8ec34ba4f64f commit 215 151 12

44785d18bb2804a9455d7a2e0d9e9f60df482af7 commit 220 156 163

cd05448adf3ee9b11b3cf846a387d1af754b6191 commit 166 120319

e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 blob 0 9 439

6303bc8384a837e7368692b03cb36cdf16d7f660 blob 149 110 448

140454ce2b3d2d493653d01fb8d41ab6bcc22f87 tree 71 81 558

a618ce33da8d21bca841f18e6432fcabf15d4477 tree 40 51 639

3a648a98d322f82a72bff20ed977539c581a181d tree 71 82 690

159dba9a492eb6ee354beda28c88652dd7d1c2e2 blob 9 20 772 1

6303bc8384a837e7368692b03cb36cdf16d7f660

2532115fab19c7ce70ff78a4929fb5df2f6131c4 tree 71 81 792

30ab28d3acb37f96ad61ad8be82c8da46d0a7307 blob 14 23 873

non delta:10 objects

chain length=1:1 object

.git/objects/pack/pack-ea00f1558d67a7df25bf9744f3d83a17a7a2bf43.pack: ok

在上面的这些信息中，第1栏是对象的SHA---1值，第2栏是对象的形态，第3栏则是文件大小。先看下面一行：

6303bc8384a837e7368692b03cb36cdf16d7f660 blob 149 110 448

这个文件是刚刚改动过的index．html，文件大小是149bytes，再看另一行：

159dba9a492eb6ee354beda28c88652dd7d1c2e2 blob 9 20 772 1

6303bc8384a837e7368692b03cb36cdf16d7f660

这个文件是改动前的index.html，但其大小只有9
bytes。原因是这个文件参照了后面的6303bc文件，所以才会这么小。也就是说，虽然在对象状态时是完整的文件(打包前)，在git进行资源回收打包时则使用了类似差异备份的方式，有效地缩小了这些对象的体积。

**4.git什么时候会自动触发资源回收机制**

(1)当.git/objects
目录的对象或打包过的packfile数量过多时，git会自动触发资源回收命令。

(2)当执行git
push命令把内容推至远端服务器时(如果仔细观察过Push命令的信息，就会发现这一点)。

其实，git并不是很在意空间的浪费，能够快速、有效率地操作才是git关注的重点。

**6.3 对分支的误解**

上节虽然介绍了如何使用分支，但我相信有些读者(即使已经使用git一段时间了)对分支还是有些误解的，本节将介绍关于分支的一些概念。

**1.你认为的分支是什么样的**

如果你曾经使用过git的分支，那么想象中的分支会是什么样子？是这样(如图6-8所示)？

![](media/image111.jpeg){width="5.719444444444444in"
height="3.647222222222222in"}

图6-8

还是这样(如图6-9所示)？

![](media/image112.jpeg){width="5.567361111111111in"
height="3.3368055555555554in"}

图6-9

**2.分支是什么**

有人可能认为，所谓的"开分支"，就是把文件先复制到另外的目录，然后进行改动，之后再合并，把文件与原本的文件比对之后放回原来的目录...其实，git不是这样做的。

**3.分支像贴纸一样**

可以把分支想象成一张贴纸，贴在某一个commit上面，如图6-10所示。

![](media/image113.jpeg){width="2.3118055555555554in"
height="0.5347222222222222in"}

图6-10

当做了一次新的commit之后，这个新的commit会指向它的前一个commit，如图6-11所示。

![](media/image114.jpeg){width="2.4159722222222224in"
height="1.3152777777777778in"}

图6-11

而接下来"当前的分支"，也就是HEAD所指的这个分支，会贴到刚刚做的那个commit上，同时HEAD也会跟着前进，如图6-12所示。

![](media/image115.jpeg){width="2.4479166666666665in"
height="1.3458333333333334in"}

图6-12

至于什么是HEAD，可参阅5.15节。

这样解释，是不是让你对分支有了一定的认识？git中的分支并不是通过复制目录或文件来进行改动形成的，它就是一个指标、一张贴纸，贴在某个commit上而已。

**4.一个分支不够，就来两个吧**

如果一个分支不够说明，那就来两个。通过git branch
cat命令创建一个新的分支。它就像一张贴纸，与master贴在同一个地方，如图6-13所示。

![](media/image116.jpeg){width="3.1034722222222224in"
height="1.229861111111111in"}

图6-13

接下来执行git checkout
cat命令，切换到cat分支。此时，HEAD转而指向cat分支，表示它是"当前的分支"，如图6-14所示。

![](media/image117.jpeg){width="3.223611111111111in"
height="1.2506944444444446in"}

图6-14

接着进行一次新的commit，这个新的commit会指向前一次commit，如图6-15所示。

![](media/image118.jpeg){width="3.2715277777777776in"
height="2.0631944444444446in"}

图6-15

然后，cat分支上的"贴纸"就会被撕下来，转而贴到最新的那个commit上；当然HEAD也是一样，如图6-16所示。

![](media/image119.jpeg){width="3.6479166666666667in"
height="1.8881944444444445in"}

图6-16

git中的分支大概就是这样。

**5.切换分支时发生了什么**

6.2节中提到过，原本在cat分支新增的catl.html文件和cat2.md文件，当切换到master分支之后就不见了，但切换回cat分支后就又出现了...git在切换分支时到底做了什么？明明前面提到分支不是将目录或文件复制出来，改动后再放回去，那么为什么切换分支会出现这样的效果？

git在切换分支时主要做了以下两件事。

(1)更新暂存区和工作目录。

git在切换分支时，会用该分支指向的那个commit的内容来"更新"暂存区(Staging
Area)及工作目录(Working
Directory)。但在切换分支之前所做的改动则会留在工作目录中，不受影响。

这段话有点难理解，先来看看前半段的意思。假设原本正处于cat分支，执行下面的命令后，就会由cat分支切换到master分支：

\$ git checkout master

接下来，git会用master分支指向的那个commit的内容来更新暂存区及工作目录。因为master此时指向的commit并没有catl．html和cat2．html这两个文件，所以"更新"之后，不管在
暂存区还是在工作目录中都不会有这两个文件。同理，再次切换回cat分支时：

\$ git checkout cat

git会用cat分支指向的那个commit的内容来"更新"暂存区及工作目录，所以这两个文件就又出现了。

等等，什么是"那个commit的内容"？

在git的世界中，每一次的commit都是一个对象，它会指向某一个Tree对象(目录)，而这些Tree对象会指向其他的Tree对象(子目录)或Blob对象(文件)。这种结构有点像葡萄，如图6-17所示。只要伸手把源头的commit对象拎起来，整串内容都可以被拿出来。关于这些git对象的详细说明，可参阅5.18节。

![](media/image120.jpeg){width="3.3833333333333333in"
height="2.16875in"}

图6-17

(2)变更HEAD的位置。

除了更新暂存区及工作目录的内容外，HEAD也会指向刚刚切换过去的那个分支，也就是说，git/HEAD文件会一起被改动。关于HEAD的介绍，可参阅5.15节。

**6.如果将文件改动了一半就切换分支会发生什么**

假设现在还在cat分支，在切换到master分支之前，新增了一个cat3.html文件，同时也改动了index.html文件的内容，这时的状态如下：

\$ git status On branch cat

Changes not staged for commit:

(use \"git add \<file\>\...\" to update what will be committed)

(use \"git checkout \--\<file\>\...\" to discard changes in working
directory)

> modified:index.html

Untracked files:

(use \"git add \<file\>\...\" to include in what will be committed)
cat3.html

no changes added to commit (use \"git add\" and/or \"git commit -a\")

当前index.html是modified状态，而cat3.html是Untracked状态。如果这时就直接切换到
master分支，也就是还没commit就切换分支，会发生什么事？

前文提到过，"git在切换分支时，会用该分支指向的那个commit的内容来"更新＇暂存区(Staging
Area)及工作目录(Working
Directory)。但在切换分支之前所做的改动则会留在工作目录
中，不受影响"。其中"在切换分支之前所做的改动则会留在工作目录中，不受影响"说的就是这件事。直接操作看看：

\$ git checkout master

M index.html

Switched to branch \'master\'

查看一下文件列表：

\$ 1s-al

total 16

drwxr-xr-x 8 eddie wheel 272 Aug 18 03:50 .

drwxrwxrwt 84 root wheel 2856 Aug 18 03:03 ..

drwxr-xr-x 16 eddie wheel 544 Aug 18 03:50 .git

-rw-r\--r\-- 1 eddie wheel 0 Aug 18 03:48 cat3.html

drwxr-xr-x 3 eddie wheel 102 Aug 17 15:06 config

-rw-r\--r\-- 1 eddie wheel 0 Aug 18 03:27 hello.html

-rw-r\--r\-- 1 eddie wheel 174 Aug 18 03:27 index.html

-rw-r\--r\-- 1 eddie wheel 11 Aug 17 14:56 welcome.html

可以看到，刚刚新增的cat3.html文件还在。再看一下git的状态：

\$ git status

On branch master

Changes not staged for commit:

(use \"git add \<file\>\...\" to update what will be committed)

(use \"git checkout \--\<file\>\...\" to discard changes in working
directory) modified:index.html

Untracked files:

(use \"git add \<file\>\...\" to include in what will be committed)

cat3.html

no changes added to commit (use \"git add\" and/or \"git commit -a\")

可以看到，git的状态与刚刚在cat分支时的状态是一样的，也就是说，切换分支并不会影响已经在工作目录中的那些改动。

**7.小结**

上面这些内容跟你原来想象或认知的分支是一样的吗？分支在git中的使用频率非常高，甚至可以说是大家使用git的主要原因之一，所以一定要建立关于分支的正确观念。这样不管是在终端机界面使用命令，还是使用图形界面工具，在操作分支时都不会轻易出现问题了。

**6.4合并分支**

在前面的例子中，从master分支开了一个cat分支，并且做了两次commit，现在大概是这个样子，如图6-18所示。

![](media/image121.jpeg){width="3.607638888888889in"
height="2.5590277777777777in"}

图6-18

任务执行得差不多了，就要准备合并回来了。如果想要用master分支来合并cat分支，就要先切换回master分支：

\$ git checkout master Switched to branch \'master\'

接下来，使用git merge 命令合并分支：

\$ git merge cat

Updating 35c42e..f17acb Fast-forward

cat1.html \| 0

cat2.html \| 0

2 files changed, 0 insertions(+), 0 deletions(-)

create mode 100644 cat1.html

create mode 100644 cat2.html

查看一下文件列表：

\$ 1s -al total 16

drwxr-xr-x 9 eddie wheel 306 Aug 18 05:14 .

drwxrwxrwt 84 root wheel 2856 Aug 18 04:29 ..

drwxr-xr-x 16 eddie wheel 544 Aug 18 05:15 .git

-rw-r\--r\-- 1 eddie wheel 0 Aug 18 05:14 cat1.html

-rw-r\--r\-- 1 eddie wheel 0 Aug 18 05:14 cat2.html

drwxr-xr-x 3 eddie wheel 102 Aug 17 15:06 config

-rw-r\--r\-- 1 eddie wheel 0 Aug 18 03:27 hello.html

-rw-r\--r\-- 1 eddie wheel 161 Aug 18 04:24 index.html

-rw-r\--r\-- 1 eddie wheel 11 Aug 17 14:56 welcome.html

因为master现在已经合并了cat分支，所以在cat分支新增的catl.html文件和cat2.html文件在
master分支也出现了。

**A合并B，与B合并A有什么不同**

对于这个问题，我一开始学git的时候也被困扰过很长时间。到底谁合并谁有那么重要吗？这就要看你关注的重点是什么了。如果以最终结果来看是一样的，但过程可能会有些区别。在此假设从master分支创建了cat和dog两个分支，并且当前正在cat分支，如图6-22所示。

![](media/image122.jpeg){width="4.4in" height="2.5256944444444445in"}

图6-22

cat分支与dog分支都是来自
master分支，所以不管master是要合并cat分支还是dog分支，git都会直接使用快转模式(Fast
Forward)进行合并，也就是master直接"收割"cat或dog的成果。

但如果是cat与dog这两个分支要互相合并就不一样了，虽然它们有同样的来源，但要合并就不会这么顺利了。在这种情况下，git会生成一个额外的commit来处理这件事。一般的commit只会指向某一个commit，但这个commit会指向两个commit，明确地标记是来自哪两个分支。

来看看会怎么演变。假设想用cat分支来合并dog分支，可用如下命令：

\$ git merge dog

Merge made by the \'recursive\' strategy.

dog1.html \| 0

dog2.html \| 0

2 files changed, 0 insertions(+), 0 deletions(-)

create mode 100644 dog1.html

create mode 100644 dog2.html

执行这个命令时会弹出一个vim编辑器窗口，如果忘记了Vim怎样操作，可回顾一下3.2节的内容。为了进行这次合并，git做出了这个额外的commit对象，这个commit会分别指向cat分支和dog分支，HEAD随着cat分支往前，而dog分支停留在原地，如图6---23所示。

![](media/image123.jpeg){width="3.9277777777777776in"
height="3.3402777777777777in"}

图6-23

如果改由dog分支来合并cat分支，则使用如下命令：

\$ git merge cat

Merge made by the \'recursive\' strategy.

cat1.html \| 0

cat2.html \| 0

2 files changed, 0 insertions(+), 0 deletions(-)

create mode 100644 catl.html

create mode 100644 cat2.html

程序上与刚才几乎是一样的。这时的状态如图6-25所示。

![](media/image124.jpeg){width="3.8555555555555556in"
height="3.2284722222222224in"}

图6-25

**2.哪里不一样**

其实就结果来看，不管是谁合并谁，这两个分支的文件最后都得到了。如果只看SourceTree的界面，则会认为不同的合并方式有谁在前面、谁在后面的差别。但事实上并不是这样，那只是因为软件没办法画出来"平行"的效果而已。

事实上不管是谁合并谁，这两个分支上的commit都是对等的。如果非要说哪里不一样，就是cat分支合并dog分支时，cat分支会往前移动，反之亦然。不过前面提到过，分支就像贴纸一样，删除或改名都不会影响现在已经存在的commit。

不一样的地方还有一处，就是这个为了合并而生成的额外的commit对象，里面会记录两个"老爸"，谁合并谁就会有"谁在前面"的区别，不过这就有点太过细节了。

图6-27所示的是cat分支合并dog分支，所以cat分支b174a5a95a在前面。

![](media/image125.jpeg){width="4.335416666666666in"
height="1.6576388888888889in"}

图6-27

图6-28所示的是dog分支合并cat分支，所以dog分支053fb212bb在前面。

![](media/image126.jpeg){width="4.303472222222222in"
height="1.7680555555555555in"}

图6-28

这很重要吗？国外曾经有一个名为Ruby(后来改名为PolyConf)的研究会，是由Ruby和Python合办的，那为什么Ruby要放前面？Python的人可能会想为什么不叫PyRu？这大概就跟A合并B与B合并A的区别差不多。

**6.5 为什么我的分支没有"小耳朵"**

我看别人的合并都会有"小耳朵"，为什么我的没有？

这里的"小耳朵"是指在合并的时候产生的线图，如图6-29所示。

![](media/image127.jpeg){width="4.367361111111111in"
height="2.904166666666667in"}

图6-29

1.不是每次的合并都这么复杂

以图6-29中的例子来说，其实有这个线图也是不得已的，cat分支与dog分支虽是"同根生"，但后来已各自"长大、分家"了，所以最后要合并时，git就会做出一个额外的commit，以记录分支是来自哪两个commit。

再看看图6-30所示的例子。

![](media/image128.jpeg){width="5.158333333333333in"
height="2.9930555555555554in"}

图6-30

cat分支是从master分支分出去的，当前领先master两次commit。如果这时回到master并且
合并cat分支，git会发现"其实你是从我这边出去的，除了这两个新的commit以外的东西我都有了"，所以git就会自动选用"快转模式"(Fast
Forward)来进行合并：

\$ git merge b174a5a

Updating e12d8ef..b174a5a

Fast-forward

cat1.html \| 0

cat2.html \| 0

2 files changed, 0 insertions(+), 0 deletions(-)

create mode 100644 cat1.html

create mode 100644 cat2.html

注意到上面这段代码中也有Fast-forward字样了吗？这个所谓的"快转模式"，其实就是把master这张贴纸撕下来，然后往前贴到cat分支所指的commit上而已，如图6-31所示。

![](media/image129.jpeg){width="5.095833333333333in"
height="2.964583333333333in"}

图6-31

这种快转模式的合并不会有额外的线图(也就是"小耳朵")出现。

**2.就是想要线图怎么办**

如果一定要加线图也是可以的，只要在合并时加上\--no-ff参数：

\$ git merge cat \--no-ff

Merge made by the \'recursive\' strategy. cat1.html \|0

cat2.html \| 0

2 files changed, 0 insertions(+), 0 deletions(-)

create mode 100644 cat1.html

create mode 100644 cat2.html

\--no-ff参数是指不要使用快转模式合并，这样就会额外做出一个commit对象，如图6-32所示。

![](media/image130.jpeg){width="4.813194444444444in"
height="3.1277777777777778in"}

图6-32

**3."小耳朵"的存在有必要吗**

那这个"小耳朵"到底必要吗？它的存在到底有意义吗？非快转模式合并的好处是可以完整保留分支的样子，但如果不是很介意这一点的话，也就没有必要非要做出"小耳朵"了。

# 5)git命令操作图示 

https://learngit
branching.js.org/，可视化，直接看到每一条git命令操作的结果。是git练习的好帮手，推荐。

**Learngit branching网站使用方法**，常用命令如下：

\$ show commands，显示支持的命令

\$ show solution，查看答案

\$ show goal / hide goal，显示/关闭目标提示

\$
levels，选择不同级别的关卡进行练习，达到设定的目标可以通关。限定只能使用某些git命令。

\$
sandbox，进入沙盒中，不在设定的关卡里，可以使用任何git命令，自由发挥。

如果想通关练习，那就输levels命令选择关卡；如果想自由发挥，那就输sandbox命令，进入沙盒中。

通关过程中，如果想查看答案，输show solution命令。

### 提交

![](media/image131.png){width="0.8958333333333334in"
height="2.261111111111111in"}

C2的父节点是C1，父节点是当前提交中变更的**基**础。

git commit

git仓库中的提交记录保存的是你的目录下所有文件的**快照**，就像是把整个目录复制，然后再粘贴一样，但比复制粘贴优雅许多。

git希望提交记录尽可能地轻量，因此在你每次进行提交时，它并不会盲目地复制整个目录。条件允许的情况下，它会将当前版本与仓库中的上一个版本进行对比，并把所有的差异打包到一起作为一个提交记录。

git还保存了提交的历史记录。这也是为什么大多数提交记录的上面都有父节点的原因
\--
我们会在图示中用箭头来表示这种关系。对于项目组的成员来说，维护提交历史对大家都有好处。

关于提交记录太深入的东西咱们就不再继续探讨了，现在你可以把提交记录看作是项目的快照。提交记录非常轻量，**可以快速地在这些提交记录之间切换**。

### 在提交树上移动

一旦熟悉了如何在 git提交树上移动，你驾驭其它命令的能力也将水涨船高。

![](media/image132.png){width="1.007638888888889in"
height="1.5444444444444445in"} 🡪
![](media/image133.png){width="1.6041666666666667in"
height="1.8131944444444446in"},
![](media/image134.png){width="1.1118055555555555in" height="1.73125in"}

\$ git checkout C2 或者，\$ git checkout C1

### 分离的HEAD

在命令执行之前的状态如下所示：HEAD -\> master -\>
C1。此时HEAD指向master，master指向C1。

执行git checkout C1命令后状态为：HEAD -\>
C1。此时HEAD指向C1，不再指向master。

**HEAD指向某一个提交、而不指向分支名**，此时称为**分离的HEAD**。git提示:You
are in \'detached HEAD\' state.

在分离的HEAD状态下，会**跳出当前分支，不在任何分支上**。

如果想看HEAD指向，可以通过cat
.git/HEAD查看，如果HEAD指向的是一个引用，还可以用git symbolic-ref
HEAD查看它的指向。

![](media/image135.png){width="1.1569444444444446in"
height="1.8805555555555555in"} 🡪
![](media/image136.png){width="1.6270833333333334in"
height="2.216666666666667in"}

正常情况下，**HEAD指向当前所在分支最后一次提交**。上图中，**HEAD指向master分支的最后一次提交C10**。

但是，某些情况下，会**造成HEAD指针脱离分支，不指向有效分支**。

例如，master分支最新提交是C10，在master分支上执行git checkout
C8_SHA命令，会造成**HEAD指向提交C8(不再指向C10)，并且跳出master分支，不在任何有效分支上**，这就是**分离的HEAD**。

注：git checkout SHA，可以是任意分支的任意提交的SHA，可以跨分支，例git
checkout test\^\^表示checkout到test分支最新提交的父提交的父提交。

![](media/image137.png){width="1.0145833333333334in"
height="1.9104166666666667in"}

在分离的HEAD上，使用git branch命令查看，显示不在任何分支上。

在分离的HEAD上进行工作不安全，会造成提交丢失。

![](media/image138.png){width="3.6041666666666665in"
height="2.0972222222222223in"}

上图，在分离的HEAD上进行工作，并且commit了两个提交C11、C12，但是这两个提交并没有保存在有效的分支上，会造成丢失。

**如何保存分离HEAD状态下的提交？**

方法一：先切换到master分支，然后使用git cherry-pick、git merge、git
rebase等命令合并。

\$ git checkout master

\$ git cherry-pick C11_SHA

或者\$ git merge C11_SHA

或者\$ git rebase C11_SHA

方法二：在分离的HEAD上，使用git branch
saveBranch新建分支，然后切换到该新建分支，这样，所有分离HEAD状态下的提交都包含在这个新建分支上了。

\$ git branch saveBranch

\$ git checkout saveBranch

新的分支saveBranch包含了所有在分离HEAD状态下的提交。

或者，直接使用一条checkout -b命令，

\$ git checkout -b saveBranch

附：怎么找到分离HEAD提交对应的哈希值SHA？事实上，**只要使用了commit命令进行了提交**，无论是分离HEAD上的提交，还是使用reset命令进行了重置，**都可以使用reflog命令找回来**，参考后续章节:git
reflog命令。

#### 基于某一个提交建立分支

理解了分离的HEAD，以及如何在分离的HEAD基础上建立分支，其实可以引申出一个方法：基于某一个提交建立分支，如下：

\$ git checkout -b branch_name SHA

这条命令会在SHA所在提交的基础上，建立一个branch_name的分支，并且切换到这个新建分支。

SHA可以是git库里的任何一次提交，可以当前分支的提交，也可以其他分支的提交，也可以是detach
HEAD状态的提交。

如果需要在某一个提交上做试验，基于某一个提交建立新的分支、开发新的特性，这条命令能省去一些步骤，一步到位。

### 强制修改分支位置

相对引用为我们提供了一种简洁的引用提交记录C1的方式，而-f则容许我们将分支强制移动到那个位置。

可以直接**使用-f选项让分支指向另一个提交**。例如:

\$ git branch -f master HEAD\~

上面的命令会将 master 分支强制指向HEAD的父提交。

**与上面git checkout
SHA不同，f参数让分支指向某个提交，不会跳出当前分支，仍然在原来分支上**。**git
branch
-f可以将分支强制指向任何位置**，也就是**将分支HEAD指向任何提交**。

![](media/image139.png){width="3.589583333333333in"
height="2.2534722222222223in"} 🡪
![](media/image140.png){width="1.4180555555555556in"
height="2.283333333333333in"}

执行git branch -f master HEAD\~

git branch -f和git
reset效果一样，可以将当前分支指向**任何提交**，**这个提交可以是在当前分支的，也可以跨分支的**，例如当前在master分支C2，可以使用git
branch -f master HEAD\~或者git reset
HEAD\~将master分支强制指向C1，也可以使用git branch -f master
C3_SHA或者git reset C3_SHA将master分支强制指向bugFix分支的C3(这个奇特)。

![](media/image141.png){width="1.3284722222222223in" height="2.19375in"}

执行git branch -f master C3或者git reset C3

但是**git reset只能修改当前分支的HEAD指向**，而git branch
-f可以**在当前分支修改其他分支的HEAD指向**。例如，当前在master分支，可以使用git
branch -f bugFix
C3将bugFix分支强制指向C3(也很奇特，都不在bugFix分支上工作，却能修改bugFix分支的HEAD指向)。

![](media/image142.png){width="4.097222222222222in"
height="1.9027777777777777in"}

执行git branch -f bugFix C3

最好不要在当前分支修改其他分支的HEAD指向，这样很危险。

小结：git reset SHA和git checkout SHA

git reset SHA在节点之间移动，和git checkout
SHA在节点之间移动的区别是：git reset
SHA是在某个分支的节点之间移动，执行该命令后仍然在某个分支上；

git checkout
SHA只是在节点之间移动，执行该命令后会处于detached状态，不在任何分支上。detached状态下的修改需要建立分支才能保存。

### 在提交记录之间切换

#### 绝对引用

使用git commit进行提交操作，产生提交对象，创建提交历史记录。

**git所有的操作都是基于提交对象**。提交历史记录的产生、分支的创建、分支合并，等等，都基于提交对象。

**所有保存在git数据库中的东西都是用哈希值来作索引的**，哈希值SHA由40个十六进制字符(0-9及a-f)组成。

**git提交对象也可以通过SHA值来索引**。

使用**git checkout SHA**可以**在任意提交对象之间移动**。

注：这个操作会跳出当前所在分支，进入detach
HEAD状态，此时HEAD不指向任何分支。

通常情况下，HEAD指向当前所在分支的最新提交。

git checkout
commit_SHA，commit可以是当前分支的提交，也可以其他分支的提交。

例如本地库有两个分支master、bugFix，假设当前在master分支上、最新提交C2，如下：

![](media/image143.png){width="3.723611111111111in"
height="2.3583333333333334in"}

可以使用git checkout HEAD\~ / git checkout HEAD\^ / git checkout
master\~ / git checkout master\^切换到C1，如下：

![](media/image144.png){width="3.80625in" height="2.3881944444444443in"}

注意，此时处于分离的HEAD状态。

也可以使用git checkout C3_SHA / git checkout bugFix\~ / git checkout
bugFix\^切换到C3，如下：

![](media/image145.png){width="3.8805555555555555in"
height="2.4479166666666665in"}

此时也处于分离的HEAD状态。

如果使用git checkout bugFix就是分支切换了。

#### 相对引用

通过指定提交记录哈希值的方式在git中移动不太方便。在实际应用时，并没有像本程序中这么漂亮的可视化提交树供你参考，所以你就不得不用git
log来查查看提交记录的哈希值。

并且哈希值在真实的git世界中也会更长(译者注：基于 SHA-1，共 40
位)。例如前一关的介绍中的提交记录的哈希值可能是fed2da64c0efc5293610bdd892f82a58e8cbc5d8。舌头都快打结了吧\...

比较令人欣慰的是，git对哈希的处理很智能。你只需要提供能够唯一标识提交记录的前几个字符即可。因此我可以仅输入fed2
而不是上面的一长串字符。

正如我前面所说，通过哈希值指定提交记录很不方便，所以
git引入了相对引用。这个就很厉害了!

使用相对引用的话，你就可以从一个易于记忆的地方(比如 bugFix 分支或
HEAD)开始计算。

相对引用非常给力，这里我介绍两个简单的用法：

使用\^向上移动1个提交记录

使用\~\<num\>向上移动多个提交记录，如\~3

![](media/image146.png){width="0.9180555555555555in"
height="2.2090277777777776in"} 🡪
![](media/image147.png){width="0.8729166666666667in" height="2.23125in"}

\$ git checkout master\^

首先看看操作符(\^)。把这个符号加在引用名称的后面，表示让git寻找指定提交记录的父提交。

所以**master\^相当于"master 的父节点"**。

master\^\^是master的第二个父节点

现在咱们切换到master的父节点：git checkout master\^

搞定。这种方式是不是比输入哈希值方便多了。

你**也可以将HEAD作为相对引用的参照**。下面咱们就用HEAD在提交树中向上移动几次。

\$ git checkout C3; git checkout HEAD\^; git checkout HEAD\^; git
checkout HEAD\^

我们可以一直使用HEAD\^向上移动。

**"\~"操作符**

如果你想在提交树中向上移动很多步的话，敲那么多\^貌似也挺烦人的，git当然也考虑到了这一点，于是又引入了操作符
\~。

该操作符后面可以跟一个数字(可选，不跟数字时与\^相同，向上移动一次)，指定向上移动多少次，例git
checkout HEAD\~4。

操作符\^和\~，加在引用名称的后面，表示让git寻找指定提交记录的父提交。

那么master\^/ master\~表示master
的父节点，master\^\^/master\~\~表示master的父节点的父节点。

\~后可以加数字，\~\<num\>表示向上移动多个提交记录，如\~3。

\~和\^的不同：\~后面可以加数字表示多级父提交,如HEAD\~3/
HEAD\~4，\^后面不能加数字, HEAD\^3没有意义。

\$ git checkout master\^或git checkout HEAD\^

上面的命令会向上移动1个提交记录。注意：这样会跳出当前分支，不在任何分支上，处于分离HEAD状态，参考下一节:分离的HEAD。

#### 分支切换

使用git checkout SHA在提交记录之间移动、切换，如果将SHA改为分支，git
checkout branch则是分支切换了。本质上，它们是一样的，git checkout
branch其实也是切换到分支的最新的提交上。

\$ git checkout SHA，在提交记录之间切换

\$ git checkout branch_2，在不同分支之间切换

\$ git checkout -b branch_2，新建分支并且切换到该新建分支，

\$ git checkout -b branch_2
some_SHA，新建分支并且切换到该新建分支，并且新建分支的HEAD指向some_SHA，或者说，基于提交some_SHA建立分支。

### 撤销修改

#### 撤销未提交的修改

撤销工作区、暂存区的修改，修改还没有提交，没产生提交记录，使用git
checkout path、git restore path、git reset \--hard HEAD撤销修改。

建议使用git checkout path、git restore path撤销工作区修改。

撤销单个文件的修改到某个提交的状态：git checkout SHA path、git checkout
HEAD path

#### 撤销已提交的修改

修改已经的提交，产生了提交记录，有两种方法用来撤销已提交的修改：git
reset和git revert。

##### git reset

![](media/image148.png){width="0.8284722222222223in"
height="2.0743055555555556in"} 🡪
![](media/image149.png){width="0.8583333333333333in"
height="2.1041666666666665in"} \|\| 🡪
![](media/image150.png){width="0.9701388888888889in"
height="2.089583333333333in"}

\$ git reset HEAD\~1 改为\$ git revert HEAD\~1

git reset
通过**把分支记录回退**几个提交记录来实现撤销改动。你可以将这想象成"改写历史"。git
reset 向上移动分支，原来指向的提交记录就跟从来没有提交过一样。

让我们来看看演示：git reset HEAD\~1

漂亮! git把 master 分支移回到 C1；现在我们的本地代码库根本就不知道有 C2
这个提交了。

(译者注：**在reset后，C2所做的变更还在，但是处于未加入暂存区状态**。)

##### git revert

虽然在你的本地分支中使用git
reset很方便，但是这种"改写历史"的方法对大家一起使用的远程分支是无效的，

为了撤销更改并分享给别人，我们需要使用 git
revert。revert之后就可以把你的更改推送到远程仓库与别人分享。

\-- git
reset只能改写本地库的历史，不能提交到远程库。revert改写历史记录是可以提交到远程库的。

为了撤销更改并分享给别人，我们需要使用 git revert。来看演示：

\$ git revert HEAD\~1

奇怪，在我们要撤销的提交记录后面居然多了一个新提交。这是因为新提交记录
C1\' 引入了更改 \-- 这些更改刚好是用来撤销 C1
这个提交的。相当仓库中C1不存在，只有C0和C2。

revert 之后就可以把你的更改推送到远程仓库与别人分享啦。

附：

\$ git pull

\$ git reset HEAD\~\~ \--hard

\$ git commit

\$ git push

此时，会拒绝push。

提示：远程仓库与你的本地仓库产生了分歧，故此上传操作无法通过Fast-forword实行(因此你的push被拒绝了)。请pull下来远程仓库里最新的更改，与这个分支合并之后再试一次。你可以通过git
pull或git pull \--rebase实现。

\$ git pull

\$ git push

问题解决。

\$ git pull

\$ git revert HEAD\~\~ \--hard

\$ git push

这样是可以的。

git reset与git revert的区别，参考后面章节。

### 分支

#### git branch

git的**分支**也非常**轻量**。**它们只是简单地指向某个提交纪录**。所以许多git爱好者传颂：早建分支！多用分支！

这是因为即使创建再多分的支也不会造成储存或内存上的开销，并且按逻辑分解工作到不同的分支要比维护那些特别臃肿的分支简单多了。

在将分支和提交记录结合起来后，我们会看到两者如何协作。现在只要记住使用分支其实就相当于在说"**我想基于这个提交以及它所有的父提交进行新的工作**。"

接下来，我们将要创建一个到名为 newImage 的分支。

![](media/image151.png){width="0.9555555555555556in"
height="1.3284722222222223in"} 🡪
![](media/image152.png){width="1.0375in" height="1.4027777777777777in"}

\$ git branch newImage //星号\*表示当前所在的分支是master

看到了吗，创建分支就是这么容易！**新创建的分支newImage指向的是提交记录C1**。

**git
branch是以当前HEAD指针为基础建立分支的**，不管当前是在分支上，还是处于dettach
HEAD状态。

git checkout -b
branch是在当前HEAD的基础上建立分支、并且切换到该新建分支。

git checkout -b branch
commit是基于指定commit建立分支、并且切换到该新建分支。

git checkout -b branch
master是基于master分支建立分支、并且切换到该新建分支。

git checkout branch是切换分支，git checkout commit则会进入dettach
HEAD状态。

![](media/image153.png){width="4.679166666666666in"
height="2.365972222222222in"}

多分支

#### git tag

相信通过前面课程的学习你已经发现了：分支很容易被人为移动，并且当有新的提交时，它也会移动。分支很容易被改变，大部分分支还只是临时的，并且还一直在变。

你可能会问了：有没有什么可以永远指向某个提交记录的标识呢，比如软件发布新的大版本，或者是修正一些重要的
Bug
或是增加了某些新特性，有没有比分支更好的可以永远指向这些提交的方法呢？

当然有了！git的 tag 就是干这个用的啊，它们可以(在某种程度上 ------
因为标签可以被删除后重新在另外一个位置创建同名的标签)永久地将某个特定的提交命名为里程碑，然后就可以像分支一样引用了。

更难得的是，它们并不会随着新的提交而移动。你也不能检出到某个标签上面进行修改提交，它就像是提交树上的一个锚点，标识了某个特定的位置。

咱们先建立一个标签，指向提交记录C1，表示这是我们1.0版本。

\$ git tag v1 C1

我们将这个标签命名为v1，并且明确地让它指向提交记录C1，如果你不指定提交记录，git会用HEAD所指向的位置。

\$ git tag v1

#### git describe

由于标签在代码库中起着"锚点"的作用，git还为此专门设计了一个命令用来描述离你最近的锚点(也就是标签)，它就是
git describe！

git describe 能帮你在提交历史中移动了多次以后找到方向；当你用 git
bisect(一个查找产生 Bug
的提交记录的指令)找到某个提交记录时，或者是当你坐在你那刚刚度假回来的同事的电脑前时，
可能会用到这个命令。

git describe 的​​语法是：

git describe \<ref\>

\<ref\>可以是任何能被git识别成提交记录的引用，如果你没有指定的话，git会以你目前所检出的位置(HEAD)。

它输出的结果是这样的：

\<tag\>\_\<numcommits\>\_g\<hash\>

tag 表示的是离 ref 最近的标签，
numcommits是表示这个ref与tag相差有多少个提交记录，
hash表示的是你所给定的ref所表示的提交记录哈希值的前几位。

当ref提交记录上有某个标签时，则只输出标签名称。

![](media/image154.png){width="1.8131944444444446in"
height="2.5520833333333335in"}

让我们来看一个例子，对于下面的提交树：git tag v2 C3

git describe master会输出：v1_2_gC2

git describe side会输出：v2_1_gC4

### cherry-pick

cherry-pick可以将提交树上任何地方的提交记录**取过来追加到HEAD上**(只要不是HEAD上游的提交就没问题)。

本系列的第一个命令是 git cherry-pick, 命令形式为: git cherry-pick
\<提交号\>\...

如果你想将一些提交复制到当前所在的位置(HEAD)下面的话， Cherry-pick
是最直接的方式了。我个人非常喜欢 cherry-pick，因为它特别简单。

![](media/image155.png){width="1.5819444444444444in"
height="2.283333333333333in"} 🡪
![](media/image156.png){width="1.5444444444444445in"
height="2.4479166666666665in"}

\$ git cherry-pick C2 C4

我们只需要提交记录C2和C4，所以git就将被它们抓过来放到当前分支下了。
就是这么简单!

摘取过来后生成一个新的提交C2\'，C2\'=C2。

### merge

在git中合并两个分支时会产生一个特殊的提交记录，它有两个父节点。翻译成自然语言相当于"我要把这两个父节点本身及它们所有的祖先都包含进来。"

我们准备了两个分支，每个分支上各有一个独有的提交。这意味着没有一个分支包含了我们修改的所有内容。咱们通过合并这两个分支来解决这个问题。

我们要把 bugFix 合并到 master 里

![](media/image157.png){width="1.5972222222222223in" height="2.5in"} 🡪
![](media/image158.png){width="1.5895833333333333in"
height="2.5145833333333334in"} 🡪
![](media/image159.png){width="1.5375in" height="2.5520833333333335in"}

\$ git merge bugFix \$ git checkout bugFix; git merge master

哇哦！看见了吗？首先，master现在指向了一个**拥有两个父节点**的提交记录。假如从master开始沿着箭头向上看，在到达起点的路上会经过所有的提交记录。这意味着master**包含了对代码库的所有修改**。

咱们再把 master 分支合并到 bugFix：

git checkout bugFix; git merge master

因为 master 继承自
bugFix，**git什么都不用做，只是简单地把bugFix移动到master所指向的那个提交记录**。

现在所有提交记录的颜色都一样了，这表明每一个分支都包含了代码库的所有修改！大功告成！

#### 快进

![](media/image160.png){width="0.9777777777777777in"
height="2.1791666666666667in"} 🡪
![](media/image161.png){width="1.0444444444444445in" height="2.19375in"}

\$ git checkout master

\$ git merge test

合并比自己更新的分支，是一次"**快进**"，**快速前进(Fast forward)**。

### rebase

第二种合并分支的方法是 git rebase。rebase
实际上就是取出一系列的提交记录，"复制"它们，然后在另外一个地方逐个的放下去。

rebase
的优势就是可以创造更线性的提交历史，这听上去有些难以理解。如果只允许使用
rebase 的话，代码库的提交历史将会变得异常清晰。

![](media/image162.png){width="1.7013888888888888in"
height="2.6569444444444446in"} 🡪
![](media/image163.png){width="1.7465277777777777in"
height="2.522222222222222in"} 🡪
![](media/image164.png){width="1.6868055555555554in"
height="2.4256944444444444in"}

\$ git rebase master \$ git checkout master; git rebase bugFix

还是准备了两个分支；注意当前所在的分支是 bugFix(星号标识的是当前分支)

我们想要把 bugFix 分支里的工作直接移到 master
分支上。移动以后会使得两个分支的功能看起来像是按顺序开发，但实际上它们是并行开发的。

咱们这次用 git rebase 实现此目标：git rebase master

怎么样？！现在 bugFix 分支上的工作在 master
的最顶端，同时我们也得到了一个更线性的提交序列。

注意，提交记录 C3 依然存在(树上那个半透明的节点)，而 C3\' 是我们 Rebase
到 master 分支上的 C3 的副本。

现在唯一的问题就是 master 还没有更新，下面咱们就来更新它吧......

现在我们切换到了 master 上。把它 rebase 到 bugFix 分支上......

git rebase bugFix

好了！由于 bugFix 继承自 master，所以 git只是简单的把 master
分支的引用向前移动了一下而已。

#### merge、rebase比较

![](media/image165.png){width="3.671527777777778in"
height="3.1569444444444446in"}

包含master和test两个分支的git库。

切换到master分支上，执行git merge命令，结果如下：

\$ git checkout master

\$ git merge test

![](media/image166.png){width="3.761111111111111in"
height="3.8430555555555554in"}

merge后生成一个新的提交c8，c8提交包含了test分支c6、c7的修改。

如果改为rebase，会怎样？

\$ undo //撤销之前操作

切换到master分支上，执行git rebase命令，结果如下：

\$ git checkout master

\$ git rebase test

![](media/image167.png){width="4.455555555555556in"
height="4.485416666666667in"}

rebase之后，master分支C3的父提交不再是C2，而是C6、C7。这就是**rebase的字面含义，re-base：重新定义基(base)**，**将master分支的基由C2变成了C6、C7**。**基改变后，相当于将C3、C4、C5在C6、C7的基础上重新生成一次，重新生成后的提交用C3\'、C4\'、C5\'表示，事实上C3\'=C3、C4\'=C4、C5\'=C5。**

如果切换到test分支上，执行git rebase命令，结果如下：

\$ git checkout test

\$ git rebase master

![](media/image168.png){width="5.910416666666666in"
height="4.395833333333333in"}

#### rebase参数

\$ git checkout master

\$ git rebase test

首先切到master分支，然后将master分支rebase到test分支上。

\$ git checkout test

\$ git rebase master

首先切到master分支，然后将master分支rebase到test分支上。

其实也可以不切换到所在分支，也能rebase，如下：

\$ git rebase test master //是将master分支rebase到test分支上，相当于git
checkout master; git rebase test

\$ git rebase master test

如下，有三个分支，当前在bugFix分支上，

![](media/image169.png){width="4.858333333333333in"
height="2.298611111111111in"}

\$ git rebase test master

![](media/image170.png){width="5.238888888888889in"
height="3.216666666666667in"}

在bugFix分支执行git rebase test
master命令，将master分支rebase到test分支上。

### rebase -i

**交互式rebase**，可以用来修改历史提交，如删除历史提交中的某一个提交、重排序历史提交记录、将多个历史提交合并为一个提交、拆分某个历史提交为多个提交，等等。

切换到master分支上，执行git rebase命令，结果如下：

\$ git checkout master

\$ git rebase -i HEAD\~4

此时进入vi编辑框，在vi编辑框里可以进行的操作有：删除历史提交中的某一个提交、重排序历史提交记录、将多个历史提交合并为一个提交、拆分某个历史提交为多个提交，等等。

![](media/image171.png){width="1.2534722222222223in"
height="3.6791666666666667in"}
![](media/image172.png){width="1.4555555555555555in"
height="2.9479166666666665in"}
![](media/image173.png){width="1.5444444444444445in"
height="3.6638888888888888in"}

图1 原始分支 图2 删除提交C3 图3 重排序,将提交C5放到提交C2的前面

我们可以通过下面的方法来克服困难：

先用 git rebase -i 将提交重新排序，然后把我们想要修改的提交记录挪到最前

然后用git add 、git commit \--amend 来进行一些小修改

接着再用 git rebase -i 来将他们调回原来的顺序

最后我们把 master 移到修改的最前端(用你自己喜欢的方法)，就大功告成啦！

当然完成这个任务的方法不止上面提到的一种(我知道你在看 cherry-pick
啦)，之后我们会多点关注这些技巧啦，但现在暂时只专注上面这种方法。

重排序有时候很有用，例如原来的提交顺序是C2 -\> C3 -\> C4 -\>
C5，现在我想调整C3、C4的次序，那么可以使用git rebase -i
C2(SHA)，将C3、C4的次序改变，变为C2 -\> C4 -\> C3 -\> C5。

git rebase -i的其他用法参考后续章节。

### 两个父节点

\^后面也可以加数字，但\^\<num\>表示的含义和\~\<num\>不同。

\^\<num\>并不是用来指定向上返回几代，而是**指定合并提交记录的某个父提交**。还记得前面提到过的**一个合并提交有两个父提交**吧，所以**遇到这样的节点时该选择哪条路径就不是很清晰了**。

git默认选择合并提交的"第一个"父提交，在操作符\^后跟一个数字可以改变这一默认行为。

例，

\$ git checkout master

\$ git merge bugFix

![](media/image174.png){width="1.6416666666666666in"
height="2.3506944444444446in"} 🡪
![](media/image175.png){width="1.663888888888889in"
height="2.3881944444444443in"} 或
![](media/image176.png){width="1.663888888888889in"
height="2.3805555555555555in"}

\$ git checkout master\^ 或 \$ git checkout master\^2

如果不加数字修改符直接检出master\^，则回到第一个父提交记录；如果加数字修改符，则回到第二个父提交记录。

这么操作后会处于detached状态，不处于任何分支上，其结果和git checkout
C1、git checkout C2是一样的。

问题：谁是第一个父提交？谁是第二个父提交？

使用\^和\~可以自由地在提交树中移动，非常给力：

![](media/image177.png){width="1.663888888888889in"
height="2.3881944444444443in"}

\$ git checkout HEAD\~

\$ git checkout HEAD\^\~2

\$ git checkout HEAD\~2

最终checkout到C3。

更厉害的是，这些操作符还支持链式操作，如下：

\$ git checkout HEAD\~\^2\~2

和前面的结果一样，但只用了一条命令。

### 1.远程仓库与操作

#### 远程仓库

git clone之后，本地仓库多了一个名为origin/master的分支,
这种类型的分支就叫**远程分支**。

**远程分支反映了远程仓库(在你上次和它通信时)的状态**。这会有助于你理解本地的工作与公共工作的差别\--这是你与别人分享工作成果前至关重要的一步.

**远程分支有一个特别的属性，在你检出时自动进入分离HEAD状态**。**git这么做是出于不能直接在这些分支上进行操作的原因,
你必须在别的地方完成你的工作,**
(更新了远程分支之后)再用远程分享你的工作成果。

为什么有origin/？

你可能想问这些远程分支的前面的origin/是什么意思呢？好吧,
远**程分支有一个命名规范\--它们的格式是:**

**\<remote name\>/\<branch
name\>**，因此，如果你看到一个名为origin/master的分支，那么这个分支就叫master，远程仓库的名称就是origin。

当你用git
clone某个仓库时，**git已经帮你把远程仓库的名称设置为origin了**。

**远程仓库默认为origin**。

**如果检出远程分支会怎么样呢？**

![](media/image178.png){width="0.9777777777777777in"
height="0.8506944444444444in"} 🡪
![](media/image179.png){width="1.5520833333333333in"
height="1.0743055555555556in"} 🡪
![](media/image180.png){width="1.0895833333333333in"
height="1.5298611111111111in"}

\$ git checkout origin/master \$ git commit C2

正如你所见，git变成了分离 HEAD
状态，当添加新的提交时origin/master也不会更新。这是因为origin/master
只有在远程仓库中相应的分支更新了以后才会更新。

注：图中origin/master简写为origin/master，后续origin/master简写为origin/master是同一个意思，都表示本地的远程分支。

#### fetch

git远程仓库相当的操作实际可以归纳为两点：向远程仓库传输数据以及从远程仓库获取数据。既然我们能与远程仓库同步，那么就可以分享任何能被
git管理的更新(因此可以分享代码、文件、想法、情书等等)。

本节课我们将学习如何从远程仓库获取数据\--命令如其名，它就是 git fetch。

你会看到**当我们从远程仓库获取数据时,
远程分支也会更新以反映最新的远程仓库**。

在解释git fetch前，我们先看看实例。这里我们有一个远程仓库,
它有两个我们本地仓库中没有的提交。

![](media/image181.png){width="4.261111111111111in"
height="1.9402777777777778in"}

注：图中虚线表示远程仓库

\$ git fetch

![](media/image182.png){width="4.261111111111111in"
height="1.9555555555555555in"}

就是这样了，C2,C3被下载到了本地仓库，同时**远程分支origin/master也被更新**，**反映到了这一变化。**

注：本地分支master并没有更新。

**git fetch做了些什么？**

git fetch完成了仅有的但是很重要的两步:

从远程仓库下载本地仓库中缺失的提交记录

更新远程分支指针(如origin/master)

**git
fetch实际上将本地仓库中的远程分支更新成了远程仓库相应分支最新的状态**。

如果你还记得上一节课程中我们说过的，**远程分支反映了远程仓库在你最后一次与它通信时的状态**，git
fetch就是你与远程仓库通信的方式了。

git fetch通常通过互联网(使用http://或git://协议)与远程仓库通信。

**git fetch不会做的事**

**git fetch
并不会改变你本地分支的状态**。**它不会更新你的master分支，也不会修改你磁盘上的文件。**

**有些资料描述有误，git
fetch是会改变你本地仓库的状态的，会更新本地仓库的远程分支到最新、与远程仓库的分支同步，但是git
fetch不会修改本地仓库的本地分支的状态。**

理解这一点很重要，因为许多开发人员误以为执行了 git
fetch以后，他们本地仓库就与远程仓库同步了。它可能已经将进行这一操作所需的所有数据都下载了下来，但是并没有修改你本地的文件。我们在后面的课程中将会讲解能完成该操作的命令。所以,
你**可以将git fetch的理解为单纯的下载操作**。

小结：**git
fetch**获取远程仓库的修改、**更新本地仓库的远程分支，但是并不更新本地仓库的本地分支**。

#### pull

现在我们学习如何将这些变化更新到我们的工作当中。

其实有很多方法的\--当远程分支中有新的提交时，你可以像合并本地分支那样来合并远程分支。也就是说就是你可以执行以下命令:

git cherry-pick origin/master

git rebase origin/master

git merge origin/master

实际上，由于**先抓取更新再合并到本地分支**这个流程很常用，因此git提供了一个专门的命令来完成这两个操作。它就是我们要讲的git
pull。

我们先来看看 fetch、merge 依次执行的效果

![](media/image183.png){width="4.6715277777777775in" height="1.5375in"}

\$ git fetch

![](media/image184.png){width="5.3284722222222225in"
height="1.7236111111111112in"}

\$ git merge origin/master

![](media/image185.png){width="5.358333333333333in"
height="2.067361111111111in"}

我们用 fetch 下载了C3, 然后通过 git merge origin/master
合并了这一提交记录。现在我们的 master
分支包含了远程仓库中的更新(在本例中远程仓库名为 origin)。

如果使用 git pull 呢?

\$ git pull

和fetch+merge同样的结果。这清楚地说明了 git pull 就是 git fetch 和 git
merge \<just-fetched-branch\> 的缩写。

// **git pull = git fetch + git merge**；**repo工具，repo sync = git
fetch + git rebase**。

注意，此时，远程分支origin/master指向C3，和远程仓库的分支master一样，但是本地master分支指向C4。远程分支origin/master和本地分支master并不同步，而是和远程库master分支同步。

#### push

OK，我们已经学过了如何从远程仓库获取更新并合并到本地的分支当中。这非常棒...但是我如何与大家分享我的成果呢？

嗯，上传自己分享内容与下载他人的分享刚好相反，那与 git pull
相反的命令是什么呢？git push！

**git push
负责将你的变更上传到指定的远程仓库，并在远程仓库上合并你的新提交记录。**一旦
git push 完成,
你的朋友们就可以从这个远程仓库下载你分享的成果了。你可以将 git push
想象成发布你成果的命令。

注意：git push 不带任何参数时的行为与 git的一个名为 push.default
的配置有关。它的默认值取决于你正使用的
git的版本，但是在教程中我们使用的是upstream。
这没什么太大的影响，但是在你的项目中进行推送之前，最好检查一下这个配置。

这里我们准备了一些远程仓库中没有的提交记录, 咱们开始先上传吧!

![](media/image186.png){width="4.641666666666667in"
height="1.5298611111111111in"}

\$ git push

![](media/image187.png){width="4.656944444444444in"
height="1.5520833333333333in"}

过去了, 远程仓库接收了 C2，远程仓库中的 master 分支也被更新到指向 C2
了，我们的远程分支 (origin/master) 也同样被更新了。所有的分支都同步了！

一般工作流程：建立本地跟踪分支，修改代码，pull更新远程修改到本地，push本地修改到远程。

\$ git checkout -b develop origin/master

\$ vi file1; git add file1; git commit -m "Add file1"

\$ git pull

\$ git push

#### 偏离的提交历史

远程提交历史的偏离

假设你周一克隆了一个仓库，然后开始研发某个新功能。到周五时，你新功能开发测试完毕，可以发布了。但是\--
天啊！你的同事这周写了一堆代码，还改了许多你的功能中使用的
API，这些变动会导致你新开发的功能变得不可用。但是他们已经将那些提交推送到远程仓库了，因此**你的工作就变成了基于项目旧版的代码，与远程仓库最新的代码不匹配了**。

这种情况下, git push 就不知道该如何操作了。如果你执行 git
push，git应该让远程仓库回到星期一那天的状态吗？还是直接在新代码的基础上添加你的代码，异或由于你的提交已经过时而直接忽略你的提交？

**因为这情况(历史偏离)有许多的不确定性，git是不会允许你 push
变更的。实际上它会强制你先合并远程最新的代码，然后才能分享你的工作。**

说了这么多，咱们还是看看实际案例吧！

![](media/image188.png){width="2.477777777777778in"
height="2.4402777777777778in"}

\$ git push

看见了吧？**什么都没有变，因为命令失败了**！git push
失败是因为你最新提交的C3基于远程分支中的C1。而远程仓库中该分支已经更新到C2了，所以**git拒绝了你的推送请求**。

提示：远程仓库与你的本地仓库产生了分歧，故此上传操作无法通过Fast-forward实现(因此你的push被拒绝了)。请pull下来远程仓库里最新的更改，与这个分支合并之后再试一次。你可以通过git
pull或git pull \--rebase实现。

那该如何解决这个问题呢？很简单，你需要做的就是使你的工作基于最新的远程分支。

有许多方法做到这一点呢，不过最直接的方法就是通过 rebase 调整你的工作。

\$ git fetch

\$ git rebase origin/master

\$ git push

![](media/image189.png){width="3.1868055555555554in"
height="2.4555555555555557in"}

我们**用 git fetch 更新了本地仓库中的远程分支**，然后用
rebase将我们的工作移动到最新的提交记录下，最后再用 git push
推送到远程仓库。

还有其它的方法可以在远程仓库变更了以后更新我的工作吗?
当然有，我们还可以使用 merge。

尽管 git merge 不会移动你的工作(它会创建新的合并提交)，但是它会告诉
git你已经合并了远程仓库的所有变更。这是因为远程分支现在是你本地分支的祖先，也就是说你的提交已经包含了远程分支的所有变化。

看下演示\...

咱们们用 merge 替换 rebase 来试一下......

\$ git fetch

\$ git merge origin/master

\$ git push

![](media/image190.png){width="2.522222222222222in"
height="2.7465277777777777in"}

我们用 git
fetch更新了本地仓库中的远程分支，然后合并了新变更到我们的本地分支(为了包含远程仓库的变更)，最后我们用
git push 把工作推送到远程仓库。

很好！但是要敲那么多命令，有没有更简单一点的？

当然\--前面已经介绍过 git pull 就是 fetch 和 merge 的简写，类似的git
pull \--rebase就是fetch和rebase的简写！

让我们看看简写命令是如何工作的。

\$ git pull \--rebase

\$ git push

跟之前fetch+rebase的结果一样，但是命令更短了。

换用常规的 pull：

\$ git pull

\$ git push

跟之前fetch+merge的结果一样。

#### 特性分支

合并特性分支

在大型项目中开发人员通常会**在特性分支上工作**，工作完成后只做一次集成。

但是有些开发人员**只在 master上做 push、pull** \-- 这样的话 master
总是最新的，始终与远程分支 (origin/master) 保持一致。

![](media/image191.png){width="5.776388888888889in"
height="2.9180555555555556in"}

\$ git fetch

\$ git rebase origin/master side1

\$ git rebase side1 side2

\$ git rebase side2 side3

\$ git rebase side3 master

\$ git push

![](media/image192.png){width="5.902777777777778in"
height="4.358333333333333in"}

有些开发人员只在 master 上做 push、pull \-- 这样的话 master
总是最新的，始终与远程分支 (origin/master) 保持一致。

有时在开发分支dev进行pull会导致冲突，开发过程中频繁的造成冲突烦人，因此，开发分支dev纯粹的就只做开发用，不用于同步代码，在master分支同步代码，合并开发分支dev、并且解决冲突。

**为什么不用 merge 呢?**

为了 push
新变更到远程仓库，你要做的就是包含远程仓库中最新变更。意思就是只要你的本地分支包含了远程分支(如
origin/master)中的最新变更就可以了，至于具体是用 rebase 还是
merge，并没有限制。

那么既然没有规定限制，为何前面几节都在着重于 rebase
呢？为什么在操作远程分支时不喜欢用 merge 呢？

在开发社区里，有许多关于 merge 与 rebase 的讨论。以下是关于 rebase
的优缺点：

优点: Rebase 使你的提交树变得很干净, 所有的提交都在一条线上

缺点: Rebase 修改了提交树的历史。

比如, 提交 C1 可以被 rebase 到 C3 之后。这看起来 C1 中的工作是在 C3
之后进行的，但实际上是在 C3 之前。

一些开发人员喜欢保留提交历史，因此更偏爱
merge。而其他人(比如我自己)可能更喜欢干净的提交树，于是偏爱
rebase。仁者见仁，智者见智。

![](media/image193.png){width="5.836111111111111in"
height="2.932638888888889in"}

\$ git checkout master

\$ git pull

\$ git merge side1

\$ git merge side2

\$ git merge side3

\$ gi push

![](media/image194.png){width="5.910416666666666in"
height="3.3361111111111112in"}

#### 远程跟踪分支

在前几节课程中有件事儿挺神奇的，git好像知道master与origin/master是相关的。当然这些分支的名字是相似的，可能会让你觉得是依此将远程分支
master和本地的master分支进行了关联。这种关联在以下两种情况下可以清楚地得到展示：

pull 操作时,
提交记录会被先下载到origin/master上，之后再合并到本地的master分支。隐含的合并目标由这个关联确定的。

push 操作时,
我们把工作从master推到远程仓库中的master分支(同时会更新远程分支origin/master)。这个推送的目的地也是由这种关联确定的。

**远程跟踪**

直接了当地讲，**master和origin/master的关联关系就是由分支的"remote
tracking"属性决定的**。**master被设定为跟踪origin/master \--这意味着为
master分支指定了推送的目的地以及拉取后合并的目标**。

你可能想知道 master
分支上这个属性是怎么被设定的，你并没有用任何命令指定过这个属性呀！好吧,
**当你克隆仓库的时候, git就自动帮你把这个属性设置好了**。

**当你克隆时,
git会为远程仓库中的每个分支在本地仓库中创建一个远程分支(比如origin/master)**。**然后再创建一个跟踪远程仓库中活动分支的本地分支，默认情况下这个本地分支会被命名为
master**。

**克隆完成后，你会得到一个本地分支(如果没有这个本地分支的话，你的目录就是"空白"的)**，**但是可以查看远程仓库中所有的分支**。这样做对于本地仓库和远程仓库来说，都是最佳选择。

这也解释了为什么会在克隆的时候会看到下面的输出：

local branch \"master\" set to track remote branch \"origin/master\"

**我能自己指定这个属性吗？**

当然可以，可以让任意分支跟踪origin/master,
然后该分支会像master分支一样得到隐含的push目的地以及merge的目标。这意味着你可以在分支totallyNotMaster上执行git
push，将工作推送到远程仓库的master分支上。

有两种方法设置这个属性，第一种就是**通过远程分支检出一个新的分支**，执行:

git checkout -b totallyNotMaster origin/master

就可以创建一个名为totallyNotMaster的分支，它跟踪远程分支origin/master。

另一种设置远程追踪分支的方法就是使用：**git branch -u命令**，执行：

git branch -u origin/master foo

这样foo就会跟踪origin/master了。如果当前就在foo分支上, 还可以省略foo：

git branch -u origin/master

演示，我们检出一个名叫 foo 的新分支，让其跟踪远程仓库中的 master。

![](media/image195.png){width="2.3506944444444446in"
height="2.3361111111111112in"} **🡪**
![](media/image196.png){width="2.477777777777778in" height="2.4625in"}

\$ git checkout -b foo origin/master

\$ git pull

正如你所看到的, 我们使用了隐含的目标
origin/master来更新foo分支。需要注意的是master并未被更新！

git push同样适用：

\$ git checkout -b foo origin/master

\$ git commit

\$ git push

![](media/image197.png){width="2.4027777777777777in"
height="2.372916666666667in"}

我们将一个并不叫 master 的分支上的工作推送到了远程仓库中的 master
分支上。

**使用git branch -u命令**

看看这种方式的实际的效果\...

![](media/image198.png){width="2.4923611111111112in"
height="1.4777777777777779in"} **🡪**
![](media/image199.png){width="2.4923611111111112in"
height="2.5076388888888888in"}

\$ git branch -u origin/master foo

\$ git commit

\$ git push

跟之前一样, 但这个命令更明确！

在不检出 master 分支的情况下将工作推送到的远程仓库中的 master 分支上。

#### git push 的参数

git push gitrepo LocalBranch:RemoteBranch
//将本地指定分支推送到远程指定分支

git push gitrepo RemoteBranch //推送到同名远程分支

git push gitrepo :RemoteBranch //删除远程分支

git push gitrepo \--delete RemoteBranch //删除远程分支

很好! 既然你知道了远程跟踪分支，我们可以开始揭开 git push、fetch 和 pull
的神秘面纱了。我们会逐个介绍这几个命令，它们在理念上是非常相似的。

首先来看 git push。在远程跟踪课程中，你已经学到了
git是通过当前检出分支的属性来确定远程仓库以及要 push
的目的地的。这是未指定参数时的行为，我们可以为 push 指定参数，语法是：

**git push \<remote\> \<place\>**

\<place\> 参数是什么意思呢？我们稍后会深入其中的细节, 先看看例子,
这个命令是:

git push origin master

把这个命令翻译过来就是：

切到本地仓库中的"master"分支，获取所有的提交，再到远程仓库"origin"中找到"master"分支，将远程仓库中没有的提交记录都添加上去，搞定之后告诉我。

我们通过"place"参数来告诉 git提交记录来自于master,
要推送到远程仓库中的master。它实际就是要同步的两个仓库的位置。

需要注意的是，因为我们通过指定参数告诉了git所有它需要的信息,
所以它就忽略了我们所检出的分支的属性！

我们看看指定参数的例子。注意下我们当前检出的位置。

![](media/image200.png){width="2.3506944444444446in"
height="2.3361111111111112in"} **🡪**
![](media/image201.png){width="2.9027777777777777in"
height="2.372916666666667in"}

\$ git checkout C0

\$ git push origin master

好了，通过指定参数, 远程仓库中的master分支得到了更新。

如果不指定参数会发生什么呢?

\$ git checkout C0

\$ git push

命令失败了(正如你看到的，什么也没有发生)! 因为我们所检出的 HEAD
没有跟踪任何分支。

#### \* \<place\>参数详解

还记得之前课程说的吧，当为 git push 指定 place 参数为 master
时，我们同时指定了提交记录的来源和去向。

你可能想问 \-- 如果来源和去向分支的名称不同呢？比如你想把本地的 foo
分支推送到远程仓库中的 bar 分支。

哎，很遗憾 git做不到...开个玩笑，别当真！当然是可以的啦 :)
git拥有超强的灵活性(有点过于灵活了)

接下来咱们看看是怎么做的...

要同时为源和目的地指定\<place\>的话，只需要用**冒号:**将二者连起来就可以了，

**[git push origin \<source\>:\<destination\>]{.mark}**

**[git push \<远程仓库名\> \<本地分支名\>:\<远程分支名\>]{.mark}**

这个参数实际的值是个refspec，"refspec"是一个自造的词，意思是
git能识别的位置(比如分支foo或者HEAD\~1)

一旦你指定了独立的来源和目的地，就可以组织出言简意赅的远程操作命令了，让我们看看演示！

![](media/image202.png){width="2.4256944444444444in"
height="2.3805555555555555in"} **🡪**
![](media/image203.png){width="2.4555555555555557in"
height="2.4402777777777778in"}

\$ git push origin foo\^:master

记住，source 可以是任何 git能识别的位置。

这是个另人困惑的命令，但是它确实是可以运行的\--
git将foo\^解析为一个位置，上传所有未被包含到远程仓库里 master
分支中的提交记录。

如果你要推送到的目的分支不存在会怎么样呢？没问题！git会在远程仓库中根据你提供的名称帮你创建这个分支！

\$ git push origin master:newBranch

![](media/image204.png){width="2.4479166666666665in"
height="2.4402777777777778in"} **🡪**
![](media/image205.png){width="2.6041666666666665in"
height="2.477777777777778in"}

#### git fetch的参数

我们刚学习了git
push的参数，很酷的\<place\>参数，还有**用冒号分隔的refspecs(\<source\>:\<destination\>)**。
这些参数可以用于git fetch吗？

你猜中了！git fetch的参数和git
push极其相似。他们的概念是相同的，只是**方向相反罢了**(因为现在你是下载，而非上传)

让我们逐个讨论下这些概念......

**\<place\> 参数**

如果你像如下命令这样为git fetch设置\<place\>的话：

**git fetch origin foo**

**git会到远程仓库的foo分支上，然后获取所有本地不存在的提交，放到本地的o/foo上**。

来看个例子(还是前面的例子，只是命令不同了)

![](media/image206.png){width="2.5520833333333335in" height="2.5375in"}
**🡪** ![](media/image207.png){width="2.5597222222222222in"
height="2.5597222222222222in"}

\$ git fetch origin foo

通过指定place，我们只下载了远程仓库中foo分支中的最新提交记录，并更新了o/foo。

你可能会好奇 \-- 为何
git会将新提交放到o/foo而不是放到我本地的foo分支呢？之前不是说这样的\<place\>参数就是同时应用于本地和远程的位置吗？

好吧,
本例中git做了一些特殊处理，因为你可能在foo分支上的工作还未完成，你也不想弄乱它。还记得在git
fetch课程里我们讲到的吗 \-- 它不会更新你的本地的非远程分支,
只是下载提交记录(这样, 你就可以对远程分支进行检查或者合并了)。

"**如果我们指定 \<source\>:\<destination\> 会发生什么呢？**"

如果你觉得直接更新本地分支很爽，那你就**用冒号分隔的refspec**
吧。不过，你不能在当前检出的分支上干这个事，但是其它分支是可以的。

**这里有一点是需要注意的 \--
source现在指的是远程仓库中的位置，而\<destination\>才是要放置提交的本地仓库的位置**。它与
git push 刚好相反，这是可以讲的通的，因为我们在往相反的方向传送数据。

理论上虽然行的通，但开发人员很少这么做。我在这里介绍它主要是为了从概念上说明
fetch 和 push 的相似性，只是方向相反罢了。

![](media/image208.png){width="2.529861111111111in"
height="2.522222222222222in"} **🡪**
![](media/image209.png){width="2.5743055555555556in"
height="2.5743055555555556in"}

\$ git fetch origin foo\~:bar

看见了吧,**git将
foo\~1解析成一个origin仓库的位置，然后将那些提交记录下载到了本地的bar分支(一个本地分支)上。注意由于我们指定了目标分支，foo和o/foo都没有被更新。**

如果执行命令前目标分支不存在会怎样呢？我们看一下上个对话框中没有 bar
分支的情况。

![](media/image210.png){width="2.738888888888889in"
height="2.701388888888889in"} **🡪**
![](media/image211.png){width="2.8361111111111112in"
height="2.8131944444444446in"}

看见了吧，跟 git push 一样，git会在fetch前**自己创建本地分支**, 就像是
git在 push 时，如果远程仓库中不存在目标分支，会自己在建立一样。

没有参数呢?

![](media/image212.png){width="2.238888888888889in"
height="2.783333333333333in"} **🡪**
![](media/image213.png){width="2.6638888888888888in"
height="2.8430555555555554in"}

\$ git fetch

如果git fetch没有参数，它会下载**所有的提交记录到各个远程分支**......

相当简单，但是仅需更新一次，值得你去做。

#### 没有source的source

古怪的 \<source\>

git有两种关于\<source\>的用法是比较诡异的，即你可以在git push或git
fetch时不指定任何source，方法就是仅保留冒号和destination部分，**source部分留空**。

git push origin :side

git fetch origin :bugFix

我们分别来看一下这两条命令的作用......

如果 push空\<source\>到远程仓库会如何呢？它会删除远程仓库中的分支！

\$ git push origin :foo，或者git push origin \--delete foo

![](media/image214.png){width="2.5444444444444443in"
height="1.5222222222222221in"} **🡪**
![](media/image215.png){width="2.7090277777777776in"
height="1.5145833333333334in"}

就是这样子, 我们通过给 push 传空值 source，成功删除了远程仓库中的 foo
分支, 这真有意思\...

同时，本地仓库的远程分支o/foo也删除了。

如果 fetch空\<source\>到本地，会在本地创建一个新分支。

\$ git fetch origin :bar

![](media/image216.png){width="2.6041666666666665in"
height="1.4479166666666667in"} **🡪**
![](media/image217.png){width="2.6118055555555557in"
height="1.5520833333333333in"}

#### git pull 的参数

既然你已经掌握关于git fetch和git push参数的方方面面了，关于git
pull几乎没有什么可以讲的了 :)

因为git
pull到头来就是fetch后跟merge的缩写。你可以理解为用同样的参数执行git
fetch，然后再merge你所抓取到的提交记录。

还可以和其它更复杂的参数一起使用, 来看一些例子:

以下命令在 git中是等效的:

git pull origin foo 相当于：

git fetch origin foo; git merge o/foo

还有\...

git pull origin bar\~1:bugFix 相当于：

git fetch origin bar\~1:bugFix; git merge bugFix

git pull实际上就是fetch + merge的缩写, git pull
唯一关注的是提交最终合并到哪里(也就是为git fetch所提供的 destination
参数)

一起来看个例子吧：

![](media/image218.png){width="2.6638888888888888in"
height="2.634027777777778in"} **🡪**
![](media/image219.png){width="2.9180555555555556in"
height="2.4923611111111112in"}

\$ git pull origin master

如果我们指定要抓取的 place，所有的事情都会跟之前一样发生，只是增加了
merge 操作。

通过指定master我们更新了origin/master。然后将origin/master
merge到我们的检出位置，无论我们当前检出的位置是哪。

pull也可以用source:destination吗? 当然喽, 看看吧:

![](media/image220.png){width="2.5375in" height="2.4854166666666666in"}
**🡪** ![](media/image221.png){width="2.716666666666667in"
height="2.3131944444444446in"}

\$ git pull origin master:foo

哇,
这个命令做的事情真多。它先在本地创建了一个叫foo的分支，从远程仓库中的master分支中下载提交记录，并合并到
foo，然后再merge到我们的当前检出的分支bar上。操作够多的吧？！

练习：

![](media/image222.png){width="5.052083333333333in"
height="1.8659722222222221in"}

\$ git pull origin bar:foo

![](media/image223.png){width="5.089583333333334in"
height="1.8729166666666666in"}

\$ git pull origin master:side

![](media/image224.png){width="5.604166666666667in"
height="2.4923611111111112in"}

#### \* \<place\>参数总结

place参数的完整形式：**\<source\>:\<destination\>**

**git pull/push/fetch \[库\] \[源\]:\[目\]**

**git pull/push/fetch \[库\] \[源分支\]:\[目的分支\]**

pull/push/fetch的格式是一样的:git pull/push/fetch \[库\]
\[源\]:\[目\]，但source、destination代表的意义不同，pull时source表示远程分支、destination表示本地分支，push时source表示本地分支、destination表示远程分支，fetch时source、destination的含义与pull一样。

**git pull repository \<source\>:\<destination\>** = **git pull
\<远程仓库\>
\<远程分支\>:\<本地分支\>**，source表示远程分支，destination表示本地分支

**git push repository \<source\>:\<destination\>** = **git push
\<远程仓库\>
\<本地分支\>:\<远程分支\>**，source表示本地分支，destination表示远程分支

**git fetch repository \<source\>:\<destination\>** =同git pull

**冒号左边是来源，右边是目的地**。

- git push：来源是本地，目的地是远程 → 本地:远程

- git pull：来源是远程，目的地是本地 → 远程:本地

[pull/push可以**省略destination，或者source、destination两个都省略，省略时destination分支与source分支同名**]{.mark}。push省略source表示删除远程分支。

\$ git push
//不指定分支，省略source、destination，表示将当前所在分支推送到远程同名分支

\$ git push origin branchname
//指定source分支，省略destination，表示将指定的本地分支推送到远程同名分支

\$ git push origin branchname:branchname_2
//source、destination都不省略，表示将指定的本地分支推送到指定的远程分支

\$ git push origin :branchname
//source留空、destination不留空，表示删除远程指定的分支。空，表示删除，或者明确使用\--delete参数删除远程分支

\$ git push origin \--delete branchname //指定\--delete选项删除远程分支

push时如果远程没有对应的分支名，那么会在远程仓库建立对应的分支；如果source留空，那么会删除对应的远程分支。

**常用用法**

  -------------------------------------------------
  命令         说明
  ------------ ------------------------------------
  git pull     拉取当前分支的上游分支，并自动合并

  git pull     从 origin 的 main
  origin main  分支拉取并合并到当前分支

  git pull     使用 rebase 代替
  \--rebase    merge，保持提交历史更整洁

  git pull     仅允许快进合并，否则拒绝合并
  \--ff-only   

  git pull     拉取 origin 的 dev 分支并合并到本地
  origin       dev 分支
  dev:dev      
  -------------------------------------------------

**常用选项**

- \--rebase：用 rebase 代替 merge，避免产生多余的 merge commit。

- \--ff-only：只允许快进合并，如果有冲突则中止操作。

- \--no-commit：拉取后不自动提交，方便检查合并结果。

- \--verbose / -v：显示详细输出。

  ------------------------------------------------------------------
  命令                  说明
  --------------------- --------------------------------------------
  git push              推送当前分支到已设置的上游分支

  git push origin main  推送本地 main 到 origin/main

  git push -u origin    推送并设置上游跟踪分支，之后可直接 git push
  feature               

  git push origin       把本地分支推送到不同名的远程分支
  local:remote          

  git push \--tags      推送所有本地标签

  git push origin       删除远程分支
  :old-branch           

  git push \--force     强制推送，可能覆盖远程历史，慎用

  git push              更安全的强制推送，远程有他人新提交时会拒绝
  \--force-with-lease   

  git push \--dry-run   预览推送结果，不实际执行

  git push \--all       推送所有本地分支
  ------------------------------------------------------------------

  ------------------------------------------------------------
  命令              说明
  ----------------- ------------------------------------------
  git fetch         从默认远程仓库获取更新

  git fetch origin  从 origin 获取所有分支更新

  git fetch origin  只获取 origin 的 main 分支更新
  main              

  git fetch \--all  获取所有远程仓库的更新

  git fetch \--tags 同时获取所有标签

  git fetch         删除远程已不存在的分支对应的本地跟踪引用
  \--prune          

  git fetch         预览会获取哪些更新，但不实际下载
  \--dry-run        

  git fetch origin  把远程 feature 分支更新到本地 feature 分支
  feature:feature   
  ------------------------------------------------------------

# 6)git图形工具 

### 常用git图形工具

[图形化工具：**gitg、gitk、git
gui**。其他：**TortoisegitSmartgit、**SourceTree、gitKraken。]{.mark}

gitg、gitk用于查看提交和分支，git gui用于查看本地文件修改。

gitg显示多个库、全部分支，显示信息全面详细，推荐。

windows
cmder带了git、gitk、git-gui等工具。RabbitVCS同时支持git/svn/hg但不好用。

### gitg用法

**[gitg \[options\] \[repository\] \[\<refspec\>\]]{.mark}**

快捷键

ctrl+f，搜索

\$ gitg，启动gitg图形界面

\$ gitg \--help

用法：

gitg \[OPTION...\] \-- Git repository viewer

帮助选项：

-h, \--help 显示帮助选项

\--help-all 显示全部帮助选项

\--help-gtk 显示 GTK+ 选项

应用程序选项：

-v, \--version Show the application's version

\--activity 以特定活动启动 gitg

-c, \--commit 以提交活动启动 gitg (是 \--activity commit 的简写)

\--no-wd 不尝试从当前工作目录加载仓库

\--standalone Run gitg in standalone mode

-a, \--all Select all commits by default in the history activity

-b, \--branches Select all branches by default in the history activity

-r, \--remotes Select all remotes by default in the history activity

-t, \--tags Select all tags by default in the history activity

-s, \--select-reference=REFERENCE Select the specified reference by
default in the history activity

\$ gitg -c，以提交活动启动gitg，弹出框可以看到当前修改

![](media/image225.png){width="4.460416666666666in"
height="1.5520833333333333in"}

不一定要在git库所在目录执行gitg，可以在gitg后面指定git库所在目录。

例如当前在/cygdrive/d/code/目录，git库在/cygdrive/d/code/github/daily_use目录，可以使用如下命令来启动gitg，

\$ gitg github/daily_use

cygwin只能使用相对路径，使用绝对路径不行。

gitk、gitg对比：

gitk**稳定**，显示结果简单，默认显示当前分支、当前库，gitk
\--all显示当前库的全部分支？不能显示多个库？

gitg**显示内容多**，显示**全部库和全部分支**，**直观**，方便对项目整体进行把握。但windows下cygwin使用gitg不稳定，有时候卡顿/异常退出，命令行打印出很多log让人烦。

![](media/image226.png){width="6.7868055555555555in"
height="3.5256944444444445in"}

**gitg显示了本地仓库及其全部分支、远程仓库及其全部分支。**

仓库与分支的解释，见：15)git仓库与分支 -\> 关联多个远程仓库。

**cygwin使用gitg**

通过cygwin
setup.exe安装的gitg有问题，只能看到提交记录，看不到提交修改内容。

下载gitg.exe安装，解决。

下载gitg-x86_64-3.32.1.exe，安装到d:\\software\\gitg\\目录，找到d:\\software\\gitg\\bin\\gitg.exe。

cygwin设置别名：alias
gitg=\'/cygdrive/d/software/gitg/bin/gitg\'，添加到\~/.bashrc中，之后就可以在cygwin使用gitg了。

使用ln /cygdrive/d/software/gitg/bin/gitg
/usr/bin/gitg，执行gitg报错：dll文件找不到，只能采用设置别名的方式。

附：

windows版gitg下载：https://www.softpedia.com/get/Programming/Other-Programming-Files/gitg.shtml

Linux版gitg下载：https://pkgs.org/download/gitg

### gitk用法

[**git log \[\<options\>\] \[\<revision range\>\]** \[**\[\--\]
\[\<path\>...​\]\]**]{.mark}

**[gitk \[\<options\>\] \[\<revision range\>\] \[\--\]
\[\<path\>...​\]]{.mark}**

**gitk用法和git log很多是一样的，可以指定路径、选项、范围。**

\$ git log 查看分支修改记录，显示commit日志。git
log显示结果：新的先显示、旧的后显示，显示在前面的是新的提交、显示在后面的是旧的提交。

\$ **git log path**
//path可以是文件路径，也可以是目录路径。绝对路径、相对路径都可以。

\$ git log ../dir/test.c //文件

\$ git log ../dir //目录

\$ git log -4查看分支最近4次修改记录

**[这些用法同样适用于gitk：]{.mark}**

\$ gitk //显示**当前分支**的提交历史记录

\$ gitk \--all //显示**全部分支**的提交历史记录

\$ gitk path

\$ gitk ../dir/test.c

\$ gitk ../dir

\$ gitk -4 //和git log -4不同，git log -4只显示4条记录，但是gitk
-4显示了5条记录

\$ gitk SHA //和git show SHA一样

\$ gitk -L\<start\>,\<end\>:\<file\>, -L:\<funcname\>:\<file\> //和git
log -L用法完全一样

[快捷键：]{.mark}

[空格、f：向下翻页]{.mark}

[b：向上翻页]{.mark}

[/：搜索，光标定位到搜索框 \-- 这些和vi是一样的]{.mark}

[ctrl+q退出gitk]{.mark}

[gitk搜索功能，从第一个结果反向搜索跳到最后一个搜索结果，从最后一个搜索结果反向搜索跳到第一个搜索结果。]{.mark}

File -\> Start git
gui，打开gui窗口，显示当前鼠标所在的提交或者修改的详细情况。

![](media/image227.png){width="1.3138888888888889in"
height="1.6736111111111112in"}

File -\> List references或F2，弹出窗口，可以看到不同分支、stash、标签等

![](media/image228.png){width="1.520138888888889in"
height="2.923611111111111in"}

**gitk用法**

参考：<https://git-scm.com/docs/gitk>

gitk是一个强悍的git图形化工具。它可不仅仅是命令行的一个替代产品，实际上它能实现很多命令行并不能提供的git功能。所以不要认为它和命令行是git操作的两种实现工具。

**1.颜色和字体**

●本地分支名称是绿色背景

●远程分支名称是橘色和绿色混合的背景色

●当前分支是加粗字体

●分支tag是黄色背景

●当前HEAD是黄色的圆点

●黄色的方块代表提交有notes(git备注是用于给提交补充消息的，但是不会改变提交信息，参考[[git-notes]{.underline}](https://git-scm.com/docs/git-notes "git-notes"))

**2.代码库操作**

这些操作都作用在提交列表上。

●右键单击提交信息

●创建tag

●创建分支

●重置当前分支到这个提交(soft/mixed/hard)

●挑选(cherry-pick)当前提交给当前分支(这个命令也不常用，我百度了一下[[关于git的cherry-pick命令]{.underline}](https://www.cnblogs.com/DreamDrive/p/4157421.html "关于git的cherry-pick命令"))

●右键单击分支名称

●检出分支

●删除分支

**3.主菜单**

●reload:
如果你在其他界面使用命令行操作了一些东西，想通过gitk刷新出来看，可以点一下F5。

F5会更新分支信息把新的值显示出来，**并且会同时显示原来的值**。这在rebase之类的操作后相当有用，因为你可以比较一下原来和现在的分支

如果使用ctrl+F5,也就是完全刷新，就不会显示变更之前的值了

●list/choose references：
要快速到指定分支，点击F2。显示出来的结果可能很多，可以通过下面的过滤框写一下模式。它不会模糊匹配，你要么写完分支名称，要么使用通配符\*。
点选一个分支整个gitk就去到新分支了，不过弹出来的窗口还在，可以继续点其他分支。

**4.浏览提交列表**

许多操作都有快捷键绑定。 比如下键可以使用n代替。不过知道了也没啥用。

●上下键，还有pageup/pagedown键，作用显而易见；

●左右键，上一个/下一个提交；

●shift+上下键，查下上一个/下一个匹配 (在第6部分讲)

**5.浏览diff信息**

下面的面板左边部分是diff信息，右面部分是diff的文件列表。

●空格键：向前一页

●退格键/删除键: 同上，不过反向

●f：下一个文件，左右两边都会移动

●b：同上，不过是前一个文件

●点击右侧文件：左侧会滚动到对应的diff

计算提交的差别

●左键选中一个提交

●找到另一个提交(可以使用滚动条，但不能使用键盘)

●右键单击选择Diff this -\> selected

现在可以和上面一样对比差别了。

**6.查找提交**

●搜索提交信息：任何时候点击\"/\"都可以开始搜索提交信息。匹配的提交会被加粗，中文尤其明显。前面说过，可以使用shift+上下键进行导航。

●根据文件搜索：匹配到提交以后，在右下面板右击文件选择Highlight this
only。

如果想匹配多个文件，可以右击其他文件，选择Highlight this
too，这些文件不用是同一个提交里的。

**注意这时候搜索模式就从**containing**变成了**touching paths

●根据代码搜索：把搜索模式改成adding/removing string即可。

**7.导航提交**

●diff面板显示提交的Parent和Child。点击对应的hash码可转过去

●diff面板显示了当前提交所属的分支信息。点击跳转到对应分支的head。

●如果提交图太复杂，连接两个提交的线就会断开。点击线部分(不是圆点或者箭头部分)，diff面板会显示这一部分对应的详情。

●如果点击了箭头，你会看到箭头翻转了，当前提交没有变。实际上箭头连接的是两部分提交。

### sourcegit --推荐

sourcegit，界面不错，而且开源。推荐。

# 第二部分 进阶

# 7)git使用经验

1.强调"**基**"的概念。

**C0** 🡨 **C1** 🡨 **C2** 🡨 **C5** 🡨 **C6** 🡨... master，
//箭头表示后面的"**基于**"前面的，如C1基于C0。

🡬 **C3** 🡨 **C4** 🡨 **C9** 🡨 **C10** 🡨... develop，

🡬 **C7** 🡨 **C8** 🡨... bugfix，

git分支由一个一个提交组成，后一次提交建立在前一次提交的基础之上，前一次提交是后一次提交的**基**，父提交。

git提交历史体现出前后依赖关系，后一次提交**基于**前一次提交；

git
branch是以当前HEAD指针为基础建立分支的，两个分支有共同的"基"，如分支master、分支develop有共同的基C1。，两个分支从其公共基开始产生了差异；

git rebase、git merge合并是在两个分支公共的"基"的基础上进行的。

2.开发过程中的注意事项

在git中，只要是commit提交过的代码，都是能找回来的，不管是reset/revert，还是删除未合并的分支，都能找回来，所以，记得[在进行rebase/merge/fetch/pull之前记得commit]{.mark}。因为rebase/merge/fetch/pull过程中可能冲突严重，如果冲突比较多需要reset
\--hard，会造成修改没有保存而丢失。

时候记得commit，commit \--amend。

阶段性修改记得commit，喝水吃饭上厕所等暂时离开座位的情况记得commit
\--amend。反正git这些操作代价不高，可以经常频繁使用。

3.git分支切换的时候可以使用\"-\"在两个分支之间来回切换，就像linux
cd命令一样。

\$ git checkout master

\$ git checkout develop

\$ git checkout - //切换到master分支

\$ git checkout - //切换到develop分支

4.对word文档不能做rebase -i操作失败。

在rebase -i的过程中会修改跟踪文件的内容？应该是。

在rebase -i的过程中git不能修改word文档内容，导致rebase -i失败？

word文档只能由office/wps等专门软件修改，其他由专门软件编辑的文件类型也一样。

git只能修改纯文本，可以做rebase -i操作。

# 8)常用命令

## git命令摘要

一、增加/删除/修改文件

\$ git diff //查看变更内容

\$ git add \[file1\] \[file2\] ... //添加指定文件到暂存区

\$ git add \[dir\] //添加指定目录到暂存区，包括子目录

\$ git add . //添加当前目录下的所有文件到暂存区

\$ git add -p
//添加每个变化前，都会要求确认。对于同一个文件的多处变化，可以实现分次提交

\$ git rm \[file1\] \[file2\] ...
//删除工作区文件，并且将这次删除放入暂存区。//注:是将删除这个操作放入暂存区，不是将删除的文件放入暂存区。

\$ git rm \--cached \[file\] //停止追踪指定文件，但该文件会保留在工作区

\$ git mv \[file-original\] \[file-destination\]
//移动文件/文件改名，并且将这个改名放入暂存区

二、代码提交

\$ git commit \[file1\] \[file2\] ... -m \[message\]
//提交暂存区的指定文件到仓库区

\$ git commit -m \[message\] //提交暂存区到仓库区

\$ git commit -a //提交工作区自上次commit之后的变化，直接到仓库区

\$ git commit -am \"message\" //相当于git add和git commit -m
\"message\"。

\$ git commit -v //提交时显示所有diff信息

\$ git commit \--amend -m \[message\]
//使用一次新的commit，替代上一次提交。如果代码没有任何新变化，则用来改写上一次commit的提交信息。

\$ git commit \--amend \[file1\] \[file2\]
//重做上一次commit，并包括指定文件的新变化

\$ git commit -m \"提交信息\" \--author \"Authorname
\<authoremail@mydomain.com\>\"
//指定提交的作者。单独为某个提交指定提交作者，不使用git
config配置的默认值。

提交的作者，和真实的提交者，可以不是同一个人。例如，执行git commit/ git
push操作的是A，但是使用git commit时指定\--author为B，这样在git
log里看到的是作者B，而不是提交者A。

我提交(commit)里的用户名和邮箱不对，如果这只是单个提交(commit)，修改它：

\$ git commit \--amend \--author \"New Authorname
\<authoremail@mydomain.com\>\"

三、分支

\$ git branch //显示所有本地分支

\$ git branch -r //列出所有远程分支

\$ git branch -a //列出所有本地分支和远程分支

\$ git checkout - //切换到上一个分支

\$ git branch \[branch-name\]
//新建一个分支，但依然停留在当前分支，新分支是当前分支的拷贝。

\$ git branch \--track \[branch\] \[remote-branch\]
//新建一个分支，与指定的远程分支建立追踪关系

\$ git branch -d \[branch-name\]
//删除分支。-d选项只能删除已经参与了合并的分支，对于未有合并的分支是无法删除的。如果想强制删除一个分支，可以使用-D选项。

\$ git checkout -b \[branch-name\] //新建一个分支，并切换到该分支

\$ git checkout \[branch-name\] //切换到指定分支，并更新工作区

\$ git checkout - //切换到上一个分支。\"-\"连字符代替分支名，和linux cd
-命令一样，\"-\"表示操作历史中的上一个。

\$ git merge \[branch\] //合并指定分支到当前分支

\$ git rebase \<branch\> //衍合指定分支到当前分支

\$ git cherry-pick \[commit\] //选择一个commit，合并进当前分支

\*创建空的分支：(执行命令之前记得先提交你当前分支的修改，否则会被强制删干净没得后悔)

\$git symbolic-ref HEAD refs/heads/\[name\]

\$rm .git/index

\$git clean -fdx

四、git仓库

\$ git fetch \[remote\] //下载远程仓库的所有变动

\$ git pull \[remote\] \[branch\] //取回远程仓库的变化，并与本地分支合并

\$ git push \[remote\] \[branch\] //上传本地指定分支到远程仓库

\$ git push \[remote\] \--force //强行推送当前分支到远程仓库，即使有冲突

\$ git push \[remote\] \--all //推送所有分支到远程仓库

\$ git push \[remote\] :\[branch/tag\] //删除远程分支或标签，或者

\$ git push origin \--delete branch/tag //删除远程分支或标签

\$ git push \--tags //？

如果想把本地的某个分支test提交到远程仓库，并作为远程仓库的master分支，或者作为另外一个名叫test的分支，如下：

\$git push origin test:master //提交本地test分支作为远程的master分支

\$git push origin test:test //提交本地test分支作为远程的test分支

\$ git push origin :\[name\] //删除远程分支。注意\":\"前面有空格

\$ git push origin \--delete \[name\] //删除远程分支

\$ git push origin :heads/\[name\] //删除远程分支。注意\":\"前面有空格

\$ git remote set-url \--push \[name\] \[newUrl\] //修改远程仓库

\$ git branch \--set-upstream \[branch\] \[remote-branch\]
//建立追踪关系，在现有分支与指定的远程分支之间

五、标签

参考git tag

六、查看信息

\$ git status //显示有变更的文件

\$ git log //显示当前分支的版本历史

\$ **git log \--graph**
//显示ASCII图形表示的提交历史和分支合并历史.。**推荐**。

\$ git log -p
filename //显示指定文件相关的每一次diff，查看某个文件filename修改的具体内容

\$ git log \--author=\"username\" //显示某个用户的所有提交

\$ git show SHA \--name-only \[commit\] //显示某次提交发生变化的文件

\$ git show SHA \--name-status \[commit\]
//显示某次提交发生变化的文件，并显示变更标记

\$ git log \--pretty=oneline

\$ git log \--oneline //显示更简短的SHA值,等效\$ git log
\--abbrev-commit \--pretty=oneline

\$ git log \--stat //显示commit历史，以及每次commit发生变更的文件

\$ git log -S \[keyword\] //搜索提交历史，根据关键词

\$ git log \[tag\] HEAD //git log SHA，显示某个commit之后的所有变动

\$ git log \[tag\] HEAD \--grep feature
//显示某个commit之后的所有变动，其"提交说明"必须符合搜索条件

\$ git log \--follow \[file\] //显示某个文件的版本历史，包括文件改名

\$ git whatchanged \[file\]
//显示某个文件的版本历史，包括文件改名、文件模式、其他

\$ git log -4//查看分支最近4次修改记录

\$ git log
-p//查看修改的具体内容，不仅显示commit日志，而且同时显示每次commit的代码改变。

\$ git log -2 -p//查看最近2次修改的具体内容。注意这里参数顺序-2
-p，不能把-p放到-2之前。

\$ git log -5 \--pretty=oneline //显示过去5次提交

\$ git log \--before=\"1 days\" //显示之前1天的版本

\$ git shortlog -sn //显示所有提交过的用户，按提交次数排序

\$ git blame \[file\] //显示指定文件是什么人在什么时间修改过

\$ git diff //显示暂存区和工作区的差异

\$ git diff \--cached \[file\] //显示暂存区和上一个commit的差异

\$ git diff HEAD //显示工作区与当前分支最新commit之间的差异

\$ git diff \[first-branch\] ...\[second-branch\]
//显示两次提交之间的差异(两个分支的两次提交)

\$ git diff \--shortstat \"@{0 day ago}\" //显示今天你写了多少行代码

\$ git show \[commit\] //显示某次提交的元数据和内容变化

\$ git show \[commit\] \[filename\] //显示某次提交时，某个文件的内容

\$ git reflog //查看当前仓库的操作日志。

\$ git grep \"Hello\" //从当前目录的所有文件中查找文本内容

\$ git grep \"Hello\" v2.5 //在某一版本中搜索文本

七、撤销

\$ git reset \--hard HEAD //撤销工作目录中所有未提交文件的修改内容

\$ git checkout HEAD \<file\> //撤销指定的未提交文件的修改内容

\$ git revert \<commit\> //撤销指定的提交

\$ git checkout \[file\] //恢复暂存区的指定文件到工作区

\$ git checkout \[commit\] \[file\]
//恢复某个commit的指定文件到暂存区和工作区

\$ git checkout **.** //恢复暂存区的所有文件到工作区

\$ git reset \[file\]
//重置暂存区的指定文件，与上一次commit保持一致，但工作区不变

\$ git reset \--hard //重置暂存区与工作区，与上一次commit保持一致

\$ git reset \[commit\]
//重置当前分支的指针为指定commit，同时重置暂存区，但工作区不变

\$ git reset \--hard \[commit\]
//重置当前分支的HEAD为指定commit，同时重置暂存区和工作区，与指定commit一致

\$ git reset \--keep \[commit\]
//重置当前HEAD为指定commit，但保持暂存区和工作区不变

\$ git revert \[commit\]
//新建一个commit，用来撤销指定commit。后者的所有变化都将被前者抵消，并且应用到当前分支

git checkout **.** //恢复暂存区的所有文件到工作区

git reset \--hard HEAD //撤销工作目录中所有未提交文件的修改内容

在没有新增文件的时候，两者的结果是一样的；当有新增文件时，前者只删除已跟踪文件的修改，后者可以不仅能删除已跟踪文件的修改、还能删除未跟踪文件(新增文件)。

八、其他

\$ gitarchive //生成一个可供发布的压缩包

## git命令帮助

\$ **git help git** //关于git本身的帮助

\$ **git log -h** //显示简要使用方法。显示的应该是git log
\--help的SYNOPSIS部分的内容。

\$ **git help log** //显示详细使用方法，多页显示时按q退出。

\$ **git log \--help** //显示详细使用方法，和git help log结果一样

...

cgywin下git帮助文档在D:\\cygwin64\\usr\\share\\doc\\git\\html目录。

**[记住随时查看命令帮助。]{.mark}**

\$ git -C github/daily_use/ status

git -C path cmd，和make -C path一样，不需要切换到path就可以执行git命令。

存在多个git库的时候这么操作挺方便，类似于repo的功能。

## git配置

git config \--list //查看当前git配置，包含了仓库级、用户级、系统级

git config \--global \--list //查看全局git配置

git config \[\--global\] user.name \"name\"
//设置提交代码时的用户信息，用户名

git config \[\--global\] user.email \"email\"
//设置提交代码时的用户信息，邮箱

[git config \[\--global\] \--unset user.name //取消设置]{.mark}

git config \[\--global\] \--edit //打开编辑器修改配置文件

修改配置的两种方法：git config aaa xxx，或git config \--edit修改配置文件

git配置分三种：**仓库级别**\--local、**全局级别**\--global 配置、**系统级别**\--system。

git config aaa
xxx，仓库级别配置保存在当前git库目录：**.**git/config。默认是\--local的，git
config \[\--local\] aaa xxx，\--local可省略。

git config \--global aaa
xxx，全局配置保存在用户目录：\~/**.**gitconfig。

git config \--system aaa
xxx，系统级别配置保存在系统目录：/etc/gitconfig。

git config \--edit
\[\--locol/\--global/\--system\]编辑的就是上面的.git/config、.git
config、/etc/gitconfig文件。

git config \--list的结果是git config \--local、git config \--global、git
config \--system三者加在一起的结果。

git config \--list \--show-origin

git默认编辑器是vim，可以改成其他编辑器

git config \--global core.editor emacs

设置缩写(别名)

git config \--global alias.co checkout

git config \--global alias.br branch

git config \--global alias.lg \'log \--color \--graph
\--pretty=format:\"%h, %Cgreen%s, %Creset%ae, %cd\"
\--date=format:\"%x-%X\"\' //见：10)历史记录查看-\> git log

git config \--global \--unset alias.lg取消别名

这些alias别名也可以写到.gitconfig文件，例如一个.gitconfig文件内容如下：

\# This is the config file, and a \'#\' or \';\' character indicates a
comment

; core variables

\[user\]

name = dukang

email = someone@126.com

; core variables

\[core\]

excludesfile = /users/dukang/.gitignore_global

\[alias\]

co = checkout

br = branch

ls = log \--pretty=format:\"%h, %s, %ae, %cd\" \--date=format:\"%x-%X\"

1\. core.autocrlf

core.autocrlf

If you're programming on Windows and working with people who are not (or
vice-versa), you'll probably run into line-ending issues at some point.
This is because [Windows uses both a carriage-return character and a
linefeed character for newlines]{.mark} in its files, whereas [Mac and
Linux systems use only the linefeed character]{.mark}. This is a subtle
but incredibly annoying fact of cross-platform work; many editors on
Windows silently replace existing LF-style line endings with CRLF, or
insert both line-ending characters when the user hits the enter key.

Git can handle this by auto-converting CRLF line endings into LF when
you add a file to the index, and vice versa when it checks out code onto
your filesystem. You can turn on this functionality with the
core.autocrlf setting. [If you're on a Windows machine, set it to
true --- this converts LF endings into CRLF when you check out
code:]{.mark}

[\$ git config \--global core.autocrlf true]{.mark}

[If you're on a Linux or Mac system that uses LF line endings, then you
don't want Git to automatically convert them when you check out
files]{.mark}; however, if a file with CRLF endings [accidentally gets
introduced]{.mark}, then you may want Git to fix it. You can tell Git to
convert CRLF to LF on commit but not the other way around by setting
core.autocrlf to input:

[\$ git config \--global core.autocrlf input]{.mark}

This setup should leave you with CRLF endings in Windows checkouts, but
LF endings on Mac and Linux systems and in the repository.

If you're a [Windows programmer doing a Windows-only project, then you
can turn off this functionality]{.mark}, recording the carriage returns
in the repository by setting the config value to false:

[\$ git config \--global core.autocrlf false]{.mark}

2\. core.fscache

core.fscache 配置项用于启用Git的文件系统缓存（File System
Cache），这可以显著提高性能，尤其是在处理大型文件仓库时。文件系统缓存可以减少磁盘I/O操作，因为它允许Git在内存中缓存文件状态。

配置选项：

true：启用文件系统缓存。

false：禁用文件系统缓存。

设置方法：

git config \--global core.fscache true

这将对所有仓库生效，同样，你也可以在单个仓库中设置：

git config core.fscache true

如果你在Windows环境下工作，并且希望自动处理行结束符，同时想要提高Git操作的速度，可以设置：

git config \--global core.autocrlf true

git config \--global core.fscache true

这样，你的Git配置就会同时处理行结束符转换和性能优化。如果你不需要自动转换行结束符或者在不同的操作系统上工作，可以选择不同的配置选项。

在Git中使用diff.astextplain.textconv和filter.lfs配置是为了处理特定类型的文件，例如二进制文件或大型文件（如图片、视频、大型数据文件等）。下面我将详细解释每个配置项的含义以及如何正确设置它们。

1\. diff.astextplain.textconv

diff.astextplain.textconv用于定义一个文本转换器，它可以将二进制文件或不适合直接比较的格式转换为文本格式，以便在Git中显示差异。这对于处理如PDF、Word文档等二进制文件特别有用。例如，如果你有一个PDF文件，你可以使用pdftotext工具来转换PDF文件为文本格式，以便查看差异。

‌设置示例：‌

\[diff \"astextplain\"\]

textconv = pdftotext -layout -nopgbrk

这里，pdftotext -layout -nopgbrk命令用于将PDF文件转换为文本格式。

2\. filter.lfs

Git Large File Storage (LFS)
是一个扩展，用于处理大文件而不必把它们完全存储在Git仓库中。这对于版本控制大文件（如视频、音频、大型数据集等）非常有用，因为它只存储文件的引用（指针），而实际文件存储在LFS服务器上。

‌设置示例：‌

\[filter \"lfs\"\]

clean = git-lfs clean \-- %f

smudge = git-lfs smudge \-- %f

process = git-lfs filter-process

required = true

这里：

clean：推送前处理文件。

smudge：检出时处理文件。

process：在推送或拉取时处理文件。

required：设置为true表示所有LFS管理的文件都必须通过LFS处理。

3\. http.sslbackend=schannel

这个配置项用于指定Git使用的SSL后端。schannel是Windows系统上的一个选项，用于处理HTTPS连接。如果你的系统是基于Windows，并且遇到SSL相关的问题，可以尝试设置这个选项。

‌设置示例：‌

\[http\]

sslbackend = schannel

总结配置步骤：

‌安装Git LFS‌（如果尚未安装）：

git lfs install

‌配置文本转换器‌（例如，处理PDF文件）：

git config \--global diff.astextplain.textconv \"pdftotext -layout
-nopgbrk\"

‌配置Git LFS‌：

git config filter.lfs.clean \"git-lfs clean \-- %f\"

git config filter.lfs.smudge \"git-lfs smudge \-- %f\"

git config filter.lfs.process \"git-lfs filter-process\"

git config filter.lfs.required true

‌配置SSL后端‌（如果需要）：

git config \--global http.sslbackend schannel

通过这些步骤，你可以有效地处理Git中的大文件和特定格式的文件，同时确保HTTPS连接的安全性和效率。

\$ git config -h

用法：git config \[\<选项\>\]

配置文件位置

\--global 使用全局配置文件

\--system 使用系统级配置文件

\--local 使用仓库级配置文件

\--worktree 使用工作区级别的配置文件

-f, \--file \<文件\> 使用指定的配置文件

\--blob \<数据对象 ID\> 从给定的数据对象读取配置

操作

\--get 获取值：名称 \[值模式\]

\--get-all 获得所有的值：键 \[值模式\]

\--get-regexp 根据正则表达式获得值：名称正则 \[值模式\]

\--get-urlmatch 获得 URL 取值：section\[.var\] URL

\--replace-all 替换所有匹配的变量：名称 值 \[值模式\]

\--add 添加一个新的变量：名称 值

\--unset 删除一个变量：名称 \[值模式\]

\--unset-all 删除所有匹配项：名称 \[值模式\]

\--rename-section 重命名小节：old-name new-name

\--remove-section 删除一个小节：name

-l, \--list 列出所有

\--fixed-value 在比较值与 \'值模式\' 时，使用字符串字面比较

-e, \--edit 打开一个编辑器

\--get-color 获得配置的颜色：配置 \[默认\]

\--get-colorbool 获得颜色设置：配置 \[stdout-is-tty\]

类型

-t, \--type \<类型\> 取值为该类型

\--bool 值是 \"true\" 或 \"false\"

\--int 值是十进制数

\--bool-or-int 值是 \--bool 或 \--int

\--bool-or-str 值是 \--bool 或字符串

\--path 值是一个路径(文件或目录名)

\--expiry-date 值是一个到期日期

其它

-z, \--null 终止值是 NUL 字节

\--name-only 只显示变量名

\--includes 查询时参照 include 指令递归查找

\--show-origin 显示配置的来源(文件、标准输入、数据对象，或命令行)

\--show-scope 显示配置的作用域(工作区、本地、全局、系统、命令)

\--default \<取值\> 使用 \--get 参数，当缺少设置时使用默认值

## git init

新建代码库

\$ git init
//初始化一个本地git库。[生成一个.git目录，git提交/分支/tree对象/blob对象等信息都保存在这个目录下。]{.mark}

\$ git init \<directory\> //将指定目录初始化为本地git库

\$ git init \--bare \[project-name\]
//新建一个目录，将其初始化为远程git库

\$ git clone \[url\] //下载一个项目和它的整个代码历史

更详细用法参考：15)git服务器搭建 -\> 小结

**git init**

git init turns any directory into a Git repository.

**What Does git init Do?**

git init is one way to start a new project with Git. To start a
repository, use either git init or git clone -- not both.

To initialize a repository, Git creates a hidden directory called .git.
That directory stores all of the objects and refs that Git uses and
creates as a part of your project\'s history. This hidden .git directory
is what separates a regular directory from a Git repository.

**How to Use git init**

**Common usages and options for git init**

- git init: Transform the current directory into a Git repository

- git init \<directory\>: Transform a directory in the current path into
  a Git repository

- git init \--bare: Create a new bare repository (a repository to [be
  used as a remote repository only]{.mark}, that won\'t contain active
  development)

**Examples of git init**

**git init vs git clone**

Starting a new project can be confusing. Sometimes, it\'s unclear if you
should use git init, git clone, or both.

- **[git init: One Person Starting a New Repository Locally]{.mark}**

Your project may already exist locally, but it doesn\'t have Git
yet. git init is probably the right choice for you. This is only run
once, even if other collaborators share the project.

- First, initialize the repository.

- Once you have initialized the repository, create a remote repository
  somewhere like GitHub.com.

- Then, add the remote URL to your local git repository with git remote
  add origin \<URL\>. This stores the remote URL under a more
  human-friendly name, origin.

<!-- -->

- Shape your history into at least one commit by using git add to stage
  the existing files, and git commit to make the snapshot.

- Once you have at least one commit, you can push to the remote and set
  up the tracking relationship for good with git push -u origin main.

- **[git clone: The Remote Already Exists]{.mark}**

If the repository already exists on a remote, you would choose to git
clone and *not* git init.

If you create a remote repository first with the intent of moving your
project to it later, you may have a few other steps to follow. If there
are no commits in the remote repository, you can follow the steps above
for git init. If there are commits and files in the remote repository
but you would still like it to contain your project files, git
clone that repository. Then, move the project\'s files into that cloned
repository. git add, git commit, and git push to create a history that
makes sense for the beginning of your project. Then, your team can
interact with the repository without git init again.

**git init Existing Folder**

The default behavior of git init is to transform the current directory
into a Git repository. For an existing project to become a Git
repository, navigate into the targeted root directory. Then, run git
init.

Or, you can create a new repository in a directory in your current path.
Use git init \<directory\> and specify which directory to turn into a
Git repository.

来源：https://github.com/git-guides

## git add

\$ git add file //添加到暂存区

git add \--all和git add .的区别

git add
.将当前目录及其子目录的修改添加到暂存区，但是在该目录以外的就不归他管了；而git
add \--all是将整个项目中的修改添加到暂存区。\--适于git2.x版本。

git add \--all = git add -A

git Version 1.x:

  --------------------------------------------------------------------------------
  命令   新文件   修改的文件   删除的文件   描述
  ------ -------- ------------ ------------ --------------------------------------
  git    √        √            √            暂存所有(新的，修改的，已删除的)文件
  add -A                                    

  git    √        √            ×            仅暂存新文件和修改过的文件
  add .                                     

  git    ×        √            √            仅修改和删除文件
  add -u                                    
  --------------------------------------------------------------------------------

git Version 2.x:

  ---------------------------------------------------------------------------------------------
  命令                新文件   修改的文件   删除的文件   描述
  ------------------- -------- ------------ ------------ --------------------------------------
  git add -A          √        √            √            暂存所有(新的，修改的，已删除的)文件

  git add .           √        √            √            暂存所有(新的，修改的，已删除的)文件

  git add -u          ×        √            √            仅修改和删除文件

  git add             √        √            ×            仅暂存新文件和修改过的文件
  \--ignore-removal .                                    
  ---------------------------------------------------------------------------------------------

**git无法添加空目录**

mkdir test创建一个空目录，此时git
status查看没有任何修改，空目录不能被git add/git
commit。此时可以在空目录下创建一个.gitkeep或.keep的文件，此时git就能感知到这个目录的存在了，可以git
add/git commit。

### git add的反操作

\$ git reset file //取消git add，从暂存区删除

\$ git restore \--staged file //取消git add，从暂存区删除

git reset \<pathspec\> is the opposite of git add \<pathspec\>, this
command is **equivalent** to git restore \--staged \<pathspec\>

![](media/image229.png){width="3.5347222222222223in"
height="1.5888888888888888in"}

[注意：]{.mark}

[git rm \--cached file不是把**git add的修改**从暂存区删除，而是把**git
add的整个文件**从暂存区删除，**不是git add的反操作**。]{.mark}

[git reset file、git restore \--staged
file才是将修改从暂存区删除，但保留暂存区文件(当然，如果是新增文件，也会同时将文件从暂存区删除)。]{.mark}

[git rm \--cached
file将文件从暂存区删除，不影响工作区，工作区文件和修改仍然存在。]{.mark}

## git commit

git commit -m \"comment\" //git
commit如果不加m参数，会弹出一个编辑框让用户输入提交信息

git commit -a -m \"comment\" //相当于git add和git
commit一起，-a参数只对已经存在于repository的文件有效，对于新增文件是无效的。

如果只是想修改commit时的提交信息，可以用：

\$ git commit \--amend -m \"comment\"

如果只更新修改内容，不修改提交信息，可以用：

\$ git commit \--amend \--no-edit

**git commit -m \"comment\"，怎么写多行注释？**

方法1：git commit不加-m参数，弹出vim编辑框，输入注释。

方法2：写注释时只输左边的引号，按enter换行，多行输入完成后，再输右边的引号。

\$ git commit -m \"comment line1
//输左边的引号，写第一行的注释，按enter换行到第二行输

comment line2 //输第二行，按enter换行到第三行输

comment line3\" //输右边的引号，按enter结束输入。

这样使用git log看的时候注释是分三行显示的。

就是在命令行双引号里写多行内容的问题，其他命令/非git命令也是一样的方法。

方法3：**使用多个 -m选项**：git commit -m \"首行摘要\" -m \"正文第一行\"
-m \"正文第二行\"。Git会将每个 -m后的内容连接为单独的段落。

方法4：**使用换行符**：在引号内直接换行。在Bash或Zsh等Shell中，可以这样写：git
commit -m \"首行摘要\"\$\'\\n\'\"\$\'\\n\'\"这里是正文部分。

方法5：git commit -m \"comment\"只能写一行提交说明，使用git commit
-e打开vi编辑器，可以编写多行提交说明，编辑完毕，输:wq保存退出。

![](media/image230.png){width="4.104166666666667in"
height="1.6243055555555554in"}

以#开头的行会被忽略，不会显示在提交说明里。

[commit中保存的是整个文件的快照，而不是修改的差异。保存整个文件的快照才能进行merge/rebase/分支切换等操作。]{.mark}

### git提交模板

Git提交模板(Commit Template)的作用就是在你输入 git
commit 命令打开编辑器时，**自动预填充一段格式化的文本**，你只需要按照提示填空即可。

**如何配置 Git 提交模板**

配置过程主要分为两步：**创建模板文件** 和 **告诉 Git 使用该文件**。

**1.第一步：创建模板文件**

你需要先在电脑的某个位置创建一个纯文本文件。为了方便管理，通常建议放在用户主目录或项目根目录下。

- 全局模板(推荐新手放在主目录)： 例如 ～/.gitmessage.txt (Mac/Linux)
  或 C:\\Users\\你的名字\\.gitmessage.txt (Windows)。

- 项目级模板： 放在项目根目录下，例如 .gitmessage.txt。

用文本编辑器(如 VS
Code、Notepad++、Vim)打开这个文件，输入你想要的格式。这里有一个通用的模板示例：

\# 请填写本次提交的简要描述(不超过50个字符)

\#

\# \* 类型: feat\|fix\|docs\|style\|refactor\|test\|chore

\# \* 范围: 模块或功能名称

\# \* 详细说明: 解决的问题或实现的功能

\#

\[type(scope): subject\]

\# 详细描述(可选)

\#

\#

\# 关联任务(如 Jira 编号或 GitHub Issue)

\#

\# Closes #123

[**提示：** 以 # 开头的行在提交时会被 Git
忽略，不会出现在最终的提交记录中，所以可以用它来写提示语。]{.mark}

**2.第二步：配置 Git 指向该模板**

打开终端(Terminal)或命令行工具，执行配置命令。

- 配置为全局生效(影响你电脑上所有的 Git 项目)：

git config \--global commit.template ～/.gitmessage.txt

- 配置为仅当前项目生效(推荐团队协作时使用)：

*\# 在项目根目录下执行，不加 \--global*

git config commit.template .gitmessage.txt

**如何使用**

提交时输 git commit 命令，不加-m选项，

1.  终端会自动打开默认的文本编辑器(如 Vim、Nano或你配置的编辑器)。

2.  [编辑器中已经自动填充了你刚才在 .gitmessage.txt 中写好的内容]{.mark}。

3.  你只需要填写具体的类型、描述和关联任务。

4.  保存并关闭文件，提交即生效。

**如何取消或修改模板？**

- 修改模板： 直接修改你第一步创建的那个 .gitmessage.txt 文件内容即可。

- 取消模板： 在配置命令后加 \--unset。

  - 全局取消：git config \--global \--unset commit.template

  - 项目取消：git config \--unset commit.template

通过使用提交模板，你可以让 Git
历史记录变得清晰、可读，无论是对自己回顾代码还是团队协作审查(Code
Review)都非常有帮助。

## git rm

git rm \--cached
filename删除暂存区中的文件。只删除暂存区中的文件可以取消系统对该文件的追踪。

git add file添加跟踪，git rm \--cached file取消跟踪。

\--cached \-- Use this option to [unstage]{.mark} and [remove paths only
from the index]{.mark}. [Working tree files, whether modified or not,
will be left alone]{.mark}.

## git branch 

\$ **git branch -a**

chanscanOK_reserved //本地分支

\* dev //本地分支。前面有\*表示当前所在分支。

master //本地分支

remotes/origin/HEAD -\> origin/master
//远程库HEAD指向origin/master，表示远程库默认在master分支上

remotes/origin/chanscanOK_reserved //远程分支

remotes/origin/master //远程分支

-v：显示详细信息

\$ **git branch -v** //**查看分支以及最后一次提交**

\* doing 77971dd 更新书写规范、优点

master d657916 新增单词，修改vi使用

reserve db36dff \[behind 1\] 更新单词

\$ **git branch -vv**
//**查看分支以及最后一次提交，本地分支对应的远程分支，并显示与远程分支之间的差异**

\* doing 77971dd 更新书写规范、优点
//可知doing分支没有跟踪远程分支，doing是在本地分支的基础上建立的，不是在远程分支的基础上建立的

master d657916 \[origin/master\] 新增单词，修改vi使用

reserve db36dff \[origin/master: behind 1\] 更新单词
//reserve分支比远程分支落后1个提交

结合使用

\$ **git branch -v**

\$ **git branch -rv**

\$ **git branch -av**

\$ git help branch

git branch \[\--color\[=\<when\>\] \| \--no-color\] \[\--show-current\]

\[-v \[\--abbrev=\<n\> \| \--no-abbrev\]\]

\[\--column\[=\<options\>\] \| \--no-column\] \[\--sort=\<key\>\]

\[\--merged \[\<commit\>\]\] \[\--no-merged \[\<commit\>\]\]

\[\--contains \[\<commit\>\]\] \[\--no-contains \[\<commit\>\]\]

\[\--points-at \<object\>\] \[\--format=\<format\>\]

\[(-r \| \--remotes) \| (-a \| \--all)\]

\[\--list\] \[\<pattern\>\...\]

git branch \[\--track\[=(direct\|inherit)\] \| \--no-track\] \[-f\]

\[\--recurse-submodules\] \<branchname\> \[\<start-point\>\]

git branch (\--set-upstream-to=\<upstream\> \| -u \<upstream\>)
\[\<branchname\>\]

git branch \--unset-upstream \[\<branchname\>\]

git branch (-m \| -M) \[\<oldbranch\>\] \<newbranch\>

git branch (-c \| -C) \[\<oldbranch\>\] \<newbranch\>

git branch (-d \| -D) \[-r\] \<branchname\>\...

git branch \--edit-description \[\<branchname\>\]

## 代码编写、提交流程

记住：先建分支，再修改代码。

建立分支的方式：

1\. git branch branchname (为当前目录所在的工程建立分支)

2\. git checkout -b branchname (为当前目录所在的工程建立分支)

3\. repo start branchname **.** (注意：后面有个点 **.**
，为当前目录所在的工程建立分支)

4\. repo start branchname \--all(为整个源代码目录下所有工程建立分支)

修改代码前确保在某一个分支上；如果不在任何分支上，修改的代码的保存位置无法确定，可能造成丢失。

使用git branch iss53、git checkout -b iss53建立分支，不能使用repo sync .
，报does not track upstream错误；

使用repo start iss53 . 建立分支可以使用repo sync . ，最好采用这种方式。

流程：\$ git checkout -b iss53 //建立分支

#vim sgk.c

\$ git diff //确认修改

\$ git add sgk.c / git add **.**

\$ git commit -m "comments of the commit"

#repo sync . //检验是否与服务器代码冲突,如果有冲突，解决完冲突再重复git

//add/commit步骤；

\$ git push \...

**1.vim sgk.cpp**

回退：取消修改，git checkout sgk.cpp

**2. git add**

使用命令 git add 开始跟踪一个新文件。

回退：取消git add，使用git checkout sgk.cpp / git checkout HEAD sgk.cpp
/ git reset HEAD sgk.cpp / git rm sgk.cpp

(注意：git checkout是取消add，文件仍然存在于工作目录；但git rm -f
newfile.cpp会把文件从暂存目录中删除，同时也从工作目录中删除；git
rm \--cache newfile.cpp的作用相当于git checkout。)

(关于git
checkout：如果暂存目录中有该文件，则是从暂存目录中checkout；如果暂存目录中没有该文件，则是从本地目录中checkout,此时和git
checkout HEAD的作用是一样的；)

**3. git commit**

\$ git commit -m \"Story 182: Fix benchmarks for speed\"

在一行命令中提交更新，-m参数后跟提交说明(-m后的注释将出现在gitg的Subject里，如果不带-m参数则会跳到vi窗口，要求填写提交说明。写多行注释时不带-m选项跳出vi窗口编辑。)

回退：取消git commit，使用git reset SHA(同一分支上以前提交的哈希值)

修改后再提交：**git commit \--amend**

![](media/image231.png){width="1.5743055555555556in"
height="0.6340277777777777in"}
![](media/image232.png){width="1.4854166666666666in"
height="0.5972222222222222in"}

右边为git\--amend之后的情况。

第一次commit之后，修改相关文件，然后git
add，再运行git\--amend，可以把新修改的文件commit，并且合并到第一次commit中，两者相当于只做了一次commit。(执行git\--amend后进入vi编辑窗口，可以修改注释。)

**4.git reset**

\$ git reset：放弃之前的某些提交；

分支已经前进了，需要返回来修改之前的某一个提交(分支：C1🡪C2🡪C3🡪C4🡪C5,分支已经前进到C5了，如果需要返回到C3进行修改和打补丁，那么要先reset到C3，修改相关代码，然后提交：git
commit \--amend。)

参考：git rebase -i SHA,交互式rebase

git reset
C3,不加hard参数,放弃C3之后的(C4、C5)提交，但是保留C4、C5提交所做的代码修改，此时，C4、C5所做的代码修改为untracked状态；

git reset \--hard
C3，加hard参数，放弃C3之后的提交，同时放弃C3之后的所做的修改；(总结：加不加hard参数，对C3之后所做的代码修改的处理方式不一样；)

不难理解git reset
HEAD\~1：提交以后后悔了，文件还是要修改后的，只是不想要这次提交。)

reset到C3后，然后对C3提交进行新的修改，然后再git commit \--amend,

(git commit \--amend不会改变C3提交的哈希值，只是打一个patch到C3上)

![](media/image233.png){width="1.5222222222222221in"
height="1.1416666666666666in"}
![](media/image234.png){width="1.4777777777777779in" height="0.4625in"}

右边是git reset 5667d1d19665eea90e647daa07b6dd1578b2b49f之后的情况。

(5667d1d19665eea90e647daa07b6dd1578b2b49f 为second commit的哈希值)

**5.获取、更新代码**

**\$ git** fetch
ssh://shiguik@sh2-git01.marvell.com:29418/android/platform/
packages/apps/Contacts refs/changes/09/509/3 && git checkout FETCH_HEAD
(sfetch C2的代码；)

(获取second
commit的代码，这个fetch地址从网页<http://sh2-git01.marvell.com/review/#/c/579/>拿到；

"fetch之后一般要新建一个分支用来保存fetch到的代码"。

\$ git
fetch之前工作目录在某分支上，**fetch之后则不在任何分支上**，因此**必须新建一个分支来保存fetch到的代码。**

#repo sync，如果repo
sync之前在new20111130分支上，那么repo之后会不在任何分支上，必须新建分支来保存repo下来的代码；

如果repo
sync之前在phs-gingerbread-dsds-dev_r3分支上，那么repo之后仍然在该分支上。phs-gingerbread-dsds-dev_r3是repo
init产生的分支，与服务器分支同名。)

**\$ git checkout -b
new_branch_name2**(新建一个分支来保存fetch到的代码。

使用fetch、repo
sync新取下来代码之后所建立的分支，其中的代码就是fetch、repo
sync得到的代码。是先fetch、repo
sync再新建分支来保存，还是先新建分支再fetch、repo sync？)

**#vi kkk.c**

**\$ git add kkk.c**

**\$ git commit \--amend (打补丁到commit3上)**

**#repo sync / repo sync .**(获取服务器最新代码)(解决冲突，重复git
add等步骤；)

**\$ git push sh2-git01 HEAD:refs/for/phs-gingerbread-d9001-dev_r2**

**6. \# repo start newbranch \--all** (跟踪远程分支；同时，**repo
start**
会在本地新建一个名为**newbranch**的分支，如果newbranch已经存在，则会覆盖；作用：使用**newbranch**分支跟踪服务器代码；如果fetch之后不repo
start则会不在任何分支上。

**\# repo start newbranch
.//**在当前目录下新建一个名为**newbranch**的分支，跟踪当前目录下的代码。)

## 取消已经暂存的文件

\$ git reset benchmarks.rb //参考：Pro git(精通git)第二版 -\> 2.git基础
-\> 撤消操作 -\> 取消暂存的文件

\$ git restore \--staged benchmarks.rb

## 取消对文件的修改

\$ git checkout benchmarks.rb //参考：Pro git(精通git)第二版 -\>
2.git基础 -\> 撤消操作 -\> 撤消对文件的修改

\$ git restore benchmarks.rb

任何已经提交到git的内容都可以被恢复。即便在已经删除的分支中的提交，或者用\--amend 重新改写的提交，都可以被恢复。所以，你可能失去的数据，仅限于没有提交过的，对
git来说它们就像从未存在过一样。

\$ **git checkout SHA
file**，将file退回到某个提交时的状态，会修改工作区和暂存区，不修改HEAD。

git checkout file和git checkout HEAD
file是一样的，应该是简写省略了HEAD吧。

撤销工作区的修改，使用checkout path、restore path

撤销暂存区的add，使用reset、restore \--staged

撤销提交历史记录，使用revert，reset

参考git reset命令的总结

## 删除一个文件、并且从git跟踪库中删除

\$ rm file

\$ git add file

\$ git commit -m \"delete a file\"

或者

\$ git rm file

\$ git commit -m \"delete a file\"

git add file不是增加文件的意思，而是将文件的修改添加到暂存区，因此rm
file之后还需要git add file，或者直接用git rm file从git库删除。

git rm file \--cached，表示将文件从git库删除，但是工作区还保留。

\$ git rm file \--cached

\$ git status

On branch master

Changes to be committed:

(use \"git restore \--staged \<file\>\...\" to unstage)

deleted: file

Untracked files:

(use \"git add \<file\>\...\" to include in what will be committed)

file

## 恢复删除的文件

得到deleting_commit信息

git rev-list -n 1 HEAD \-- \<file_path\>

回到删除文件deleting_commit之前的状态

git checkout \<deleting_commit\>\^ \-- \<file_path\>

或者，使用git log \--diff-filter找到删除文件所在SHA，见：10)历史记录查看
-\> git log \--diff-filter

这个文件以前git
add添加过到git库，才可以恢复，否则不能使用这里的方法恢复，可能操作系统有办法恢复？

注意：

git rev-list -n 1 HEAD \--
\<[file_path]{.mark}\>，注意要把文件所在路径写上，git rev-list -n 1 HEAD
\-- drivers/eth/test.c

git log \--diff-filter=D \--summary \| grep -C 10
\<[file_name]{.mark}\>，只需要写文件名、不需要写路径，git log
\--diff-filter=D \--summary \| grep -C 10 test.c

## 文件改名

\$ mv file filenew

\$ git add

\$ git commit

或者

\$ git mv file filenew

\$ git commit

git根据文件内容来计算SHA值，所以文件名不重要，重要的是文件内容。当更改文件名时，git并不会为此创建一个新的blob对象，而只是指向原来的blob对象。但是文件名变了，git会为此创建一个新的tree对象。

## checkout

checkout的三个作用：

1.切换分支

\--新版本git推荐使用git switch切换分支、创建分支，不推荐git
checkout。20260129

git checkout branchname，切换到某个已有的分支。新版本git使用git switch
branchname切换分支。

git checkout -b
newbranchname，新建一个分支，并切换到这个新分支。如果分支不存在则创建一个分支，如果分支已存在则切换到这个分支。

git checkout -b newbranchname
SHA，以SHA这个提交为基础新建一个分支，并切换到这个新分支。这样新建分支HEAD在SHA这个提交上。回退版本或基于某个旧的提交开始修改可用这么操作。相当于:git
checkout -b newbranchname; git reset \--hard SHA。

**[git
checkout切换分支前工作区有修改，切换分支后，修改会保留，修改会带到切换后的分支上去，切换分支前后，工作区、暂存区的状态不变。]{.mark}**

2.撤销修改

git checkout path 撤销一个文件或目录的修改，path可以是文件或者目录 \--
[撤销工作区没有git add的修改]{.mark}

git checkout filename，撤销一个文件的修改

git checkout dir ，撤销指定目录的修改

git checkout **.** ，撤销当前目录所有文件的修改

git checkout stash@{n} \-- file，从stash中恢复一个文件的修改

3.切换到指定提交

git checkout SHA，切换到指定提交，会退出当前分支，处于detached状态

## switch

git switch是Git
2.23版本引入的专门用于切换分支的命令，它旨在取代功能过于宽泛的 git
checkout命令，让分支操作更加清晰和安全。

下面这个表格汇总了它的核心用法，你可以快速查阅。

  -----------------------------------------------------------------------------------------------
  操作场景             命令                            说明
  -------------------- ------------------------------- ------------------------------------------
  切换到现有分支​       git switch \<branch-name\>      切换到指定的本地分支，如git switch main

  创建并切换到新分支​   git switch -c                   基于当前提交创建新分支并立即切换过去
                       \<new-branch-name\>             

  强制创建/重置分支​    git switch -C                   强制创建新分支，如果分支已存在，则重置它
                       \<new-branch-name\>             

  切换到上一个分支​     git switch -                    快速切换回你之前所在的分支，非常方便

  切换到远程分支​       git switch -t                   在本地创建并切换到跟踪指定远程分支的分支
                       origin/\<remote-branch-name\>   
  -----------------------------------------------------------------------------------------------

  --------------------------------------------------
  操作               旧命令(易混淆)   新命令(清晰)
  ------------------ ---------------- --------------
  切换分支           git checkout     git switch
                     main             main

  创建并切换新分支   git checkout -b  git switch -c
                     new              new

  恢复工作区文件     git checkout     git restore
                     file             file

  恢复暂存区文件     git checkout     git restore
                     \--staged file   \--staged file
  --------------------------------------------------

**进阶用法与技巧**

•**创建无历史的新起点**：使用 git switch \--orphan
\<new-branch\>可以创建一个全新的、没有任何提交历史的分支。这在需要初始化一个新项目结构或创建类似gh-pages的页面分支时特别有用。

•**临时检查历史提交**：通过 git switch \--detach \<commit-hash\>可以让
HEAD
指针直接指向某个历史提交，进入"分离HEAD"状态。在此状态下可以查看代码或进行实验性提交，但切换回其他分支后这些临时提交可能会被丢弃。

•**遇到未提交的更改时**：如果你有未提交的更改，Git默认会阻止你切换分支以避免冲突，这时你有几种选择：

･**提交更改**：如果工作已完成，直接 git add和 git commit。

･**暂存更改**：如果工作未完成，使用 git stash暂存更改，切换分支后再用
git stash pop恢复。

･**强制切换(不推荐)**：使用 git switch
\--force会丢弃未提交的更改，**请谨慎使用**。

## \--双横杠的作用

\$ git log English/new_words/word_fc.c

致命错误：有歧义的参数
\'English/new_words/word_fc.c\'：未知的版本或路径不存在于工作区中。

使用 \'\--\' 来分隔版本和路径，例如：

\'git \<命令\> \[\<版本\>\...\] \-- \[\<文件\>\...\]\'

\$ git log \-- English/new_words/word_fc.c，解决报错

备注：git log
English/new_words/word_fc.c之所以报错是因为这个文件不存在，这里只是举个例子描述一下报错信息。

git checkout \--help / git reset \--help对\--的解释：[Do not interpret
any more arguments as options]{.mark}.

git rm \--help对\--的解释：This option can be used to [separate
command-line options from the list of files]{.mark}, (useful when
[filenames might be mistaken for command-line options]{.mark}).

git checkout \-- file

一般情况下git checkout file和git checkout \--
file是一样的，但是有时候文件名file可能和git的关键字同名，此时git无法区分是文件名还是git参数，此时需要使用双横杠\--明确告诉git这是文件名。

全部git命令中都可以说使用\--，在可能造成git将文件名误认为参数的情况下，都要加上\--，git
add \-- \*.c、git checkout \-- \*.c、git reset \-- \*.c、git rm \--
\*.c、git log \-- \*.c等等。

## restore

**退回修改使用git restore**，不要轻易暴力还原git reset \--hard。

\$ git restore path

\$ git restore . //恢复当前目录到未修改状态

这个命令是 git 2.23 版本之后新加的，用来分担之前git
checkout命令的功能，作用就是用暂存区或者版本库中的文件覆盖本地文件的修改可以达到回退修改的目的，同时也可以使用版本库中的文件覆盖暂存区的文件，达到回退git
add命令的目的。

1、文件在暂存区且未作修改的情况

使用git restore \--staged \<file\>
把文件从暂存区移动到工作区，即文件不被追踪；

2、文件在暂存区且已经修改的情况

使用git restore \--staged \<file\>
把文件从暂存区移动到工作区，且不会撤销修改的内容；

使用git restore \<file\> 文件仍在暂存区且会撤销对文件修改的内容；

3、文件在本地代码库已经修改的情况

使用git add \<file\> 把文件重新放到暂存区，且保留文件的修改；

使用git restore \<file\> 文件仍在本地代码库且会撤销文件的修改；

git restore
\<file\>撤销文件的修改，使文件恢复到暂存区或本地代码库(取决于文件在修改前的状态)；

git restore \--staged
\<file\>把文件从暂存区撤回到工作区，保留文件最后一次修改的内容。

[git restore、git reset \--hard回退已跟踪文件，git clean
-fd删除未跟踪文件。]{.mark}

[git reset \--hard只能回退已跟踪文件？是的，已验证。]{.mark}

[那么reset、restore有什么区别？\--todo]{.mark}

[回退版本、清除编译中间文件，可以git restore path、git clean
-fd一起使用，或者git reset \--hard、git clean -fd一起使用。]{.mark}

[旧版git version 2.9.5不支持git restore命令，cygwin上测试：git:
\'restore\' is not a git command. See \'git \--help\'.。]{.mark}

[新版git version 2.39.0支持git restore命令。20230417]{.mark}

## restore(2)

git restore 是 Git 2.23
版本引入的新命令，专门用于**撤销修改**或**恢复文件**，旨在替代 git
checkout 的文件恢复功能，语义更加清晰。

**恢复工作区文件 (丢弃修改)**

用于放弃工作区(Working
Directory)中未提交的修改，将文件还原到暂存区或最新提交的状态。

git restore test.c

git restore src/test.c

git restore .

git restore src/

git restore \*.js

git restore file1.txt file2.txt

**撤销暂存 (Unstage)**

用于将文件从暂存区(Staging
Area)移出，还原到工作区，**保留**你的修改内容。相当于旧版的 git reset
HEAD \<file\>。

git restore \--staged test.c

git restore \--staged src/

git restore \--staged .

git restore -S test.c

git restore \--staged file1.txt file2.txt

**恢复到指定版本 (历史版本)**

用于从特定的提交(Commit)、分支或标签中恢复文件内容。

git restore \--source=HEAD test.c

git restore -s HEAD\^ test.c

git restore \--source=main test.c

git restore \--source=v1.0.0 test.c

git restore \--source=5d3a1b2 test.c

git restore \--source=origin/main src/

**彻底重置 (工作区 + 暂存区)**

用于同时重置工作区和暂存区，彻底丢弃所有未提交的修改(包括 git
add 过的和没 git add 的)，相当于旧版的 git reset \--hard(针对文件)。

git restore \--staged \--worktree test.c

git restore -SW test.c

git restore \--staged \--worktree .

git restore \--source=HEAD \--staged \--worktree test.c

**交互式恢复 (Patch)**

用于只恢复文件中的**部分修改**，Git 会逐块询问你是否要恢复。

git restore \--patch test.c

git restore -p test.c

git restore -p src/

git restore \--patch \--staged test.c

**恢复被删除的文件**

如果你误删了文件(rm test.c)，且尚未提交删除操作，可以用此命令找回。

git restore test.c

git restore src/deleted_file.txt

**常用参数速查表**

  -------------------------------------------------------------------------
  **参数**             **简写**   **作用**       **场景**
  -------------------- ---------- -------------- --------------------------
  \--staged            -S         仅恢复暂存区   撤销 git add，保留代码修改

  \--worktree          -W         仅恢复工作区   丢弃代码修改(默认行为)

  \--source            -s         指定来源       恢复到某个分支或历史版本

  \--patch             -p         交互模式       选择性恢复部分代码块

  \--ignore-unmerged   \-         忽略未合并     在冲突解决时使用
  -------------------------------------------------------------------------

## reset

参考：Pro git(精通git)第二版 -\> 7.git工具 -\> 重置揭密

\$ git reset \--soft/\--mixed/\--hard SHA

首先解析以下这三个相关的状态和概念：

①
**HEAD(本地仓库)**：可以描述为当前分支最后一个提交。即本地的信息中的当前版本。

② **Index(暂存区)**：在工作副本修改之后执行过git
add操作的版本文件，可以commit了的。\\\\Staging

③ **Working
Directory(工作目录)**：工作副本是你正在修改，但是没有执行任何git操作的文件。

修改代码，在Working Directory，

git add，将Working Copy的修改保存到Index，

git commit，将Inex的修改保存到HEAD。

如果代码修改了之后进行git add操作，然后git
commit，那么所有三者(HEAD,Index,Working
Directory)都是相同的状态，内容相同。

**\$ git reset \--soft/\--mixed/\--hard SHA**

  ------------------------------------------------------------------------------------------------
  **操作**         **HEAD**   **暂存区**(**Staging**)   **工作区**(**Files**)   **是否丢代码？**
  ---------------- ---------- ------------------------- ----------------------- ------------------
  \--soft          ❌ 回退    ✅ 保留变更(已 add)       ✅ 保留                 ❌ 否

  \--mixed(默认)   ❌ 回退    ❌ 清空(变未 add)         ✅ 保留                 ❌ 否

  \--hard          ❌ 回退    ❌ 清空                   ❌ **强制覆盖**         ✅ **是！**
  ------------------------------------------------------------------------------------------------

① \--**soft**：重置HEAD，保留index暂存区，保留Working
Directory工作区。相当于**git commit的反操作**。

② \--**mixed**(default)：重置HEAD，删除index暂存区，保留Working
Directory工作区。相当于**git commit和git add的反操作**。

git reset不加参数时**默认**表示\--mixed。

③ \--**hard**：重置HEAD指针，删除index暂存区，重置working
copy工作区。**相当于git commit和git add和工作区修改的反操作**。

**git reset \--soft/mixed/hard分别如何恢复到reset之前的状态？**

恢复 git reset 操作的关键在于理解每种模式改变了什么，以及 Git
内部的指针机制。

简单来说，恢复的核心命令通常是 git reset 配合 reflog 找到的之前的 Commit
ID。但在执行恢复前，你需要先确认之前的状态信息。

以下是针对三种模式的详细恢复指南：

**通用恢复原理(核心步骤)**

无论你使用了哪种模式，恢复的第一步通常是查看操作历史，找到你"reset
之前"的那个版本号。

- **查看操作日志**： 执行 git reflog。这个命令会列出你最近所有的 HEAD
  变动记录(包括 commit、reset 等操作)。

  - 你会看到类似 abc1234 HEAD@{0}: reset: moving to HEAD\~1 的记录。

  - 你需要找到 reset **之前** 那个提交的 Commit ID(例如 def5678)。

- **执行恢复**： 使用 git reset \--hard \<Commit ID\> 或 git reset
  \--soft \<Commit ID\> 跳转回去。

**三种模式的具体恢复策略**

虽然恢复的核心逻辑一样，但不同模式下，你的**工作区文件状态**不同，这决定了你恢复后是否需要重新提交文件。

+----------+------------------------------------+---------------+-------------------------------------------------------------+
| 模式     | 恢复前的文件状态                   | 恢复命令      | 恢复后状态                                                  |
+:=========+:===================================+:==============+:============================================================+
| \--soft  | 文件处于"已暂存"状态(绿灯)，       | git reset     | 文件和提交记录完全恢复。                                    |
|          |                                    | \--hard       |                                                             |
|          | 保留了提交记录。                   | ORIG_HEAD,或  |                                                             |
|          |                                    |               |                                                             |
|          |                                    | git reset     |                                                             |
|          |                                    | \--hard       |                                                             |
|          |                                    | \<CommitID\>  |                                                             |
+----------+------------------------------------+---------------+-------------------------------------------------------------+
| \--mixed | 文件处于"已修改未暂存"状态(红灯)， | git reset     | 文件内容保留，但需要重新 add 和 commit。                    |
|          |                                    | \--hard       |                                                             |
|          | 保留了文件修改。                   | \<CommitID\>  |                                                             |
+----------+------------------------------------+---------------+-------------------------------------------------------------+
| \--hard  | 工作区被清空/回退，                | git reset     | 注意:只能恢复已提交的版本，未提交的更改无法通过此命令找回。 |
|          |                                    | \--hard       |                                                             |
|          | **未提交的修改会丢失**。           | \<CommitID\>  |                                                             |
+----------+------------------------------------+---------------+-------------------------------------------------------------+

**详细场景解析**

**1.恢复 git reset \--soft**

\--soft 操作最温和，它只移动了 HEAD 指针，但把"暂存区"的内容保留了下来。

**恢复方法**：

- **最快方式**：Git 在执行 reset 时，会把 reset
  前的位置记录在 .git/ORIG_HEAD 中。你可以直接执行：

git reset \--hard ORIG_HEAD

- **通用方式**：通过 git reflog 找到之前的 Commit ID，然后 git reset
  \--hard \<ID\>。

**结果**：你的提交历史和暂存状态会完全复原。

**2.恢复 git reset \--mixed (或默认)**

\--mixed 是默认行为。它移动了 HEAD
指针，并重置了暂存区，但保留了工作目录里的文件修改。

**恢复方法**：

- 执行 git reflog，找到 reset 之前那个版本的 Commit ID。

- 执行 git reset \--hard \<CommitID\>。

**注意**：如果你在 reset 后又修改了文件，或者执行了其他操作，git
reflog 是找回丢失历史的唯一可靠途径。

**3.恢复 git reset \--hard**

这是最危险的操作，它会丢弃工作区和暂存区的所有更改。

**恢复方法**：

- 必须依赖 git reflog。因为 git log 只能显示当前 HEAD
  往前的历史，而 reflog 记录了所有分支的移动轨迹。

- 在 reflog 中找到你"误删"的那个提交的 ID，然后执行 git reset \--hard
  \<ID\>。

**警告**：

- **已提交的内容**：只要提交过(commit)，通过 reflog 几乎总能找回来。

- **未提交的修改**：如果你在执行 reset
  \--hard 之前，有\*\*没有提交(commit)\*\*的代码修改，这些修改会被永久覆盖，无法通过
  Git 命令恢复(除非编辑器有自动备份)。

**💡 一个实用的小技巧**

如果你刚刚执行了 reset，想立刻回到**上一个HEAD的位置**(即撤销这次
reset)，可以使用 HEAD@{1} 语法：

*\# 查看刚才的位置是什么*

git show HEAD@{1}

*\# 直接重置回刚才的位置*

git reset \--hard HEAD@{1}

**总结建议**：在执行 git reset \--hard
之前，如果不确定未来是否需要回滚，建议先创建一个临时分支备份：git branch
backup-temp。这样即使 reflog 混乱，你也能通过分支名找回来。

[\$ git reset
SHA，如果SHA!=HEAD时，会修改HEAD，**让HEAD指向SHA**；如果SHA==HEAD时，则不会修改HEAD。]{.mark}

[**git reset不仅可以后退，而且可以前进**。以前一直以为git
reset只能回退，这是误解。]{.mark}

[总之，git reset
SHA就是**在当前分支上前后移动HEAD指针**，让HEAD指向SHA，既能向前移动也能向后移动。]{.mark}

**[可以比喻成一把游标卡尺，多个commit相当于卡尺上的刻度，HEAD就像游标，可以在卡尺的不同刻度之间移动。既能向前移动，也能向后移动。]{.mark}**

[git reset sha和git checkout
sha不同的是，checkout会跳出当前分支、处于dettached状态，git
reset不会跳出当前分支，在当前分支的commit上前后移动HEAD指针。]{.mark}

**git checkout SHA和git reset SHA都可以在提交记录之间移动。**

git checkout SHA会跳出当前分支、处于detached状态(游离状态)。

git reset SHA不会跳出当前分支。

git checkout SHA之后做修改，需要新建分支才能保存修改，例：git checkout
SHA -\> vi file1 -\> git add file1 -\> git commit -\> git branch
savebranch -\> git checkout savebranch。

[git reset除了可以还原到某个SHA，还可以取消git add，见git add -\> git
add的反操作。]{.mark}

\$ git reset \--keep \[commit\]
//重置当前HEAD为指定commit，但保持暂存区和工作区不变\--保留未提交的本地修改。

\--keep和\--soft有什么区别？

## checkout、reset、restore的区别

1\. git checkout \-- filename，撤销工作区**[没有git add的修改]{.mark}**

2\. git reset \--
filename，撤销git库的提交和暂存区记录，不影响工作区(不加\--hard就没事)

3\. git restore，撤销工作区**[没有git add的修改]{.mark}**

  -------------------------------------------------
                 HEAD   Index   Workdir   Workdir
                                          safe
  -------------- ------ ------- --------- ---------
  基于提交                                

  reset \--soft  是     否      否        是
  \[commit\]                              

  reset          是     是      否        是
  \[\--mixed\]                            
  \[commit\]                              

  reset \--hard  是     是      是        否
  \[commit\]                              

  reset \--hard  否     是      是        否
  HEAD                                    

  checkout       是     是      是        是
  \<commit\>                              

  基于文件                                

  reset          否     是      否        是
  \[commit\]                              
  \<path\>                                

  checkout       否     是      是        否
  \[commit\]                              
  \<path\>                                

  基于修改                                

  stash          否     是      是        是

  restore        否     否      是        否
  -------------------------------------------------

**[工作区未提交的修改]{.mark}**是否保留、或者可恢复，来确定是不是安全。

例如git reset \--soft
SHA，会修改HEAD指针，但不影响暂存区，不影响工作区，不会改变工作区未提交修改，是安全的。

git reset \--hard SHA、git checkout SHA file、git restore
path会将工作区未提交修改覆盖掉，是不安全的。

git checkout SHA和git checkout SHA
file不同，如果工作区有未提交修改，那么git checkout
SHA会失败，工作区不影响，因此是安全的。但是git checkout SHA
file1会直接覆盖工作区file1的未提交修改，因此是不安全的。当然git checkout
SHA file1只会覆盖file1，不会覆盖file2。

git reset \--hard SHA、git checkout SHA file、git restore
path不安全，其他操作都是安全的，工作区未提交的修改可恢复。只要修改做了git
commit提交，都是可以恢复的。

只要有提交，就可以恢复。只要能找到提交的SHA，或者reflog，就可以恢复。平时写代码记得勤做提交，避免修改丢失。

[git reset \--hard commit的特殊用法，commit = HEAD时：git reset \--hard
HEAD，可以用于删除工作区、暂存区的修改，保留HEAD。]{.mark}

[git reset \--hard HEAD、git clean
-fd一起使用可以删除编译生成的文件，恢复未修改的初始状态。]{.mark}

git reset SHA和git reset SHA file是不一样的，git reset
SHA会移动HEAD指针，不改变暂存区和工作区，git reset SHA
file则不改变HEAD和工作区，只改变这个文件在暂存区的状态。

git checkout SHA和git checkout SHA file是不一样的，git checkout
SHA会跳出分支，处于游离状态,detached，也会移动HEAD到SHA，而git checkout
SHA file则不会改变HEAD，只改变这个文件在暂存区和工作区的状态。git
checkout SHA file将文件回退到指定版本、但又不改变HEAD。

[小结：**基于提交的reset/checkout**会改变HEAD指针，**基于文件的reset/checkout**不改变HEAD指针，只会改变这个文件在暂存区和/或工作区的状态。]{.mark}

git
stash将工作区、暂存区的修改保存到stash存储区，也是会改变暂存区和工作区的，但是这种改变是安全的，可以恢复。

git stash相当于做了一次git add和git
commit，只不过不是提交到git库，而是提交到stash存储区。

以前git模型的三个区：工作区暂存区git库，应该在增加一个区：④stash存储区，共四个区。

[git checkout SHA
file，如果想撤销一个文件的修改，或者将文件还原到某个提交时的状态，可以使用这条命令。]{.mark}

## clean

git clean，强制删除 untracked
的文件。使用clean命令后，删除的文件无法找回。

不会影响tracked的文件的改动，只会删除untracked的文件。

如果不指定文件文件名，则清空所有工作的untracked文件。

\$ git clean -h

用法：git clean \[-d\] \[-f\] \[-i\] \[-n\] \[-q\] \[-e \<模式\>\] \[-x
\| -X\] \[\--\] \<路径规格\>\...

-q, \--quiet 不打印删除文件的名称

-n, \--dry-run 演习

-f, \--force 强制

-i, \--interactive 交互式清除

-d 删除整个目录

-e, \--exclude \<模式\> 添加 \<模式\> 到忽略规则

-x **[也]{.mark}**删除忽略的文件

-X **[只]{.mark}**删除忽略的文件

git clean
-f，删除当前目录下所有**没有track过的文件**，他不会删除.gitignore文件里面指定的文件夹和文件,不管这些文件有没有被track过

git clean -f path，删除指定路径下的没有被track过的文件

git clean -df，删除当前目录下没有被track过的文件和文件夹

git clean
-xf，删除当前目录下所有没有track过的文件，会删除.gitignore文件里面指定的文件夹和文件

git clean \--dry-run或-n，是一次clean的演习, 告诉你哪些文件会被删除.
记住他不会真正的删除文件, 只是一个提醒

git clean \<directory-name\>
-df，清空指定目录，如果不指定目录名称，则清空所有工作的untracked目录

git clean可以**删除编译生成的文件**，如.o、.so、.a、.exe等文件。

**git reset / restore / git checkout 撤销已经被tracked的文件，**

**git clean删除工作区[没有被tracked的文件]{.mark}，**

git reset / restore / git checkout和git
clean结合使用，回退到一个指定commit的未修改状态，git
status查看是未修改的。

例：

\$ git reset \--hard HEAD

\$ git clean -fd

git-clean - Remove [untracked]{.mark} files from the working tree

**SYNOPSIS**

git clean \[-d\] \[-f\] \[-i\] \[-n\] \[-q\] \[-e \<pattern\>\] \[-x \|
-X\] \[\--\] \[\<pathspec\>\...\]

DESCRIPTION

Cleans the working tree by recursively removing [files that are not
under version control]{.mark}, starting from the current directory.

Normally, only files unknown to Git are removed, but if the -x option is
specified, ignored files are also removed. This can, for example, be
useful to remove all build products.

If any optional \<pathspec\>\... arguments are given, only those paths
that match the pathspec are affected.

**OPTIONS**

-d

Normally, when no \<pathspec\> is specified, git clean will not
[recurse]{.mark} into untracked directories to avoid removing too much.
Specify -d to have it recurse into such directories as well. If a
\<pathspec\> is specified, -d is irrelevant; all untracked files
matching the specified paths (with exceptions for [nested]{.mark} git
directories mentioned under \--force) will be removed.

-f, \--force

If the Git configuration variable clean.requireForce is not set to
false, git clean will refuse to delete files or directories unless given
-f or -i. [Git will refuse to modify untracked nested git repositories
(directories with a .git subdirectory) unless a second -f is
given]{.mark}.

-i, \--interactive

Show what would be done and clean files interactively. See "Interactive
mode" for details.

-n, \--dry-run

[Don't actually remove anything, just show what would be done]{.mark}.

-q, \--quiet

Be quiet, only report errors, but not the files that are successfully
removed.

-e \<pattern\>, \--exclude=\<pattern\>

Use the given exclude pattern in addition to the standard ignore rules
(see gitignore(5)).

-x

Don't use the standard ignore rules (see gitignore(5)), but still use
the ignore rules given with -e options from the command line. This
allows removing all untracked files, including build products. This can
be used (possibly in conjunction with git restore or git reset) to
create a pristine working directory to test a clean build.

-X

Remove only files ignored by Git. This may be useful to rebuild
everything from scratch, but keep manually created files.

## revert

**git revert 是撤销某次提交，此次提交之后的提交都会被保留。**

**git reset 是撤销某次之后的所有提交，此次提交会本身被保留。**

步骤1：具体一个例子，假设有四个提交 \-- git log
\--pretty=oneline查看如下:

commit4: add test4.c \-- 8da306200cc2ba41a8359a86ea37b497e532f15f (HEAD
-\> master) Add file 4

commit3: add test3.c \-- 69d90402563d2a3eeca051ff2f62c3e32bf20ad8 Add
file 3

commit2: add test2.c \-- d8b07d677adefc3ce8842f403f327523bfb1b1e4 Add
file 2

commit1: add test1.c \-- 696199e34574e6fa4261246f55ae950ac93a72aa Add
file 1

步骤2：执行git revert HEAD\~2，git log可以看到如下：

Revert \"add test2.c\" \-- a23508ac132583e256ca065fe55341ca29d5513d
(HEAD -\> master) Revert \"Add file 2\"

commit4: add test4.c \-- 8da306200cc2ba41a8359a86ea37b497e532f15f Add
file 4

commit3: add test3.c \-- 69d90402563d2a3eeca051ff2f62c3e32bf20ad8 Add
file 3

commit2: add test2.c \-- d8b07d677adefc3ce8842f403f327523bfb1b1e4 Add
file 2

commit1: add test1.c \-- 696199e34574e6fa4261246f55ae950ac93a72aa Add
file 1

git revert以后**产生一个新的提交**Revert \"add
test2.c\"记录此次修改，**其作用与commit2的作用正好相反**，**相当于commit2不起作用**。git
revert后产生一个新的提交，起被revert的提交的**反作用**。注意:**git
revert并没有将原有提交删除**，而是产生一个和原有提交**起相反作用**的新提交，和原有提交的作用相互**抵消**。**原有提交仍然存在于提交的历史记录中，仍然是可以被恢复的。**

步骤3：为了便于比较，先用git reset \--hard
HEAD\~将revert对应的那个提交**删除**掉，回到和刚开始时一样的状态。此时，git
log查看如下：

commit4: add test4.c \-- 8da306200cc2ba41a8359a86ea37b497e532f15f (HEAD
-\> master) Add file 4

commit3: add test3.c \-- 69d90402563d2a3eeca051ff2f62c3e32bf20ad8 Add
file 3

commit2: add test2.c \-- d8b07d677adefc3ce8842f403f327523bfb1b1e4 Add
file 2

commit1: add test1.c \-- 696199e34574e6fa4261246f55ae950ac93a72aa Add
file 1

可知，现在的状态已经和刚开始提交commit4时的状态完全一样。

步骤4：现在，使用git reset HEAD\~2，以便和git revert HEAD\~2比较。

执行git reset HEAD\~2，git log可以看到如下：

commit2: add test2.c \-- d8b07d677adefc3ce8842f403f327523bfb1b1e4 (HEAD
-\> master) Add file 2

commit1: add test1.c \-- 696199e34574e6fa4261246f55ae950ac93a72aa Add
file 1

可知，commit2之后的提交都被删除了。

修改步骤3：步骤3如果不使用git reset \--hard HEAD\~，而是使用git reset
\--hard HEAD，结果如下：

Revert \" Revert \"add test2.c\"\" \--
550a336341bf9e6c372b1dfb979f0937f9aee468 (HEAD -\> master) Revert
\"Revert \" Add file 2\"\"

Revert \"add test2.c\" \-- a23508ac132583e256ca065fe55341ca29d5513d
Revert \"Add file 2\"

commit4: add test4.c \-- 8da306200cc2ba41a8359a86ea37b497e532f15f Add
file 4

commit3: add test3.c \-- 69d90402563d2a3eeca051ff2f62c3e32bf20ad8 Add
file 3

commit2: add test2.c \-- d8b07d677adefc3ce8842f403f327523bfb1b1e4 Add
file 2

commit1: add test1.c \-- 696199e34574e6fa4261246f55ae950ac93a72aa Add
file 1

**小结**：

git
revert将中间的某一个\"提交\"的作用**抵消**(**注意是抵消,并没有删除**)，且git
revert**不会改变已有的历史记录**。

git
reset将某次提交之后的所有提交都**删除**，**某次提交本身则会保留**，会**改变已有提交历史记录**。

git reset有\--hard/\--soft/\--mixed等不同选项。

git revert 进行一次与指定版本**相反**的commit。如：\
\$ git revert \<sha\> \#
commit一次和\<sha\>指定commit相反的改动，会弹出编辑框修改注释，如果不想修改注释则使用git
revert SHA \--no-edit\
\$ git revert -n \<sha\> \# 和前一命令一样，但不提交

### git reset与git revert比较

- **git restore**：针对未提交(工作区/暂存区)的后悔操作；

- **git
  reset**：针对本地 HEAD 的历史回退，主要用于撤销已提交但未推送的提交；

- **git
  revert**：针对已推送到远程的后悔药，通过新增一个相反变更的提交来"撤销"历史。

**git reset**

git
reset的作用是还原Index的状态或修改本地分支HEAD的位置。这个命令适合用于从某个提交点重新开新的分支。比如，如果某个提交之后的代码我们都不要了，就可以在本地reset至指定commit，然后开一个新的branch继续新的开发(原来分支在远程上没有发生任何变化的)。

**使用git
reset是不影响远程分支**的，一切都在**本地**发生。**如果回退需要很快影响远程分支的，应该使用git
revert**。

**git revert**

假如某些旧提交我们不想要了，而又不愿通过自己修改代码重新提交的方式来完成，这个时候我们就可以把这项工作交给revert命令。

git
revert原理：根据你要回退的提交所做的改动做相反的改动，然后重新提交代码，使代码达到没有这些旧提交所能达到的状态。

如果对于git
revert的回退策略还没理解，这样讲也许你就能理解了：回退旧的提交必然会导致当前最新代码发生变化，比如之前某个提交加了一行代码，那么回退就是在相同位置减一行代码。git不会真的把旧提交抛弃，如果直接抛弃，历史记录就追踪不到了。因此，旧提交其实是没动的，git只是根据旧提交反着做了一遍，这才导致最新的代码发生了改变。只有把revert命令回退导致的改动重新提交，revert命令才算真的完成并生效，否则效果只相当于修改了工作树的文件而已。

注意：revert之后需要push到远程分支上其他用户才能看到回退发生的改动。

使用git revert会出现的问题

因为git
revert是用新提交覆盖旧提交，因此，被覆盖的提交等于不会被采用了。如果两个分支(假设是master和A分支)先合并再用revert回滚，之后又合并(A合并到master)，就会发现在master分支上，A分支第一次合并之前的修改大部分不见了。这是因为从时间的发生顺序来看，A分支第一次合并之前的修改发生在revert之前，revert发生在后，而
revert抛弃了A第一合并之前的修改，那么再合并git就认为你永远抛弃了A第一次之前的修改。

要解决这个问题，需要把revert产生的提交再revert一次。

### merge后如何revert ？

git log 查看结果如下：

\$ git log \--oneline

\* 3cde2df1, Comment1, someone@email.com, 08/06/26-14:01:13

\* 139ba703, Comment2, , someone@email.com, 08/06/26-11:40:50

\* ee304518, Merge branch \'key_new_board\' into \'main\', ,
someone@email.com, 08/04/26-08:15:07

\|\\

\| \* 43ef2dc7, Comment1, someone@email.com, 08/04/26-15:50:50

\|/

\* 75bb7a31, Merge branch \'ota\' into \'main\', , someone@email.com,
08/04/26-03:18:19

\|\\

\| \* 406196f6, Comment1, someone@email.com, 08/04/26-11:14:06

\|/

\* f0e8b4e5, Merge branch \'xrtos_fix11\' into \'main\', ,
someone@email.com, 08/04/26-02:34:45

问题：如果要回退43ef2dc7这个git提交，应该使用git revert
43ef2dc7，还是git revert ee304518？

结论：应回退43ef2dc7([功能提交]{.mark})，git revert 43ef2dc7。

原因：[真正改动的是]{.mark}43ef2dc7。

不能直接git revert
ee304518，会报错([多父节点]{.mark})，ee304518只是merge节点，改动内容来自43ef2dc7。

要撤销该功能，[revert功能提交]{.mark}即可。

若一定要 revert merge，必须指定主线父节点(一般是 main，即 -m 1)：

git revert -m 1 ee304518，对这种「merge
只带进一个功能提交」的情况，效果通常和 git revert 43ef2dc7接近，但：

以后若还想再合同一分支，会更麻烦(Git 认为该 merge 已处理过)。

## git diff

见：4)基本概念 -\> 一.git仓库、工作区、暂存区 -\> add/commit/diff的含义

基本概念：

git diff //比较工作区与暂存区之间的差异

git diff \--cached //比较暂存区与git库之间的差异

git diff HEAD //比较工作区与git库之间的差异

git diff SHA1 SHA2 //比较两次提交，**从SHA1到SHA2的变化**
//关键:**从\*到\***，**从X到Y的变化**

git diff SHA2 SHA1
//比较两次提交，**从SHA2到SHA1的变化**。这是不同的，例如一个文件，目前在c1提交，然后修改文件，**增加一行、内容为1**，提交、生成c2，那么:git
diff c1 c2的结果是**增加了一行、内容为1**\--按提交次序正向比较，但是:git
diff c2 c1的结果是**减少了一行、内容为1**\--按提交次序反向比较。

diff：当然是**两个对象比较才能形成difference**，git diff sha1
sha2表示**以sha1为比较的基准、从sha1到sha2所发生的变化**，sha2在sha1的基础上做了什么修改；git
diff sha2 sha1正好相反。git revert是不是利用了git
diff的这个特点做了一次相反的提交，从而抵消掉想要revert的那次提交？

git diff省略了比较对象，默认比较工作区域和暂存区，git diff
HEAD也省略了一个比较对象，默认比较工作区域和HEAD。

//上述git diff c1 c2等效于git diff HEAD\~ HEAD,、git diff c2 c1等效于git
diff HEAD HEAD\~。

git diff可以比较两个分支：

git diff master develop

**git diff SHA1 SHA2很有用，直接比较两个提交之间的差异。**

git diff SHA\~ SHA，结果和git show SHA是一样的，但是git show SHA是以git
diff的方式显示差异，不直观，这时git icdff SHA\~ SHA就很有用了，git icdff
SHA\~ SHA以直观、左右两栏对比的方式显示差异。

用法举例：

git diff SHA1 SHA2

git diff SHA\~ SHA = git show SHA

git diff HEAD\~ HEAD = git show HEAD

**git diff SHA1 SHA2 filepath**，比较两个提交中某个文件的差异

### git diff结果的解释

\$ git diff

diff \--git a/dev/usb/class/cdcserial/cdcserial.c
b/dev/usb/class/cdcserial/cdcserial.c

index 412663cd..cd8b0de7 100644

\-\-- a/dev/usb/class/cdcserial/cdcserial.c

+++ b/dev/usb/class/cdcserial/cdcserial.c
//同时表示修改的是usb_register_cb这个函数内的代码

@@ -155,6 +155,9 @@ static status_t usb_register_cb(
//从修改前的第155行开始显示、共显示6行，修改后也从第155行开始显示、共显示9行

} //显示的第1行，修改前的第155行，修改后的第155行

//显示的第2行，修改前的第156行，修改后的第156行

chan-\>usb_online = true; //显示的第3行，...

\+ if (chan-\>online_cb) {
//显示的第4行，修改前没有这一行，新增了一行，修改后的第158行

\+ chan-\>online_cb(chan, true);

\+ }

} else if (op == USB_CB_SETUP_MSG) {
//显示的第7行，修改前的第158行，修改后的第161行

static uint8_t buf\[EP0_MTU\];

const struct usb_setup \*setup = args-\>setup;

@@ -245,7 +248,8 @@ static status_t usb_recv_cplt_cb(ep_t endpoint,
usbc_transfer_t \*t) //修改前从第245行开始，修改后从第248行开始

} //修改前后显示的起始行号不相同，因为前一个修改改变了行数

//修改后的行号是当前看到的行号，查找代码应该看修改后的行号

// Write len bytes to the CDC Serial Virtual Com Port.

-status_t cdcserial_write(cdcserial_channel_t \*chan, size_t len,
uint8_t \*buf)

+status_t cdcserial_write_async(cdcserial_channel_t \*chan,
usbc_transfer_t \*transfer, ep_callback cb,

\+ size_t len, uint8_t \*buf)

{

LTRACEF(\"len = %d, buf = %p\\n\", len, buf);

git diff显示的格式：

**@@ -start,count +start,count @@**

**文件的原始状态用-表示，新状态用+表示**。

**-start**表示**原始文件**的**起始行号**，count表示从起始行开始**连续包含的行数**。

**+start**表示**修改后文件**的起始行号，count表示从起始行开始连续包含的行数。

@@ -155,6 +155,9 @@ static status_t usb_register_cb(

表示修改前从第155行开始，显示内容包含6行，

修改后的文件也从第155行开始，显示内容包含9行。

修改前起始行号，和修改后起始行号不一定相同，如果是这个文件的第一个修改，则相同，如果是这个文件的第二个修改，并且前一个修改改变了行数，则是不相同的。

当前所看到的是修改后的文件，看修改后的行号更有意义。

注意：

第155行并不是实际修改的那一行，实际修改的是第158行、第159行、第160行，增加了这3行。

实际修改行的前面有+-符号，其他行只是作为上下文相关行，多显示出来以方便阅读。

patch文件的格式也是这样的，应该就是基于diff比较差异的结果。

### git diff可直接用于比较两个文件

**git diff可直接用于比较两个文件，显示效果比diff好。**

\$ echo A \> file1

\$ echo A \> file2

\$ echo B \>\> file2

\$ git diff file1 file2

diff \--git a/file1 b/file2

index f70f10e..35d242b 100644

\-\-- a/file1

+++ b/file2

@@ -1 +1,2 @@

A

+B

\$ diff file1 file2

1a2

\> B

### 指定diff比较工具：icdiff, vimdiff, beyondcompare

git diff显示效果不好看，可以指定比较工具。

**git中用来对比差异的有两条命令：git diff与git difftool。**

git diff使用默认工具diff进行比较。

git difftool用于指定第三方工比较工具，如icdiff、vimdiff、beyondcompare。

如果你喜欢通过图形化的方式或其它格式输出方式的话，可以使用git
difftool命令来用Araxis、emerge、vimdiff等软件输出diff分析结果。

##### 1)使用icdiff作为比较工具

**icdiff** : improved colored diff, side-by-side highlighted command
line diffs.左右两栏对比的方式显示差异，彩色、高亮。

git icdiff使用方法：

①从<https://github.com/jeffkaufman/icdiff>下载，[将icdiff和git-icdiff拷贝到\~/bin/目录]{.mark}。Cygwin放到cygwin64\\usr\\local\\bin目录，或PATH中的目录。

②直接就可以使用了，git icdiff，或git-icdiff。按q退出比较。

**git icdiff更直观，左右两栏显示差异**

![](media/image235.png){width="7.295833333333333in"
height="1.7569444444444444in"}

###### 定制icdiff显示方式 

①配置显示行号、高亮：git config \--global icdiff.options \'\--highlight
\--line-numbers\'

②配置只想显示两行上下文：git config \--global icdiff.options
\'\--highlight \--line-numbers -U 2\'

icdiff的使用方法:总结,Linux命令.doc -\> 二、文件和目录操作2 -\>
icdiff,增强比较工具。原文帮助:<https://github.com/jeffkaufman/icdiff>。

如果只是执行一次：git difftool \--extcmd icdiff。

另一种方法：将icdiff拷贝到\~/bin/，git config \--global alias.diff
icdiff添加别名，这样git diff还和以前一样，git
icdiff使用icdiff作为比较工具。

\--其实这个配置步骤已经在git-icdiff文件中做了，不需要再按照上面的步骤配置了，如果要修改显示方式，那就修改git-icdiff文件。

git icdiff之所以能直接运行，是因为有git-icdiff这个文件，**执行git
icdiff命令实际是执行git-icdiff这个文件**，**命令行写git
icdiff或git-icdiff都可以**，git与icdiff之间既可以写空格、也可以写横杠，把横杠-当作空格了？**使用其他比较工具时也可以用这个方法**。

[icdiff和git-icdiff都是脚本，icdiff是python脚本，git-icdiff是shell脚本，git-icdiff在icdiff的基础上封装了一下。]{.mark}

**icdiff文件内容**：

#!/usr/bin/env python3

\_\_version\_\_ = \"2.0.4\"

color_codes = {

\"black\": \'\\033\[0;30m\',

\"red\": \'\\033\[0;31m\',

\"green\": \'\\033\[0;32m\',

\"yellow\": \'\\033\[0;33m\',

...

}

...

color_mapping = {

\"add\": \"green_bold\",

\"subtract\": \"red_bold\",

\"change\": \"yellow_bold\",

\"separator\": \"blue\",

...

}

**git-icdiff文件内容**：

#!/bin/sh

ICDIFF_OPTIONS=\$(git config \--get icdiff.options)

ICDIFF_OPTIONS=\"\${ICDIFF_OPTIONS} \--is-git-diff\"

GITPAGER=\$(git config \--get icdiff.pager)

if \[ -z \"\$GITPAGER\" \]; then

GITPAGER=\$(git config \--get core.pager)

fi

if \[ -z \"\$GITPAGER\" \]; then

GITPAGER=\"\${PAGER:-less}\" \-- 使用less作为分页显示控制

fi

if \[ \"\${GITPAGER%% \*}\" = \"more\" \] \|\| \[ \"\${GITPAGER%% \*}\"
= \"less\" \]; then

GITPAGER=\"\$GITPAGER -R\"

fi

#修改：加上-N显示行号

git difftool \--no-prompt \--extcmd=\"icdiff [-N]{.mark}
\$ICDIFF_OPTIONS\" \"\$s@\" \| \$GITPAGER

可以用这种方式封装自己的命令。

##### 2)使用difft作为比较工具

1、安装difftastic

snap install difftastic

snap help refresh

difftastic \--help

alias difft=dfftastic

2、按照git-icdiff的方式创建git-difft脚本

#!/bin/sh DIFFTASTIC_OPTIONS=\$(git config \--get difftastic.options)

#DIFFTASTIC_OPTIONS=\"\${DIFFTASTIC_OPTIONS} \--is-git-difft\"

GITPAGER=\$(git config \--get difftastic.pager)

if \[ -z \"\$GITPAGER\" \]; then

GITPAGER=\$(git config \--get core.pager)

fi

if \[ -z \"\$GITPAGER\" \]; then

GITPAGER=\"\${PAGER:-less}\" \-- 使用less作为分页显示控制

fi

if \[ \"\${GITPAGER%% \*}\" = \"more\" \] \|\| \[ \"\${GITPAGER%% \*}\"
= \"less\" \]; then

GITPAGER=\"\$GITPAGER -R\"

fi

git difftool \--no-prompt \--extcmd=\"difftastic \$DIFFTASTIC_OPTIONS\"
\"\$@\" \| \$GITPAGER

##### 3)使用vimdiff作为比较工具

vimdiff是vim自带的比较工具，使用方法：vimdiff file1 file2。

可以使用vimdiff作为git的比较工具，如下：

git difftool \--no-prompt \--extcmd \"vimdiff -n\"

git difftool \--no-prompt \--extcmd=\"vimdiff
-n\"//\--extcmd后跟等号或空格都可以

只能跟一个具体的文件名，不能像git diff那样可以连续比较多个文件。

输:q退出当前文件比较，显示当前文件全部内容，再输:q进入下一个文件比较。

如果按ctrl+z直接退出全部文件比较。

或者：git difftool \--no-prompt \--extcmd \"vimdiff -n\"
file，只比较一个文件。

取个别名git vimdiff

git config \--global alias.vimdiff \'difftool \--no-prompt \--extcmd
\"vimdiff -n\"\'

git vimdiff file

**3)使用beyondcompare作为比较工具**

1.mac os 配置

git config \--global diff.tool bc4

git config \--global difftool.prompt false

git config \--global difftool.bc4.cmd \'\"/usr/local/bin/bcomp\"
\"\$LOCAL\" \"\$REMOTE\"\'

git config \--global merge.tool bc4

git config \--global mergetool.prompt false

git config \--global mergetool.bc4.cmd \'\"/usr/local/bin/bcomp\"
\"\$LOCAL\" \"\$REMOTE\" \"\$BASE\" \"\$MERGED\"\'

git config \--global mergetool.bc4.trustexitcode true

2.windows 配置

git config \--global diff.tool bc4

git config \--global difftool.prompt false

git config \--global difftool.bc4.cmd \'\"C:\\Program Files\\Beyond
Compare 4\\BComp.exe\" \"\$LOCAL\" \"\$REMOTE\"\'

git config \--global merge.tool bc4

git config \--global mergetool.prompt false

git config \--global mergetool.bc4.cmd \'\"C:\\Program Files\\Beyond
Compare 4\\BComp.exe\" \"\$LOCAL\" \"\$REMOTE\" \"\$BASE\"
\"\$MERGED\"\'

git config \--global mergetool.bc4.trustexitcode true

注意配置的是BComp.exe，不是BCompare.exe。

3.配置完后输git difftool启动Beyond Compare比较。git
diff仍然是以前默认的比较工具。

有问题：windows cygwin按照上述2.配置完后，弹出Beyond
Compare左边有内容、右边是空白，如下：

![](media/image236.png){width="5.821527777777778in"
height="2.5965277777777778in"}

[其实没必要按照上述步骤配置，直接使用\--extcmd调用BeyondCompare就可以了：]{.mark}

[git difftool \--no-prompt
\--extcmd=/cygdrive/d/BeyondCompare/BComp]{.mark}

**4)指定比较工具**

[git difftool \--extcmd=vimdiff和git difftool
\--tool=vimdiff都能启动vimdiff作为比较工具。]{.mark}

[如果不想每次执行都弹出提示，可以使用\--no-prompt选项：]{.mark}

[git difftool \--no-prompt \--extcmd=vimdiff和git difftool \--no-prompt
\--tool=vimdiff都能启动vimdiff作为比较工具。]{.mark}

[git difftool \--no-prompt
\--extcmd=/cygdrive/d/BeyondCompare/Bcomp正常，但是git difftool
\--no-prompt \--tool=/cygdrive/d/BeyondCompare/BComp 报错Unknown merge
tool。]{.mark}

使用git difftool \--help查看帮助，使用git difftool
\--tool-help查看系统支持哪些git diff插件，使用git mergetool
\--tool-help查看支持哪些merge插件。

\$ git difftool \--help

-t \<tool\>, \--tool=\<tool\>

Use the diff tool specified by \<tool\>. Valid values include emerge,
kompare, meld, and vimdiff. Run git difftool \--tool-help for the list
of valid \<tool\> settings.

If a diff tool is not specified, git difftool will use the configuration
variable diff.tool. If the configuration variable diff.tool is not set,
git difftool will pick a suitable default.

You can explicitly provide a full path to the tool by setting the
configuration variable difftool.\<tool\>.path. For example, you can
configure the absolute path to kdiff3 by setting difftool.kdiff3.path.
Otherwise, git difftool assumes the tool is available in PATH.

Instead of running one of the known diff tools, git difftool can be
customized to run an alternative program by specifying the command line
to invoke in a configuration variable difftool.\<tool\>.cmd.

When git difftool is invoked with this tool (either through the -t or
\--tool option or the diff.tool configuration variable) the configured
command line will be invoked with the following variables available:
\$LOCAL is set to the name of the temporary file containing the contents
of the diff pre-image and \$REMOTE is set to the name of the temporary
file containing the contents of the diff post-image. \$MERGED is the
name of the file which is being compared. \$BASE is provided for
compatibility with custom merge tool commands and has the same value as
\$MERGED.

\--tool-help

Print a list of diff tools that may be used with \--tool.

-x \<command\>, \--extcmd=\<command\>

Specify a custom command for viewing diffs. git-difftool ignores the
configured defaults and runs \$command \$LOCAL \$REMOTE when this option
is specified. Additionally, \$BASE is set in the environment.

**5) icdiff帮助**

\$ icdiff -h

Usage: icdiff \[options\] left_file right_file

Show differences between files in a two column view.

Options:

\--version show program\'s version number and exit

-h, \--help show this help message and exit

\--cols=COLS specify the width of the screen. Auto detection is Unix
only

\--encoding=ENCODING specify the file encoding; defaults to utf8
\--无效，设置了没用

-E MATCHER, \--exclude-lines=MATCHER

Do not diff lines that match this regex. Not compatible with the
\'line-numbers\' option

\--head=HEAD consider only the first N lines of each file

-H, \--highlight color by changing the background color instead of the
foreground color. Very fast, ugly, displays all changes

-L LABELS, \--label=LABELS

override file labels with arbitrary tags. Use twice, one for each file.
You may include the formatting

strings \'{path}\' and \'{basename}\'

-N, \--line-numbers generate output with line numbers. Not compatible
with the \'exclude-lines\' option.

\--no-bold use non-bold colors; recommended for solarized

\--no-headers don\'t label the left and right sides with their file
names

\--output-encoding=OUTPUT_ENCODING specify the output encoding; defaults
to utf8

-r, \--recursive recursively compare subdirectories

-s, \--report-identical-files report when two files are the same

\--show-all-spaces color all non-matching whitespace including that
which is not needed for drawing the eye to changes. Slow,

ugly, displays all changes

\--tabsize=TABSIZE tab stop spacing

-t, \--truncate truncate long lines instead of wrapping them

-u, \--patch generate patch. This is always true, and only exists for
compatibility

-U NUM, \--unified=NUM, \--numlines=NUM

how many lines of context to print; can\'t be combined with
\--whole-file

-W, \--whole-file show the whole file instead of just changed lines and
context

\--strip-trailing-cr strip any trailing carriage return at the end of an
input line

\--color-map=COLOR_MAP

choose which colors are used for which items. Default is
\--color-map=\'add:green_bold,change:yellow_bold,desc

ription:blue,line-numbers:white,meta:magenta,separator
:blue,subtract:red_bold\'. You don\'t have to override

all of them: \'\--color-map=separator:white,description:cyan

\--is-git-diff Show the real file name when displaying git-diff result

### 技巧：查看某个提交的修改

\$ git lg 13bba0c7 -1 \--name-status

\* 13bba0c7, adjust search results tab view, , gaheadus@126.com,
2026/08/ 6-22:47:10\|

\| M src/app/i18n/en.ts

\| M src/app/i18n/zh_CN.ts

\| M src/app/i18n/zh_TW.ts

\| M src/ui/src/crawlerwidget.cpp

git show 13bba0c7，查看指定提交的修改，显示所有文件。

git show 13bba0c7 \--
src/ui/src/crawlerwidget.cpp，查看指定提交的指定文件的修改，或者使用git
diff

git diff 13bba0c7\~ 13bba0c7
src/ui/src/crawlerwidget.cpp，查看指定文件的修改。使用git diff SHA\~
SHA的好处是可以指定diff工具如icdiff，

git icdiff 13bba0c7\~ 13bba0c7
src/ui/src/crawlerwidget.cpp，icdiff显示效果比git show、git diff好。

### diff比较二进制文件

diff比较二进制文件，需要加**\--text**选项。git默认只能比较utf-8编码格式的文件，如果不是utf-8编码，则需要使用\--text选项。

\$ file file2

file2: Unicode text, UTF-16, big-endian text

\$ git diff

diff \--git a/file2 b/file2

index 547ed84..299d48a 100644

Binary files a/file2 and b/file2 differ

\$ git diff \--text

diff \--git a/file2 b/file2

index 547ed84..299d48a 100644

\-\-- a/file2

+++ b/file2

@@ -1,3 +1,2 @@

\-[\<FE\>\<FF\>\^@]{.mark}1[\^@]{.mark}

\-[\^@]{.mark}2[\^@]{.mark}

\-[\^@]{.mark}3

\\ No newline at end of file

\+[\<FE\>\<FF\>\^@]{.mark}2[\^@]{.mark}

\+[\^@]{.mark}3[\^@]{.mark}

\$ diff file2 file3

二进制文件 file2 和 file3 不同

\$ diff **\--text** file2 file3

1,3c1,2

\< ▒▒1

\< 2

\< 3

\\ 文件末尾没有换行符

\-\--

\> ▒▒2

\> 3

\$ cat file2

▒▒1

2

3

\$ cat file3

▒▒2

3

## git status

git status \[\<options\>...​\] \[\--\] \[\<pathspec\>...​\]

git status后面是可以加路径的，查看指定路径的状态

\$ git status /home/dukang/work/cpp

\$ git status cpp

[git status中文乱码，解决：git config \--global core.quotepath
false或git config \--global core.quotepath off]{.mark}

\$ git status -uno //-uno能提高速度，但需要小心不要忘了添加新文件(参见
\'git help status\')。

当git库很大时，执行一次git status需要很长时间时，使用-uno可以提高速度。

分析：git status -uno == git status
\--untracked-files=no，不显示没有跟踪的代码。

-u\[\<mode\>\], \--untracked-files\[=\<mode\>\]

Show untracked files.

The mode parameter is used to specify the handling of untracked files.
It is optional: it defaults to all, and if

specified, it must be stuck to the option (e.g. -uno, but not -u no).

The possible options are:

• no - Show no untracked files.

• normal - Shows untracked files and directories.

• all - Also shows individual files in untracked directories.

When -u option is not used, untracked files and directories are shown
(i.e. the same as specifying normal), to help

you avoid forgetting to add newly created files. Because it takes extra
work to find untracked files in the

filesystem, this mode may take some time in a large working tree.
Consider enabling untracked cache and split index

if supported (see git update-index \--untracked-cache and git
update-index \--split-index), Otherwise you can use no

to have git status return more quickly without showing untracked files.

The default can be changed using the status.showUntrackedfiles
configuration variable documented in git-config(1).

\$ git status -s
//不显示提示信息，只显示有变化的文件名，修改状态有颜色。

\$ git status \--porcelain
//不显示提示信息，只显示有变化的文件名，修改状态无颜色。可以搭配过滤器使用，如:

\$ git status \--porcelain\|grep **\^\" M\"**，注意\"
M\"字母M前面有个空格。

\$ svn status \|grep \^M //svn不需要在M前面加空格

\$ svn status \|grep \^M\|grep -E \"\*\\.c\$\|\*\\.h\$\"

\$ git status \--porcelain \| grep \^\" M\" \| awk \'{print \$2}\'
//方便在脚本中、其他命令中调用

test.txt

\$ git add \`git status \--porcelain \| grep \^\" M\" \| awk \'{print
\$2}\'\`

\$ **git status**

位于分支 test

要提交的变更：

(使用 \"git restore \--staged \<文件\>\...\" 以取消暂存)

新文件： file1

尚未暂存以备提交的变更：

(使用 \"git add \<文件\>\...\" 更新要提交的内容)

(使用 \"git restore \<文件\>\...\" 丢弃工作区的改动)

修改： English/专业英语,单词,生词,new_words/fc.c

未跟踪的文件:

(使用 \"git add \<文件\>\...\" 以包含要提交的内容)

file2

\$ **git status -s**

M English/专业英语,单词,生词,new_words/fc.c

A file1

?? file2

\$ **git status \--porcelain**

M English/专业英语,单词,生词,new_words/fc.c

A file1

?? file2

## git tag

查看tag

\$ git tag //列出所有本地标签

\$ git tag -l \"v0.1.\*\" //搜索符合模式的标签

\$ git show \[tag\] //查看tag信息

\$ git checkout -b \[branch\] \[tag\] //新建一个分支，指向某个tag

创建tag

\$ git tag \[tag-name\] //创建轻量标签。基于最新提交创建标签。

\$ git tag \[tag-name\] -m \"注释\" //给tag加注释

\$ git tag \[tag-name\] SHA
//基于某个提交创建标签。如果不指定commit，默认在当前最新提交HEAD上打tag。

\$ git tag \[tag-name\] SHA -m \"注释\" //给tag加注释

\$ git tag -a \[tag-name\] //创建附注标签

\$ git tag -a \[tag-name\] -m \"comments\"

\$ git tag -d \[tag-name\] //删除标签

\$ git push \[remote\] \[tag\] //提交指定tag

\$ git push \[remote\] \--tags //提交所有tag

\$ git push origin \--tags //上传本地tag到远程仓库

\$ git push origin:refs/tags/\[tag-name\] //删除远程tag， git push
origin \--delete :refs/tags/\[tag-name\]可以吗？

\$ git pull origin \--tags //合并远程仓库的tag到本地

打标签

git标签分为两种类型：轻量标签和附注标签。**轻量标签是指向提交对象的引用，附注标签则是仓库中的一个独立对象**。建议使用附注标签。

\$ git tag v0.1.2-light //创建轻量标签

\$ git tag -a v0.1.2 -m \"0.1.2版本\" //创建附注标签

创建轻量标签不需要传递参数，直接指定标签名称即可。

创建附注标签时，参数a即annotated的缩写，指定标签类型，后附标签名。参数m指定标签说明，说明信息会保存在标签对象中。

删除标签

误打或需要修改标签时，需要先将标签删除，再打新标签。

\$ git tag -d v0.1.2 //删除标签

参数d即delete的缩写，意为删除其后指定的标签。

给指定的commit打标签

打标签不必要在head之上，也可在之前的版本上打，这需要你知道某个提交对象的校验和(SHA,通过git
log获取)。

\$ git tag v0.1.1 9fbc3d0 //补打标签

标签发布

通常的git push不会将标签对象提交到git服务器，我们需要进行显式的操作：

\$ git push origin v0.1.2 //将v0.1.2标签提交到git服务器

\$ git push origin \--tags //将本地所有标签一次性提交到git服务器

注意：如果想看之前某个标签状态下的文件，可以这样操作

1.git tag //查看当前分支下的标签

2.git checkout v0.21
//此时会指向打v0.21标签时的代码状态，(但现在处于一个空的分支上)

3.cat test.txt //查看某个文件

### 查看tag记录，并且显示tag创建时间

推荐：git log \--tags \--simplify-by-decoration \--pretty=\"%ci %d\"

原生的 git tag命令默认不会显示创建时间，但通过其他 Git
命令可以轻松实现这个需求。
下面这个表格总结了几种最实用的方法，你可以根据需求选择。

+------------------+---------------------------+--------------------------------------------------------------------+
| 方法             | 命令示例                  | 输出特点与适用场景                                                 |
+:=================+:==========================+:===================================================================+
| 按时间排序列表​   | git for-each-ref          | %(taggerdate:short)\" refs/tags\`                                  |
|                  | \--sort=taggerdate        |                                                                    |
|                  | \--format                 |                                                                    |
|                  | \"%(refname:short)\"      |                                                                    |
+------------------+---------------------------+--------------------------------------------------------------------+
| 查看单个标签详情​ | git show v1.0.0           | 信息详尽，可查看某个特定标签的完整元数据（创建者、时间、注释等）。 |
+------------------+---------------------------+--------------------------------------------------------------------+
| 可读性更强的日志​ | git log \--tags           | 与提交历史结合，展示了项目历史中标签被打上的时间点。               |
|                  | \--simplify-by-decoration |                                                                    |
|                  | \--pretty=\"%ci %d\"      |                                                                    |
|                  |                           |                                                                    |
|                  | \--**推荐**               |                                                                    |
+------------------+---------------------------+--------------------------------------------------------------------+

**💡 使用方法与提示**

- **按时间排序列表**

如果你想获得一个**最整洁、专门用于按时间顺序浏览标签的列表**，推荐使用
git for-each-ref命令。它可以对标签引用进行排序和格式化输出。

git for-each-ref \--sort=-taggerdate \--format=\"%(tag) \|
%(taggerdate:short)\" refs/tags

**\--sort=-taggerdate**：这里的减号
-表示按时间**降序**排列，即最新的标签在最前面。如果想看最老的标签在前，去掉减号即可。

**\--format**：可以自定义输出格式。%(tag)显示标签名，%(taggerdate:short)显示短格式日期。你也可以使用
%(taggerdate:relative)来显示相对时间（如"2 weeks ago"）。

- **查看单个标签详情**

当你需要**检查某个特定发布版本的详细信息**时，使用 git show是最佳选择。

git show v1.4.0

执行命令后，你会看到类似以下的详细信息，其中就包含了打标签的准确时间：

tag v1.4

Tagger: Scott Chacon \<schacon@gee-mail.com\>

Date: Mon Feb 9 14:45:11 2009 -0800 \<\-\-- 这就是标签的创建时间

my version 1.4

commit 15027957951b64cf874c3557a0f3547bd83b3ff6

\...

**⚠️ 重要提示**

需要注意的是，**"创建时间"信息主要存在于"附注标签"（annotated
tag）中**。另一种"轻量标签"（lightweight
tag）只是对一个提交的简单引用，本身不存储额外的元数据。如果你使用 git
show查看一个轻量标签，显示的结果将是它所指向的提交的详细信息，而不是标签本身的创建信息。

**💎 总结**

- 想**快速查看所有标签及其时间**，用 git for-each-ref命令。

- 想**详细了解某个特定标签**，用 git show \<tag_name\>。

## 冲突

报冲突内容如下：

1

\<\<\<\<\<\<\< HEAD

5

3

=======

2

3

4

\>\>\>\>\>\>\> master

当前在dev分支上，修改了文件，使用git merge master合并，产生上述冲突。

**以等号===为界分为两部分，表示这两部分修改了同一个地方、修改不一致造成了冲突。**

===之前、HEAD表示当前最新提交、冲突之前的代码，

===之后是merge其他分支的代码。

HEAD指向当前提交，本来就是这个意思。

## git stash

**stash功能**

(1)**git stash** ：保存**[暂存区和工作区]{.mark}**的修改。

git stash只会保存已经被git tracked的文件，对于新增文件，还没有被git
track，是不会被保存的，如果需要保存，使用git stash -u。

git stash保存已跟踪文件，git stash
-u保存**已**跟踪文件**和未**跟踪文件。

git stash默认不加注释，没有注释不方便以后查看，使用save选项添加注释，git
stash save \"comments\"。唯一添加注释不需要加-m参数的命令。新版本git
stash save被标记为**过时**、**不推荐**，**使用git stash
push替代**。需要不断的学习才行，一定要在最版本上多看看git command
help帮助。

(2)**git stash push** ：保存**[暂存区和工作区]{.mark}**的修改，功能和git
stash一样。好处是git stash push可以加路径和注释，git stash push
code/src/file1，只保存指定文件，不再是将暂存区和工作区修改一股脑儿全部保存，更精细化了。如果不加路径，git
stash push还是将暂存区和工作区的修改全部保存。

[stash添加注释使用git stash push path -m \"comments\"，和git commit -m
\"comments\"统一了]{.mark}，点赞。

git stash只会保存已经被git tracked的文件，对于新增文件，还没有被git
track，是不会被保存的，如果需要保存，使用git stash push -u。git stash

push保存已跟踪文件，git stash push
-u保存**已**跟踪文件**和未**跟踪文件。\-- 和git stash一样

(3)**git stash list** ：列出所有存储

(3)**git stash show
stash@{n}**：显示修改的文件列表。如果要查看修改内容，则加个-p参数：git
stash show stash@{n} -p。

(4)**git show stash@{n}**：按照show命令的方式显示stash@{n}，而git stash
show是按照stash的方式显示stash@{n}。见git show命令。

git show stash@{n}的显示结果和git stash show stash@{n} -p是一样的，git
show stash@{n} \--name-only和git stash show stash@{n}的结果是一样的。

(5)**git stash apply**
:应用某个存储,将修改恢复到工作区，但**不会将stash从缓存堆栈中删除**。默认使用第一个存储,即stash@{0}，使用git
stash apply stash@{n}指定恢复某个存储，例git stash apply stash@{2}。

(6)**git stash pop** ：**是git stash
push的反操作**，恢复之前缓存的工作目录，**将stash从缓存堆栈中删除**，并将对应修改应用到当前的工作目录下,默认为第一个stash,即stash@{0}，使用git
stash pop stash@{n}恢复指定某个存储，例git stash pop stash@{2}。

(7)**git stash drop stash@{\$num}** ：删除某一个存储

(8)**git stash clear** ：删除所有存储

(9)**git checkout stash@{n} \-- file**，从stash中取出某个文件的修改。git
stash apply stash@{n}是将stash@{n}中所有文件的修改恢复到工作区，而git
checkout stash@{n} \-- file则只恢复指定文件的修改。

还有一个不同，git stash apply只恢复工作区修改，git checkout stash@{n}
file同时恢复工作区修改和暂存区index的状态。

(10)**git stash branch \<branchname\> \<stash\>** 基于进度创建分支

**部分暂存**

1.只存指定文件

不想把所有改动都stash，可以只暂存部分文件。

**git stash push -m \"comment\" \-- src/main/java/order/**
//只暂存指定文件，其余改动留在工作区

**git stash push -m \"comment2\" \-- application.yml** //暂存单个文件

2.交互式选择暂存

-p参数可以逐块选择哪些改动要stash，哪些留在工作区。

**git stash push -p -m \"partial stash\"**
//逐块确认，输入y暂存/n跳过/q退出

注意：-p按hunk粒度选择，同一个文件可以只暂存部分改动。但拆得太细恢复时容易漏，建议按功能模块分。

**分支切换**

1\. stash直接创建分支

恢复stash的同时创建新分支，适合\"临时改动越写越多，发现应该独立成新分支\"的场景。

**git stash branch feature-new stash@{0}** //从stash创建新分支并切换过去

这个命令相当于：创建新分支 → 切过去 → apply stash → drop
stash，一步到位。

默认情况下， git
stash命令会把以下修改存储到一个新的堆栈中。堆栈中的内容(stash)**可以被所有分支访问**。

▪[暂存区中的]{.mark}修改

▪[工作区中已经存在的]{.mark}文件的修改

也就是说，默认情况下，git stash 命令不会存储下列文件。

▪工作区中[新增的]{.mark}文件(untracked files)

▪被版本库[忽略的]{.mark}文件(.gitignore 中定义的)

如果想要存储 untracked files，可以使用-u选项，git stash
-u。\--[新增加的文件]{.mark}如果想要暂存，那么需要使用-u选项。

如果想要存储 untracked files和被版本库忽略的文件，可以使用-a选项，git
stash
-a。一般不推荐这么做，因为既然是被版本库忽略的文件，就没有必要再存储起来。除非你有非常特别的需求。

执行 git stash 命令后，工作区就恢复到了上一次git
commit时的状态。具体表现为：

▪暂存区中的修改看不见了。

▪工作区中已经存在的文件的修改也看不见了。

▪如果使用了-u选项，工作区中[新添加的文件]{.mark}对于工作区也看不见了。

这样工作区就干净多了。使用 git diff 和 git diff \--cached
也看不到工作区和暂存区中的修改了。因为它们都被存储到了一个堆栈中。

然后，我们就可以新建分支，切换到新的分支来处理其他的需求。

**git stash、git stash pus、git stash save的区别**

这三条命令的关系其实是一个**"新旧更替"**的故事。简单来说：git
stash 是最基础的写法，git stash push 是功能更强大的新版标准写法，而 git
stash save 是已经被废弃的旧命令。

为了让你在实际工作中不踩坑，我为你详细拆解它们的区别：

  -----------------------------------------------------------------------
  特性         git stash/git stash push   git stash save
  ------------ -------------------------- -------------------------------
  当前状态     [推荐 (现代标准)]{.mark}   [已废弃 (不推荐)]{.mark}

  语义清晰度   push (推入堆栈)            save (保存)，容易误解为"覆盖"

  添加备注     [git stash push -m         git stash save \"msg\"
               \"msg\"]{.mark}            

  指定文件     支持 (如 git stash push    不支持
               file.js)                   

  底层逻辑     明确的"堆栈"操作           旧版模糊逻辑
  -----------------------------------------------------------------------

**1. git stash与git stash push (本质一样，写法不同)**

在绝大多数情况下，git stash 其实就是 git stash push 的**简写(Alias)**。

- 相同点：它们底层执行的逻辑是一样的，都会将修改压入 stash 堆栈。

- 不同点：git stash push 语法更规范，支持更多参数。

**什么时候必须用 push？**\
当你需要**只暂存部分文件**或者**添加备注**时，必须使用 push 语法：

git stash push path/to/file.js \#*暂存特定文件*

git stash push -m \"正在开发用户模块，暂存\" \#*添加描述信息
(推荐始终加描述)*

**2. git stash save (历史遗留命令)**

这是老版本 Git(2.13 之前)常用的写法。

- 为什么被废弃？

  - 语义不清：save 听起来像是"保存并覆盖"，但实际上它是"暂存并推入堆栈"。push 更符合栈(Stack)的数据结构逻辑。

  - 功能受限：它不支持像 push 那样灵活地指定路径或使用现代参数。

- 现状：虽然现在的 Git
  版本为了兼容性还能运行 save，但官方明确建议不要再使用它，未来版本可能会彻底移除。

**最佳实践建议**

为了保证代码操作的清晰性和可维护性，我建议你遵循以下原则：

**1. 日常暂存：用最简写法**\
如果你只是想快速把所有改动藏起来，直接用最简单的：

git stash

**2. 重要暂存：用 push 并加备注**\
如果你预计这个暂存会放很久，或者有很多暂存记录，**强烈建议加上 -m 备注**，这会让你以后查看 git
stash list 时一目了然：

git stash push -m \"修复支付流程中的空指针异常\"

**3. 选择性暂存：必须用 push**\
如果你修改了 A、B、C 三个文件，只想把 A 文件藏起来，B 和 C
继续留在工作区，这就必须用 push 指定文件路径：

git stash push -m \"先藏起这个复杂的逻辑\" path/to/fileA.js

**总结**

- 不要用：git stash save(过时了，别学了)。

- 可以用：git stash(简单快捷)。

- 推荐用：git stash push -m \"描述\"(规范，且能加备注，防止遗忘)。

你可以把 git stash 理解为"快捷方式"，而 git stash
push 是"完整程序"，两者殊途同归，但后者功能更全。

# 10)历史记录查看

## git blame

\$ git blame
./telephony/java/com/android/internal/telephony/PhoneBase.java

查看这个文件**最新版本**的**每一行最后一次被谁修改**。

\$ git log -p SHA //git blame在每一行行首显示SHA值，结合git log -p
SHA一起使用可以查看到某个提交的修改。

## git log基本用法

选项 说明

-p 按补丁格式显示每个更新之间的差异。

\--stat 显示每次更新的文件修改统计信息。

\--shortstat 只显示 \--stat 中最后的行数修改添加移除统计。

**\--name-status** 显示新增、 修改、 删除的文件清单。

\--name-only 仅在提交信息后显示已修改的文件清单。

\--abbrev-commit 仅显示 SHA-1 的前几个字符， 而非所有的 40 个字符。

\--relative-date 使用较短的相对时间显示(比如， "2 weeks ago") 。

\--graph 显示ASCII图形表示的分支合并历史。

\--pretty 使用其他格式显示历史提交信息。 可用的选项包括 oneline，
short， full， fuller 和format(后跟指定格式) 。

-n 仅显示最近的 n 条提交

\--since, \--after 仅显示指定时间之后的提交。

\--until, \--before 仅显示指定时间之前的提交。

\--author 仅显示指定作者相关的提交。

\--committer 仅显示指定提交者相关的提交。

\--grep 仅显示含指定关键字的提交

-S 仅显示添加或移除了某个关键字的提交

[**git log \[\<options\>\] \[\<revision range\>\]** \[**\[\--\]
\[\<path\>...​\]\]**]{.mark}

\$ git log 查看分支修改记录，显示commit日志。git
log显示在前面的是新的提交、显示在后面的是旧的提交。

[\$ **git log path**
//**path可以是文件名，也可以是目录名，可以是绝对路径，也可以是相对路径**]{.mark}

\$ git log ../dir/test.c //文件

\$ git log ../dir //目录，git log .显示当前目录历史记录，git log
..显示父目录历史记录

\$ git log -4查看分支最近4次修改记录

\$ **git log
-p**按**补丁**格式显示每个提交引入的差异，显示包括修改的具体内容、commit日志等

\$ git log -p filename 查看某个文件filename修改的具体内容

\$ git log -2 -p查看最近2次修改的具体内容。注意这里参数顺序-2
-p，不能把-p放到-2之前。

\$ git log **SHA**  从SHA提交开始显示修改记录(SHA 及比SHA 更早的提交)

\$ git log SHA -2  从SHA提交开始显示修改记录(共两次提交)

\$ git log -p SHA从SHA提交开始显示修改记录、并且显示修改的具体内容

\$ git log -2 -p SHA

[\$ **git log \--author=\"username\"** //查看某人的修改内容]{.mark}

[\$ git log \--author=**\"John\\\|Mary\"**]{.mark}

[\$ git log \--name-status
//显示新增、修改、删除的文件清单，比\--name-only更好，推荐。]{.mark}

[\$ git log \--name-only //仅在提交信息后显示已修改的文件清单。]{.mark}

[\$ **git log**
**branchname**查看某个分支修改记录，可特别的选定某一个分支]{.mark}

如果当前在newbranch分支，那么我想查看master分支和issue分支，怎么办？

\$ git log master

\$ git log issue

\$ git-2 -p log issue

**[\$ git log -2 -p branch path//各种组合]{.mark}**

**[\$ git log -1 -p master
develop_enviroment/envsetup_modified.sh]{.mark}**

错误用法：

\$ git log -p master develop_enviroment/envsetup_modified.sh -1

fatal: 选项 \'-1\' 必须在其他非选项参数之前

\$ git log master develop_enviroment/envsetup_modified.sh -p

fatal: 选项 \'-p\' 必须在其他非选项参数之前

**[结论：path要放到最后]{.mark}**

**\[\--\] \<path\>...**​

Consider only commits that are enough to explain how the files that
match the specified paths came to be.

Paths may need to be prefixed with \-- to separate them from options or
the revision range, when confusion arises.

**\--的用法**

有时你可能只对某个文件的修改感兴趣，或你只想查看跟某个文件相关的历史信息，你只需要插入你感兴趣文件的路径就可以了。

比如：git log \-- foo.py bar.py
，只返回和foo.py文件或bar.py文件的相关commit。

这里的\--是告诉git，后面的参数是文件路径而不是branch的名字。如果后面的文件路径不会和某个branch产生混淆，你可以省略\--，比如git
log foo.py。

另外，后边的路径还支持正则，比如：git log \*install.md
，是指定项目路径下的所有以install.md结尾文件的提交历史。

另外，文件名应该放到参数的最后位置，通常在前面加上\--并用空格隔开表示是文件。

另外，git log file/，可以查看file文件夹下所有文件的提交记录。

\--branchName
branchName参数：为任意一个分支名字，查看某个分支上的提交记录。

需要放到参数中的最后位置处。

如果分支名与文件名相同，系统会提示错误，可通过\--选项，来指定给定的参数，是分支名还是文件名。

比如：在当前分支中有一个名为v1的文件，同时还存在一个名为v1的分支。如下：

git log v1 \--，此时的v1代表的是分支名字(\--后边是空的)。

git log \-- v1，此时的v1代表的是名为v1的文件。

git log v1 \-- v1：代表v1分支下的v1文件

**\$ git log SHA -cnt -p \--graph \--author=name \--name-only \--oneline
branch path**

**语法：path放最后，branch放path前面，其他选项放在branch和path的前面，SHA紧跟在git
log后面。**

这个格式包含了大部分git
log的用法，可以作为一个**万能公式**，实际使用时按需要从这个格式里面减掉不需要的选项或path参数。path可以是文件名也可以是目录名,可以是相对路径也可以是绝对路径。

\$ git log 7e483ce9778b56f12ed5bf727533010a1626797f -2 -p master
develop_enviroment/envsetup_modified.sh

\$ git log 7e483ce9778b56f12ed5bf727533010a1626797f -2 -p \--graph
master develop_enviroment/envsetup_modified.sh

\$ git log 7e483ce9778b56f12ed5bf727533010a1626797f -2 \--graph
\--author=gaheadus \--name-only \--oneline master
develop_enviroment/envsetup_modified.sh

## git log -p path//很有用

\$ git log -p
./telephony/java/com/android/internal/telephony/PhoneBase.java

查看修改过这个文件的所有提交以及每次提交所修改的内容。git log -p比git
blame对修改内容的显示更详细

\$ git log -p
ca82a6dff817ec66f44342007202690a93763949//显示某次及以前提交的详细修改内容

## git log \--name-status / \--name-only //很有用

\$ **git log \--name-status -3**

commit f76f5db49edbda14aa1acf7e8299143abdb51147

Author: dukang \<gaheadus@126.com\>

Date: Tue Apr 4 23:43:04 2023 +0800

git：增加图片

A Resources/git仓库与分支模型.jpg

A Resources/git仓库的结构.png

A Resources/git版本库.png

M tools_and_skills/git使用.md

commit 63560da9be582ee16adb114edfdadea0500672ae

Author: dukang \<gaheadus@126.com\>

Date: Fri Mar 24 21:48:35 2023 +0800

更正一处错误

M tools_and_skills/git使用.md

\$ **git log \--name-only -3**

commit f76f5db49edbda14aa1acf7e8299143abdb51147

Author: dukang \<gaheadus@126.com\>

Date: Tue Apr 4 23:43:04 2023 +0800

git：增加图片

Resources/git仓库与分支模型.jpg

Resources/git仓库的结构.png

Resources/git版本库.png

tools_and_skills/git使用.md

commit 63560da9be582ee16adb114edfdadea0500672ae

Author: dukang \<gaheadus@126.com\>

Date: Fri Mar 24 21:48:35 2023 +0800

更正一处错误

tools_and_skills/git使用.md

name-status显示文件的修改状态，name-only只显示修改过的文件，**推荐使用name-status**。

## git log显示格式控制/定制显示内容

**git log \--pretty=oneline** //按一行输出，显示完整SHA

**git log \--oneline** //按一行输出，显示简短SHA

**git log -4 \--pretty=format:\"%h, %s, %ae, %cd\"**
//关注的内容：哈希值, 提交注释, 作者邮箱, 提交日期

**git log -4 \--formate=format:\"%h, %s, %ae, %cd\"** //一样

git
log可以使用**\--pretty=format:\"\<string\>\"**选项，可以像printf一样的占位符来输出提交。

比如，下面命令中的%H、%cn、%cd这三种占位符会被分别替换为提交的SHA、作者名字、提交日期。

\$ **git log \--pretty=format:\"%h, %s, %ae, %cd\" -4**

f76f5db, git：增加图片, gaheadus@126.com, Tue Apr 4 23:48:13 2023 +0800

63560da, 更正一处错误, gaheadus@126.com, Fri Mar 24 21:48:35 2023 +0800

c1f8d4d, 新增单词, gaheadus@126.com, Sat Feb 11 21:47:00 2023 +0800

3d19619, 调整，全部专业英语单词放在一个sourceinsight工程,
gaheadus@126.com, Mon Dec 5 23:23:56 2022 +0800

双引号里面可以指定显示的字符：

\$ **git log \--pretty=format:\"%h, 标题:%s, 邮箱:%ae, %cd\" -4**

f76f5db, 标题:git：增加图片, 邮箱:gaheadus@126.com, Tue Apr 4 23:48:13
2023 +0800

63560da, 标题:更正一处错误, 邮箱:gaheadus@126.com, Fri Mar 24 21:48:35
2023 +0800

c1f8d4d, 标题:新增单词, 邮箱:gaheadus@126.com, Sat Feb 11 21:47:00 2023
+0800

3d19619, 标题:调整，全部专业英语单词放在一个sourceinsight工程,
邮箱:gaheadus@126.com, Mon Dec 5 23:23:56 2022 +0800

**输出格式中间有空格时，需要加双引号；没有空格，可以不加双引号。**

\$ git log \--pretty=format:\"%H, commiter:%cn,data:%cd\" \--
有空格，要加双引号

\$ git log \--pretty=format:%H,commiter:%cn,data:%cd \--
没有空格，可以不加双引号

**\--pretty=format:\"\<string\>\"** ，可以**定制记录的显示格式**。
这样的输出对后期提取分析格外有用。常用的选项：

%H 提交的完整哈希值

%h 提交的简写哈希值

%T 树的完整哈希值

%t 树的简写哈希值

%P 父提交的完整哈希值

%p 父提交的简写哈希值

%an 作者名字

%ae 作者的电子邮件地址

%ad 作者修订日期([可以用\--date=选项来定制格式]{.mark})

%ar 作者修订日期，按多久以前的方式显示

%cn 提交者的名字

%ce 提交者的电子邮件地址

%cd 提交日期([可以用\--date=选项来定制格式]{.mark})

%cr 提交日期(距今多长时间)

[%d 见后面\--decorate]{.mark}

%s 提交说明

%Cred 切换到红色

%Cgreen 切换到绿色

%Cblue 切换到蓝色

%Creset 重设颜色

%C(\...) 制定颜色, as described in color.branch.\* config option

%m left, right or boundary mark

%n 换行

%% a raw %

%x00 print a byte from a hex code

%w(\[\<w\>\[,\<i1\>\[,\<i2\>\]\]\]) switch line wrapping, like the -w
option of git-shortlog(1).

你一定奇怪 **作者** 和 **提交者** 之间究竟有何差别，其实作者指的是实际作出修改的人，提交者指的是最后将此工作成果提交到仓库的人。所以，当你为某个项目发布补丁，然后某个核心成员将你的补丁并入项目时，你就是作者，而那个核心成员就是提交者。我们会在[分布式git](https://git-scm.com/book/zh/v2/ch00/ch05-distributed-git)再详细介绍两者之间的细微差别。

参考：https://git-scm.com/docs/pretty-formats、https://git-scm.com/docs/git-config

**能设置的颜色值包括：reset(默认的灰色), red, green, blue, yellow**

cygwin终端实际显示效果如下：

\$ git log \--pretty=format:\"%h, %Cblue%s, %ae, %cd\"
\--date=format:\"%x-%X\" -4

![](media/image237.png){width="4.227083333333334in"
height="0.5020833333333333in"}

\$ git log \--pretty=format:\"%h, %Cblue%s, %Cred%ae, %Creset%cd\"
\--date=format:\"%x-%X\" -4

![](media/image238.png){width="4.720138888888889in"
height="0.4708333333333333in"}

颜色可以用RGB指定，格式：%C(#RGB)

\$ git log -4 \--color \--graph \--pretty=format:\"%h, %C(#4169e1)%s,
%Creset%ae, %cd\" \--date=format:\"%x-%X\" //推荐颜色

![](media/image239.png){width="5.694444444444445in" height="0.4875in"}

\$ git log -4 \--color \--graph \--pretty=format:\"%h, %C(#FF33FF)%s,
%Creset%ae, %cd\" \--date=format:\"%x-%X\"

![](media/image240.png){width="5.584027777777778in"
height="0.4777777777777778in"}

\$ git log -4 \--color \--graph \--pretty=format:\"%h, %C(#00FFFF)%s,
%Creset%ae, %cd\" \--date=format:\"%x-%X\"

![](media/image241.png){width="5.454166666666667in"
height="0.45902777777777776in"}

可以设置字体，如粗体、斜体等，支持的字体有bold, dim, ul, blink, reverse, italic,
and strike。

例：%Cblue，%C(bold blue)，%C(bold #FF33FF)

### \*推荐显示方式

git log \--color \--graph \--pretty=format:\"%C(#bfa400)%h,
%C(#4169e1)%s, %C(#bfa400)%d%C(reset), %Creset%ae, %cd\"
\--date=format:\"%x-%X\"

可以将指定格式设置一个别名：

git config \--global alias.lg \'log \--color \--graph
\--pretty=format:\"%C(#bfa400)%h, %C(#4169e1)%s, %C(#bfa400)%d%C(reset),
%Creset%ae, %cd\" \--date=format:\"%x-%X\"\'

之后使用git lg就可以查看log了。

![](media/image242.png){width="5.603472222222222in"
height="1.8902777777777777in"}

git log \--graph \--format=format:\'%C(bold blue)%h%C(reset) -
%C(white)%an%C(reset)%C(bold yellow)%d%C(reset) %C(white)- %s%C(reset),
%C(dim yellow)(%cd)%C(reset)\' \--date=format:\"%x-%X\" \--all

![](media/image243.png){width="4.903472222222222in"
height="1.4513888888888888in"}

**日期时间显示方式指定：**

%ad、%cd都可以使用\--date=format:\'string\'来设定日期显示方式。

\$ **git log \--pretty=format:\"%h, %s, %ae, %cd\"
\--date=format:\"%x-%X\" -4**
//单引号双引号都可以\--date=format:\'%x-%X\'、\--date=format:\"%x-%X\"

f76f5db, git：增加图片, gaheadus@126.com, 04/04/23-23:48:13

63560da, 更正一处错误, gaheadus@126.com, 03/24/23-21:48:35

c1f8d4d, 新增单词, gaheadus@126.com, 02/11/23-21:47:00

3d19619, 调整，全部专业英语单词放在一个sourceinsight工程,
gaheadus@126.com, 12/05/22-23:23:56

\--date=
(relative\|local\|default\|iso\|rfc\|short\|raw)，定制后边如果出现%ad或%cd时的日期格式。选项：\
\--date=relative：shows dates relative to the current time, e.g. \"2
hours ago\".\
\--date=local：shows timestamps in user's local timezone.\
\--date=iso (or \--date=iso8601)：shows timestamps in ISO 8601 format.\
\--date=rfc (or \--date=rfc2822)：shows timestamps in RFC 2822
format,often found in E-mail messages.\
\--date=short：shows only date but not time, in YYYY-MM-DD
format.这个挺好用\
\--date=raw：shows the date in the internal raw git format %s %z
format.\
\--date=default：shows timestamps in the original timezone (either
committer's or author's).\
也可以自定义格式(git 2.6.0以上)，比如\--date=format:\'%Y-%m-%d
%H:%M:%S\' 会格式化成：2016-01-13 11:32:13，其他的格式化占位符如下：\
%a：Abbreviated weekday name\
%A：Full weekday name\
%b：Abbreviated month name\
%B：Full month name\
%c：Date and time representation appropriate for locale\
%d：Day of month as decimal number (01 -- 31)\
%H： Hour in 24-hour format (00 -- 23)\
%I：Hour in 12-hour format (01 -- 12)\
%j：Day of year as decimal number (001 -- 366)\
%m：Month as decimal number (01 -- 12)\
%M：Minute as decimal number (00 -- 59)\
%p：Current locale\'s A.M./P.M. indicator for 12-hour clock\
%S：Second as decimal number (00 -- 59)\
%U：Week of year as decimal number, with Sunday as first day of week (00
-- 53)\
%w：Weekday as decimal number (0 -- 6; Sunday is 0)\
%W：Week of year as decimal number, with Monday as first day of week (00
-- 53)\
%x：Date representation for current locale\
%X：Time representation for current locale\
%y：Year without century, as decimal number (00 -- 99)\
%Y：Year with century, as decimal number\
%z, %Z：Either the time-zone name or time zone abbreviation, depending
on registry settings; no characters if time zone is unknown\
%%：Percent sign

## git log \--graph / \--decorate

\$ **git log \--graph**
//**以ASCII树状图形式展示提交历史和分支合并历史**。

\$ git log \--oneline -20 \--all \$ git log \--oneline -20 \--all
\--graph

![](media/image244.png){width="3.451388888888889in"
height="1.9770833333333333in"}、![](media/image245.png){width="3.3819444444444446in"
height="2.0555555555555554in"}

\*表示一个提交；\|表示分支前进；/表示分叉；\\表示合入。

**\$ git log
\--decorate**//**显示分支和标签的名称。显示指向这个提交的所有引用，比如说HEAD指针、分支、标签等**。

默认打开了\--decorate选项，不需要明确打开。只在定制显示方式的情况下需要明确打开。

在\--pretty=format:\"\<string\>\"定制显示格式中，%d表示\--decorate。

\$ git log \--color \--graph \--pretty=format:\"%C(#bfa400)%h,
%C(#4169e1)%s, %Creset%ae, %cd\" \--date=format:\"%x-%X\" -10

![](media/image246.png){width="6.263888888888889in" height="1.04375in"}

\$ git log \--color \--graph \--pretty=format:\"%C(#bfa400)%h,
%C(#4169e1)%s, %C(#bfa400)%d%C(reset), %Creset%ae, %cd\"
\--date=format:\"%x-%X\" -10

![](media/image247.png){width="6.331944444444445in"
height="1.1041666666666667in"}

## git log \--all

git log 仅显示当前分支的提交历史。

git log
\--all 显示**所有分支和标签**的提交历史，包括本地分支(refs/heads/)、远程跟踪分支(refs/remotes/)、已删除的分支、标签(refs/tags/)等 refs/ 目录下的所有引用。包括：

- 所有本地分支：不仅限于当前所在的分支，而是显示所有本地分支的提交记录。

- 远程分支：显示从远程仓库获取的所有远程分支的提交历史。

- 已删除的分支：通常，已删除分支的提交历史在分支被删除后仍然保留在仓库中，\--all选项会显示这些提交。

- 标签：显示指向提交的所有标签。

通过使用\--all选项，可以获得项目完整的提交历史视图，了解各个分支的演变和合并情况。

**注意事项**

- 不包含悬空提交：未被任何引用直接或间接指向的提交(如 git
  commit 后未添加到分支的提交)不会显示。

- \--all与 \--branches、\--tags 的区别：\--all 更全面，包括所有引用类型，而 \--branches 仅限分支，\--tags 仅限标签。

- 信息量大：由于\--all显示所有提交历史，输出可能非常庞大，特别是在大型项目中。

\$ git log \--graph \--decorate \--oneline -20 \$ git log \--graph
\--decorate \--oneline -20 \--all

![](media/image248.png){width="3.314583333333333in"
height="1.8305555555555555in"}、![](media/image249.png){width="3.265972222222222in"
height="1.9847222222222223in"}

没有分支线、 有分支线

## git log \--simplify-by-decoration，只显示被branch或tag引用的commit

\--simplify-by-decoration：只显示被branch或tag引用的commit

![](media/image250.png){width="3.3375in" height="0.43194444444444446in"}

## git log \--diff-filter，查看文件的增加/删除/修改

git log \--diff-filter=D \--summary \| grep delete，查看所有删除文件

git log \--diff-filter=D \--summary \| grep -C 10
\<file_name\>，查看文件是哪个提交删除的。注意file_name只写文件名，不要写文件所在的路径。

git log \--diff-filter=A \--summary \| grep -C 10
\<file_name\>，查看文件是哪个提交增加的

[\--diff-filter]{.mark}=\[(A\|C\|D\|M\|R\|T\|U\|X\|B)\...\[\*\]\]

Select only files that are Added (**A**), Copied (**C**), Deleted
(**D**), Modified (**M**), Renamed (**R**), have their type (i.e.
regular file, symlink, submodule, \...) changed

(**T**), are Unmerged (**U**), are Unknown (**X**), or have had their
pairing Broken (**B**). Any combination of the filter characters
(including none) can be used. When **\***

(All-or-none) is added to the combination, all paths are selected if
there is any file that matches other criteria in the comparison; if
there is no file that matches other criteria, nothing is selected.

Also, these upper-case letters can be downcased to [exclude]{.mark}.
E.g. [\--diff-filter]{.mark}**=ad** excludes added and deleted paths.

Note that not all diffs can feature all types. For instance, copied and
renamed entries cannot appear if detection for those types is disabled.

git log \--diff-filter=D \--summary \| grep -C 10 example.c

## git log其他

定位具体的历史记录

\$ git log V3..V7 //显示V3之后直至V7的所有历史记录(V3，V7是之前用git
tag打上的tag)

\$ git log V3.. //显示所有 V3
之后的历史记录。注意\<since\>..\<until\>中任何一个被省略

都将被默认设置为 HEAD。所以如果使用..\<until\>的话，git log
在大部分情况下会输出空的。

\$ git log -since="2 weeks ago" //显示 2
周前到现在的所有历史记录。具体语法可查询git-ref-parse 命令的帮助文件。

\$ git log stable..experimental //将显示在 experimental 分支但不在
stable 分支的历史记录

\$ git log experimental..stable //将显示在 stable 分支但不在
experimental 分支的历史记录

git log tag1..tag2              查看两个tag之间的日志。

git log -p tag1..tag2 file    查看一个文件在两个tag之间的不同。

git log tag..                   查看tag和HEAD之间的不同。

过滤合并提交

git
log输出时默认包括合并提交。但是，如果你的团队采用强制合并策略(意思是merge你修改的上游分支而不是将你的分支rebase到上游分支)，你的项目历史中会有很多外来的提交。

你可以通过\--no-merges标记来排除这些提交：

git log \--no-merges

另一方面，如果你只对合并提交感兴趣，你可以使用\--merges标记：

git log \--merges

它会返回所有包含两个父节点的提交。

## git shortlog

git shortlog是用于创建发布公告的一种特殊的git
log命令。按作者对每个提交分组，并展示每个提交信息的第一行。这种方式能很容易看出谁参与了工作。

例如，两个开发者向一个项目贡献了五次提交，git
shortlog的输出会像下面这样：

Mary (2):

Fix a bug in the feature

Fix a serious security hole in our framework

John (3):

Add the initial code base

Add a new feature

Merge branch \'feature\'

通常，git
shortlog会按照作者的名字来排序，但你也可以通过-n选项来按照每个作者的提交数量排序。

\$ git shortlog -h

usage: git shortlog \[\<options\>\] \[\<revision-range\>\] \[\[\--\]
\[\<path\>\...\]\]

-n, \--numbered sort output according to the number of commits per
author

-s, \--summary Suppress commit descriptions, only provides commit count

-e, \--email Show the email address of each author

-w\[\<w\[,i1\[,i2\]\]\>\] Linewrap output

\$ git shortlog -s

236 DuKang

26 dukang

70 gaheadus

1 hahahah

2 haloooooooooo

3 就是你大爷

1 康大爷

## git ls-files

git
ls-files，显示索引和工作树中的文件信息。可以用来查看哪些文件被添加到git库管理中了。

git ls-files -t，展示所有 tracked 的文件

git ls-files \--others，展示所有 untracked 的文件

git ls-files \--others -i \--exclude-standard，展示所有忽略的文件

git status \--ignored，展示所有忽略的文件

git ls-files \[-z\] \[-t\] \[-v\] \[-f\]

(\--\[cached\|deleted\|others\|ignored\|stage\|unmerged\|killed\|modified\])\*

(-\[c\|d\|o\|i\|s\|u\|k\|m\])\*

\[\--eol\]

\[-x \<pattern\>\|\--exclude=\<pattern\>\]

\[-X \<file\>\|\--exclude-from=\<file\>\]

\[\--exclude-per-directory=\<file\>\]

\[\--exclude-standard\]

\[\--error-unmatch\] \[\--with-tree=\<tree-ish\>\]

\[\--full-name\] \[\--recurse-submodules\]

\[\--abbrev\] \[\--\] \[\<file\>...​\]

## 过滤提交历史

格式化提交输出只是git
log其中的一个用途。另一半是理解如何浏览整个提交历史。接下来的文章会介绍如何用git
log选择项目历史中的特定提交。所有的用法都可以和上面讨论过的格式化选项结合起来。

**按数量**

git
log最基础的过滤选项是限制显示的提交数量。当你只对最近几次提交感兴趣时，它可以节省你一页一页查看的时间。

你可以在后面加上-\<n\>选项。比如说，下面这个命令会显示最新的3次提交：

git log -3

**按日期**

如果你想要查看某一特定时间段内的提交，你可以使用\--after 或 \--before 标记来按日期筛选。它们都接受好几种日期格式作为参数。比如说，下面的命令会显示2014年7月1日后(含)的提交：

git log \--after=\"2014-7-1\"

你也可以传入相对的日期，比如一周前(\"1 week
ago\")或者昨天(\"yesterday\")：

get log \--after=\"yesterday\"

你可以同时提供\--before 和 \--after 来检索两个日期之间的提交。比如，为了显示2014年7月1日到2014年7月4日之间的提交，你可以这么写：

git log \--after=\"2014-7-1\" \--before=\"2014-7-4\"

注意\--since 、\--until 标记和\--after 、\--before标记分别是等价的。

**按作者**

当你只想看某一特定作者的提交的时候，你可以使用\--author标记。它接受正则表达式，返回所有作者名字满足这个规则的提交。如果你知道那个作者的确切名字你可以直接传入文本字符串：

git log \--author=\"John\"

它会显示所有作者叫John的提交。作者名不一定是全匹配，只要包含那个子串就会匹配。

你也可以用正则表达式来创建更复杂的检索。比如，下面这个命令检索名叫Mary或John的作者的提交。

git log \--author=\"John\\\|Mary\"

注意作者的邮箱地址也算作是作者的名字，所以你也可以用这个选项来按邮箱检索。

如果你的工作流区分提交者和作者，\--committer也能以相同的方式使用。

**按提交信息**

按提交信息来过滤提交，你可以使用\--grep标记。它和上面的\--author标记差不多，只不过它搜索的是提交信息而不是作者。

比如说，你的团队规范要求在提交信息中包括相关的issue编号，你可以用下面这个命令来显示这个issue相关的所有提交：

git log \--grep=\"JRA-224:\"

你也可以传入-i参数来忽略大小写匹配。

区分：

\$ git grep \"Hello\" //从当前目录的所有文件中查找文本内容

\$ git grep \"Hello\" v2.5 //在某一版本中搜索文本

**按文件**

很多时候，你只对某个特定文件的更改感兴趣。为了显示某个特定文件的历史，你只需要传入文件路径。比如说，下面这个命令返回所有和foo.py和bar.py文件相关的提交：

git log \-- foo.py bar.py

\--告诉git
log接下来的参数是文件路径而不是分支名。如果分支名和文件名不可能冲突，你可以省略\--。

**按内容**

我们还可以根据源代码中某一行的增加和删除来搜索提交。这被称为pickaxe，它接受形如-S\"\<string\>\"的参数。比如说，当你想要知道Hello,
World!字符串是什么时候加到项目中哪个文件中去的，你可以使用下面这个命令：

git log -S \"Hello, World!\"

如果你想用正则表达式而不是字符串来搜索，你可以使用-G\"\<regex\>\"标记。

这是一个非常强大的调试工具，它能让你定位到所有影响代码中特定一行的提交。它甚至可以让你看到某一行是什么时候复制或者移动到另一个文件中去的。

**按范围**

你可以传入范围来筛选提交。这个范围由下面这样的格式指定，其中\<since\>和\<until\>是提交的引用：

git log \<since\>..\<until\>

这个命令在你使用分支引用作为参数时特别有用。这是显示两个分支之间区别最简单的方式。看看下面这个命令：

git log master..feature

其中的master..feature范围包含了在feature分支而不在master分支中所有的提交。换句话说，这个命令可以看出从master分支fork到feature分支后发生了哪些变化。它可以这样可视化：

注意如果你更改范围的前后顺序(feature..master)，你会获取到master分支而非feature分支上的所有提交。如果git
log输出了全部两个分支的提交，这说明你的提交历史已经分叉了。

**过滤合并提交**

git
log输出时默认包括合并提交。但是，如果你的团队采用强制合并策略(意思是merge你修改的上游分支而不是将你的分支rebase到上游分支)，你的项目历史中会有很多外来的提交。

你可以通过\--no-merges标记来排除这些提交：

git log \--no-merges

另一方面，如果你只对合并提交感兴趣，你可以使用\--merges标记：

git log \--merges

它会返回所有包含两个父节点的提交。

## 如何快速查看某一行是谁修改的？

\$ git blame testfile.txt \| grep \"changed text\"
//查找是哪个提交修改了\"changed text\"，git blame会显示提交的SHA

\$ git log -p SHA //查看对应提交的修改的具体内容。

## git show

git
show后可以是[文件名、提交、分支名、tag名、stash等]{.mark}，用于查看文件、提交、分支、tag、stash的修改内容。

\$ git show SHA

[\$ git show SHA file //查看指定提交的指定文件的修改]{.mark}

\$ git show file //文件，或者路径，git show path

\$ git show branch_name

\$ git show tag_name

\$ git show stash@{0}

和git log一样，可以使用\--name-status、\--name-only、-p等参数

\$ git show SHA \--name-status

\$ git show stash@{n} \--name-status

如果你想要显示一个分支的最后一次提交的对象，例如假设 topic1 分支指向
ca82a6d，那么下面的命令是等价的：

\$ git show ca82a6dff817ec66f44342007202690a93763949

\$ git show topic1

\$ git show-branch \--more=n \# 前n个提交历史信息

我们可以使用 git show 再加上述的 commit 名称来显式更详细的 commit 信息：

\$ git show 5b888402aadd3cd41b3fe8c84a8658da07893b20

你完全可以用一个最短的且唯一的"名称前几个字符"来只待某次 commit：

\$ git show 5b888 //只要能区别与其他名称就足够了

使用 git show 加分支名称，亦可以显示分支信息：

\$git show master

\$git show experimental

使用 HEAD 字段可以代表当前分支的头(也就是最近一次 commit)：

\$git show HEAD

每一次 commit 都会有"parent commit"，可以使用\^表示 parent：

\$git show HEAD\^ //查看HEAD的父母的信息

\$git show HEAD\^\^ //查看HEAD的父母的父母的信息

\$git show HEAD\~4 //查看HEAD上溯 4 代的信息

要注意的是 git-merge 是会产生双父母的，这种情况这样处理：

\$git show HEAD\^1 //查看HEAD的第一个父母

\$git show HEAD\^2 //查看HEAD的第二个父母

如果你在引用最后加上一个\^，git将其理解为此次提交的父提交。

\$ git show HEAD\^

你也可以在\^后添加一个数字------例如，d921970\^2 意思是"d921970
的第二父提交"。

这种语法只在合并提交时有用，因为合并提交可能有多个父提交。第一父提交是你合并时所在分支，而第二父提交是你所合并的分支：

## git reflog

git reflog 查看引用日志

使用git reset撤消commit后，git
log无法看到撤消掉的commit历史，但可以用reflog命令看到。

如果想恢复reset撤销掉的commit，可以使用reflog查看对应的sha值，然后使用cherry-pick或merge合并到当前分支。

git reflog -n 10

ssssgit reflog \--date=iso

git reflog \--date=iso \| grep \"2026\" \# 按时间范围筛选

git reflog \--grep=\"checkout\" \# 查找所有切换分支记录

恢复误删分支‌\
即使分支已被 git branch -D 删除，只要reflog未过期：

git reflog show refs/heads/feature/login *\# 查看被删分支的 reflog*

git branch feature/login \<commit-hash\> *\# 重建分支*

## 版本回退

有时候碰到新版本出了问题，直接定位问题比较困难，此时可以回退到指定的历史版本。例如回退到某个时间点的版本。

### 回退到指定时间的版本

repo回退当前分支下所有仓库到指定日期前的最新代码版本，<http://blog.chinaunix.net/uid-31390529-id-5761908.html>

执行下面这样的repo命令：

**\$ repo forall -c \'commitID=\`git log \--before \"2017-03-17 07:00\"
-1 \--pretty=format:\"%H\"\`; git reset \--hard \$commitID\'**

**\$ repo forall -c git reset \--hard \`git log \--before \"2017-03-17
07:00\" -1 \--pretty=format:\"%H\"\`**

参数说明：

forall　　操作分支中的所有仓库

-c　　 命令

\--before　　早于指定时间点的提交记录

-1　　 只显示最近的1条记录(注意这是数字1 ，如果要显示2条就写2，以此类推)

\"2017-03-17 07:00\"　　希望回退到的日期(时间点)

\--pretty　　以指定格式显示提交记录

%H　　 提交记录的hash值，即commit id，见git log

解释：这条repo命令的实质就是在当前分支的每个仓库下执行git
log命令，找出该仓库下符合时间条件的第一个提交记录，然后对该仓库执行git
reset \--hard操作。

### 多分支merge的情况下版本回退

**\$ git log \--graph
\--pretty=format:%h,%Cred%an,%cn,%Cgreen%cd,%Cblue%s**

\* 797e4b8,DuKang,DuKang,Mon Dec 16 00:46:27 2019 +0800,new modify

\* 335243f,DuKang,DuKang,Mon Dec 16 00:45:06 2019 +0800,new modify

\* c0a51f4,DuKang,DuKang,Mon Dec 16 00:35:06 2019 +0800,Merge branch
\'master\' of ...

\|\\

\| \* a1d6075,zhanglong, zhanglong,Mon Dec 16 00:28:53 2019
+0800,omnipeek modify

\* \| f59da50,DuKang,DuKang,Mon Dec 16 00:33:36 2019 +0800,omnipeek
modify

\|/

\* cfb5b35,DuKang,DuKang,Sat Dec 14 00:58:06 2019 +0800,Merge branch
\'master\' of ...

\|\\

\| \* 29b1ad9,zhanglong,zhanglong,Sat Dec 14 00:55:10 2019 +0800,Merge
branch \'master\' of ...

\| \|\\

\* \| \\ 8a39d54,DuKang,DuKang,Sat Dec 14 00:57:33 2019 +0800,Merge
branch \'master\' of ...

\|\\ \\ \\

\| \|/ /

\|/\| /

\| \|/

\| \* b7bfc68,wanggang,wanggang,Sat Dec 14 00:50:35 2019 +0800,Merge
branch \'master\' of ...

\| \|\\

\* \| \\ 21d867c,DuKang,DuKang,Sat Dec 14 00:54:50 2019 +0800,Merge
branch \'master\' of ...

\|\\ \\ \\

\| \|/ /

\|/\| /

\| \|/

\| \* bf6f330,liming,liming,Sat Dec 14 00:43:00 2019 +0800,\--no-edit

\* \| d72fb25,DuKang,DuKang,Sat Dec 14 00:49:00 2019 +0800,\--no-edit

\|/

\* 608e1c4,DuKang,DuKang,Sat Dec 14 00:36:12 2019 +0800,add wireshark
usage

\* 4d22b06,DuKang,DuKang,Fri Dec 13 00:32:01 2019 +0800,Merge branch
\'master\' of ...

多人开发，各自本地建立不同的分支，多个分支合并到服务器库上分支。

在版本回退时，**应该回退到服务器库上分支的结点(包括merge到库上分支的结点)**，才是**服务器库上代码的状态**。例如上述797e4b8、cfb5b35、8a39d54等结点。

如果回退到**非服务器库上分支的结点**，如上述29b1ad9、b7bfc68等，就会**处于其他人本地电脑中分支代码的状态，而不是服务器库上代码的状态**。例如回退到29b1ad9就会**处于zhanglong本地电脑中代码的状态**，回退到b7bfc68就会**处于wanggang本地电脑中代码的状态**，都**不是服务器库上代码的状态**。

git
log看到的节点，包括个人本地电脑上分支的节点，和服务器上分支的节点。要用**git
log
\--graph点线图**才能**区分哪些节点是服务器上分支的节点、哪些是个人本地电脑上分支的节点**。

注：①版本回退使用git reset \--hard SHA命令。

### 多分支merge的情况下版本回退2

接上面内容，节点c0a51f4由两个分支合并而成，它有两个父提交，怎么回退到指定父提交所在的分支？

git reset \--hard f59da50是回退到分支A ？git reset \--hard
a1d6075是回退到分支B ？

\-- 不是，不能回退到指定分支，只能git checkout
branch在分支之间切换，然后使用git reset \--hard
SHA在分支的节点之间移动，或者使用git checkout SHA在节点之间移动。
参考前面章节内容：git命令操作图示 -\> 两个父提交

git merge:

A\-\--B\-\--C topic

/ \\

D\-\--E\-\--F\-\--G\-\--H master

假设当前在master分支上，HEAD在G，执行git merge
topic，合并topic分支到master分支。

执行git reset B后，master分支的内容如下：

A\-\--B master

/

D

[此时master分支的提交记录和原来topic分支是一样的，但是仍然是在master分支上，并不是在topic分支上]{.mark}。并且，此时对master的修改不会影响topic分支。

git checkout SHA跳出分支后，可以使用git checkout branch回到分支中。

[git reset
SHA不仅可以向后移动，而且是可以向前移动的]{.mark}，如上，假设当前HEAD在H，可以git
reset E回到历史提交，之后可以使用git reset
H回到最新提交。这个容易被忽略。

不论git reset SHA还是git checkout
SHA，都是在已经提交的节点之间移动，并**[不会更改提交历史，已有的提交记录、分支结构，都不会因此而改变]{.mark}**。因此，git
reset SHA、git checkout
SHA后是可以还原到最初状态的，不需要担心破坏提交记录无法还原。最好是使用git
log \--graph \> backup.txt保存一个备份的提交记录，之后就可以使用git
reset SHA、git checkout
SHA在节点之间任意移动了，想要移动到哪个节点可以从备份的backup.txt中取想要的SHA。

### 版本回退的一些经验

怎么回退版本？

每一步操作都要有记录，做到**有记录、可回溯，便于后续分析总结**。

首先将代码更新到最新到最新提交，git log \>
file导出所有提交记录。选择一些关键的提交点进行回退、测试，记录测试结果成功失败、现象是什么。记录就写在这个git
log导出文件中，与SHA值一一对应。20220829

# 11)分支操作

## 分支改名

\$ git branch -m oldName newName

例：

\$ git branch

cat

dog

\*master

\$ git branch -m cat tiger //-m参数表示分支改名，move的意思吗？

\$ git branch

tiger

dog

\*master

master分支名也可以改

\$ git branch -m master slave

\$ git branch

cat

dog

\*slave

## show-branch

git show-branch

git show-branch \--sha1-name

git show-branch \--sha1-name \--more=3

例子

![](media/image251.png){width="5.473611111111111in"
height="2.0180555555555557in"}

![](media/image252.png){width="5.48125in" height="2.6979166666666665in"}

git show-branch 是 Git
中用于查看多个分支的历史提交记录的命令。该命令可以帮助开发者快速了解不同分支之间的提交情况，尤其是在项目中多个分支并行开发时，它可以提供一个清晰的视图，展示各分支的最新提交和合并情况。

git
show-branch非常适合查看分支历史和比较分支之间差异，它能直观地显示出分支之间的交集、差异以及合并点。

git show-branch 是 Git
中一个轻量且非常直观的命令行工具，专门用于快速查看多个分支的提交历史关系。

**1. 基本语法**

[git show-branch \[\<options\>\] \[\<branch\>\...\]]{.mark}

如果不指定分支，默认会显示当前仓库中所有本地分支的提交历史。

**2. 输出结构解析**

执行命令后，输出结果通常分为上下两部分：

- **上半部分(分支头部)**：列出分支名称，[当前分支前用 \* 标记，其他分支用 ! 标记(不同颜色)]{.mark}，后面紧跟该分支最新提交的日志消息。

- **下半部分(提交矩阵)**：按时间倒序排列的提交摘要。左侧使用符号(\*、+、-)表示该提交属于哪些分支。

  - [\*：表示该提交属于当前分支。]{.mark}

  - [+：表示该提交属于对应的非当前分支。]{.mark}

  - [-：表示这是一个合并提交(Merge commit)。]{.mark}

  - [**多列符号**：如果同一行出现多个符号(如 +\*)，说明该提交被多个分支共同指向，是它们的共同祖先或已合并的节点。]{.mark}

**3. 常用选项与参数**

- \--all：显示所有分支的提交历史，包括本地分支和远程追踪分支。

- \--more=\<n\>：[默认情况下命令在显示所有分支的共同祖先时就会停止输出]{.mark}。使用此选项可以[强制多显示 n 个共同祖先之后的提交]{.mark}，方便查看更深的历史记录。

- \--current：将当前分支包含在未在命令行中提供的分支列表中进行比较。

- \--sha1-name：用短SHA-1哈希值替代提交摘要来命名提交，便于比对具体的提交
  ID。

- \--topics：只显示不在第一个指定分支上的提交。这在跟踪主题分支(topic
  branches)时非常有用，可以隐藏已经合并到开发主线中的提交。

- \--merge-base：不显示提交列表，而是确定指定提交的可能合并基础(Merge
  base)。

**4. 常见使用场景示例**

- **查看所有本地分支关系**：

git show-branch

- **比较特定分支**(例如 master 和 develop)：

git show-branch master develop

- **查看包含远程分支的全局关系**：

git show-branch \--all

- **查看更多的历史交集**：

git show-branch \--more=5 master feature

**5. 使用注意事项**

- **数量限制**：该命令一次最多只能显示29个分支和提交。如果分支过多，输出会变得混乱，建议一次只比较2-4个相关的分支。

- **无图形树状图**：show-branch 提供的是半可视化的矩阵视图，不支持像 git
  log \--graph 或 gitk 那样直观的图形化树状连线。

- **合并关系局限**：它无法直接看出 merge commit
  的具体父提交关系，如需详细查看，需结合 git show \<commit\> 命令。

\--阿里通义千问

用法：git show-branch \[-a \| \--all\] \[-r \| \--remotes\]
\[\--topo-order \| \--date-order\]

\[\--current\] \[\--color\[=\<何时\>\] \| \--no-color\] \[\--sparse\]

\[\--more=\<n\> \| \--list \| \--independent \| \--merge-base\]

\[\--no-name \| \--sha1-name\] \[\--topics\]

\[(\<版本\> \| \<通配符\>)\...\]

或：git show-branch (-g \| \--reflog)\[=\<n\>\[,\<起始点\>\]\]
\[\--list\] \[\<引用\>\]

-a, \--\[no-\]all 显示远程跟踪的和本地的分支

-r, \--\[no-\]remotes 显示远程跟踪的分支

\--\[no-\]color\[=\<何时\>\] 着色 \'\*!+-\' 到相应的分支

\--\[no-\]more\[=\<n\>\] 显示共同祖先后的 \<n\> 个提交

\--\[no-\]list 和 more=-1 同义

\--no-name 不显示字符串命名

\--name 与 \--no-name 相反

\--\[no-\]current 包括当前分支

\--\[no-\]sha1-name 以对象名字命名提交

\--\[no-\]merge-base 显示可能合并的基线

\--\[no-\]independent 显示没有任何引用的的引用

\--topo-order 以拓扑顺序显示提交

\--\[no-\]topics 只显示不在第一个分支上的提交

\--\[no-\]sparse 显示仅一个分支可访问的合并提交

\--date-order 拓扑方式排序，并尽可能地保持日期顺序

-g, \--reflog\[=\<n\>\[,\<base\>\]\] 显示从起始点开始的 \<n\>
条最近的引用日志记录

1.命令的基本语法和用法

git show-branch \[\<options\>\] \[\<branch\>\...\]

\<options\>：用于控制命令的行为，过滤和格式化输出。

\<branch\>：指定要显示的分支。如果不指定，git show-branch
会显示当前所有的分支。

常见使用场景

示例 1：查看所有分支的提交

git show-branch

该命令显示当前仓库中所有分支的提交历史。它以图形化的方式展示每个分支的提交记录。

示例 2：查看特定分支的提交

git show-branch master develop

此命令仅展示 master 和 develop
分支的提交历史，便于比较这两个分支的不同。

示例 3：显示分支的提交历史并过滤输出

git show-branch \--more=5

通过 \--more 选项，可以控制输出的提交数量，方便查看更多的历史记录。

2.命令的常用选项及参数

git show-branch
提供了一些有用的选项，可以帮助用户根据需求定制输出内容。以下是一些常见的选项：

\--all：显示所有分支的提交历史，包括本地和远程分支。

git show-branch \--all

\--current：仅显示当前分支的提交历史。

git show-branch \--current

\--more=\<n\>：指定要显示的提交数量，n 是一个数字。默认为
10，可以增加或减少显示的提交数量。

git show-branch \--more=5

\--list：显示简洁的分支信息，包括分支的名称和提交哈希，而不显示具体的提交内容。

git show-branch \--list

\--branches=\<pattern\>：指定要显示的分支，支持通配符。

git show-branch \--branches=feature/\*

\--remotes=\<pattern\>：显示远程分支的提交历史，可以使用通配符来过滤特定的远程分支。

git show-branch \--remotes=origin/feature/\*

4\. 命令的执行示例

示例 1：查看所有分支的提交历史

git show-branch

执行该命令后，Git
会展示所有本地分支的提交历史。每个分支的提交会以不同的符号和颜色标识，以帮助用户区分不同的分支和提交。

示例 2：查看特定分支的提交历史

git show-branch master develop

该命令显示 master 和 develop
两个分支的提交历史，帮助开发者对比这两个分支的变更。

示例 3：查看当前分支与远程分支的差异

git show-branch \--remotes=origin/master \--branches=feature/\*

该命令显示远程 origin/master 分支与本地 feature/\*
分支的提交历史。可以帮助开发者了解本地特性分支与远程主分支之间的差异。

示例 4：查看最近的 5 次提交

git show-branch \--more=5

该命令将展示过去5次提交记录。可以控制输出的提交历史数量，适用于快速浏览历史提交。

5\. 命令的进阶用法

进阶用法 1：比较多个分支的提交

git show-branch feature1 feature2 develop

使用此命令可以查看 feature1、feature2 和 develop
分支的所有提交。输出将直观显示这些分支的提交记录，帮助开发者比较不同分支的进展情况。

进阶用法 2：结合 \--list 和 \--branches 选项查看分支概况

git show-branch \--list \--branches=feature/\*

使用 \--list 选项，可以简洁地查看所有以 feature/
开头的分支的基本信息，包括分支名称和对应的最新提交哈希，而不显示完整的提交内容。

进阶用法 3：结合 \--all 查看所有分支(包括远程分支)

git show-branch \--all

该命令显示当前仓库中所有的分支，包括本地和远程分支，有助于全面了解项目中所有分支的状态。

6\. 命令的常见问题与解答

问题 1：git show-branch 为什么输出的提交记录格式比较复杂？

git show-branch
输出的提交记录格式可能比较复杂，因为它需要在一个表格中显示不同分支的提交记录。这种格式的设计是为了帮助开发者在一个视图中比较不同分支的提交，虽然信息量较大，但它能提供很清晰的分支间差异视图。

问题 2：如何查看所有的远程分支提交？

可以使用 \--remotes
选项来查看远程分支的提交记录，结合通配符可以过滤出特定的远程分支。例如：

git show-branch \--remotes=origin/\*

该命令会显示所有远程分支的提交记录。

问题 3：为什么 git show-branch 显示的提交记录中有时会显示 \* 符号？

在 git show-branch 的输出中，\*
符号表示当前分支。它用于标记当前你所在的分支，以便开发者快速辨认。

7\. 总结与建议

git show-branch
是一个非常有用的命令，特别适合在多人协作和分支管理中，快速查看多个分支的提交记录。它能帮助开发者在并行开发的过程中了解各个分支的进展和差异，尤其在解决合并冲突时，能够快速查看分支历史。

最佳实践建议：

使用 \--branches 和 \--remotes
来过滤需要关注的分支：当分支较多时，可以通过通配符筛选出你关心的分支进行查看。

结合 \--more 和 \--list
选项：当你只关心分支的概况而不需要详细的提交内容时，可以使用
\--list，结合 \--more 控制显示的提交数量。

定期检查分支差异：在合并前，使用 git show-branch
来查看各分支的差异，可以帮助避免冲突。

通过使用 git show-branch，你可以 更高效 地管理 Git 分支，优化开发流程。

\--https://blog.csdn.net/wzt001005/article/details/145923329

## 将一个分支上的修改合并到另一个分支

将一个分支上的修改合并到另一个分支，有4种方法：

32. git merge

33. git rebase

34. git cherry-pick 这三个命令用于同一个文件夹内、不同分支；

35. git format-patch -1, git am **跨文件夹**合并，

## merge

### 冲突解决

**\$ git merge**

**合并中冲突的处理：**

\$ git merge feture1

Auto-merging gameoflife-deploy/pom.xml

CONFLICT (content): Merge conflict in gameoflife-deploy/pom.xml

Automatic merge failed; fix conflicts and then commit the result.

merge命令可以一次性把所有冲突的文件合并，然后提示用户合并冲突去解决。

冲突文件的格式基本如下：

Here are lines that are either unchanged from the common

ancestor, or cleanly resolved because only one side changed.

\<\<\<\<\<\<\< yours:sample.txt

Conflict resolution is hard;

let\'s go shopping.

=======

git makes conflict resolution easy.

\>\>\>\>\>\>\> theirs:sample.txt

And here is another line that is cleanly resolved or unmodified.

\<\<\<\<\<\<\<到=======是在当前分支合并之前的文件内容，

=======到\>\>\>\>\>\>\>是在其它分支下修改的内容，

需要在这个两个版本中选择一个，然后把标记符号也要一起删除。

解决完冲突以后，运行git add命令把文件添加到暂存区，继续执行git merge
\--continue命令编辑新生成的提交的log信息。

需要删掉下面这两行：

Conflicts:

testfile.txt

保存，退出，合并成功。

命令格式：

git merge \[-n\] \[\--stat\] \[\--no-commit\] \[\--squash\]
\[\--\[no-\]edit\]

\[-s \<strategy\>\] \[-X \<strategy-option\>\] \[-S\[\<keyid\>\]\]

\[\--\[no-\]allow-unrelated-histories\]

\[\--\[no-\]rerere-autoupdate\] \[-m \<msg\>\] \[-F \<file\>\]
\[\<commit\>...\]

git merge \--abort

git merge \--continue

**\--abort**

Abort the current conflict resolution process, and try to reconstruct
the pre-merge state.

If there were uncommitted worktree changes present when the merge
started, git merge \--abort will in some cases be unable to reconstruct
these changes. It is therefore recommended to always commit or stash
your changes before running git merge.

git merge \--abort is equivalent to git reset \--merge when MERGE_HEAD
is present.

**\--continue**

After a git merge stops due to conflicts you can conclude the merge by
running git merge \--continue (see \"HOW TO RESOLVE CONFLICTS\" section
below).

## rebase

### 1.base的理解

**base，基，基础，起点。**

**旧的提交是新的提交的base(基)，旧的提交在前、新的提交在后，新的提交建立在旧的提交的基础之上。**

**rebase = re - base = 重新(re)定义基(base)。**

![](media/image253.png){width="2.089583333333333in"
height="1.6791666666666667in"}

图 3-27. 最初分叉的提交历史。

1\. \$git checkout experiment

\$ git rebase master

![](media/image254.png){width="2.8881944444444443in"
height="1.3430555555555554in"}

图 3-29. 把 C3 里产生的改变衍合到 C4 中

**rebase前，c2是c3的base，rebase后，c4变成了c3的base，也就是说重新定义了c3的base，这就是rebase字面上最直观的意义了**。(c3以前的都是c3的base，如c2/c1/c0，rebase后，c4也变成了c3的base了。此时，c3标记为c3',但是c3就是c3'，两者就是同一个东西，这么标记只是为了便于理解。至于c4是放在c2后还是前，还是放在c1后还是前，由其提交时间的先后决定。)

2\. \$ git checkout experiment

\$ git merge master

![](media/image255.png){width="2.80625in" height="1.69375in"}

图 3-28. 通过合并一个分支来整合分叉了的历史

merge，合并是把两个分支的内容取出来合并在一起，并产生一个新的提交c5。

### 用法

\$ git checkout experiment

\$ git rebase master

或者：

\$ git rebase master experiment

使用 git rebase \[basebranch\] \[topicbranch\]
可以直接**[将]{.mark}**特性分支(即本例中的experiment)**[变基到]{.mark}**目标分支(即master)上。这样做能省去你先切换到
experiment分支，再对其执行变基命令的多个步骤。

git rebase B
A，将A分支变基到B分支，A是想要改变基的分支、目标分支，B是基，是A想要变基到的基。

git rebase base topic、git diff base dest，写在前面的是基。

\$ git rebase \--help

Assume the following history exists and the current branch is \"topic\":

A\-\--B\-\--C topic

/

D\-\--E\-\--F\-\--G master

From this point, the result of either of the following commands:

git rebase master

git rebase master topic

would be:

A\'\--B\'\--C\' topic

/

D\-\--E\-\--F\-\--G master

**NOTE:** The latter form is just a short-hand of **git checkout topic**
followed by **git rebase master**. When rebase exits **topic** will
remain the checked-out branch.

### 冲突解决

\$ **git rebase issue1**

First, rewinding head to replay your work on top of it\...

Applying: conflict in master

Using index info to reconstruct a base tree\...

Falling back to patching base and 3-way merge\...

Auto-merging file1_issue1.c

CONFLICT (add/add): Merge conflict in file1_issue1.c

Failed to merge in the changes.

Patch failed at 0001 conflict in master

When you have resolved this problem run \"git rebase \--continue\".

If you would prefer to skip this patch, instead run \"git rebase
\--skip\".

To check out the original branch and stop rebasing run \"git rebase
\--abort\".

\$ **git add file1_issue1.c**

\$ **git rebase \--continue**

二、解决冲突

在rebase的过程中，也许会出现冲突(conflict).
在这种情况，git会停止rebase并会让你去解决
冲突；在解决完冲突后，用\"git-add\"命令去更新这些内容的索引(index),
然后，你**无需**执行git-commit,只要执行:

\$ git rebase \--continue

这样git会继续应用(apply)余下的补丁。

在任何时候，你可以用\--abort参数来终止rebase的行动，并且\"mywork\"
分支会回到rebase开始前的状态。

\$ git rebase \--abort

### 1.git rebase -i, 交互式rebase

#### 将多个提交合并成一个提交

将多个提交合并成一个提交。操作如下：

**\$ git log \--oneline**

f185c6e (HEAD -\> for_rebase, master, for_reset) C5\--Add file5

6d4c76e C4\--Add file4

d8bef46 C3\--Add file3

8ce9fe8 C2\--Add file2

a63777b C1\--Add file1

共有5个提交：C1 🡨 C2 🡨 C3 🡨 C4 🡨 C5。

git log显示的次序为C5 C4 C3 C2
C1，显示在最前面的是最新的提交，再显示倒数第二次提交，从上往下，从新到旧显示。

执行git rebase -i命令：

**\$ git rebase -i HEAD\~3**

弹出编辑框：

pick d8bef46 C3\--Add file3

pick 6d4c76e C4\--Add file4

pick f185c6e C5\--Add file5

\# Rebase 8ce9fe8..f185c6e onto 8ce9fe8 (3 commands)

\#

\# Commands:

\# p, pick = use commit

\# r, reword = use commit, but edit the commit message

\# e, edit = use commit, but stop for amending

\# s, squash = use commit, but meld into previous commit

\# f, fixup = like \"squash\", but discard this commit\'s log message

\# x, exec = run command (the rest of the line) using shell

\# d, drop = remove commit

\#

\# These lines can be re-ordered; they are executed from top to bottom.

\# If you remove a line here THAT COMMIT WILL BE LOST.

\# However, if you remove everything, the rebase will be aborted.

\# Note that empty commits are commented out

编辑框显示的内容是，HEAD到HEAD\~3之间的三次提交C3、C4、C5。

注意git rebase -i SHA的**显示次序和git
log相反，从上往下，从旧到新显示**：C3 C4
C5，显示在前面的是旧的提交、显示在后面的是新的提交。

**git rebase -i
SHA，从最新提交到SHA为止，不包括SHA，区间(SHA,HEAD\]之间的提交**。这里git
rebase -i SHA_C2包括C3 C4 C5，不包括C2。

根据提示，将C4、C5提交前面对应的pick改为squash，表示**将C4、C5合并到提交C3上**，**作为一个提交**。如下：

pick d8bef46 C3\--Add file3

squash 6d4c76e C4\--Add file4

squash f185c6e C5\--Add file5

保存，退出编辑框。小结：**squash,只能将新的提交合并到旧的提交，不能将旧的提交合并到新的提交**。

之后再次弹出编辑框，要求**修改提交信息**。此时的提交信息**包含了原来三次提交的信息**，可以将其删除，改为新的提交信息，这里将提交信息改为：C6\--This
is C6, after do rebase interactively.。

保存，退出编辑框。

**\$ git log \--oneline**

2318afc (HEAD -\> for_rebase) C6\--This is C6, after do rebase
interactively.

8ce9fe8 C2\--Add file2

a63777b C1\--Add file1

可以看到，提交C3、C4、C5没有了，产生一个新的提交C6。C6是将C3、C4、C5三个提交合并后形成的一个新提交。

小结：合并后产生一个新的提交(SHA值变了，和C3的SHA不同了)。

根据提示：# s, squash = use commit, but meld into previous
commit，将某个提交**融合到(meld
into)比自己更早(previous)**的提交上，也就是说**只能将新的提交合并到旧的提交，但是不能将旧的提交合并到新的提交**。上例中**只能将C4、C5合并到C3**，**但反过来不行，不能将C3合并到C4**，否则报错。

**base，基，基础，旧的提交是新的提交的base，只能将新的提交re-base到旧的提交上去，反过来不行。**

也可以使用git reset合并多个提交到一个提交，如下：

**\$ git reset HEAD\~3**

**\$ git add .**

**\$ git commit -m \"C6\--This is C6, after do reset softly.\"**

#### git rebase -i进阶

**\$ git rebase -i \[start\] \[end\] // git rebase -i \[old\] \[new\]**

①**(start,
end\]前开后闭区间**，**从start开始到end为止，不包括start、包括end**。

②**默认省略end，表示当前最新提交HEAD**，**git rebase -i SHA == git
rebase -i SHA HEAD**。

③**从旧到新，start是旧的提交, end是新的提交**，**git rebase -i \[start\]
\[end\] == git rebase -i \[old\] \[new\]。**

[小结：git rebase -i start
end，从左到右，从旧到新，start是旧的提交，end是新的提交；不包括起点start，包括终点end，(start,end\]，**左开右闭**；如果end是HEAD，则可以省略不写，只写start，git
rebase -i start == git rebase -i start HEAD。]{.mark}

例子：

\$ git log \--oneline

d163c5e (HEAD -\> master) C6

2c01406 C5

ce2d3d9 C4

7104d6e C3

7c4912c C2

d319284 C1

**如果想将C3 C4 C5三个提交合并成一个提交，怎么写？ \-- git rebase -i C2
C5**

**git rebase -i new old \-- 错误**

\$ git rebase -i 2c01406 7c4912c // git rebase -i C5 C2

打开编辑器之后，**报错**，如下：

noop

\# rebase 2c01406..7c4912c onto 2c01406 (1 command)

退出编辑器之后，跳出分支，处于detached状态。

\$ git branch

\* (HEAD detached at 2c01406)

master

**git rebase -i old new \-- 正确**

\$ git rebase -i 7c4912c 2c01406 // **git rebase -i C2 C5**

pick 7104d6e C3

pick ce2d3d9 C4

pick 2c01406 C5

\# Rebase 7c4912c..2c01406 onto 7c4912c (3 commands)

\#

\# Commands:

\# p, pick \<commit\> = use commit

\# r, reword \<commit\> = use commit, but edit the commit message

\# e, edit \<commit\> = use commit, but stop for amending

\# s, squash \<commit\> = use commit, but meld into previous commit

\# f, fixup \<commit\> = like \"squash\", but discard this commit\'s log
message

\# x, exec \<command\> = run command (the rest of the line) using shell

\# b, break = stop here (continue rebase later with \'git rebase
\--continue\')

\# d, drop \<commit\> = remove commit

\# l, label \<label\> = label current HEAD with a name

\# t, reset \<label\> = reset HEAD to a label

\# m, merge \[-C \<commit\> \| -c \<commit\>\] \<label\> \[#
\<oneline\>\]

\# . create a merge commit using the original merge commit\'s

\# . message (or the oneline, if no original merge commit was

\# . specified). Use -c \<commit\> to reword the commit message.

\#

\# These lines can be re-ordered; they are executed from top to bottom.

\#

\# If you remove a line here THAT COMMIT WILL BE LOST.

\#

\# However, if you remove everything, the rebase will be aborted.

### 交互式rebase的使用

<http://blog.chinaunix.net/uid-27714502-id-3436703.html>

**一、基本  **

对于git rebase,
你亦可以选择进行交互式的rebase。这种方法通常用于在向别处推送提交之前对它们进行重写。**交互式rebase**提供了一个简单易用的途径让你在和别人分享提交之前对你的提交进行分割、合并或者重排序。在把从其他开发者处拉取的提交应用到本地时，你也可以使用交互式rebase对它们进行清理。

如果你想在rebase的过程中对一部分提交进行修改，你可以在\'git
rebase\'命令中加入\'-i\'或\'\--interactive\'参数去调用交互模式。

\$ git rebase -i origin/master

这个命令会执行交互式rebase操作，操作对象是那些自最后一次从origin仓库拉取或者向origin推送之后的所有提交。

若想查看一下将被rebase的提交，可以用如下的log命令：

\$ git log github/master..

一旦运行了\'rebase
-i\'命令，你所预设的编辑器会被调用，其中含有如下的内容：

pick fc62e55 added file_size

pick 9824bf4 fixed little thing

pick 21d80a5 added number to log

pick 76b9da6 added the apply command

pick c264051 Revert \"added file_size\" - not implemented correctly

\# Rebase f408319..b04dc3d onto f408319

\#

\# Commands:

\#  p, pick = use commit

\#  e, edit = use commit, but stop for amending

\#  s, squash = use commit, but meld into previous commit

\#

\# If you remove a line here THAT COMMIT WILL BE LOST.

\# However, if you remove everything, the rebase will be aborted.

\#

这些信息表示从你上一次推送操作起有5个提交。每个提交都用一行来表示，行格式如下：

(action) (partial-sha) (short commit message)

现在你可以将操作(action)改为\'edit\'(使用提交，但是暂停以便进行修正)或者\'squash\'(使用提交，但是把它与前一提交合并)，默认是\'pick\'(使用提交)。你可以对这些行上下移动从而对提交进行重排序。当你退出编辑器时，git会按照你指定的顺序去应用提交，并且做出相应的操作(action)。

**二、pick操作**

如果指定进行\'pick\'操作，git会应用这个补丁，以同样的提交信息(commit
message)保存提交。

**三、squash操作**

如果指定进行\'squash\'操作，git会把这个提交和前一个提交合并成为一个新的提交。这会再次调用编辑器，你在里面合并这两个提交的提交信息。所以，如果你(在上一步)以如下的内容离开编辑器：

pick   fc62e55 added file_size

squash 9824bf4 fixed little thing

squash 21d80a5 added number to log

squash 76b9da6 added the apply command

squash c264051 Revert \"added file_size\" - not implemented correctly

你必须基于以下的提交信息创建一个新的提交信息：

\# This is a combination of 5 commits.

\# The first commit\'s message is:

added file_size

\# This is the 2nd commit message:

fixed little thing

\# This is the 3rd commit message:

added number to log

\# This is the 4th commit message:

added the apply command

\# This is the 5th commit message:

Revert \"added file_size\" - not implemented correctly

This reverts commit fc62e5543b195f18391886b9f663d5a7eca38e84.

一旦你完成对提交信息的编辑并且退出编辑器，这个新的提交及提交信息会被保存起来。

四、edit操作

如果指定进行\'edit\'操作，git会完成同样的工作，但是在对下一提交进行操作之前，它会返回到命令行让你对提交进行修正，或者对提交内容进行修改。

例如你想要分割一个提交，你需要对那个提交指定\'edit\'操作：

pick   fc62e55 added file_size

pick   9824bf4 fixed little thing

edit   21d80a5 added number to log

pick   76b9da6 added the apply command

pick   c264051 Revert \"added file_size\" - not implemented correctly

你会进入到命令行，重置(reset)该提交，然后创建两个(或者更多个)新提交。假设提交21d80a5修改了两个文件，file1和file2，你想把这两个修改放到不同的提交里。你可以在进入命令行之后进行如下的操作：

\$ git reset HEAD\^

\$ git add file1

\$ git commit \'first part of split commit\'

\$ git add file2

\$ git commit \'second part of split commit\'

\$ git rebase \--continue

现在你有6个提交了，而不是5个。

五、丢弃提交操作

交互式rebase的最后一个作用是丢弃提交。如果把一行删除而不是指定\'pick\'、\'squash\'和'edit\'\'中的任何一个，git会从历史中移除该提交。

### rebase -i：修改已提交历史记录

[小结：git rebase -i
SHA，进入vi界面，将需要修改的提交改成edit，wq保存，之后便进入到这个提交的状态中，此时可以对这个提交进行修改，vim/git
add/git commit \--amend，最后git rebase \--continue应用修改。]{.mark}

[如果想要将修改作为一次新的提交，那么使用vim/git add/git commit -m
\"comment\"，如果不想将修改作为一次新的提交，仍然使用原来的提交，那么使用vim/git
add/git commit \--amend，如果也不想修改注释，则使用git commit \--amend
\--no-edit。]{.mark}

更新时间：2020年07月31日 10:21:51   作者：lucky9322  

有三次提交，发现第二次提交有误，需要修改第二次提交。

git log \--oneline查看

f206555 add 2222

572a41e add 1111

c195175 feat:create file

git rebase -i c195175回到第一次提交的基础上，

![](media/image256.jpeg){width="4.279861111111111in"
height="2.761111111111111in"}

将需要修改的提交前面的pick改成edit，如下：

![](media/image257.jpeg){width="4.566666666666666in"
height="2.714583333333333in"}

此时已经回到第一次提交的基础上了，

![](media/image258.jpeg){width="4.877083333333333in"
height="2.6868055555555554in"}

对文件进行修改、提交

vim tmp.txt 

git status

git add .

git commit \--amend

再次git status查看

![](media/image259.jpeg){width="4.814583333333333in"
height="1.5055555555555555in"} 

提示使用git rebase \--continue 保存刚刚做的修改，

git rebase \--continue

![](media/image260.jpeg){width="5.008333333333334in"
height="2.7527777777777778in"}

此时是出现了冲突需要解决冲突然后继续

![](media/image261.png){width="3.265972222222222in"
height="0.8736111111111111in"}

解决掉冲突之后查看git状态\
提示需要git add .\
进行git add .，继续查看git状态

![](media/image262.jpeg){width="5.0472222222222225in"
height="3.941666666666667in"}

git rebase \--coninue

![](media/image263.jpeg){width="6.520138888888889in"
height="3.952777777777778in"} 

根据提示继续git rebase
\--continue，如果没有冲突就可以回到master了，否则需要继续解决冲突。

来源：https://www.jb51.net/article/192226.htm

### rebase -i 之后怎么操作？

git rebase -i，修改某个提交后，git add、git commit \--amend
\--no-edit，再git rebase \--continue。

如果不修改提交注释，那么使用git add、git commit \--amend
\--no-edit。其实如果不修改提交注释，那么git add后不需要git
commit，为什么呢？git
commit的目的就是产生一个提交，此时提交是已经存在了的，因此不需要再git
commit了。当然，如果要修改提交注释，那么git add后使用git commit \--amend
-m \"new comment\"修改提交注释。

关键是要理解原理：要理解git add、git commit的目的是什么？

### 出现的问题

git commit \--amend出现的问题：

![](media/image264.png){width="3.9027777777777777in"
height="2.2909722222222224in"}

解决办法：

1)按r键

2)#rm .git/.COMMIT_EDITMSG.swp

3)\$ git commit \--amend

以.swp结尾的文件一般是文件在编辑过程中产生的临时文件，删掉即可。

## cherry-pick

### cherry-pick理解

**git merge**是用来合并两个分支的。

**git
cherry-pick**可以选择**某一个分支中的一个或几个commit(s)**来进行操作。例如，假设我们有个稳定版本的分支，叫v2.0，另外还有个开发版本的分支v3.0，我们不能直接把两个分支合并，这样会导致稳定版本混乱，但是又想增加一个v3.0中的某个功能到v2.0中，这里就可以使用cherry-pick了。

\# 先在v3.0中查看要合并的commit的commit id

\$git log

\# 假设是 commit f79b0b1ffe445cab6e531260743fa4e08fb4048b

\# 切到v2.0中

\$git checkout v2.0

\# 合并commit

\$git cherry-pick f79b0b1ffe445cab6e531260743fa4e08fb4048b

fenzhi1:C1🡪 C2🡪 C3 ，fenzhi2:C1🡪 C7

\$git checkout fenzhi2

\$git cherry-pick SHA_C2

这样，C2的修改就合并到fenzhi2上了，同时在fenzhi2上产生了一个新的提交，这个提交里是C2的内容，fenzhi2变为：fenzhi2:C1🡪
C7🡪C2。

[**cherry-pick 和 rebase
的混合用法**](http://blog.luzi82.com/2010/08/git-cherry-pick-rebase.html)

之前在 git上遇过一个问题

A-B master\
\\\
C-D-E-F-G topic

　　问题是，我只想把 D,F加到master，其他的留在topic
，而且又不想把history搞得很乱，最好就变成这个样子：

A-B-D-F master\
\\\
C-E-G topic

　　有甚么好的作法？\
原来答案相当简单。

\$ git checkout master\
\$ git cherry-pick D\
\$ git cherry-pick F\
\$ git checkout topic\
\$ git rebase master (把master分支的修改衍合到topic分支上；)

就这样。

### 冲突解决

和git rebase解决冲突一样。

\$ git cherry-pick 19a4694d77b956c9746d4dc2bf6b7b8c97a6809b

error: could not apply 19a4694\... make conflict

hint: after resolving the conflicts, mark the corrected paths

hint: with \'git add \<paths\>\' or \'git rm \<paths\>\'

hint: and commit the result with \'git commit\'

\$ vi file_name.c //修改冲突的地方

\$ git add file_name.c //add修改

\$ git cherry-pick \--continue //或git commit，此时git
commit后不加任何参数

git cherry-pick解决冲突后，git cherry-pick \--continue提示信息如下：

图片使用相对路径

\# Conflicts:

\# tools_and_skills/git使用.md

\#

\# 似乎您正在做一个拣选提交。如果不对，请运行

\# git update-ref -d CHERRY_PICK_HEAD

\# 然后重试。

\# 请为您的变更输入提交说明。**以 \'#\'
开始的行将被忽略**，而一个空的提交 \--
以#开头的行表示注释，没有以#开头的行表示提交comment。

\# 说明将会终止提交。 \-- git cherry-pick \--continue、git rebase
\--continue、git merge \--continue、

\# \-- git commit \--amend等，都会弹出一个这样的vi编辑界面，修改完提交

\# 日期： Wed Jul 19 22:20:44 2023 +0800 \--
comment后，wq保存退出就可以了。

\#

\# 位于分支 master

\# 您的分支与上游分支 \'origin/master\' 一致。

\#

\# 您在执行拣选提交 8abe22d 的操作。

\#

\# 要提交的变更：

\# 修改： tools_and_skills/git使用.md

\#

cherri-pick详解

git cherry-pick \[\<options\>\] \<commit-ish\>\...

常用options:

\--quit 退出当前的chery-pick序列

\--continue 继续当前的chery-pick序列

\--abort 取消当前的chery-pick序列，恢复当前分支

-n, \--no-commit 不自动提交

-e, \--edit 编辑提交信息

当使用git cherry-pick发生冲突后,将会出现如下信息：

\$ git cherry-pick 23d9422

error: could not apply 23d9422\... \[Description\]:branch2 commit 3

hint: after resolving the conflicts, mark the corrected paths

hint: with \'git add \<paths\>\' or \'git rm \<paths\>\'

hint: and commit the result with \'git commit\'

这时如果要继续cherry-pick，则首先需要解决冲突，通过git add
.将文件标记为已解决，然后可以使用git cherry-pick
\--continue命令，继续进行cherry-pick操作。

如果要中断这次cherry-pick,则使用git cherry-pick
\--quit，这种情况下当前分支中未冲突的内容状态将为modified状态，

如果要取消这次cherry-pick,则使用git cherry-pick
\--abort，这种情况下当前分支恢复到cherry-pick前的状态，没有改变。

**常见问题**

1.The previous cherry-pick is now empty, possibly due to conflict
resolution.

原因:

在cherry-pick时出现冲突，解决冲突后本地分支中内容和cherry-pick之前相比没有改变，因此当在以后的步骤中继续git
cherry-pick或执行其他命令时，由于此时还处于上次cherry-pick，都会提示该信息，表示可能是由于解决冲突造成上一次cherry-pick内容是空的。

解决方案:

1.执行git cherry-pick \--abort取消上次操作。

2.执行git commit \--allow-empty,表示允许空提交。

2.fatal: You are in the middle of a cherry-pick \-- cannot amend.

原因:

在cherry-pick时出现冲突，没有解决冲突就执行git commit
\--amend命令，从而会提示该信息。

解决方案:

首先在git commit \--amend之前解决冲突，并完成这次cherry-pick:

\$ git add .

\$ git cherry-pick \--continue

### 如何在不切换分支的情况下cherry-pick

当前在brancha分支上，提交了commit1，如何在不切换分支的情况下，将提交commit1提交cherry-pick到另外一个分支branchb？

**标准 Cherry-pick 流程（常规做法）**

如果你不介意手动切换，标准的 cherry-pick 流程如下：

1.  查找提交哈希：在 brancha 上找到 commit1 的哈希值（假设为 abc1234）。

git log \--oneline

2.  切换并摘取：

git checkout branchb

git cherry-pick abc1234

3.  处理冲突（如有）：如果发生冲突，Git 会暂停。手动解决冲突文件后，执行
    git add .，然后运行 git cherry-pick \--continue。如果想放弃，执行
    git cherry-pick \--abort。

**方法：使用 Git Worktree（高级且推荐）**

[当前正在 brancha 上开发，工作区很乱，完全不想打断当前状态，可以使用 Git
原生的多工作树功能。它能在不切换当前分支的情况下，把 branchb
挂载到另一个目录进行操作。]{.mark}

*\# 1. 将 branchb 检出到一个临时目录（例如 /tmp/branchb_work）*

git worktree add /tmp/branchb_work branchb

*\# 2. 进入该目录，此时相当于在独立环境中操作 branchb*

cd /tmp/branchb_work

*\# 3. 执行 cherry-pick*

git cherry-pick \<commit1的哈希值\>

*\# 4. 操作完成后，返回原目录并清理临时工作树*

cd -

git worktree remove /tmp/branchb_work

- 优势：你的主工作区（brancha）完全不受任何影响，IDE
  或终端状态也不会被打断。

分析：利用worktree能让工作目录同时在两个分支上的特点，其实是两个不同工作目录各自在自己的一个分支上，同一个工作目录仍然只能同时在一个分支上，宏观上看就是工作目录同时在两个不同分支上。

## merge、rebase、cherry-pick的区别

### 总结,rebase和merge的区别

把一个分支整合到另一个分支的办法有两种：merge(合并) 和 rebase(衍合)。

Eclipse上GIT插件EGIT使用手册之九_rebase和merge的区别
<http://www.open-open.com/lib/view/open1328435894375.html>

rebase和merge操作最终的结果是一样的，但是实现原理不一样。

其实默认pull的操作就是一个分支的merge操作，如下图重现一下：

Mairo弟弟的提交记录如下：

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image265.png){width="2.3208333333333333in"
height="0.32083333333333336in"}

Mairo哥哥的提交记录如下：

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image266.png){width="2.3208333333333333in"
height="0.31319444444444444in"}

首先是Mairo弟弟把更新push到服务器，这样服务器端的记录就和Mairo弟弟本地的记录是一样的，接着Mairo哥哥执行pull操作，现在分析下pull是如何操作的。

pull默认就是先把服务器端的最新记录更新到本地的Remote
Tracking中对应的mirror分支

接着对Local的mirror分支和Remote Tracking的mirror分支进行merge操作

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image267.png){width="1.9180555555555556in" height="1.30625in"}

merge操作后的结果就是会新增加一个merge记录节点，如下所示：

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image268.png){width="3.634027777777778in"
height="1.1194444444444445in"}

从上图可以看出，mushroomA是在mushroomB之前的，这个时间关系不取决于谁先执行push，而取决于本地仓库中谁先执行commit。所以merge会按照时间顺序严格的记录每一次commit。

接下来看看rebase，其实rebase也是把两个分支进行合并的操作，当Mairo弟弟push更新后，服务器端的mirror分支的历史如下：

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image265.png){width="2.23125in" height="0.31319444444444444in"}

Mairo哥哥本地的历史如下：

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image266.png){width="2.3131944444444446in"
height="0.31319444444444444in"}

现在Mairo哥哥不是执行merge操作，而是执行rebase操作，最后结果如下：

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image269.png){width="3.3361111111111112in"
height="0.5597222222222222in"}

很明显的区别是没有出现分支的记录，而且注意到mushroomA\*，请注意这个记录和mushroomA不是同一个记录，我们先分析下rebase操作下，Mairo哥哥的历史记录都做了哪些变化：

先将当前分支的更新部分保存到临时区域，而当前分支重置到上一次pull的记录

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image270.png){width="1.3729166666666666in"
height="0.7763888888888889in"}

然后将服务器端的更新添加到当前分支，此时当前分支和服务器端分支是一样的

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image271.png){width="2.23125in" height="0.7166666666666667in"}

最后将原分支的更新部分mushroomA提交到当前分支的后面，就是要在mushroomB的后面添加mushroomA的更新，当然此时更新记录已经不是之前的mushroomA了，如果出现冲突则使用对比工具解决冲突，最后记录变成mushroomA\*。

![Eclipse上GIT插件EGIT使用手册之九_Rebase和Merge的区别
](media/image269.png){width="3.477777777777778in"
height="0.5819444444444445in"}

如果Mairo哥哥提交过mushroomA1、mushroomA2、mushroomA3，那么执行rebase后会对mushroomA1、
mushroomA2、mushroomA3分别顺序执行上图所示的合并，最后记录为mushroomA1\*、mushroomA2\*、
mushroomA3\*。很显然rebase操作更复杂，冲突的概率也更高，并且不是按照时间顺序记录。

### 总结：merge与rebase、cherry-pick的区别

base1 🡨 base2 🡨 master1 🡨 master2 🡨 master3 (master分支)

base2 🡨 topic1 🡨 topic2 (topic分支)

\$ git checkout master

\$ git merge topic

base1🡨 base2 🡨 master1 🡨 master2 🡨topic1🡨master3🡨topic2🡨a_new_commit
(master分支)

(这里🡨 master1 🡨 master2 🡨 topic1 🡨 master3 🡨
topic2的顺序根据每个commit提交的时间而定，也可能不是这个顺序；)

\$ git rebase topic

base1 🡨 base2🡨 topic1 🡨 topic2 🡨 master1**\*** 🡨 master2**\*** 🡨
master3**\*** (master分支)

base---master分支的base被改变了

\$ git cherry-pick SHA-topic1

base1 🡨 base2 🡨 master1 🡨 master2 🡨 master3 🡨 topic1 (master分支)
(将topic1获取到master分支)

git rebase\--**重新定义(re)分支的起点(base)**；

分支1 和 分支2

![](media/image272.png){width="3.1041666666666665in"
height="0.5145833333333333in"}

![](media/image273.png){width="3.1791666666666667in"
height="0.49236111111111114in"}

\$ git checkout fenzhi1

\$ git merge

![](media/image274.png){width="2.872916666666667in" height="1.0375in"}

\$ git rebase

![](media/image275.png){width="3.0743055555555556in"
height="0.8881944444444444in"}

\$ git cherry-pick fenzhi2的commit1的SHA值

![](media/image276.png){width="2.3208333333333333in"
height="0.7090277777777778in"}

## 实验:分支操作

建立分支：master\<-test1\<-test2\<-test3,然后在test3中通过git rebase -i
HEAD\~3修改了test1的c1提交的提交说明，这之后gitg查看到的结构图如下：

\$git init/vi master_file1.c/git add master_file1.c/git commit -m 'c1'

\$git branch test1/git checkout test1/vi test1_file1.c/git add ./git
commit -m 'c1 of test1 with

test1_file1'

\$git checkout test2/vi test2_file1.c/git add ./git commit -m 'c1 test2
file1'

\$git checkout test3/vi test3_file1.c/git add ./git commit -m 'c1 test3
file1'

\$git rebase -i HEAD\~3 /git commit \--amend -m 'c1 test1 file1 modified
in test3'/git rebase

\--continue

![](media/image277.png){width="2.022222222222222in" height="1.0in"}

\$git checkout -b test3

\$git branch test4

![](media/image278.png){width="1.7763888888888888in"
height="1.1270833333333334in"}

\$git checkout test3

\$git merge SHA_c1_test2_file1

![](media/image279.png){width="4.261111111111111in"
height="1.3805555555555555in"}

\$git checkout test4

\$git rebase SHA\_ Merge_commit'cf41...'into_test3

![](media/image280.png){width="3.7090277777777776in"
height="1.2166666666666666in"}

\$git tag3 SHA_c1_test3_file1

![](media/image281.png){width="3.8506944444444446in"
height="1.2534722222222223in"}

这样就可以用tag3来替代c1 test3 file1这个提交了，如：

\$git show tag3 等价于

\$git show SHA_c1_test3_file1

## 为什么会冲突？

冲突产生的核心原因：多人同时修改同一文件的相同区域。

当两个或以上开发者[对同一文件的同一行或相邻行代码进行不同修改]{.mark}时，[Git无法自动判断应保留哪一方的更改]{.mark}。例如：

- 开发者A将某行代码改为 a = 1，开发者B改为 a = 2。

- Git无法确定逻辑意图，必须由人工选择正确版本或合并逻辑。

但是注意，两个开发者修改同一个文件不一定会冲突，只有修改同一个文件的同一行，并且git无法自动判断应保留哪一方的修改时才会报冲突。

## \*总结：合并修改的几种方法

[合并修改的方法：git merge、git rebase、git cherry-pick、git stash + git
stash apply、git format-patch + git am、git diff + git apply。]{.mark}

这些方法可用于同一个仓库的不同分支之间的代码合并，patch方式可以在不同仓库之间合并，也可以通过邮件等方式远程发送。

## \*总结：冲突解决的步骤

只要是合并代码，都有可能产生冲突，merge、rebase、cherry-pick、stash
apply、am、apply都可能产生冲突。

解决冲突的步骤是一样的：merge、rebase、cherry-pick，修改有冲突的部分、git
add、git \--continue或\--abort。

stash apply、am、apply不需要上述步骤，因为还没有提交到git库。

问题：git合并代码产生冲突，不同合并方式产生冲突的解决步骤是什么样的？有区别吗？

例如merge、rebase、cherry-pick、stash
apply、am、apply产生冲突后怎么解决？解决冲突后是否需要git add、然后再git
cmd \--continue？

**Qwen3-Max** 00:07:12

是的，**不同 Git 操作(如 merge、rebase、cherry-pick、stash
apply、am、apply)在发生冲突时，解决流程的核心步骤是相似的**，但**后续"继续"操作使用的命令不同**。下面我为你系统梳理：

**通用冲突解决流程(所有场景都适用)**

无论哪种操作引发冲突，**解决冲突本身的过程完全一致**：

**步骤 1：编辑冲突文件**

- 打开标记了 \<\<\<\<\<\<\< HEAD、=======、\>\>\>\>\>\>\> \... 的文件。

- 手动保留你想要的代码，删除冲突标记。

**步骤 2：标记冲突已解决**

git add \<resolved-file\>

[**必须执行 git add**，这是告诉
Git："这个文件的冲突我已经处理好了"。]{.mark}

**不同操作的"继续"命令(关键区别)**

  -------------------------------------------------------------------------------------------------
  操作            冲突后继续命令                           备注
  --------------- ---------------------------------------- ----------------------------------------
  git merge       git merge \--continue\                   现代 Git 推荐用 \--continue
                  或直接 git commit(旧版 Git)              

  git rebase      git rebase \--continue                   必须用此命令

  git cherry-pick git cherry-pick \--continue              若 pick 多个提交，会继续下一个

  git stash apply 无 \--continue！\                        apply 是一次性操作，不记录"进行中状态"
                  解决后只需 git add + 正常提交            

  git stash pop   同上，解决后 git add + 提交即可          pop = apply + drop

  git am(应用     git am \--continue                       常用于邮件补丁流程
  mbox 补丁)                                               

  git             无 \--continue！\                        apply 本身不创建提交
  apply(打补丁)   它只是修改工作区，解决冲突后需手动 git   
                  add + commit                             
  -------------------------------------------------------------------------------------------------

**核心规律**：

- 如果该操作会自动创建提交(如 merge、cherry-pick)或分步进行(如 rebase、am)，Git会记录"in-progress"状态，因此需要 \--continue。

- 如果操作只修改工作区/暂存区(如 stash
  apply、apply)，则无"继续"概念，解决后手动提交即可。

**详细场景说明**

**1. git merge 冲突**

git merge feature

*\# Auto-merging file.txt*

*\# CONFLICT (content): Merge conflict in file.txt*

*\# \...*

解决后：

git add file.txt

git merge \--continue *\# 或 git commit(效果相同)*

**2. git rebase 冲突**

git rebase main

*\# CONFLICT (content): file.txt*

解决后：

git add file.txt

git rebase \--continue *\# 必须！不能用 commit*

若想放弃：git rebase \--abort

**3. git cherry-pick 冲突**

git cherry-pick abc123

*\# CONFLICT \...*

解决后：

git add file.txt

git cherry-pick \--continue

**4. git stash apply / pop 冲突**

git stash apply

*\# Auto-merging file.txt*

*\# CONFLICT (content): \...*

解决后：

git add file.txt

git commit -m \"resolve stash conflict\" *\# 手动提交！无 \--continue*

stash apply 不改变 HEAD，也不启动"合并会话"，所以 Git
不知道你在"继续"什么。

**5. git am 冲突(用于应用 .patch 文件)**

git am \< patch.diff

*\# Patch failed at 0001 \...*

解决后：

git add file.txt

git am \--continue

**6. git apply 冲突**

git apply patch.diff

*\# error: patch failed: file.txt:10*

*\# error: file.txt: patch does not apply*

注意：git apply 默认**不会**自动产生带冲突标记的文件！\
要让它生成冲突标记，需加 \--3way：

git apply \--3way patch.diff

*\# 此时才会出现 \<\<\<\<\<\<\< 标记*

解决后：

git add file.txt

git commit -m \"apply patch\"

apply 本质是"打补丁到工作区"，不涉及 Git 的"进行中操作"状态。

**总结：一张表看懂**

  ----------------------------------------------------------------------------------
  操作          是否有"进行中"状态？   冲突后是否需\--continue？   解决后是否要git
                                                                   add？
  ------------- ---------------------- --------------------------- -----------------
  merge         是                     merge \--continue           必须

  rebase        是                     rebase \--continue          必须

  cherry-pick   是                     cherry-pick \--continue     必须

  am            是                     am \--continue              必须

  stash apply   否                     无                          必须(然后手动
                                                                   commit)

  apply         否                     无                          必须(然后手动
                                                                   commit)
  ----------------------------------------------------------------------------------

**最佳实践建议**

1.  永远先 git add 再 \--continue ------ 这是 Git
    判断"冲突已解决"的唯一方式。

2.  如果不确定当前处于什么"进行中"状态，运行：

git add \<resolved-file\>

它会明确提示你该用哪个 \--continue 命令。

3.  想放弃？大多数操作支持 \--abort(如 rebase \--abort, am
    \--abort)，但 merge 只能 reset 回退。

## \*总结：如何理解"冲突标记\<\<\<\<\<\<\< ======= \>\>\>\>\>\>\>"

[如何理解**冲突标记**\<\<\<\<\<\<\< ======= \>\>\>\>\>\>\>]{.mark}

我方、已有的 代码在哪里？

对方、我方还没有的 代码在哪里？

**实验**

\$ git \--version

git version 2.51.0

\$ git branch

\* master

\$ vim test.sh

val=1

echo hallo, this is \$val

\$ git add test.sh ; git commit -m init

\$ git switch -c develop

\$ vim test.sh

val=3

echo hallo, this is \$val

\$ git add test.sh ; git commit -m modify_to_3

\$ git switch -c master

\$ vim test.sh

val=2

echo hallo, this is \$val

\$ git add test.sh ; git commit -m modify_to_2

### 一、merge冲突

\$ git branch

develop

\* master

\$ git merge develop

自动合并 test.sh

冲突（内容）：合并冲突于 test.sh

自动合并失败，修正冲突然后提交修正的结果。

\$ vim test.sh

\<\<\<\<\<\<\< HEAD // \<\<\<\<\<\<\<HEAD 我方，已有的

val=2

======= // ======= 分界线

val=3

\>\>\>\>\>\>\> develop // \>\>\>\>\>\>\>branchname 对方，还没有的

echo hallo, this is \$val

[可知，git merge冲突，\<\<\<\<\<\<\<HEAD =======之间是 我方
已有的代码，======= \>\>\>\>\>\>\>branchname之间是对方
我方没有的代码。]{.mark}

可以形象的比喻为我站在自己家里，伸手将对方的东西**整个掰过来**，HEAD在我家(方)。

\$ git status

位于分支 master

您有尚未合并的路径。

（解决冲突并运行 \"git commit\"）

（使用 \"git merge \--abort\" 终止合并）

未合并的路径：

（使用 \"git add \<文件\>\...\" 标记解决方案）

双方修改： test.sh

修改尚未加入提交（使用 \"git add\" 和/或 \"git commit -a\"）

\$ git merge \--abort

### 二、rebase冲突

\$ git branch

develop

\* master //后面的实验都是在master分支操作

\$ git rebase develop

自动合并 test.sh

冲突（内容）：合并冲突于 test.sh

错误：不能应用 cba32d3\... modify_to_2

提示： Resolve all conflicts manually, mark them as resolved with

提示： \"git add/rm \<conflicted_files\>\", then run \"git rebase
\--continue\".

提示： You can instead skip this commit: run \"git rebase \--skip\".

提示： To abort and get back to the state before \"git rebase\", run
\"git rebase \--abort\".

提示： Disable this message with \"git config set advice.mergeConflict
false\"

不能应用 cba32d3\... \# modify_to_2

\$ git branch

\* （非分支，正变基 master）

develop

master

\$ git status

交互式变基操作正在进行中；至 1de6856

最后完成的命令（1 条命令被执行）：

pick cba32d3 \# modify_to_2

未剩下任何命令。

您在执行将分支 \'master\' 变基到 \'1de6856\' 的操作。

（解决冲突，然后运行 \"git rebase \--continue\"）

（使用 \"git rebase \--skip\" 跳过此补丁）

（使用 \"git rebase \--abort\" 以检出原有分支）

未合并的路径：

（使用 \"git restore \--staged \<文件\>\...\" 以取消暂存）

（使用 \"git add \<文件\>\...\" 标记解决方案）

双方修改： test.sh

\$ vim test.sh

\<\<\<\<\<\<\< HEAD // \<\<\<\<\<\<\<HEAD 对方，还没有的

val=3

======= // ======= 分界线

val=2

\>\>\>\>\>\>\> cba32d3 (modify_to_2) // \>\>\>\>\>\>\>comment
我方，已有的

echo hallo, this is \$val

[可知，git rebase冲突，\<\<\<\<\<\<\<HEAD =======之间是 对方
我方没有的代码，======= \>\>\>\>\>\>\>comment之间是 我方
已有的代码。]{.mark}

[这与git merge冲突正好相反。]{.mark}

在当前分支执行git
rebase操作，**先将HEAD移动到被rebase到的分支**，然后将**当前分支**上的提交合并到HEAD上去(以对方分支HEAD为基础(base)，使用git
cherry-pick将我方修改一个一个地**拿过去**？rebase成功后再将HEAD移动到最新提交上？)，所以冲突标记\<\<\<\<\<\<\<HEAD
=======之间表示的是被rebase到的分支的代码，所以根本原因是**移动了HEAD指针？**\--可能是这样，需要看代码确认！

可以形象的比喻为我站在对方家里，伸手将自己家的东西拿过去，HEAD在对方家里。

\--
[很多资料**写错**了，腾讯元宝等AI回答也是**错误**的，这些资料将merge冲突和rebase冲突混为一谈。\--20260129]{.mark}

那么，对于git merge、git
rebase冲突，如何区分我方代码和对方代码？死记？好像没有更好的方法，只能记住，git
merge冲突\<\<\<\<\<\<\<HEAD =======之间是我方的，git
rebase冲突\<\<\<\<\<\<\<HEAD =======之间是对方的。

\$ git merge \--abort

### 三、cherry-pick冲突

\$ git branch -vv

develop 1de6856 modify_to_3

\* master cba32d3 modify_to_2

\$ git cherry-pick 1de6856

自动合并 test.sh

冲突（内容）：合并冲突于 test.sh

错误：不能应用 1de6856\... modify_to_3

提示： 解决所有冲突之后，用 \"git add/rm \<路径规格\>\" 标记它们，

提示： 然后执行 \"git cherry-pick \--continue\"。您也可以执行

提示： \"git cherry-pick \--skip\"
命令跳过这个提交。如果想要终止执行并回到

提示： 执行 \"git cherry-pick\" 之前的状态，执行 \"git cherry-pick
\--abort\"。

提示： Disable this message with \"git config set advice.mergeConflict
false\"

\$ vim test.sh

\<\<\<\<\<\<\< HEAD // \<\<\<\<\<\<\<HEAD 我方，已有的

val=2

======= // ======= 分界线

val=3

\>\>\>\>\>\>\> 1de6856 (modify_to_3) // \>\>\>\>\>\>\>comment
对方，还没有的

echo hallo, this is \$val

[可知，git cherry-pick冲突，\<\<\<\<\<\<\<HEAD =======之间是 我方
已有的代码，======= \>\>\>\>\>\>\>branchname之间是对方
我方没有的代码。和git merge冲突是一样的。]{.mark}

可以形象的比喻为我站在自己家里，伸手将对方的东西一个一个地pick**拿过来**，HEAD在我家(方)。

git cherry-pick冲突和git merge冲突不同的是，git
cherry-pick冲突\>\>\>\>\>\>\>comment尖括号后面是提交注释，而git
merge冲突\>\>\>\>\>\>\>branchname尖括号后面是分支名。

\$ git cherry-pick --abort

### 四、stash apply冲突

\$ git stash list

stash@{0}: On bug: modify_to_3

\$ git stash show stash@{0} -p

diff \--git a/test.sh b/test.sh

index 5cf7f53..ea5fb11 100644

\-\-- a/test.sh

+++ b/test.sh

@@ -1,3 +1,3 @@

-val=1

+val=3

echo hallo, this is \$val

\$ git stash apply

自动合并 test.sh

冲突（内容）：合并冲突于 test.sh

位于分支 master

未合并的路径：

（使用 \"git restore \--staged \<文件\>\...\" 以取消暂存）

（使用 \"git add \<文件\>\...\" 标记解决方案）

双方修改： test.sh

修改尚未加入提交（使用 \"git add\" 和/或 \"git commit -a\"）

\$ vim test.sh

\<\<\<\<\<\<\< Updated upstream // \<\<\<\<\<\<\<HEAD 我方，已有的

val=2

======= // ======= 分界线

val=3

\>\>\>\>\>\>\> Stashed changes // \>\>\>\>\>\>\>comment 对方，还没有的

echo hallo, this is \$val

### 小结

merge、cherry-pick、stash apply，冲突标记中\<\<\<\<\<\<\<HEAD
=======之间是我方已有的代码，

rebase，冲突标记中\<\<\<\<\<\<\<HEAD
=======之间是对方的、我方还没有的代码。rebase和其他三个不一样。

merge、rebase、cherry-pick、stash
apply都是基于本地仓库的操作，会有**冲突标记**\<\<\<\<\<\<\< =======
\>\>\>\>\>\>\>，

但是，am、apply不一定是基于本地仓库的修改，可以通过邮件、网络的方式传输，没有冲突标记\<\<\<\<\<\<\<
======= \>\>\>\>\>\>\>。

### 五、am冲突

\$ git branch -vv

develop 1de6856 modify_to_3

\* master cba32d3 modify_to_2

将develop分支修改打包patch

\$ git format-patch 1de6856 -1

0001-modify_to_3.patch

在master分支应用patch

\$ git am 0001-modify_to_3.patch

应用：modify_to_3

错误：打补丁失败：test.sh:1

错误：test.sh：补丁未应用

打补丁失败于 0001 modify_to_3

提示： 用 \'git am \--show-current-patch=diff\' 命令查看失败的补丁

提示： 当您解决这一问题之后，执行 \"git am \--continue\"。

提示： 如果您想要跳过这一补丁，则执行 \"git am \--skip\"。

提示： 若要复原至原始分支并停止补丁操作，执行 \"git am \--abort\"。

提示： Disable this message with \"git config set advice.mergeConflict
false\"

[应用patch失败，没有修改文件，看不到冲突的内容，如何解决冲突？]{.mark}

网上说法，使用\--reject选项，git am \--reject
0001-modify_to_3.patch，生成test.sh.rej文件，test.sh.rej标记冲突的代码位置，根据\*.rej文件逐个修改冲突\--没有merge/rebase/cherry-pick解决冲突那么好用。

\$ git am \--reject 0001-modify_to_3.patch

test.sh.rej文件内容如下：

diff a/test.sh b/test.sh (rejected hunks)

@@ -1,3 +1,3 @@

-val=1

+val=3

echo hallo, this is \$val

\--修改代码量小，直接对比两个文件就行，但是修改代码量大时怎么办？看来只能创建一个新的分支，回退代码到冲突之前的提交，应用patch，然后再回到想要应用patch的分支，使用git
merge/rebase/cherry-pick合并，然后根据冲突标记修改。

### 六、apply冲突

\$ git apply modify_to_3.patch

错误：打补丁失败：test.sh:1

错误：test.sh：补丁未应用

解决冲突的方法和git am一样，使用\--reject选项，

\$ git am \--reject modify_to_3.patch

test.sh.rej文件内容如下：

diff a/test.sh b/test.sh (rejected hunks)

@@ -1,3 +1,3 @@

-val=1

+val=3

echo hallo, this is \$val

## git工具 \-- rerere

[https://git-scm.com/book/zh/v2/git-%E5%B7%A5%E5%85%B7-Rerere](https://git-scm.com/book/zh/v2/Git-%E5%B7%A5%E5%85%B7-Rerere)

**git rerere是一个隐藏的功能**。 正如它的名字 "reuse recorded
resolution" 所指，它允许你让
git记住解决一个块冲突的方法，这样在下一次看到相同冲突时，git可以为你自动地解决它。

有几种情形下这个功能会非常有用。
在文档中提到的一个例子是如果你想要保证一个长期分支会干净地合并，但是又不想要一串中间的合并提交。
将 rerere 功能打开后偶尔合并，解决冲突，然后返回到合并前。
如果你持续这样做，那么最终的合并会很容易，因为 rerere 可以为你自动做所有的事情。

可以将同样的策略用在维持一个变基的分支时，这样就不用每次解决同样的变基冲突了。
或者你将一个分支合并并修复了一堆冲突后想要用变基来替代合并 -
你可能并不想要再次解决相同的冲突。

另一个情形是当你偶尔将一堆正在改进的特性分支合并到一个可测试的头时，就像
git项目自身经常做的。
如果测试失败，你可以倒回合并之前然后在去除导致测试失败的那个特性分支后重做合并，而不用再次重新解决所有的冲突。

为了启用 rerere 功能，仅仅需要运行这个配置选项：

\$ git config \--global rerere.enabled true

也通过在特定的仓库中创建 .git/rr-cache 目录来开启它，但是设置选项更干净并且可以应用到全局。

现在我们看一个简单的例子，类似之前的那个。 假设有一个像这样的文件：

#! /usr/bin/env ruby

def hello

puts \'hello world\'

end

在一个分支中修改单词 "hello" 为 "hola"，然后在另一个分支中修改 "world"
为 "mundo"，就像之前一样。

![](media/image282.png){width="2.470138888888889in"
height="1.8881944444444445in"}

当合并两个分支到一起时，我们将会得到一个合并冲突：

\$ git merge i18n-world

Auto-merging hello.rb

CONFLICT (content): Merge conflict in hello.rb

Recorded preimage for \'hello.rb\'

Automatic merge failed; fix conflicts and then commit the result.

你会注意到那个新行 Recorded preimage for FILE。
除此之外它应该看起来就像一个普通的合并冲突。
在这个时候，rerere 可以告诉我们几件事。
和往常一样，在这个时候你可以运行 git status 来查看所有冲突的内容：

\$ git status

\# On branch master

\# Unmerged paths:

\# (use \"git reset HEAD \<file\>\...\" to unstage)

\# (use \"git add \<file\>\...\" to mark resolution)

\#

\# both modified: hello.rb

\#

然而，git rerere 也会通过 git rerere status 告诉你它记录的合并前状态。

\$ git rerere status

hello.rb

并且 git rerere diff 将会显示解决方案的当前状态 -
开始解决前与解决后的样子。

\$ git rerere diff

\-\-- a/hello.rb

+++ b/hello.rb

@@ -1,11 +1,11 @@

#! /usr/bin/env ruby

def hello

-\<\<\<\<\<\<\<

\- puts \'hello mundo\'

-=======

+\<\<\<\<\<\<\< HEAD

puts \'hola world\'

-\>\>\>\>\>\>\>

+=======

\+ puts \'hello mundo\'

+\>\>\>\>\>\>\> i18n-world

end

同样(这并不是真的与 rerere 有关系)，可以使用 ls-files
-u 来查看冲突文件的之前、左边与右边版本：

\$ git ls-files -u

100644 39804c942a9c1f2c03dc7c5ebcd7f3e3a6b97519 1 hello.rb

100644 a440db6e8d1fd76ad438a49025a9ad9ce746f581 2 hello.rb

100644 54336ba847c3758ab604876419607e9443848474 3 hello.rb

现在可以通过改为 puts \'hola mundo\' 来解决它，可以再次运行 rerere
diff 命令来查看 rerere 将会记住的内容：

\$ git rerere diff

\-\-- a/hello.rb

+++ b/hello.rb

@@ -1,11 +1,7 @@

#! /usr/bin/env ruby

def hello

-\<\<\<\<\<\<\<

\- puts \'hello mundo\'

-=======

\- puts \'hola world\'

-\>\>\>\>\>\>\>

\+ puts \'hola mundo\'

end

所以从本质上说，当 git看到一个 hello.rb 文件的一个块冲突中有 "hello
mundo" 在一边与 "hola world" 在另一边，它会将其解决为 "hola mundo"。

现在我们可以将它标记为已解决并提交它：

\$ git add hello.rb

\$ git commit

Recorded resolution for \'hello.rb\'.

\[master 68e16e5\] Merge branch \'i18n\'

可以看到它 \"Recorded resolution for FILE\"。

![](media/image283.png){width="4.3284722222222225in"
height="2.1638888888888888in"}

现在，让我们撤消那个合并然后将它变基到 master
分支顶部来替代它。可以通过使用之前在 重置揭密 看到的 reset 来回滚分支。

\$ git reset \--hard HEAD\^

HEAD is now at ad63f15 i18n the hello

我们的合并被撤消了。 现在让我们变基特性分支。

\$ git checkout i18n-world

Switched to branch \'i18n-world\'

\$ git rebase master

First, rewinding head to replay your work on top of it\...

Applying: i18n one word

Using index info to reconstruct a base tree\...

Falling back to patching base and 3-way merge\...

Auto-merging hello.rb

CONFLICT (content): Merge conflict in hello.rb

Resolved \'hello.rb\' using previous resolution.

Failed to merge in the changes.

Patch failed at 0001 i18n one word

现在，正像我们期望的一样，得到了相同的合并冲突，但是看一下 Resolved FILE
using previous resolution 这行。
如果我们看这个文件，会发现它已经被解决了，而且在它里面没有合并冲突标记。

\$ cat hello.rb

#! /usr/bin/env ruby

def hello

puts \'hola mundo\'

end

同样，git diff 将会显示出它是如何自动地重新解决的：

\$ git diff

diff \--cc hello.rb

index a440db6,54336ba..0000000

\-\-- a/hello.rb

+++ b/hello.rb

@@@ -1,7 -1,7 +1,7 @@@

#! /usr/bin/env ruby

def hello

\- puts \'hola world\'

\- puts \'hello mundo\'

++ puts \'hola mundo\'

end

![](media/image284.png){width="4.514583333333333in"
height="2.3881944444444443in"}

也**可以通过 checkout 命令重新恢复到冲突时候的文件状态**：

**\$ git checkout \--conflict=merge hello.rb**

\$ cat hello.rb

#! /usr/bin/env ruby

def hello

\<\<\<\<\<\<\< ours

puts \'hola world\'

=======

puts \'hello mundo\'

\>\>\>\>\>\>\> theirs

end

我们将会在 高级合并 中看到这个的一个例子。
然而现在，让我们通过运行 rerere 来重新解决它：

\$ git rerere

Resolved \'hello.rb\' using previous resolution.

\$ cat hello.rb

#! /usr/bin/env ruby

def hello

puts \'hola mundo\'

end

我们通过 rerere 缓存的解决方案来自动重新解决了文件冲突。
现在可以添加并继续变基来完成它。

\$ git add hello.rb

\$ git rebase \--continue

Applying: i18n one word

所以，如果做了很多次重新合并，或者想要一个特性分支始终与你的 master
分支保持最新但却不想要一大堆合并，或者经常变基，打开 rerere 功能可以帮助你的生活变得更美好。

# 12)打包解包,patch操作

## patch概述

  --------------------------------------------------------------------------------
  特性       **git diff + git apply         **git format-patch + git am
             (标准补丁)**                   (git专用补丁)**
  ---------- ------------------------------ --------------------------------------
  核心特点​   生成代码差异文件               生成包含完整提交信息的补丁

  提交信息​   不包含提交信息、作者等元数据   包含作者、日期、提交信息等完整元数据

  应用命令​   git apply                      git am

  适用场景​   分享未提交的本地修改           传递已提交的 commit
  --------------------------------------------------------------------------------

## 打patch、应用patch

**打patch，生成补丁，git format-patch：**

\$ git format-patch -1 和 git format-patch HEAD\^
等效，生成当前分支最近一次提交的patch

\$ git format-patch -2 和 git format-patch HEAD\^\^
等效，生成当前分支最近两次提交的patch

\$ git format-patch -1 SHA //生成指定提交的patch

\$ git format-patch -n SHA
//从SHA值开始(含SHA值当次)之前的n次提交的patch

**应用补丁，git am**：\
\$ git am 0001-trival-patch.patch

git am用了git apply，用它打补丁会生成commit信息。如果出现错误previous
rebase directory ../.git/rebase-apply still exists but mbox
given，可以用：

\$ git am \--abort

上述方法用于**已经commit的**更改，如果是还没有commit的修改，可以用**git
diff生成的本地修改的patch**，则可以用下面方法生成patch、应用patch：

**打patch，生成补丁，git diff \> \*\*\*.patch：**\
\$ git diff \> diff.patch\
**应用patch，git apply或apply**：

\$ patch -p1 \< diff.patch//**推荐使用patch命令**，git apply命令经常出错

\$ git apply diff.patch / \$ git apply \--ignore-space-change
\--ignore-whitespace diff.patch

有时git apply命令出错，patch -p1可以正常使用。

有这样的目录层次 x/xx/xxx/xxx/ttt.c

而我的当前位置 是 x/下，执行git diff\> test.patch，

在test.patch补丁文件里的路径信息是这样的：

\- - - a/xx/xxx/xxx

+++b/xx/xxx/xxx

如果应用test.patch的时候的位置是在x/下，那么执行patch -p1 \<
test.patch。

注意，使用git
diff产生的patch都应该在执行patch命令时指定-p1，当位置是"在哪里制作的patch，就在哪里执行"。

或者直接使用git apply
test.patch打补丁,执行这个命令的位置也是"在哪里制作的patch，就在哪里执行此命令"。

两种patch的比较：

兼容性：很明显，git
diff生成的patch**兼容性强**。如果你在修改的代码的官方版本库不是git管理的版本库，那么你必须使用git
diff生成的patch才能让你的代码被项目的维护人接受。

除错功能：对于git diff生成的patch，你可以用git apply
\--check查看补丁是否能够干净顺利地应用到当前分支中；如果git format-patch
生成的补丁不能打到当前分支，git
am会给出提示，并协助你完成打补丁工作，你也可以使用git am
-3进行三方合并，详细的做法可以参考git手册或者《Progit》。从这一点上看，两者除错功能都很强。

版本库信息：由于git
format-patch生成的补丁中含有这个补丁开发者的名字、邮箱等信息，因此在应用补丁时，这些信息会被记录进版本库，显然，这样做是恰当的。因此，目前使用git的开源社区往往建议大家使用format-patch生成补丁。

## git format-patch

**使用git format-patch生成的一系列的patch**。git
format-patch生成的git专用补丁。

法一：使用HEAD生成patch

\$ git format-patch HEAD\^ \<==最近的1次commit的patch

\$ git format-patch HEAD\^\^ \<==最近的2次commit的patch

\$ git format-patch HEAD\^\^\^ \<==最近的3次commit的patch

\$ git format-patch HEAD\^\^\^\^ \<==最近的4次commit的patch

\$ git format-patch HEAD\^\^\^\^\^ \<==不支持！！！！error！！！

git format-patch -1 和 git format-patch HEAD\^
等效，生成当前分支最近一次提交的patch

git format-patch -2 和 git format-patch HEAD\^\^
等效，生成当前分支最近两次提交的patch

git format-patch -n , n是具体某个数字， 例如 \'git format-patch -1\'
这时便会根据log生成一个对应的补丁，如果 \'git format-patch -2\'
那么便会生成2个补丁，当然前提是你的log上有至少有两个记录。

法二：根据commit SHA生成patch

\$ git format-patch -1 SHA //生成指定提交的patch

\$ git format-patch -n SHA
//从SHA值开始(**含SHA当次**)以及之前的n次提交的patch(**比SHA更旧的**提交、**在SHA之前的**提交)

\$ git format-patch commit1..commit4 //生成从commit2到commit4的patch

\$ git format-patch -s SHA
//此SHA值提交**以后的**所有patch(**不含SHA当次**)
(**比SHA更新的**提交、**在SHA之后的**提交)

法三：指定分支

\$ git format-patch -M master //当前分支所有超前master的提交

\$ git format-patch -n master //生成最近n次commit的patch

\$ git format-patch master\~4..master\~2
//生成master\~4和master\~2之间差异的patch

**\$ git log**

commit b0783b0a1fdd994a8e2bbe8678d47783d2e3acb4

Author: junwei \<junwei@junwei-fc12.(none)\>

Date: Wed Sep 28 17:49:19 2011 +0800

v1.4

commit 7508329c355c7ea00b9fd25a74ed7d5024cfb4b9

Author: junwei \<junwei@junwei-fc12.(none)\>

Date: Wed Sep 28 17:49:10 2011 +0800

v1.3

commit ae10f81cc52d5eb539a057ad3098b09da0c50b86

Author: junwei \<junwei@junwei-fc12.(none)\>

Date: Wed Sep 28 17:48:37 2011 +0800

v1.2

commit cef313f3ee6ed988388383635b264680d1dc7594

Author: junwei \<junwei@junwei-fc12.(none)\>

Date: Wed Sep 28 17:47:17 2011 +0800

v1.1

commit 85f88806e76ac8a393c901c19bb2d0e544190610

Author: junwei \<junwei@junwei-fc12.(none)\>

Date: Wed Sep 28 17:46:59 2011 +0800

v1.0

\$ git format-patch HEAD\^ \<==最近的一次commit的patch

0001-v1.4.patch

\$ cat 0001-v1.4.patch 

From b0783b0a1fdd994a8e2bbe8678d47783d2e3acb4 Mon Sep 17 00:00:00 2001\
From: junwei \<junwei@junwei-fc12.(none)\>\
Date: Wed, 28 Sep 2011 17:49:19 +0800\
Subject: \[PATCH\] v1.4\
\-\--\
 a \|    1 +\
 1 files changed, 1 insertions(+), 0 deletions(-)\
diff \--git a/a b/a\
index b92eaea..71f3b7f 100644\
\-\-- a/a\
+++ b/a\
@@ -2,3 +2,4 @@ This is the orignal versiom v1.0.\
 This is the orignal versiom v1.1.\
 This is the orignal versiom v1.2.\
 This is the orignal versiom v1.3.\
+This is the orignal versiom v1.4\
\-- \
1.6.5.2

\$ rm 0001-v1.4.patch \
\$ git format-patch HEAD\^\^ 《=== 最近的2次commit的patch

0001-v1.3.patch\
0002-v1.4.patch

## git am

**\$****git am \~/patch/0001-trival-patch.patch**

如果贡献者也用 git，且擅于制作 format-patch
补丁，那你的合并工作将会非常轻松。

因为这些补丁中除了文件内容差异外，还包含了作者信息和提交消息，所以请鼓励贡献者用format-patch
生成补丁。

对于传统的diff命令生成的补丁，则只能用patch或git apply处理。

对于 format-patch 制作的新式补丁，应当使用 git am命令。

**使用git-am合并git format-patch生成的一系列的patch**

**\$git am \~/patch/0001-trival-patch.patch**

在git使用当中，会有很多时候别人(供应商或者其他的开发人员)发过来一系列的patch，这些patch通常的是类似这样的名字：

0001\--JFFS2-community-fix-with-not-use-OOB.patch\
0002\--Community-patch-for-Fix-mount-error-in.patch\
0003\--partial-low-interrupt-latency-mode-for-ARM113.patch\
0004\--for-the-global-I-cache-invalidation-ARM11.patch

里面包含了提交的日志，作者，日期等信息。你想做的是把这些patch引入到你的\
代码库中，最好是也可以把日志也引入进来，方便以后维护用。

传统的打patch方式是：patch -p1 \<
0001\--JFFS2-community-fix-with-not-use-OOB.patch

这样来打patch，**会把这些有用的信息丢失**。

git-am能解决有用信息丢失的问题。

在使用git-am之前，你要首先git am
-abort一次，来放弃掉以前的am信息，这样才可以进行一次全新的am。不然会遇到这样的错误:.git/rebase-apply
still exists but mbox given.

git-am
可以一次合并一个文件，或者一个目录下所有的patch，或者你的邮箱目录下的patch.

下面举两个例子：

你现在有一个code base：small-src,
你的patch文件放在\~/patch/0001-trival-patch.patch

\$**git am \~/patch/0001-trival-patch.patch**

如果成功patch上去， 你就可以去喝杯茶了。

如果失败了，git会提示错误， 比如：

error: patch failed: android/mediascanner.cpp:452\
error: android/mediascanner.cpp: patch does not apply

这样你就需要先看看patch，
然后改改错误的这个文件，让这个patch能够patch上去。

### 冲突解决

\$git am \*.patch

来merge这些patch， 报错，Patch failed at 0001 add
line这样我们看0001这个patch,原来patch需要的是some text, 而file里面是the
text, 所以我们用编辑器把这行改成some text,

\$vi file\
\$git apply 0001-add-line.patch\
\$git add file\
\$git am \--resolved

在解决完冲突以后， 比如用git add来让git知道你已经解决完冲突了。

如果你发现这个冲突是无法解决的，要撤销整个am的东西。 可以运行git am
-abort，

如果你想只是忽略这一个patch，可以运行git am -skip来跳过这个patch.

git format-patch -1     生成最后一个提交对应的patch文件。

git am \< patch          把一个patch文件加入git仓库中。

git am \--resolved       如果有冲突，在解决冲突后执行。

git am \--skip           放弃当前git am所引入的patch。

## git diff \> change.patch

也可以使用git diff来生成patch文件，如\$git diff \> change.patch，\$git
diff sha1 sha2 \> change.patch。

## git apply

\$ git apply /tmp/patch-ruby-client.patch

如果收到的补丁文件是用 git diff 或由其它Unix的diff命令生成，就该用 git
apply 命令来应用补丁。假设补丁文件存在
/tmp/patch-ruby-client.patch，可以这样运行：

\$ git apply /tmp/patch-ruby-client.patch

通过git format-patch与git
apply工具的使用，可以将早期项目的修改提交制成.patch文件，在之后的代码merge时可以很方便的将其导入，减轻的任务的工作量。

以本人在S3_JB上提交的某commit为例。我需要将本次修改内容merge到分支 phone/racer-a_ics上。

首先在S3_JB的分支上找到本人的提交

me@me-Lenovo-Product:\~/workspaces/S3_JB/frameworks/base\$ git log
\--author=\"me\"

\<code\>commit eada6f926e17c9719dff250d4dd0fd3d4d560986\</code\>

Author: me \<me@workspces.com\>

Date: Wed Sep 19 10:53:21 2012 +0800

\[FIX\]S3_JB代码merge

\[WHT\]增加的呼叫限制部分framework层的支持,修正了紧急号码列表支持，修正了响铃动作，优化了指令流程，增加了调试用log

Change-Id: Ibd168ae3cd1b56e29d4e3084de803694c631eb9d

**根据这个commit我生成一个patch文件**

\$ git format-patch -1 eada6f926e17c9719dff250d4dd0fd3d4d560986 

0001-FIX-S3_JB-merge.patch

**将这个patch文件导入到新的分支当中**

\$git apply \~/0001-FIX-S3_JB-merge.patch \--reject

git apply相当于patch命令。

\--check 检查能否正常打上补丁，-v verbose模式， -R
reverse模式，反打补丁。

有时候使用git am/git apply应用补丁出错，使用patch命令不会报错，patch -p0
\< to-file.patch，见：linux打补丁和git打patch方法。

### 应用补丁时指定目录层次

git apply \--directory=vendor/atbm6463_ipc
vendor/atbm6463_ipc/0001-053.patch

\--todo

git apply \--check

Instead of applying the patch, see if the patch is applicable to the
current working tree and/or the index file and detects errors. Turns off
\"apply\".

## git format-patch生成的patch能使用git apply应用吗？

**不能**。git format-patch生成的补丁文件**不能**使用 git
apply来应用，反之亦然。

这两种方法生成的是**结构完全不同**的补丁文件，因此必须配对使用对应的应用命令。

**核心区别**

你可以把这两种补丁想象成两种不同的"文件格式"：

1.  **git format-patch生成的是"邮件补丁"**

    - **内容**：它是一个完整的电子邮件格式文件，包含了**邮件头**（如发件人、日期、提交信息）和**邮件正文**（即代码差异）。

    - **设计目的**：用于通过邮件列表发送代码提交，可以被 git
      am完整解析并重建提交。

2.  **git diff生成的是"纯差异补丁"**

    - **内容**：它**只包含**代码差异部分，没有任何额外的元数据。

    - **设计目的**：仅用于传递代码变更，不关心提交历史。

**直观对比**

假设你对 README.md做了一次提交，以下是两种补丁文件的**内容概览**：

**git format-patch -1 HEAD生成的 0001-xxx.patch文件内容结构：**

> From 123abc\... Mon Sep 1 12:00:00 2024 \<\-- 邮件头开始
>
> From: 张三 \<zhangsan@example.com\>
>
> Date: Mon, 1 Sep 2024 12:00:00 +0800
>
> Subject: \[PATCH\] 更新文档说明
>
> \-\--
>
> README.md \| 2 +-
>
> 1 file changed, 1 insertion(+), 1 deletion(-)
>
> diff \--git a/README.md b/README.md \<\-- 差异内容开始
>
> index abc1234..def5678 100644
>
> \-\-- a/README.md
>
> +++ b/README.md
>
> @@ -1,5 +1,5 @@
>
> \# 项目简介
>
> -这是一个旧描述。
>
> +这是一个新描述。
>
> **git diff HEAD\~1 HEAD生成的 change.patch文件内容结构：**
>
> diff \--git a/README.md b/README.md \<\-- 直接就是差异内容
>
> index abc1234..def5678 100644
>
> \-\-- a/README.md
>
> +++ b/README.md
>
> @@ -1,5 +1,5 @@
>
> \# 项目简介
>
> -这是一个旧描述。
>
> +这是一个新描述。

**如果混用会发生什么？**

- **用 git apply去应用 format-patch的补丁**：

git apply会尝试从文件开头直接解析差异块，但它遇到 From
123abc\...这样的邮件头时会完全无法识别，导致报错：error: corrupt patch
at line 5\...。

- **用 git am去应用 git diff的补丁**：

git
am期望一个带有完整邮件头的补丁。当它发现文件开头没有标准的邮件头时，会报错，因为它无法确定作者、提交者等信息来创建提交。

**正确配对与转换**

请始终坚持以下配对：

- **生成**：git diff→ **应用**：git apply

- **生成**：git format-patch→ **应用**：git am

**特殊情况**：如果你只有一个
format-patch生成的邮件补丁，但只想应用代码变化而不保留提交信息，可以使用工具**提取**出纯差异部分：

\# 从 format-patch 生成的补丁中提取出纯差异，再用 git apply

git mailinfo -k my_email.patch \| git apply

但这属于特殊情况处理，通常情况请严格遵循正确的命令配对。

## 如何合并第三方代码？

\--todo

技术上，如果一件事情很难做，可能是方法不对，换个思路和方法，说不定很容易解决。尤其那种拼体力的活，一定有巧妙的方法可以解决。历史上有些技术看上去是偷懒，实际上是技术进步。

合入第三方代码修改，最差的办法就是beyondcompare逐个文件一行一行比较，修改很多的时候累死人，而且容易疏忽，用git打patch再应用patch是最靠谱又快速的方法。比如两个版本......

得用git的思路

git打patch前先把不需要的文件删掉

相较于git，beyondcompare既费力效率低又容易出错

对于双方都在改的代码，有什么好办法合并修改

再本地打patch比较确认修改到位

git合并完后使用beyondcompare比较，而不是通过beyondcompare比较来合并

sourcegit确认

以wpa_supplicant的两次提交为实例进行说明

## 不是git库管理的目录，怎么打patch？

有时候需要将修改给到其他人，但是代码不是用git库管理的，改动大的时候一行一行照着改费时间。

可以将修改代码的目录初始化为一个git库，再打patch。具体操作步骤如下：

1.打patch的一方，有两份代码：一份代码是原始的、没有修改，一份代码是修改过的。首先将原始代码目录初始化成git库，git
init，git add，git
commit；然后把原始代码目录下的.git库目录拷贝到修改过代码所在目录，此时git
status就可以看到哪些文件修改过，然后git add、git commit将修改提交，再git
format-patch生成patch文件。

或者，直接使用diff命令将两个目录的差异生成patch文件，git diff \>
modify.patch。

2.应用patch的一方，同样的操作，将需要应用patch的目录初始化成git库目录：git
init，git add，git commit，然后git am/apply应用patch。

如果以后不需要git库了那么可以删除.git目录。

\--直接用diff工具就可以了，diff是linux命令，并非git专有，可以直接使用，git
diff也是使用diff命令。

## linux打补丁和git打patch方法

<http://blog.chinaunix.net/uid-29140689-id-4030348.html>

一、linux打补丁方法\
1、处理单个文件补丁的方法：\
\$ diff -uN from-file to-file \>to-file.patch //产生补丁\
\$ patch -p0 \< to-file.patch //打补丁\
\$ patch -RE -p0 \< to-file.patch //取消补丁\
\
2、对整个文件夹打补丁的情况：\
\$ diff -uNr  from-dir to-dir \> my.patch //产生补丁\
\$ patch -p1 \< my.patch //打补丁\
\$ patch -R -p1 \<to-docu.patch //取消补丁

注，冲突：\
.orig 合并前文件备份。\
.rej 文件里是冲突没合入的内容。

二、git打patch方法\
1、git format-patch  (推荐)\
只适用于git的patch，包含diff信息，包含提交人，提交时间等。\
如果git format-patch生成的补丁不能打到当前分支，git
am会给出提示，并协助你完成打补丁工作。\
例如从master checkout一个新分支修改然后与master对比生成patch。git
format-patch -M master //-M选项表示这个patch要和那个分支比对。\
git am 001-xxx.patch(不必重新commit)\
\
2、git diff \
生成标准的patch，只包含diff信息\
git diff生成的patch兼容性强，可以用git apply
\--check查看补丁是否能够干净顺利地应用到当前分支中。\
例如从master checkout一个新分支修改然后与master对比生成patch，git diff
master \> xxx.patch，git apply xxx.patch(需要重新commit)。

假如，有这样的目录层次x/xx/xxx/xxx/ttt.c，

而我的当前位置是在x/下，执行git diff\> test.patch

在test.patch补丁文件里的路径信息是这样的：

\- - - a/xx/xxx/xxx   

+++b/xx/xxx/xxx   

如果应用test.patch的时候的位置是在x/下，那么执行patch -p1 \<
test.patch。

或者使用git apply
test.patch打补丁,执行这个命令的位置也是在哪里制作的patch，就在哪里执行此命令。

## 打patch \-- 更多介绍

**如何打patch 及git打patch 失败的处理方法**

https://blog.csdn.net/RonnyJiang/article/details/54342871

最近分配了一些打patch的任务。打的那个叫稀巴烂。想必对我很失望。这个过程中学到了如何打patch.

正常来说我们打的git生成的标准patch如果没有没有问题那很好打。

　只需要进入patch对应的代码树，然后执行git am
\$patchdir/\*\*\*\*\*.patch   就可以把对应的patch打进去了

** (最好使用git am \--keep-cr
\$patchdir/\*\*\*\*\*.patch，这样\*nix系统和windows的换行问题应该就避免掉了，强烈建议始终加\--keep-cr参数)**

 (如果很小的patch，行号不对也可以尝试用git am -3 
\$patchdir/\*\*\*\*\*.patch  这样会强制merge，但未必每次都可以merge)

 

 
往往一个patch下涉及一个git库中的多个文件，很容易失败。如果失败了可以用git
am \--abort，放弃此次的patch。这样本次patch操作失效。但毕竟patch
abort了，并没有打上，没有解决我们的问题。

  
正如你所见，如果冲突发生，git只是输出上述信息，然后就停下来。一个小冲突会导致整个patch都不会被集成。

打patch执行: **  git am \--keep-cr
../94.21/device/common/0025-build-recovery.img-after-boot.img-was-generated.patch**

报错如下：

Applying: build boot-with-sig.img after boot.img was generated

/home/ronny/mypatch/mydevice/.git/rebase-apply/patch:51: trailing
whitespace.

\$(PRODUCT_OUT)/boot.toc: \$(PRODUCT_OUT)/boot-with-sig.img
\$(SECURE_SDK_DIR)

error: patch failed: hk388/hk388.mk:167

error: hk388/hk388.mk: patch does not apply

Patch failed at 0001 build boot-with-sig.img after boot.img was
generated

When you have resolved this problem run \"git am \--resolved\".

If you would prefer to skip this patch, instead run \"git am \--skip\".

To restore the original branch and stop patching run \"git am
\--abort\".

** 简单的方法**：

 处理这种问题的最简单方法是先使用 git am
\--abort，然后手动的添加此patch, patch -p1 \<
PATCH，手动解决掉代码冲突，最后使用 git commit -a
提交代码。但是这样做有个问题就是你会失去PATCH中原本包含的commit信息(比如From，Date，Subject，Signed-off-by等)。

**这里需要注意的是手动解决错误在用patch
-p时注意层数的问题，怎么确定层数呢？**

参数-p来指定从第几层开始比较。比如有一个patch文件的补丁头是这样的：

代码:

\-\-- old/modules/pcitableMon Sep 27 11:03:56 1999+++
new/modules/pcitableTue Dec 19 20:05:41 2000

如果使用参数-p0，就表示从当前目录，找一个叫作new的目录，在它下面找一个叫modules的目录，再在它下面找一个叫pcitableMon的目录。

如果使用参数-p1,就表示忽略第一层，从当前目录找一个叫modules的目录，在它下面找一个叫modules的目录。这样会忽略掉补丁头提到的new目录。

依此类推。

应该有一种更聪明的方法。

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--

即：在 .git/rebase-apply 目录下，存放着相应的补丁文件，名字是"0001"
(在更新的git版本中，存放补丁文件的目录名有所改变，这里使用的git版本是
1.7.9.5)。

事实上，你可以使用 git apply 命令打patch(git apply
是git中的patch命令)。如同使用 patch -p1
命令时一样，然后手动解决代码冲突(检视生成的 .rej
文件，与冲突文件比较，修改冲突内容，并最终把文件加入到index中)：

 \$ git apply PATCH \--reject    (这里的PATCH即为.git/rebase-apply
目录下的0001，如果我们输入git am
\--abort那么。git下就会清除掉rebase-apply目录，属于白玩了)

\$ edit edit edit

(译注：根据.rej文件手动解决所有冲突)

\$ git add FIXED_FILES

\$ git am \--resolved   

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--

eg：现在来处理上面patch failed问题：

ronny@ronny:\~/mypatch/mydevice\$ git apply
.git/rebase-apply/　　　　　(提示中的0001即为我们要的patch)

0001               applying           final-commit      
keep               msg                next              
patch              scissors           threeway           

abort-safety       apply-opt          info              
last               msg-clean          no_inbody_headers 
quiet              sign               utf8               

ronny@ronny:\~/mypatch/mydevice\$ **git apply .git/rebase-apply/0001
\--reject**

.git/rebase-apply/0001:64: trailing whitespace.

\$(PRODUCT_OUT)/boot.toc: \$(PRODUCT_OUT)/boot-with-sig.img
\$(SECURE_SDK_DIR)

Checking patch

\.....

error: patch failed: hk388/hk388.mk:167

Applying patch\.....

Rejected hunk #1.

Rejected hunk #2.

Rejected hunk #3.

Applying patch hk388/hk388.mk with 1 rejects\...

Rejected hunk #1.

ronny@ronny:\~/mypatch/mydevice\$ **git status**

\# On branch master

\# Your branch is ahead of \'origin/master\' by 22 commits.

\#

\# Changes not staged for commit:

#   (use \"git add \<file\>\...\" to update what will be committed)

#   (use \"git checkout \-- \<file\>\...\" to discard changes in working
directory)

\#

#    modified:   hk388/Android.mk

#    modified:   hk388/init.rc

\# Untracked files:

#   (use \"git add \<file\>\...\" to include in what will be committed)

\#

#    hk388/init.rc.rej　

#    hk388/hk388.mk.rej

nothing added to commit but untracked files present (use \"git add\" to
track)

这样就产生了２个.rej。然后手动解决代码冲突(检视生成的２个 .rej
文件，与冲突文件比较，修改冲突内容，并最终把文件加入到index中)：

提示：上面的modified:  
hk388/Android.mk　在下面并没有hk388/Android.mk.rej说明这个文件的的修改是ok的，并没有冲突

ronny@ronny:\~/mypatch/mydevice\$ **vim hk388/Android.mk
hk388/Android.mk.rej -O **   (-O 
大O是纵向打开两个窗口，小o是横向打开两个窗口)

然后看hk388/Android.mk.rej涉及到要改的内容，在 hk388/Android.mk改掉就好

**最后git add hk388/Android.mk**

**  　  git add hk388/init.rc**

** 　    git add hk388/hk388.mk**

**　 　git am \--resolved   (完毕)**

就这么简单！

想多一些解释，好吧。git am 并不改变index，你需要使用 git apply \--reject
打patch(patch保存在 .git/rebase-apply中我这里叫0001)，手动解决代码冲突，

(译注：使用 git status
列出所有涉及文件)，把所有文件(不仅仅是引起冲突的文件)添加到(git
add)index，最后告诉 git am 你已经解决(\--resolved)了问题。

这样做的好处是你不需要重新编辑commit信息。而且，如果你正在打的是一系列patch(就是说你在打的是多个patch，比如
git am \*.patch)你不需要使用 git am \--abort，然后又 git am。

**patch命令里面的层数-p0 -p1**

参数-p来指定**从第几层开始比较**。比如有一个patch文件的补丁头是这样的：

\-\-- old/modules/pcitableMon Sep 27 11:03:56 1999

+++ new/modules/pcitableTue Dec 19 20:05:41 2000

如果使用参数-p0，就表示从当前目录，找一个叫作new的目录，在它下面找一个叫modules的目录，再在它下面找一个叫pcitableMon的目录。

如果使用参数-p1,就表示忽略第一层，从当前目录找一个叫modules的目录，在它下面找一个叫modules的目录。这样会忽略掉补丁头提到的new目录。

# 13)查找/搜索

## git查找/搜索

**1. git log \--grep，在提交注释中搜索**

git log \--grep eslint //在提交注释中搜索eslint关键词

git log \--grep \--oneline eslint //在提交注释中搜索eslint关键词,
简化输出信息

git log \--grep=\'eslint\' \--oneline

git log \--grep eslint \--author liangyuetian@outlook.com
//在提交注释中搜索eslint关键词,并且筛选提交人

**2. git grep/git log -S/-G/-L，在提交内容中搜索**

git grep eslint //在提交文件中搜索关键词

git grep -n eslint //-n 显示行号

git grep \--count \'pay_box\' //\--count只输出匹配的文件和匹配的个数

git grep -p \'pay_box\' //-p输出前后字符，用来判断这个关键字的类型

git log -S eslint
//查看关键字是什么时候引入的，可以使用-S选项来显示新增和删除该字符串的提交

git log -S eslint \--oneline //简化输出信息

git log -S \'eslint\' \--pretty=format:\'%h %ad %s\' \--date=short

git log -G \'MicVolume\|Video\' \--all \--pretty=format:\'%h %ad %s\'
\--date=short //正则匹配（改名、附近一起改也算）

git log -L :countDownDiff:date.js
//查看指定文件、指定函数的变更记录。注意冒号:紧挨着函数名countDownDiff，-L后有空格。

git show fa83f9d3 -p \| grep -n -C 8 \'Video\\\|MicVolume\'
//看某个提交里具体删了什么

**1.查找某个关键字(比如函数名)：**

\$ git grep xmmap

config.c: contents = xmmap(NULL, contents_sz, PROT_READ,

diff.c: s-\>data = xmmap(NULL, s-\>size, PROT_READ, MAP_PRIVATE, fd, 0);

git-compat-util.h: extern void \*xmmap(void \*start, size_t length, int
prot, int fla

read-cache.c: mmap = xmmap(NULL, mmap_size, PROT_READ \| PROT_WRITE,
MAP_PRIVATE,

refs.c: log_mapped = xmmap(NULL, mapsz, PROT_READ, MAP_PRIVATE, logfd,
0);

sha1_file.c: map = xmmap(NULL, mapsz, PROT_READ, MAP_PRIVATE, fd, 0);

sha1_file.c: idx_map = xmmap(NULL, idx_size, PROT_READ, MAP_PRIVATE, fd,
0);

sha1_file.c: win-\>base = xmmap(NULL, win-\>len,

sha1_file.c: map = xmmap(NULL, \*size, PROT_READ, MAP_PRIVATE, f

sha1_file.c: buf = xmmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

wrapper.c: void \*xmmap(void \*start, size_t length,

 

1.1 如果要显示行号，添加'-n'选项：

\$ git grep -n xmmap

config.c:1016: contents = xmmap(NULL, contents_sz, PROT_READ,

diff.c:1833: s-\>data = xmmap(NULL, s-\>size, PROT_READ, MAP_PRIVATE,
fd,

git-compat-util.h:291: extern void \*xmmap(void \*start, size_t length,
int prot, int

read-cache.c:1178: mmap = xmmap(NULL, mmap_size, PROT_READ \|
PROT_WRITE, MAP\_

refs.c:1345: log_mapped = xmmap(NULL, mapsz, PROT_READ, MAP_PRIVATE,
logfd, 0);

sha1_file.c:377: map = xmmap(NULL, mapsz, PROT_READ, MAP_PRIVATE, fd,
0);

sha1_file.c:479: idx_map = xmmap(NULL, idx_size, PROT_READ, MAP_PRIVATE,
fd

sha1_file.c:780: win-\>base = xmmap(NULL, win-\>len,

sha1_file.c:1076: map = xmmap(NULL, \*size, PROT_READ, MAP_PR

sha1_file.c:2393: buf = xmmap(NULL, size, PROT_READ, MAP_PRIVATE, fd

wrapper.c:89: void \*xmmap(void \*start, size_t length,

 

1.2 如果只显示文件名，添加'\--name-only'选项：

\$ git grep \--name-only xmmap

config.c

diff.c

git-compat-util.h

read-cache.c

refs.c

sha1_file.c

wrapper.c

 

1.3 统计每个文件里有多少行匹配内容，添加'-c'选项：

\$ git grep -c xmmap

config.c:1

diff.c:1

git-compat-util.h:1

read-cache.c:1

refs.c:1

sha1_file.c:5

wrapper.c:1

 

1.4 查找git仓库里某个特定版本里的内容，添加tag名或sha号：

\$ git grep xmmap v1.5.0

v1.5.0:config.c: contents = xmmap(NULL, st.st_size, PROT_READ,

v1.5.0:diff.c: s-\>data = xmmap(NULL, s-\>size, PROT_READ, MAP_PRIVATE,
fd,

v1.5.0:git-compat-util.h:static inline void \*xmmap(void \*start, size_t
length,

v1.5.0:read-cache.c: cache_mmap = xmmap(NULL, cache_mmap_size,

v1.5.0:refs.c: log_mapped = xmmap(NULL, st.st_size, PROT_READ,
MAP_PRIVATE, logfd

v1.5.0:sha1_file.c: map = xmmap(NULL, st.st_size, PROT_READ,
MAP_PRIVATE, fd,

v1.5.0:sha1_file.c: idx_map = xmmap(NULL, idx_size, PROT_READ,
MAP_PRIVATE, fd

v1.5.0:sha1_file.c: win-\>base = xmmap(NULL, win-\>len,

v1.5.0:sha1_file.c: map = xmmap(NULL, st.st_size, PROT_READ,
MAP_PRIVATE, fd,

v1.5.0:sha1_file.c: buf = xmmap(NULL, size, PROT_READ, MAP_PRIVATE, fd

 

1.5
查找git仓库里某个特定版本、特定文件里的内容(省略版本，默认当前版本)，添加tag名或sha号、文件名：

\$ git grep xmmap v1.5.0 diff.c

v1.5.0:diff.c: s-\>data = xmmap(NULL, s-\>size, PROT_READ, MAP_PRIVATE,
fd,

 

**2. 某些关键字的逻辑组合**

2.1 与逻辑：某一行既包括\...又包括\...

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep -e \'pu\' \--and -e
\'lic\'

a.txt:public

c.txt:public

c.txt:public

 

2.2 或逻辑：某一行包括\...或者包括\...

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep -e \'public\' \--or
-e \'void\'

a.txt:public

a.txt:void

b.txt:void

c.txt:public

c.txt:public

 

\--or 是默认行为，如果省略：

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep -e \'public\' \--or
-e \'void\'

a.txt:public

a.txt:void

b.txt:void

c.txt:public

c.txt:public

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep -e \'public\' -e
\'void\'

a.txt:public

a.txt:void

b.txt:void

c.txt:public

c.txt:public 

 

2.3 非逻辑：某一行不包括\...

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep \--not -e \'public\'

a.txt:ab

a.txt:bc

a.txt:void

b.txt:void

b.txt:aaa

b.txt:bbb

c.txt:kkkk

c.txt:sfs

c.txt:l

 

2.4 组合逻辑：与或非的组合(为测试组合逻辑，又在库中新添加了d.txt文件)

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep -e \'public\' \--and
\\( -e \'void\' -e \'return\' \\)

d.txt:public void int save

d.txt:public void string save

d.txt:public return a

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep -e \'public\' \--and
\\( -e \'void\' \--or -e \'return\' \\)

d.txt:public void int save

d.txt:public void string save

d.txt:public return a

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep -e \'public\' \--and
\\( -e \'void\' \--and -e \'int\' \\)

d.txt:public void int save

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep -e \'public\' \--and
\\( \--not -e \'int\' \\)

a.txt:public

c.txt:public

c.txt:public

d.txt:public void string save

d.txt:public return a 

 

2.5 全匹配：某一文件既包含\...又包含\...

\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\>\$ git grep \--all-match -e
\'public\' -e \'void\'

a.txt:public

a.txt:void

d.txt:public void int save

d.txt:public void string save

d.txt:public return a

 

2.6 以上各个命令还可以加'-n\'、'-c'、'\--name-only'、版本、文件等限制

2.7** **查找**某个字符串在何时添加**

git log -S\"string wanted to search\" \--oneline

81fbf7e a commit

来源：https://www.cnblogs.com/drizzlewithwind/p/5728761.html

## git查找/搜索

无论仓库里的代码量有多少，你经常需要查找一个函数是在哪里调用或者定义的，或者一个方法的变更历史。
git
提供了两个有用的工具来快速地从它的[数据库](https://cloud.tencent.com/solution/database?from=10680)中浏览代码和提交。
我们来简单的看一下。

### \* \--grep/grep/-S/-G/-L

\--grep/grep/-S/-G/-L的用法，以及区别，见：git
\--grep、grep、-S、-G、-L.mhtml、git \--grep、grep、-S、-G、-L \_2.mhtml

### [git grep](https://git-scm.com/book/zh/v2/Git-%E5%B7%A5%E5%85%B7-%E6%90%9C%E7%B4%A2#Git-Grep)，提交内容查找

git提供了一个 grep
命令，你可以很方便地从提交历史或者工作目录中查找一个字符串或者正则表达式。我们用git本身源代码的查找作为例子。

默认情况下git会查找你工作目录的文件。 你可以传入 -n 参数来输出 git
所找到的匹配行行号。

\$ git grep -n gmtime_r

compat/gmtime.c:3:#undef gmtime_r

compat/gmtime.c:8: return git_gmtime_r(timep, &result);

compat/gmtime.c:11:struct tm \*git_gmtime_r(const time_t \*timep, struct
tm \*result)

compat/gmtime.c:16: ret = gmtime_r(timep, result);

compat/mingw.c:606:struct tm \*gmtime_r(const time_t \*timep, struct tm
\*result)

compat/mingw.h:162:struct tm \*gmtime_r(const time_t \*timep, struct tm
\*result);

date.c:429: if (gmtime_r(&now, &now_tm))

date.c:492: if (gmtime_r(&time, tm)) {

git-compat-util.h:721:struct tm \*git_gmtime_r(const time_t \*, struct
tm \*);

git-compat-util.h:723:#define gmtime_r git_gmtime_r

grep 命令有一些有趣的选项。

例如，你可以使用 \--count 选项来使 git
输出概述的信息，仅仅包括哪些文件包含匹配以及每个文件包含了多少个匹配。

\$ git grep \--count gmtime_r

compat/gmtime.c:4

compat/mingw.c:1

compat/mingw.h:1

date.c:2

git-compat-util.h:2

如果你想看匹配的行是属于哪一个方法或者函数，你可以传入 -p 选项：

\$ git grep -p gmtime_r \*.c

date.c=static int match_multi_number(unsigned long num, char c, const
char \*date, char \*end, struct tm \*tm)

date.c: if (gmtime_r(&now, &now_tm))

date.c=static int match_digit(const char \*date, struct tm \*tm, int
\*offset, int \*tm_gmt)

date.c: if (gmtime_r(&time, tm)) {

在这里我们可以看到在 date.c 文件中有 match_multi_number 和 match_digit
两个函数调用了gmtime_r。

你还可以使用 \--and
标志来查看复杂的字符串组合，也就是在同一行同时包含多个匹配。
比如，我们要查看在旧版本 1.8.0 的 git 代码库中定义了常量名包含 "LINK"
或者 "BUF_MAX" 这两个字符串所在的行。

这里我们也用到了 \--break 和 \--heading 选项来使输出更加容易阅读。

\$ git grep \--break \--heading \\

-n -e \'#define\' \--and \\( -e LINK -e BUF_MAX \\) v1.8.0

v1.8.0:builtin/index-pack.c

62:#define FLAG_LINK (1u\<\<20)

v1.8.0:cache.h

73:#define S_IFGITLINK 0160000

74:#define S_ISGITLINK(m) (((m) & S_IFMT) == S_IFGITLINK)

v1.8.0:environment.c

54:#define OBJECT_CREATION_MODE OBJECT_CREATION_USES_HARDLINKS

v1.8.0:strbuf.c

326:#define STRBUF_MAXLINK (2\*PATH_MAX)

v1.8.0:symlinks.c

53:#define FL_SYMLINK (1 \<\< 2)

v1.8.0:zlib.c

30:/\* #define ZLIB_BUF_MAX ((uInt)-1) \*/

31:#define ZLIB_BUF_MAX ((uInt) 1024 \* 1024 \* 1024) /\* 1GB \*/

相比于一些常用的搜索命令比如 grep 和 ack，git grep 命令有一些的优点。
第一就是速度非常快，第二是你不仅仅可以可以搜索工作目录，还可以搜索任意的
git 树。 在上一个例子中，我们在一个旧版本的 git
源代码中查找，而不是当前检出的版本。

[git grep支持正则表达式，git grep -n -E \"regular
expression\"，和grep是一样的。]{.mark}

### git log \--grep，提交注释查找

git log \--grep查找注释中包含指定字符串的提交，提交注释：git commit -m
\"注释\"。

\$ git log \--grep tcpdump

commit 560620ae0fa17d13c37fcdd7b62967f5e5708ac9

Author: dukang \<gaheadus@126.com\>

Date: Sun Aug 28 11:06:28 2022 +0800

增加tcpdump使用

对比git grep查找的是提交内容

\$ git grep tcpdump

wifi_bluetooth/工具与使用.md:\$ tcpdump
//不加任何参数，默认情况下将抓取第一个非lo网卡上所有的数据包

wifi_bluetooth/工具与使用.md:\$ tcpdump -D //命令查看哪些接口可用于捕获

wifi_bluetooth/工具与使用.md:\$ tcpdump -i eth0
//选择接口(网卡)。tcpdump -i any抓所有接口

wifi_bluetooth/工具与使用.md:\$ tcpdump -i eth0 -w test.pcap
//保存到文件。有的系统抓包过程中查看文件大小为0，需要将tcpdump进程杀掉，才会才会将抓包写到文件。

### git log -S / -G，提交内容查找：查找字符串的新增或删除

或许你不想知道某一项在哪里，而是想知道是什么时候存在或者引入的。 git log
命令有许多强大的工具可以通过提交信息甚至是 diff
的内容来找到某个特定的提交。

例如，如果我们想找到 ZLIB_BUF_MAX
常量是什么时候引入的，我们可以使用-S选项来显示新增和删除该字符串的提交。

\$ git log -S ZLIB_BUF_MAX \--oneline

e01503b zlib: allow feeding more than 4GB in one go

ef49a7a zlib: zlib can only process 4GB at a time

如果我们查看这些提交的diff，我们可以看到在 ef49a7a
这个提交引入了常量，并且在 e01503b 这个提交中被修改了。

如果你希望得到更精确的结果，你可以使用-G选项来使用正则表达式搜索。

-S\"\<string\>\"、-G\"\<string\>\"：**仅显示添加或删除内容匹配指定字符串的提交**。修改内容不能匹配？

假设你想知道Hello,World!这句话，是什么时候加入到项目里去的，可以用：git
log -S\"Hello,World!\"。

另外，如果你想使用**正则表达式**去匹配，而不是字符串，那么你可以使用**-G**代替-S。

这是一个非常有用的debug工具，使用他可以定位所有跟某行代码相关的commit，甚至可以查看某行是什么时候被copy的，什么时候移到另外一个文件中去的。

注意：-S后没有\"=\"，与查询内容之间也没有空格符。

### git log -L，提交内容查找：行日志搜索

行日志搜索是另一个相当高级并且有用的日志搜索功能。
这是一个最近新增的不太知名的功能，但却是十分有用。 在 git log 后加上 -L
选项即可调用，它可以展示代码中一行或者一个函数的历史。

例如，假设我们想查看 zlib.c 文件中git_deflate_bound
函数的每一次变更，我们可以执行 git log -L:git_deflate_bound:zlib.c。 git
会尝试找出这个函数的范围，然后查找历史记录，并且显示从函数创建之后一系列变更对应的补丁。

\$ git log -L:git_deflate_bound:zlib.c

commit ef49a7a0126d64359c974b4b3b71d7ad42ee3bca

Author: Junio C Hamano \<gitster@pobox.com\>

Date: Fri Jun 10 11:52:15 2011 -0700

zlib: zlib can only process 4GB at a time

diff \--git a/zlib.c b/zlib.c

\-\-- a/zlib.c

+++ b/zlib.c

@@ -85,5 +130,5 @@

-unsigned long git_deflate_bound(z_streamp strm, unsigned long size)

+unsigned long git_deflate_bound(git_zstream \*strm, unsigned long size)

{

\- return deflateBound(strm, size);

\+ return deflateBound(&strm-\>z, size);

}

commit 225a6f1068f71723a910e8565db4e252b3ca21fa

Author: Junio C Hamano \<gitster@pobox.com\>

Date: Fri Jun 10 11:18:17 2011 -0700

zlib: wrap deflateBound() too

diff \--git a/zlib.c b/zlib.c

\-\-- a/zlib.c

+++ b/zlib.c

@@ -81,0 +85,5 @@

+unsigned long git_deflate_bound(z_streamp strm, unsigned long size)

+{

\+ return deflateBound(strm, size);

+}

\+

如果 git
无法计算出如何匹配你代码中的函数或者方法，你可以提供一个正则表达式。
例如，这个命令和上面的是等同的：git log -L \'/unsigned long
git_deflate_bound/\',/\^}/:zlib.c。
你也可以提供单行或者一个范围的行号来获得相同的输出。

来源：https://cloud.tencent.com/developer/article/1434771

**[-L\<start\>,\<end\>:\<file\>, -L:\<funcname\>:\<file\>]{.mark}**

Trace [the evolution of]{.mark} the line range given by
\<start\>,\<end\>, or by the function name regex \<funcname\>, within
the \<file\>. You may not give any pathspec limiters. This is currently
limited to a walk starting from a single revision, i.e., you may only
give zero or one positive revision arguments, and \<start\> and \<end\>
(or \<funcname\>) must exist in the starting revision. You can specify
this option more than once. Implies \--patch. Patch output can be
suppressed using \--no-patch, but other diff formats (namely \--raw,
\--numstat, \--shortstat, \--dirstat, \--summary, \--name-only,
\--name-status, \--check) are not currently implemented.

\<start\> and \<end\> can take one of these forms:

• number

If \<start\> or \<end\> is a number, it specifies an absolute line
number (lines count from 1).

• /regex/

This form will use the first line matching the given POSIX regex. If
\<start\> is a regex, it will search from the end of the previous -L
range, if any, otherwise from the start of file. If \<start\> is
\^/regex/, it will search from the start of file.

If \<end\> is a regex, it will search starting at the line given by
\<start\>.

• +offset or -offset

This is only valid for \<end\> and will specify a number of lines before
or after the line given by \<start\>.

## git bisect二分查找

git
bisect是git提供的一个二分查找工具，用于快速定位引入bug的具体提交(commit)。\--
git binary section

它通过交互式地在"好(good)"和"坏(bad)"提交之间进行二分搜索，高效缩小问题范围。

**使用步骤(精要版)**

第1步：启动bisect

git bisect start

第2步：标记一个已知"坏"的提交(通常为当前HEAD)

git bisect bad \# 默认标记当前提交为bad

git bisect bad \<commit\> \# 或指定某个commit

第3步：标记一个已知"好"的提交(bug不存在的版本)

git bisect good \<commit\> \# 例如git bisect good SHA。必须确保
\<commit\> 确实没有该bug

第4步：git自动检出中间提交 → 你测试并反馈结果。

git会自动checkout到"好"与"坏"之间的中间提交，你需要手动测试当前代码是否存在bug。

如果 有bug(坏)，则标记bad：

git bisect bad

如果 无bug(好) ，则标记good：

git bisect good

git会继续二分，直到找到第一个引入bug的提交。

第5步：定位完成，退出bisect

当git找到罪魁祸首时，会输出类似：

\<commit-hash\> is the first bad commit

此时退出查找并回到原分支：

git bisect reset

这会结束bisect会话，并恢复到最初执行bisect start时的分支状态。

**注意事项**

确保"好"提交确实没有bug，"坏"提交确实有bug。测试过程应可重复、稳定(避免环境干扰)。

bisect 期间不要手动切换分支或修改工作区(除非用于测试)。

若遇到无法测试的提交(如编译失败)，可用：

git bisect skip

git会尝试其他路径。

**高级技巧**

自动化测试(推荐)

如果你有自动化测试脚本(如npm test、pytest等)，可让git自动判断：

git bisect start

git bisect bad HEAD

git bisect good v1.0

git bisect run ./test-script.sh

脚本返回 0 → git视为 good

脚本返回 非0 → git视为 bad

极大提升效率，避免人工重复测试。

查看当前bisect状态

git bisect log \# 显示已标记的good/bad提交历史

git bisect visualize \# 在图形工具中查看(需配置)

中途中止

git bisect reset \# 任何时候都可退出

# 14)新功能，新命令

## git worktree

### 基础

**.git仓库目录、工作目录、主工作树、链接工作树。**

**worktree**、**工作树**、**工作目录**、**工作区** \--**是同一个意思**

![](media/image285.png){width="5.973611111111111in"
height="2.303472222222222in"}

**目录结构Directory Structure**

![](media/image286.png){width="6.0in" height="2.1708333333333334in"}

**[One repository, multiple independent working copies]{.mark}**.

The core concept is \"[One Brain (.git), Multiple Bodies (Working
Directories).]{.mark}\" It\'s much more efficient than running clone
multiple times.

Using Worktree reduces context switching costs to near zero. [Different
branches are physically spread out in different folders]{.mark}.

**语法SYNOPSIS**

git worktree add \<path\>

git worktree add \<path\> \[branch\]

git worktree add \<path\> \[commit\]

git worktree add \[-b new-branch\] \<path\> \[branch\]

git worktree add \[-b new-branch\] \<path\> \[commit\]

[git]{.underline} [worktree]{.underline} [add]{.underline} \[-f\]
\[\--detach\] \[\--checkout\] \[\--lock \[\--reason \<string\>\]\]
\[\--orphan\] \[(-b \| -B) \<new-branch\>\] **\<path\>**
\[\<commit-ish\>\]

[git]{.underline} [worktree]{.underline} [list]{.underline} \[-v \|
\--porcelain \[-z\]\]

[git]{.underline} [worktree]{.underline} [remove]{.underline} \[-f\]
\<worktree\>

[git]{.underline} [worktree]{.underline} [move]{.underline} \<worktree\>
\<new-path\>

[git]{.underline} [worktree]{.underline} [prune]{.underline} \[-n\]
\[-v\] \[\--expire \<expire\>\]

[git]{.underline} [worktree]{.underline} [repair]{.underline}
\[\<path\>\...\]

[git]{.underline} [worktree]{.underline} [lock]{.underline} \[\--reason
\<string\>\] \<worktree\>

[git]{.underline} [worktree]{.underline} [unlock]{.underline}
\<worktree\>

git worktree lets you create **[multiple working
directories]{.mark}** from [**a** **single Git repository**]{.mark},
each tied to its own branch. This enables true **[parallel]{.mark}**
development without constantly switching branches or using git stash.

**Key benefits**:

- [**Multiple** branches checked out **simultaneously**.]{.mark}

- [All worktrees **share the same .git data**, saving disk
  space.]{.mark}

- No need for temporary commits or stashes when switching tasks.

**Creating a new worktree with a new branch**

Create a new branch and worktree in one step

\$ git worktree add -b feature/login ../my-project-login

This creates:

1.  feature/login branch.

2.  ../my-project-login directory with that branch checked out.

**Using an existing branch**

\$ git worktree add ../my-project-hotfix hotfix/bug-123

The branch must already exist.

**Listing worktrees**

\$ git worktree list

**Removing a worktree**

\$ git worktree remove ../my-project-login

If you deleted the folder manually, clean up with:

\$ git worktree prune

**Important notes**

- [A branch can only be checked out in **one** worktree at a
  time]{.mark}.

- Worktrees are lightweight: [**.git** objects are **shared**]{.mark},
  only [**working files** are **duplicated**]{.mark}.

- [Removing a worktree does **not** delete its branch --- delete
  branches separately if needed]{.mark}.

- Always use git worktree remove instead of manually deleting the folder
  to avoid stale references.

**Example: emergency fix without touching current work**

\$ git worktree add -b hotfix/critical ../hotfix-dir

\$ cd ../hotfix-dir

make changes

\$ git commit -am \"Critical fix\"

\$ git push origin hotfix/critical

\$ cd ../my-project

\$ git worktree remove ../hotfix-dir

This keeps your original work untouched while handling urgent tasks
efficiently.

**DESCRIPTION**

[Manage **multiple working trees** attached to **the same git
repository**]{.mark}.

A git repository can support multiple working trees, allowing you to
[check out more than one branch at a time]{.mark}. With **git worktree
add** a new working tree is associated with the repository, along with
additional metadata that differentiates that working tree from others in
the same repository. The working tree, along with this metadata, is
called a \"**worktree**\".

This new worktree is called a \"**[linked worktree]{.mark}**\" as
opposed to the \"**[main worktree]{.mark}**\" prepared by
**git‐init**(1) or **git‐clone**(1). [A repository has one main worktree
(if it's not a bare repository) and zero or more linked
worktrees]{.mark}. When you are done with a linked worktree, remove it
with **git worktree remove**.

In its simplest form, **git worktree add** [\<path\>]{.underline}
automatically creates a new branch whose name is the final component of
[\<path\>]{.underline}, which is convenient if you plan to work on a new
topic. For instance, **[git worktree add ../hotfix]{.mark}** creates new
branch **hotfix** and checks it out at path **../hotfix**. To instead
work on an existing branch in a new worktree, use [**git worktree add**
[\<path\>]{.underline} [\<branch\>]{.underline}]{.mark}. On the other
hand, if you just plan to make some experimental changes or do testing
without disturbing existing development, it is often convenient to
create a [throwaway]{.underline} worktree not associated with any
branch. For instance, [**git worktree add -d**
[\<path\>]{.underline}]{.mark} creates a new worktree with a detached
**HEAD** at the same commit as the current branch.

If a working tree is deleted without using **git worktree remove**, then
its associated administrative files, which reside in the repository (see
\"DETAILS\" below), will eventually be removed automatically (see
**gc.worktreePruneExpire** in **git‐config**(1)), or you can run **git
worktree prune** in the main or any linked worktree to clean up any
stale administrative files.

If the working tree for a linked worktree is stored on a portable device
or network share which is not always mounted, you can prevent its
administrative files from being pruned by issuing the **git worktree
lock** command, optionally specifying **\--reason** to explain why the
worktree is locked.

我的理解：

旧版本git，.git仓库目录放在工作目录下，.git仓库目录、git工作目录两者是**绑定**在一起的，是**一对一**的关系。

新版本git
2.5+，.git库目录和工作目录在**逻辑上分离**，虽然在**物理上**.git仓库目录仍然必须放在主工作目录之下，但是在**逻辑上**.git仓库目录不再和工作目录**一一绑定**，在逻辑上一个.git仓库目录可以绑定到多个工作目录，是**一对多**的关系。通过git
worktree
add添加不同工作目录关联到.git库目录，实现多个工作目录对应一个.git库目录，多对一。

旧版本git，创建2个工作目录必然会有2个.git库目录，新版本使用git
worktree创建2个工作目录可以只要1个.git库目录，**节省了.git库目录的存储空间**，**如果.git库占用空间特别大，那么使用worktree有优势**，但是如果.git库占用空间不大，使用worktree完全没有优势，还不如按照旧的方法创建两个.git库，使用起来更方便。如果要临时检出某个分支、某个提交到某个目录，和现有代码做对比，同时存在两个不同版本的代码，效率高，worktree能完美满足要求。

\--腾讯元宝AI回答

传统的 Git
工作区是"工作目录包含.git目录"的紧耦合结构，一个.git目录只能服务一个工作目录。而
git
worktree打破了这种一对一绑定，实现了"一个共享的.git目录服务于多个独立工作目录"的一对多关系。这本质上是将版本控制库(.git)和工作空间进行了**逻辑分离**。

我们可以这样清晰地对比：

**传统模式(Git 2.5 之前)：紧密绑定，一一对应**

my-project/ (唯一的工作目录)

├── .git/ (仓库数据，内嵌于此)

├── src/

└── README.md

- **规则**：一个 .git目录**必须且只能**位于其唯一对应的工作目录(这里是
  my-project)的根目录下。

- **限制**：要同时工作在另一个分支，您必须切换当前目录的状态，或者克隆一份全新的副本(带来完整的.git目录)。

**Worktree 模式(Git 2.5 起)：中心辐射，一对多**

①**主工作树**：

my-project/ (也是一个工作树)

├── .git/ (唯一共享的仓库数据)

├── src/

└── README.md

②**链接工作树**(通过git worktree add 添加的多个**从属工作树**)：

./

├── my-project/ \# 主工作树
（该目录下有一个.git仓库目录，是唯一的仓库数据）

├── my-project-hotfix/ \# 从属工作树1，**链接到**主.git
（该目录下有一个.git文件，注意不是.git目录，链接到.git仓库目录）

├── my-project-feature/ \# 从属工作树2，链接到主.git
（该目录下有一个.git文件）

└── my-experiment/ \# 从属工作树3，链接到主.git
（该目录下有一个.git文件）

- **新规则**：一个.gi目录(位于**主工作树**内)可以作为**中心仓库**，被**多个独立的工作目录**(主工作树和所有从属工作树)同时共享和链接。

- **您的理解体现为**：

  - **分离**：工作目录(如my-project-hotfix)和.git仓库目录在物理上是分开的，不再是强制嵌套关系。

  - **链接**：每个从属工作树(如my-project-hotfix/)内部只有一个简化的.git文件，其内容类似于gitdir:
    /path/to/my-project/.git/worktrees/my-project-hotfix，这是一个指向中心.git的指针。

  - **多对一**：实现了多个工作目录(处理不同分支)对一个中心仓库的映射。

**总结**

您准确地把握了从"**嵌入独占**"到"**链接共享**"的范式转变。git
worktree解除了"一个工作目录必须独占一个.git目录"的绑定，允许一个.git仓库**同时支撑多个并行的、位置灵活的工作上下文**。这正是它实现高效多任务并行而无需重复克隆全部历史数据的架构基础。

### 命令

#### worktree add

git worktree add \<path\>

git worktree add \<path\> \[branch\]

git worktree add \<path\> \[commit\]

git worktree add \[-b new-branch\] \<path\> \[branch\]

git worktree add \[-b new-branch\] \<path\> \[commit\]

以\[branch\]为基础，在\<path\>创建工作区，同时创建分支名\<new-branch\>。

如果省略分支名\[branch\]，git worktree add \[-b \<new-branch\>\]
../hotfix以当前所在分支为基础创建../hotfix工作区，同时创建一个名为new-branch的分支。

如果省略分支名\[branch\]和\[-b \<new-branch\>\]，git worktree add
../hotfix以当前所在分支为基础创建../hotfix工作区，同时创建一个与工作区同名的分支。

选项：

-b \<new-branch\>, -B \<new-branch\>

With **add**, create a new branch named [\<new-branch\>]{.underline}
starting at [\<commit-ish\>]{.underline}, and check out
[\<new-branch\>]{.underline} into the new worktree. If
[\<commit-ish\>]{.underline} is omitted, it defaults to **HEAD**. By
default, **-b** refuses to create a new branch if it already exists.
**-B** overrides this safeguard, resetting [\<new-branch\>]{.underline}
to [\<commit-ish\>]{.underline}.

例子

git worktree add ../test

git worktree add ../test master

git worktree add ../test SHA

git worktree add -b newbranch ../test master

git worktree add -b newbranch ../test SHA

#### worktree list

github下载源码：github clone git@github.com:itldg/web-serial-debug.git。

\$ git worktree add -b origin ../web-serial-origin

\$ git worktree add \--detach ../web-serial-detach d426a4e

\$ git worktree add -b hallo ../web-serial-hallo origin/main

\$ git worktree list

/cygdrive/d/ziliao/code/web-serial-debug 934682b \[main\]

/cygdrive/d/ziliao/code/web-serial-detach d426a4e (detached HEAD)

/cygdrive/d/ziliao/code/web-serial-hallo 934682b \[hallo\]

/cygdrive/d/ziliao/code/web-serial-origin 934682b \[origin\]

输出包含三列(以空格分隔)：

1.  **工作树路径**​ - 工作目录的绝对路径

2.  **提交哈希**​ - 当前检出的提交(短哈希)

3.  **分支信息**​ -
    当前检出的分支(用方括号括起)，如果是分离头指针则显示(detached HEAD)

**详细选项**

**1. \--porcelain格式**

机器可读格式，适合脚本处理：

\$ git worktree list \--porcelain

worktree /Users/alice/projects/myapp

HEAD abc1234567890abcdef1234567890abcdef1234

branch refs/heads/main

worktree /Users/alice/projects/myapp-feature

HEAD def56789abcdef0123456789abcdef0123456789

branch refs/heads/feature/new-ui

worktree /Users/alice/projects/myapp-hotfix

HEAD ghi90123456789abcdef0123456789abcdef0123

branch refs/heads/hotfix/security

**2. -z选项**

使用空字符分隔，避免路径中的特殊字符问题：

git worktree list -z

\# 或结合 porcelain

git worktree list \--porcelain -z

**3. \--verbose或 -v**

显示更详细的信息（Git 2.20+）：

\$ git worktree list -v

/Users/alice/projects/myapp abc1234 \[main\] (clean)

/Users/alice/projects/myapp-feature def5678 \[feature/new-ui\] (dirty)

/Users/alice/projects/myapp-hotfix ghi9012 \[hotfix/security\] (locked)

状态信息包括：

- (clean)- 工作目录干净，无未提交更改

- (dirty)- 有未提交的更改

- (locked)- 工作树被锁定

- (prunable)- 可清理(目录不存在但记录还在)

#### git branch的显示

添加了 worktree 后，git
branch的显示行为**会发生变化**，特别是在显示**检出状态**时。下面是详细的解析：

**一、基本行为变化**

**1. 传统单一工作树的情况**

\$ git branch

\* main

feature/login

hotfix/urgent

develop

- 当前检出的分支前有 \*号标记

- 其他分支只显示名称

**2. 添加 worktree 后的变化**

\# 假设我们在3个工作树中分别检出了不同分支

\$ git branch

feature/login

hotfix/urgent

\* main

\+ develop

**注意**：现在可能有**多个分支**会显示特殊标记，但含义不同。

**二、特殊状态标记说明**

1.  **\*标记**：仅表示**当前所在工作树**检出的分支

2.  **+标记**：表示该分支在**其他 worktree 中被检出**

3.  **无标记**：该分支未被任何 worktree 检出

4.  **冲突保护**：同一分支不能被多个 worktree 同时检出

**示例解析**

\$ git branch

feature/api

\+ feature/auth

\* feature/ui

\+ hotfix/urgent

develop

解读：

1.  \* feature/ui- **当前所在工作树**检出的分支

2.  \+ feature/auth- 在其他worktree中检出的分支

3.  \+ hotfix/urgent- 在另一个worktree中检出的分支

4.  无标记分支 - 未被任何worktree检出

**三、实际场景演示**

**场景1：多个工作树的状态**

\# 创建3个工作树

cd /projects/main-repo

git worktree add ../ui-branch feature/ui

git worktree add ../auth-branch feature/auth

git worktree add ../hotfix-branch hotfix/urgent

\# 在不同工作树中查看 git branch

- **在主工作树中查看：**

cd /projects/main-repo

\$ git branch

feature/api

\+ feature/auth \# 在 ../auth-branch 中检出

\+ feature/ui \# 在 ../ui-branch 中检出

\* main \# 当前工作树检出

\+ hotfix/urgent \# 在 ../hotfix-branch 中检出

develop

- **在 UI 工作树中查看：**

cd /projects/ui-branch

\$ git branch

feature/api

\+ feature/auth

\* feature/ui \# 现在这是当前工作树

\+ main

\+ hotfix/urgent

develop

**四、详细状态查看命令**

**1. git branch -vv(详细查看)**

\$ git branch -vv

\* main abc1234 \[origin/main\] 最新提交信息

feature/ui def5678 \[feature/ui\] 在其他工作树中检出

feature/auth ghi9012 \[feature/auth\] 在其他工作树中检出

- 会显示每个分支跟踪的远程分支

- 但**不会明确显示**是哪个 worktree 检出了分支

**2. git branch \--all**

\$ git branch \--all

\* main

\+ feature/ui

\+ feature/auth

remotes/origin/main

remotes/origin/feature/ui

remotes/origin/feature/auth

- 包含远程跟踪分支

- worktree 检出状态标记依旧有效

**3. git branch \--list**

\# 列出所有包含特定模式的分支

\$ git branch \--list \'feature/\*\'

feature/api

\+ feature/auth

\* feature/ui

\+ feature/login

**五、获取更详细的工作树信息**

**结合 git worktree list查看完整状态**

\# 获取完整的工作树-分支映射

\$ git worktree list

/projects/main-repo abc1234 \[main\]

/projects/ui-branch def5678 \[feature/ui\]

/projects/auth-branch ghi9012 \[feature/auth\]

/projects/hotfix-branch jkl3456 \[hotfix/urgent\]

\# 再查看分支状态

\$ git branch

feature/api

\+ feature/auth

\* main

\+ feature/ui

\+ hotfix/urgent

develop

**六、特殊情况处理**

**1.分离的HEAD状态**

\# 在某个worktree中检出特定提交(非分支)

cd /projects/temp-worktree

git checkout abc1234 \# 特定提交哈希

\# 查看分支

\$ git branch

\* (HEAD detached at abc1234)

\+ feature/auth

\+ feature/ui

main

\+ hotfix/urgent

develop

**2.[同一分支不能被多个worktree检出]{.mark}**

\# 尝试在第二个 worktree 检出已被检出的分支

git worktree add ../another-ui feature/ui

\# 错误：fatal: \'feature/ui\' is already checked out at
\'/projects/ui-branch\'

### worktree : 同一个仓库多个分支并行开发

**一、什么是git worktree**

Git
2.5+原生功能，**一个仓库、多个工作区**，同时检出不同分支/提交，互不干扰。\--**工作区/工作树/worktree**

- **主工作树**：正常git clone出来的目录，含完整.git。

- **链接工作树**：git worktree
  add创建，轻量、仅存当前分支文件，通过.git文件指向主仓库。

- **核心**：**共享.git数据库**，省磁盘、免重复克隆、免频繁stash/switch。

git
worktree让一个git仓库对应到有多个工作目录，每个工作目录指向不同的分支，能够在不切换分支的情况下并行工作。

**二、常用命令(速查)**

1.查看所有工作树

git worktree list

显示路径、分支/HEAD、是否锁定。

2.创建工作树

#1.检出已有分支到新目录

git worktree add ../hotfix main

#2.新建分支并检出(-b)

git worktree add -b feature/login ../feature-login

#3.基于远程分支(推荐)

git worktree add -b feature/login ../feature-login origin/feature/login

#4.检出到某个提交(游离HEAD)

git worktree add ../test SHA \--detach

以游离态的方式创建工作区，不会创建分支，工作区不在任何分支上。

注意：不能同时在多个工作区中使用同一分支，同一分支只能在一个工作区检出(会报错：fatal:
\'hallo\' is already used by worktree at
\'/cygdrive/d/ziliao/code/web-serial-hallo\')。但不是说在链接工作区不能切换分支，在链接工作区是可以切换到其他分支的，只是不能同时将两个工作区切换到同一个分支。

3.删除工作树

#正常删除(需干净)

git worktree remove ../hotfix

注意：git worktree
remove只是删除工作区，并不会删除创建工作区时创建的分支，git worktree
remove删除工作区后，分支还在。

#强制删(含未提交修改)

git worktree remove -force ../hotfix

#清理已删除目录残留

git worktree prune

4.锁定/解锁(防误删)

git worktree lock ../feature-login

git worktree unlock ../feature-login

**三、典型场景**

- **并行开发**：主分支开发+紧急热修同时进行。

- **多版本验证**：同时跑不同分支/标签的编译/测试。

- **代码评审**：快速切到其他分支，不影响当前工作。

- **大仓库**：避免多次克隆，节省几十GB空间。

四、注意事项

链接工作树必须在主仓库外(不能在主目录内)。

所有worktree共享仓库，pull/push全局生效。

四、注意事项

- 链接工作树**必须在主仓库外(不能在主目录内)**。

- 所有worktree**共享仓库**，全局pull/push生效。

- 不要手动删除链接目录，用git worktree remove。

**git worktree主分支开发+线上热修完整实战流程**

你只要按顺序复制命令就能跑，全程不用动当前开发分支。

**一、先搞懂结构**

- **main**：线上稳定分支

- **dev**：你平时开发分支

- **热修时**：用worktree单独**开一个临时目录**切到main修bug，不影响当前开发。

**二、完整实战流程**

1.查看当前有哪些worktree

git worktree list

2.从main新建一个热修worktree(关键)

git worktree add -b hotfix ../hotfix origin/main

hotfix：热修分支名

../hotfix：同级目录新开文件夹，不污染当前开发

3.进入热修目录

cd ../hotfix

4.修复代码、提交

git add xxx

git commit -m \"fix: resolve some bug\"

5.推送到远程

git push origin hotfix

6.热修合并回main后，删除临时worktree。

回到原项目目录：

cd -

删除临时worktree目录：

git worktree remove ../hotfix

如果删不掉，则强制删除：

git worktree remove -force ../hotfix

三、你正常开发不影响(全程不用切分支)

你原来在dev开发，全程不用动，热修是另一个文件夹(临时文件夹)。

四、常用worktree命令速查

#查看

git worktree list

#新增

git worktreeadd -b branch path origin/branch

#删除

git worktree remove path

#清理无效(比如手动删了文件夹)

git worktree prune

### worktree : 多分枝管理

文章：

Git Worktree 详解：高效管理多分支.mhtml

为什么需要 git worktree ？.docx

### 对比

git worktree介绍

\--腾讯元宝AI回答

git worktree是 Git 的一个实用命令，它允许你在同一个 Git
仓库中，**同时创建多个关联的工作目录**。每个工作目录(worktree)都指向一个不同的分支，这让你可以在不切换分支的情况下，在不同的目录中并行处理多个分支的工作。

**它解决的核心痛点**

在传统的 Git
工作流中，一个本地仓库只能有一个"工作目录"。如果你想**同时**处理两个分支(比如，在主分支main上修复紧急bug，同时又在特性分支feature上开发新功能)，就必须频繁地使用git
stash或git checkout来切换状态，这很不方便且容易打断思路。

git worktree让你可以：

•**同时打开多个分支的代码**：每个分支在一个独立的文件夹里，你可以用不同的编辑器窗口同时查看和编辑。

•**长时间运行不同任务**：比如在一个工作树运行
main分支的测试，在另一个工作树编译 feature分支的代码。

•**快速预览其他分支**：无需打扰当前工作区，新建一个工作树来查看另一个分支的内容。

**基本用法**

**1.添加一个新的工作树**

*\# 基本格式：git worktree add \<新目录路径\> \<分支名\>*

git worktree add ../my-project-feature feature/new-ui

这会在**当前仓库的父目录**中创建一个名为
my-project-feature的新文件夹，并将
feature/new-ui分支的代码检出到那里。这个新目录就是一个完整的工作区。

**2.列出所有工作树**

git worktree list

这会显示所有工作树的路径、关联的提交哈希和分支名。

**3.切换到不同工作树**

不需要特殊的 Git
命令，**直接进入对应的目录操作即可**。每个目录都是独立的。

**4.移除一个工作树**

*\# 首先，删除工作树目录(或者使用操作系统的删除方式)*

rm -rf ../my-project-feature

*\# 然后，清理 Git 的内部记录*

git worktree prune

更安全的方式是使用：

git worktree remove ../my-project-feature

**主要注意事项**

•**分支互斥**：同一个分支不能在多个工作树中同时被检出(处于"已检出"状态)。git
worktree add会自动创建一个新的分支或关联现有分支。

•**主工作树**：你最初克隆或初始化仓库时所在的目录称为"主工作树"，它和其他添加的工作树是平等的。

•**删除清理**：直接删除物理文件夹后，需要用 git worktree prune来清理 Git
的引用，否则会留下"僵尸"记录。

**与 git clone的区别**

  ----------------------------------------------------------------------------------------------------
  **特性**       **git worktree**                           **git clone**
  -------------- ------------------------------------------ ------------------------------------------
  **仓库关系**​   多个工作树**共享同一个 .git仓库**。        创建**一个全新的、独立的**仓库。

  **存储占用**​   非常节省空间，对象库是共享的。             占用完整空间，每个克隆都有独立的对象库。

  **同步速度**​   极快，因为所有对象本地已有。               可能需要重新下载网络数据。

  **独立性**​     工作树之间会有些许相互影响(如分支互斥)。   完全独立，可任意操作。
  ----------------------------------------------------------------------------------------------------

**简单来说**：git
worktree适合在**同一台机器上、同一项目**的并行多任务开发；而 git
clone更适合完整的代码复制、隔离实验或备份。

如果你需要在一个项目上"多线作战"，git
worktree是一个能极大提升效率的工具。

从多个维度对比 git worktree与传统多克隆/多目录方案的优劣势：

**比较维度对比表**

  -----------------------------------------------------------------------------------------------------------------------
  **比较维度**   **git worktree (方式A)​**                **传统多克隆/多目录 (方式B)​**           **评价**
  -------------- --------------------------------------- --------------------------------------- ------------------------
  **1.           ✅ **极高**\                            ❌ **较低**\                            **git worktree胜出**\
  存储效率**​     • 所有工作树**共享同一个.git对象库**\   • 每个克隆都有**完整独立的.git文件夹**\ 尤其大型仓库优势明显
                 • 仅多出工作目录文件本身                • 重复存储所有Git对象和历史             

  **2.           ✅ **极快**\                            ❌ **较慢**\                            **git worktree胜出**\
  创建速度**​     • 仅检出文件，无需下载/复制历史         • 需克隆/复制整个仓库历史               几乎瞬间完成

  **3. 同步性**​  ✅ **实时同步**\                        ❌ **异步**\                            **git worktree胜出**\
                 • 分支操作、提交、标签**立即全局可见**\ • 需手动fetch/pull同步更改\             统一管理更方便
                 • 配置、钩子、子模块**统一管理**​        • 配置、钩子需单独维护                  

  **4. 隔离性**​  ⚠️ **有限隔离**\                        ✅ **完全隔离**\                        **传统方式胜出**\
                 • .git共享，配置全局\                   • 每个目录是**独立仓库**\               适合需要完全隔离的场景
                 • 分支**互斥**(同一分支不能多开)\       • 可同时打开同一分支\                   
                 • 操作可能互相影响                      • 可分别设置配置/钩子                   

  **5.           ❌ **存在限制**\                        ✅ **无限制**\                          **传统方式胜出**\
  操作限制**​     • 工作树需在同一文件系统\               • 可放置在不同位置/文件系统\            灵活度更高
                 • 不能同时检出同一分支\                 • 完全独立操作                          
                 • 某些高级操作受限                                                              

  **6.           ⚠️ **需额外步骤**\                      ✅ **直接删除**\                        **传统方式胜出**\
  删除清理**​     • 需git worktree remove或prune\         • 直接rm -rf目录即可\                   清理更简单
                 • 否则留下僵尸引用                      • 无残留                                

  **7.           ⚠️ **兼容性参差**\                      ✅ **完美兼容**\                        **传统方式胜出**\
  工具兼容**​     • 较新IDE/工具支持良好\                 • 所有工具都视作标准仓库                兼容性100%
                 • 旧工具可能异常                                                                

  **8.           • 同时处理**多个特性分支**\             • 需要**完全实验隔离**\                 **各有适用场景**​
  典型场景**​     • 快速预览/测试其他分支\                • 不同机器/位置工作\                    
                 • 长期并行开发任务                      • 工具链要求高兼容性                    
  -----------------------------------------------------------------------------------------------------------------------

**决策建议**

**使用 git worktree​ 当：**

1.  **同一项目多任务并行**(如：主分支修复 + 特性开发)

2.  **存储空间有限**​ 或仓库**体积巨大**

3.  需要**快速切换/预览**不同分支

4.  在**单机单文件系统**上工作

5.  希望**配置/钩子统一管理**

**使用 传统多克隆​ 当：**

1.  需要**完全隔离的实验环境**

2.  工作在不同**物理位置/文件系统**

3.  使用的**工具链不支持**​worktree

4.  需要**同时打开同一分支**的不同版本

5.  进行**高风险操作**(如历史重写)

**混合策略**

实际开发中可结合使用：

- 用 git worktree处理日常**多分支开发**

- 用独立克隆进行**危险实验**(如filter-branch)

- 用独立克隆作为**备份/快照**

**总结**

git
worktree是**效率优化工具**，适合**常态化的多任务并发**；传统多克隆是**安全隔离方案**，适合**实验性/高风险**场景。根据你的具体需求(效率优先
vs 安全隔离优先)选择即可。

### git worktree只能基于commit提交创建工作副本吗？

问题：git
worktree只能基于commit提交创建工作副本吗？能不能基于分支创建工作副本？

假设本地有分支main、orgin/main、dev、origin/dev，可以使用 git worktree
add ../test
SHA基于提交commit创建工作副本../test，能基于分支origin/dev创建工作副本吗？例如git
worktree add ../test origin/dev

\--综合阿里通义千问、腾讯元宝总结如下

**git worktree
完全可以直接基于分支创建工作副本，且支持直接使用远程分支名创建。** 

针对你提到的本地有 main、dev、origin/main、origin/dev 的场景，具体操作与注意事项如下：

**基于本地分支创建**

如果本地已经存在 dev 分支，直接使用以下命令即可：

git worktree add ../test dev

这会[在 ../test 目录创建一个工作副本，并自动检出 dev 分支]{.mark}。

**基于远程分支创建**

直接使用 git worktree add ../test
origin/dev **通常不能直接生效**。因为 origin/dev 是远程跟踪分支（remote-tracking
branch），[Git要求工作副本必须检出一个本地分支]{.mark}。
推荐使用以下标准写法：

git worktree add \--track -b dev ../test origin/dev

这条命令的作用是：

- -b dev：在本地新建一个名为 dev 的分支。

- \--track：让本地的 dev 分支自动跟踪远程的 origin/dev。

- origin/dev：指定新分支的起点为远程分支。

> \--所以，从原理上来说，应该"[先创建本地分支，然后创建工作副本]{.mark}"，因此书写的顺序很重要：git
> worktree add -b dev ../test origin/dev

⚠️**前置操作**：执行前建议先运行 git fetch
origin，确保本地的 origin/dev 信息是最新的，因为 git worktree
add 默认不会自动拉取远程分支信息。

**核心限制与补充**

- 分支互斥：同一个分支不能同时被多个 worktree
  检出。如果 dev 分支已经在其他 worktree 中检出，命令会报错。

- 基于 Commit
  创建：如果你只想查看某个提交而不绑定分支，可以使用 \--detach 参数创建分离
  HEAD 状态的工作副本：

git worktree add \--detach ../test \<commit-SHA\>

- 查看与清理：创建后可用 git worktree
  list 查看所有工作副本；不再需要时，使用 git worktree remove
  ../test 安全删除。

git worktree add 不只是能基于 commit SHA，也能基于分支；但"基于远程分支
origin/dev"要分两种写法，结果不一样。

**一、基于本地分支：直接写分支名**

如果本地已经有 dev，且它当前没有在别的 worktree 里检出：

git worktree add ../test dev

会在 ../test 创建工作副本，并检出本地 dev。

注意规则：同一个本地分支不能同时被两个 worktree 检出。比如主仓库已经在
dev 上，再执行上面这条会报类似：

fatal: \'dev\' is already checked out at \'\...\'

这时要么先回主仓库切到别的分支，要么换一个新分支基于 dev 开。

**二、基于远程分支 origin/dev：推荐用 -b 建本地分支**

origin/dev 是远程跟踪引用，不是本地分支。若你想"基于 origin/dev
开一个可提交、可 pull/push 的工作副本"，正确写法：

\# [新建本地分支 dev-test，基于 origin/dev，并设跟踪]{.mark}

git worktree add -b dev-test ../test origin/dev

等价于先建本地分支再跟踪：

git fetch origin

git worktree add -b dev-test \--track ../test origin/dev

进去后 git branch -vv 会看到 dev-test 跟踪 origin/dev。

如果你希望工作副本直接用本地 dev 名字、且本地还没有 dev，可以先 fetch
再简写：

git fetch origin

git worktree add ../test dev

当本地没有 dev、但唯一远程有 origin/dev，且没加 -b/-B/\--detach，Git
会自动按下面处理：

git worktree add \--track -b dev ../test origin/dev

也就是自动建本地 dev 并跟踪 origin/dev。

**三、直接写 git worktree add ../test origin/dev 会怎样**

不建议这样写。把 origin/dev 作为位置参数传给 add
时，它被视为"起点/提交对象"而不是"要创建的本地分支名"，结果通常是在
../test 里检出到**分离 HEAD（detached HEAD）**，指向 origin/dev
那个提交；不会自动建一个叫 origin/dev 的本地分支，后续 git pull
也会提示不在分支上。

如果只想要临时看代码/跑测试、不打算提交到某分支，可以用分离头方式显式写：

git worktree add \--detach ../test origin/dev

**四、结合你的分支列表给几种常用法**

本地有 main、origin/main、dev、origin/dev：

- 主仓库在 main，想再开一个基于最新 origin/main 的新功能副本：

git fetch origin

git worktree add -b feature/x ../test origin/main

- 主仓库在 main，想基于本地 dev 开新修复分支：

git worktree add -b dev-hotfix ../test dev

- 本地还没 dev，想直接按远程 dev 开工作副本：

git fetch origin

git worktree add ../test dev \# [自动建本地 dev 跟踪 origin/dev]{.mark}

- 本地已有 dev 且主仓库没占用 dev：

git worktree add ../test dev

- 只临时验证 origin/dev 某个提交、不建分支：

git worktree add \--detach ../test origin/dev

### 更多git worktree介绍

见文件夹：git新功能，新命令\\git worktree\\

# 15)其他

git修改时间显示

git config log.date iso-local //2020-04-23 19:08:26 +0800

git config log.date iso-strict-local //2020-04-23T19:04:08+08:00

git config \--global log.date iso-strict-local //全局设置

常用的log格式化

# 第三部分 仓库和分支，专题，问题和解决

# 16)git仓库与分支

基本概念，见：4)基本概念 -\> 六.git仓库和分支

6)git图形工具 -\> gitg用法

## git仓库

**本地仓库、远程仓库**

**git init，创建一个本地git仓库**

**git init \--bare，创建一个远程git仓库**

**git clone http://xxx.xxx./sample.git，克隆一个远程git仓库到本地**

**git init创建本地仓库、git
clone克隆一个远程到本地**，相应的目录下**有一个.git目录，就是git仓库目录**。\
**git init \--bare创建远程仓库，没有.git目录，执行git init
\--bare命令的目录下有类似.git目录下的文件**。

本地仓库包含的文件：COMMIT_EDITMSG description gitk.cache hooks info
objects packed-refs config FETCH_HEAD HEAD index logs ORIG_HEAD refs

远程git仓库包含的文件：config description HEAD hooks info objects refs

[**git仓库保存了每一次修改的历史记录**。]{.mark}

**git仓库、git工作区 (git库目录、git工作目录)**

**一个使用git管理的项目由两部分组成：git库和git工作区**。假设项目为myproject，那么myproject/.git是**git库目录**(git仓库)，myproject/目录下除.git之外的部分是**git工作目录**(git工作区)。git工作目录的内容为某一个git版本。

**一个使用repo管理的项目由两部分组成：repo库和repo工作区**。假设项目为myproject，那么myproject/.repo是repo目录(或repo仓库)；myproject/中除.repo之外的部分为repo工作目录(repo工作区)。repo工作目录的内容为某一个repo版本。

参考：git之repo总结.doc -\> repo介绍

**[只要有git仓库，就能恢复git工作区。]{.mark}**

[**因为.git仓库保存了git工作区的每一次修改记录，可以使用git checkout
branch来恢复git工作目录**。]{.mark}

在工程代码量比较大的情况下，**[只需要保存.git仓库就可以了，不需要保存工作区，节省空间]{.mark}**。例如某个项目18G，其中git库目录12G，git工作目录6G，如果只保存git库的12G，那么能节省6G空间。由于git库保存的是每一次修改的历史记录，git库占用的空间大小比git工作目录大很多。

使用git checkout branch恢复git工作目录时，branch名字怎么确定？

假设工程目录为**myproject/**，在myproject目录下有一个.git目录，**在myproject/目录执行git
branch能看到本地分支名**。

**[只要有git仓库就能使用git命令，和是否存在git工作目录没有关系。]{.mark}**

**如果要新建一个工程，通常的做法是git clone通过网络下载到本地。**

以上述"项目工程18G，其中git库目录12G，git工作目录6G"为例，**每次新建工程都需要git
clone下载18G代码，网速慢的情况下，那是漫长而痛苦的**。而且，其中的git工作目录6G完全没有必要通过网络下载，通过git库checkout恢复就可以了，只有git仓库的12G是需要通过网络下载的。更进一步，**如果本地已经有这个git库了，那么这个12G的git仓库也不需要通过网络下载，[直接将git库拷贝到新建工程目录下，使用git
checkout branch就能恢复git工作目录，再使用git
pull更新到最新代码]{.mark}。这样只需要从网络下载比当前本地git库更新的代码，极大的加快了创建工程的速度**。

🡺**拷贝代码只需要拷贝git库就可以了，不需要拷贝git工作区，提高效率**。

将.git库目录复制到其他地方，只有本地分支、没有代码，可以使用git restore
**.**来恢复代码。

git
clone有时候只下载git库、不下载工作区，有时候git库、工作区都下载，应该是有个地方设置的？\--todo

对于18G只用一个git库进行管理的项目，如果想取消代码修改，使用git
reset太慢，git
clone更慢。既然我们修改的是git工作区，git库并不能直接修改，那么可以新建一个目录，**只需要将git库目录拷贝过来**，使用git
checkout
branch就能恢复一份没有修改过的代码。虽然18G的代码只使用一个git库不值得推荐，但是既然碰到了这样的项目，这种还原代码的方法是速度最快最高效的。

## 仓库与分支，本地仓库和远程仓库

见前面的章节：4)基本概念 -\> 六.git仓库和分支 ， 5)git命令操作图示 -\>
仓库与分支 、 远程仓库与操作， 6)git图形工具 -\> gitg用法

[一定要按照:
"15)git服务器搭建"一章的描述进行操作验证，才能更好的理解git仓库。]{.mark}

**git仓库**

**①仓库**

**本地仓库**，**位于本地电脑上**，可以进行代码修改、提交、push。**本地仓库是远程仓库的拷贝、副本**。

**远程仓库**，**位于远程服务器上**。

注:远程仓库也可以在本地主机上。你完全可以在一个"远程"仓库上工作，而实际上它在你本地的主机上。词语"远程"未必表示仓库在网络或互联网上的其它位置，而只是表示它在别处。在这样的远程仓库上工作，仍然需要和其它远程仓库上一样的标准推送、拉取和抓取操作。见:15)git服务器搭建
-\> 测试4。

**②分支**

**一个git仓库，包含多个分支**，默认包含master或main分支。

**本地仓库的分支**分两类：**本地分支、远程分支。**

本地仓库的本地分支，简称为本地分支；本地仓库的远程分支，简称为远程分支。

使用git branch
-a命令查看，名为master、dev的是本地分支，名为origin/master、origin/dev的是远程分支。

**远程分支**

**远程分支是在本地仓库中**，并不是在远程仓库中，这个名字容易迷惑。

**远程分支是远程仓库同名分支映射到本地仓库后产生，存在于本地仓库中**。**本地分支，远程分支，都存在于本地库**。

**远程分支、远程仓库的分支**

**远程分支、远程仓库的分支，是两回事、不是同一个东西。**

下图中，**本地仓库也有master、develop等分支，也有origin/master、orgin/develop等分支。**

**origin/master、origin/develop称为远程分支。名字叫远程分支，但实际上是在本地仓库中。**

**远程仓库的分支master位于远程仓库，但是远程分支origin/master却位于本地仓库。**

严格地说应该分别称为"**远程仓库的分支**"和"**本地仓库的远程分支**"。

**使用gitg可以看到本地仓库及其全部分支、远程仓库及其全部分支**。见：6)git图形工具
-\> gitg用法

![](media/image226.png){width="6.6618055555555555in"
height="3.4604166666666667in"}

上图中，

本地仓库有四个分支：master、develop、to_gitee、test；

两个远程仓库：origin、gitee，其中origin仓库有三个分支master、develop、to_gitee，gitee仓库有两个分支master、to_gitee。

git branch看到的分支是本地分支，git branch
-a可以看到本地分支和远程分支。那么，什么是远程分支？

**远程分支其实是位于本地仓库，并不是位于远程仓库**，**远程分支**和**远程仓库的分支**其实是两个不同的东西，但有关联。

**git
clone复制远程仓库到本地，同时也复制远程仓库的全部分支到本地**。远程仓库的分支复制到本地后，称为**远程分支**。

**远程分支**以\"**库名/分支名**\"的方式表示，例如origin仓库有master、develop、to_gitee三个分支，复制到本地后对应到origin/master、origin/develop、origin/to_gitee三个远程分支。

**git
clone将远程仓库的分支一一复制到本地仓库的远程分支，两者一一对应，远程分支是远程仓库的分支在本地仓库的一个映射，一一映射**。

小结：远程分支与远程仓库的分支之间是**一一对应、一一映射**的关系。

上图中，master分支和gitee/master分支、origin/master分支在同一个提交点上，develop分支和origin/develop分支在同一个提交点上，to_gitee分支和origin/to_gitee分支、gitee/to_gitee分支在同一个提交点上，比master分支多一个提交。

上图中，本地分支和远程分支都在同一个提交点上，问题：本地分支和远程分支必须在同一个提交点吗？什么时候不在同一个提交点？

git reset \--hard SHA命令使本地分支跳到指定提交点，或者，git
commit产生新的提交、但还没有push到远程仓库，这两种情况都不会改变远程分支，此时本地分支和远程分支不在同一个提交点；本地分支可以使用git
reset \--hard SHA在分支上任意移动，或者git
commit产生新的提交向前移动，都是改变本地分支，但是不能改变远程分支，远程分支只能通过fetch/pull/push命令更新，不能通过其他命令修改\--只有与远程仓库交互才能修改远程分支。

为了便于理解，可以在分支名的前面加上仓库名，这样可以将分支分为三类：**本地仓库的本地分支，本地仓库的远程分支，远程仓库的分支。**

本地仓库的远程分支一般就叫远程分支。本地分支和远程分支都是在本地，只有远程仓库的分支是在远程。

git remote查看远程仓库，git remote -vv查看远程仓库的url，git remote show
\[仓库名\]查看远程仓库的详细情况，

\$ git remote

gitee

origin

\$ git remote -vv

gitee git@gitee.com:gaheadus/daily_use.git (fetch)

gitee git@gitee.com:gaheadus/daily_use.git (push)

origin git@github.com:gaheadus/daily_use.git (fetch)

origin git@github.com:gaheadus/daily_use.git (push)

\$ git remote show origin

\* 远程 origin

获取地址：git@github.com:gaheadus/daily_use.git

推送地址：git@github.com:gaheadus/daily_use.git

HEAD 分支：master

远程分支：

develop 已跟踪

master 已跟踪

to_gitee 已跟踪

为 \'git pull\' 配置的本地分支：

master 与远程 master 合并

为 \'git push\' 配置的本地引用：

develop 推送至 develop (最新)

master 推送至 master (最新)

\$ git remote show gitee

\* 远程 gitee

获取地址：git@gitee.com:gaheadus/daily_use.git

推送地址：git@gitee.com:gaheadus/daily_use.git

HEAD 分支：master

远程分支：

gitee_self 已跟踪

master 已跟踪

to_gitee 已跟踪

为 \'git pull\' 配置的本地分支：

develop 与远程 master 合并

gitee_self 与远程 master 合并

为 \'git push\' 配置的本地引用：

gitee_self 推送至 gitee_self (最新)

master 推送至 master (最新)

使用git branch -vv本地分支的情况，git branch -avv查看所有分支的情况。

\$ git branch

develop

gitee_self

master

\* test

\$ git branch -vv

develop d657916 \[gitee/master: 落后 14\] 新增单词，修改vi使用

gitee_self b5595bd \[gitee/master: 领先 1，落后 14\]
git使用，gitee图片无法显示，修改成gitee图片网址

master 0fd0b26 \[origin/master\] 更新git使用

\* test 902af30 更新测试

\$ git branch -avv

develop d657916 \[gitee/master: 落后 14\] 新增单词，修改vi使用

gitee_self b5595bd \[gitee/master: 领先 1，落后 14\]
git使用，gitee图片无法显示，修改成gitee图片网址

master 0fd0b26 \[origin/master\] 更新git使用

\* test 902af30 更新测试

remotes/gitee/gitee_self b5595bd
git使用，gitee图片无法显示，修改成gitee图片网址

remotes/gitee/master 0fd0b26 更新git使用

remotes/gitee/to_gitee b5595bd
git使用，gitee图片无法显示，修改成gitee图片网址

remotes/origin/HEAD -\> origin/master

remotes/origin/develop d657916 新增单词，修改vi使用

remotes/origin/master 0fd0b26 更新git使用

remotes/origin/to_gitee b5595bd
git使用，gitee图片无法显示，修改成gitee图片网址

**git
fetch是从远程仓库的master分支下载代码，保存到本地仓库的远程分支remote/master。**

git fetch+git merge remote/master=git pull，先git
fetch修改到本地仓库的远程分支，然后使用git rebase remote/master或git
merge remote/master将修改合并到本地分支。

## clone/pull/push/fetch与本地仓库、远程仓库

**远程仓库只有仓库区，没有工作区，git
clone到本地后会产生仓库区、工作区、远程分支。**

之前的所有git命令都是操作\"**本地仓库的本地分支\"**进行的；

fetch/pull/push进行本地仓库和远程仓库之间的交互，fetch/pull用于更新本地仓库，只有git
push能操作\"**远程仓库的分支**\"。

\"**本地仓库的远程分支**\"不能人为的修改，只会**在fetch/pull/push操作过程中跟随**\"**远程库的分支**\"**的变化而变化**。

实际上git pull的过程分两步，第一步使用git
fetch命令将\"**远程仓库的dev分支\"**的代码拉取到\"**本地仓库的远程分支origin/dev**\"，第二步使用git
merge命令将本地仓库的远程分支origin/dev合并到\"**本地分支dev**\"中。**pull
= fetch + merge**。

可以使用git pull
\--rebase指定pull时使用rebase方式进行合并，或者配置全局git config
\--global pull.rebase true，这样git
pull时使用rebase方式进行合并，而不是merge方式进行合并。

**从概念上区分远程分支、本地分支**，才能理解git fetch、git pull，git
fetch只将修改**拉取**到远程分支，不涉及与本地分支的合并，因此不会改变本地分支，git
pull先将修改**拉取**到远程分支，再**合并**到本地分支，会改变本地分支。

git pull = git fetch + git merge

git pull \--rebase = git fetch + git rebase

git默认使用merge的方式合并分支代码，git pull
\--rebase指定使用rebase方式合并分支代码。

配置git config \--global pull.rebase
true指定pull使用rebase方式合并分支代码。

**一份代码，git
clone下载到本地的时候是没有本地分支的，只有本地的远程分支**。此时需要自己创建本地分支，使用git
checkout -b \<new-branch-name\>建立本地分支。使用git checkout
origin/branch-name切换到远程分支会提示:You are in \'detached HEAD\'
state。

git
clone有时候会创建本地分支master或main，有时候不会创建本地分支，与什么配置有关？

Android使用repo start branch-name \--all建立本地分支。

刚克隆下来的代码是没有分支的，repo start实际是对git checkout
-b命令的封装。
为指定的项目或所有的项目(若使用-all)，以清单文件中为设定的分支，创建特定的分支。

  repo start branch-name \--all与git checkout -b 还是有很大区别的：

  ⚫git checkout -b 是在当前所在的分支的基础上创建特性分支。

  ⚫而repo start 是在清单文件设定的分支的基础上创建特性分支。

## 查看分支和远程仓库，git branch、git remote

git branch //查看有本地分支(是本地仓库的本地分支)

git branch -r //查看所有远程分支(本地仓库的远程分支) //ubuntu
git还会标记出来其所跟踪的远程仓库中的分支

git branch -a //查看所有本地分支和远程分支。是git branch和git branch
-r的总和

git branch -v //显示哈希值和主题，若参数出现两次则显示上游分支(git
branch -vv显示本地分支与远程分支之间的跟踪关系)

git branch -av 、git branch -avv

git branch用于查看分支，git remote查看仓库

git remote //显示所有远程仓库

git remote -v //显示远程分支的克隆地址，git remote -vv显示更详细的信息

git remote show \[remote-name\] //查看某个远程仓库的详细信息

**查看本地分支和远程分支的跟踪关系**

**\$ git branch -vv**

develop 08775f9 \[origin/develop\] develop //
develop分支跟踪远程origin/develop分支

feature_1 b41865d \[origin/feature_1\] feature_1 //...

\* master 1399706 \[my_github/master\] init commit //
master跟踪远程my_github/master分支，当前在master分支上

git branch -v, -vv, \--verbose的解释：

When in list mode, show sha1 and commit subject line for each head,
along with relationship to upstream branch (if any). If given twice,
print the path of the linked worktree (if any) and the name of the
upstream branch, as well (see also git remote show \<remote\>). Note
that the current worktree's HEAD will not have its path printed (it will
always be your current directory).

## 仓库与分支的多种组合

**①单个本地分支，多个远程分支，单个远程仓库**：

**\$ git branch**

\* master

**\$ git branch -r**

origin/master

origin/new_branch

**\$ git branch -a**

\* master

remotes/origin/master // remotes/origin/master和git branch
-r显示的origin/master都表示远程分支，应该是**同一个东西**

remotes/origin/new_branch //**的两个不同名字** 🡪
远程分支可以写成remotes/origin/master，也可以写成origin/master。

**\$ git remote**

origin

**\$ git remote -v**

origin https://github.com/gaheadus/temp.git(fetch)

origin https://github.com/gaheadus/temp.git(push)

**\$ git remote show origin**

\* remote origin

Fetch URL: https://github.com/gaheadus/temp.git

Push URL: https://github.com/gaheadus/temp.git

HEAD branch: master

Remote branches:

master tracked

new_branch tracked

Local branch configured for \'git pull\':

master merges with remote master

Local ref configured for \'git push\':

master pushes to master (fast-forwardable)

当前git本地仓库，有一个远程仓库origin，有一个本地分支master，两个远程分支origin/master、origin/new_branch。

本地分支master是建立在远程分支origin/master的基础上的。

**②多个本地分支，多个远程分支，单个远程仓库**：

**③多个本地分支，多个远程分支，多个远程仓库**：

**\$ git remote**

origin

**\$ git remote -v**

origin https://github.com/gaheadus/temp.git(fetch)

origin https://github.com/gaheadus/temp.git(push)

private git@github.com:gaheadus/daily_use.git(fetch)

private git@github.com:gaheadus/daily_use.git(push)

一个git本地仓库，两个远程仓库origin和private。

## 远程仓库的分支

要查看当前配置有哪些远程仓库，可以用 git
remote 命令，它会列出每个远程库的简短名字。

\$git remote，显示全部的远程仓库

\$git remote -v 显示仓库的详细信息，fetch/pull对应的默认URL。git remote
-vv显示更详细。

\$git remote show \[remote-name\] 查看指定远程仓库的详细信息

![](media/image287.png){width="4.432638888888889in"
height="5.163888888888889in"}

![](media/image288.png){width="4.201388888888889in"
height="0.9555555555555556in"}

可以看出，远程aosp库下有phs-jb-pxa988-base-dev_r1/rls_pxa920_ics_bate3/linaro_android_4.1.2等等分支，本地分支所跟踪的远程分支是：

本地分支phs-jb-pxa988-dsds-dev_r2跟踪的远程分支是phs-jb-pxa988-dsds-dev_r2，也就是aosp/phs-jb-pxa988-dsds-dev_r2

本地分支rls-pxa920-ics-beta3跟踪的远程分支是rls-pxa920-ics-beta3，=aosp/rls-pxa920-ics-beta3

本地分支testbranch跟踪的远程分支是marvell-android-4.3-dsds-dev

上图所示，当前platform/packages/apps/Bluetooth工程下，本地分支名是phs-jb-pxa988-dsds-dev_r2,所跟踪的远程分支名是phs-jb-pxa988-dsds-dev_r2，从Local
ref configured for 'git pull'可以看出来，

## 本地分支与远程分支之间的跟踪关系，跟踪远程分支/关联远程分支

### 跟踪分支的基本概念

基本概念：5)git命令操作图示 -\> 1.远程仓库与操作 -\> 远程跟踪分支

本地分支分两种：跟踪分支、非跟踪分支。

**在远程分支分支的基础上建立的本地分支**是**跟踪分支**，如git checkout
-b newbr origin/master。

**在其他本地分支的基础上建立的本地分支**是**非跟踪分支**，如git checkout
-b newbr2 newbra。

非跟踪分支不能直接pull/push，使用git branch \--track localbr
remotebr将本地分支设置为跟踪某个远程分支，然后才能直接pull/push。

注意：非跟踪分支不能**直接**pull/push，并不是不能fetch/pull/push，是可以通过指定远程分支名和本地分支名来pull/push的，如git
push orgin localbr:remotebr。

参考后续章节：15)git仓库与分支 -\>
本地分支与远程分支之间的跟踪关系，跟踪远程分支/关联远程分支

参考[https://git-scm.com/book/zh/v1/git-%E5%9F%BA%E7%A1%80-%E8%BF%9C%E7%A8%8B%E4%BB%93%E5%BA%93%E7%9A%84%E4%BD%BF%E7%94%A8](https://git-scm.com/book/zh/v1/Git-%E5%9F%BA%E7%A1%80-%E8%BF%9C%E7%A8%8B%E4%BB%93%E5%BA%93%E7%9A%84%E4%BD%BF%E7%94%A8)

[git把远程分支拿到本地，**并建立关联关系**，**本地分支跟踪远程分支**。**跟踪:track**。]{.mark}

**将本地分支与远程分支关联起来，建立一种映射关系**。建立这种映射关系后，对应的远程分支叫**upstream**。

**这种关联关系，可以在创建本地分支的时候指定，也可以在本地分支创建以后再指定。可以随时取消与远程分支的这种关联关系，也可以指定关联到不同远程分支。**详细操作见：如何创建跟踪分支。

**[在git中'追踪分支'是用于联系本地分支和远程分支的]{.mark}**。如果你在'追踪分支\'(Tracking
Branches)上执行推送(push)或拉取(pull)时,它会自动推送(push)或拉取(pull)到关联的远程分支上。

如果你经常要从远程仓库里拉取(pull)分支到本地,并且不想很麻烦的使用\"git
pull origin mybranch:master\"这种格式;
那么就应当使用'追踪分支\'(Tracking Branches)。

'git
clone'命令会自动在本地建立一个\'master\'分支，它是\'origin/master\'的'追踪分支'.
而\'origin/master\'就是被克隆(clone)仓库的\'master\'分支。

译者注: origin一般是指原始仓库地址的别名。

你可以在使用\'git branch\'命令时加上\'\--track\'参数,
来手动创建一个\'追踪分支\'

\$git branch \--track experimental origin/experimental

当你运行下命令时:

\$ git pull experimental

它会自动从'origin\'抓取(fetch)内容，再把远程的\'origin/experimental\'分支合并进(merge)本地的\'experimental\'分支.

当要把修改推送(push)到origin时,
它会将你本地的\'experimental\'分支中的修改推送到origin的'experimental\'分支里,无需指定它(origin)。

查看远程有哪些分支，

\$ git branch -r //查看远程分支

\$ git branch -a //查看远程分支和本地分支

**从远程分支 checkout 出来的本地分支，称为_跟踪分支(tracking
branch)\_。**跟踪分支是一种和远程分支有直接联系的本地分支。

**(1.从本地checkout的本地分支，2.从远程checkout的本地分支，跟踪分支。)**

**在跟踪分支里输入git
push，git会自行推断应该向哪个服务器的哪个分支推送数据。反过来，在这些分支里运行git
pull 会获取所有远程索引，并把它们的数据都合并到本地分支中来。(我们用(远程仓库名)/(分支名)
这样的形式表示远程分支)**

在克隆仓库时，git通常会自动创建一个名为 master 的分支来跟踪 origin/master，这正是 git
push 和 git
pull 一开始就能正常工作的原因。当然，你可以随心所欲地设定为其它跟踪分支，比如 origin 上除了master 之外的其它分支。

可以使用如下方法**创建本地分支用来跟踪远程分支**：

**\$ git checkout -b \[本地分支名\] \--track \[远程名\]/\[分支名\]**

**\$ git branch \--track \[本地分支名\] \[远程名\]/\[分支名\]**

例子：

\$ git checkout -b track1 \--track aosp/gingerbread-mr4-release

Branch track1 set up to track remote branch gingerbread-mr4-release from
aosp.

Switched to a new branch \'track_test\'

\$ git branch

origin_android4.4.4_r2

\* track1

\$ git branch -v

origin_android4.4.4_r2 bc405e7 Import translations. DO NOT MERGE

\* track1 647056f reset back to latest, and keep history

\$ git checkout -b track1 \--track aosp/gingerbread-mr4-release，

建立本地分支track1，这个本地分支跟踪远程分支aosp/gingerbread-mr4-release。

现在，本地分支 track1会自动向 aosp/gingerbread-mr4-release推送和抓取数据了。

如果你有 1.6.2 以上版本的
git，还可以简化\--track 选项。可以只写"\--track +远程分支名"，不写本地分支名：

\$ git checkout \--track aosp/gingerbread-mr4-release

Branch gingerbread-mr4-release set up to track remote branch
gingerbread-mr4-release from aosp.

Switched to a new branch \'gingerbread-mr4-release\'

\$ git branch

\* gingerbread-mr4-release

origin_android4.4.4_r2

这样，默认会建立名字为gingerbread-mr4-release的本地分支，这个名字和所跟踪的远程分支名字是一样的。

如果要为本地分支设定不同于远程分支的名字，需要使用-b参数明确指定本地分支名：

\$ git checkout -b track2 \--track aosp/gingerbread-mr4-release

Branch track2 set up to track remote branch gingerbread-mr4-release from
aosp.

Switched to a new branch \'track2\'

还可以再简化，"只写-b+本地分支名+远程分支名"就可以：

\$ git checkout -b track4 aosp/gingerbread-mr4-release

Branch track4 set up to track remote branch gingerbread-mr4-release from
aosp.

Switched to a new branch \'track4\'

再继续简化，只写-b，不写本地分支名：

\$ git checkout -b aosp/gingerbread-mr4-release

Switched to a new branch \'aosp/gingerbread-mr4-release\'

\$ git branch

\* aosp/gingerbread-mr4-release //默认和远程分支名一样，包括aosp/前缀

origin_android4.4.4_r2

本地分支名和-b、\--track都不写：

\$ git checkout aosp/gingerbread-mr4-release

Note: checking out \'aosp/gingerbread-mr4-release\'.

You are in \'detached HEAD\' state. You can look around, make
experimental

changes and commit them, and you can discard any commits you make in
this

state without impacting any branches by performing another checkout.

If you want to create a new branch to retain commits you create, you may

do so (now or later) by using -b with the checkout command again.
Example:

git checkout -b new_branch_name

HEAD is now at 647056f\... reset back to latest, and keep history

这样的话，需要用git branch localbranch新建本地分支，用来保存刚才git
checkout下来的远程分支代码，所以，最好是指定本地分支名。

**\--track**

When creating a new branch, set up \"upstream\" configuration. See
\"\--track\" in git-branch(1) for details.

If no -b option is given, the name of the new branch will be derived
from the remote-tracking branch. If \"remotes/\" or \"refs/remotes/\" is
prefixed it is stripped away, and then the part up to the next slash
(which would be the nickname of the remote) is removed. This would tell
us to use \"hack\" as the local branch when branching off of
\"origin/hack\" (or \"remotes/origin/hack\", or even
\"refs/remotes/origin/hack\"). If the given name has no slash, or the
above guessing results in an empty name, the guessing is aborted. You
can explicitly give a name with -b in such a case.

\--track

When creating a new branch, set up configuration to mark the start-point
branch as \"upstream\" from the new branch. This configuration will tell
git to show the relationship between the two branches in git status and
**git branch -v**. Furthermore, it directs git pull without arguments to
pull from the upstream when the new branch is checked out.

This behavior is the default when the start point is a remote-tracking
branch. Set the branch.autosetupmerge configuration variable to false if
you want git checkout and git branch to always behave as if \--no-track
were given. Set it to always if you want this behavior when the
start-point is either a local or remote-tracking branch.

也可用git branch来跟踪远程分支(此时并不会切换分支)：

\$ git branch \--track track5 aosp/gingerbread-mr4-release

Branch track5 set up to track remote branch gingerbread-mr4-release from
aosp.

\$ git branch

\* origin_android4.4.4_r2

track2

track3

track4

track5

git
checkout和\--track结合使用，获取远程代码后会切换本地分支到新建分支上，而git
branch和\--track结合使用，获取远程分支代码后不会切换到新建分支上(和git
checkout/git branch本来的用法一样)。

上述都是新建分支，同时让所新建的分支跟踪远程分支，那么，如果本地分支已经存在，如何让本地分支跟踪远程分支呢？

\$ git branch

br_existed

\* origin_android4.4.4_r2

track2

\$ git branch br_existed \--track aosp/gingerbread-mr4-release

fatal: A branch named \'br_existed\' already exists.

\$ git branch br_existed \--track aosp/gingerbread-mr4-release -f
//加-f参数

Branch br_existed set up to track remote branch gingerbread-mr4-release
from aosp.

\$ git branch -v

br_existed 647056f reset back to latest, and keep history

\* origin_android4.4.4_r2 bc405e7 Import translations. DO NOT MERGE

track2 647056f reset back to latest, and keep history

track3 647056f reset back to latest, and keep history

<http://blog.csdn.net/arkblue/article/details/9790129>
，<http://progit.org/book/zh/ch3-5.html>

<http://hubingforever.blog.163.com/blog/static/17104057920124126297235/>
，  <http://gitbook.liuhui998.com/4_7.html>

<http://www.hi-ruby.com/articles/1033>

今天经过老大的指点，终于一解困惑我多年的这个问题：

使用git时候，本地新建分支，push到remote上去后，再次pull下来，会报以下提示：

You asked me to pull without telling me which branch you

want to merge with, and \'branch.production.merge\' in

your configuration file does not tell me, either. Please

specify which branch you want to use on the command line and

try again (e.g. \'git pull \<repository\> \<refspec\>\').

See git-pull(1) for details.

If you often merge with the same branch, you may want to

use something like the following in your configuration file:

\[branch \"production\"\]

remote = \<nickname\>

merge = \<remote-ref\>

\[remote \"\<nickname\>\"\]

url = \<url\>

fetch = \<refspec\>

See git-config(1) for details.

之前都是按照提示手动配置的，一直在寻找利用口令直接配置的方法，经过老大指点，问题轻松解决：

\$ git branch \--set-upstream production origin/production

结果是在**项目目录下
.git/config**中添加如下内容，也就是之前我一直手动添加的代码：

\[branch \"production\"\]

remote = origin

merge = refs/heads/production

man git branch如下：

When a local branch is started off a remote-tracking branch, git sets up
the branch so that git pull will appropriately merge from the
remote-tracking branch. This behavior may be changed via the global
branch.autosetupmerge configuration flag. That setting can be overridden
by using the \--track and \--no-track options, and changed later using
git branch \--set-upstream.

**跟踪分支，可用于pull/push；非跟踪分支，不能直接pull/push，需要加参数指定远程库和分支。**

非跟踪分支不设置跟踪属性也是可以推送到远程仓库的，在push的时候使用\--set-upstream参数就可以了，如下：

\$ git push \--set-upstream git@github.com:gaheadus/temp.git myBranch

不管是在跟踪分支上，还是在非跟踪分支上，都能做fetch操作，因为fetch更新的是本地的远程分支，并不更新本地的本地分支。

本地分支与远程分支之间的跟踪关系使用git branch -vv查看。

我的观点：

一般，在非跟踪分支上做开发，不要直接在开发分支上push代码，保持开发分支与远程分支之间的独立性，这样做有两个好处：

1.可以避免在开发过程中引入冲突而带来困扰。开发过程中将全部精力专注于开发，如果意外pull代码造成冲突，还得另外花时间解决冲突，分散精力。

2.防止意外push本地临时修改的代码到远程仓库。可能要在本地分支上做一些试验，临时修改了代码、提交，或者包含开发过程中尚未修改完善、编译错误的代码，如果不小心push到远程仓库，会带来困扰。

开发过程中，一个master分支，用于pull/push；针对不同功能，建立不同开发分支\--特性分支，不用于pull/push。

不同特性分支之间保持独立性、纯粹性。

一个功能建立一个开发分支，一方面，保持开发过程的单一，不会使得代码修改庞大复杂，另一方面，不同特性功能之间互不干扰，保持目的的单一。

### 如何创建跟踪分支

方法一、创建分支的时候指定跟踪远程分支

git checkout -b mybranch origin/master

git branch \--track mybranch origin/master

git branch -t mybranch origin/master //-t、\--track是一样的

方法二、先创建分支，再指定跟踪远程分支

git checkout -b mybranch

git branch \--set-upstream-to=origin/master
//-u和\--set-upstream-to的作用是一样的

git branch -u origin/master //指定当前所在分支跟踪远程origin/master分支

git branch -u origin/master mybranch
//指定mybranch分支跟踪远程origin/master分支

方法三、push推送的时候指定跟踪远程分支

git push -u origin/master

取消对远程分支的跟踪，使用git branch \--unset-upstream、git branch
mybranch \--unset-upstream。

详见git branch命令。

实例，**注意看命令执行结果提示**：

方法一：创建分支的时候指定跟踪远程分支

\$ git checkout -b test origin/master
//如果不指定origin/master则创建的是创建非跟踪分支

Branch test4 set up to track remote branch master from origin.

Switched to a new branch \'test\'

\$ git branch -vv

master 5251c95 \[origin/master\] update envsetup.sh

\* test 5251c95 \[origin/master\] update envsetup.sh

git branch创建分支

\$ git branch \--track test5 origin/master

Branch test5 set up to track remote branch master from origin.

\$ git branch -vv

\* master 560620a \[origin/master\] 增加tcpdump使用

test 5251c95 \[origin/master: behind 1\] update envsetup.sh

test5 560620a \[origin/master\] 增加tcpdump使用

方法二：先创建分支，再指定跟踪远程分支

\$ git checkout -b test2_no_track

Switched to a new branch \'test2_no_track\'

\$ git branch -vv

master 5251c95 \[origin/master\] update envsetup.sh

test 5251c95 \[origin/master\] update envsetup.sh

\* test2_no_track 5251c95 update envsetup.sh

\$ git branch \--set-upstream-to=origin/master

Branch test2_no_track set up to track remote branch master from origin.

\$ git branch -vv

master 5251c95 \[origin/master\] update envsetup.sh

test 5251c95 \[origin/master\] update envsetup.sh

\* test2_no_track 5251c95 \[origin/master\] update envsetup.sh

方法三：push推送的时候指定跟踪远程分支

\$ git checkout -b test3_no_track

Switched to a new branch \'test3_no_track\'

\$ git branch -vv

master 5251c95 \[origin/master\] update envsetup.sh

test 5251c95 \[origin/master\] update envsetup.sh

test2_no_track 5251c95 \[origin/master\] update envsetup.sh

\* test3_no_track 5251c95 update envsetup.sh

\$ git push //报错

fatal: The current branch test3_no_track has no upstream branch.

To push the current branch and set the remote as upstream, use

git push \--set-upstream origin test3_no_track

\$ git push \--set-upstream origin test3_no_track

Counting objects: 4, done.

Delta compression using up to 20 threads.

Compressing objects: 100% (4/4), done.

Writing objects: 100% (4/4), 1.41 KiB \| 0 bytes/s, done.

Total 4 (delta 2), reused 0 (delta 0)

remote: Resolving deltas: 100% (2/2), completed with 2 local objects.

remote:

remote: Create a pull request for \'test3_no_track\' on gitHub by
visiting:

remote: https://github.com/gaheadus/daily_use/pull/new/test3_no_track

remote:

To github.com:gaheadus/daily_use.git

\* \[new branch\] test3_no_track -\> test3_no_track
//创建一个新的远程分支

Branch test3_no_track set up to track remote branch test3_no_track from
origin.

\$ git branch -avv

master 5251c95 \[origin/master\] update envsetup.sh

test 5251c95 \[origin/master\] update envsetup.sh

test2_no_track 5251c95 \[origin/master\] update envsetup.sh

\* test3_no_track 560620a \[origin/test3_no_track\] 增加tcpdump使用
//创建了新的远程分支origin/test3_no_track，并跟踪该分支

remotes/origin/HEAD -\> origin/master

remotes/origin/master 5251c95 update envsetup.sh

remotes/origin/test3_no_track 560620a 增加tcpdump使用

产生了一个新的远程分支origin/test3_no_track，不是想要的结果，将其删除：

\$ git push origin :test3_no_track，或git push origin \--delete
:test3_no_track

如果不想创建远程分支，只想将代码push到已有远程分支origin/master，那么应该写成：git
push \--set-upstream origin test4_no_track:master。

\$ git checkout -b test4_no_track

Switched to a new branch \'test4_no_track\'

\$ git branch -avv

master 5251c95 \[origin/master\] update envsetup.sh

test 5251c95 \[origin/master\] update envsetup.sh

test2_no_track 5251c95 \[origin/master\] update envsetup.sh

test3_no_track 560620a \[origin/test3_no_track\] 增加tcpdump使用

\* test4_no_track 560620a 增加tcpdump使用

remotes/origin/HEAD -\> origin/master

remotes/origin/master 5251c95 update envsetup.sh

remotes/origin/test3_no_track 560620a 增加tcpdump使用

\$ git push

fatal: The current branch test4_no_track has no upstream branch.

To push the current branch and set the remote as upstream, use

git push \--set-upstream origin test4_no_track

\$ git push \--set-upstream origin test4_no_track:master

Total 0 (delta 0), reused 0 (delta 0)

To github.com:gaheadus/daily_use.git

5251c95..560620a test4_no_track -\> master

Branch test4_no_track set up to track remote branch master from origin.

\$ git branch -avv

master 5251c95 \[origin/master: behind 1\] update envsetup.sh

test 5251c95 \[origin/master: behind 1\] update envsetup.sh

test2_no_track 5251c95 \[origin/master: behind 1\] update envsetup.sh

test3_no_track 560620a \[origin/test3_no_track\] 增加tcpdump使用

\* test4_no_track 560620a \[origin/master\] 增加tcpdump使用
//可以看到test4_no_track跟踪远程分支origin/master

remotes/origin/HEAD -\> origin/master

remotes/origin/master 560620a 增加tcpdump使用

remotes/origin/test3_no_track 560620a 增加tcpdump使用

方法四、取消对远程分支的跟踪

\$ git branch -vv

master 5251c95 \[origin/master: behind 1\] update envsetup.sh

test 5251c95 \[origin/master: behind 1\] update envsetup.sh

test2_no_track 5251c95 \[origin/master: behind 1\] update envsetup.sh

test3_no_track 560620a \[origin/test3_no_track: gone\] 增加tcpdump使用
// gone表示origin/test3_no_track远程分支已经被删除了

\* test4_no_track 560620a \[origin/master\] 增加tcpdump使用

\$ git branch \--unset-upstream //取消当前所在分支的跟踪关系

\$ git branch -vv

master 5251c95 \[origin/master: behind 1\] update envsetup.sh

test 5251c95 \[origin/master: behind 1\] update envsetup.sh

test2_no_track 5251c95 \[origin/master: behind 1\] update envsetup.sh

test3_no_track 560620a \[origin/test3_no_track: gone\] 增加tcpdump使用

\* test4_no_track 560620a 增加tcpdump使用
//可以看到test4_no_track不再跟踪远程分支了

\$ git branch -vv

\* master 560620a \[origin/master\] 增加tcpdump使用

test 5251c95 \[origin/master: behind 1\] update envsetup.sh

test2_no_track 5251c95 \[origin/master: behind 1\] update envsetup.sh

test3_no_track 560620a \[origin/test3_no_track: gone\] 增加tcpdump使用

test4_no_track 560620a \[origin/master\] 增加tcpdump使用

test5 560620a \[origin/master\] 增加tcpdump使用

test6 560620a \[origin/master\] 增加tcpdump使用

\$ git branch test6 \--unset-upstream //取消指定分支的跟踪关系

\$ git branch -vv

\* master 560620a \[origin/master\] 增加tcpdump使用

test 5251c95 \[origin/master: behind 1\] update envsetup.sh

test2_no_track 5251c95 \[origin/master: behind 1\] update envsetup.sh

test3_no_track 560620a \[origin/test3_no_track: gone\] 增加tcpdump使用

test4_no_track 560620a \[origin/master\] 增加tcpdump使用

test5 560620a \[origin/master\] 增加tcpdump使用

test6 560620a 增加tcpdump使用

### 查看分支的跟踪情况

git branch -vv、git branch
-avv可以查看分支的跟踪情况，也可以查看对应工程目录下的.git/config文件。

\$ **ll .git/config**

lrwxrwxrwx 1 shiguik Domain Users 55 Sep 2 08:45 .git/config -\>
../../../../.repo/projects/packages/apps/Tag.git/config

\$ **cat ../../../.repo/projects/packages/apps/Tag.git/config**
//内容如下：

\[core\]

repositoryformatversion = 0

filemode = true

ignorecase = true

\[remote \"aosp\"\]

url = git://android.git.linaro.org/platform/packages/apps/Tag

projectname = platform/packages/apps/Tag

fetch = +refs/heads/\*:refs/remotes/aosp/\*

\[branch \"origin_android4.4.4_r2\"\]

remote = aosp

merge = refs/tags/android-4.4.4_r2

\[branch \"track2\"\]

remote = aosp

merge = refs/heads/gingerbread-mr4-release

\[branch \"track3\"\]

remote = aosp

merge = refs/heads/gingerbread-mr4-release

\[branch \"br_existed\"\]

remote = aosp

merge = refs/heads/gingerbread-mr4-release

\[branch \"gingerbread-mr4-release\"\]

remote = aosp

merge = refs/heads/gingerbread-mr4-release

### 跟踪的作用

跟踪分支：建立跟踪关系后，可以直接使用git
pull/push进行拉取/推送。[git根据跟踪关系找到本地分支对应的远程分支]{.mark}，然后进行push/pull。

非跟踪分支：不建立跟踪关系，也可以pull/push，但是需要加参数，指定库名、本地分支名、远程分支名，git
pull/push \[库名\] \[源分支\]:\[目的分支\]。

建立了跟踪关系后，如果想推送代码到远程库的非跟踪分支上，也需要指定库名、本地分支名、远程分支名，git
pull/push \[库名\] \[源分支\]:\[目的分支\]，拉取代码也一样。

所以，建立跟踪关系或者不建立跟踪关系都可以，没有本质的区别，只是使用上的便利性不同、使用习惯不同而已。

branch -vv查看本地分支与远程分支之间的跟踪关系。

### 分支的经验

不要把所有分支都做成跟踪分支。

不要把本地正在修改的分支做成跟踪分支。**习惯性地**git
pull更新代码，**不经意间**就把当前的环境破坏了，不利于问题复现、定位。

因此把本地正在修改的分支做成非跟踪分支，无法直接git
pull更新代码，确实需要更新代码，可以使用git
rebase到跟踪分支上去，操作麻烦一点，不至于在不经意的时候更新代码。

## 1.跟踪分支推拉，非跟踪分支推拉，跨仓库推拉

push：推送，pull：拉取，在本地仓库与远程仓库之间推/拉修改。

①跟踪分支的推拉

使用git push将当前分支的修改推送到远程仓库的跟踪分支，git
pull从远程仓库的跟踪分支拉取代码到当前仓库。

建立跟踪分支的好处是使用git push、git
pull直接推拉修改，不需要加参数，默认在当前分支与对应的远程跟踪分支之间推拉。

\$ git pull

\$ git push

②非跟踪分支的推拉

如果本地分支没有与远程分支之间建立跟踪关系，那么使用git
push/pull不加参数会报错，因为**git不知道推送到哪个分支、从哪个分支拉取**(这就是本地分支与远程分支之间建立跟踪关系的目的，就是告诉git将修改推送到哪里去、从哪里拉取修改)。

**此时如果需要推拉代码，需要明确指定仓库名、远程分支名、本地分支名**，使用push/pull的完整格式：git
push 仓库名 本地分支名:远程分支名、git pull 仓库名
远程分支名:本地分支名。

如果本地分支与远程分支之间建立了跟踪关系，那么pull/push时git可以根据跟踪关系推断出源分支、目的分支，因此在可以省略源/目分支，只需要写git
push/pull就可以。

小结：要让git知道推送到哪个分支、从哪个分支拉取，要么根据跟踪关系推断，要么pull/push/fetch时明确指定远程仓库名、远程分支名、本地分支名。

\$ git pull myrepo remote_br:local_br

\$ git push myrepo local_br:remote_br

如果是当前分支，push时源分支可以写本地分支名或HEAD，pull时可以省略本地分支名，如下：

\$ git pull myrepo remote_br

\$ git push myrepo HEAD:remote_br

③跨仓库推拉

如果一个本地仓库，对应多个远程仓库，从一个远程仓库拉取代码，推送到另外一个远程仓库的情况，那么需要使用push/pull的完整格式：git
push 仓库名 本地分支名:远程分支名、git pull 仓库名
远程分支名:本地分支名，和②是一样的。

\$ git pull myrepo remote_br:local_br

\$ git push myrepo local_br:remote_br

如果是当前分支，push时源分支可以写本地分支名或HEAD，pull时可以省略本地分支名，和②一样，如下：

\$ git pull myrepo remote_br

\$ git push myrepo HEAD:remote_br

见下一节：一个本地仓库关联多个远程仓库ssssssssssss

pull/push/fetch的完整格式，见：5)git命令操作图示 -\> 1.远程仓库与操作
-\> git pull 的参数，git push 的参数，git fetch
的参数，\<place\>参数小结

git push报错：

\$ git push

致命错误：您当前分支的上游分支和您当前分支名不匹配，为推送到远程的上游分支，

使用

git push gitee HEAD:master

为推送至远程同名分支，使用

git push gitee HEAD

为了永久地选择任一选项，参见 \'git help config\' 中的 push.default。

为了避免在与本地分支名字不匹配时自动设置上游分支，参见 \'git help
config\'

中 branch.autoSetupMerge 的 \'simple\' 选项。

## 一个本地仓库关联多个远程仓库

一个本地仓库能不能即关联github，又关联gitee呢？可以。

因为git是分布式版本控制系统，可以同步到一个远程库，也可以同步到多个远程库。

使用多个远程库是注意，git给远程库起的名字默认是origin，如果有多个远程库，不同远程库需要使用不同的名字。

一个本地仓库关联多个远程库，方法如下：

方法一

注意这里的origin和gitee为自定义远程仓库的名字，不能重复。

// 添加github

git remote add origin https://github.com/xxx(仓库地址)

// 添加gitee

git remote add gitee https://git.gitee.com/xxxx(仓库地址)

// 删除origin仓库

git remote rm origin

// 提交到github

git push origin

// 提交到gitee

git push gitee

// 从github更新

git pull origin master

// 从gitee更新

git pull gitee master

本地仓库关联到github和gitee，关系如下：

![](media/image289.emf)

不同远程库直接pull/push

**跨仓库pull/push，需要使用pull/push的完整格式，指定远程仓库和远程分支，和非跟踪分支pull/push是一样的。**

例，本地分支test，从github库master分支拉取代码，推送到gitee库master分支。

\$ git checkout -b test

\$ git pull github master:test

\$ git push gitee test:master，或git push gitee HEAD:master

git pull/fetch下载当前分支所关联的库，不会下载非当前分支所关联的库。

**git fetch \--all，git pull \--all**，下载全部远程库到本地。

方法二

添加第二个gitee仓库

假如已经添加了github为origin

git remote set-url \--add origin https://git.gitee.com/xxxx(仓库地址)

// 此时只需要一次push就能同步到多个远程仓库

git push

查看remote地址

git remote -v

总结

方法一可以选择任一仓库进行pull，而方法二缺默认只能从config中的第一个url内的仓库pull代码。

## 删除远程分支

git push\[远程库名\] :\[远程分支名\] //本地分支名留空

git push \[远程库名\] \--delete \[远程分支名\]

例：

\$ git push origin :serverfix //删除远程库上的serverfix分支

\$ git push origin \--delete :serverfix //指定\--delete选项删除远程分支

碰到的问题：**合作开发，A将远程库的分支删除了，但是B在本地库还能看到被删除的远程分支**，怎么解决？

远程分支已经删除了，但是git branch -a仍然能看到，此时需要执行git remote
prune origin清理一下，再次执行git branch -a就看不到了。

\$ git branch -a

\* master

remotes/origin/HEAD -\> origin/master

remotes/origin/master

remotes/origin/todo

remotes/origin/temp

\$ git remote show origin

\* 远程 origin

获取地址：git@github.com:gaheadus/daily_use.git

推送地址：git@github.com:gaheadus/daily_use.git

HEAD 分支：master

远程分支：

master 已跟踪

refs/remotes/origin/todo 过时(使用\'git remote prune\'来移除) \--
这个远程分支已经删除了，但是本地仓库还能看到

refs/remotes/origin/temp 过时(使用\'git remote prune\'来移除)

为 \'git pull\' 配置的本地分支：

master 与远程 master 合并

为 \'git push\' 配置的本地引用：

master 推送至 master (可快进)

\$ git remote prune //移除已经删除的远程分支

\$ git branch -a

\* master

remotes/origin/HEAD -\> origin/master

remotes/origin/master

\$ git remote show origin

\* 远程 origin

获取地址：git@github.com:gaheadus/daily_use.git

推送地址：git@github.com:gaheadus/daily_use.git

HEAD 分支：master

远程分支：

master 已跟踪

为 \'git pull\' 配置的本地分支：

master 与远程 master 合并

为 \'git push\' 配置的本地引用：

master 推送至 master (可快进)

## 碰到的问题

**1.git push出问题**

git push出问题，提示：phs-gingerbread-dkbtd-dsds-dev_r2不存在，

解决：换一个分支push，push到phs-gingerbread-dsds-dev_r2；

![](media/image290.png){width="6.720138888888889in"
height="0.35555555555555557in"}

repo sync .的时候，跳出分支，不在任何分支的情况，

![](media/image291.png){width="3.5902777777777777in"
height="0.3138888888888889in"}

解决：repo sync .后跳出分支，可以使用repo start new_branch_name **.**
来在当前工程下**新建并跟踪**一个分支，然后就可以使用repo
sync了。必须要先使用repo start，才能使用repo sync？\--
因为所在分支不是跟踪分支，不能进行push/pull。

注：repo start new_branch_name 是在整个Android源码下新建跟踪分支，

repo start new_branch_name **.** ，是在当前工程下新建跟踪分支。

1.使用git branch new_br_name / git checkout -b
new_br_name新建的分支，只能在原有的base上修改代码，不能repo
sync，否则会报上面的错误；

2.使用repo start new_br_name **.**新建的分支，是可以使用repo
sync跟踪服务器最新代码的(所新建的分支中的代码也是最新的)；

根据需要选择采用上述两种方式之一来新建分支。

**2.** **git fetch出问题**

1.  git fetch ...//获取源码

2.  报冲突，conflict，

![](media/image292.png){width="6.0in" height="1.4402777777777778in"}

3.  vi/souceinsight修改冲突部分，

4.  git add .

5.  git commit //这里git commit后不带参数 \--
    如果不需要修改提交注释，那就不需要git commit，只需要git add就可以了

注意，在git
commit这一步,会弹出vi界面，**要记得把注释删除，**否则会出现change-id改变，从而无法push。

![](media/image293.png){width="3.8805555555555555in"
height="2.3208333333333333in"}

记得要把如下三行注释删掉，

conflicts:

src/com/android/contacts/dialpad/DialpadFragment.java

6.修改完冲突后，git rebase \--continue或git merge \--continue

明明已经将pub key上传到gerrit了，为什么还会报错：

\# git pull

dukang@172.16.30.72: Permission denied (publickey).

fatal: Could not read from remote repository.

Please make sure you have the correct access rights

and the repository exists.

原因：切换用户了，所以认证失败，切换回添加pub key的用户再git
pull就可以了。

\# su gaheadus

gaheadus@ubuntu:\~/work/UGW_Repo\$ git pull

Already up to date.

小结：切换到不同用户，需要添加该用户的pub
key到gerrit。虽然是同一台机器，但是不同用户，是不能用同一个pub key的。

## 记录

**在gerrit网页获取某个patch的下载地址**

\$ git fetch
ssh://shiguik@sh2-git01.marvell.com:19418/platform/frameworks/base
refs/changes/42/1242/1 && git cherry-pick FETCH_HEAD

## git clone

\$ git clone git@ip:path //下载到与远程库同名的本地目录

\$ git clone git@ip:path dirname //下载到本地指定目录dirname

问题：git clone后目录下没有任何代码，只有.git目录，git branch
-a看到没有本地分支、只有一个远程分支。

解决：在远处分支的基础上新建一个本地分支，git checkout origin/master -b
master。

git checkout -b master失败的原因：git checkout -b
master的含义是在当前所在分支的基础上建立一个新的分支master，然而现在没有本地分支，当前不在任何分支上，因此git
checkout -b
master失败。此时需要在远程分支origin/master的基础上建立本地分支，使用git
checkout origin/master -b master。

还有一种情况，git clone下来代码后，git
branch看有本地分支，但是没有代码，此时使用git restore **.**来恢复代码。

从其他地方复制的代码，如果只复制了.git库，同样只有本地分支、没有代码，也使用git
restore **.**来恢复代码。

git clone git@github.com:Forec/remote-control.git
//失败，需要pubkey，改用https协议下载，成功。

git clone https://github.com/Forec/remote-control.git
//如果只是下载代码，不想登录、传pubkey等繁琐步骤，可以这么操作

### 本地克隆

[git clone
url]{.mark}，从[远程git服务器]{.mark}下载代码。其实[本地代码复制也可以使用git
clone]{.mark}。

假设已有代码目录\~/code/test，使用[git clone \~/code/test
\~/code/test2]{.mark}可以将\~/code/test目录复制到\~/code/test2目录，复制包括.git库目录和代码目录。其实直接复制完整目录也一样cp
-rf \~/code/test/ \~/code/test2，或者cp -rf \~/code/test/.git
\~/code/test2/，然后在\~/code/test2目录下执行git restore .恢复代码。

相对于其他方式，[git clone \~/code/test \~/code/test2更简单直接，git
clone local_path1 local_path2，路径可以是相对路径或绝对路径]{.mark}。

## git remote

\$ git remote -v //显示所有远程仓库

\$ git remote -vv

\$ git remote show \[remote\] //显示某个远程仓库的信息

\$ git remote add \<LABLE_FOR_REMOTE\> \<URL\>

\$ git remote remove \[name\] //删除远程仓库

\$ git remote rename \[name1\] \[name2\]
//重命名远程库，将远程仓库名name1重命名为name2\
\$ git remote set-url \<LABLE_FOR_REMOTE\> \<URL\> //修改远程仓库的 url
地址

\$ git fetch \<LABLE_FOR_REMOTE\>

\$ git remote add \[name\] \[url\]
//增加一个新的远程仓库，并命名。这里只是为远程仓库建立一个别名，以后就可以使用这个别名代替远程仓库了。由于别名简短，使用起来更方便。例如git
remote add my_remote
https://github.com/gaheadus/test.git之后，所有使用远程仓库https://github.com/gaheadus/test.git的地方都可以用my_remote来代替，例如git
push my_remote master:remote_new_branch与git push
https://github.com/gaheadus/test.gitmaster:remote_new_branch等价。

\$ git remote -h

usage: git remote \[-v \| \--verbose\]

or: git remote **add** \[-t \<branch\>\] \[-m \<master\>\] \[-f\]
\[\--tags \| \--no-tags\] \[\--mirror=\<fetch\|push\>\] \<name\> \<url\>

or: git remote **remove** \<name\>

or: git remote **rename** \<old\> \<new\>

or: git remote set-head \<name\> (-a \| \--auto \| -d \| \--delete \|
\<branch\>)

or: git remote \[-v \| \--verbose\] show \[-n\] \<name\>

or: git remote prune \[-n \| \--dry-run\] \<name\>

or: git remote \[-v \| \--verbose\] update \[-p \| \--prune\]
\[(\<group\> \| \<remote\>)\...\]

or: git remote set-branches \[\--add\] \<name\> \<branch\>\...

or: git remote get-url \[\--push\] \[\--all\] \<name\>

or: git remote set-url \[\--push\] \<name\> \<newurl\> \[\<oldurl\>\]

or: git remote set-url \--add \<name\> \<newurl\>

or: git remote set-url \--delete \<name\> \<url\>

-v, \--verbose be verbose; must be placed before a subcommand

## git fetch

一旦远程主机的版本库有了更新，需要将这些更新取回本地，这时就要用到 git
fetch 命令。

git fetch \<远程仓库名\>

上面命令将某个远程主机的更新，全部取回本地。 默认情况下，git fetch
取回所有分支(branch)的更新。如果只想取回特定分支的更新，可以指定分支名。

git fetch \<远程仓库名\> \<分支名\>

比如，取回 origin 主机的 master 分支

git fetch origin master

所取回的更新，在本地主机上要用"远程仓库名/分支名"的形式读取。比如 origin
主机的 master，就要用 origin/master读取。

git fetch -p ：取回远程更新，删除不存在的分支。

默认情况下，git
fetch只更新当前分支所在仓库(包括当前仓库所有分支)，如果要更新所有仓库，使用git
fetch -all。

同样，git pull只更新当前分支所在仓库，git pull \--all更新全部仓库。

注意：git fetch -a不等效于git fetch \--all，git fetch
-a是append的意思，追加到.git/FETCH_HEAD而不是覆盖它。

## git pull

git pull
命令的作用是，取回远程主机的某个分支的更新，再与本地的指定分支合并，完整格式如下：

git pull \<远程仓库名\> \<远程分支名\>:\<本地分支名\>

比如，取回origin主机的next分支，与本地的master分支合并，需要写成下面这样。

git pull origin next:master

如果远程分支是与当前分支合并，则冒号后面的部分可以省略。

git pull origin master

上面的命令表示，取回 origin/master
分支，再与当前分支合并。实质上，这等同于先做 git fetch，再 merge。

git fetch origin

git merge origin/master

在某些场合，git
会自动在本地分支与远程分支之间，建立一种追踪关系(tracking)。比如，在 git
clone
的时候，所有本地分支默认与远程主机的同名分支，建立追踪关系，也就是说，本地的
master 分支自动"追踪" origin/master 分支。

git 也允许手动建立追踪关系。

git branch \--set-upstream master origin/next

上面的命令指定 master 分支追踪 origin/next 分支。

如果当前分支与远程分支存在追踪关系，git pull 就可以省略远程分支名。

git pull origin

上面命令表示，本地的当前分支自动与对应的 origin
主机"追踪分支"(remote-tracking branch)进行合并。

如果当前分支只有一个追踪分支，连远程仓库名都可以忽略。

git pull

上面命令表示，当前分支自动与唯一一个追踪分支进行合并。

如果合并需要采用 rebase 模式，可以使用 -rebase 选项。

git pull \--rebase \<远程仓库名\> \<远程分支名\>:\<本地分支名\>

**如果不想在git pull时打印提示信息，使用\--quiet/-q参数，git pull
\--quiet。**

### 临时性从另外一个git目录拉取代码

从远程ssh服务器的某个git目录拉取代码：\
git pull ssh://user@ubuntu_server_ip:/path/to/repo/.git main\
或者从本地另外一个git目录拉取代码：\
git pull /path/to/repo/.git main\
注意：路径必须写 .git 目录（非 bare 仓库的 git 数据目录）。

## git push

git push \<远程仓库名\> \<本地分支名\>:\<远程分支名\>

如果省略远程分支名，则表示将本地分支推送与之存在"追踪关系"的远程分支(通常两者同名)，如果该远程分支不存在，则会被新建。

git push origin master

默认推送当前分支。

git push origin master

git push origin master:master //等价

上面命令表示，将本地的master分支推送到origin主机的同名分支(master分支)。如果后者不存在，则会被新建。

**如果省略本地分支名，则表示删除指定的远程分支，因为这等同于推送一个空的本地分支到远程分支。**

git push origin \--delete master，简写git push origin -d
master，等同于git push origin :master

上面命令表示删除origin主机的master分支。如果当前分支与远程分支之间存在追踪关系，则本地分支和远程分支都可以省略。

本地缓存同步：删除远程分支后，其他团队成员或你本地的Git缓存可能仍会保留该分支的追踪引用。建议执行以下命令来清理本地已过时的远程分支信息：git
fetch \--prune(\--prune或-p表示修剪掉所有在远程已不存在的引用)。

git push origin

上面命令表示，将当前分支推送到 origin 主机的对应分支。
如果当前分支只有一个追踪分支，那么主机名都可以省略。

git push

如果当前分支与多个主机存在追踪关系，则可以使用-u选项指定一个默认主机，这样后面就可以不加任何参数使用
git push 。

git push -u origin master

上面的命令将本地 master 分支推送到 origin 主机，同时指定 origin
为默认主机，后面就可以不加任何参数使用 git push 了。不带任何参数的 git
push ，默认只推送当前分支，这叫做 simple 方式。此外，还有一种 matching
方式，会推送所有有对应的远程分支的本地分支。 git 2.0 版本之前，默认采用
matching 方式，现在改为默认采用 simple
方式，如果要修改这个设置，可以采用 git config 命令。

git config \--global push.default matching

或者

git config \--global push.default simple

还有一种情况，就是不管是否存在对应的远程分支，将本地的所有分支都推送到远程主机，这时需要使用
-all 选项。

[官方解释，git 2.9.5]{.mark}

**[push.default]{.mark}**

Defines the action **git push** should take if no refspec is given
(whether from the command-line, config, or elsewhere). Different values
are well-suited for specific workflows; for instance, in a purely
central workflow (i.e. the fetch source is equal to the push
destination), **upstream** is probably what you want. Possible values
are:

• **nothing** - do not push anything (error out) unless a refspec is
given. This is primarily meant for people who want to avoid mistakes by
always being explicit.

• **current** - push the current branch to update a branch with the same
name on the receiving end. Works in both central and non-central
workflows.

• **upstream** - push the current branch back to the branch whose
changes are usually integrated into the current branch (which is called
**\@{upstream}**). This mode only makes sense if you are pushing to the
same repository you would normally pull from (i.e. central workflow).

• **tracking** - This is a deprecated synonym for **upstream**.

• **simple** - pushes the current branch with the same name on the
remote.

If you are working on a centralized workflow (pushing to the same
repository you pull from, which is typically **origin**), then you need
to configure an upstream branch with the same name. This mode is the
default since Git 2.0, and is the safest option suited for beginners.

• **matching** - push all branches having the same name on both ends.
This makes the repository you are pushing to remember the set of
branches that will be pushed out (e.g. if you always push
[maint]{.underline} and [master]{.underline} there and no other
branches, the repository

you push to will have these two branches, and your local
[maint]{.underline} and [master]{.underline} will be pushed there).

To use this mode effectively, you have to make sure [all]{.underline}
the branches you would push out are ready to be pushed out before
running [git]{.underline} [push]{.underline}, as the whole point of this
mode is to allow you to push all of the branches in one go. If you
usually finish work on only one branch and push out the result, while
other branches are unfinished, this mode is not for you. Also this mode
is not suitable for pushing into a shared central repository, as other
people may add new branches there, or update the tip of existing
branches outside your control. This used to be the default, but not
since Git 2.0 ([**simple** is the new default]{.mark}).

git push \--all origin

上面命令表示，将所有本地分支都推送到 origin 主机。
如果远程主机的版本比本地版本更新，推送时 git 会报错，要求先在本地做 git
pull 合并差异，然后再推送到远程主机。这时，如果你一定要推送，可以使用
-force 选项。

git push \--force origin

上面命令使用-force选项，结果导致在远程主机产生一个"非直进式"的合并(non-fast-forward
merge)。除非你很确定要这样做，否则应该尽量避免使用 -force 选项。
最后，git push 不会推送标签(tag)，除非使用 -tags 选项。 git push origin
\--tags

https://cloud.tencent.com/developer/article/1960842?areaSource=102001.6&traceId=kGQh9YA68ioGgBufXQZRg

问题：执行git push \--delete
test删除远程分支报错"不存在该远程分支"，但是从远程仓库看test分支仍然存在。为什么？

可能是本地仓库的远程分支没了，与远程仓库不同步了？执行git fetch
\--all之后再git push \--delete test能不能解决问题？

\--阿里通义千问AI

[执行 git push \--delete test 报错"不存在该远程分支"(通常对应 remote ref
does not
exist)，但远程仓库实际上仍然存在该分支，这通常是由**命令语法错误**或**本地缓存过期**导致的]{.mark}。

以下是具体的原因分析及解决步骤：

**1.清理本地过期缓存**

Git
的"远程分支"本质上是本地对远程状态的一份快照缓存。如果你或同事之前删除过该分支，或者本地缓存长时间未更新，Git
可能会产生误判。

- 解决方法：执行以下命令强制拉取最新的远程分支列表，并清理本地已经失效的远程跟踪引用：

> [git fetch \--prune]{.mark} //简写 git fetch -p。

**2.确认远程分支的真实状态**

不要完全依赖 git branch -a 或 git branch
-r 的结果，因为它们显示的可能是本地缓存1。

- 验证方法：执行以下命令直接查询远程仓库的真实分支列表：

[git ls-remote \--heads origin \| grep \"test\"]{.mark}

如果输出中确实包含 test 分支，说明远程确实存在5。此时再使用正确的命令 git
push origin \--delete test 即可成功删除。

**3.检查分支保护规则与权限**

如果排除了以上问题仍然无法删除，可能是权限或平台保护策略导致的拦截。

- 分支保护：登录 GitHub/GitLab
  等远程仓库网页，检查该分支是否被设置为了"受保护分支(Protected
  Branches)"，受保护分支通常禁止直接删除。

- 权限不足：确认你的账号是否拥有删除分支的权限(例如 Gitolite
  中的 RW+ 权限，或 GitLab 中的 Maintainer
  权限)。如果是权限问题，通常会报 permission denied 或 cannot delete
  branch，但有时也可能表现为其他异常报错。

**4.检查命令语法是否多写了前缀(最常见原因)**

Git 对分支名称非常敏感。如果你在命令中误加了 origin/ 前缀(例如写成了 git
push origin \--delete origin/test)，Git
会去远程寻找一个名为 origin/test 的分支，自然会找不到并报错。

- 正确写法：命令后面只跟纯粹的分支名，不带任何前缀。

[git push origin \--delete test]{.mark}

- 注意：Git 对大小写敏感，请确保 test 的拼写与远程完全一致3。

**总结操作流：**\
先运行 git fetch \--prune 刷新缓存 -\> 确认命令写的是 git push origin
\--delete test(无 origin/ 前缀) -\>
若仍报错，通过网页端检查分支保护规则与个人权限。

如果执行 git ls-remote \--heads origin \| grep
\"test\" 后没有输出，说明远程仓库里其实已经没有这个分支了，可能是网页端缓存没刷新，需要我教你怎么强制清除网页缓存吗？

## pull/push/fetch格式总结

**git pull origin \<source\>:\<destination\>** //**git pull
\<远程仓库名\>
\<远程分支名\>:\<本地分支名\>**，source表示远程仓库的分支，destination表示本地分支

**git push origin \<source\>:\<destination\>** // **git push
\<远程仓库名\>
\<本地分支名\>:\<远程分支名\>**，source表示本地分支，destination表示远程仓库的分支

**git fetch origin \<source\>:\<destination\>** //同pull

**git pull/push/fetch repository \<source\>:\<destination\>**
//**从左到右，表示从source到destination**，pull/push/fetch在格式上是一样的。

见前面的章节：4)基本概念 -\> 六.git仓库和分支 ， 5)git命令操作图示 -\>
仓库与分支 、 远程仓库与操作

5)git命令操作图示 -\> 1.远程仓库与操作 -\> git pull的参数

## \--dry-run

pull/push/fetch都支持\--dry-run选项，表示pull/push/fetch操作时只是做"演习"，并不真正改变git库和工作目录。

\--dry-run，干跑，演习。

执行\--dry-run可以看到push的时候有哪些提交会上传，pull的时候有哪些提交会下载。

add、commit、clean等也支持\--dry-run。

\$ git add file
\--dry-run，需要指定file，这个选项好像没什么用处，在pull/push/fetch中还可以用来检查有哪些提交需要pull/push/fetch。

\$ git commit \--dry-run，显示结果和git status一样，也没什么用。

## git merge

通常，合并分支时，如果可能，Git 会用 Fast froward
模式，但这种模式下，删除分支后，会丢掉分支信息。 如果要强制禁用 Fast
forward 模式，Git 就会在 merge 时生成一个新的 commit
，这样，从分支历史上就可以看出分支信息。

git merge \--no-ff -m \'merge with no-ff\' dev

因为本次合并要创建一个新的 commit，所以加上 -m 参数，把 commit
描述写进去。

合并分支时，加上 \--no-ff
参数就可以用普通模式合并，合并后的历史有分支，能看出来曾经做过合并，而
fast forward 合并就看不出来曾经做过合并。

**git pull = git fetch + git merge**，git
pull默认使用merge来合并本地分支和远程分支，合并后产生一个新的提交Merge
branch \*\*\* into \*\*\*。

[git merge的提交历史和分支看上去混乱]{.mark}。

![](media/image294.png){width="1.5256944444444445in"
height="2.7215277777777778in"}

git merge的提交历史

使用git
rebase不会产生新的提交，只有一条分支，很直，看上去清爽，也便于后续维护。

git merge的历史有多条分支，git reset
\--hard回退到哪个分支的提交？是有歧义的，会造成结果的不一致。

git rebase只有一条分支，git reset \--hard回退到哪个提交是确定的。

因此，推荐是个git rebase来合并分支。

如果需要使用git rebase，那么可以分两步：先git fetch，再git rebase。

也可以使用git pull \--rebase指定pull时使用rebase，一步完成。

或者配置全局git config \--global pull.rebase true。

# 17)git服务器搭建 

## [创建git仓库](https://www.cnblogs.com/sxkgeek/p/9120742.html) 

**git init，初始化一个本地git仓库。**

**[usage: git init \[-q \| \--quiet\] \[\--bare\]
\[\--template=\<template-directory\>\] \[\--shared\[=\<permissions\>\]\]
\[\<directory\>\]]{.mark}**

\--template \<template-directory\> directory from which templates will
be used

\--bare create a bare repository

\--shared\[=\<permissions\>\] specify that the git repository is to be
shared amongst several users

-q, \--quiet be quiet

\--separate-git-dir \<git dir\> separate git dir from working tree

**\$ git init**
//**创建git库**，**在当前目录生成.git目录**，就是**git库目录**，在.git目录生成branches
config description HEAD hooks info objects refs等目录和文件

**\$ git init /home/dukang/work/testdir1**
//**在指定目录创建git库**，**生成.git目录**，就是**git库目录**，在.git目录生成branches
config description HEAD hooks info objects refs等目录和文件

**\$ git init \--bare**
//**\--bare**：**创建git库**，不生成.git目录，在当前目录生成branches
config description HEAD hooks info objects
refs等目录和文件，可见**当前目录就是.git库目录**。

**\$ git init \--bare /home/dukang/work/testdir2**
//**\--bare**：**在指定目录创建git库**，不生成.git目录，直接在指定目录生成branches
config description HEAD hooks info objects
refs等目录和文件。这个指定目录就是.git库目录。

**[git init用于创建本地git库，git init
\--bare用于创建远程git库]{.mark}**，见后面的内容：测试:搭建git服务器 -\>
测试1、测试4

## ubuntu搭建git服务器

https://www.cnblogs.com/EasonJim/p/8326220.html

环境：VMware创建ubuntu虚拟机作为git服务器，而客户端在windows系统下搭建。

**一、在ubuntu服务器上安装ssh、git，创建远程git库**

1、安装SSH

sudo apt-get install openssh-server

sudo service ssh start

2、安装git

sudo apt-get install git

3、创建用户git

sudo adduser git

4、禁止git用户Shell登录

sudo vim /etc/passwd

git:x:1001:1001:,,,:/home/git:/bin/bash\
改成\
git:x:1001:1001:,,,:/home/git:/usr/bin/git-shell

5、创建存放的仓库

sudo mkdir /home/git/repositories
#最好使用repositories作为文件夹名称，这样可以简化后面的操作

sudo chown git:git/home/git/repositories

sudo chmod 755 /home/git/repositories

6、创建子项目

cd /home/git/repositories

[sudo git init \--bare sample.git]{.mark}

7、修改子项目权限

sudo chown -R git:git sample.git

**二、在windows电脑上clone远程git库，生成本地git库**

1、在windows配置提交者的账号信息

git config \--global user.name \"你的注册用户名\"

git config \--global user.emall \"你的注册邮箱\"

2、在windows电脑上进行clone然后开始提交推送等操作

git clone git@IP:/home/git/repositories/sample.git

touch README

git add README

git commit -m \'first commit\'

git remote add origin git@IP:/home/git/repositories/sample.git

git push -u origin master

**三、配置免密码登录git账号**

在windows电脑上，使用ssh-keygen -t
rsa命令生成密钥，会在windons用户目录的/.ssh文件夹下生成id_rsa和id_rsa.pub。

将公钥id_rsa.pub的内容添加到ubuntu服务器的/home/git/.ssh/authorized_keys文件中。

在ubuntu服务器上创建.ssh文件夹并进入目录创建authorized_keys文件，将公钥id_rsa.pub的内容追加到此文件中。

　\$ mkdir .ssh

　\$ cat id_rsa.pub \>\> /home/git/.ssh/authorized_keys

这样就可以实现免密码登录。

其实不难发现这个操作就是SSH的免密码登录操作，参考：[[http://www.cnblogs.com/EasonJim/p/7569611.html]{.underline}](http://www.cnblogs.com/EasonJim/p/7569611.html)

**四、扩展**

要方便管理公钥，用[[gitosis]{.underline}](https://github.com/sitaramc/gitolite)；

要像SVN那样变态地控制权限，用[[gitolite]{.underline}](https://github.com/sitaramc/gitolite)，或者gogs。

参考

[[https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/00137583770360579bc4b458f044ce7afed3df579123eca000]{.underline}](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000/00137583770360579bc4b458f044ce7afed3df579123eca000)

[[http://blog.csdn.net/xsl1990/article/details/25486211]{.underline}](http://blog.csdn.net/xsl1990/article/details/25486211)

[[https://www.cnblogs.com/dee0912/p/5815267.html]{.underline}](https://www.cnblogs.com/dee0912/p/5815267.html)

[[http://blog.csdn.net/wave_1102/article/details/47779401]{.underline}](http://blog.csdn.net/wave_1102/article/details/47779401)

## 测试:搭建git服务器 \-- 验证OK, 20210807

安装git、配置ubuntu服务器，见前一节:git版本控制之ubuntu搭建git服务器。

### 测试1 \-- 使用git init \--bare建立远程git库 (推荐) {#测试1----使用git-init---bare建立远程git库-推荐 .标题紧3-8}

根据测试步骤1失败的经验，使用\--bare参数初始化远程git库。

**在ubuntu端建立远程git库**

root@ubuntu:/home/sgk/work# mkdir sample

[root@ubuntu:/home/sgk/work# cd sample]{.mark}

[root@ubuntu:/home/sgk/work**\# git init \--bare
//初始化git库**。只有这里和测试1不一样。]{.mark}

[root@ubuntu:/home/sgk/work# **git init \--bare sample**
//上述两条命令可以合并成这一条命令]{.mark}

root@ubuntu:/home/sgk/work# ls sample -a

. .. branches config description HEAD hooks info objects refs

root@ubuntu:/home/sgk/work# cd sample

root@ubuntu:/home/sgk/work/sample# git status //报错。但是可以使用git
log、git branch

fatal: this operation must be run in a work tree

root@ubuntu:/home/sgk/work/sample# git branch //默认创建master分支

\* master

root@ubuntu:/home/sgk/work/sample# git log

fatal: your current branch \'master\' does not have any commits yet

**在windows端克隆，生成本地git库**

\$ git clone git@192.168.161.130:/home/sgk/work/sample

[\$ ls -a]{.mark}

[. .. .git //默认生成了.git目录。使用git init
\--bare创建的远程库上是没有这个目录的。]{.mark}

\$ git branch -a

\* master

remotes/origin/master

\$ git remote -v

origin git@192.168.161.130:/home/sgk/work/sample (fetch)

origin git@192.168.161.130:/home/sgk/work/sample (push)

新建一个文件，提交

\$ vim 1.txt

\$ git add 1.txt

\$ git commit -m \"1st commit\"

**\$ git push**

[error: remote unpack failed :unable to create temporary object
directory]{.mark}

To 192.168.161.130:/home/sgk/work/sample

! \[remote rejected\] master -\> master (unpacker error)

error: failed to push some refs to
\'192.168.161.130:/home/sgk/work/sample\'

报错了。

[原因：权限不够，无法在远程git库上创建文件。]{.mark}

到ubuntu服务器端查看git库权限

root@ubuntu:/home/sgk/work# ls -l

drwxrwxr-x 3 sgk sgk 4096 Aug 7 01:51 sample

[sample所有者是sgk，不是git。更改所有者为git，]{.mark}

[root@ubuntu:/home/sgk/work# **chown -R git:git sample/**]{.mark}

root@ubuntu:/home/sgk/work# ls -l

drwxrwxr-x 3 git git 4096 Aug 7 01:51 sample

回到windows客户端**再次push**，**成功**。

到ubuntu服务器端查看

root@ubuntu:/home/sgk/work/sample# git log

commit ef3c54df25f96ba961244b38f708b92af6f57b23 (HEAD -\> master)

Author: gaheadus \<gaheadus@163.com\>

Date: Sat Aug 7 18:26:57 2021 +0800

1st commit

root@ubuntu:/home/sgk/work/sample# ls

branches config description HEAD hooks info objects refs

在远程git库上有git log记录，但是看不到客户端提交的文件(没有git工作区)。

有什么办法初始化一个远程git库，保存在.git目录，在远程git库能到修改的文件？\--
不行，只有在客户端才能看到.git库目录和没有git工作区。

### 测试2 \-- 使用git init建立远程git库 {#测试2----使用git-init建立远程git库 .标题紧3-8}

**在ubuntu端建立远程git库**

root@ubuntu:/home/sgk/work# cd /home/sgk/work/

root@ubuntu:/home/sgk/work# mkdir sample2

root@ubuntu:/home/sgk/work# cd sample2

[root@ubuntu:/home/sgk/work/sample2**\# git init //初始化git库**]{.mark}

root@ubuntu:/home/sgk/work/sample2# ls -a [//生成了.git目录]{.mark}

. .. .git

root@ubuntu:/home/sgk/work/sample2# vim first.c

root@ubuntu:/home/sgk/work/sample2# git add first.c

root@ubuntu:/home/sgk/work/sample2# git commit -m \"first commit\"

**在windows端克隆，生成本地git库**

\$ git clone git@192.168.161.130:/home/sgk/work/sample2

\$ cd sample2

\$ ls

first.c

新建一个文件，提交

\$ vim second.cpp

\$ git status

\$ git diff

\$ git add second.cpp

\$ git commit -m \"add a file from the client\"

\$ git push

git@192.168.161.130\'s password:

remote: error: refusing to update checked out branch: refs/heads/master

remote: error: [By default, updating the current branch in a non-bare
repository]{.mark}

remote: [is denied]{.mark}, because it will make the index and work tree
inconsistent

remote: with what you pushed, and will require \'git reset \--hard\' to
match

remote: the work tree to HEAD.

remote:

remote: You can set the \'receive.denyCurrentBranch\' configuration
variable

remote: to \'ignore\' or \'warn\' in the remote repository to allow
pushing into

remote: its current branch; however, this is not recommended unless you

remote: arranged to update its work tree to match what you pushed in
some

remote: other way.

remote:

remote: To squelch this message and still keep the default behaviour,
set

remote: \'receive.denyCurrentBranch\' configuration variable to
\'refuse\'.

To 192.168.161.130:/home/sgk/work/sample

! \[remote rejected\] master -\> master (branch is currently checked
out)

error: 推送一些引用到 \'192.168.161.130:/home/sgk/work/sample\' 失败

报错了。

[**只能用\--bare参数来创建远程git库**？]{.mark}

网上的一个解决办法：https://blog.csdn.net/wangjia55/article/details/48549403

这是因为git默认拒绝了push操作，需要进行设置，修改.git/config文件后面添加如下代码：

\[receive\]

denyCurrentBranch = ignore

[但是这样造成一个问题：在远程git库上无法查看push后的代码。]{.mark}

**[建议在初始化远程仓库时使用git init \--bare，而不要使用git
init。]{.mark}**

git init 和git init \--bare有什么区别？

如果使用了git init初始化，则远程仓库的目录下，也包含work
tree，当本地仓库向远程仓库push时，如果远程仓库正在push的分支上(如果当时不在push的分支,那就没有问题)，那么push后的结果不会反应在work
tree上，也即在远程仓库的目录下对应的文件还是之前的内容。

解决方法：远程仓库使用 git reset \--hard 才能看到客户端push后的内容。

### 小结 {#小结-1 .标题紧3-8}

概念

git仓库：远程git库，本地git库。

git分支：远程分支，本地分支。

git库目录、git工作目录(git工作区)、暂存区。

测试2：git init
dir，在dir下[生成.git目录，就是git库目录]{.mark}，dir下除.git目录之外的部分是[git工作区]{.mark}。可以在dir目录进行

git status、git add、git commit等操作。

测试1：git init \--bare
dir，不生成.git目录，[dir目录就是(远程)git库目录]{.mark}。[只有git库目录，没有git工作区]{.mark}。

因为没有git工作区，所以不能在dir目录进行git add、git commit、git
status，执行这些命令会报错: fatal: this operation

must be run in a work tree。

git
clone到本地后，[生成.git目录就是本地git库目录]{.mark}，本地目录除.git目录之外的部分是git工目录。

在git工作目录进行git status、git add、git commit、git
push等操作。在本地库目录.git下也是不能进行git status、

git add、git commit操作的，和远程git库目录一样报错。🡪
在git库目录，不管是本地.git目录还是远程dir目录，

都只能使用git branch、git log命令，不能进行git add、git commit、git
status等操作。本地git库local/.git目录和

远程git库dir目录的内容是一样的，只有config文件不一样，本地git库多了index、packed-refs两个文件。

推荐**使用git init \--bare创建远程仓库** \-- 测试1

推荐**使用git init创建本地仓库** \-- 测试4

git init也能创建远程仓库，但是使用会有问题：git
clone到本地后无法push到远程仓库，不推荐这种方式创建远程仓库。

### 测试3 \-- 远程库和本地库在同一台电脑上 {#测试3----远程库和本地库在同一台电脑上 .标题紧3-8}

测试2将远程git库放在ubuntu，在windows端使用git clone
git@ip:/home/path克隆到本地git库。

事实上，**远程库**和**本地库**可以**在同一台电脑上**，git clone
url时使用**本地路径**(绝对路径相对路径都可以)。

在ubuntu上

**①建立远程git库**

root@ubuntu:/home/sgk/work# mkdir sample3

root@ubuntu:/home/sgk/work# git init \--bare sample3

**②克隆远程git库，生成本地git库**

root@ubuntu:/home/sgk/work# mkdir test

root@ubuntu:/home/sgk/work# cd test/

[root@ubuntu:/home/sgk/work/test# **git clone /home/sgk/work/sample3**
//使用本地路径(绝对路径)]{.mark}

[root@ubuntu:/home/sgk/work/test# **git clone ../sample3**
//使用本地路径(相对路径)]{.mark}

root@ubuntu:/home/sgk/work/test# ls

sample3

root@ubuntu:/home/sgk/work/test# cd sample3/

[root@ubuntu:/home/sgk/work/test/sample3# ls -a]{.mark}

[. .. .git]{.mark}

后续步骤和windows上是一样的，可以在这个本地git库新增文件、git
add、commit、push等操作。

### 测试4 \-- 本地已有git仓库，关联到远程仓库 {#测试4----本地已有git仓库关联到远程仓库 .标题紧3-8}

前面的测试都是先建立远程git库，再从远程库克隆到本地，先有远程git库后有本地git库。

测试4描述的是先建立本地git库，然后**[将已有本地库关联到远程git库]{.mark}**，先有本地git库，后有远程git库。

**对于[已有本地git库，并且在本地仓库已经有多次提交，需要保留本地提交历史记录的情况]{.mark}**，适合于本节描述的方法。

**①创建本地git库，并进行了多次提交**

\$ mkdir test

\$ cd test

\$ git init

\$ vim helloworld.c

\$ git add helloworld.c

\$ git commit -m \"1st commit\"

\$ vim test.c ; git add test.c ; git commit -m \"2nd commit\"

\$ ...

**②创建远程git库**

root@ubuntu:/home/sgk/work# mkdir sample4

root@ubuntu:/home/sgk/work# git init \--bare sample4

**③将本地库关联到远程库**

目前，远程服务器上的这个sample4仓库还是空的，[可以clone远程库到本地，也可以将已有的本地库关联到远程库，然后将本地库推送到远程库]{.mark}。

\$ cd test

**[\$ git remote add origin
git@192.168.161.130:/home/sgk/work/sample4]{.mark}**

\$ git branch

\* master

\$ git push //报错

fatal: The current branch master has no upstream branch.

To push the current branch and set the remote as upstream, use

git push \--set-upstream origin master //根据提示操作

\$ git push \--set-upstream origin master //成功

**④回到远程仓库查看**

回到远程仓库，使用git
log可以看到本地仓库以前就有的提交历史记录已经提交到远程仓库了。

小结2

使用git init创建本地仓库，可以在本地进行修改提交，git diff/git add/git
commit/git branch支持大部分操作，只是没有关联的远程git库，不能git
push。**这些提交历史记录都保存在本地git库**。如果只需要在本地修改/保存/提交/查看，那么这样就可以了，不需要再有其他操作。[如果想在任何地方都能复制或者下载这些修改和提交历史，或者需要分享给其他人下载，那么可以将其保存到远程服务器上]{.mark}。测试4就是为了解决:**[先有本地git库后有远程git库、需要将本地库的提交历史记录保存到远程库]{.mark}**的情况。

如果本地git库没有于远程库关联，那么git branch
-a看到的只有本地分支没有远程分支，git remote -v看到的是空的。

### 测试5 \-- 远程库和本地库在同一台电脑上(windows) {#测试5----远程库和本地库在同一台电脑上windows .标题紧3-8}

使用cygwin命令行。

windows没有linux那么严格的用户和权限管理，使用起来更简单。

**①创建远程git库**

\$ pwd

/cygdrive/f/temp/

**\$ mkdir remotedir**

\$ ls -l \| grep remotedir

drwxrwxr-x+ 1 dukang None 0 Aug 16 01:04 remotedir

\$ cd remotedir

**[\$ git init \--bare]{.mark}**

\$ ls

HEAD config description hooks info objects refs

**②克隆远程git库到本地**

\$ pwd

/cygdrive/f/temp/

\$ mkdir localdir

\$ ls -l \| grep localdir

drwxrwxr-x+ 1 dukang None 0 Aug 16 01:12 localdir

\$ cd localdir/

**[\$ git clone ../remotedir/]{.mark}**

**[\$ git clone /cygdrive/f/temp/remotedir]{.mark}**
//相对路径、绝对路径都可以

\$ ls

remotedir

\$ cd remotedir/

\$ ls -a

. .. .git

\$ git status

On branch master

No commits yet

nothing to commit (create/copy files and use \"git add\" to track)

\$ echo 1111 \> 1.txt

\$ git status

\$ git add 1.txt

\$ git commit -m \"1st commit\"

\$ git push

Enumerating objects: 3, done.

Counting objects: 100% (3/3), done.

Writing objects: 100% (3/3), 203 bytes \| 203.00 KiB/s, done.

Total 3 (delta 0), reused 0 (delta 0), pack-reused 0

To /cygdrive/f/temp/localdir/../remotedir/

\* \[new branch\] master -\> master //创建一个分支master

远程仓库是空的，是没有分支的。第一次提交、第一次push的时候会创建一个master分支。

\$ git branch

\* master

\$ git branch -r

origin/master

\$ git branch -a

\* master

remotes/origin/master

\$ git remote -v

origin /cygdrive/f/temp/localdir/../remotedir/ (fetch)

origin /cygdrive/f/temp/localdir/../remotedir/ (push)

**[在这里，本地库和远程库都在同一台windows电脑上，本地和远程只是概念上的东西，远程并不需要在另外一天远程电脑上。]{.mark}**

**[应用：windows使用cygwin，在同一台电脑上建立本地仓库和远程仓库，方便资料保存、跟踪修改状态。远程仓库设置为隐藏，本地仓库下的.git/.gitignore/.gitkeep等都设置为隐藏。]{.mark}**

[在windows中，通常需要从大量文件中跟踪少数几个文件，.gitignore只需要写一个\*符号，表示忽略所有文件，对于需要git跟踪的单个文件或目录使用git
add -f。]{.mark}

从另外一台电脑克隆windows上的远程git库

**\$ git clone dukang@192.168.1.16:/cygdrive/f/temp/remotedir** \-- fail

Cloning into \'remotedir\'\...

[ssh: connect to host 192.168.1.16 port 22: Connection refused]{.mark}

fatal: Could not read from remote repository.

Please make sure you have the correct access rights

and the repository exists.

可知，git
clone使用的是ssh协议。windows默认没有开通ssh访问功能，因此报错。

如何解决上述报错？

win10开启ssh server服务远程登录

路径不应该写/cygdrive/f/temp/remotedir，应该写/f:/temp/remotedir，按照ssh访问的方式来写。

\$ git clone dukang@192.168.1.16:/f:/temp/remotedir \-- fail

\$ git clone dukang@192.168.1.16:f:\\\\temp\\\\remotedir \-- fail

\$ ssh dukang@10.1.1.211 \-- success

\$ ssh dukang@10.1.1.211 dir f:\\\\gittest\\\\remotedir \-- success

ssh登录win10成功，但是scp和git失败，尝试路径的多种写法都失败。目前没有找到方法。20210816

**windows开启sshd服务：**

![](media/image295.emf)

https://www.pugetsystems.com/labs/hpc/How-To-Use-SSH-Client-and-Server-on-Windows-10-1470/?\_\_cf_chl_captcha_tk\_\_=pmd_411d430258e82efc055ee415d5d633174828c133-1629126950-0-gqNtZGzNA3ijcnBszQiO

### 测试6 \-- 已有本地git库，远程库和本地库在同一台windows电脑上 {#测试6----已有本地git库远程库和本地库在同一台windows电脑上 .标题紧3-8}

测试6=测试4+测试5

windows已有本地git库

\$ cd \"d:/work/ziliao/cmds\"

\$ git remote show

origin

\$ git remote -vv

origin git@192.168.248.128:/home/tenda/backup/daily_use/cmds (fetch)

origin git@192.168.248.128:/home/tenda/backup/daily_use/cmds (push)

windows创建远程git库

\$ cd \"D:\\me\\backup\\gitrepo\\cmds\"

\$ git init \--bare

已初始化空的 git仓库于 /cygdrive/d/me/backup/gitrepo/cmds/

添加远程库

\$ git remote add winremote d:/me/backup/gitrepo/cmds

\$ git remote show

origin

winremote

\$ git remote -v

origin git@192.168.248.128:/home/tenda/backup/daily_use/cmds (fetch)

origin git@192.168.248.128:/home/tenda/backup/daily_use/cmds (push)

winremote d:/me/backup/gitrepo/cmds (fetch)

winremote d:/me/backup/gitrepo/cmds (push)

\$ git push winremote //有多个远程库时需要指定push到哪一个远程库

To d:/me/backup/gitrepo/cmds

\* \[new branch\] master -\> master

删除旧的远程库

\$ git remote remove origin

\$ git remote show

winremote

\$ git remote -v

winremote d:/me/backup/gitrepo/cmds (fetch)

winremote d:/me/backup/gitrepo/cmds (push)

\$ git push

fatal: No configured push destination.

Either specify the URL from the command-line or configure a remote
repository using

git remote add \<name\> \<url\>

and then push using the remote name

git push \<name\>

能不能直接使用git push？ \-- 可以

\$ git push \--set-upstream winremote master

Branch \'master\' set up to track remote branch \'master\' from
\'winremote\'

Everything up-to-date

做了一次之后，现在已经有了一个跟踪分支，后续就可以直接使用git push了。

\$ git push

Everything up-to-date

参考：http://www.955yes.com/ask/107680989.html

另：

\$ git branch \--set-upstream-to origin/master

Branch master set up to track remote branch master from origin.

## git init和git init \--bare的区别

如果使用了git init初始化，则远程仓库的目录下，也包含work
tree，当本地仓库向远程仓库push时，如果远程仓库正在push的分支上(如果当时不在push的分支,就没有问题),
[那么push后的结果不会反应在work tree上]{.mark},
也即在远程仓库的目录下对应的文件还是之前的内容，必须得使用git reset
\--hard才能看到push后的内容。

用\"git init \--bare\"初始化的版本库(暂且称之为bare
repository)[仅包含\".git\"目录(记录版本历史)，不含项目源文件拷贝]{.mark}。如果你进入版本目录，你会发现仅有\".git\"目录，没有其他文件。版本库仅包含记录着版本历史的文件。

用\"git
init\"初始化的版本库用户也可以在该目录下执行所有git方面的操作。但别的用户在将更新push上来的时候容易出现冲突。

比如有用户在该目录(就称为远端仓库)下执行git操作，且有两个分支(master和b1)，当前在master分支下。另一个用户想把自己在本地仓库(就称为本地仓库)的master分支的更新提交到远端仓库的master分支，他就想当然的敲了

git push origin master:master

于是乎出现错误，因为远端仓库的用户正在master的分支上操作，而你又要把更新提交到这个master分支上，当然就出错了。

但如果是往远端仓库中空闲的分支上提交还是可以的，比如git push origin
master:b1还是可以成功的。

解决办法就是**使用\"git init
\--bare\"方法创建裸仓库**，之所以叫裸仓库是因为这个仓库只保存git历史提交的版本信息，而不允许用户在上面进行各种git操作，如果你硬要操作的话，只会产生错误：This
operation must be run in a work
tree。这个就是最好把远端仓库初始化成bare仓库的原因。

## git init指定默认分支名

\$ git init

提示：使用 \'master\'
作为初始分支的名称。这个默认分支名称可能会更改。要在新仓库中

提示：配置使用初始分支名，并消除这条警告，请执行：

提示：

提示： git config \--global init.defaultBranch \<名称\>

提示：

提示：除了 \'master\' 之外，通常选定的名字有 \'main\'、\'trunk\' 和
\'development\'。

提示：可以通过以下命令重命名刚创建的分支：

提示： git branch -m \<name\>

\$ git config \--global init.defaultBranch dukang //[这条命令要在git
init创建仓库之前执行才有效]{.mark}

\$ git config \--global \--list

user.email=gaheadus@126.com

user.name=dukang

init.defaultbranch=dukang

\$ git init

已初始化空的 git 仓库于 /cygdrive/d/me/code/temp2/.git/

\$ git status

位于分支 dukang

尚无提交

无文件要提交(创建/拷贝文件并使用 \"git add\" 建立跟踪)

\$ git branch

//还没有提交记录，分支还是空的

\$ echo B1 \> file1

\$ git add .

\$ git commit -m \"add_file1\"

\[dukang(根提交) 2de484f\] add_file1

1 file changed, 1 insertion(+)

create mode 100644 file1

\$ git branch

\* dukang

有一个提交之后，可以看到有分支了。

\$ git log

commit 2de484fe0aee4f7d62ece82de5c072e1259d84e5 (HEAD -\> dukang)

Author: dukang \<dukang@tenda.cn\>

Date: Tue Aug 30 10:10:02 2022 +0800

add_file1

# 18)专题

## "detached HEAD"state(分离头指针状态)

"detached HEAD"state(分离头指针状态)------HEAD
头指针指向了一个具体的提交ID，而不是一个引用(分支)。

下面的例子是我在"分离头指针"状态添加了很多文件，结果发现没有在任何分支上，结果切换到了master分支上，之前的操作早不到了，即在"分离头指针"的状态的操作没有任何意义。

![](media/image296.png){width="3.76875in" height="2.0597222222222222in"}

按照上面的操作，不知道如何合并"分离头指针状态"做的操作，类似于解决了在master分支上做的操作，解决办法如下：

![](media/image297.png){width="4.26875in" height="0.6715277777777777in"}

执行如下命令

git merge 3f263a6

**代码commit到了莫名的分支或者被分离的HEAD上了，如何处理**

*https://www.jianshu.com/p/5c2422919f72*

只需三部就可以把你不知道提交到了哪的代码，再移动到选定分支上；

这种情况的出现原因:

1:
有可能是确实提交到了某条分支上，但是提交之后发现分支错了，找不到那次提交了；

2: 有可能是未检出分支或者未切换分支，直接在分离的HEAD上进行开发了，
这时你commit后的代码实际是属于游离状态的，不属于任何分支，但是你的电脑本地是存在提交记录的；这就是找回代码的依据；

第一步：git
reflog，(查看所有分支的所有操作记录(包括commit和reset的操作，包括已经被删除的commit记录，git
log则不能察看已经删除了的commit记录)

找到你丢失的那次commit记录，记下commit id (就是前面的一串字母加数字)

第二步：git checkout \<你想提交到的分支上\>

例如：git checkout master，(查看远端的全部分支： git branch -a
(列出全部的分支名))

第三步：git cherry-pick \<commit id\> 例如：git cherry-pick hbd37gf76sg

(\<commit id\>就是在第一步里记录的commit id)
选出这次记录重新提交到当前分支上

(此时，如果使用了SourceTree，就可以在该分支的提交记录上看到了此次提交)，
然后再正常的pull + push 就OK了

## 查看本地分支追踪和远程分支的关系

git跟踪远程分支，查看本地分支追踪和远程分支的关系。
<https://www.jianshu.com/p/4ceb39ee4b2b>

**跟踪远程分支**

如果用git
push指令时，当前分支没有跟踪远程分支(没有和远程分支建立联系)，那么就会git就会报错

There is no tracking information for the current branch. Please specify
which branch you want to merge with.

因为当前分支没有追踪远程指定的分支的话，**不知道要推送给哪一个分支**，当前分支指定的版本快照不知道要作为服务器哪一个分支的版本快照的子节点。

那么如何建立远程分支：

①.克隆时自动将创建好的master分支追踪origin/master分支

git clone 服务器地址

②.git checkout -b develop origin/develop

在远程分支的基础上建立develop分支，并且让develop分支追踪origin/develop远程分支。

③.git branch \--set-upstream branch-name origin/branch-name

将branch-name分支追踪远程分支origin/branch-name

④.git branch -u origin/serverfix

设置当前分支跟踪远程分支origin/serverfix

**查看本地分支和远程分支的跟踪关系**

\$ git branch -vv

develop 08775f9 \[origin/develop\] develop

feature_1 b41865d \[origin/feature_1\] feature_1

\* master 1399706 \[my_github/master\] init commit

可知，

develop分支跟踪origin/develop

feature_1分支跟踪origin/feature_1

master跟踪了my_github/master，且当前分支为master分支

那么假如我此时想要将master的改变推送到origin服务器的master分支上：

\$ git checkout master//切换到master分支 \...

\$ git branch -u origin/master//将当前分支跟踪origin/master Branch
\'master\' set up to track remote branch \'master\' from \'origin\'.

之后就可以执行git add和git commit了。

现在再查看一下本地和远程的分支关系：

\$ git branch -v

develop 08775f9 \[origin/develop\] develop

feature_1 b41865d \[origin/feature_1\] feature_1

\* master 1399706 \[origin/master\] init commit

master已经跟踪了origin/master了。

## repo使用

参考：总结,repo.doc

## 历史记录

1.Ubuntu下查看命令执行历史：history

2.git下查看一个文件的修改历史：git log -p \<file_name\>

3.git下查看一个文件的最新修改：git blame \<file_name\>

git log -p \<file_name\>和git blame \<file_name\>的不同：git log
-p查看一个文件每一次的修改记录，git blame查看文件最新的一次修改。

使用 git经常遇到这样的使用场景

•查看一个文件被哪些兄弟修改过

•查看一个文件近期是否发生改动

查看一个文件的历史修改记录列表

git log \<file_name\>

会列出 commit 的概要列表

\$ git log src/views/ArticleView.vue

commit 57448f63785b3e4fe43f88b56969215c7b2325be

Author: Hanks \<zhanghan.me@gmail.com\>

Date: Sat Dec 31 03:15:53 2016 +0800

add https filter for url

commit 30c885432007ef1e8a54b7f68dc5be975feef8fb

Author: Hanks \<zhanghan.me@gmail.com\>

Date: Sat Dec 31 03:05:54 2016 +0800

add global mixin

commit adc5d7cfdf7294f261cb5a8c413b613917b29630

Author: Jinjiang \<zhaojinjiang@me.com\>

Date: Fri Dec 30 01:26:42 2016 +0800

improved \<web\> preview

commit c3b61ad119815f8a3975e7e6529202495714cb1a

Author: Hanks \<zhanghan.me@gmail.com\>

Date: Thu Dec 22 01:34:30 2016 +0800

modify the component dependence

commit 8d03b2419895c1ee3a564cd818cce87550a0dde5

Author: Hanks \<zhanghan.me@gmail.com\>

Date: Mon Dec 19 17:33:31 2016 +0800

\[router\] import vue-router

commit 14922ceb40bc7cbd35d83adcd67f57f12e6330b9

Author: Hanks \<zhanghan.me@gmail.com\>

Date: Thu Dec 15 16:48:47 2016 +0800

\[vue\] add artice view

如果想查看一次提交的具体修改

git show \<commit\>

例如

\$ git show 57448f63785b3e4fe43f88b56969215c7b2325be

commit 57448f63785b3e4fe43f88b56969215c7b2325be

Author: Hanks \<zhanghan.me@gmail.com\>

Date: Sat Dec 31 03:15:53 2016 +0800

add https filter for url

diff \--git a/src/filters/index.js b/src/filters/index.js

index c102984..03eb942 100644

\-\-- a/src/filters/index.js

+++ b/src/filters/index.js

@@ -6,6 +6,13 @@ export function host (url) {

return parts.join(\'.\')

}

+export function https (url) {

\+ if (WXEnvironment.platform === \'iOS\' && typeof url === \'string\')
{

\+ return url.replace(/\^http\\:/, \'https:\')

\+ }

\+ return \'\'

+}

\+

一次性展示出所有提交的具体修改

git log -p \<file_name\>

原文：https://www.sunzhongwei.com/git-view-the-change-history-of-the-specified-file

## 使用通配符和特殊符号

git支持\*?两个通配符，

git add example.?，添加example.c和example.h，

git add \-- \*.c，添加全部c文件。

git diff example.?，

git diff \-- \*.c。

使用\*时加上\--防止git将文件名误认为命令参数。

但是，git add
.，添加当前目录下全部文件，.不是通配符，也不是正则表达式任意一个符号的意思。

[.由git解释，而通配符\*?由shell解释。]{.mark}

[点号.在git中被认为是一个路径，.表示当前路径，git add .、git reset
.、git checkout .等。]{.mark}

git是否支持正则表达式？

## 单引号/双引号

\$ git restore \--staged \"\~\$ATBM6463记录-红外雷达.docx\"

error: pathspec \'\~记录-红外雷达.docx\' did not match any file(s) known
to git

改成单引号，正常

\$ git restore \--staged \'\~\$ATBM6463记录-红外雷达.docx\'

## \^\~与多个父提交

相对提交名

- Git还提供一种机制来确定相对于另一个引用的提交，通常是分支的头。

例如，master和master\^，其中master\^始终指的是在master分支中的倒数第二个提交。还有一些其他的方法，例如master\^\^、master\~2，甚至像master\~10\^2\~2\^2这样复杂的名字。

- 除了第一个根提交之外，每一个提交都来自至少一个比它更早的提交，这其中的直接祖先称作该提交的父提交。若某个提交存在多个父提交，那么它必定是由合并操作产生的。其结果是，每个分支都有一个父提交贡献给合并提交。

- 在同一代提交中，插入符号\^是用来选择不同的父提交的。给定一个提交C，C\^1是其第一个父提交，C\^2是其第二个父提交，C\^3是其第三个父提交等等，如图6-1所示。

![](media/image298.png){width="1.7006944444444445in"
height="1.6756944444444444in"} \--
**怎么确定哪一个是c\^1，哪个是c\^2？**

- 波浪线～用于返回父提交之前并选择上一代提交。同样，给定一个提交C，C\~1是其第一个父提交，C\~2是其第一个祖父提交，C\~3是第一个曾祖父提交。当在同一代中存在多个父提交时，紧跟其后的是第一个父提交的第一个父提交。你可能会注意到，C\^1和C\~1都指的是C的第一个父提交，两个都是对的，如图6-2所示。

![](media/image299.png){width="2.1618055555555555in"
height="1.6958333333333333in"}

- Git也支持其他形式的简写和组合。如C\^和C\~两种简写形式分别等同于C\^1和C\~1。另外，C\^\^与C\^1\^1相同，因为这代表提交C的第一父提交的第一父提交，它也可以写做C\~2。

- 通过把引用与"\^"和"\~"组合，就可以从提交历史图中引用任意提交。不过要注意，这些名字都相对于引用的当前值。如果当前引用指向一个新提交，那么提交历史图将变为"新版本"，所有父提交"辈分"都会上升一层。

+-----------------------------------------------------------------------+
| //查看master分支的SHA1值                                              |
|                                                                       |
| \# git rev-parse master                                               |
|                                                                       |
| f0cd009b8980e0845e271c568b44bace460c2aa2                              |
|                                                                       |
|                                                                       |
|                                                                       |
| //列出当前分支的历史提交                                              |
|                                                                       |
| \# git show-branch \--more=10                                         |
|                                                                       |
| \[master\] Commit a file that says hello3                             |
|                                                                       |
| \[master\^\] Commit a file that says hello2                           |
|                                                                       |
| \[master\~2\] Commit a file that says hello                           |
+:======================================================================+

- git
  rev-parse命令会把任何形式的提交名(包含标签、相对名、简写或绝对名称)转换成对象库中实际的提交ID。

https://www.cnblogs.com/maiblogs/p/17228437.html

## 忽略某些文件(夹)：.gitignore

### 一个通用.gitignore文件 {#一个通用.gitignore文件 .标题紧3-8}

一个通用.gitignore文件，内容如下：

target/ #忽略该文件夹。\'#\'表示注释

offer.iml #忽略该文件

\*.rar #忽略所有.rar文件

!src/ #不忽略该文件夹

!.gitignore #不忽略该文件

!/mtk/do.c

!\*.zip #不忽略所有.zip文件

\*.\[oa\]   #忽略后缀名为.o和.a的文件

\~\*
#windows下忽略word产生的临时文件。备注：单独一个\*符号表示忽略所有文件。

### 详解.gitignore {#详解.gitignore .标题紧3-8}

1、给项目添加.gitignore

.gitignore可以忽略你不想让git跟踪的文件，比如doc,target,classes等等。

[在.git同目录下创建一个.gitignore文件]{.mark}，添加不需要被git跟踪的目录或文件，例如

/doc/

/target/

/.idea/

/offer.iml

2、对于已经添加到.gitignore忽略的文件，可以使用git add -f添加。

3、git对于.gitignore
配置文件是按行从上到下进行规则匹配的，意味着如果前面的规则匹配的范围更大，则后面的规则将不会生效。

[4、不仅根目录可以使用.gitignore过滤，子目录也可以使用.gitignore创建自己的过滤规则。子目录.gitignore根据各自目录创建过滤规则，避免根目录下.gitignore使用大而全的规则应用于所有目录、无法精确控制。]{.mark}

**[5、要养成在项目开始就创建.gitignore文件的习惯，否则一旦push，处理起来会非常麻烦。]{.mark}**

为什么.gitignore中的文件没有起作用？

已经将文件添加到.gitignore，但是没起作用，git
status查看仍然显示文件有修改，为什么？

因为.gitignore只能忽略那些原来没有被track的文件，也就是说.gitignore设置的规则只对规则设置之后的文件有效，对在.gitignore规则设置之前就存在的文件是不生效的。

[如果某些文件已经被纳入了版本管理中，则修改.gitignore是无效的]{.mark}。那么[解决方法就是先把本地缓存删除(改变成未track状态)，然后再提交]{.mark}：

git rm -r \--cached .

git add .

git commit -m \'update .gitignore\'

[在版本管理的根目录下(与[**.git**](http://lib.csdn.net/base/28 "Git知识库")文件夹同级)创建一个**.gitignore**(gitignore是隐藏文件，注意最前面有个点\"**.**\")。]{.mark}

应用实例(摘自互联网)

项目中有clist.h clist.c main.c三个文件，编译执行后，生成了三个文件
 clist.o  main.o
main(执行文件)。这三个文件是不需要进行版本管理的，所以需要忽略这些文件，使用
git stauts查看后，发现这三个文件也是处于 Untracked
files状态。而实际上我们是想忽略他。

![](media/image300.png){width="4.3805555555555555in" height="1.69375in"}

使用.gitignore文件来解决这个问题，步骤是：

   \$  vim  .gitignore     #编辑文件，加入指定文件           

         .gitignore   #忽略gitignore文件。一般不要忽略.gitignore文件

         \*.\[oa\]   #忽略后缀名为.o和.a的文件 

         main   #显示指定忽略名称为main的文件

**.gitignore的格式规范：**\
A：#为注释   \
B：可以使用shell所使用的正则表达式来进行模式匹配   \
C：匹配模式最后跟\"/\"说明要忽略的是目录 \
D：使用!取反(例如目录中包含test.a，并且.gitignore文件中包含\*.\[oa\]，如果在文件中加入!test.a，表明忽略除test.a文件以外的后缀名为.a或者.o的文件)
。

例子

\# 此为注释 \-- 将被 git忽略

\*.a        # 忽略所有 .a 结尾的文件

!lib.a     \# 但 lib.a 除外

/TODO     # 仅仅忽略项目根目录下的 TODO 文件，不包括 subdir/TODO

build/     # 忽略build/ 目录下的所有文件

doc/\*.txt  # 会忽略 doc/notes.txt 但不包括 doc/server/arch.txt

### .gitignore编写规则 {#gitignore编写规则 .标题紧3-8}

语法规范

- 空行不匹配任何文件，因此它可以作为可读性的分隔符。

- 以#开头的行用作注释

- 斜线/用作目录分隔符

- \* 匹配除斜杠以外的任何内容

- ? 匹配除/之外的任何一个字符

- \*\* 与完整路径名匹配的模式中的两个连续星号具有特殊含义

  - 前导 \*\* 后跟斜杠表示在所有目录中匹配

  - 尾随的 /\*\* 匹配里面的所有内容

  - 斜杠后跟两个连续的星号，然后斜杠匹配零个或多个目录

  - 其他连续的星号被视为常规星号，将根据之前的规则进行匹配

- ! 表示不忽略匹配到的文件或目录

关于路径指定/dir/ 就是当前的dir文件夹，不包含子文件夹，而dir/
不仅仅是当前的文件夹也包括子文件夹。

.gitignore文件示例

\# 忽略所有目录下文件名为a的任何文件

a.\*

\# 忽略所有目录下后缀为txt的文件

\*.txt

\# 不忽略所有目录下的c.txt文件

!c.txt

\# 忽略file目录下所有文件，包括其他目录下的file目录下的文件

\# 例如 a/file下面的文件会被忽略

file/

\# 只忽略当前file目录下所有文件，不包括其他目录下的file目录下的文件

\# 例如 a/file下面的文件不会被忽略

/file

\# 忽略任何位置file目录下的所有文件

file

\# 忽略任何位置file目录下的所有文件 同file

\*\*/file

\# 忽略任何直接位于c目录下的file目录下的所有文件

\*\*/c/file

\# 同file/

file/\*\*

\# 忽略a/file，a/c/file，a/c/d/file 目录下的所有文件

a/\*\*/file

当.gitignore配置发生冲突时，后面的配置会覆盖前面的配置

Github 上为开发者提供了各种环境以及各种编程语言的 gitignore
文件[配置模版](https://link.juejin.cn?target=https%3A%2F%2Fgithub.com%2Fgithub%2Fgitignore "https://github.com/github/gitignore")，可以根据自己的需求选用。

注意⚠️

.gitignore文件中的配置只能影响那些当前还未交由git来管理的文件。如果其中某个文件已经被现有的仓库包含了，那么他的修改依然会被git记录。我们可以通过下面的方法来解决这个问题。

git update-index \--assume-unchanged 文件名

// 恢复该文件的提交

git update-index \--no-assume-unchanged 文件名

#注释 .gitignore的注释

!src.a 忽略除 src.a 外的其他文件

/todo 仅忽略项目根目录下的 todo 文件，不包括 src/todo

build/ 忽略 build/目录下的所有文件，过滤整个build文件夹；

doc/\*.txt 忽略doc目录下所有 .txt 后缀的文件，但不包括doc子目录的 .txt
的文件

bin/: 忽略当前路径下的 bin
文件夹，该文件夹下的所有内容都会被忽略，不忽略 bin 文件

/\*.c: 忽略 cat.c，不忽略 build/cat.c

debug/\*.obj: 忽略debug/io.obj，不忽略
debug/common/io.obj和tools/debug/io.obj

\*\*/foo: 忽略/foo, a/foo, a/b/foo等

a/\*\*/b: 忽略a/b, a/x/b, a/x/y/b等

!/bin/run.sh 仅不忽略bin目录下的run.sh文件

\*.log: 忽略所有 .log 文件

config.js: 忽略当前路径的 config.js 文件

/mtk/
忽略整个文件夹。[linux的绝对路径根目录，还是.git同级的根目录？]{.mark}

/mtk/do.c 忽略某个具体文件

### \*不修改.gitignore的情况下忽略文件 {#不修改.gitignore的情况下忽略文件 .标题紧3-8}

总有些时候，本地跑出几个不想被 Git 追踪的文件(比如你个人的 IDE
配置文件，或者随便建的测试脚本)。但为了这几个特殊文件去动仓库[公共的 .gitignore]{.mark}，提交时还要小心翼翼地剔除。

对此，可以分两种情况处理。

**1. 忽略没被追踪过的新文件**

最直接的方法是修改 [.git/info/exclude]{.mark}。

它的语法和 .gitignore 完全一样，[区别是它藏在本地的 .git 目录里，不会被push到远程仓库( .gitignore会被push到远程仓库)]{.mark}。[把个人的私有忽略规则写在这里最安全]{.mark}。

**2. 忽略已经被追踪的文件**

这才是最头疼的场景。比如某个核心配置文件已经被提交到代码库了，但你本地调试时必须往里填自己的密码。你既不能提交它，又不能不改它。

用 update-index 命令：

\$ git update-index \--skip-worktree \<file\>

敲完这段命令，不管你怎么改文件，git status 看过去永远是干干净净的。

要是哪天真想把修改提交上去，再把状态改回来就好：

\$ git update-index \--no-skip-worktree \<file\>

**2.1. 一个需要注意的点**

这个方法很好用，但有一点：你在本地的修改其实还在磁盘上。所以当别人也修改了这个文件并推上远端，你只要一 git
pull 或者 git checkout，Git 就会立刻罢工并飘出一段报错：

error: Your local changes to the following files would be overwritten by
checkout:

README.md

Please commit your changes or stash them before you switch branches.

Aborting

Git 这么做只是怕强行覆盖会弄丢你本地的数据。

要处理这种冲突，逻辑就是"解除忽略 -\> 暂存 -\> 拉新代码 -\> 恢复代码 -\>
重新忽略"：

\$ git update-index \--no-skip-worktree README.md

\$ git stash

\$ git pull

\$ git stash pop

\$ git update-index \--skip-worktree README.md

来源：https://zhuanlan.zhihu.com/p/2023491412268777769

### .gitignore、.gitattributes、.gitkeep用法解析 {#gitignore.gitattributes.gitkeep用法解析 .标题紧3-8}

https://developer.aliyun.com/article/1134645

**简介：** .gitignore、.gitattributes、.gitkeep都是常见的Git相关文件，本文介绍它们到底该如何使用。

#### .gitignore

[ProGit](https://git-scm.com/docs/gitignore)对.gitignore有相应的描述。

.gitignore是一个需要写入内容的文件，用于指定要忽略的刻意untrack的文件。

需要注意的是，.gitignore不对已经track的文件起效。

.gitignore文件中的每一行都指定一个模式(pattern)。在决定是否忽略路径(path)时，Git通常会检查来自多个源的gitignore pattern，按照以下从高到低的优先顺序(在一个优先级内，最后匹配的pattern决定结果)：

- 从命令行读取支持它们的命令的pattern。

- 从与路径相同的目录或任何父目录(直到工作树的顶层)中的.gitignore文件中读取的pattern，较高级别文件中的pattern被较低级别文件中的pattern覆盖到包含文件的目录。这些pattern式与.gitignore文件的位置相匹配。项目通常在其存储库中包含此类.gitignore文件，其中包含作为项目构建的一部分生成的文件的pattern。

- 从\$GIT_DIR/info/exclude读取的pattern。\--[也可以在.git/info/exclude文件中添加忽略]{.mark}

- 从配置变量core.excludesFile指定的文件中读取的pattern。

放置pattern的文件取决于pattern的使用方式：

- 应该受版本控制并通过clone分发到其他存储库的pattern(即所有开发人员都希望忽略的文件)应该使用.gitignore文件。

- 特定于特定存储库但不需要与其他相关存储库共享的pattern(例如，存在于存储库中但特定于一个用户工作流的辅助文件)应该使用\$GIT_DIR/info/exclude文件。

- 用户希望Git在所有情况下忽略的pattern(例如，由用户选择的编辑器生成的备份或临时文件)通常使用用户\~/.gitconfig中由core.excludesFile指定的文件。它的默认值为\$XDG_CONFIG_HOME/git/ignore。如果\$XDG_CONFIG_HOME未设置或为空，则使用\$HOME/.config/git/ignore代替。

底层Git管道工具，例如git ls-files和git
read-tree，读取由命令行选项指定的gitignore pattern，或从命令行选项指定的文件中读取。\
而更高级别的Git工具，例如git status和git add，使用上述来源的pattern。

Pattern Format：

- 空行不匹配任何文件，因此它可以用作分隔符以提高可读性。

- 以#开头的行用作注释。对于以hash开头的pattern，在第一个hash前放置一个\\。

- 每行pattern的尾部空格将被忽略，除非它们用\\转义。

- 可选前缀!起到否定pattern排除的作用，任何被此前的pattern排除的匹配文件都将再次包含在内。

  - 出于性能考虑，Git不会列出排除的目录，因此如果已经排除!修饰文件的父目录，则无法重新包含该文件，包含文件的任何pattern都无效，无论它们是在哪里定义的。

  - 以!开头的pattern文本需要用\\转义。

- /用作目录分隔符，可能出现在pattern的任何位置。

  - 如果pattern的开头或(和)中间有/，则该pattern是相对于特定gitignore文件本身的目录级别的，否则pattern也可能在gitignore级别以下的任何级别匹配。

  - 如果pattern的末尾有/，则该pattern将仅匹配目录，否则该pattern可以匹配文件和目录。

- \*匹配除/以外的任何内容。

- ?匹配除/之外的任何一个字符。

- 范围符号，例如\[a-zA-Z\]，可用于匹配范围内的字符之一。

- 与完整路径名匹配的pattern中的\*\*具有特殊含义：

  - 前导\*\*后跟/表示在所有目录中都匹配。

  - 末尾\*\*匹配里面的所有内容，深度无限制。

  - /后跟\*\*，/匹配零个或多个目录。

  - 其他的连续\*组合被视为常规星号，将根据之前的规则进行匹配。

如果要停止跟踪当前track的文件，可以使用git rm \--cached。

访问工作树中的.gitignore文件时，Git不遵循符号链接。当从索引或树访问文件而不是从文件系统访问文件时，这可以保持行为一致。\
说明：符号链接，也称软链接，是一类特殊的文件，其包含有一条以绝对路径或者相对路径的形式指向其它文件或者目录的引用。

#### .gitattributes

[ProGit](https://git-scm.com/docs/gitattributes)对.gitattributes有相应的描述。

.gitattributes是一个需要写入内容的文件，用于定义每个路径的属性。

.gitattributes文件中的每一行格式为pattern attr1 attr2 \...：

- 一个模式后跟一个属性列表，用空格分隔。

- 前导和尾随空格将被忽略。

- 以#开头的行将被忽略，视作注释。

- 以双引号开头的pattern以C语言风格引用。

- 当pattern与所讨论的路径匹配时，该行中列出的属性将被赋予该路径。

对于给定路径，每个属性的状态可能是：

- Set：只列出属性列表中的属性名称，指定特定的属性值true。

- Unset：列出以属性列表中的属性名称，加上-前缀，指定特定的属性值false。

- Set to a
  value：列出以属性列表中的属性名称，加上=和属性值后缀，指定特定字符串的属性值。

- Unspecified：没有pattern匹配路径，并且没有说明路径是否具有属性。

当多个pattern与路径匹配时，后面的行会覆盖前面的行，此覆盖是按属性完成的。

pattern匹配路径的规则与.gitignore文件中的规则基本相同，不同点在于：

- 禁止否定型pattern。

- 与目录匹配的pattern不会递归匹配该目录内的路径。

属性分配给路径的优先级(从高到低)：

- \$GIT_DIR/info/attributes文件

- 与相关路径位于同一目录中的.gitattributes文件

- 相关路径的父目录中的.gitattributes文件(从文件所在目录开始直至工作树，包含.gitattributes的目录离相关路径越远，其优先级越低)

- 全局和系统范围的相关文件。

当工作树中缺少.gitattributes文件时，索引中的路径将用作后备。在checkout过程中，使用索引中的.gitattributes，然后将工作树中的文件用作后备。

属性配置的位置选择：

- 如果属性只影响单个存储库(即将属性分配给特定于该存储库的一个用户工作流的文件)，则应该设置\$GIT_DIR/info/attributes文件。

- 如果属性应该受版本控制并分发到其他存储库，则应该设置.gitattributes文件。

- 如果属性影响单个用户的所有存储库，应该设置由core.attributesFile配置选项指定的文件，与git
  config有关，默认值为\$XDG_CONFIG_HOME/git/attributes。如果\$XDG_CONFIG_HOME未设置或为空，则使用\$HOME/.config/git/attributes代替。系统上所有用户的属性都应该放在\$(prefix)/etc/gitattributes文件中。

!为前缀的属性名称可用于覆盖未指定状态路径的属性设置。

#### .gitkeep

ProGit没有专门对.gitkeep做出规定。

.gitkeep是一个空文件，用于充当一个空文件夹的占位符。Git不允许track或者commit一个空文件夹，想要提交并显示这样的空文件夹，保持这个项目的结构，就需要.gitkeep充当占位符。

实际上，.nofile或者其他的占位文件也可以起到同样的作用。之所以使用.gitkeep是一种规范，是因为这是一种普遍习惯下的约定俗成。

#### 文件生成

Windows系统生成以上文件可以借助文本编辑器，也可以记事本txt直接改名。

文本编辑器生成的方法非常简单，略。

Windows记事本txt改名的方法是创建默认的新建文本文档.txt，更名为.gitattributes.，即生成.gitattributes。

请注意更名为.gitattributes.而不是.gitattributes。

#### 案例分析

例如，存在如下的目录结构：

📁root

📁src

📁main

📁resources

🗄️application.yml

📁java

📁com

📁example

📁constant

📁controller

🗄️StudentManagementController.java

📁dao

🗄️StudentDAO.java

📁entity

🗄️Student.java

📁service

📁impl

🗄️StudentManagementImpl.java

🗄️StudentManagement.java

📁test (非空)

📁...... (省略)

🗄️...... (省略)

📁target (非空)

📁...... (省略)

🗄️...... (省略)

🗄️.gitattributes

🗄️.gitignore

🗄️pom.xml

🗄️README.md

.gitattributes配置为：

\*.\* linguist-language=python

.gitignore配置为：

.idea

.classpath

.project

.settings

.checkstyle

.DS_Store

\*.iml

target

\*\*/.flattened-pom.xml

根据以上设定：

- GitHub解析到的语言类型是Python(所有的文件都会被识别为Python文件，尽管这是完全不合理的，实际不要这样去操作)

- target文件夹及其包含的所有子文件夹和文件都会被忽略，不会被记录下来

- /root/src/main/java/com/example/constant目录不会被记录下来，想要记录下来需要在其中加一个.gitkeep的空文件

## 忽略文件权限修改

\$ git status

尚未暂存以备提交的变更：

（使用 \"git add \<文件\>\...\" 更新要提交的内容）

（使用 \"git restore \<文件\>\...\" 丢弃工作区的改动）

修改： package.json

修改： src/entrypoints/content/App.svelte

修改： src/lib/dir-listing.ts

修改： src/lib/render.ts

修改： src/panels/FolderPanel.svelte

修改： src/styles/content.css

修改： wxt.config.ts

修改尚未加入提交（使用 \"git add\" 和/或 \"git commit -a\"）

\$ git diff

diff \--git a/package.json b/package.json

old mode 100644

new mode 100755

diff \--git a/src/entrypoints/content/App.svelte
b/src/entrypoints/content/App.svelte

old mode 100644

new mode 100755

\...

\$ git diff \--summary

mode change 100644 =\> 100755 package.json

mode change 100644 =\> 100755 src/entrypoints/content/App.svelte

mode change 100644 =\> 100755 src/lib/dir-listing.ts

...

\$ git config core.fileMode false

\$ git status

警告：缓存未跟踪文件在本系统或位置中被禁用

位于分支 main

您的分支与上游分支 \'origin/main\' 一致。

无文件要提交，干净的工作区

\--cursor回答

可以通过 Git 配置忽略文件的可执行权限变化：

**仅当前仓库生效：**

git config core.fileMode false

**对所有仓库生效：**

git config \--global core.fileMode false

然后检查：

git diff \--summary

git status

不过你当前的 diff 已经显示为 100755，说明文件在 Git
索引中可能已经被记录成可执行文件。仅设置 core.fileMode=false 不一定会自动修正，需要先把索引中的权限恢复为普通文件：

git update-index \--chmod=-x wxt.config.ts

再检查：

git diff \--summary

正常情况下应恢复为：

old mode 100644

new mode 100644

如果该权限修改已经被暂存，可以先取消暂存再执行：

git restore \--staged wxt.config.ts

git update-index \--chmod=-x wxt.config.ts

通常建议在当前项目执行：

git config core.fileMode false

git update-index \--chmod=-x wxt.config.ts

这样只影响这个项目，不会改变其他仓库的 Git 行为。

## git环境变量

\$ git var GIT_EDITOR //git默认使用vi作为编辑器

vi

\$ git var GIT_PAGER //git默认使用less作为分页显示，git diff/git cmd
\--help超过一页时使用less来显示

less

\$ git var GIT_DEFAULT_BRANCH //默认分支名

master

\$ git var -l //查看全部环境变量

user.name=dukang

user.email=gaheadus@126.com

safe.directory=/cygdrive/e/sourcecode/github

safe.directory=/cygdrive/e/sourcecode/github/daily_use

safe.directory=/cygdrive/e/sourcecode/github/Wi-Fi_Study_Public

safe.directory=/cygdrive/e/sourcecode/gitsource/git

safe.directory=/cygdrive/e/sourcecode/marvell-android-4.4-pxa1908-dev/packages/apps/Phone

safe.directory=/cygdrive/e/sourcecode/marvell-android-4.4-pxa1908-dev/device/common

safe.directory=/cygdrive/e/sourcecode/lk

icdiff.options=\--highlight \--line-numbers -U 2

alias.co=checkout

alias.lg=log \--color \--graph \--pretty=format:\"%h, %C(#4169e1)%s,
%Creset%ae, %cd\" \--date=format:\"%x-%X\"

core.quotepath=off

core.repositoryformatversion=0

core.filemode=false

core.bare=false

core.logallrefupdates=true

core.ignorecase=true

remote.origin.url=git@github.com:gaheadus/daily_use.git

remote.origin.fetch=+refs/heads/\*:refs/remotes/origin/\*

branch.master.remote=origin

branch.master.merge=refs/heads/master

gitg.mainline=refs/heads/master

gui.wmstate=normal

gui.geometry=1920x1109+8+31 322 166

GIT_COMMITTER_IDENT=dukang \<gaheadus@126.com\> 1686669899 +0800

GIT_AUTHOR_IDENT=dukang \<gaheadus@126.com\> 1686669899 +0800

GIT_EDITOR=vi

GIT_PAGER=less

GIT_DEFAULT_BRANCH=master

\$ git config \--list //比git var
-l少了GIT_COMMITTER_IDENT、GIT_AUTHOR_IDENT等变量

user.name=dukang

user.email=gaheadus@126.com

safe.directory=/cygdrive/e/sourcecode/github

safe.directory=/cygdrive/e/sourcecode/github/daily_use

safe.directory=/cygdrive/e/sourcecode/github/Wi-Fi_Study_Public

safe.directory=/cygdrive/e/sourcecode/gitsource/git

safe.directory=/cygdrive/e/sourcecode/marvell-android-4.4-pxa1908-dev/packages/apps/Phone

safe.directory=/cygdrive/e/sourcecode/marvell-android-4.4-pxa1908-dev/device/common

safe.directory=/cygdrive/e/sourcecode/lk

icdiff.options=\--highlight \--line-numbers -U 2

alias.co=checkout

alias.lg=log \--color \--graph \--pretty=format:\"%h, %C(#4169e1)%s,
%Creset%ae, %cd\" \--date=format:\"%x-%X\"

core.quotepath=off

core.repositoryformatversion=0

core.filemode=false

core.bare=false

core.logallrefupdates=true

core.ignorecase=true

remote.origin.url=git@github.com:gaheadus/daily_use.git

remote.origin.fetch=+refs/heads/\*:refs/remotes/origin/\*

branch.master.remote=origin

branch.master.merge=refs/heads/master

gitg.mainline=refs/heads/master

gui.wmstate=normal

gui.geometry=1920x1109+8+31 322 166

\$ **git var \--help**

GIT-VAR(1) Git Manual GIT-VAR(1)

NAME

git-var - Show a Git logical variable

SYNOPSIS

git var (-l \| \<variable\>)

DESCRIPTION

Prints a Git logical variable.

OPTIONS

-l

Cause the logical variables to be listed. In addition, all the variables
of the Git configuration file .git/config are listed as well.

(However, the configuration variables listing functionality is
deprecated in favor of git config -l.)

EXAMPLES

\$ git var GIT_AUTHOR_IDENT

Eric W. Biederman \<ebiederm@lnxi.com\> 1121223278 -0600

VARIABLES

GIT_AUTHOR_IDENT

The author of a piece of code.

GIT_COMMITTER_IDENT

The person who put a piece of code into Git.

GIT_EDITOR

Text editor for use by Git commands. The value is meant to be
interpreted by the shell when it is used. Examples: \~/bin/vi,

\$SOME_ENVIRONMENT_VARIABLE, \"C:\\Program Files\\Vim\\gvim.exe\"
\--nofork. The order of preference is the \$GIT_EDITOR environment
variable,

then core.editor configuration, then \$VISUAL, then \$EDITOR, and then
the default chosen at compile time, which is usually vi.

GIT_PAGER

Text viewer for use by Git commands (e.g., less). The value is meant to
be interpreted by the shell. The order of preference is the

\$GIT_PAGER environment variable, then core.pager configuration, then
\$PAGER, and then the default chosen at compile time (usually less).

GIT_DEFAULT_BRANCH

The name of the first branch created in newly initialized repositories.

SEE ALSO

git-commit-tree(1) git-tag(1) git-config(1)

GIT

Part of the git(1) suite

Git 2.39.0 12/12/2022 GIT-VAR(1)

## git gc，清理git仓库

### git gc介绍 {#git-gc介绍 .标题紧3-8}

git gc，清理不必要的文件并优化本地存储库。

**[git gc \[\--aggressive\] \[\--auto\] \[\--quiet\] \[\--prune=\<date\>
\| \--no-prune\] \[\--force\]]{.mark}**

在当前存储库中运行许多内务处理任务，例如压缩文件修订(以减少磁盘空间并提高性能)并移除可能由之前git
add调用创建的不可达对象。

鼓励用户在每个存储库中定期运行此任务，以保持良好的磁盘空间利用率和良好的操作性能。

一些git命令可能会自动运行git gc;
\--auto详细信息请参阅下面的标志。如果您知道自己在做什么，并且所有您想要的都是永久禁用此行为而无需进一步考虑，请执行以下操作：

\$ git config \--global gc.auto 0

选项

\--aggressive

通常git gc运行速度很快，同时提供良好的磁盘空间利用率和性能
此选项将导致git
gc更积极地优化存储库，但花费更多时间。这种优化的效果是持久的，所以这个选项只需要偶尔使用;
每隔几百个变更集左右。

\--auto

使用此选项，git gc检查是否需要进行任何清洁工作;
如果没有，它会退出而不执行任何工作。一些git命令git gc
\--auto在执行可能会产生许多松散对象的操作之后运行。

如果存储库中的松散对象太多或包装太多，则需要进行内务处理。如果松散对象的数量超过了gc.auto配置变量的值，则所有松散对象都将使用组合到一个包中git
repack -d -l。将值设置gc.auto为0将禁用自动填充松散物体。

如果包装数量超过了价值gc.autoPackLimit，那么现有包装(标有.keep文件的包装除外)将通过使用-A选项合并到一个包装中git
repack。设置gc.autoPackLimit为0将禁用自动合并包装。

\--prune=\<date\>

修剪比日期更旧的松散对象(默认为2周前，可由配置变量覆盖gc.pruneExpire)。\--prune
=不管年龄大小，都修剪松散的物体，并且如果另一个进程同时写入存储库，则会增加腐败风险;
请参阅下面的"注意事项"。\--prune默认打开。

\--no-prune

不要修剪任何松动的物体。

\--quiet

取消所有进度报告。

\--force

git gc即使可能有另一个git gc实例在此存储库上运行，也强制运行。

**组态**

可选配置变量gc.reflogExpire可以设置为指示每个分支的reflog中的历史条目应该在此存储库中保持可用的时间。该设置表示为一段时间，例如90
days或3 months。它默认为90 days。

可选配置变量gc.reflogExpireUnreachable可设置为指示不属于当前分支的历史请求日志条目在此存储库中保持可用的时间。这些类型的条目通常是由于使用git
commit \--amend或git
rebase而创建的，并且是在修改或重新发生之前的提交。由于这些更改不是当前项目的一部分，因此大多数用户都希望尽快过期。该选项默认为30
days。

上述两个配置变量可以赋予一个模式。例如，这会将非默认到期值设置为远程跟踪分支：

\[gc \"refs/remotes/\*\"\]

reflogExpire = never

reflogExpireUnreachable = 3 days

可选的配置变量gc.rerereResolved指示您先前解决的冲突合并记录的保存期限。这默认为60天。

可选的配置变量gc.rerereUnresolved表示保留了多久没有解决的冲突合并记录。这默认为15天。

可选的配置变量gc.packRefs确定是否git gc运行git
pack-refs。可以将其设置为"notbare"，以便在所有非裸回购库中启用它，或者可以将其设置为布尔值。这默认为true。

可选配置变量gc.aggressiveWindow控制在指定\--aggressive选项时优化存储库中对象的增量压缩所花费的时间。值越大，优化增量压缩花费的时间就越多。有关更多详细信息，请参阅git-repack
\[1\]中\--window\'选项的文档。这默认为250。

同样，可选的配置变量gc.aggressiveDepth控制git-repack
\[1\]中的\--depth选项。默认值为50。

可选的配置变量gc.pruneExpire控制未修剪的松散对象在修剪之前必须经过多久。默认值是"2周前"。

**注意**

git
gc尽量不要删除在存储库中任何位置引用的对象。特别是，它不仅会保存当前一组分支和标记所引用的对象，还会保留由索引引用的对象，远程跟踪分支，git
filter-branchrefs / original
/中保存的引用或reflogs(可引用分支中的提交后来修改或倒带)。如果您希望某些对象被删除而不是，请检查所有这些位置，并决定在您的情况下删除这些引用是否有意义。

另一方面，当git
gc与另一个进程同时运行时，可能会删除另一个进程正在使用但尚未创建引用的对象。这可能会导致其他进程失败或者可能会损坏存储库，如果其他进程稍后添加对已删除对象的引用。Git有两个功能可以显着缓解这个问题：

\--prune保留修改时间比日期更新的任何对象以及可从其访问的所有对象。

将对象添加到数据库的大多数操作都会更新对象的修改时间(如果该对象已存在，以便应用＃1)。

然而，这些功能并不能提供完整的解决方案，因此，同时运行命令的用户必须忍受一些腐败风险(实践中似乎很低)，除非他们关闭自动垃圾收集git
config gc.auto 0。

**Hooks**

该git gc
\--auto命令将运行该pre-auto-gc钩子。有关更多信息，请参阅githooks。

### git gc分析 {#git-gc分析 .标题紧3-8}

在执行git gc之前我们看一下.git目录的一些信息：\
refs目录下边有三个文件夹：\
![这里写图片描述](media/image301.png){width="4.1618055555555555in"
height="2.5083333333333333in"}\
此三个文件夹下边都存在一些本地、远程分支的信息，以及标签的 信息。

执行git gc：\
执行完毕之后，heads、remotes、tags下边的内容消失，git并不是删除了这些信息，而是存放在
.git/packed-refs文件里边，即进行了压缩。\
![这里写图片描述](media/image302.png){width="4.246527777777778in"
height="2.5590277777777777in"}\
通过里边的内容我们还可以验证带有注释标签的一些信息，v1.0只有一个id指向的就是一个commitid，而带有注释的v2.0有两个id第一id是其本身，第二个是指向的commitid，可以看到id前边有个"\^"符号。

此时我们如果在进行一次提交和推送，那么又会在.git/refs/下边出现新的内容记录git的信息：\
![这里写图片描述](media/image303.png){width="4.370833333333334in"
height="3.83125in"}\
如图我们对test.txt进行了提交，在.git/refs/heads和.git/refs/remotes下边出现了新的内容，而不是放在.git/packed-refs文件里边。

此外git
gc还会对每次提交的文件进行压缩，我们知道git和svn的区别就是git是全量记录文件的提交，而svn是记录变化量，既然git
记录的是全量的文件，那是不是会很大，占用空间，并且是怎么存放的呢？\
其实所有的提交文件记录都在.git/objects/里边：\
![这里写图片描述](media/image304.png){width="7.4631944444444445in"
height="3.765972222222222in"}\
执行git gc之后文件都会=消失，转而放在pack目录下：

\$ git gc

Counting objects: 18, done.

Delta compression using up to 8 threads.

Compressing objects: 100% (10/10), done.

Writing objects: 100% (18/18), done.

Total 18 (delta 4), reused 15 (delta 4)

Administrator@CeaserWang MINGW64 /e/Study/mygit (master)

\$ ls .git/objects/

info/ pack/

Administrator@CeaserWang MINGW64 /e/Study/mygit (master)

\$ ls .git/objects/pack/

pack-94d0a6b4da258363c6f774e525a8615469b64e03.idx
pack-94d0a6b4da258363c6f774e525a8615469b64e03.pack

### git prune {#git-prune .标题紧3-8}

git-prune，从对象数据库中删除所有不可访问的对象

**[git prune \[-n\] \[-v\] \[\--expire \<expire\>\] \[\--\]
\[\<head\>...​\]]{.mark}**

注意 在大多数情况下，用户应该运行 git gc，它调用 git
prune。请参阅下面的"注意"部分。

这将git fsck
\--unreachable使用所有可用的引用refs/，可选地包含在命令行中指定的其他对象集合，并修剪来自对象数据库的任何这些头对象不可访问的所有解压缩对象。另外，它通过运行修剪也在包中找到的未打包对象git
prune-packed。它还从 .git / shallow 中删除任何 ref 无法访问的条目。

请注意，无法访问，打包的对象将保留。如果不需要，请参阅 git-repack
\[1\]。

选项

-n \--dry-run

不要删除任何东西; 只是报告它会删除什么。

-v \--verbose

报告所有移除的对象。

不要将更多的参数解释为选项。

\--expire \<time\>

只会过期比\<time\>更旧的松散对象。

\<head\>...​

除了我们任何引用可访问的对象之外，还可以从列出的\<head\>中保持对象可访问。

示例

要修剪未由您的存储库使用的对象或从您的存储库借用以下内容的对象.git/objects/info/alternates：

\$ git prune \$(cd ../another && git rev-parse \--all)

注意

在大多数情况下，用户不需要git prune直接调用，而是应该调用git
gc，它可以处理修剪以及许多其他内务处理任务。

有关修剪考虑哪些对象的描述，请参阅git fsck\'s \--unreachable 选项。

也可以看看

git-fsck, git-gc, git-reflog

## windows使用git

windows系统使用git时注意，**不要在office打开word文档的情况下进行reset或rebase**，[office打开word时会锁住文档，不允许其他程序修改，此时git
reset或rebase造成不可知后果]{.mark}。

[sourceinsight打开文件不会锁住文件，其他程序仍然可以修改，此时可以reset或rebase]{.mark}。

# 19)问题与解决

## 已提交到gerrit的代码冲突

A本地代码修改，并且已经提交到gerrit，还没有合并到远程仓库。B也修改了代码并提交到gerrit，并且代码先合并。此时，A已提交到gerrit、还没有合并的代码冲突。A怎么解决gerrit上的冲突呢？

正常情况下，提交代码之前先repo
sync同步最新代码到本地，没有冲突再提交到gerrit。

但是，由于A的代码已经提交到gerrit，此时不能使用repo
sync下载最新代码，也就不能使用repo
sync最新代码、本地解决冲突、再提交的方式。怎么办？

方法1：在当前分支执行git
fetch，获取远程仓库代码到本地远程分支，然后执行git rebase
当前分支到本地远程分支，解决冲突，再执行git push。 //使用git branch
-vv查看本地分支和远程分支之间的对应关系。

方法2：本地新建一个分支temp、并repo
sync，然后切换回原来提交gerrit所在分支，rebase到新分支temp上，然后再git
push。删除不再使用的temp分支。比方法1多了一些步骤，这么用也是因为没有理解git的工作原理。

方法3:使用相同的change-id提交。参考：总结,gerrit.docx -\>
git修改前一次提交的方法(注意保持Change-Id不变)。

## 1.git pull / push Connection refused {#git-pull-push-connection-refused .标题紧2-9}

### 问题现象 {#问题现象 .标题紧3-8}

\$ git pull

fatal: unable to access
\'https://github.com/gaheadus/daily_use.git/\'：Failed to connect to
127.0.0.1 port 1080: Connection refused

造成的原因：国内git访问很卡，网上搜索到一个方法设置了代理：git config
https.proxy http://127.0.0.1:1080，之后便出现了上述Connection
refused的问题。

### 网上方法：失败 {#网上方法失败 .标题紧3-8}

<https://blog.csdn.net/weixin_41010198/article/details/87929622>

解决git下载出现：Failed to connect to 127.0.0.1 port 1080: Connection
refused拒绝连接错误

一、git拒绝连接原因分析

使用git从远程仓库下载代码出现上述的错误是因为使用了proxy代理，所以要解决该问题，核心操作就是要取消代理

二、错误解决方式

1、查看Linux当前有没有使用代理

方式一：通过git的配置文件查看有无使用代理(没有成功)

查询是否使用代理：git config \--global http.proxy

注：
我在使用该方法并没有返回任何信息，也没有返回代理使用，当然啦，你可以尝试，毕竟好多人都是用这种方法查看的。还有，你可以试试git
config \--global \--unset https.proxy 在http协议后面加s试一下

方式二：通过查询系统环境有没有使用代理(成功)

env\|grep -I proxy

我是用这个命令查询出有在使用代理的，返回信息如下：\
![在这里插入图片描述](media/image305.png){width="2.432638888888889in"
height="1.1270833333333334in"}\
从上面可以看出，有很多协议占用了这个端口，有http、ftp、all、socks、https、no

取消代理设置

方式一：通过git取消代理设置

\$ git config \--global \--unset http.proxy

\$ git config \--global \--unset https.proxy

我尝试了该方法，并没有取消代理，代理依然存在，当然啦，你可以尝试一下

方式二：

export http_proxy=\"\"

export https_proxy=\"\"

export HTTP_PROXY=\"\"

export HTTPS_PROXY=\"\"

我尝试了该方法，并没有取消代理，代理依然存在，当然啦，你可以尝试一下

方式三：通过系统命令取消代理

\$ unset http_proxy

\$ unset ftp_proxy

\$ unset all_proxy

\$ unset https_proxy

\$ unset no_proxy

把上面出现的所有使用代理的协议，全部都取消掉，然后问题成功解决。

[\-\-\-- 按照上述方法反复示例几次，都失败了，没能解决问题。20210424 by
dukang]{.mark}

### 1.最终解决：成功 {#最终解决成功 .标题紧3-8}

尝试了多种方法取消代理，都失败了：采用网上方法，没有解决问题；**查看****\~/.git
config文件并没有关于代理的内容**；查看windows系统代理设置，并没有问题；删除cygwin重装也没有解决问题。

偶然想到，不如重新从github clone代码试试，尝试github clone
git@github.com:gaheadus/daily_use.git是成功的，这**说明系统环境变量、代理都是没问题的**。那么，很有可能是**代码目录下保存了有关代理的配置**导致的出错。

**每一个git库都有一个.git目录保存相关配置，是不是这个目录下保存了代理配置？
\--
于是，进入代码目录下的git库目录/cygdrive/f/sourcecode/github/daily_use/.git，其中有个config文件，打开一看，确实有两行是设置代理的：**

\[http\]

proxy = 127.0.0.1:1080

**git
pull/push报错的正是这里的代理配置。于是，删除这两行，再回到代码目录/cygdrive/f/sourcecode/github/daily_use/执行git
pull / push，成功了，问题解决。**20210424 by dukang

**\$ cd** **/cygdrive/f/sourcecode/github/daily_use/.git**

**\$ ls**

COMMIT_EDITMSG **config** description FETCH_HEAD HEAD hooks index info
logs objects ORIG_HEAD

refs

**\$ vim config**

\[core\]

repositoryformatversion = 0

filemode = false

bare = false

logallrefupdates = true

symlinks = false

ignorecase = true

\[remote \"origin\"\]

url = https://github.com/gaheadus/daily_use.git

fetch = +refs/heads/\*:refs/remotes/origin/\*

\[branch \"master\"\]

remote = origin

merge = refs/heads/master

**\[http\] \-- 删除这两行，问题解决**

**proxy = 127.0.0.1:1080 \-- 删除这两行，问题解决**

### 1.拓展：git代理设置 {#拓展git代理设置 .标题紧3-8}

网上搜索到设置git代理的方法

git config \--global https.proxy http://127.0.0.1:1080

git config \--global https.proxy https://127.0.0.1:1080

git config \--global \--unset http.proxy \--
**无效**命令，验证这里的unset并**不能**取消之前设置的代理

git config \--global \--unset https.proxy
\--**无效**命令。**不推荐使用**这些命令。20210424 by dukang

拓展：做了个试验，发现**git
config加\--global选项、不加\--global选项，配置的值写入了不同的文件**。

**加\--global选项选项，参数值写入了\~/.git
config文件，不加\--global选项，参数值写入了代码目录下git库目录下的config文件。**

\$ git config \--global https.proxy http://127.0.0.1:1080

\$ vim \~/.git config

\[user\]

email = gaheadus@126.com

name = dukang

\[https\]

proxy = http://127.0.0.1:1080

\$ git config https.proxy http://127.0.0.1:1080

\$ vi .git/config

\[core\]

repositoryformatversion = 0

filemode = false

bare = false

logallrefupdates = true

symlinks = false

ignorecase = true

\[remote \"origin\"\]

url = https://github.com/gaheadus/daily_use.git

fetch = +refs/heads/\*:refs/remotes/origin/\*

\[branch \"master\"\]

remote = origin

merge = refs/heads/master

\[https\]

proxy = http://127.0.0.1:1080

### 没做任何修改，却push失败 {#没做任何修改却push失败 .标题紧3-8}

\$ git push

git@192.168.248.128\'s password:

To 192.168.248.128:/home/tenda/backup/daily_use/cmds

! \[rejected\] master -\> master (non-fast-forward)

error: 推送一些引用到
\'192.168.248.128:/home/tenda/backup/daily_use/cmds\' 失败

提示：更新被拒绝，因为您当前分支的最新提交落后于其对应的远程分支。

提示：再次推送前，先与远程变更合并(如 \'git pull \...\')。详见

提示：\'git push \--help\' 中的 \'Note about fast-forwards\' 小节。

\$ git pull

git@192.168.248.128\'s password:

提示：不建议在没有为偏离分支指定合并策略时执行 pull 操作。
您可以在执行下一次

提示：pull 操作之前执行下面一条命令来抑制本消息：

提示：

提示： git config pull.rebase false \# 合并(缺省策略)

提示： git config pull.rebase true \# 变基

提示： git config pull.ff only \# 仅快进

提示：

提示：您可以将 \"git config\" 替换为 \"git config \--global\"
以便为所有仓库设置

提示：缺省的配置项。您也可以在每次执行 pull 命令时添加
\--rebase、\--no-rebase，

提示：或者 \--ff-only 参数覆盖缺省设置。

自动合并 cmd_mesh.txt

冲突(内容)：合并冲突于 cmd_mesh.txt

自动合并失败，修正冲突然后提交修正的结果。

解决

\$ git push -f

## SSL certificate problem {#ssl-certificate-problem .标题紧2-9}

clone、pull或push等证书异常，

fatal: unable to access \'https:/github.com\'xxx.git\'

SSL certificate problem: unable to get local issuer certificate

解决办法：git config \--global http.sslverify false

## git status/git log中文乱码 {#git-statusgit-log中文乱码 .标题紧2-9}

git status中文路径显示一堆数字的问题

![在这里插入图片描述](media/image306.png){width="4.668055555555555in"
height="0.98125in"}

[解决：git config \--global core.quotepath false或git config \--global
core.quotepath off]{.mark}

![在这里插入图片描述](media/image307.png){width="4.539583333333334in"
height="0.7041666666666667in"}

如何设置让git log显示提交记录的comment正常显示中文，但是git switch/git
rebase/git merge等命令本身的结果显示为英文而不是中文？

\--腾讯元宝AI回答

要让Git在不同场景下使用不同语言，核心是**将 Git
的界面语言设置为英文**，同时确保**编码配置支持中文显示**。这样，git
log中的**提交信息(commit comment)能正常显示中文**，而 git
switch/status/rebase/merge等命令的**系统提示和输出结果将保持英文**。

请按以下步骤操作：

**解决方案**

**1. 将 Git 的界面语言设置为英文**

这是最关键的一步，它决定了命令输出的语言。

- **Windows (Git Bash / CMD / PowerShell)**:

在系统环境变量中，添加一个新的环境变量：

- **变量名**: LANG

- **变量值**: en_US.UTF-8

或者，直接在终端会话中执行(但只对当前窗口有效)：

set LANG=en_US.UTF-8

- **Linux / macOS**:

在终端配置文件(如 \~/.bashrc, \~/.zshrc)中添加：

export LANG=en_US.UTF-8

\# 或者，更具体地设置给 Git

\# export GIT_INTERNAL_GETTEXT_TEST_FALLBACKS=1

然后执行 source \~/.bashrc使配置生效。

**2. 配置 Git 以正确显示和输入中文**

即使界面是英文，也需要确保 Git 不会"转义"中文字符，导致 git
log显示乱码。

执行以下 Git 全局命令：

\# 关闭路径转义，使中文路径和文件名正常显示

git config \--global core.quotepath off

\# 设置提交信息输入和日志输出的编码为 UTF-8

git config \--global i18n.commitEncoding utf-8

git config \--global i18n.logOutputEncoding utf-8

\# 对于 Windows 用户，还需要设置控制台编码(如果使用 Git
Bash，通常已设置)

\# git config \--global core.unicode auto

**原理说明**

- **LANG=en_US.UTF-8**： 这个环境变量告诉
  Git(以及其他命令行工具)使用美式英语(en_US)作为界面语言，并使用
  UTF-8编码。UTF-8
  完美支持中文，因此提交信息里的中文可以正常存储和显示。

- **core.quotepath off**： 默认情况下，Git 会将非 ASCII
  字符(如中文)转义，这个设置会关闭该行为。

- **i18n.logOutputEncoding utf-8**： 明确指定 git log输出日志时使用
  UTF-8 编码，确保中文提交信息正确渲染。

**验证结果**

完成设置后：

- 执行 git log，你看到的**提交历史中的中文信息**将是正常的中文字符。

- 执行 git status, git switch -c new-branch, git merge main等操作时，Git
  返回的提示信息(如 Switched to a new branch \'new-branch\', Already up
  to date.)都将是**英文**。

这样就实现了你想要的效果：**内容(提交信息)是中文，界面(命令反馈)是英文**。

## git diff中文乱码 {#git-diff中文乱码 .标题紧2-9}

### git diff中文乱码 {#git-diff中文乱码-1 .标题紧3-8}

在命令行查看git的diff，碰到GBK编码的文件时，中文显示会是乱码。

[原因：**git diff的输出使用less**，而less不支持gbk编码。]{.mark}

[在我的cygwin中，less默认支持中文，git
diff也支持中文。但在另外一台笔记本cygwin less/git
diff不支持中文，不知道哪里配置有问题。]{.mark}

less/git diff支持中文电脑中cygwin的locale参数如下：

\$ locale

LANG=zh_CN.UTF-8

LC_CTYPE=\"zh_CN.UTF-8\"

LC_NUMERIC=\"zh_CN.UTF-8\"

LC_TIME=\"zh_CN.UTF-8\"

LC_COLLATE=\"zh_CN.UTF-8\"

LC_MONETARY=\"zh_CN.UTF-8\"

LC_MESSAGES=\"zh_CN.UTF-8\"

LC_ALL=

按照网上的说法修改LANG=zh_CN.UTF-8、LESSCHARSET=utf-8、LESS=-isMrf都不生效。

只能退而求其次，将git diff输出到一个支持gbk的编辑器中，如git diff \| vim
-R -，或git difftool \--no-prompt \--extcmd \"vimdiff -n\"。

git var GIT_PAGER查看到**[git默认使用less控制分页显示]{.mark}**，git
diff/git cmd \--help等超过一页时使用less来控制分页显示。

或者将GIT_PAGER改成more试试？GIT_PAGER=more git diff \-- 待测试

不分页显示

还是不行，那就设置为不分页显示，不使用less，那就不会乱码了。

**[git \--no-pager log]{.mark}**

**[git \--no-pager diff]{.mark}**或者[GIT_PAGER= git diff]{.mark}

不分页显示，一次性将log全部打印到屏幕上，可以使用鼠标滚轮回过去查看(如果修改不是特别多的话，这样也可以)。

注意\--no-pager只能放在git后面，不能放在log/diff后面(报错)。

另外一个解决办法，使用vimdiff作为比较工具：

[\$ git difftool \--no-prompt \--extcmd=\"vimdiff -n\"]{.mark}

见：8)常用命令 -\> git diff -\> 指定diff比较工具, icdiff, vimdiff,
beyondcompare

### 附：less中文显示 {#附less中文显示 .标题紧3-8}

**man less关于charset的介绍**

**NATIONAL CHARACTER SETS**

There are three types of characters in the input file:

normal characters

can be displayed directly to the screen.

control characters

should not be displayed directly, but are expected to be found in
ordinary text files (such as backspace and tab).

binary characters

should not be displayed directly and are not expected to be found in
text files.

A \"character set\" is simply a description of which characters are to
be considered normal, control, and binary. The LESSCHARSET environment
variable may be used to select a character set. Possible values for
LESSCHARSET are:

ascii BS, TAB, NL, CR, and formfeed are control characters, all chars
with values between 32 and 126 are normal, and all others are binary.

iso8859

Selects an ISO 8859 character set. This is the same as ASCII, except
characters between 160 and 255 are treated as normal characters.

latin1 Same as iso8859.

latin9 Same as iso8859.

dos Selects a character set appropriate for MS-DOS.

ebcdic Selects an EBCDIC character set.

IBM-1047

Selects an EBCDIC character set used by OS/390 Unix Services. This is
the EBCDIC analogue of latin1. You get similar results by setting either
LESSCHARSET=IBM-1047 or LC_CTYPE=en_US in your environment.

koi8-r Selects a Russian character set.

next Selects a character set appropriate for NeXT computers.

utf-8 Selects the UTF-8 encoding of the ISO 10646 character set. UTF-8
is special in that it supports multi-byte characters in the input file.
[It is the only character set that supports multi-byte
characters.]{.mark}

windows

Selects a character set appropriate for Microsoft Windows (cp 1251).

In rare cases, it may be desired to tailor less to use a character set
other than the ones definable by LESSCHARSET. In this case, the
environment variable LESSCHARDEF can be used to define a character set.
It should be set to a string where each charac‐

ter in the string represents one character in the character set. The
character \".\" is used for a normal character, \"c\" for control, and
\"b\" for binary. A decimal number may be used for repetition. For
example, \"bccc4b.\" would mean character 0 is binary,

1, 2 and 3 are control, 4, 5, 6 and 7 are binary, and 8 is normal. All
characters after the last are taken to be the same as the last, so
characters 9 through 255 would be normal. (This is an example, and does
not necessarily represent any real character

set.)

This table shows the value of LESSCHARDEF which is equivalent to each of
the possible values for LESSCHARSET:

ascii 8bcccbcc18b95.b

dos 8bcccbcc12bc5b95.b.

ebcdic 5bc6bcc7bcc41b.9b7.9b5.b..8b6.10b6.b9.7b

9.8b8.17b3.3b9.7b9.8b8.6b10.b.b.b.

IBM-1047 4cbcbc3b9cbccbccbb4c6bcc5b3cbbc4bc4bccbc

191.b

iso8859 8bcccbcc18b95.33b.

koi8-r 8bcccbcc18b95.b128.

latin1 8bcccbcc18b95.33b.

next 8bcccbcc18b95.bb125.bb

[If neither LESSCHARSET nor LESSCHARDEF is set, but any of the strings
\"UTF-8\", \"UTF8\", \"utf-8\" or \"utf8\" is found in the LC_ALL,
LC_CTYPE or LANG environment variables, then the default character set
is utf-8. \--
如果不设置LESSCHARSET和LESSCHARDEF，那么less跟随系统环境变量LC_ALL、LC_CTYPE或LANG。]{.mark}

If that string is not found, but your system supports the setlocale
interface, less will use setlocale to determine the character set.
setlocale is controlled by setting the LANG or LC_CTYPE environment
variables.

Finally, if the setlocale interface is also not available, the default
character set is latin1.

Control and binary characters are displayed in standout (reverse video).
Each such character is displayed in caret notation if possible (e.g. \^A
for control-A). Caret notation is used only if inverting the 0100 bit
results in a normal printable character.

Otherwise, the character is displayed as a hex number in angle brackets.
This format can be changed by setting the LESSBINFMT environment
variable. LESSBINFMT may begin with a \"\*\" and one character to select
the display attribute: \"\*k\" is blinking, \"\*d\"

is bold, \"\*u\" is underlined, \"\*s\" is standout, and \"\*n\" is
normal. If LESSBINFMT does not begin with a \"\*\", normal attribute is
assumed. The remainder of LESSBINFMT is a string which may include one
printf-style escape sequence (a % followed by x, X, o,

d, etc.). For example, if LESSBINFMT is \"\*u\[%x\]\", binary characters
are displayed in underlined hexadecimal surrounded by brackets. The
default if no LESSBINFMT is specified is \"\*s\<%02X\>\". Warning: the
result of expanding the character via LESSBINFMT must be less than 31
characters.

When the character set is utf-8, the LESSUTFBINFMT environment variable
acts similarly to LESSBINFMT but it applies to Unicode code points that
were successfully decoded but are unsuitable for display (e.g.,
unassigned code points). Its default value is

\"\<U+%04lX\>\". Note that LESSUTFBINFMT and LESSBINFMT share their
display attribute setting (\"\*x\") so specifying one will affect both;
LESSUTFBINFMT is read after LESSBINFMT so its setting, if any, will have
priority. Problematic octets in a UTF-8 file

(octets of a truncated sequence, octets of a complete but non-shortest
form sequence, invalid octets, and stray trailing octets) are displayed
individually using LESSBINFMT so as to facilitate diagnostic of how the
UTF-8 file is ill-formed.

### 附：vi中文乱码 {#附vi中文乱码 .标题紧3-8}

见：vi详解,总结.docx -\> 专题 -\> vi/vim中文乱码

## ssno matching key exchange method found {#ssno-matching-key-exchange-method-found .标题紧2-9}

[git](https://so.csdn.net/so/search?q=git&spm=1001.2101.3001.7020) pull\
Unable to negotiate with 10.6.127.6 port 29418: no matching key exchange
method found. Their offer:
diffie-hellman-group14-sha1,diffie-hellman-group1-sha1\
fatal: Could not read from remote repository.

这是因为ssh版本不同，加密方式不同。

SSH有几种不同类型的密钥：RSA密钥 (ssh-rsa)
可以支持多种签名。签名类型sssh-rsa是指带有SHA-1的RSA，而签名类型rsa-sha2-256是带有SHA-256的RSA，rsa-sha2-512是带有SHA-512的RSA。

上面报错中提示，git服务端中使用的密钥是ssh-rsa类型的，而我本机的ssh(OpenSSH_for_Windows_8.6p1,
LibreSSL 3.4.3)默认不支持这种算法，需要指定下算法。

解决方案:

进入\~/.ssh目录，打开config文件(没有的话新建一个)，添加如下配置：\
Host \*\
    KexAlgorithms +diffie-hellman-group1-sha1\
    HostkeyAlgorithms +ssh-dss,ssh-rsa\
    PubkeyAcceptedKeyTypes +ssh-dss,ssh-rsa\
    Ciphers +aes128-cbc

# 20)未解决问题

### git init问题 {#git-init问题 .标题紧3-8}

一般方法是先建立一个空目录，git init，再一步一步的往里面加东西。

但是如果不是从空目录开始git init，而是从一个已经存在的多级目录开始git
init，如果在顶层目录git
init，会造成无法跟踪子目录的情况。是个bug吗？这种情况下只能从最底层目录开始git
init，而且是从底往上一层目录一层目录地进行git init。

### git clone问题 {#git-clone问题 .标题紧3-8}

①Permission denied (publickey)

\$ git clone URL

正克隆到 \'UGW_main\'\...

dukang@172.16.30.72: Permission denied (publickey).

fatal: 无法读取远程仓库。

请确认您有正确的访问权限并且仓库存在。

②使用ssh命令跟踪

\$ ssh -v dukang@172.16.30.72

OpenSSH_8.9p1, OpenSSL 1.1.1n 15 Mar 2022

debug1: Connecting to 172.16.30.72 \[172.16.30.72\] port 22.

debug1: Connection established.

debug1: identity file /home/tengda/.ssh/id_rsa type 0

debug1: identity file /home/tengda/.ssh/id_rsa-cert type -1

debug1: identity file /home/tengda/.ssh/id_ecdsa type -1

debug1: identity file /home/tengda/.ssh/id_ecdsa-cert type -1

debug1: identity file /home/tengda/.ssh/id_ecdsa_sk type -1

debug1: identity file /home/tengda/.ssh/id_ecdsa_sk-cert type -1

debug1: identity file /home/tengda/.ssh/id_ed25519 type -1

debug1: identity file /home/tengda/.ssh/id_ed25519-cert type -1

debug1: identity file /home/tengda/.ssh/id_ed25519_sk type -1

debug1: identity file /home/tengda/.ssh/id_ed25519_sk-cert type -1

debug1: identity file /home/tengda/.ssh/id_xmss type -1

debug1: identity file /home/tengda/.ssh/id_xmss-cert type -1

debug1: identity file /home/tengda/.ssh/id_dsa type 1

debug1: identity file /home/tengda/.ssh/id_dsa-cert type -1

debug1: Local version string SSH-2.0-OpenSSH_8.9

debug1: Remote protocol version 2.0, remote software version
OpenSSH_6.6.1p1 Ubuntu-2ubuntu2.13

debug1: compat_banner: match: OpenSSH_6.6.1p1 Ubuntu-2ubuntu2.13 pat
OpenSSH_6.6.1\* compat 0x04000002

debug1: Authenticating to 172.16.30.72:22 as \'dukang\'

debug1: load_hostkeys: fopen /home/tengda/.ssh/known_hosts2: No such
file or directory

debug1: load_hostkeys: fopen /etc/ssh_known_hosts: No such file or
directory

debug1: load_hostkeys: fopen /etc/ssh_known_hosts2: No such file or
directory

debug1: SSH2_MSG_KEXINIT sent

debug1: SSH2_MSG_KEXINIT received

debug1: kex: algorithm: curve25519-sha256@libssh.org

debug1: kex: host key algorithm: ssh-ed25519

debug1: kex: server-\>client cipher: chacha20-poly1305@openssh.com MAC:
\<implicit\> compression: none

debug1: kex: client-\>server cipher: chacha20-poly1305@openssh.com MAC:
\<implicit\> compression: none

debug1: expecting SSH2_MSG_KEX_ECDH_REPLY

debug1: SSH2_MSG_KEX_ECDH_REPLY received

debug1: Server host key: ssh-ed25519
SHA256:E0mga31W30EWFNYLWpXKxGnsBYzXNO7dDCNX6ttxolY

debug1: load_hostkeys: fopen /home/tengda/.ssh/known_hosts2: No such
file or directory

debug1: load_hostkeys: fopen /etc/ssh_known_hosts: No such file or
directory

debug1: load_hostkeys: fopen /etc/ssh_known_hosts2: No such file or
directory

debug1: hostkeys_find_by_key_hostfile: hostkeys file
/home/tengda/.ssh/known_hosts2 does not exist

debug1: hostkeys_find_by_key_hostfile: hostkeys file
/etc/ssh_known_hosts does not exist

debug1: hostkeys_find_by_key_hostfile: hostkeys file
/etc/ssh_known_hosts2 does not exist

The authenticity of host \'172.16.30.72 (172.16.30.72)\' can\'t be
established.

ED25519 key fingerprint is
SHA256:E0mga31W30EWFNYLWpXKxGnsBYzXNO7dDCNX6ttxolY.

This key is not known by any other names

Are you sure you want to continue connecting (yes/no/\[fingerprint\])?
no

Host key verification failed.

③fingerprint

The authenticity of host \'172.16.30.72 (172.16.30.72)\' can\'t be
established.

ED25519 key fingerprint is
SHA256:E0mga31W30EWFNYLWpXKxGnsBYzXNO7dDCNX6ttxolY.

This key is not known by any other names

Are you sure you want to continue connecting (yes/no/\[fingerprint\])?
[fingerprint]{.mark}

Please type \'yes\', \'no\' or the fingerprint: [yes]{.mark}

Warning: Permanently added \'172.16.30.72\' (ED25519) to the list of
known hosts.

debug1: rekey out after 134217728 blocks

debug1: SSH2_MSG_NEWKEYS sent

debug1: expecting SSH2_MSG_NEWKEYS

debug1: SSH2_MSG_NEWKEYS received

debug1: rekey in after 134217728 blocks

debug1: Skipping ssh-dss key /home/tengda/.ssh/id_dsa - corresponding
algo not in PubkeyAcceptedAlgorithms

debug1: Will attempt key: /home/tengda/.ssh/id_rsa RSA
SHA256:zVSNQ6n2klY8OyBpOVOB1guQsImdX+gvYa3zWzGL13c

debug1: Will attempt key: /home/tengda/.ssh/id_ecdsa

debug1: Will attempt key: /home/tengda/.ssh/id_ecdsa_sk

debug1: Will attempt key: /home/tengda/.ssh/id_ed25519

debug1: Will attempt key: /home/tengda/.ssh/id_ed25519_sk

debug1: Will attempt key: /home/tengda/.ssh/id_xmss

Connection closed by 172.16.30.72 port 22

#  第四部分 git与svn

# 21)git与svn的区别

![](media/image308.png){width="3.207638888888889in"
height="1.9381944444444446in"}
![](media/image309.png){width="3.7243055555555555in"
height="2.7118055555555554in"}

**svn -集中式管理工作流程 git-分布式管理工作流程**

**最核心的区别是，svn是集中式的，git是分布式的。**所以[在使用git时，哪怕断网，或者不在公司开发环境下，你仍然能提交文件、查看历史版本记录、创建项目分支等]{.mark}。\--
**[git可以本地提交代码、进行版本管理]{.mark}**，这是git最大的优势。

svn属于集中化的版本控制系统，使用起来有点像档案仓库的感觉，它具有悲观锁的功能，能够实现一个用户在编辑时对文件进行锁定，阻止多人同时编辑同一文件，比如产品使用excel管理需求文档，建议使用svn； \
git是一个分布式版本控制系统，它擅长的是程序代码的版本化管理。

git按元数据方式存储，svn按文件存储。**.git目录是处于你机器上的一个克隆的版本库，它拥有中心版本库上所有的东西，例如tag,
branch, commit等。**

git没有一个全局版本号，而svn有。**git的内容存储使用的是SHA-1哈希算法生成一个128位的ID作为版本号**，而**svn使用一个递增的序列号作为全局唯一的版本号**，更加简明易懂。虽然可以用git
tag来建立别名。

git的内容完整性要优于svn，git如果遇到磁盘故障可以很好的恢复，而svn备份版本库的任务是管理员非常头疼的任务。

git中branch是基于版本号，而svn的branch本质上是一个拷贝操作。所以git的branch更有利于代码合并，而svn的branch可以针对任何子目录。

# 22)同时使用git和svn管理代码

## 同时使用的方法

**[git的优势：①可以在本地提交修改，精细控制修改历史记录；②分支切换很方便，代价很小。]{.mark}**

**svn最大的问题是不能在本地提交修改，只能提交到远程仓库。**

如果本地临时修改提交到远程仓库那么会给其他人带来麻烦，**[没办法在本地记录修改历史]{.mark}**。

还没修改完成的代码，可能需要多个**中间临时版本**做测试，这些**中间临时版本**是不能提交到远程库的，还可能需要在多个**版本之间来回切换**，**这种情况下svn非常不方便**。

**[git可以在本地提交修改，可以对修改历史记录进行精细版本控制]{.mark}**。git可以将**临时修改、阶段性的修改**作为一次提交，便于**修改前后对比**。在开发阶段，这种修改前后进行差异对比是很重要的，能大大提高效率。

**git在本地代码提交和版本管理上特别好用**，同时远程版本管理上也好用。而**svn在本地代码管理上很差、没有本地代码提交的功能**，版本管理需要与远程库同步才能使用。

对于**已有使用svn管理的项目**，可以**同时使用git管理**，既能**保留svn修改历史记录**，也能**用git对后续的修改进行精细控制和跟踪**。

步骤：

1、先svn现在代码，svn checkout url。

2、在下载的代码中初始化为git库，以当前状态为基础提交第一次，git
init、git add -A、git
commit。注意提交之前增加.gitignore忽略.svn目录，svn添加忽略文件的方法参考svn总结。

3、关联到远程git库，这一步并不是必要。关联到远程git库，一方面放在本地代码被删除了可以再从远程git库下载，另一方面也方便git
clone拷贝到其他目录。

关联到远程git库：git remote add
giturl。如果远程git库中还没有提交，那么直接git
push；如果远程git库中已有提交，那么先rm -rf
\*删除所有目录和文件(不会删除隐藏目录.svn、.git)，再git pull，然后svn
up更新，如果svn
up后有变更，那么将变更提交到远程git库\--**保持远程git库和svn库同步**。

怎么建立远程git库、怎么关联到远程git库，参考：14)git服务器搭建。

## 使用git-svn(推荐)

**分别使用git
svn和svn下载两份代码，再将库目录拷贝到对方代码目录下**。**简单可靠**，**推荐**。

步骤：

① \$ git svn clone url dirA //此时git remote
-v查看远程库是空的，可以添加自己的远程库，便于代码的管理、备份。

② \$ svn checkout url dirB

③ \$ cp -arf dirB/.svn/ dirA //将dirB/.svn/库目录拷贝到dirA

备注：git svn clone url dirA -r 8958、svn checkout url dirA -r
8958，下载指定版本，不指定则下载最新版本。

此时dirA目录下的代码可用同时使用git和svn管理，git status、git log、git
svn log、...、svn status、svn log、...

或者:\$ cp -arf dirA/.git dirB
//将dirA/.git库目录拷贝到dirB，此时dirB目录下的代码也能同时使用git和svn管理。

④ \$ svn up再git svn fetch; git rebase remotes/git-svn
//更新代码，参考后一节：使用git-svn和svn同时管理代码时怎么更新版本。

总结：**分别用git
svn和svn下载一份代码，再将.git/.svn拷贝到对方目录下。**

如果不想分别用git svn和svn下两份代码，也可以如下操作：

**先git
svn下载，删除所有代码(保留.git库目录)，再svn下载一次**。**注意git
svn和svn下载同一个版本**。

① \$ git svn clone url dirA

② \$ rm -rf dirA/\* //删除所有文件、保留.git库目录。附:rm -rf
\*删除可见文件、保留隐藏文件，rm -rf .\*删除隐藏文件、保留可见文件。

③ \$ svn checkout url dirA

或者先svn checkout url dirA，然后cd dirA、rm -rf
dirA/\*删除工作区文件，再git svn clone url dirA。

必须有第③步，否则git status/svn
status查看的状态不对。通过git/svn模型可知，**版本管理分两部分：库目录、代码目录**，**在下载或更新代码时这两部分都需要更新**。已经使用svn下载了代码，再用git
svn下载代码时检查代码目录已经有文件了，于是**不再下载代码，只下载了.git库目录**，因为git没有下载代码的记录，于是git
status查看的状态文件是删除的，**.git库目录的更新和代码目录的更新没有同步造成的**，**所以上述rm
-rf dirA/\*删除所有代码，这样git
clone时会同步更新.git库和代码目录，这样git
status查看的状态才是对的**。**git和svn都要有更新库目录和代码目录的记录才能使得git
status/svn
status查看的状态是正确的，\"**使用git-svn和svn同时管理代码时怎么更新版本**\"**一节中的操作也是基于这个原理**。**

\--这些操作验证了：(1)版本管理分两部分:.git/.svn库目录、代码目录，库目录和代码目录要同步更新才能使得git/svn
status是正确的；(2)库目录和代码目录是分离的，.git/.svn库目录可用任意移动。

## 使用git-svn和svn同时管理代码时怎么更新版本

步骤：

① \$ svn clone url dirA -r 8958

② \$ git svn checkout url dirB -r 8958

③ \$ cp -arf dirB/.svn/ dirA

④ \$ cd dirA //此时svn status查看是干净的、多出来一个.git目录未跟踪，git
status查看也是干净的，多出来一个.svn目录未跟踪。将.svn添加到.gitignore忽略中，svn怎么忽略.git？\--todo

**⑤ 更新版本**

**先更新git版本，再更新svn版本，推荐**

\$ git svn fetch -r 8969 //更新git版本库

\$ git rebase remotes/git-svn
//更新工作目录。此时工作目录代码已经被git更新到r8969，但是svn版本还在r8958，svn
status查看是有修改的

\$ svn up -r 8969 //更新svn版本库。此时git版本和svn版本都在r8969，git
status/svn status查看都是干净的

这样git版本库、svn版本库、工作目录都在同一个版本上，svn status、git
status查看又都是干净的了。

**git和svn都要有更新库目录和代码目录的记录才能使得git status/svn
status查看的状态是正确的。**

**git和svn升级到相同的版本，才能git status、svn
status查看是干净的**，否则两个版本库版本不一致，git status或svn
status查看是有修改的。

推荐这个方法，因为先更新git库再更新svn库简单些，不需要git stash。

如果本地有修改未提交那么git更新会失败，svn更新则会直接覆盖本地修改(会造成本地修改丢失)，因此git/svn同时管理代码时，先用git更新再用svn更新更好。

**先更新svn版本，再更新git版本**

\$ svn up -r 8969
//此时git库还在版本r8958，但是工作目录代码已经被svn更新到r8969，git
status查看是有修改的，git fetch更新会报错，这个时候需要git
stash暂存一下，然后再更新

\$ git stash

\$ git svn fetch -r8969

\$ git rebase remotes/git-svn

\$ git stash drop //stash不需要了可用删掉

## 代码的修改、提交

**为什么需要同时使用git和svn管理代码？**

继承的代码是使用svn进行版本管理的。**[svn没有本地代码提交的功能、只能提交到远程库，因此有必要使用git进行本地提交的管理。]{.mark}**

对于继承svn管理的代码，同时使用git管理后，为了**防止本地代码被删除，可以备份到个人git库，本地git提交、push到个人git库备份**。

\$ cd \~/backup; mkdir repository; cd repository; mkdir wifi
//个人git库目录:\~/backup/repository/wifi

\$ cd \~/backup/repository/wifi; git init \--bare

\$ cd \~/work; svn checkout url wifi; rm -rf wifi/\*; git svn clone url
wifi //工作目录:\~/work/wifi

\$ cd wifi; git remote add origin \~/backup/repository/wifi; git push
//第一次提交使用git push \--set-upstream origin master

\$ vim tx.c; git add tx.c; git commit -m \"modify tx.c\"; git push;
//**[中间过程修改使用git提交到本地，最终修改使用svn提交]{.mark}**:svn
commit tx.c -m \"modify tx.c\"

# 23)git/svn模型：库目录、代码目录

**git/svn代码管理分两部分：库目录、代码目录。git库保存在代码目录下的.git目录，svn库目录保存在代码目录的.svn目录。**

**git/svn是通过库目录.git/.svn来管理代码目录的。**

**git在本地使用.git库目录保存提交历史记录，svn在本地使用.svn库目录保存提交历史记录。**

**因为版本是通过.git、.svn目录进行管理的**，实际上**只需要将.git、.svn目录拷贝到对应的代码目录**就可以**同时使用git和svn进行管理了，要保证.git、.svn目录不受对方影响。**

**库目录和代码目录是可用分离的**

**.git目录和代码目录是可以分离的，只需要.git目录就可以在本地恢复本地代码。**

**.svn目录和代码目录是可以分离的，但是不能通过.svn在本地恢复整个代码，需要连接到远程svn服务器才能恢复本地代码。**

![](media/image80.png){width="2.1875in" height="1.3423611111111111in"}

**实际上.git库目录、.svn库目录可以任意拷贝和移动**，从而有上面"同时使用git和svn管理代码的新方法"。

这里的**代码目录、库目录、工程目录是逻辑上的**，**实际上代码目录和工程目录是同一个目录，库目录.git/.svn存放在代码根目录下**。

**同时使用git和svn管理代码时，git使用.git目录作为库目录，svn使用.svn作为库目录，git和svn共用一个工作目录。**

**git
pull更新两部分：更新代码目录下的文件，更新库目录.git下的历史记录。**

**svn
up也一样，更新两部分：更新代码目录下的文件，更新库目录.svn下的历史记录。**

**git fetch只是更新库目录.git，并没有更新工作目录，需要使用git rebase
\<REMOTE_BRANCH_NAME\>才能更新工作目录。或者git merge
\<REMOTE_BRANCH_NAME\>。**

**在同时使用git和svn管理代码时，如果先用git
pull更新，那么会更新代码目录和.git库目录，代码和git提交记录更新了，但svn提交记录还没更新，此时可以执行svn
up更新，因为代码已经是更新过的，此时实际上只是更新.svn库目录和svn提交记录而已(会对代码目录再次更新，但是内容不变)**。**先使用svn更新、再使用git更新，道理是一样的。**

**基于这个模型，对git fetch/git pull解释，git
fetch只更新.git库目录、不更新工作目录，git pull=git fetch+git merge，git
pull先更新.git库目录，再使用git merge更新工作目录？**

# 24)git svn详解

## git svn介绍

**[git svn可以将svn库转换成git库，同时保留svn提交历史记录。]{.mark}**

安装：apt-get install git-svn

git svn clone下载代码，本地只有.git目录，没有.svn目录。

下载指定版本的代码：git svn clone url localdir -r 6548。

使用git svn log查看提交历史记录，使用方法和git log一样。区别：git svn
log显示方式比git log更好，git svn
log只能看到已经提交到svn库的提交、看不到本地提交，git
log能看到本地提交和已经提交到svn库的提交。

更新代码使用git svn fetch、git svn rebase。

与原有svn库交互使用git svn
fetch/rebase/dcommit，与自己的git远程库交互使用git本来的命令。

## git svn常用命令

git svn clone svnurl

git svn clone svnurl localdir

git svn clone \--username=dukang svnurl localdir -r 6548

git svn info

git svn log

git svn reset

git svn fetch

git svn rebase

git svn dcommit

## git svn命令帮助

\$ **git svn help**

usage: **git svn \<command\> \[options\] \[arguments\]**

Available **commands**:

**blame** Show what revision and author last modified each line of a
file

\--git-format

**branch** Create a branch in the SVN repository

\--commit-url \<arg\>

\--destination, -d \<arg\>

\--dry-run, -n

\--message, -m \<arg\>

\--parents

\--tag, -t

\--username \<arg\>

[**clone** Initialize and fetch revisions]{.mark}

\--add-author-from

\--authors-file, -A \<arg\>

\--authors-prog \<arg\>

\--branches, \--b=s@

\--config-dir \<arg\>

\--follow-parent, \--follow!

\--ignore-paths \<arg\>

\--ignore-refs \<arg\>

\--include-paths \<arg\>

\--localtime

\--log-window-size \<num\>

\--minimize-url, \--m!

\--no-auth-cache

\--no-checkout

\--no-metadata

\--placeholder-filename \<arg\>

\--prefix \<arg\>

\--preserve-empty-dirs

\--quiet, \--q+

\--repack-flags, \--repack-args, \--repack-opts \<arg\>

\--repack \<num\>

\--revision, -r \<arg\>

\--rewrite-root \<arg\>

\--rewrite-uuid \<arg\>

\--shared \<arg\>

\--stdlayout, -s

\--tags, \--t=s@

\--template \<arg\>

\--trunk, -T \<arg\>

\--use-log-author

\--use-svm-props

\--use-svnsync-props

\--username \<arg\>

**commit-diff** commit a diff between two trees

\--copy-similarity, -C \<num\>

\--edit, -e

\--file, -F \<arg\>

\--find-copies-harder

-l \<num\>

\--message, -m \<arg\>

\--revision, -r \<arg\>

\--rmdir

**create-ignore** Create a .gitignore per svn:ignore

\--revision, -r \<num\>

[**dcommit** commit several diffs to merge with upstream]{.mark}

\--add-author-from

\--authors-file, -A \<arg\>

\--authors-prog \<arg\>

\--commit-url \<arg\>

\--config-dir \<arg\>

\--copy-similarity, -C \<num\>

\--dry-run, -n

\--edit, -e

\--fetch-all, \--all

\--find-copies-harder

\--follow-parent, \--follow!

\--ignore-paths \<arg\>

\--ignore-refs \<arg\>

\--include-paths \<arg\>

\--interactive, -i

-l \<num\>

\--localtime

\--log-window-size \<num\>

\--mergeinfo \<arg\>

\--merge, -m, -M

\--no-auth-cache

\--no-checkout

\--no-rebase

\--quiet, \--q+

\--repack-flags, \--repack-args, \--repack-opts \<arg\>

\--repack \<num\>

\--revision, -r \<num\>

\--rmdir

\--set-svn-props \<arg\>

\--strategy, -s \<arg\>

\--use-log-author

\--username \<arg\>

\--verbose, -v

[**fetch** Download new revisions from SVN //和git
fetch一样，只更新.git库目录，不更新工作区]{.mark}

\--add-author-from

\--authors-file, -A \<arg\>

\--authors-prog \<arg\>

\--config-dir \<arg\>

\--fetch-all, \--all

\--follow-parent, \--follow!

\--ignore-paths \<arg\>

\--ignore-refs \<arg\>

\--include-paths \<arg\>

\--localtime

\--log-window-size \<num\>

\--no-auth-cache

\--no-checkout

\--parent, -p

\--quiet, \--q+

\--repack-flags, \--repack-args, \--repack-opts \<arg\>

\--repack \<num\>

[\--revision, -r \<arg\>]{.mark}

\--use-log-author

\--username \<arg\>

**find-rev** Translate between SVN revision numbers and tree-ish

-A, \--after

-B, \--before

**gc** Compress unhandled.log files in .git/svn and remove index files
in .git/svn

[**info** Show info about the latest SVN revision on the current branch
\--url]{.mark}

[**init** Initialize a repo for tracking (requires URL argument)]{.mark}

\--branches, \--b=s@

\--config-dir \<arg\>

\--ignore-paths \<arg\>

\--ignore-refs \<arg\>

\--include-paths \<arg\>

\--minimize-url, \--m!

\--no-auth-cache

\--no-metadata

\--prefix \<arg\>

\--rewrite-root \<arg\>

\--rewrite-uuid \<arg\>

\--shared \<arg\>

\--stdlayout, -s

\--tags, \--t=s@

\--template \<arg\>

\--trunk, -T \<arg\>

\--use-svm-props

\--use-svnsync-props

\--username \<arg\>

**log** Show commit logs

\--authors-file, -A \<arg\>

\--color

\--incremental

\--limit \<num\>

\--non-recursive

\--oneline

\--pager \<arg\>

\--revision, -r \<arg\>

\--show-commit

\--verbose, -v

**migrate** Migrate configuration/metadata/layout from

previous versions of git-svn

\--config-dir \<arg\>

\--ignore-paths \<arg\>

\--ignore-refs \<arg\>

\--include-paths \<arg\>

\--minimize

\--no-auth-cache

\--username \<arg\>

**mkdirs** recreate empty directories after a checkout

\--revision, -r \<num\>

**propget** Print the value of a property on a file or directory

\--revision, -r \<num\>

**proplist** List all properties of a file or directory

\--revision, -r \<num\>

**propset** Set the value of a property on a file or directory - will be
set on commit

[**rebase** **Fetch and rebase** your **working directory**]{.mark}

\--add-author-from

\--authors-file, -A \<arg\>

\--authors-prog \<arg\>

\--config-dir \<arg\>

\--dry-run, -n

\--fetch-all, \--all

\--follow-parent, \--follow!

\--ignore-paths \<arg\>

\--ignore-refs \<arg\>

\--include-paths \<arg\>

\--localtime

\--local, -l

\--log-window-size \<num\>

\--merge, -m, -M

\--no-auth-cache

\--no-checkout

\--preserve-merges, -p

\--quiet, \--q+

\--rebase-merges, -p

\--repack-flags, \--repack-args, \--repack-opts \<arg\>

\--repack \<num\>

\--strategy, -s \<arg\>

\--use-log-author

\--username \<arg\>

\--verbose, -v

[**reset** Undo fetches back to the specified SVN revision]{.mark}

\--parent, -p

[\--revision, -r \<arg\>]{.mark}

**set-tree** Set an SVN repository to a git tree-ish

\--add-author-from

\--authors-file, -A \<arg\>

\--authors-prog \<arg\>

\--config-dir \<arg\>

\--copy-similarity, -C \<num\>

\--edit, -e

\--find-copies-harder

\--follow-parent, \--follow!

\--ignore-paths \<arg\>

\--ignore-refs \<arg\>

\--include-paths \<arg\>

-l \<num\>

\--localtime

\--log-window-size \<num\>

\--no-auth-cache

\--no-checkout

\--quiet, \--q+

\--repack-flags, \--repack-args, \--repack-opts \<arg\>

\--repack \<num\>

\--rmdir

\--stdin

\--use-log-author

\--username \<arg\>

**show-externals** Show svn:externals listings

\--revision, -r \<num\>

**show-ignore** Show svn:ignore listings

\--revision, -r \<num\>

**tag** Create a tag in the SVN repository

\--commit-url \<arg\>

\--destination, -d \<arg\>

\--dry-run, -n

\--message, -m \<arg\>

\--parents

\--username \<arg\>

GIT_SVN_ID may be set in the environment or via the \--id/-i switch to
an

arbitrary identifier if you\'re tracking multiple SVN
branches/repositories in

one git repository and want to keep them separate. See git-svn(1) for
more

information.

## git svn用法

### Synchronizing Repositories

https://wiki.bnl.gov/dayabay/index.php?title=Synchronizing_Repositories\$
git_and_SVN

From Daya Bay

Jump to:
[navigation](https://wiki.bnl.gov/dayabay/index.php?title=Synchronizing_Repositories#column-one),
[search](https://wiki.bnl.gov/dayabay/index.php?title=Synchronizing_Repositories#searchInput)

You can synchronize not just to Daya Bay repositories but between
personal and/or 3rd party ones. One way is to use
[git](http://git.or.cz/) to glue CVS and SVN repositories together. This
topic describes ways to exploit this strategy.

#### Why do this?

⚫Track changes in 3rd party code with local modifications not
acceptable to upstream

⚫Allow for offline commits

⚫Allow for \"out of band\" peer-to-peer code sharing

#### GIT and CVS and SVN

Previous attempts (below) failed to put both upstream CVS and downstream
SVN into one GIT repository. The trick to doing this is maintaining
strict separation between the pristine CVS branch and the one used to
upload to SVN. Also important is to make sure that the SVN branch has
the CVS branch in its history so subsequent updates to the CVS branch
can be more easily merged into the SVN branch.

The example below uses the Relax project which provides Reflex
dictionaries for common HEP and STL classes.

##### Initial CVS importation

bviren@lycastus:nuwa-git\> git cvs import -r upstream-cvs -o
upstream-cvs-head -d :pserver:anonymous@relax.cvs.cern.ch:/cvs/relax -C
relax relax

bviren@lycastus:(master):relax\> git branch -a

\* master

upstream-cvs/HEAD

upstream-cvs/LCG53_b

upstream-cvs/RELAX_1_1_2_branch

upstream-cvs/avendor

upstream-cvs/upstream-cvs-head

bviren@lycastus:(master):relax\> rm -r \*

##### Initialize SVN project

svn mkdir <http://dayabay.ihep.ac.cn/svn/dybsvn/relax>

svn mkdir <http://dayabay.ihep.ac.cn/svn/dybsvn/relax/trunk>

svn mkdir <http://dayabay.ihep.ac.cn/svn/dybsvn/relax/tags>

svn mkdir <http://dayabay.ihep.ac.cn/svn/dybsvn/relax/branches>

svn co <http://dayabay.ihep.ac.cn/svn/dybsvn/relax>

cd relax/trunk/

echo \"This area tracks Relax CVS
at :pserver:anonymous@relax.cvs.cern.ch:/cvs/relax.\" \> README

svn add README

svn commit -m \"Prime this project area.\" README

##### Initialize GIT\'s SVN branch

bviren@lycastus:(master):relax\> git svn init -s \--username=bv
\--prefix=downstream-svn/ <http://dayabay.ihep.ac.cn/svn/dybsvn/relax>

bviren@lycastus:(master):relax\> git svn fetch

bviren@lycastus:(master):relax\> git checkout \--track -b
downstream-svn-trunk downstream-svn/trunk

bviren@lycastus:(downstream-svn-trunk):relax\> git branch -a

\* downstream-svn-trunk

master

downstream-svn/trunk

upstream-cvs/HEAD

upstream-cvs/LCG53_b

upstream-cvs/RELAX_1_1_2_branch

upstream-cvs/avendor

upstream-cvs/upstream-cvs-head

##### Merge CVS head branch into SVN trunk branch

bviren@lycastus:(downstream-svn-trunk):relax\> git merge \--no-commit
upstream-cvs/HEAD

Automatic merge went well; stopped before committing as requested

bviren@lycastus:(downstream-svn-trunk):relax\> git commit -m \"Merge of
Relax\'s CVS HEAD.\"

Created commit 30e7dc9: Merge of Relax\'s CVS HEAD.

##### Upload changes to SVN

bviren@lycastus:(downstream-svn-trunk):relax\> git svn dcommit

bviren@lycastus:(downstream-svn-trunk):relax\> rm \$(find . -name
.cvsignore -print)

bviren@lycastus:(downstream-svn-trunk):relax\> git commit -a -m \"Remove
.cvsignore cruft.\"

##### Update to latest in CVS

t.b.d.

#### GIT and CVS

This [blog
posting](http://issaris.blogspot.com/2005/11/cvs-to-git-and-back.html)
is the main inspiration for this section. It is reproduced here for
safety.

This uses two git repositories:

myrepo.git.cvs-gateway 

a pristine git mirror of the state of the CVS repository

myrepo.git.devel 

a tracking clone of the above that supports editting

##### Initalize git to cvs gateway repository

mkdir myrepo.git.cvs-gateway

git cvs import -p x -v -d \$CVSROOT \[optional_module_name\]

##### Initialize the git repository for development

git clone -l myrepo.git.cvs-gateway myrepo.git.devel

Local mods can be done in this repository. By default you will have a
newly created \"master\" branch which tracks the CVS HEAD. Normal git
commands can be done in this repository. Like usual, work on branches
that track remote branches and not on remote branches directly.

##### Update the git-to-cvs gateway repository

cd myrepo.git.cvs-gateway

git cvs import \[-a\] -p x -v -d \$CVSROOT

The same command is used, but the -a is useful if you want to get very
recent CVS commits.

##### Updating development git

cd myrepo.git.devel

git pull

##### commit back to CVS

This step is a little wonky. You will run a git cvs command from the a
checked out copy of the CVS module but will point git at the devel
repository.

cd cvs-checked-out-project/\[optional_module_name\]

GIT_DIR=/path/to/myrepo.git.devel git cvs export commit \<HASH\>

The \<HASH\> is the SHA1 hash reported by git commit. If you missed when
committing, use gitk to find it. Finally follow the printed CVS commit
command which will be something like:

cvs commit -F .msg file1 file2 \...

#### GIT and SVN

Using GIT and SVN repositories together is done through the git svn
tool. It is used to access SVN as a remote GIT repository.

##### Creating a git svn repository

Create a git svn repository with \"git svn init\" like:

**[git svn init \[\--prefix=prefix/\] \--username \[SVNUSER\] \[SVNURL\]
\[TARGET\]]{.mark}**

The target is a directory that git svn will create to hold the
repository. You can run this in a pre-existing GIT project (and leave
off the \"TARGET\" argument). If you don\'t specify a prefix then the
remote git svn branch will be named \"git-svn\".

Note, that depending on the SVNURL you will download different parts of
the repository. This may include branches and/or tags sub directories.
Modify the SVNURL to limit the download to a sub-part of the repository
as desired.

##### Getting a working copy of SVN files

The init will not pull down any SVN files. To do that for the first time
and for any subsequent updates of SVN use:

git svn fetch

If your URL specifies something other than the top level of the SVN
repository you may see a \"Path Not Found\" warning. It is apparently
innocuous.

After the fetch you will be sitting in a working branch \"master\". To
get a working branch with a more descriptive name, am explicit checkout
is recommended.

git checkout \--track -b git-svn-working git-svn/remote-branch

##### Updating GIT

To [update your git repository]{.mark} with any potential changes made
in SVN do a fetch:

[git svn fetch]{.mark}

If any come in they will live in a branch in your GIT repository coming
off you recent local commits. To \"replay\" your locally committed
modifications use

[git svn rebase]{.mark}

This may throw conflicts which you will have to resolve by hand.

##### Updating SVN

To update SVN with locally committed modifications (not working
directory mods) first update your git repository as above then issue:

[git svn dcommit]{.mark}

Note the \"d\" in dcommit.

There is always a potential race condition between your last
fetch/rebase and the dcommit. If someone happened to commit in the mean
time you will get a somewhat cryptic message:

shell-prompt\> git svn dcommit

Merge conflict during commit: Your file or directory

\'git/path/to/some/committed/file\' is probably out-of-date: The

version resource does not correspond to the resource within the

transaction. Either the requested version resource is out of date

(needs to be updated), or the requested version resource is newer

than the transaction root (restart the commit). at /path/to/git-svn

line 405

Just redo this tripple:

[git svn fetch]{.mark}

[git svn rebase]{.mark}

[git svn dcommit]{.mark}

##### Checking where you are at

If a git svn fetch causes remote commits to be downloaded you can check
where your currently at in your local development.

⚫Find out changes your working directory has which haven\'t been
locally committed

git status

⚫Find out what branch you are on and what others are available

git branch -a

⚫Browse the commits and branche structure.

[gitk \--all]{.mark}

##### Advanced: Linking another, remote GIT repository to your GIT and GIT-SVN

**[You can use an intermediate GIT repository to syncronize an SVN
repository to another GIT repository, be it a native GIT or]{.mark}**
GIT-CVS or GIT-SVN one. To do this, first set up an intermediate git-svn
repository like above. If it is a new repository, it should be
\"primed\" with at least a single file. Then, add the remote GIT
repository:

[git remote add \<LABLE_FOR_REMOTE\> \<REMOTE_GIT_URL\>]{.mark}

[git fetch \<LABLE_FOR_REMOTE\>]{.mark}

This links the labeled remote GIT repository and fetches its single
file.

To upload remote history to SVN first make sure you are working in
git-svn-working (git branch -a will tell). Then decide between one of
two methods:

###### Mostly lossless history with git svn set-tree

**Warning:** use this command with caution as it forces a commit that
makes the SVN area appear just like the state at the given git commit.

To upload a single remote commit to SVN use

git svn set-tree \<COMMIT\>

or

git svn set-tree \<COMMIT1\>..\<COMMIT2\>

To upload all commits between #1 and #2 inclusive. Note: use set-tree
only in this special case of syncing with a remote branch. If you are
using git only to track SVN you should use git svn dcommit to upload
changes.\
The commit ID can be taken from running gitk on the remote branch like:

gitk \$(cat .git/refs/remotes/LABEL_FOR_REMOTE/REMOTE_BRANCH_NAME)

While this does replay remote commits into SVN, the commits will have
current dates and will be attributed to the git-svn user and not the
original author.

Your working branch will still be at the pre set-tree state. To catch up
do

git reset \--hard git-svn

Where \"git-svn\" is the branch created during git svn init. If you
choose something besides the default, substitute it here.

###### Lossy history with git merge + git svn dcommit

If you want to control how the remote history is uploaded you can
periodically merge the remote branch with the git-svn one:

git merge \[-m \"some merge commit message\"\]
\<LABEL_FOR_REMOTE/REMOTE_BRANCH_NAME\>

Followed by a \"dcommit\"

git svn dcommit

This will not preserve any history of the remote branch in SVN. That is,
it will look like a single commit regardless of how many commits were
made to the remote branch. It will be attributed to the git-svn user and
will have a commit message like \"Merge commit
\'LABEL_FOR_REMOTE/REMOTE_BRANCH_NAME\' into git-svn-working\" unless
the -m option was given.

#### GIT and GIT

I keep a GIT/GIT-SVN repository as well as a \"local-working-copy\" GIT
repository. Each has the other as a remote.

git remote add -f local-working-copy /path/to/working/copy/.git

To sync I do the following in the git/git-svn repository:

git cherry HEAD remotes/local-working-copy/dybsvn-trunk

to see how they differ:

gitk \$(cat .git/refs/heads/dybsvn-trunk
.git/refs/remotes/local-working-copy/dybsvn-trunk )&

git merge \--no-commit \[top commit of local-working-copy\]

(I think I can also use just remotes/local-working-copy/dybsvn-trunk)

This may have conflicts, fix them and

git commit

This collapses all the commit in the local-working-copy into one so some
fine grained details of the history are lost. I would like to keep them,
but I don\'t see how.

From the working directory I just do a git pull.

### git svn用法

svn作为一个优秀源码版本的管理工具，可以适合绝大多数项目。但是因为它的采用中心化管理，不可避免的存在本地代码的备份和版本管理问题。也就是说对于尚未或暂无法提交到Subversion服务器的本地代码来说，存在着被误删除和版本更新无法回退两大情形。

git作为一个分布式版本管理工具，可以很好的解决这个问题。因为它的大多数操作是在本地进行的。这里要说的是git是如何做到既可以管理好本地代码又可以与已有的SVN中心库进行同步的。

支持去中心化，是git与生俱来的特性，它在本地保留了从中心服务器clone出来的源码库的全部信息，这样，你在本地修改完代码后便可以直接提交到本地
的代码版本库中。本地代码的备份和版本管理的问题就这样被git轻而一举的就解决了。而本地源码库与SVN中心源码库的同步操作则是由git提供的
git-svn工具来完成的。

下面是一个git-svn的一般使用流程：

1、git-svn clone svn_repository

2、修改本地代码，使用git add/commit将修改提交到本地git库

3、定期使用git-svn rebase获取中心svn repository的更新

4、使用git-svn dcommit命令将本地git库的修改同步到中心svn库

检出一个已存在svn repository(类似于svn checkout)

可以通过git-svn clone命令完成这个操作： git-svn clone svn_repository_url

一般情况下git svn
clone这个操作会从第一个版本开始同步，如果版本号已经到了好几万(或更高？)，这个操作会相当的费时。这时可以使用参数-r\$REVNUMBER:HEAD检出指定版本后的代码。

因此，更好的步骤应该是这样：

svn info svn_repository_url, 记录最后的版本号，假设是260

假设要检出最后5个版本，做个简单的减法： 260 - 5 = 255

开始clone操作了：git-svn clone -r255:HEAD svn_repository_url

从中心服务器的svn repository获取最新更新

这个操作可以通过"git-svn
rebase"完成。注意这里用的是rebase，而不是update。update命令对于通过git-svn检出的svn
repostory的git版本库是不可用的。

查看提交历史日志

使用"git-svn
log"，加上-v选项，还可以提供每次commit操作涉及的相关文件的详细信息。

将本地代码同步到Svn服务器

完成这一操作需要通过"git-svn dcommit"命令。这个命令会将你在本地使用git
commit提交到本地代码库的所有更改逐一提交到svn库中。加上-n选项，则该命令不会真正执行commit到svn的操作，而是会显示会有哪些本地
变动将被commit到svn服务器。git-svn
dcommit似乎不能单独提交某个本地版本的修改，而是一次批量提交所有与svn中心版本库的差异。

提交时的冲突解决：

如果你正在提交的文件在svn服务器上已经被别人改过，就会发生提交冲突。通常解决方法如下：

首先使用git-svn
rebase获取svn服务器上的最新冲突文件，比如：conflict.c，这将导致与本地conflict.c冲突，不过此时svn版本信息已经添加到本地git库中(通过git
log可以查看)，git-svn rebase提示你在解决conflict.c的冲突后，运行git
rebase \--continue完成rebase操作

打开conflict.c，修改代码，解决冲突

执行git rebase \--continue，git提示：You must edit all merge conflicts
and then mark them as resolved using git add

执行git add conflict.c，告知git已完成冲突解决

再次执行git rebase \--continue，提示"Applying: git xxx"，此时"git
xxx"版本又一次成功加入本地版本库，可通过git log查看；

执行git-svn
dcommit将conflict.c的改动同步到svn中心库，到此算是完成一次冲突解决。

### git svn用法

1、从svn
clone出项目，加上-s参数以标记识别svn标准的目录分支结构，同时通过show-ignore设置git库的exclude属性：

git svn clone -s https://svn.xxx.com/svn/xxx

git svn show-ignore \>\> .git/info/exclude

2、建立本地工作分支，开始工作：

git checkout -b work

修改内容直接commit，加上-a开头以省略git add操作：

git commit -a

3、提交回svn的过程：

git checkout master

git merge work

git svn rebase

git svn dcommit

在今天工作中，我提交回svn的方式是：

git checkout master

git svn rebase

git merge work

结果svn
rebase时在master分支上产生了一个新的node，这样merge时就不能快速合并，出现了冲突，修复后，在dcommit时出错，出现N个孤立节点。因为不熟悉，就checkout出work分支，进行了dcommit，然后重新生成一次git库。

今天解决了这个问题，参考以下网址：https://wiki.bnl.gov/dayabay/index.php?title=Synchronizing_Repositories。

以下重新描述一下问题和解决方法：

1、在执行git svn dcommit时，出现如下错误：

committing to https://svn.xxx.com/svn/projects/trunk \...

提交时发生合并冲突:
您的文件或目录"test/functional/xxx_controller_test.rb"可能已经过时: The
version resource does not correspond to the resource within the
transaction. Either the requested version resource is out of date (needs
to be updated), or the requested version resource is newer than the
transaction root (restart the commit). at /usr/bin/git-svn line 450

2、这时，重新执行以下步骤即可：

git svn fetch

git svn rebase

git svn dcommit

但我在执行git svn
rebase时，又出现冲突，这个时候，只需要手工合并掉冲突，并重新add一下：

git add .

然后，再执行：

git rebase \--continue

如果报告说没有修改内容，则换成执行：

git rebase \--skip

完成rebase过程，这时就可以git svn dcommit了。

这样，总算解决了svn历史冲突问题，不用象前面那样笨笨的重新git-svn clone.

http://www.cppblog.com/kuchao/archive/2009/12/18/103462.html

# 第六部分 git协作/互助/帮助

# 25)帮助他人解决git问题的步骤

帮助他人解决问题，**一定要把背景搞清楚**。不要一上来就动手，也不知道别人为什么要这么做，结果费了很大力气，没能解决问题，反而把问题搞复杂，得不偿失了。

帮人解决git问题，总结如下步骤：

目的：需要做什么？为什么要这么做？

背景：

git remote -vv查看有几个库

git branch -vv查看有几个分支

git log \--oneline查看有几个需要操作的提交

history查看做过什么

**搞清楚目的和背景后，才能着手去解决问题。**

# 第七部分 资源

# 26)素材 

![](media/image310.png){width="5.902777777777778in"
height="3.567361111111111in"}

# 27)todo
