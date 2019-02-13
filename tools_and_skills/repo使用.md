# repo -- TODO
- [概念](#概念)  
- [git命令,摘要](#git命令摘要)  
    - [新建代码库](#一新建代码库)  &emsp;&emsp;  [配置](#二配置)  &emsp;&emsp;  [增加/删除/修改文件](#三增加删除修改文件)  &emsp;&emsp;  [代码提交](#四代码提交)  &emsp;&emsp;  [分支](#五分支)  
    - [标签](#六标签)  &emsp;&emsp;  [查看信息](#七查看信息)  &emsp;&emsp;  [远程操作](#八远程操作)  &emsp;&emsp;  [撤销](#九撤销)  &emsp;&emsp;  [其他](#十其他)  
- [patch的使用](#patch的使用)  


## 概念
TODO


# repo介绍

repo是Google开发的用于管理Android版本库的一个工具，repo是使用Python对git进行了一定的封装，并不是用于取代git，它简化了对多个Git版本库的管理。用repo管理的版本库都需要使用git命令来进行操作。

注：**repo**只是用**Python**脚本写的调用**git**的一个脚本**，对git封装了一下。

 

 

# 1.repo的用法

下载 repo 的地址: http://android.git.kernel.org/repo，可以用以下二者之一来下载repo，

wget http://android.git.kernel.org/repo 或者 curl http://android.git.kernel.org/repo > ~/bin/repo  

下载完成后须修改repo的权限： chmod a+x ~/bin/repo 

 

## repo支持的命令

repo所支持的命令可以到源码source/.repo/repo/subcmds/目录下查看，如./abandon.py、./branches.py、./checkout.py…，每一个py文件对应一个可支持的repo命令有：abandon/branches/checkout/cherry_pick/diff/diffmanifests/download/forall/grep/ help/info/init/list/manifest/overview/prune/rebase/selfupdate/smartsync/stage/start/status/sync/upload/version/__init__等。

获取帮助：

repo help [ command ]   //显示command 的详细的帮助信息内容

 

## repo init

repo help init 来获取 repo init的其他用法。

$ repo init -u URL用以**在当前目录安装**repository**，**会在当前目录创建一个目录**.repo**，-u参数指定一个URL，从这个URL中取得repository的manifest文件。   

示例：repo init -u git://android.git.kernel.org/platform/manifest.git

获取的manifest文件放在.repo目录中，命名为manifest.xml。这个文件的内容其实就是所有被git管理的仓库的列表。

可以用-m参数来选择获取repository中的某一个特定的manifest文件，如果不具体指定，那么表示为默认的 manifest文件(default.xml)。

repo init -u git://android.git.kernel.org/platform/manifest.git -m dalvik-plus.xml

(有诸多供我们选择的manifest文件，所有的manifest文件都放在目录.repo/manifests中，该目录本身亦被git所管理，你可以cd进去看看)

可以用 -b 参数来指定某个manifest 分支。

repo init -u git://android.git.kernel.org/platform/manifest.git -b release-1.0

你会发现.repo/manifests是个被git管理的仓库，这里放的是所有的manifest文件（*.xml），因为被git管理，固然有分支，-b可以切换到你想要的分支然后再下载相关的xml文件，当然具体下载那个xml还要看-m参数了，所以如果你仅仅指定-b而没有-m的话，就是下载-b指定分支下的default.xml文件。

如果不指定-b参数，那么会默认使用master分支。

 

## repo sync

$ repo sync [project-list]

下载最新本地工作文件，更新成功，这本地文件和repository中的代码是一样的。可以指定需要更新的project。 

$repo sync #如果不指定任何参数，会同步整个所有的项目。

$repo sync frameworks/base #如果指定工程名，会单独下载指定的工程。

如果是第一次运行repo sync，则这个命令相当于git clone，会把repository中的所有内容都拷贝到本地。如果不是第一次运行repo sync，则相当于git remote update ; git rebase origin/branch . repo sync会更新.repo下面的文件。 如果在merge的过程中出现冲突，这需要手动运行git rebase –continue。

 

用repo sync 在抓去 android source code的时候，会经常出现一些错误导致 repo sync中断，每次都要手动开始。 可以用如下的命令，来自动重复

$?=1; 

while [ $? -ne 0 ] ; 

do repo sync ; 

done

 

## repo start

**初始化分支**

   Sync成功后，所有的git库都处于 no branch状态，不能进行操作

​     *~/test$ **repo branch***

​             *(no branches)*

初化分支

​    *~/test$ **repo start master --all***

​       *Starting master: 100% (45/45), done.*

   --all意思为对所有项目操作，也可以只对某个项目操作如$ repo start mybranch frameworks/base。

repo初如化分支后，可切入各git库进行git的操作。

 

$repo start branchname --all#在源码根目录下执行，对源码目录下所有工程建立branchname分支。

$repo start branchname frameworks/base/#在源码根目录下执行，对frameworks/base/工程建立branchname分支。

$repo start branchname **. #**在对应工程目录下执行，创建branchname分支。"."代表当前工作的工程目录。

 

 

## repo forall -c

在源码根目录执行

$ repo forall -c ls / repo forall --command ls / repo forall -c git branch / repo forall -c git checkout originbranch

这个命令会遍历所有的git仓库，并在每个仓库执行-c/--command所指定的命令(这个被执行的命令就不限于仅仅是git命令了，而是任何被系统支持的命令，比如：ls、pwd、cp等)

$ repo forall -c git checkout  45451 //所有库检出45451分支与远程45451分支对应（若无，则跳过）

$ repo forall -c git checkout  -b developing //对源码根目录下所有工程新建developing分支并切换到该分支。

​                                      //和repo start developing --all一样？

当我想通过这个命令遍历所有的仓库并在每个仓库执行"git checkout . "用以将每个仓库的改动都清除的时候，我这么输入命令：**repo forall -c git checkout .** 

我发现这样根本不行。看来repo不能遍历执行checkout这个命令。今天我终于想到了另外一个命令"git reset --hard HEAD" 哈哈

**$repo forall -c git reset --hard HEAD**

**再说一个新发现：以前用**repo forall**执行一些命令的时候，可能再遍历到某个仓库的时候出了问题，但是我却苦于不知道这个仓库到底是哪个。一直也没有解决。今天终于找到了**…**  **关键时候还是要看命令自己带的帮助手册呀**…**

**$repo help forall**  **用这个命令查看下针对**forall**的帮助吧。说的很清楚，**repo**执行的时候加上**-p**参数就可以在遍历到每个仓库的时候先打印出当前的**pwd**，然后再继续执行**-c**所指定的命令。举例如下：**

**$repo forall -p -c git branch**    

**//**该命令会遍历所有仓库并打印每个仓库的分支情况，由于有了**-p**参数，这样便会打印出每个仓库的路径。**

 

## repo branch

$ repo branch [projectname]

作用：读取项目分支的情况

$ repo branch packages/apps/Contacts //在源码根目录下执行

repo branch/repo status/repo diff/repo checkout/repo abandon和单独的git命令是一样的，只不过是把对应的git命令包装了一下，等效于git branch/git status/git diff/git checkout/git branch -D。

有一点区别就是：repo branch等命令在源码根目录下执行，git branch命令在对应的工程目录下执行。

repo branch等后不加具体工程名，则对源码根目录下所有工程操作，如果加具体工程名，则只对这个工程操作。

 

## repo status

$ repo status [projectname] 

作用：显示分支及修改情况

$ repo status //显示 project 中每个仓库的状态，并打印仓库名称

 

## repo diff

$ repo diff [ project-list ]

显示提交的代码和当前工作目录代码之间的差异。

 

## repo checkout

$repo checkout <branchname> [projectname] 

作用：等同于带项目参数的git checkout

 

## repo abandon

repo abandon <branchname> [projectname]

 作用：删除指定项目的指定分支,强制删除不管是否有合并,等同git branch –D

怎样删除代码文件夹下所有git库的分支？ repo abandon <分支名>

示例，在源码根目录执行，

$ repo forall -c git checkout -b bra1 / repo start bra1 --all

$ repo forall -c git checkout -b bra2 

$ repo abandon bra1 / $ repo abandon bra1 packages/apps/Contacts

 

## repo update

$ repo update[ project-list ]

上传修改的代码 ，如果你本地的代码有所修改，那么在运行 repo sync 的时候，会提示你上传修改的代码，所有修改的代码分支会上传到 Gerrit (基于web 的代码review 系统), Gerrit 受到上传的代码，会转换为一个个变更，从而可以让人们来review 修改的代码。

 

## repo download

$ repo download  target revision

下载特定的修改版本到本地，例如:repo download pltform/frameworks/base 1241，下载修改版本为1241的代码。

 

## repo prune

$ repo prune [project list]

 删除已经merge 的 project

 

## repo version

$ repo version

作用：显示repo版本

 

 

# 1.[repo和git使用遇到的疑难杂症](http://blog.csdn.net/huangxiaohu_coder/article/details/6782260)

<http://blog.csdn.net/huangxiaohu_coder/article/details/6782260>

最近在使用Android的repo和git的过程中遇到了很多莫名奇妙的问题，现在记录一下，便于自己以后的查用。

1.repo sync中遇到error:......checkout ....接一串hashnumber

  解决方法：进到它说提示的目录中，用git status显示文件，将修改过的文件删除掉，再重新repo sync

2.repo sync中遇到：contains uncommitted changes

  解决方法：进到它说提示的目录中，使用git reset --hard命令

**3.** **怎么对**repo**下的所有**project**执行**git**命令**

​    **解决方法：**repo forall -c git checkout --track origin/xxxx -b  //**该条命令会对**repo**下的**project**执行切换**branch**的命令**

**4.** **怎么切换到你想要的**branch**

​    **解决方法：**git checkout branchName**，比如** **git checkout testBranch**

​                        **git checkout --track origin/xxxx -b testbrach**  

**//**在本地建立名为**testbrach** **分支来对应远端的**origin/xxxx**的分支，其中**origin/xxxx**需要使用**git branch -r**来查看。**

\5. git pull时遇到unmerged的问题，再切到问题目录下，查看它的branch，出 现Not currently on any branch

​    解决方法：出现此问题的原因是可能由于你的修改和别人的修改改到一起了，也有可能你有些修改没有git push，这种直接push就好了，其他的情况按照下面的步骤试试：git diff查看冲突的文件，能确定引起冲突的问题话，解决冲突，<<<<<<<<与========之间是你自己的修改，=========与>>>>>>>>是别人都修改，用编辑器编辑留下你要的代码，然后删除掉你冲突的标记符号（<<<<<<,=======,>>>>>>>之类的）。我这个问题恰恰是文件我都没有改过，不是我负责的模块，不确定需要的代码，所以我处理的流程是：git reset  -hard，然后git stash，然后git checkout [branch name]切到正确的branch上。

\6. 你的代码是在no branch上做的commit，后来你切换到真正的branch上（例如testbranch），这时却找不到原来在no branch上提交的代码，怎么办啊？

​    解决方法：用git reflog显示近期的ref历史，记住你想要找回来的commit号，merge进来就好了。
  Git reflog
  Git checkout testbranch
  Git merge commitID
  Git push

\7. 直接使用git pul的出现You asked me to pull without telling me which branch……的错误？

解决办法：在使用git pull的时候写全remote name和branch name，例如git pull origin testBranch

\8. repo sync的时候出现a new version of repo available……得错误？

解决方法：将repo init后会建立.repo文件夹，将.repo/repo/repo拷贝到~/bin/目录下，覆盖原有repo工具即可。

​    或者：删除掉android根目录下的.repoconfig文件夹。

 

 

 

 

**repo用法详解**

<http://blog.csdn.net/sunweizhong1024/article/details/8055372>

Android 为企业提供一个新的市场，无论大企业，小企业都是处于同一个起跑线上。研究 Android 尤其是 Android 系统核心或者是驱动的开发，首先需要做的就是本地克隆建立一套 Android 版本库管理机制。

Android 使用 Git 作为代码管理工具，开发了 Gerrit 进行代码审核以便更好的对代码进行集中式管理，还开发了 Repo 命令行工具，对 Git 部分命令封装，将百多个 Git 库有效的进行组织。要想克隆和管理这百多个 Git 库，还真不是一件简单的事情。

在研究 Repo 的过程中，发现很多文档在 Google Group 上，非“翻墙”不可看。非法的事情咱不干，直接阅读 repo 的代码吧。

## 创建本地 Android 版本库镜像的思路

如果了解了 Repo 的实现，参考 [《Using Repo and Git》](http://source.android.com/source/git-repo.html) , 建立一个本地的 android 版本库镜像还是不难的：

下载 repo bootstrap 脚本

```
$ curl http://android.git.kernel.org/repo >~/bin/repo
$ chmod a+x ~/bin/repo
$ export PATH=$PATH:~/bin
```

提供 --mirror 参数调用 repo init ，建立 git 版本库克隆

```
$ repo init -u git://android.git.kernel.org/platform/manifest.git --mirror
```

使用 --morror 则下一步和源同步的时候，本地按照源的版本库组织方式进行组织，否则会按照 manifest.xml 指定的方式重新组织并检出到本地

开始和源同步

```
$ repo sync
```

修改 manifest ，修改 git 库地址，指向本地的 git 服务器

修改 platform/manifest.git 库中现有的 xml 文件，或者创建一个新的 xml 文件

将 git 的地址改为本地地址，提交并 push

本地 repo 镜像建立完毕之后，就可以在执行 repo init 时，使用本地更改后的 manifest 库，之后执行 repo sync 就是基于本地版本库进行同步了。

也可以改造 repo，使得不必为 repo 工具初始化，也在本地网络完成操作…



## Repo init 干了些什么？

实际上，得到客户使用 repo 的信息后，首先下载 repo 执行脚本开始研究。

```
curl http://android.git.kernel.org/repo >~/bin/repo
```

难道只有 600 行的 python 代码么？要是这样应该很简单的呀。可以看下来，却发现远非如此。



### Shell script or python？

首先 repo 脚本使用了一个魔法：从脚本第一行的 shebang 来看应该是 shell 脚本，但是满眼却都是 python 语法，怎么回事？

```
#!/bin/sh
## repo default configuration
##
REPO_URL='git://android.git.kernel.org/tools/repo.git'
REPO_REV='stable'
# Copyright (C) 2008 Google Inc.
   ...
magic='--calling-python-from-/bin/sh--'
"""exec" python -E "$0" "$@" """#$magic"
 
if __name__ == '__main__':
   import sys
  if sys.argv[-1] == '#%s' % magic:
     del sys.argv[-1]
del magic
```

魔法就在第 23 行，巧妙的通过 python 三引号字串写出了一个能被 python 和 shell script 都能理解的代码，以此为界，代码由 Shell 脚本进入了 Python 的世界。



### Bootstrap 和真正的 repo

通过 curl 下载的的 repo 并非完整的 repo 脚本，只是一个 bootstrap。当 repo 执行时，会负责下载完整的 repo 代码，并将控制权转移给真正的 repo。

通过 main 函数，可以看到 repo 运行的开始，就试图发现本地真正的完整的 repo 代码，以便移交控制权：

```
544 def main(orig_args):
545   main, dir = _FindRepo()
586   try:
587     os.execv(main, me)
```

其中 545 行的 _FindRepo() 会在当前目录开始向上递归查找 “.repo/repo/main.py”，如果找到则移交控制权（587行）。



### Repo bootstrap 脚本调用 init 只完成第一阶段的初始化

Repo 的 bootstrap 脚本只支持两个命令 help 和 init，而 init 也只完成 repo 版本库克隆（即安装 repo 完整工具），之后就转移控制权。

在 Repo bootstrap 执行 init 可以提供很多参数，但实际上第一阶段初始化，只用到两个参数（而且都有默认值）

参数：–repo-url=URL
 repo 工具本身的 git 库地址。缺省为：git://android.git.kernel.org/tools/repo.git

参数：–repo-branch=REVISION
 使用 repo 的版本库，即 repo git 库的分支或者里程碑名称。缺省为 stable



### 第二阶段的 repo init

执行第二阶段的 repo init，控制权已经移交给刚刚克隆出来的 repo git 库的脚本。

Repo git 库被克隆/检出到执行 repo init 命令当前目录下的 .repo/repo 子目录中，主要的执行脚本为 .repo/repo/main.py。main.py 接着执行 repo init 命令。

Repo 的代码组织的非常好，在 .repo/repo/subcmds/ 子目录下，是各个 repo 命令的处理脚本。repo init 的第二阶段脚本正是由 .repo/repo/subcmds/init.py 负责执行的。第二阶段主要完成：

克隆由 -u 参数提供的 manifest Git 库，如克隆 android 库时：

```
$ repo init -u git://android.git.kernel.org/platform/manifest.git
```

如果不提供 -b REVISION 或者 –manifest-branch=REVISION参数，则检出 manifest Git 库的 master 分支

如果不提供 -m NAME.xml 或者 –manifest-name=NAME.xml 参数，则使用缺省值 default.xml

如果提供 –mirror 参数，则后续同步操作会有相应的体现



## Repo start 干了些什么？

Android 源码网站在介绍 repo 的使用模型中，有一个图片： http://source.android.com/images/git-repo-1.png , 介绍了 repo 的使用流程。其中 “repo start” 是紧接着 “repo sync” 后的第一个动作。那么这个动作是干什么的呢？

得益于 repo 对 git 操作的封装，”repo start” 命令的处理代码只有区区 68 行。

```
37   def Execute(self, opt, args):
 41     nb = args[0]
 47     projects = []
 48     if not opt.all:
 49       projects = args[1:]
 54     all = self.GetProjects(projects)
 57     for project in all:
 59       if not project.StartBranch(nb):
 60         err.append(project)
```

看到第 59 行了么，就是对 repo 同步下来的项目的多个 Git 版本库，逐一执行 project.StartBranch 操作。 nb 是 repo start 的第一个参数，即分支名称。

关于 StartBranch 的代码，在 project.py 中：

```
 857   def StartBranch(self, name):
 858     """Create a new branch off the manifest's revision.
 859     """
894     if GitCommand(self,
 895                   ['checkout', '-b', branch.name, revid],
 896                   capture_stdout = True,
 897                   capture_stderr = True).Wait() == 0:
 898       branch.Save()
 899       return True

```

原来如此， repo start <branch_name> 就是逐一为各个版本库创建工作分支，以便在此分支下进行工作。

读者可以按图索骥，找到 repo 各个命令的实现，破解心中的疑惑。

 

 

**repo详解**

<http://www.360doc.com/content/14/0220/17/97538_354256755.shtml>

# 1 repo介绍

Android 使用 Git 作为代码管理工具，开发了 Gerrit 进行代码审核以便更好的对代码进行集中式管理，还开发了 Repo 命令行工具，对 Git 部分命令封装，将百多个 Git 库有效的进行组织。

## 1.1  清单库文件介绍

一个清单库可以包含多个清单文件和多个分支，每个清单文件和分支都有对应的版本。清单文件以xml格式组织的。举个例子：

[![repo使用](file:///C:/Users/lenovo/AppData/Local/Temp/msohtmlclip1/01/clip_image002.jpg)](http://photo.blog.sina.com.cn/showpic.html#blogid=89f592f50100vpau&url=http://s15.sinaimg.cn/orignal/89f592f5hb015cab0dd9e)

Ø         remote元素，定义了名为korg的远程版本库，其库的基址为git：//172.16.1.31/

Ø         default元素，设置各个项目默认远程版本库为korg，默认的的分支为gingerbread-exdroid-stable。当然各个项目(project元素)还可以定义自己的remote和revision覆盖默认的配置

Ø         project元素，用于定义一个项目，path属性表示在工作区克隆的位置，name属性表示该项目的远程版本库的相对路径

Ø         project元素的子元素copyfile，定义了项目克隆后的一个附件动作，从src拷贝文件到dest

## 1.2 下载repo代码

$mkdir android2.3.4

$cd android2.3.4

$git clone git://172.16.1.31/repo.git

​     于是在android目录下便有repo文件夹，里面包含了repo的源代码，里面有个repo脚本，用它来执行repo指令。

在本地开发的用户需要下载repo代码，在172.16.1.7服务器上开发的用户则不用下载repo代码，因为已经把repo脚本添加到了环境变量，执行repo init 就会附加的下载repo代码。

# 2 repo常用指令

备注：“*”表示新添加的指令

## 2.1 repo init (下载repo并克隆manifest)

Usage：

repo init –u URL [OPTIONS]

Options:

l         -u:指定一个URL，其连接到一个maniest仓库

l         -m:在manifest仓库中选择一个xml文件

l         -b:选择一个maniest仓库中的一个特殊的分支

命令repo init 要完成如下操作：

Ø         完成repo工具的完整下载，执行的repo脚本只是引导程序

Ø         克隆清单库manifest.git (地址来自于-u 参数)

Ø         克隆的清单库位于manifest.git中，克隆到本地.repo/manifests.清单.repo/manifest.xml只是符号链接，它指向.repo/manifests/default.xml

Ø         如果manifests中有多个xml文件，repo init 可以任意选择其中一个，默认选择是default.xml

Example：

repo init  -u git://172.16.1.31/manifest.git

|      |                                                              |
| ---- | ------------------------------------------------------------ |
|      | ![repo使用](file:///C:/Users/lenovo/AppData/Local/Temp/msohtmlclip1/01/clip_image003.png) |

在android2.3.4目录下面出现了.repo文件夹。

 

repo  init  -u git://172.16.1.31/manifest.git –m android.xml

选择的是android.xml里面的配置，.repo/manifest.xml便指向.repo/manifests/android.xml

## 2.2 repo sync(下载代码)

Usage:

repo sync [<project>…]

用于参照清单文件.repo/manifest.xml克隆并同步版本库。如果某个项目版本库尚不存在，则执行repo sync 命令相当于执行git clone，如果项目版本库已经存在，则相当于执行下面的两条指令：

l         git remote update

相当于对每一个remote源执行了fetch操作

l         git rebase origin/branch

针对当前分支的跟踪分支执行rebase操作。

Example:

repo sync

[![repo使用](file:///C:/Users/lenovo/AppData/Local/Temp/msohtmlclip1/01/clip_image005.jpg)](http://photo.blog.sina.com.cn/showpic.html#blogid=89f592f50100vpau&url=http://s2.sinaimg.cn/orignal/89f592f5hb015cf6250c1)

也可以选择克隆其中的一个项目:

repo sync platform/build

## 2.3 repo start(创建并切换分支)

Usage:

repo start  <newbranchname> [--all | <project>…]

​    刚克隆下来的代码是没有分支的,repo start实际是对git checkout –b 命令的封装。为指定的项目或所有项目（若使用—all参数），以清单文件中为设定的分支，创建特性分支。这条指令与git checkout –b 还是有很大的区别的，git checkout –b 是在当前所在的分支的基础上创建特性分支，而repo start是在清单文件设定分支的基础上创建特性分支。

Example：

  repo start  stable  --all

假设清单文件中设定的分支是gingerbread-exdroid-stable，那么执行以上指令就是对所有项目，在gingerbread-exdroid-stable的基础上创建特性分支stable。

  repo start  stable  platform/build platform/bionic

假设清单文件中设定的分支是gingerbread-exdroid-stable，那么执行以上指令就是对platform/build、platform/bionic项目，在gingerbread-exdroid-stable的基础上创建特性分支stable

​    

## 2.4 repo checkout(切换分支)

 Usage：

repo checkout <branchname>  [<project>…]

实际上是对git checkout 命令的封装，但不能带-b参数，所以不能用此命令来创建特性分支。

Example：

repo checkout crane-dev 

repo checkout crane-dev  platform/build  platform/bionic

## 2.5 repo branches(查看分支)

Usage：

repo branches [<project>…]

Example：

repo branches 

repo branches platform/build platform/bionic

 

## 2.6 repo diff(查看工作区文件差异)

 Usage：

repo diff [<project>…]

   实际是对git diff 命令的封装,用于分别显示各个项目工作区下的文件差异。

Example：

repo diff                            ---查看所有项目

repo diff platform/build platform/bionic  ---只查看其中两个项目

## 2.7 repo stage(把文件添加到index表中)

​     实际是对git add --interactive命令的封装、用于挑选各个项目工作区中的改动以加入暂存区。

Usage：

repo stage -i [<project>…]

​    -i代表git add --interactive命令中的--interactive，给出个界面供用户选择

## 2.8 repo prune(删除已经合并分支)

   实际上是对git branch –d命令的封装，该命令用于扫面项目的各个分支，并删除已经合并的分支，用法如下：

repo prune [<project>…]

 

## 2.9 repo abandon(删除指定分支)

   实际上是对git branch –D 命令的封装，用法如下：

repo abandon <branchname> [<project>…]

## 2.10 repo status(查看文件状态)

实际上是对git diff-index、git diff-filse命令的封装，同时显示暂存区的状态和本地文件修改的状态

$repo/repo status platform/bionic

![repo使用](file:///C:/Users/lenovo/AppData/Local/Temp/msohtmlclip1/01/clip_image006.png)

以上的实例输出显示了platform/bionic项目分支的修改状态

Ø         每个小节的首行显示羡慕名称，以及所在分支的名称

Ø         第一个字母表示暂存区的文件修改状态

l         -:没有改变

l         A:添加（不在HEAD中，在暂存区中）

l         M：修改（在HEAD中，在暂存区中，内容不同）

l         D:删除（在HEAD中，不在暂存区）

l         R：重命名（不在HEAD中，在暂存区，路径修改）

l         C：拷贝（不在HEAD中，在暂存区，从其他文件拷贝）

l         T：文件状态改变（在HEAD中，在暂存区，内容相同）

l         U：未合并，需要冲突解决

Ø         第二个字母表示工作区文件的更改状态

l         -：新/未知（不在暂存区，在工作区）

l         m：修改（在暂存区，在工作区，被修改）

l         d：删除（在暂存区，不在工作区）

Ø         两个表示状态的字母后面，显示文件名信息。如果有文件重名还会显示改变前后的文件名及文件的相似度

## 2.11 *repo remote(设置远程仓库)

Usage:

repo remote add <remotename>  <url> [<project>…] 

repo remote rm <remotename>  [<project>…]

Example:

repo remote add org ssh://172.16.1.31/git_repo

这个指令是根据xml文件添加的远程分支，方便于向服务器提交代码，执行之后的build目录下看到新的远程分支org：

![repo使用](file:///C:/Users/lenovo/AppData/Local/Temp/msohtmlclip1/01/clip_image007.png)

删除远程仓库：

$repo  remote  rm  org

## 2.12 *repo push

repo push org

   这是新添加的指令，用于向服务器提交代码，使用方法：

repo push <remotename> [--all |<project>…]

repo会自己查询需要向服务器提交的项目并提示用户。

## 2.13repo forall

 Usage：

repo forall [<project>…] –c <command>

迭代器，可以在所有指定的项目中执行同一个shell指令

 Options：

l         -c:后面所带的参数着是shell指令

l         -p:在shell指令输出之前列出项目名称

l         -v:列出执行shell指令输出的错误信息

 additional environment variables:

l         REPO_PROJECT:指定项目的名称

l         REPO_PATH:指定项目在工作区的相对路径

l         REPO_REMOTE:指定项目远程仓库的名称

l         REPO_LREV:指定项目最后一次提交服务器仓库对应的哈希值

l         REPO_RREV:指定项目在克隆时的指定分支，manifest里的revision属性

 另外，如果-c后面所带的shell指令中有上述环境变量，则需要用单引号把shell指令括起来。

### 3.13.1 添加的环境变量

 



repo forall –c ‘echo $REPO_PROJECT’

|                                                              |
| ------------------------------------------------------------ |
|                                                              |
| ![repo使用](file:///C:/Users/lenovo/AppData/Local/Temp/msohtmlclip1/01/clip_image008.png) |

 

$repo forall  –c ‘echo $REPO_PATH’

|      |      |
| ---- | ---- |
|      |      |

 

 

### 3.13.2 merge(合并多个分支)

​    把所有项目多切换到master分支，执行以下指令将topic分支合并到master分支

 



repo forall –p –c git merge topic

|      |      |
| ---- | ---- |
|      |      |

### 3.13.3 tag(打标签)

在所有项目下打标签

repo forall –c git tag crane-stable-1.6

### 3.13.4 remote (设置远程仓库)

引用环境变量REPO_PROJECT添加远程仓库：

repo forall –c ‘git remote add korg ssh://xiong@172.16.31/$REPO_PROJECT.git’

删除远程仓库：

repo forall –c git remote add korg

### 3.13.5 branch(创建特性分支)

repo forall –c git branch crane-dev

repo forall –c git checkout –b crane-dev

# 3 repo的额外命令集

## 3.1 repo grep

相当于对git grep 的封装，用于在项目文件中进行内容查找

## 3.2 repo manifest

显示manifest文件内容

Usage:

repo manifest –o android.xml

## 3.3 repo version

显示repo的版本号

## 3.4 repo upload

repo upload相当于git push，但是又有很大的不同。它不是将版本库改动推送到克隆时的远程服务器，而是推送到代码审核服务器(Gerrit软件架设)的特殊引用上，使用SSH协议。代码审核服务器会对推送的提交进行特殊处理，将新的提交显示为一个待审核的修改集，并进入代码审查流程，只有当审核通过后，才会合并到官方正式的版本库中。

因为全志没有代码审核服务器，所以这条指令用不到。

 Usage：

repo upload [--re --cc] {[<project>]… | --replace <project>}

 Options:

l         -h, --help:显示帮助信息

l         -t:发送本地分支名称到Gerrit代码审核服务器

l         --replace:发送此分支的更新补丁集

l         --re=REVIEWERS:要求指定的人员进行审核

l         --cc=CC:同时发送通知到如下邮件地址

## 3.5 repo download

主要用于代码审核者下载和评估贡献者提交的修订

Usage

repo download {project change [patchset]}…

## 3.6 repo selfupdate

​    用于repo自身的更新

参考：

<http://wenku.baidu.com/view/672c8faddd3383c4bb4cd257.html>

 

# 4 添加的remote指令

   在sumcmds中添加remote.py,程序如下：

\# Copyright (C) 2009 The Android Open Source Project

\#

\# Licensed under the Apache License, Version 2.0 (the "License");

\# you may not use this file except in compliance with the License.

\# You may obtain a copy of the License at

\#

\#      http://www.apache.org/licenses/LICENSE-2.0

\#

\# Unless required by applicable law or agreed to in writing, software

\# distributed under the License is distributed on an "AS IS" BASIS,

\# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

\# See the License for the specific language governing permissions and

\# limitations under the License.

 

import sys

from color import Coloring

from command import Command

from progress import Progress

 

class Remote(Command):

  common = True

  helpSummary = "View current topic branches"

  helpUsage = """

%prog add <remotebranchname> <url> [<project>...]

​       %prog rm  <remotebranchname> [<project>...]

 

\--------------

"""

  def str_last(self ,string):

​     for c in string:

​         last=c

​     return last

 

  def Execute(self, opt, args):

​    if not args:

​      print >>sys.stderr, "error:..........wrong command........"

​      print >>sys.stderr, "Usage:repo remote add <remotebranchname> <url> [<project>...]"

​      print >>sys.stderr, "      repo remote rm  <remotebranchname> [<project>...] "          

​      print >>sys.stderr, "................................"

​      return

 

​    err = []

​    operate=args[0]

​    \#url = args[2]

   \# branch_name=args[1]

​    if operate == "rm":

​       if not len(args) >=2:

​         print >>sys.stderr, "error:miss remotebrancname"

​         return

 

​       branch_name=args[1]

​       projects = args[2:]

​    elif operate == "add":

​       if not len(args) >=3:

​         print >>sys.stderr, "error:miss remotebranchname or url"

​         return

 

​       branch_name=args[1]

​       projects = args[3:]

​    else:

​       print >>sys.stderr, "error: the operand is add or rm "

​       return

​     

​    all = self.GetProjects(projects)

   \# print >>sys.stderr, all

​    pm = Progress('remote %s' % operate, len(all))

​    for project in all:

​       if operate == "add":

​          if self.str_last(args[2])=="/":

​             url = args[2]+project.name+'.git'

​          else :

​             url = args[2]+'/'+project.name+'.git'

​       else:

​         url = ""

 

​       pm.update() 

​       if not project.Remote(operate,branch_name,url):

​         err.append(project)

​    pm.end()

​       

​    if err:

​      if len(err) == len(all):

​        print >>sys.stderr, 'error: no project remote  %s %s' % (operate,branch_name)  

​      else:

​        for p in err:

​          print >>sys.stderr,\

​            "error: %s/: cannot remote %s %s " \

​            % (p.relpath, operate,branch_name)

​      sys.exit(1)

 

在preject.py中添加Remote（operate,branch_name,url）方法：

   def Remote(self,operate,branch_name,url):

​     """Prune  topic branches already merged into upstream.

​     """

​     if url=="":   #rm

​       return GitCommand(self,

​                         ['remote', operate, branch_name],

​                         capture_stdout = True,

​                         capture_stderr = True).Wait() == 0

 

​     else:  #add

​       return GitCommand(self,

​                         ['remote', operate, branch_name,url],

​                         capture_stdout = True,

​                         capture_stderr = True).Wait() == 0

 

[5  添加push指令](http://blog.sina.com.cn/s/blog_89f592f50100vpau.html#SinaEditor_Temp_FontName)

 在subcmds中添加push.py,代码如下：

 \#

\# Copyright (C) 2010 JiangXin@ossxp.com

\#

\# Licensed under the Apache License, Version 2.0 (the "License");

\# you may not use this file except in compliance with the License.

\# You may obtain a copy of the License at

\#

\#      http://www.apache.org/licenses/LICENSE-2.0

\#

\# Unless required by applicable law or agreed to in writing, software

\# distributed under the License is distributed on an "AS IS" BASIS,

\# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

\# See the License for the specific language governing permissions and

\# limitations under the License.

 

import copy

import re

import sys

 

from command import InteractiveCommand

from editor import Editor

from error import UploadError, GitError

from project import ReviewableBranch

 

def _ConfirmManyUploads(multiple_branches=False):

  if multiple_branches:

​    print "ATTENTION: One or more branches has an unusually high number of commits."

  else:

​    print "ATTENTION: You are uploading an unusually high number of commits."

  print "YOU PROBABLY DO NOT MEAN TO DO THIS. (Did you rebase across branches?)"

  answer = raw_input("If you are sure you intend to do this, type 'yes': ").strip()

  return answer == "yes"

 

def _die(fmt, *args):

  msg = fmt % args

  print >>sys.stderr, 'error: %s' % msg

  sys.exit(1)

 

def _SplitEmails(values):

  result = []

  for str in values:

​    result.extend([s.strip() for s in str.split(',')])

  return result

 

class Push(InteractiveCommand):

  common = True

  helpSummary = "Upload changes for code review"

  helpUsage="""

%prog <remotebranchname> {[<project>]... }

"""

  helpDescription = """

The '%prog' command is used to send changes to the Gerrit Code

Review system.  It searches for topic branches in local projects

that have not yet been published for review.  If multiple topic

branches are found, '%prog' opens an editor to allow the user to

select which branches to upload.

 

'%prog' searches for uploadable changes in all projects listed at

the command line.  Projects can be specified either by name, or by

a relative or absolute path to the project's local directory. If no

projects are specified, '%prog' will search for uploadable changes

in all projects listed in the manifest.

 

If the --reviewers or --cc options are passed, those emails are

added to the respective list of users, and emails are sent to any

new users.  Users passed as --reviewers must already be registered

with the code review system, or the upload will fail.

 

If the --replace option is passed the user can designate which

existing change(s) in Gerrit match up to the commits in the branch

being uploaded.  For each matched pair of change,commit the commit

will be added as a new patch set, completely replacing the set of

files and description associated with the change in Gerrit.

 

Configuration

\-------------

review.URL.autoupload:

To disable the "Upload ... (y/n)?" prompt, you can set a per-project

or global Git configuration option.  If review.URL.autoupload is set

to "true" then repo will assume you always answer "y" at the prompt,

and will not prompt you further.  If it is set to "false" then repo

will assume you always answer "n", and will abort.

 

review.URL.autocopy:

 

To automatically copy a user or mailing list to all uploaded reviews,

you can set a per-project or global Git option to do so. Specifically,

review.URL.autocopy can be set to a comma separated list of reviewers

who you always want copied on all uploads with a non-empty --re

argument.

 

review.URL.username:

 

Override the username used to connect to Gerrit Code Review.

By default the local part of the email address is used.

 

The URL must match the review URL listed in the manifest XML file,

or in the .git/config within the project.  For example:

 

  [remote "origin"]

​    url = git://git.example.com/project.git

​    review = http://review.example.com/

 

  [review "http://review.example.com/"]

​    autoupload = true

​    autocopy = johndoe@company.com,my-team-alias@company.com

 

References

\----------

 

Gerrit Code Review:  http://code.google.com/p/gerrit/

 

"""

  def _SingleBranch(self, opt, branch):

​    project = branch.project

​    name = branch.name

​    remote = project.GetBranch(name).remote

 

​    key = 'review.%s.autoupload' % remote.review

​    answer = project.config.GetBoolean(key)

 

​    if answer is False:

​      _die("upload blocked by %s = false" % key)

 

​    if answer is None:

​      date = branch.date

​      list = branch.commits

 

​      print 'Upload project %s/:' % project.relpath

​      print '  branch %s (- commit%s, %s):' % (

​                    name,

​                    len(list),

​                    len(list) != 1 and 's' or '',

​                    date)

​      for commit in list:

​        print '         %s' % commit

 

​      pushurl = project.manifest.manifestProject.config.GetString('repo.pushurl')

​      sys.stdout.write('to %s (y/n)? ' % (pushurl and 'server: ' + pushurl or 'remote') )

​      answer = sys.stdin.readline().strip()

​      answer = answer in ('y', 'Y', 'yes', '1', 'true', 't')

 

​    if answer:

​      self._UploadAndReport(opt, [branch])

​    else:

​      _die("upload aborted by user")

 

  def _MultipleBranches(self, opt,remoebranch ,pending):

​    projects = {}

​    branches = {}

 

​    script = []

​    script.append('# Uncomment the branches to upload:')

​    for project, avail in pending:

​      script.append('#')

​      script.append('# project %s/:' % project.relpath)

 

​      b = {}

​      for branch in avail:

​        name = branch.name

​        date = branch.date

​        list = branch.commits

​       \# print >>sys.stdout, name

​        

​        if b:

​          script.append('#')

​        script.append('  branch %s (- commit%s, %s):' % (    ##########3

​                      name,

​                      len(list),

​                      len(list) != 1 and 's' or '',

​                      date))

​        for commit in list:

​          script.append('#         %s' % commit)

​        b[name] = branch

 

​      projects[project.relpath] = project

​      branches[project.name] = b

​    script.append('')

 

  \#  script = Editor.EditString("\n".join(script)).split("\n")

 

​    project_re = re.compile(r'^#?\s*project\s*([^\s]+)/:$')

​    branch_re = re.compile(r'^\s*branch\s*([^\s(]+)\s*\(.*')

 

​    project = None

​    todo = []

 

​    for line in script:

​      m = project_re.match(line)

​      if m:

​        name = m.group(1)

​        project = projects.get(name)

​        if not project:

​          _die('project %s not available for upload', name)

​        continue

 

​      m = branch_re.match(line)

​      if m:

​        name = m.group(1)

​        if not project:

​          _die('project for branch %s not in script', name)

​        branch = branches[project.name].get(name)

​        if not branch:

​          _die('branch %s not in %s', name, project.relpath)

​        todo.append(branch)

​    if not todo:

​      _die("nothing uncommented for upload")

 

​    self._UploadAndReport(opt, remoebranch,todo)

 

  def _UploadAndReport(self, opt,remoebranch,todo):

​    have_errors = False

​    for branch in todo:

​      try:

​        \# Check if there are local changes that may have been forgotten

​        if branch.project.HasChanges():

​            key = 'review.%s.autoupload' % branch.project.remote.review

​            answer = branch.project.config.GetBoolean(key)

 

​            \# if they want to auto upload, let's not ask because it could be automated

​            if answer is None:

​                sys.stdout.write('Uncommitted changes in ' + branch.project.name + ' (did you forget to amend?). Continue uploading? (y/n) ')

​                a = sys.stdin.readline().strip().lower()

​                if a not in ('y', 'yes', 't', 'true', 'on'):

​                    print >>sys.stderr, "skipping upload"

​                    branch.uploaded = False

​                    branch.error = 'User aborted'

​                    continue

 

​        branch.project.UploadNoReview(opt, remoebranch,branch=branch.name)

​        branch.uploaded = True

​      except UploadError, e:

​        branch.error = e

​        branch.uploaded = False

​        have_errors = True

​      except GitError, e:

​        print >>sys.stderr, "Error: "+ str(e)

​        sys.exit(1)

 

​    print >>sys.stderr, ''

​    print >>sys.stderr, '--------------------------------------------'

 

​    if have_errors:

​      for branch in todo:

​        if not branch.uploaded:

​          print >>sys.stderr, '[FAILED] %-15s %-15s  (%s)' % (

​                 branch.project.relpath + '/', \

​                 branch.name, \

​                 branch.error)

​      print >>sys.stderr, ''

 

​    for branch in todo:

​        if branch.uploaded:

​          print >>sys.stderr, '[OK    ] %-15s %s' % (

​                 branch.project.relpath + '/',

​                 branch.name)

 

​    if have_errors:

​      sys.exit(1)

 

  def Execute(self, opt, args):

​    

​    if len(args)==0:

​      print >>sys.stdout,"error:miss remotebranchname"

​      print >>sys.stdout, "Usage:repo push <remotebranchname> [<project>...]"

​      return

​    project_list = self.GetProjects(args[1:])

​    pending = []

 

​    remoebranch=args[0]

​    \# if not create new branch, check whether branch has new commit.

​    for project in project_list:

​      if (project.GetUploadableBranch(project.CurrentBranch) is None):

​        continue

​      branch = project.GetBranch(project.CurrentBranch)

​      

​      rb = ReviewableBranch(project, branch, branch.LocalMerge)

​      pending.append((project, [rb]))

 

​    \# run git push

​    if not pending:

​      print >>sys.stdout, "no branches ready for upload"

   \# elif len(pending) == 1 and len(pending[0][1]) == 1:

​     \# self._SingleBranch(opt, pending[0][1][0])

​    else:

​      self._MultipleBranches(opt,remoebranch ,pending)

 

  在preject.py中添加如下方法：UploadNoReview(opt, remoebranch,branch=branch.name)

   def UploadNoReview(self, opt, remoebranch,branch=None):

​    """If not review server defined, uploads the named branch directly to git server.

​    """

​    \#print >>sys.stdout, branch

​    now_branch=branch

​    if branch is None:

​      branch = self.CurrentBranch

​    if branch is None:

​      raise GitError('not currently on a branch')

 

​    branch = self.GetBranch(branch)

 

​    if not branch.LocalMerge:

​      raise GitError('branch %s does not track a remote' % branch.name)

 

   \# if opt.new_branch:

   \#   dest_branch = branch.name

   \# else:

​    dest_branch = branch.merge

 

​    if dest_branch.startswith(R_TAGS):

​      raise GitError('Can not push to TAGS (%s)! Run repo push with --new flag to create new feature branch.' % dest_branch)

​    if not dest_branch.startswith(R_HEADS):

​      dest_branch = R_HEADS + dest_branch

 

​    if not branch.remote.projectname:

​      branch.remote.projectname = self.name

​      branch.remote.Save()

 

​    \# save git config branch.name.merge

   \## if opt.new_branch:

​    \#  branch.merge = dest_branch

​    \#  branch.Save()

 

​    ref_spec = '%s:%s' % (R_HEADS + branch.name, dest_branch)

​    pushurl = self.manifest.manifestProject.config.GetString('repo.%s.pushurl'

​              % branch.remote.name)

​    if not pushurl:

​      pushurl = self.manifest.manifestProject.config.GetString('repo.pushurl')

​    if not pushurl:

​      pushurl = branch.remote.name

​    else:

​      pushurl = pushurl.rstrip('/') + '/' + self.name

​      remote = self.manifest.remotes.get(branch.remote.name)

​      if remote and remote.autodotgit is not False:

​        pushurl += ".git"

 

​    cmd = ['push']

​    \#print >>sys.stdout, now_branch+'now'

​    cmd.append(remoebranch)

​    cmd.append(now_branch)

​    print >>sys.stdout, "push"+" "+self.name+':'

​    if GitCommand(self, cmd).Wait() != 0:

​      raise UploadError('Upload failed')

 

​    if branch.LocalMerge and branch.LocalMerge.startswith('refs/remotes'):

​      self.bare_git.UpdateRef(branch.LocalMerge,

​                              R_HEADS + branch.name)

 