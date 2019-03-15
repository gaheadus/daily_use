# git
- [概念](#概念)  
- [git命令,摘要](#git命令摘要)  
    - [新建代码库](#一新建代码库)  &emsp;&emsp;  [配置](#二配置)  &emsp;&emsp;  [增加/删除/修改文件](#三增加删除修改文件)  &emsp;&emsp;  [代码提交](#四代码提交)  &emsp;&emsp;  [分支](#五分支)  
    - [标签](#六标签)  &emsp;&emsp;  [查看信息](#七查看信息)  &emsp;&emsp;  [远程操作](#八远程操作)  &emsp;&emsp;  [撤销](#九撤销)  &emsp;&emsp;  [其他](#十其他)  
- [patch的使用](#patch的使用)  
- [git学习网址](#git学习网址)  


## 概念
**1.1 基本概念：工作区、暂存区、本地仓库、远程仓库**  
1.工作区(workspace)：用文本编辑器打开文件能查看/修改文件内容，此时文件在工作目录；git checkout到不同分支时所在目录；文件状态：unstaged。*本地*。  
2.暂存区(Index/ Stage Area)：git add之后文件所在目录。文件状态：staged , uncommitted。*本地*。  
3.本地仓库(Repository)：git commit之后，文件所在目录。文件状态：committed。*本地*。  
4.远程仓库(Remote Repository)：git push/pull，公司服务器，公用。*远程*。  
工作区、暂存区、本地仓库都在本地机器上，远程仓库在远程服务器的另一台电脑上。  
有些资料上也称：工作目录、暂存目录、本地目录、远程目录。  

![git的四个区域](https://github.com/gaheadus/daily_use/blob/master/Resources/git%E7%9A%84%E5%9B%9B%E4%B8%AA%E5%8C%BA%E5%9F%9F.png)

repository /rɪˈpɒzɪtərɪ/ n.  
①贮存处;存放处;仓库，A repository is a place where something is kept safely.  
A church in Moscow became a repository for police files. 莫斯科的一座教堂成为警方存放档案的地点。  
②博学者;无所不知的人，A repository of information is a person or group of people who know a lot of information about a particular place or subject.  
The repository of all important knowledge in a small town was the chief barman of the local pub. 小镇上最无所不知的人就是当地酒吧里的服务员领班。  

**概念：SHA、HEAD、分支**  
1.2 SHA  
SHA-1哈希值，作为指纹字符串。该字符串由40个十六进制字符(0-9及a-f)组成,如：  
24b9da6552252987aa493b52f8696cd6d3b00373  
Git 的工作完全依赖于这类指纹字符串，所以你会经常看到这样的哈希值。实际上，所有保存在Git数据库中的东西都是用此哈希值来作索引的，而不是靠文件名。  

1.3 HEAD  
HEAD：指向本地目录的一个已committed对象，指代当前分支最新的一次提交。  
每一次commit会在git分支树上产生一个节点(对象，HEAD)，对应到一个哈希值(SHA)。  
HEADˆ，意思是“HEAD的父提交”，也可以在ˆ后添加一个数字，例如d921970ˆ意思是“d921970的父提交”。  
SHA:d921970aadf03b3cf0e71becdaab3147ba71cdef，简写为d921970。  
也可以用\~指明祖先提交，\~也是指向第一父提交，所以 HEAD\~和HEADˆ是等价的。  
HEADˆˆˆ，最新提交的第一父提交的第一父提交的第一父提交。  
HEADˆˆˆ= HEAD\~\~\~= HEADˆ3 = HEAD\~3，  
d921970aadf03b3cf0e71becdaab3147ba71cdefˆ3 = d921970aadf03b3cf0e71becdaab3147ba71cdef \~3 = d921970ˆ3 = d921970 \~3  

小结：  
HEAD ← HEAD^ / HEAD\~ / HEAD^1 / HEAD\~1 ← HEAD^^ / HEAD\~\~ / HEAD^2 / HEAD\~2 ← …  
最新提交 ← 最新提交的父提交                 ← 最新提交的父提交的父提交   ← …  

Git有几个内置的符号索引指针：  
HEAD：永远指向当前分支的最近一次commit  
ORIG_HEAD：git reset或git merge后，原来的HEAD被存在这里  
FETCH_HEAD：git fetch后所有分支的头索引指针  
MERGE_HEAD：git merge时另一分支的头索引指针  
相对索引：HEAD^ HEAD\~ HEAD\~2 HEAD@{2}等  

ORIG_HEAD用于指向前一个操作状态，因此在git pull之后如果想得到pull的  
内容就可以：  
git diff ORIG_HEAD  
git diff --stat  用于生成统计信息。  
git diff --stat ORIG_HEAD  

1.4 分支  
一个git仓库，包含多个分支，默认包含master分支。参考《Pro Git》-- 3.Git分支  
[*返回目录*](#git)


## git命令,摘要  
### 一、新建代码库  
$ git init  //在当前目录下新建一个git代码库  
$ git init [project-name]  //新建一个目录，将其初始化为git代码库  
$ git clone [url]  //下载一个项目和它的整个代码历史  
[*返回目录*](#git)

### 二、配置  
Git的设置文件为.gitconfig，它可以在用户主目录下(全局配置)，也可以在项目目录下(项目配置)。  
$ git config --list  //显示当前的git配置  
$ git config -e [--global]  //编辑git配置文件  
$ git config [--global] user.name "name"  //设置提交代码时的用户信息，用户名  
$ git config [--global] user.email "email address"  //设置提交代码时的用户信息，邮箱  
[*返回目录*](#git)

### 三、增加/删除/修改文件  
$ git diff  //查看变更内容  
$ git add [file1] [file2] … //添加指定文件到暂存区  
$ git add [dir]  //添加指定目录到暂存区，包括子目录  
$ git add .  //添加当前目录下的所有文件到暂存区  
$ git add -p  //添加每个变化前，都会要求确认。对于同一个文件的多处变化，可以实现分次提交  
$ git rm [file1] [file2] …  //删除工作区文件，并且将这次删除放入暂存区  
$ git rm --cached [file]  //停止追踪指定文件，但该文件会保留在工作区  
$ git mv [file-original] [file-destination]  //移动文件/文件改名，并且将这个改名放入暂存区  
[*返回目录*](#git)

### 四、代码提交  
$ git commit [file1] [file2] … -m [message]  //提交暂存区的指定文件到仓库区  
$ git commit -m [message]  //提交暂存区到仓库区  
$ git commit -a  //提交工作区自上次commit之后的变化，直接到仓库区  
$ git commit -am "message" //相当于git add和git commit -m "message"。  
$ git commit -v  //提交时显示所有diff信息  
$ git commit --amend -m [message]  //使用一次新的commit，替代上一次提交。如果代码没有任何新变化，则用来改写上一次commit的提交信息。  
$ git commit --amend [file1] [file2]  //重做上一次commit，并包括指定文件的新变化  
[*返回目录*](#git)

### 五、分支  
$ git branch  //显示所有本地分支  
$ git branch -r //列出所有远程分支  
$ git branch -a //列出所有本地分支和远程分支  
$ git branch [branch-name] //新建一个分支，但依然停留在当前分支  
$ git branch --track [branch] [remote-branch] //新建一个分支，与指定的远程分支建立追踪关系  
$ git branch -d [branch-name] //删除分支。-d选项只能删除已经参与了合并的分支，对于未有合并的分支是无法删除的。如果想强制删除一个分支，可以使用-D选项。  
$ git checkout -b [branch-name] //新建一个分支，并切换到该分支  
$ git checkout [branch-name] //切换到指定分支，并更新工作区  
$ git checkout - //切换到上一个分支。"-"连字符代替分支名  
$ git merge [branch] //合并指定分支到当前分支  
$ git rebase <branch> //衍合指定分支到当前分支  
$ git cherry-pick [commit] //选择一个commit，合并进当前分支  

*创建空的分支：(执行命令之前记得先提交你当前分支的修改，否则会被强制删干净没得后悔)  
$git symbolic-ref HEAD refs/heads/[name]  
$rm .git/index  
$git clean -fdx  
[*返回目录*](#git)

### 六、标签  
$ git tag //列出所有本地标签  
$ git show [tag] //查看tag信息  
$ git tag <tag-name> //基于最新提交创建标签  
$ git tag -d <tag-name> //删除标签  
$ git tag -a [tag-name] -m 'yourMessage' //创建带注释的tag  
$ git push origin:refs/tags/[tag-name] //删除远程tag  
$ git push [remote] [tag] //提交指定tag  
$ git push [remote] --tags //提交所有tag   
$ git push origin --tags //上传本地tag到远程仓库  
$ git checkout -b [branch] [tag] //新建一个分支，指向某个tag  
$ git pull origin --tags //合并远程仓库的tag到本地  
[*返回目录*](#git)


### 七、查看信息  
$ git status //显示有变更的文件  
$ git log //显示当前分支的版本历史  
$ git log --pretty=oneline  
$ git log --oneline //显示更简短的SHA值,等效$ git log --abbrev-commit --pretty=oneline  
$ git log --graph  //以图表形式输出提交日志  
$ git log --stat //显示commit历史，以及每次commit发生变更的文件  
$ git log -S [keyword] //搜索提交历史，根据关键词  
$ git log [tag] HEAD --pretty=format:%s //显示某个commit之后的所有变动，每个commit占据一行  
$ git log [tag] HEAD --grep feature //显示某个commit之后的所有变动，其”提交说明”必须符合搜索条件  
$ git log --follow [file] //显示某个文件的版本历史，包括文件改名  
$ git whatchanged [file] //显示某个文件的版本历史，包括文件改名、文件模式、其他  
$ git log -4//查看分支最近4次修改记录  
$ git log -p//查看修改的具体内容，不仅显示commit日志，而且同时显示每次commit的代码改变。  
$ git log -2 -p//查看最近2次修改的具体内容。注意这里参数顺序-2 -p，不能把-p放到-2之前。  
$ git log -p filename //显示指定文件相关的每一次diff，查看某个文件filename修改的具体内容  
$ git log -5 --pretty --oneline //显示过去5次提交  
$ git log --before="1 days" //显示之前1天的版本  
$ git shortlog -sn //显示所有提交过的用户，按提交次数排序  
$ git blame [file] //显示指定文件是什么人在什么时间修改过  
$ git diff //显示暂存区和工作区的差异  
$ git diff --cached [file] //显示暂存区和上一个commit的差异  
$ git diff HEAD //显示工作区与当前分支最新commit之间的差异  
$ git diff [first-branch] …[second-branch] //显示两次提交之间的差异  
$ git diff --shortstat "@{0 day ago}" //显示今天你写了多少行代码  
$ git show [commit] //显示某次提交的元数据和内容变化  
$ git show --name-only [commit] //显示某次提交发生变化的文件  
$ git show [commit]:[filename] //显示某次提交时，某个文件的内容  
$ git reflog //查看当前仓库的操作日志。  
[*返回目录*](#git)


### 八、远程操作  
$ git remote -v //显示所有远程仓库  
$ git remote -vv  
$ git remote show [remote] //显示某个远程仓库的信息  
$ git remote add [shortname] [url] //增加一个新的远程仓库，并命名。这里只是为远程仓库建立一个别名，以后就可以使用这个别名代替远程仓库了。由于别名简短，使用起来更方便。例如git add my_branch https://github.com/gaheadus/test.git之后，所有使用远程仓库https://github.com/gaheadus/test.git的地方都可以用my_branch来代替，例如git push my_branch master:remote_new_branch与git push https://github.com/gaheadus/test.git master:remote_new_branch等价。  
$ git add my_branch https://github.com/gaheadus/test.git  
$ git add origin https://github.com/gaheadus/test.git  

$ git remote rm [name] //删除远程仓库  
$ git fetch [remote] //下载远程仓库的所有变动  
$ git pull [remote] [branch] //取回远程仓库的变化，并与本地分支合并  
$ git push [remote] [branch] //上传本地指定分支到远程仓库  
$ git push [remote] --force //强行推送当前分支到远程仓库，即使有冲突  
$ git push [remote] --all //推送所有分支到远程仓库  
$ git push <remote> :<branch/tag-name> //删除远程分支或标签  
$ git push --tags //？  

如果想把本地的某个分支test提交到远程仓库，并作为远程仓库的master分支，或者作为另外一个名叫test的分支，如下：  
$git push origin test:master  //提交本地test分支作为远程的master分支  
$git push origin test:test     //提交本地test分支作为远程的test分支  
格式: git push 远程仓库 本地分支:远程分支。如果本地分支留空如git push origin :branch则是删除远程分支。  

$ git push origin :[name] //删除远程分支。注意":"前面有空格  
$ git push origin --delete [name] //删除远程分支  
$ git push origin :heads/[name] //删除远程分支。注意":"前面有空格  

$ git remote set-url --push [name] [newUrl] //修改远程仓库  
$ git branch --set-upstream [branch] [remote-branch] //建立追踪关系，在现有分支与指定的远程分支之间  
[*返回目录*](#git)


### 九、撤销  
$ git reset --hard HEAD //撤销工作目录中所有未提交文件的修改内容  
$ git checkout HEAD <file> //撤销指定的未提交文件的修改内容  
$ git revert <commit> //撤销指定的提交  
$ git checkout [file] //恢复暂存区的指定文件到工作区  
$ git checkout [commit] [file] //恢复某个commit的指定文件到暂存区和工作区  
$ git checkout . //恢复暂存区的所有文件到工作区  
$ git reset [file] //重置暂存区的指定文件，与上一次commit保持一致，但工作区不变  
$ git reset --hard //重置暂存区与工作区，与上一次commit保持一致  
$ git reset [commit] //重置当前分支的指针为指定commit，同时重置暂存区，但工作区不变  
$ git reset --hard [commit] //重置当前分支的HEAD为指定commit，同时重置暂存区和工作区，与指定commit一致  
$ git reset --keep [commit] //重置当前HEAD为指定commit，但保持暂存区和工作区不变  
$ git revert [commit] //新建一个commit，用来撤销指定commit。后者的所有变化都将被前者抵消，并且应用到当前分支  
$ git stash //暂时将未提交的变化保存，稍后再恢复  
$ git stash pop //恢复之前保存的变化  
[*返回目录*](#git)


### 十、其他  
$ git archive //生成一个可供发布的压缩包  
[*返回目录*](#git)



## patch的使用  
**1.打patch、应用patch**  
打patch，生成补丁：  
$ git format-patch -n master \\生成最近n次commit的patch  
$ git format-patch master\~4..master\~2 \\生成master\~4和master\~2之间差异的patch  
$ git format-patch -s <sha> \\生成指定commit的patch，加签名  
应用补丁：  
$ git am 0001-trival-patch.patch  
git am用了git apply，用它打补丁会生成commit信息。如果出现错误  
previous rebase directory ../.git/rebase-apply still exists but mbox given  
可以用  
$ git am --abort  

前面方法用于**已经commit的**更改，如果是**用git diff生成的本地修改的**patch，则可以用下面方法生成本地修改的patch。  
打patch，生成补丁：  
$ git diff > diff.patch  
应用patch：  
$ git apply diff.patch  /  $ git apply --ignore-space-change --ignore-whitespace diff.patch  
或者  
$ patch -p1 < diff.patch  
当然这更像svn中的习惯，在git里反正是本地提交，提交的成本很低，所以可以先提交再生成patch。  

branch之间打patch用：  
$ git cherry-pick  

**git format-patch**  
git format-patch生成的一系列的patch  
法一：使用HEAD生成patch  
$ git format-patch HEAD^ <==最近的1次commit的patch  
$ git format-patch HEAD^^ <==最近的2次commit的patch  
$ git format-patch HEAD^^^ <==最近的3次commit的patch  
$ git format-patch HEAD^^^^ <==最近的4次commit的patch  
$ git format-patch HEAD^^^^^ <==不支持！！！！error！！！  
法二：根据commitSHA生成patch  
$ git format-patch commit  -----根据commit生成patch  
$ git format-patch commit1..commit4  -----结果是从commit2到4的patch  

git format-patch -1 = git format-patch HEAD^ ,等价操作  
git format-patch -2 = git format-patch HEAD^^  

**git am**  
$git am ~/patch/0001-trival-patch.patch  
如果贡献者也用 Git，且擅于制作 format-patch 补丁，那你的合并工作将会非常轻松。  
因为这些补丁中除了文件内容差异外，还包含了作者信息和提交消息。所以请鼓励贡献者用format-patch 生成补丁。对于传统的 diff 命令生成的补丁，则只能用 git apply 处理。  
对于 format-patch 制作的新式补丁，应当使用 git am命令。  

**使用git-am合并git format-patch生成的一系列的patch**  
$git am \~/patch/0001-trival-patch.patch  
在git使用当中，会有很多时候别人(供应商或者其他的开发人员)发过来一系列的patch，这些patch通常的是类似这样的名字：  
0001--JFFS2-community-fix-with-not-use-OOB.patch  
0002--Community-patch-for-Fix-mount-error-in.patch  
0003--partial-low-interrupt-latency-mode-for-ARM113.patch  
0004--for-the-global-I-cache-invalidation-ARM11.patch  
里面包含了提交的日志，作者，日期等信息。你想做的是把这些patch引入到你的  
代码库中，最好是也可以把日志也引入进来，方便以后维护用。  
传统的打patch方式是：patch -p1 < 0001--JFFS2-community-fix-with-not-use-OOB.patch  
这样来打patch，会把这些有用的信息丢失。  
由于这些patch显然是用git format-patch来生成的，所以用git的工具应该就可以很好的做好。  
git-am 就是作这件事情。  
在使用git-am之前，你要首先git am -abort一次，来放弃掉以前的am信息，这样才可以进行一次全新的am。不然会遇到这样的错误:.git/rebase-apply still exists but mbox given.  
git-am 可以一次合并一个文件，或者一个目录下所有的patch，或者你的邮箱目录下的patch.  
下面举两个例子：  
你现在有一个code base：small-src, 你的patch文件放在~/patch/0001-trival-patch.patch  
$git am \~/patch/0001-trival-patch.patch  
如果成功patch上去， 你就可以去喝杯茶了。  
如果失败了，git 会提示错误， 比如：  
error: patch failed: android/mediascanner.cpp:452  
error: android/mediascanner.cpp: patch does not apply  
这样你就需要先看看patch， 然后改改错误的这个文件，让这个patch能够patch上去。  

**冲突的解决**  
$git am *.patch  
来merge这些patch， 报错，Patch failed at 0001 add line这样我们看0001这个patch,原来patch需要的是some text, 而file里面是the text, 所以我们用编辑器把这行改成some text,  
$vi file  
$git apply 0001-add-line.patch  
$git add file  
$git am --resolved  
在解决完冲突以后， 比如用git add来让git知道你已经解决完冲突了。  
如果你发现这个冲突是无法解决的，要撤销整个am的东西。 可以运行git am -abort，  
如果你想只是忽略这一个patch，可以运行git am -skip来跳过这个patch.  

git format-patch -1     生成最后一个提交对应的patch文件。  
git am < patch          把一个patch文件加入git仓库中。  
git am --resolved       如果有冲突，在解决冲突后执行。  
git am --skip           放弃当前git am所引入的patch。  

**git diff > new.patch**  
也可以使用git diff来生成patch文件，如:git diff >new.patch。  

**git apply**  
$ git apply /tmp/patch-ruby-client.patch  
如果收到的补丁文件是用 git diff 或由其它 Unix 的 diff 命令生成，就该用 git apply 命令来应用补丁。假设补丁文件存在 /tmp/patch-ruby-client.patch，可以这样运行。  
[*返回目录*](#git)


### git学习  
#### git动画演示
https://learngitbranching.js.org/，git可视化，动画演示每一步的操作结果(推荐)  

**上述动画演示操作命令如下：**  
[*https://www.cnblogs.com/WMCH/p/7876056.html*](https://www.cnblogs.com/WMCH/p/7876056.html)  
上述动画演示操作命令如下：  
https://www.cnblogs.com/WMCH/p/7876056.html  
本地  
/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/  
基础篇  
git branch bugFix 建立bugFix分支  
git checkout bugFix 转换"当前分支"为bugFix  
git commit 提交,生成节点  
git checkout master  
git commit  
git merge bugFix 把bugFix合并到"当前分支master" 【merge from】  
git rebase master 把"当前分支bugFix"rebase到master下边！【rebase to】  
git rebase bugFix 分支已经是最新!  

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/  
高级篇  
1.HEAD  
git checkout C1  
git checkout master  
git commit  
git checkout C2  
HEAD一开始指向master，后指向C1，后指向master  
master提交后，HEAD随着master一起移动，并继续指向master  
后指向C2,这一步叫做"分离的HEAD状态"  
想完成此关，从 bugFix 分支中分离出 HEAD 并让其指向一个提交记录。  
答案：  
git checkout bugFix  
git checkout C4  

2.相对引用  
实际中，提交的节点哈希值不会是C0/C1/C2这么简单的数值，而是40位的...  
所以还是用相对引用简单。  
git checkout master^ 寻找指定提交记录的父提交  
git checkout master^^ 寻找指定提交记录的父父提交  
此外还可以把HEAD作为，相对引用的参照。  
git checkout HEAD^  
要完成此关，切换到 bugFix 的父节点。这会进入"分离 HEAD 状态"。  
答案：  
git checkout bugFix  
git checkout C4  
git checkout HEAD^  

3.相对引用2  
git branch -f master HEAD\~3  
将master分支强制指向 HEAD 的第 3 级父提交。  
答案：  
git checkout C1 HEAD指向C1  
git branch -f bugFix HEAD^ 分支bugFix指向HEAD的上一级  
git branch -f master C6 分支master直接指向C6  

4.版本回退  
\#git reset HEAD\~1  
Git 把 master 分支移回到 C1；现在我们的本地代码库根本就不知道有 C2 这个提交了。  
在reset后， C2 所做的变更还在，但是处于未加入暂存区状态。  

\#git revert HEAD  
虽然在你的本地分支中使用 git reset 很方便，但是这种“改写历史”的方法对大家一起使用的远程分支是无效的！  
为了撤销更改并分享给别人，我们需要使用 git revert。  
在我们要撤销的提交记录后面多出一个新提交！  
这是因为新提交记录 C2' 引入了更改 —— 这些更改刚好是用来撤销 C2 这个提交的。也就是说 C2' 的状态与 C1 是相同的。  
revert 之后就可以把你的更改推送到远程仓库与别人分享啦。  

如果C2后边还有C3,C4等等提交，C3,C4的修改不会动，仅仅是撤销C2的这次提交修改的内容！并在C4后边生成新的提交（撤销C2的修改）。  
要完成此关，分别撤销 local 分支和 pushed 分支上的最近一次提交。共需要撤销两个提交（每个分支一个）。  
记住 pushed 是远程分支，local 是本地分支 —— 这么说你应该知道用分别哪种方法了吧？  
git reset HEAD^  
git checkout pushed  
git revert HEAD  

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/  
移动提交记录篇  
"我想要把这个提交放到这里，那个提交放到刚才那个提交的后面"  
1.将一些提交复制到当前所在的位置（HEAD）下面。  
git cherry-pick <提交号>  
git cherry-pick C2 C4  
就会把他们抓过来放到当前分支下。  
答案：  
git cherry-pick C3 C4 C7  

2.图形交互式rebase  
你不清楚你想要的提交记录的哈希值时，rebase 加参数 --interactive （-i）  
Git 会打开一个 UI 界面，并列出将要被复制到目标分支的备选提交记录，  
它还会显示每个提交记录的哈希值和提交说明，提交说明有助于你理解这个提交进行了哪些更改。  

当 rebase UI界面打开时, 你能做3件事:  
\#调整提交记录的顺序（通过鼠标拖放来完成）  
\#删除你不想要的提交（点击切换 pick 的状态来完成，关闭就意味着你不想要这个提交记录）  
\#合并提交。它允许你把多个提交记录合并成一个。  

git rebase -i HEAD\~4  
可以对提交记录做排序，也可以删除某些提交。  
（命令的动作：从master到HEAD\~4，这整串分支，从HEAD\~4位置复制了一份）  

要通过本关, 做一次交互式的 rebase，整理成目标窗口中的提交顺序。  
记住，你随时都可以用 undo、reset 修正错误。  
答案：  
git rebase -i HEAD\~4  
之后删除C2，调整C4C5的顺序  

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/  
杂项  
1.只取一个提交记录  
本地栈式提交  
我正在解决某个特别棘手的 Bug，为了便于调试而在代码中添加了一些调试命令并向控制台打印了一些信息。  
这些调试和打印语句都在它们各自的提交记录里。  
最后我终于找到了造成这个 Bug 的根本原因，解决掉以后觉得沾沾自喜！  
最后就差把 bugFix 分支里的工作合并回 master 分支了。  
你可以选择通过 fast-forward 快速合并到 master 分支上，但这样的话 master 分支就会包含我这些调试语句了。  
你肯定不想这样，应该还有更好的方式……  

实际我们只要让 Git 复制解决问题的那一个提交记录就可以了。  
跟之前我们在“整理提交记录”中学到的一样，我们可以使用  
git rebase -i  
git cherry-pick  
来达到目的。  

$ git rebase -i HEAD\~3 忽略debug/print分支，只把bugFix分支移动到master下  
$ git merge master 这个时候，bugFix是"当前分支"，但master是bugFix的父节点...  
分支已经是最新啦  
$ git checkout master  
$ git merge master 写错  
分支已经是最新啦  
$ git merge bugFix 必须把"当前分支"调整为master之后，再操作合并。  


2.提交技巧 \#1：使用rebase -i  
你之前在 newImage 分支上进行了一次提交，然后又基于它创建了 caption 分支，然后又提交了一次。  
此时你想对的某个以前的提交记录进行一些小小的调整。  
比如设计师想修改一下 newImage 中图片的分辨率，尽管那个提交记录并不是最新的了。  

->先用 git rebase -i 将提交重新排序，然后把我们想要修改的提交记录挪到最前  
->然后用 git commit --amend 来进行一些小修改  
->接着再用 git rebase -i 来将他们调回原来的顺序  
->最后我们把 master 移到修改的最前端（用你自己喜欢的方法），就大功告成啦！  

当然完成这个任务的方法不止上面提到的一种（我知道你在看 cherry-pick 啦），  
最后有必要说明一下目标状态中的那几个' —— 我们把这个提交移动了两次，每移动一次会产生一个 '；  
而 C2 上多出来的那个是我们在使用了 amend 参数提交时产生的，所以最终结果就是这样了。  

也就是说，我在对比结果的时候只会对比提交树的结构，  
对于 ' 的数量上的不同，并不纳入对比范围内。  
只要你的 master 分支结构与目标结构相同，我就算你通过。  
$ git rebase -i HEAD^^ 调整c2c3，得到c3' c2'  
$ git commit --amend （修改c2'，得到c2''）  
$ git rebase -i HEAD^^ 调整c2'' c3'，得到c2''' c3''  
$ git checkout master  
$ git merge caption caption指向c3''，合并到master  

3.提交技巧 \#2：使用cherry-pick实现相同效果  
$ git checkout master   
$ git cherry-pick C2 把C2转到master分支下，得到C2'  
$ git commit --amend （修改c2'，得到c2''）  
$ git cherry-pick C3 把C3转到master分支下（c2''下），得到C3'  

4.git Tag  
相信通过前面课程的学习你已经发现了：  
分支很容易被人为移动，并且当有新的提交时，它也会移动。  
分支很容易被改变，大部分分支还只是临时的，并且还一直在变。  

有没有什么可以永远指向某个提交记录的标识呢，比如软件发布新的大版本，或者是修正一些重要的 Bug 或是增加了某些新特性，有没有比分支更好的可以永远指向这些提交的方法呢？  

更难得的是，它们并不会随着新的提交而移动。  
你也不能检出到某个标签上面进行修改提交，它就像是提交树上的一个锚点，标识了某个特定的位置。  

git tag v1 C1  
如果不指定C1，会加到HEAD指向的位置。  
在这个关卡中，按照目标建立两个标签，然后检出到 v1 上面，要注意你会进到分离 HEAD 的状态——这是因为不能直接在v1 上面做 commit。  

5.git describe  
Git Describe  
标签在代码库中起着“锚点”的作用，  
Git 为此专门设计的一个命令用来描述离你最近的锚点（也就是标签）。  

Git Describe 能帮你在提交历史中移动了多次以后找到方向；  
当你用 git bisect（一个查找产生 Bug 的提交记录的指令）找到某个提交记录时，  
或者是当你坐在你那刚刚度假回来的同事的电脑前时，可能会用到这个命令。  

git describe 的语法是：git describe <ref>  
<ref> 可以是任何能被 Git 识别成提交记录的引用，  
如果你没有指定的话，Git 会以你目前所检出的位置（HEAD）。  

它输出的结果是这样的：  
<tag>_<numCommits>_g<hash>  
tag 表示的是离 ref 最近的标签  
numCommits 是表示这个 ref 与 tag 相差有多少次提交记录  
hash 表示的是你所给定的 ref 所表示的提交记录哈希值的前几位。  
当 ref 提交记录上有某个标签时，则只输出标签名称  

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/  
1.多分支rebase  
2.选择父提交记录  
操作符 ^ 与 \~ 符一样，后面也可以跟一个数字。  
但是该操作符后面的数字与 \~ 后面的不同，并不是用来指定向上返回几代，  
而是指定合并提交记录的某个父提交。  
还记得前面提到过的一个合并提交有两个父提交吧，所以遇到这样的节点时该选择哪条路径就不是很清晰了。  
Git 默认选择合并提交的“第一个”父提交，在操作符 ^ 后跟一个数字可以改变这一默认行为。  

git checkout HEAD\~  
git checkout HEAD^2  
git checkout HEAD\~2  
链式：git checkout HEAD\~^2\~2  
git branch bugWork master^^2^ 在那个地方创建分支  

3.纠缠不清的分支  
现在我们的 master 分支是比 one、two 和 three 要多几个提交。  
出于某种原因，我们需要把 master 分支上最近的几次提交做不同的调整后，分别添加到各个的分支上。  
one 需要重新排序并删除 C5  
two 仅需要重排排序  
three 只需要提交一次。  

我的：  
$ git checkout three  
$ git merge C2  

$ git checkout C1  
$ git cherry-pick C4 C3 C2  

$ git checkout two  
$ git cherry-pick C5  
$ git cherry-pick C4' C3' C2'  

答案：  
$ git checkout one  
$ git cherry-pick C4 C3 C2  
$ git checkout two  
$ git cherry-pick C5 C4 C3 C2  
$ git branch -f three C2  
不用merge，而是用强制指向即可。  

远程  
/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/  
1. git clone 在本地创建一个远程仓库的拷贝  
在我们的本地仓库多了一个名为 origin/master 的分支, 这种类型的分支就叫远程分支。  

远程分得有一个特别的属性，在你检出时自动进入分离 HEAD 状态。  
Git 这么做是出于不能直接在这些分支上进行操作的原因, 你必须在别的地方完成你的工作,   
（更新了远程分支之后）再用远程分享你的工作成果。  
用 git clone 某个仓库时，Git 已经帮你把远程仓库的名称默认设置为 origin 了.  
git checkout origin/master  
git commit  
正如你所见，Git变成了分离 HEAD 状态，当添加新的提交时 origin/master 也不会更新。  
这是因为 origin/master 只有在远程仓库中相应的分支更新了以后才会更新。  

2. git fetch   
从远程仓库获取一次提交记录，并且远程分支origin/master会更新  
它不会更新你的 master 分支，也不会修改你磁盘上的文件。  
理解这一点很重要，因为许多开发人员误以为执行了 git fetch 以后，他们本地仓库就与远程仓库同步了。  
它可能已经将进行这一操作所需的所有数据都下载了下来，但是并没有修改你本地的文件。  
所以, 你可以将 git fetch 的理解为单纯的下载操作。  

3. git pull  
用 git fetch 获取远程的数据,  
再将这些变化更新到我们的工作当中。  
git cherry-pick o/master  
git rebase o/master  
git merge o/master  
等等  

由于先抓取更新再合并到本地分支，这个流程很常用，  
因此 Git 提供了一个专门的命令来完成这两个操作。  
它就是 git pull。  

4.模拟团队合作  
克隆一个远程仓库（用 git clone），  
再在刚创建的远程仓库中模拟一些修改，【模拟远程修改指令git fackTeamwork <分支名><提交次数>】  
然后在你自己的本地分支上做一些提交，  
再拉取远程仓库的变更。  
这看起来像是包含了好几节的课程。  

$ git clone  
local branch "master" set to track remote branch "o/master"  
$ git fakeTeamwork master 2  
$ git commit  
$ git fetch  
$ git merge o/master  

5. git push  
git push 负责将你的变更上传到指定的远程仓库，并在远程仓库上合并你的新提交记录。  
你可以将 git push 想象成发布你成果的命令！！！  
注意 —— git push 不带任何参数时的行为与 Git 的一个名为 push.default 的配置有关。  
它的默认值取决于你正使用的 Git 的版本，但是在教程中我们使用的是 upstream。  
这没什么太大的影响，但是在你的项目中进行推送之前，最好检查一下这个配置。  
远程仓库接收了 C2，  
远程仓库中的 master 分支也被更新到指向 C2 了，  
我们的远程分支 (o/master) 也同样被更新了。  
所有的分支都同步了！  

6.远程库提交历史的偏离  
假设你周一克隆了一个仓库，然后开始研发某个新功能。  
到周五时，你新功能开发测试完毕可以发布了。  
但是你的同事这周写了一堆代码，  
还改了许多你的功能中使用的 API，  
这些变动会导致你新开发的功能变得不可用。  
但是他们已经将那些提交推送到远程仓库了，  
因此你的工作就变成了基于项目旧版的代码，  
与远程仓库最新的代码不匹配了。  

这种情况下, git push 就不知道该如何操作了。  
如果你执行 git push，Git 应该让远程仓库回到星期一那天的状态吗？  
还是直接在新代码的基础上添加你的代码，  
异或由于你的提交已经过时而直接忽略你的提交？  

因为这情况（历史偏离）有许多的不确定性，Git 是不会允许你 push 变更的。  
实际上它会强制你先合并远程最新的代码，然后才能分享你的工作。  

方法：  
git fetch  
git rebase origin/master  
git push  
我们用 git fetch 更新了本地仓库中的远程分支，  
然后用 rebase 将工们的工作移动到最新的提交记录下，  
最后再用 git push 推送到远程仓库。  

其它的方法，merge  
尽管 git merge 不会移动你的工作（它会创建新的合并提交），  
但是它会告诉 Git 你已经合并了远程仓库的所有变更。  
这是因为远程分支现在是你本地分支的祖先，  
也就是说你的提交已经包含了远程分支的所有变化。  

git fetch  
git merge origin/master  
git push  
git fetch 更新了本地仓库中的远程分支，  
然后合并了新变更到我们的本地分支（为了包含远程仓库的变更），  
最后我们用 git push 把工作推送到远程仓库  

简化操作：  
git pull 就是 fetch 和 merge 的简写  
git pull --rebase 就是 fetch 和 rebase 的简写！  

要完成本关，你需要完成以下几步：  
克隆你的仓库  
模拟一次远程提交（fakeTeamwork）  
完成一次本地提交  
用 rebase 发布你的工作  

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/  
1.推送主分支  
在大型项目中开发人员通常会在（从 master 上分出来的）特性分支上工作，工作完成后只做一次集成。这跟前面课程的描述很相像（把 side 分支推送到远程仓库），不过本节我们会深入一些.  
但是有些开发人员只在 master 上做 push、pull —— 这样的话 master 总是最新的，始终与远程分支 (o/master) 保持一致。  
对于接下来这个工作流，我们集成了两个步骤：  
将特性分支集成到 master 上  
推送并更新远程分支  

这个关卡的 Boss 很厉害 —— 以下是通关提示：  
这里共有三个特性分支 —— side1 side2 和 side3  
我需要将这三分支按顺序推送到远程仓库  
因为远程仓库已经被更新过了，所以我们还要把那些工作合并回来  
$ git fetch C8拿回本地  
$ git rebase o/master side1 rebase to o/master from side1  
$ git rebase side1 side2  
$ git rebase side2 side3  
$ git rebase side3 master  
快速前进...  
$ git push  

2.合并远程仓库  
在开发社区里，有许多关于 merge 与 rebase 的讨论。  
以下是关于 rebase 的优缺点：  
优点: Rebase 使你的提交树变得很干净, 所有的提交都在一条线上  
缺点: Rebase 修改了提交树的历史  
比如, 提交 C1 可以被 rebase 到 C3 之后。  
这看起来 C1 中的工作是在 C3 之后进行的，  
但实际上是在 C3 之前。  
一些开发人员喜欢保留提交历史，因此更偏爱 merge。  
而其他人（比如我自己）可能更喜欢干净的提交树，于是偏爱 rebase。  

使用merge实现相同功能：  
$ git checkout master   
$ git pull C8拿回本地，并且origin/master指向它，master也指向它！  
快速前进...  
$ git merge side1  
$ git merge side2  
$ git merge side3  
$ git push  

3.远程追踪  
pull 操作时, 提交记录会被先下载到 o/master 上，之后再合并到本地的 master 分支。  
隐含的合并目标由这个关联确定的。  
push 操作时, 我们把工作从 master 推到远程仓库中的 master 分支(同时会更新远程分支 o/master) 。  
这个推送的目的地也是由这种关联确定的！  
master 和 o/master 的关联关系就是由分支的“remote tracking”属性决定的。  
master 被设定为跟踪 o/master  
这意味着为 master 分支指定了推送的目的地以及拉取后合并的目标。  
当你克隆仓库的时候, Git 就自动帮你把这个属性设置好了。  

有两种方法设置这个属性，  
第一种就是通过远程分支检出一个新的分支，执行:  
git checkout -b totallyNotMaster o/master  
就可以创建一个名为 totallyNotMaster 的分支，它跟踪远程分支 o/master。  

另一种方法就是使用：（这个命令更明确！）  
git branch -u o/master foo  
这样 foo 就会跟踪 o/master 了。  
如果当前就在 foo 分支上, 还可以省略 foo：  
git branch -u o/master  

答案：  
$ git checkout -b side o/master  
local branch "side" set to track remote branch "o/master"  
$ git commit  
$ git pull --rebase  
$ git push  

4.git push 参数  
在远程跟踪中，Git通过当前检出分支的属性来确定远程仓库以及要 push 的目的地。  
这是未指定参数时的行为，我们可以为 push 指定参数，语法是：  
git push <remote> <place>  
git push origin master  
切到本地仓库中的“master”分支，  
获取所有的提交，  
再到远程仓库“origin”中找到“master”分支，  
将远程仓库中没有的提交记录都添加上去，  
搞定之后告诉我。  

“place”参数告诉 Git 提交记录来自于 master, 要推送到远程仓库中的 master。  
它实际就是要同步的两个仓库的位置。  

例子：  
git checkout C0  
git push  
命令失败了，什么也没有发生!  
因为检出 HEAD 没有跟踪任何分支。  
git checkout C0  
git push origin master  
可以的  

5.git push 参数2  
如果来源和去向分支的名称不同呢？  
比如你想把本地的 foo 分支推送到远程仓库中的 bar 分支。  

git push origin <source>:<destination>  
这个参数实际的值是个 refspec，“refspec” 是一个自造的词，  
意思是 Git 能识别的位置（比如分支 foo 或者 HEAD\~1）  

如果你要推送到的目的分支不存在，Git 会在远程仓库中根据你提供的名称帮你创建这个分支！  

$ git push origin master^:foo  
$ git push origin foo:master  

6.git fetch 参数  
git fetch 的参数和 git push 极其相似。  
他们的概念是相同的，只是方向相反罢了（因为现在你是下载，而非上传）  

git fetch origin foo  
为何 Git 会将新提交放到 o/foo 而不是放到我本地的 foo 分支呢？  
本例中 Git 做了一些特殊处理，因为你可能在 foo 分支上的工作还未完成，你也不想弄乱它。  
fetch它不会更新你的本地的非远程分支, 只是下载提交记录（这样, 你就可以对远程分支进行检查或者合并了）。  

如果你觉得直接更新本地分支很爽，那你就用冒号分隔的 refspec 吧。  
不过，你不能在当前检出的分支上干这个事，但是其它分支是可以的。  
注意：  
source 现在指的是远程仓库中的位置，而 <destination> 才是要放置提交的本地仓库的位置。  
它与 git push 刚好相反，这是可以讲的通的，因为我们在往相反的方向传送数据。  
理论上虽然行的通，但开发人员很少这么做。  

如果参数分支不存在，就会新建。  
如果 git fetch 没有参数，它会下载所有的提交记录到各个远程分支……  

答案：  
$ git fetch origin master\~1:foo  
$ git fetch origin foo:master  
$ git checkout foo  
$ git merge master  

7.没有source的source  
如果 push 空 <source> 到远程仓库会如何呢？它会删除远程仓库中的分支！  
git push origin :foo  
我们通过给 push 传空值 source，成功删除了远程仓库中的 foo 分支, 这真有意思...  

如果 fetch 空 <source> 到本地，会在本地创建一个新分支。  
git fetch origin :bar  
很神奇吧！但无论怎么说, 这就是 Git！  

8.git pull 参数  
一样的。  
[*返回目录*](#git)