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


### git学习网址  
https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000  
https://learngitbranching.js.org/  
[*返回目录*](#git)