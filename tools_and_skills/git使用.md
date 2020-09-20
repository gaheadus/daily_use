# git
- [概念](#概念)  
- [git命令](#git命令)  
- [git学习](#git学习)  
- [repo](#repo)  
- [专题](#专题)  
- [网址收藏](#网址收藏)  

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
HEAD ← HEAD^ / HEAD\~ / HEAD\~1 ← HEAD^^ / HEAD\~\~ / HEAD\~2 ← HEAD^^^ / HEAD\~\~\~ / HEAD\~3  
\~和^的不同：\~后面可以加数字表示多级父提交,如HEAD\~3/ HEAD\~4，^后面不能加数字, HEAD^3没有意义。  

Git有几个内置的符号索引指针：  
HEAD：永远指向当前分支的最近一次commit  
ORIG_HEAD：git reset或git merge后，原来的HEAD被存在这里  
FETCH_HEAD：git fetch后所有分支的头索引指针  
MERGE_HEAD：git merge时另一分支的头索引指针  
相对索引：HEAD^ HEAD\~ HEAD\~2 HEAD@{2}等  

ORIG_HEAD用于指向前一个操作状态，因此在git pull之后如果想得到pull的内容可以使用如下命令：  
git diff ORIG_HEAD  
git diff --stat  用于生成统计信息。  
git diff --stat ORIG_HEAD  

1.4 分支  
一个git仓库，包含多个分支，默认包含master分支。参考《Pro Git》-- 3.Git分支  
[返回*概念*](#概念)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  


## git命令  
[新建代码库](#一新建代码库)  &emsp;&emsp;  [配置](#二配置)  &emsp;&emsp;  [增加/删除/修改文件](#三增加删除修改文件)  &emsp;&emsp;  [代码提交](#四代码提交)  &emsp;&emsp;  [分支](#五分支)  
[标签](#六标签)  &emsp;&emsp;  [查看信息](#七查看信息)  &emsp;&emsp;  [远程操作](#八远程操作)  &emsp;&emsp;  [撤销](#九撤销)  &emsp;&emsp;  [其他](#十其他)  
[*返回目录*](#git)    

### 一、新建代码库  
$ git init  //在当前目录下新建一个git代码库  
$ git init [project-name]  //新建一个目录，将其初始化为git代码库  
$ git clone [url]  //下载一个项目和它的整个代码历史  
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  

### 二、配置  
Git的设置文件为.gitconfig，它可以在用户主目录下(全局配置)，也可以在项目目录下(项目配置)。  
$ git config --list  //显示当前的git配置  
$ git config -e [--global]  //编辑git配置文件  
$ git config [--global] user.name "name"  //设置提交代码时的用户信息，用户名  
$ git config [--global] user.email "email address"  //设置提交代码时的用户信息，邮箱  
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  

### 三、增加/删除/修改文件  
$ git diff  //查看变更内容  
$ git add [file1] [file2] … //添加指定文件到暂存区  
$ git add [dir]  //添加指定目录到暂存区，包括子目录  
$ git add .  //添加当前目录下的所有文件到暂存区  
$ git add -p  //添加每个变化前，都会要求确认。对于同一个文件的多处变化，可以实现分次提交  
$ git rm [file1] [file2] …  //删除工作区文件，并且将这次删除放入暂存区  
$ git rm --cached [file]  //停止追踪指定文件，但该文件会保留在工作区  
$ git mv [file-original] [file-destination]  //移动文件/文件改名，并且将这个改名放入暂存区  
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  

### 四、代码提交  
$ git commit [file1] [file2] … -m [message]  //提交暂存区的指定文件到仓库区  
$ git commit -m [message]  //提交暂存区到仓库区  
$ git commit -a  //提交工作区自上次commit之后的变化，直接到仓库区  
$ git commit -am "message" //相当于git add和git commit -m "message"。  
$ git commit -v  //提交时显示所有diff信息  
$ git commit --amend -m [message]  //使用一次新的commit，替代上一次提交。如果代码没有任何新变化，则用来改写上一次commit的提交信息。  
$ git commit --amend --no-edit //--no-edit表示不想编辑提交信息，直接用以前的就行。  
$ git commit --amend [file1] [file2]  //重做上一次commit，并包括指定文件的新变化  

$ git commit -m "提交信息" --author "Authorname <authoremail@mydomain.com>" //指定提交的作者。单独为某个提交指定提交作者，不使用git config配置的默认值。  
提交的作者，和真实的提交者，可以不是同一个人。例如，执行git commit/ git push操作的是A，但是使用git commit时指定--author为B，这样在git log里看到的是作者B，而不是提交者A。  

我提交(commit)里的用户名和邮箱不对，如果这只是单个提交(commit)，修改它：  
$ git commit --amend --author "New Authorname <authoremail@mydomain.com>"  
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  

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
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  

### 六、标签  
git标签分为两种类型：轻量标签和附注标签。轻量标签是指向提交对象的引用，附注标签则是仓库中的一个独立对象。建议使用附注标签。  
创建轻量标签不需要传递参数，直接指定标签名称即可。  
创建附注标签时，参数a即annotated的缩写，指定标签类型，后附标签名。参数m指定标签说明，说明信息会保存在标签对象中。  
$ git tag [tag-name] //创建轻量标签。基于最新提交创建标签。  
$ git tag [tag-name] SHA //基于某个提交创建标签。如果不指定commit，默认在当前最新提交HEAD上打tag。  
$ git tag [tag-name] SHA -m "注释"  //给tag加注释  
$ git tag -a [tag-name] //创建附注标签  
$ git tag -a [tag-name] -m 'yourMessage'  
$ git tag -d [tag-name] //删除标签  
$ git tag //列出所有本地标签  
$ git tag -l "v0.1.\*"  //搜索符合模式的标签  
$ git show [tag] //查看tag信息  
$ git checkout -b [branch] [tag] //新建一个分支，指向某个tag  
$ git push [remote] [tag] //提交指定tag  
$ git push [remote] --tags //提交所有tag   
$ git push origin --tags //上传本地tag到远程仓库  
$ git push origin:refs/tags/[tag-name] //删除远程tag  
$ git pull origin --tags //合并远程仓库的tag到本地  
参考：https://git-scm.com/book/zh/v2/Git-%E5%9F%BA%E7%A1%80-%E6%89%93%E6%A0%87%E7%AD%BE  
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  


### 七、查看信息  
$ git status //显示有变更的文件  
$ git log //显示当前分支的版本历史  
$ **git log --graph**  //显示ASCII图形表示的提交历史和分支合并历史。推荐。  
&emsp;&emsp;&emsp;&emsp;\*表示一个commit， 注意不要管*在哪一条主线上  
&emsp;&emsp;&emsp;&emsp;|表示分支前进  
&emsp;&emsp;&emsp;&emsp;/表示分叉  
&emsp;&emsp;&emsp;&emsp;\\表示合入  
$ git log --graph --decorate  
$ git log --graph --decorate --pretty=format:"%H - %cn, %an : %s" --all  
$ git log --graph --decorate --oneline --all  
&emsp;&emsp;&emsp;&emsp;--decorate： 标记会让git log显示每个commit的引用  
&emsp;&emsp;&emsp;&emsp;--simplify-by-decoration：只显示被branch或tag引用的commit  
&emsp;&emsp;&emsp;&emsp;--oneline： 一行显示  
&emsp;&emsp;&emsp;&emsp;--all: 所有分支  

$ git log -p//查看修改的具体内容，不仅显示commit日志，而且同时显示每次commit的代码改变。  
$ git log -p filename //显示指定文件相关的每一次diff，查看某个文件filename修改的具体内容  
$ git log -4//查看分支最近4次修改记录  
$ git log -2 -p//查看最近2次修改的具体内容。注意这里参数顺序-2 -p，不能把-p放到-2之前。  
$ git log --author="username"  //显示某个用户的所有提交  
$ git log --author="John\|Mary"

[--] <path>…  
Consider only commits that are enough to explain how the files that match the specified paths came to be.  
Paths may need to be prefixed with -- to separate them from options or the revision range, when confusion arises.  

过滤合并提交  
git log输出时默认包括合并提交。但是，如果你的团队采用强制合并策略（意思是merge你修改的上游分支而不是将你的分支rebase到上游分支），你的项目历史中会有很多外来的提交。  
你可以通过--no-merges标记来排除这些提交：  
git log --no-merges  
另一方面，如果你只对合并提交感兴趣，你可以使用--merges标记：  
git log --merges  
它会返回所有包含两个父节点的提交。  

按提交信息来过滤提交，你可以使用--grep标记。它和上面的--author标记差不多，只不过它搜索的是提交信息而不是作者。  
比如说，你的团队规范要求在提交信息中包括相关的issue编号，你可以用下面这个命令来显示这个issue相关的所有提交：  
git log --grep="JRA-224:"  //你也可以传入-i参数来忽略大小写匹配。  
区分：  
$ git grep "Hello" //从当前目录的所有文件中查找文本内容  
$ git grep "Hello" v2.5 //在某一版本中搜索文本  

$ git log --pretty=oneline  
$ git log -5 --pretty --oneline //显示过去5次提交  
$ git log --oneline //显示更简短的SHA值,等效$ git log --abbrev-commit --pretty=oneline  
$ git log --stat //显示commit历史，以及每次commit发生变更的文件  
$ git log -S [keyword] //搜索提交历史，根据关键词  
$ git log [tag] HEAD --pretty=format:%s //显示某个commit之后的所有变动，每个commit占据一行  
$ git log [tag] HEAD --grep feature //显示某个commit之后的所有变动，其”提交说明”必须符合搜索条件  
$ git log --follow [file] //显示某个文件的版本历史，包括文件改名  
$ git whatchanged [file] //显示某个文件的版本历史，包括文件改名、文件模式、其他  
$ git log --before="1 days" //显示之前1天的版本  
$ git shortlog -sn //显示所有提交过的用户，按提交次数排序  

git log自定义显示格式  
对于git log格式需求，可以使用--pretty=format:"<string>"选项。它允许你使用像printf一样的占位符来输出提交。  
$ git log -9 --graph --pretty=format:%H,%Cred%an,%cn,%Cgreen%cd,%Cblue%s,%Creset%P  
$ git log -9 --graph --pretty=format:%h,%Cred%an,%cn,%Cgreen%cd,%Cblue%s,%Creset%p  
参考：https://git-scm.com/docs/pretty-formats  

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

Git log用法：  
https://git-scm.com/book/zh/v2/Git-%E5%9F%BA%E7%A1%80-%E6%9F%A5%E7%9C%8B%E6%8F%90%E4%BA%A4%E5%8E%86%E5%8F%B2  
https://www.cnblogs.com/biglucky/p/5076885.html  
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  


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
$ git push <remote> :<branch/tag-name> //删除远程分支或标签，或者  
$ git push origin --delete my-branch   //删除远程分支或标签  
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
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  


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
$ git reset --keep [commit] //重置当前HEAD为指定commit，但保持暂存区和工作区不变--保留未提交的本地修改。  
$ git revert [commit] //新建一个commit，用来撤销指定commit。后者的所有变化都将被前者抵消，并且应用到当前分支  
$ git stash //暂时将未提交的变化保存，稍后再恢复  
$ git stash -u //暂时将未提交的变化、和新增的文件保存，稍后再恢复
$ git stash pop //恢复之前保存的变化  
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  


### 十、其他  
$ git clean -fd，删除**未被追踪的**文件和文件夹  
$ git archive //生成一个可供发布的压缩包  
[返回*git命令*](#git命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  




### git学习  
#### git动画演示
https://learngitbranching.js.org/ ，可视化，直接看到每一条git命令操作的结果。是git练习的好帮手，推荐。  
**Learngitbranching网站使用方法**，常用命令如下：  
$ show commands，显示支持的命令  
$ show solution，查看答案  
$ show goal / hide goal，显示/关闭目标提示  
$ levels，选择不同级别的关卡进行练习，达到设定的目标可以通关。限定只能使用某些git命令。  
$ sandbox，进入沙盒中，不在设定的关卡里，可以使用任何git命令，自由发挥。  
如果想通关练习，那就输levels命令选择关卡；如果想自由发挥，那就输sandbox命令，进入沙盒中。  
通关过程中，如果想查看答案，输show solution命令。  

#### 参考网址
http://www.softwhy.com/qiduan/git_course/

[返回*git学习*](#git学习)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)  



# repo  
- [repo介绍](#repo介绍)    
- [repo使用步骤](#repo使用步骤)    
- [repo命令](#repo命令)    
- [repo和git使用遇到的疑难杂症](#repo和git使用遇到的疑难杂症)    
- [repo start干了些什么？](#repo-start干了些什么)    
[*返回目录*](#git)    

## repo介绍    
**①repo是对git的封装。**  
**②repo用于管理一个工程(project)下多个git仓库(项目)**。  
repo命令行工具**对Git命令进行了封装**，可以**管理多个git项目**，从而更好地对代码进行集中式管理。  
**repo**是Google**用Python脚本写的调用Git的脚本**，用于下载、管理Android项目的软件仓库。repo主要包含Repo配置信息以及Repo所管理的Git项目集合。  
repo**使用Python对git进行了一定的封装**，简化了**对多个Git版本库的管理**。它并不是用于取代git，用repo管理的版本库都需要使用git命令来进行操作。  
repo用于管理多个git项目，**同一产品可能包含多个git项目**，不同的git项目集合，可能形成不同产品，通过repo可以实现方便的管理。  
对于所有git管理的项目，例如mygitproject，其中mygitproject/.git是git目录（或git库）；mygitproject/中除.git之外的内容为git工作目录，来自相应git目录中的某个版本。  
对于所有repo管理的项目，例如myrepoproject，其中myrepoproject/.repo是repo目录（或repo库）；myrepoproject/中除.repo之外的内容为repo工作目录，来自相应repo目录中的某个版本。  
**git只能同时对一个git库管理**，操作不同git库需要**cd切换到对应的git库目录**。  
**repo能同时管理多个git库**，**在项目顶层目录**就可以**同时**管理项目下的**多个git库**，**不需要cd到对应的git库目录**，对于管理多个git库的项目很方便。  
repo命令使用了和git命令**相同的名字**，如repo diff和git diff、repo branch和git branch、repo status和git status、repo checkout和git checkout，**使用方法也一样**。  
[*返回repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    


## repo使用步骤  
### 下载repo工具  
首先，确认主目录下存在 bin/ 目录并已包含在路径中：  
mkdir \~/bin  
PATH=\~/bin:$PATH  
下载Repo工具并设置可执行的权限：  
curl https://storage.googleapis.com/git-repo-downloads/repo > \~/bin/repo  
chmod a+x \~/bin/repo  
注：下载Repo只针对第一次使用。  

### 清单库文件介绍  
一个清单库可以包含多个清单文件和多个分支，每个清单文件和分支都有对应的版本。清单文件以xml格式组织的。举个例子：  
![](https://github.com/gaheadus/daily_use/blob/master/Resources/repo%E6%B8%85%E5%8D%95%E5%BA%93.jpg)  
remote元素，定义了名为korg的远程版本库，其库的基址为git://172.16.1.31/  
default元素，设置各个项目默认远程版本库为korg，默认的的分支为gingerbread-exdroid-stable。当然各个项目(project元素)还可以定义自己的remote和revision覆盖默认的配置project元素，用于定义一个项目，path属性表示在工作区克隆的位置，name属性表示该项目的远程版本库的相对路径 project元素的子元素copyfile，定义了项目克隆后的一个附件动作，从src拷贝文件到dest。  

### 建立本地repo目录、初始化git库  
**建立本地**repo**目录**(Create local repository)**  
\#cd \~  
\#mkdir sgk  
\#cd sgk  
\# repo init -u ssh://sh2-git01.marvell.com:29418/android/platform/manifest.git -b dkbttc-gingerbread-dsds-dev_r2 --repo-url=ssh://sh2-git01.marvell.com:29418/android/tools/repo.git  
\#repo start localbranchname --all (如果不进行这一个步骤，会造成后续repo sync的时候跳出分支不在任何分支上的情况；)(跟踪远程分支，同时在为整个本地代码新建一个名为localbranchname的分支；  
repo start <branch_name> 就是逐一为各个工程创建工作分支,git branch <branch_name>在当前工程目录下建立新分支；  
开发时，一般以进行repo start的分支作为主分支，然后在此基础上建立其他分支-从分支；)  
\#repo sync  
**repo start**  
$repo start <branchname> 就是逐一为各个版本库创建工作分支，以便在此分支下进行工作。  
建立本地分支branchname，同时跟踪远程分支。跟踪的远程分支是谁？？  
答案：是repo init的时候指定的。  
**文件修改、增减，提交**  
\#vim sgk.c  
\#git status / git diff /  
\#git add .  
\#git commit -m “hhh”/ git commit --amend  
\#repo sync . ，如果有冲突，合并冲突，再重复第4、5步；  
\#git push .  
\#repo sync和\#repo sync .的区别  
\#repo sync进行整个源文件目录的同步；  
\#repo sync .进行本工程目录下的同步；  


### repo的过程中出现的问题  
在上述**建立本地**repo**目录**步骤5中，repo sync的时候出错，无法取得远程服务器的代码；  
原因：在\~目录下错误的进行了第4步的repo init -u…操作(本来应该是在sgk目录)，以至于在sgk目录下进行repo sync操作的时候把代码保存到\~目录下去了，而没有保存到sgk目录里。  
解决办法是：删除\~目录中的.repo/文件夹中的全部内容(rm -rf .repo/)，然后在sgk目录下重新进行第4、5步操作；  
**附：**  
.repo文件夹中内容如下，是由repo init -u…操作所产生的；  
![](https://github.com/gaheadus/daily_use/blob/master/Resources/repo%20init%20-u%2C1.png)  
在没有进行repo init -u…的时候进行repo sync 会报如下错误；  
![](https://github.com/gaheadus/daily_use/blob/master/Resources/repo%20init%20-u%2C2.png)  
  

### git和repo流程表  
![](https://github.com/gaheadus/daily_use/blob/master/Resources/git%E5%92%8Crepo%E6%B5%81%E7%A8%8B%E8%A1%A8.png)  
[*返回repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    


## repo命令  
repo所支持的命令可以到源码source/.repo/repo/subcmds/目录下查看，如./abandon.py、./branches.py、./checkout.py…，每一个py文件对应一个可支持的repo命令有：abandon/branches/checkout/cherry_pick/diff/diffmanifests/download/forall/grep/ help/info/init/list/manifest/overview/prune/rebase/selfupdate/smartsync/stage/start/status/sync/upload/version/__init__等。  
获取帮助：repo help [command]，获取command的详细的帮助信息内容  

[repo init](#repo-init) &emsp; [repo sync](#repo-sync) &emsp; [repo start](#repo-start)  &emsp; [repo branch](#repo-branch)  &emsp; [repo forall -c](#repo-forall--c)  
[repo status](#repo-status) &emsp; [repo diff](#repo-diff) &emsp; [repo checkout](#repo-checkout) &emsp; [repo push](#repo-push) &emsp; [repo update](#repo-update)  
[repo download](#repo-download) &emsp; [repo upload](#repo-upload) &emsp; [repo selfupdate](#repo-selfupdate) &emsp; [repo prune](#repo-prune) &emsp; [repo abandon](#repo-abandon)  
[repo remote](#repo-remote) &emsp; [repo grep](#repo-grep) &emsp; [repo manifest](#repo-manifest) &emsp; [repo version](#repo-version) &emsp; [repo help](#repo-help)  
[*返回repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo init  
repo init -u URL [OPTIONS]  
repo init -u manifest_git_path -m manifest_file_name -b branch_name --repo-url=repo_url --no-repo-verify  
在当前目录下安装 repo。这会产生一个.repo/目录，目录包括装 repo源代码和标准 Android 清单文件的 Git 仓库。.repo/ 目录还包括 manifest.xml，是一个在 .repo/manifests/ 目录选择清单的符号链接。  
选项：  
-u: 指定Manifest库的Git访问路径。  指定一个URL，其连接到一个manifest仓库。  
-m: 指定要使用的Manifest文件。  在manifest仓库中选择一个 NAME.xml 文件。  
-b: 指定要使用Manifest仓库中的某个特定分支。  
--repo-url: 指定要检查repo是否有更新的远端repoGit库的访问路径。  
--no-repo-verify: 指定不检查repo库是否需要更新。  
注：  
·  如果不提供 -b REVISION 或者 --manifest-branch=REVISION参数，则检出 manifest Git 库的 master 分支。  
·  如果不提供 -m NAME.xml 或者 --manifest-name=NAME.xml 参数，则使用缺省值 default.xml。  
作用是下载或更新好repo配置和脚本集（相当于对repo配置和repo脚本集进行git pull，但是它还额外做了更多的事情），repo配置和脚本本身又是由git管理的，repo配置指定使用哪些git项目，脚本是repo命令本身的实现。  
在空目录中执行这个repo init命令后，会生成一个.repo目录，查看.repo目录，会看到有如下内容：  
$ls .repo  
manifests/ manifests.git/ manifest.xml repo/  
具体解释如下：  
（*）.repo：此为repo目录，可用于提取相应项目工作目录到外面的repo工作目录。  
（*）.repo/manifests.git：此为repo配置信息的git库，不同版本包含不同配置信息，配置信息大致描述内容见后面。  
（*）.repo/manifests：此为repo配置信息的工作目录（将配置信息的工作目录和相应的实际git目录分离管理，并且配置信息中的.git目录实际只是指向实际git库的软连接），其中可能包含一个或多个xml文件描述的配置。每个xml文件是独立的一套配置，配置内容包括当前repo工作目录包含哪些git项目、所有git项目所处的默认公共分支、以及远端地址等。  
（*）.repo/manifest.xml：repo工作目录中的内容同一时刻只能采用manifests中的一个xml文件做为其配置，该文件就是其软连接，通过init的-m选项指定采用哪个文件；另外，同一xml文件也可能处于manifests库的不同版本或者不同分支，通过init的-b选项指定使用manifests中的哪个分支，每次init命令都会从服务器更新最新的配置。这里通过-m指定的manifests中的xml文件中，有两个需要注意：default.xml是稳定版，default_head.xml是开发版，开发版始终包含最新的内容。  
（*）.repo/repo：此为repo脚本集的git库，用于repo管理所需的各种脚本，repo的所有子命令就是其中的对应脚本实现。该脚本也通过git管理，.repo/repo/.git为对应的git目录。这里包含repo命令所需的所有子命令脚本实现，由python完成（我们可以在.repo/repo/subcmds中看到类似repo的init等的子命令脚本实现，如repo的init子命令即repo init，它由.repo/repo/subcmds/init.py实现），这个目录本身又由git来管理。不同的repo库或者不同版本的repo库，其repo命令实现会有些不同，所以也对应不同的repo脚本集，建议每次采用对应repo项目的最新的repo库做为其repo命令集实现。第一次使用repo时，采用的repo脚本实际是一个简单的repo的引导脚本，它既符合shell语法，又符合python语法，最终会将所需的具体脚本实现下载至最新的.repo/repo中，后面类似"repo init"、"repo sync"等脚本的实现，全都有这里的内容来实现。我们发现.repo/repo/repo，这个文件其实就是当前repo库中最新的repo引导脚本，可供其它没有使用过repo的用户做为repo的引导脚本来使用。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo sync  
$ repo sync [project-list]  
下载最新本地工作文件，更新成功，这本地文件和repository中的代码是一样的。  
可以使用repo sync project_name的形式指定需要更新的project。  
$repo sync \#如果不指定任何参数，会同步整个所有的项目。  
$repo sync frameworks/base \#如果指定工程名，会单独下载指定的工程。  
选项：  
-j：开启多线程同步操作，会加快sync命令的执行速度。默认情况下，使用4个线程并发进行sync。  
-c, --current-branch：只同步指定的远程分支。默认情况下，sync会同步所有的远程分支，当远程分支比较多的时候，下载的代码量就大。使用该参数，可以缩减下载时间，节省本地磁盘空间。  
-d, --detach：脱离当前的本地分支，切换到manifest.xml中设定的分支。在实际操作中这个参数很有用，当我们第一次sync完代码后，往往会切换到dev分支进行开发。如果不带该参数使用sync，  则会触发本地的dev分支与manifest设定的远程分支进行合并，这会很可能会导致sync失败。  
-f, --force-broken：当有git库sync失败了，不中断整个同步操作，继续同步其他的git库。  
--no-clone-bundle：在向服务器发起请求时，为了做到尽快的响应速度，会用到内容分发网络(CDN, Content Delivery Network)。同步操作也会通过CDN与就近的服务器建立连接，  使用HTTP/HTTPS的$URL/clone.bundle来初始化本地的git库，clone.bundle实际上是远程git库的镜像，通过HTTP直接下载，这会更好的利用网络带宽，加快下载速度。  
-s：同步到一个已知的构建 manifest-server 在当前清单指定的元素。  
用于参照清单文件.repo/manifest.xml克隆并同步版本库。  
如果版本库不存在，则相当于执行git clone，会把repository中的所有内容都拷贝到本地。  
如果版本库已经存在，则相当于执行：  
git remote update //对每个remote源进行fetch操作  
git rebase/origin/branch //针对当前分支的跟踪分支进行rebase操作  
如果在merge的过程中出现冲突，这需要手动运行git rebase --continue。  
作用是下载当前repo配置的所有项目，并生成对应的repo工作目录。执行之后，会看到.repo目录包含如下内容：  
$ls .repo  
manifests manifests.git manifest.xml projects repo  
还有.repo外面也多出了许多目录。  
也就是说，多出了一个projects目录，和.repo外面的许多目录，具体内容如下：  
（*）.repo/projects：此为repo所管理的所有git项目集，包含repo当前配置所指定的所有git项目对应的git目录。不同的清单文件（即manifest.xml）内容，指定不同的git项目集组合，表征不同的项目版本或者项目，而如上所述，manifest.xml文件的内容又由其指向的manifests中的、具体的分支下的、xml文件来决定。  
（*）.repo/../*：此为repo的工作区。在repo目录（即.repo）之外，根据repo配置（即.repo/manifest.xml文件），从.repo/projects/*中提取出指定分支的各个git项目（即.repo/projects中git项目的子集）的工作目录，形成repo工作目录，可供开发使用。其中每个git工作目录中的.git只是指向.repo/projects/*的软连接，在repo工作目录中的某个git工作目录更新相应的git库，其实最终会更新到.repo/projects中对应的git库。刚刚repo sync之后，当前工作目录不处于任何分支，其中的修改只能本地保存无法提交至远端，若想提交工作，需要先创建一个分支保存工作内容。  
repo sync做了什么？fetch+merge还是fetch+rebase？  
repo upload呢？  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo start  
初始化分支  
$ repo start master --all  
--all意思为对所有项目操作，也可以只对某个项目操作如$ repo start mybranch frameworks/base。  
repo初如化分支后，可切入各git库进行git的操作。  
$repo start branchname --all\#在源码根目录下执行，对源码目录下所有工程建立branchname分支。  
$repo start branchname frameworks/base/\#在源码根目录下执行，对frameworks/base/工程建立branchname分支。  
$repo start branchname . #在对应工程目录下执行，创建branchname分支。"."代表当前工作的工程目录。  
repo start <newbranchname> [--all|<project>...]  
创建并切换分支。刚克隆下来的代码是没有分支的，repo start实际是对git checkout -b命令的封装。  
为指定的项目或所有的项目（若使用-all），以清单文件中为设定的分支，创建特定的分支。  
这条指令与git checkout -b 还是有很大区别的。  
· git checkout -b 是在当前所在的分支的基础上创建特性分支。  
· 而repo start 是在清单文件设定的分支的基础上创建特性分支。  
repo start stable --all  
假设清单文件中设定的分支是gingerbread-exdroid-stable，那么执行以上指令就是对所有项目，在gingerbread-exdroid-stable的基础上创建特性分支stable。  
repo start stable platform/build platform/bionic  
假设清单文件中设定的分支是gingerbread-exdroid-stable，那么执行以上指令就是对platform/build、platform/bionic项目，在gingerbread-exdroid-stable的基础上创建特性分支stable。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo branch  
$ repo branch [projectname]  
作用：读取项目分支的情况  
$ repo branch packages/apps/Contacts //在源码根目录下执行  
repo branch/repo status/repo diff/repo checkout/repo abandon和单独的git命令是一样的，只不过是把对应的git命令包装了一下，等效于git branch/git status/git diff/git checkout/git branch -D。  
有一点区别就是：repo branch等命令在源码根目录下执行，git branch命令在对应的工程目录下执行。  
repo branch等后不加具体工程名，则对源码根目录下所有工程操作，如果加具体工程名，则只对这个工程操作。  
**关于分支**  
以上描述，有几个分支的概念需要明确。  
（1）repo分支：这里通过repo init -b ，中的-b所指定的分支，是manifests的分支，不同分支，其中的文件清单内容有所不同。  
（2）清单文件指定的分支：通过清单文件manifest.xml中的default实体的revision属性，指定版本库默认的分支为revision属性值，该属性值做为repo sync之后工作目录中所有git项目的公共起点分支，也就是说，该manifest对应所有的git项目都有一个以revision属性值为名的分支，repo sync之后，在任意一个repo工作目录下的git库中，使用git branch或者repo start创建的分支，都是基于该git库中revision属性值为名的分支来创建。我们可以将这个分支设置为和repo分支类似的名字。  
（3）git分支：除了repo管理的用于repo配置的repo分支，和用于设置工作目录起点的清单文件分支，每个工作目录对应的git库，也可设置自己的工作分支，和平时使用git时的含义一样。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo forall -c  
在源码根目录执行  
$ repo forall -c ls / repo forall --command ls / repo forall -c git branch / repo forall -c git checkout originbranch  
这个命令会遍历所有的git仓库，并在每个仓库执行-c/--command所指定的命令(这个被执行的命令就不限于仅仅是git命令了，而是任何被系统支持的命令，比如：ls、pwd、cp等)  
$ repo forall -c git checkout  45451 //所有库检出45451分支与远程45451分支对应（若无，则跳过）  
$ repo forall -c git checkout  -b developing //对源码根目录下所有工程新建developing分支并切换到该分支。  
//和repo start developing --all一样？  
当我想通过这个命令遍历所有的仓库并在每个仓库执行"git checkout . "用以将每个仓库的改动都清除的时候，我这么输入命令：**repo forall -c git checkout .**  
我发现这样根本不行。看来repo不能遍历执行checkout这个命令。今天我终于想到了另外一个命令"git reset --hard HEAD" 哈哈  
**$repo forall -c git reset --hard HEAD**  
**再说一个新发现：以前用**repo forall**执行一些命令的时候，可能再遍历到某个仓库的时候出了问题，但是我却苦于不知道这个仓库到底是哪个。一直也没有解决。今天终于找到了**…** **关键时候还是要看命令自己带的帮助手册呀**…**  
**$repo help forall** **用这个命令查看下针对**forall**的帮助吧。说的很清楚，**repo**执行的时候加上**-p**参数就可以在遍历到每个仓库的时候先打印出当前的**pwd**，然后再继续执行**-c**所指定的命令。举例如下：**  
**$repo forall -p -c git branch    **  
**//**该命令会遍历所有仓库并打印每个仓库的分支情况，由于有了**-p**参数，这样便会打印出每个仓库的路径。**  
repo forall [<project>...] -c <command>  
迭代器，可以在所有指定的项目中执行同一个shell指令。  
选项：  
-c 后面所带的参数是shell指令，即执行命令和参数。命令是通过 /bin/sh 评估的并且后面的任何参数就如 shell 位置的参数通过。  
-p 在shell指令输出之前列出项目名称，即在指定命令的输出前显示项目标题。这是通过绑定管道到命令的stdin，stdout，和 sterr 流，并且用管道输送所有输出量到一个连续的流，显示在一个单一的页面调度会话中。  
-v 列出执行shell指令输出的错误信息，即显示命令写到 sterr 的信息。  
附加环境变量：  
REPO_PROJECT 指定项目的名称  
REPO_PATH 指定项目在工作区的相对路径  
REPO_REMOTE 指定项目远程仓库的名称  
REPO_LREV 指定项目最后一次提交服务器仓库对应的哈希值  
REPO_RREV 指定项目在克隆时的指定分支，manifest里的revision属性  
如果-c后面所带的shell指令中有上述环境变量，则需要用单引号把shell指令括起来。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo status  
$ repo status [projectname]  //显示分支及修改情况  
$ repo status //显示project中每个仓库的状态，并打印仓库名称  
\#输出skipper/build项目分支的修改状态  
repo status skipper/build  
每个小节的首行显示项目名称，以及所在的分支的名称。  
每个字母表示暂存区的文件修改状态。  
字母  含义  描述  
- 无变化  没有修改，在 HEAD 和在索引中是一样的  
A 添加  不在HEAD中，在暂存区中  
M 修改  在HEAD中，  在暂存区中，内容不同  
D 删除  在HEAD中，不在暂存区  
R 重命名  不在HEAD中，在暂存区中  
C 拷贝  不在HEAD中，在暂存区，从其他文件拷贝  
T 文件状态改变  在HEAD中，在暂存区，内容相同  
U 未合并  需要冲突解决  
第二个字符表示工作区文件的更改状态。  
字母  含义  描述  
- 新/未知  不在暂存区，在工作区  
m 修改  在暂存区，在工作区，被修改  
d 删除  在暂存区，不在工作区  
两个表示状态的字母后面，显示文件名信息。如果有文件重名还会显示改变前后的文件名及文件的相似度。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo diff  
$ repo diff [ project-list ]  
显示提交的代码和当前工作目录代码之间的差异。  
实际是对git diff 命令的封装,用于分别显示各个项目工作区下的文件差异。  
repo diff                            ---查看所有项目  
repo diff platform/build platform/bionic ---只查看其中两个项目  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo checkout  
$repo checkout <branchname> [projectname]   
实际上是对git checkout 命令的封装，但不能带-b参数，所以不能用此命令来创建特性分支。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo push  
repo push <remotename> [--all|<project>...]  
向服务器提交代码。repo会自己查询需要向服务器提交的项目并提示用户。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo update  
$ repo update[ project-list ]  
上传修改的代码  ，如果你本地的代码有所修改，那么在运行 repo sync 的时候，会提示你上传修改的代码，所有修改的代码分支会上传到 Gerrit (基于web 的代码review 系统), Gerrit 受到上传的代码，会转换为一个个变更，从而可以让人们来review 修改的代码。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo download  
$ repo download  target revision  
下载特定的修改版本到本地，例如:repo download pltform/frameworks/base 1241，下载修改版本为1241的代码。  
repo download {project change[/patchset]}...  
repo download命令主要用于代码审核者下载和评估贡献者提交的修订。  
贡献者的修订在Git版本库中refs/changes//引用方式命名（缺省的patchset为1），和其他Git引用一样，用git fetch获取，该引用所指向的最新的提交就是贡献者待审核的修订。  
使用repo download命令实际上就是用git fetch获取到对应项目的refs/changes//patchset>引用，并自动切换到对应的引用上。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo upload  
repo upload [--re --cc] {[<project>]...|--replace <project>}  
repo upload 相当于git push，但是又有很大的不同。它不是将版本库改动推送到代码审核服务器（Gerrit软件架设）的特殊引用上，使用SSH协议。代码审核服务器会对推送的提交进行特殊处理，将新的提交显示为一个待审核的修改集，并进入代码审核流程，只有当审核通过后，才会合并到官方正式的版本库中。  
选项：  
-h, –help 显示帮助信息  
-t 发送本地分支名称到Gerrit代码审核服务器  
--replace 发送此分支的更新补丁集  
--re=REVIEWERS 要求指定的人员进行审核  
--cc=CC 同时发送通知到如下邮件地址  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo selfupdate  
repo selfupdate  
用于 repo 自身的更新。如果有新版本的repo存在, 这个命令会升级repo到最新版本。通常这个动作在repo sync时会自动去做, 所以不需要最终用户手动去执行。  
选项:  
-h, –help 显示这个帮助信息后退出.  
–no-repo-verify 不要验证repo源码.  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo prune  
$ repo prune [project list]  
删除已经合并分支。实际上是对git branch -d 命令的封装，该命令用于扫描项目的各个分支，并删除已经合并的分支。  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo abandon  
repo abandon <branchname> [projectname]  
删除指定分支。实际是对git brance -D命令的封装。   
怎样删除代码文件夹下所有git库的分支？ repo abandon <分支名>  
示例，在源码根目录执行，  
$ repo forall -c git checkout -b bra1 / repo start bra1 --all  
$ repo forall -c git checkout -b bra2  
$ repo abandon bra1 / $ repo abandon bra1 packages/apps/Contacts  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo remote  
repo remote add <remotename> <url> [<project>...]  
repo remote rm <remotename> [<project>...]  
设置远程仓库。  
示例：  
repo remote add org ssh://10.11.10.11/git_repo  
这个指令根据xml文件添加的远程分支，方便于向服务器提交代码，执行之后的build目录下看到新的远程分支org。  
repo remote rm org //删除远程仓库  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo grep  
repo grep {pattern | -e pattern} [<project>...]  
打印出符合某个模式的行。相当于对 git grep 的封装，用于在项目文件中进行内容查找。  
示例：  
\#要找一行, 里面有\#define, 并且有'MAX_PATH' 或者 'PATH_MAX':  
repo grep -e '\#define' --and -\( -e MAX_PATH -e PATH_MAX \)  
\#查找一行, 里面有 'NODE'或'Unexpected', 并且在一个文件中这两个都有的.  
repo grep --all-match -e NODE -e Unexpected  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo manifest  
repo manifest [-o {-|NAME.xml} [-r]]  
manifest检验工具，用于显示manifest文件内容。  
选项:  
-h, –help 显示这个帮助信息后退出  
-r, –revision-as-HEAD 把某版次存为当前的HEAD  
-o -|NAME.xml, –output-file=-|NAME.xml 把manifest存为NAME.xml  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo version  
$ repo version  
作用：显示repo版本  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### repo help  
repo help [--all|command]  
显示命令的详细帮助。  
选项:  
-h, –help 显示这个帮助信息后退出  
-a, –all 显示完整的命令列表  
[返回*repo命令*](#repo命令)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; [返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    


## repo和git使用遇到的疑难杂症  
[http://blog.csdn.net/huangxiaohu_coder/article/details/6782260](http://blog.csdn.net/huangxiaohu_coder/article/details/6782260)  
最近在使用Android的repo和git的过程中遇到了很多莫名奇妙的问题，现在记录一下，便于自己以后的查用。  
1.repo sync中遇到error:......checkout ....接一串hashnumber  
解决方法：进到它说提示的目录中，用git status显示文件，将修改过的文件删除掉，再重新repo sync  
2.repo sync中遇到：contains uncommitted changes  
解决方法：进到它说提示的目录中，使用git reset --hard命令  
**3\.** **怎么对**repo**下的所有**project**执行**git**命令**  
**解决方法：**repo forall -c git checkout --track origin/xxxx -b  //**该条命令会对**repo**下的**project**执行切换**branch**的命令**  
**4\.** **怎么切换到你想要的**branch**  
**解决方法：**git checkout branchName**，比如** **git checkout testBranch**  
**                        git checkout --track origin/xxxx -b testbrach  **  
**//**在本地建立名为**testbrach **分支来对应远端的**origin/xxxx**的分支，其中**origin/xxxx**需要使用**git branch -r**来查看。**  
5\. git pull时遇到unmerged的问题，再切到问题目录下，查看它的branch，出 现Not currently on any branch  
解决方法：出现此问题的原因是可能由于你的修改和别人的修改改到一起了，也有可能你有些修改没有git push，这种直接push就好了，其他的情况按照下面的步骤试试：git diff查看冲突的文件，能确定引起冲突的问题话，解决冲突，<<<<<<<<与\=\=\=\=\=\=\=\=之间是你自己的修改，\=\=\=\=\=\=\=\=\=与>>>>>>>>是别人都修改，用编辑器编辑留下你要的代码，然后删除掉你冲突的标记符号（<<<<<<,=\=\=\=\=\=\=,>>>>>>>之类的）。我这个问题恰恰是文件我都没有改过，不是我负责的模块，不确定需要的代码，所以我处理的流程是：git reset  -hard，然后git stash，然后git checkout [branch name]切到正确的branch上。  
6\. 你的代码是在no branch上做的commit，后来你切换到真正的branch上（例如testbranch），这时却找不到原来在no branch上提交的代码，怎么办啊？  
解决方法：用git reflog显示近期的ref历史，记住你想要找回来的commit号，merge进来就好了。 Git reflog  
Git checkout testbranch  
Git merge commitID  
Git push  
7\. 直接使用git pul的出现You asked me to pull without telling me which branch……的错误？  
解决办法：在使用git pull的时候写全remote name和branch name，例如git pull origin testBranch  
8\. repo sync的时候出现a new version of repo available……得错误？  
解决方法：将repo init后会建立.repo文件夹，将.repo/repo/repo拷贝到\~/bin/目录下，覆盖原有repo工具即可。  
或者：删除掉android根目录下的.repoconfig文件夹。  
**[repo用法详解](http://blog.csdn.net/sunweizhong1024/article/details/8055372)**  
[http://blog.csdn.net/sunweizhong1024/article/details/8055372](http://blog.csdn.net/sunweizhong1024/article/details/8055372)  
Android 为企业提供一个新的市场，无论大企业，小企业都是处于同一个起跑线上。研究 Android 尤其是 Android 系统核心或者是驱动的开发，首先需要做的就是本地克隆建立一套 Android 版本库管理机制。  
Android 使用 Git 作为代码管理工具，开发了 Gerrit 进行代码审核以便更好的对代码进行集中式管理，还开发了 Repo 命令行工具，对 Git 部分命令封装，将百多个 Git 库有效的进行组织。要想克隆和管理这百多个 Git 库，还真不是一件简单的事情。  
在研究 Repo 的过程中，发现很多文档在 Google Group 上，非“翻墙”不可看。非法的事情咱不干，直接阅读 repo 的代码吧。  
### 创建本地 Android 版本库镜像的思路  
如果了解了 Repo 的实现，参考 [《Using Repo and Git》](http://source.android.com/source/git-repo.html) , 建立一个本地的 android 版本库镜像还是不难的：  
下载 repo bootstrap 脚本  
$ curl http://android.git.kernel.org/repo >\~/bin/repo  
$ chmod a+x \~/bin/repo  
$ export PATH=$PATH:\~/bin  
提供 --mirror 参数调用 repo init ，建立 git 版本库克隆  
$ repo init -u git://android.git.kernel.org/platform/manifest.git --mirror  
使用 --morror 则下一步和源同步的时候，本地按照源的版本库组织方式进行组织，否则会按照 manifest.xml 指定的方式重新组织并检出到本地  
开始和源同步  
$ repo sync  
修改 manifest ，修改 git 库地址，指向本地的 git 服务器  
修改 platform/manifest.git 库中现有的 xml 文件，或者创建一个新的 xml 文件  
将 git 的地址改为本地地址，提交并 push  
本地 repo 镜像建立完毕之后，就可以在执行 repo init 时，使用本地更改后的 manifest 库，之后执行 repo sync 就是基于本地版本库进行同步了。  
也可以改造 repo，使得不必为 repo 工具初始化，也在本地网络完成操作…  
### Repo init 干了些什么？  
实际上，得到客户使用 repo 的信息后，首先下载 repo 执行脚本开始研究。  
curl http://android.git.kernel.org/repo >\~/bin/repo  
难道只有 600 行的 python 代码么？要是这样应该很简单的呀。可以看下来，却发现远非如此。  
###\# Shell script or python？  
首先 repo 脚本使用了一个魔法：从脚本第一行的 shebang 来看应该是 shell 脚本，但是满眼却都是 python 语法，怎么回事？  
\#!/bin/sh  
repo default configuration  
REPO_URL='git://android.git.kernel.org/tools/repo.git'  
REPO_REV='stable'  
Copyright (C) 2008 Google Inc.  
...  
magic='--calling-python-from-/bin/sh--'  
"""exec" python -E "$0" "$@" """\#$magic"  
if __name__ == '__main__':  
import sys  
if sys.argv[-1] == '\#%s' % magic:  
del sys.argv[-1]  
del magic  
魔法就在第 23 行，巧妙的通过 python 三引号字串写出了一个能被 python 和 shell script 都能理解的代码，以此为界，代码由 Shell 脚本进入了 Python 的世界。  
### Bootstrap 和真正的 repo  
通过 curl 下载的的 repo 并非完整的 repo 脚本，只是一个 bootstrap。当 repo 执行时，会负责下载完整的 repo 代码，并将控制权转移给真正的 repo。  
通过 main 函数，可以看到 repo 运行的开始，就试图发现本地真正的完整的 repo 代码，以便移交控制权：  
544 def main(orig_args):  
545   main, dir = _FindRepo()  
586   try:  
587     os.execv(main, me)  
其中 545 行的 _FindRepo() 会在当前目录开始向上递归查找 “.repo/repo/main.py”，如果找到则移交控制权（587行）。  
### Repo bootstrap 脚本调用 init 只完成第一阶段的初始化  
Repo 的 bootstrap 脚本只支持两个命令 help 和 init，而 init 也只完成 repo 版本库克隆（即安装 repo 完整工具），之后就转移控制权。  
在 Repo bootstrap 执行 init 可以提供很多参数，但实际上第一阶段初始化，只用到两个参数（而且都有默认值）  
参数：–repo-url=URL  
repo 工具本身的 git 库地址。缺省为：git://android.git.kernel.org/tools/repo.git  
参数：–repo-branch=REVISION 使用 repo 的版本库，即 repo git 库的分支或者里程碑名称。缺省为 stable  
### 第二阶段的 repo init  
执行第二阶段的 repo init，控制权已经移交给刚刚克隆出来的 repo git 库的脚本。  
Repo git 库被克隆/检出到执行 repo init 命令当前目录下的 .repo/repo 子目录中，主要的执行脚本为 .repo/repo/main.py。main.py 接着执行 repo init 命令。  
Repo 的代码组织的非常好，在 .repo/repo/subcmds/ 子目录下，是各个 repo 命令的处理脚本。repo init 的第二阶段脚本正是由 .repo/repo/subcmds/init.py 负责执行的。第二阶段主要完成：  
克隆由 -u 参数提供的 manifest Git 库，如克隆 android 库时：  
$ repo init -u git://android.git.kernel.org/platform/manifest.git  
如果不提供 -b REVISION 或者 –manifest-branch=REVISION参数，则检出 manifest Git 库的 master 分支  
如果不提供 -m NAME.xml 或者 –manifest-name=NAME.xml 参数，则使用缺省值 default.xml  
如果提供 –mirror 参数，则后续同步操作会有相应的体现  
[返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    


## repo start干了些什么？  
Android 源码网站在介绍 repo 的使用模型中，有一个图片： http://source.android.com/images/git-repo-1.png , 介绍了 repo 的使用流程。其中 “repo start” 是紧接着 “repo sync” 后的第一个动作。那么这个动作是干什么的呢？  
得益于 repo 对 git 操作的封装，”repo start” 命令的处理代码只有区区 68 行。  
37   def Execute(self, opt, args):  
41     nb = args[0]  
47     projects = []  
48     if not opt.all:  
49       projects = args[1:]  
54     all = self.GetProjects(projects)  
57     for project in all:  
59       if not project.StartBranch(nb):  
60         err.append(project)  
看到第 59 行了么，就是对 repo 同步下来的项目的多个 Git 版本库，逐一执行 project.StartBranch 操作。 nb 是 repo start 的第一个参数，即分支名称。  
关于 StartBranch 的代码，在 project.py 中：  
857   def StartBranch(self, name):  
858     """Create a new branch off the manifest's revision.  
859     """  
894     if GitCommand(self,  
895                   ['checkout', '-b', branch.name, revid],  
896                   capture_stdout = True,  
897                   capture_stderr = True).Wait() == 0:  
898       branch.Save()  
899       return True  
原来如此， repo start <branch_name> 就是逐一为各个版本库创建工作分支，以便在此分支下进行工作。  
读者可以按图索骥，找到 repo 各个命令的实现，破解心中的疑惑。  
[返回*repo*](#repo)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    


## 专题
[git log进阶](#git-log进阶)  &emsp;&emsp;  [回退到指定日期的版本](#回退到指定日期的版本)  &emsp;&emsp;  [git stash](#git-stash)  &emsp;&emsp;  [patch的使用](#patch的使用)  &emsp;&emsp;  [撤销修改:checkout,reset,clean,revert](#撤销修改checkoutresetcleanrevert)  &emsp;&emsp;  [git rebase -i](#git-rebase--i)  &emsp;&emsp;  
[*返回目录*](#git)  


### git log进阶
**显示指定时间的提交**  
显示指定日期之间的提交:  
git log --after=2019-06-05   --before=2019-06-18  
git log --after="2019-06-05" --before="2019-06-18" //中间没有空格，双引号可要可不要  
git log --since=2019-06-05 --until=2019-06-18  
还可以指定更精确的时间，如下：  
git log --after="2019-06-01 10:00" --before="2019-06-18 23:00"  //中间有空格，需要外加双引号  

git log --author=DuKang //仅显示指定作者相关的提交  

> 选项 说明  
-p 按补丁格式显示每个更新之间的差异。  
--stat 显示每次更新的文件修改统计信息。  
--shortstat 只显示 --stat 中最后的行数修改添加移除统计。  
--name-only 仅在提交信息后显示已修改的文件清单。  
--name-status 显示新增、 修改、 删除的文件清单。  
--abbrev-commit 仅显示 SHA-1 的前几个字符， 而非所有的 40 个字符。  
--relative-date 使用较短的相对时间显示（比如，“2 weeks ago”）。  
--graph 显示 ASCII 图形表示的分支合并历史。  
--pretty 使用其他格式显示历史提交信息。 可用的选项包括 oneline， short， full， fuller 和format（后跟指定格式） 。  
-(n) 仅显示最近的 n 条提交  
--since, --after 仅显示指定时间之后的提交。  
--until, --before 仅显示指定时间之前的提交。  
--author 仅显示指定作者相关的提交。  
--committer 仅显示指定提交者相关的提交。  
--grep 仅显示含指定关键字的提交  
-S 仅显示添加或移除了某个关键字的提交  

**指定输出格式**  
git log --pretty=oneline     //按一行输出，完整SHA  
git log --oneline           //按一行输出，简短SHA  

git log --pretty=format:%H  //commit hash  
git log --pretty=format:%h   //abbreviated commit hash  
git log --pretty=format:%s   //subject  
git log --pretty=format:%an  //author name  
git log --pretty=format:%ae  //author email  
git log --pretty=format:%ad  //author date (format respects --date= option)  
git log --pretty=format:%ai  //author date, ISO 8601-like format  
git log --pretty=format:%cn  //committer name  
git log --pretty=format:%ce  // committer email  
git log --pretty=format:%cd  // committer date (format respects --date= option)  
git log --pretty=format:%ci  // committer date, ISO 8601-like format  

几个格式一起输出：  
git log –pretty=format:%H,%s,%an,%ae        //中间不能有空格  
git log –pretty=format:"%H,   %s,%an,%ae"    //中间有空格则必须外加双引号  
[返回*专题*](#专题)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    



### 回退到指定日期的版本  
repo forall -c 'commitID=\`git log --before "2017-03-17 07:00" -1 --pretty=format:"%H"\`; git reset --hard $commitID'  
[返回*专题*](#专题)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    



### git stash  
常用git stash命令：  
（1）git stash 对当前的暂存区和工作区状态进行保存。  
     git stash save "save message"  : 执行存储时，添加备注，方便查找，只有git stash也是可以的，但查找时不方便识别。  
     git stash save 将工作区和暂存区的修改保存，只会保存已经被git tracked的文件，对于新增文件，还没有被git track，如果需要保存，使用git stash save -u。  
     对新增加的文件进行暂存，推荐使用git stash save -u，不推荐git add之后git stash save，这样可以避免在git stash apply的时候将新增文件、不必要的文件纳入跟踪范围。这样在git apply恢复暂存的修改后，可以使用git checkout .和git clean -f取消修改，否则要使用git reset --hard HEAD和rm取消修改，更麻烦。  

（2）git stash list  ：列出所有保存的进度列表。  
（3）git stash show ：显示做了哪些改动，默认show第一个存储,如果要显示其他存贮，后面加stash@{$num}，比如第二个 git stash show stash@{1}  
（4）git stash show -p : 显示第一个存储的改动，如果想显示其他存存储，命令：git stash show  stash@{$num}  -p ，比如第二个：git stash show  stash@{1}  -p  
（5）git stash apply :应用某个存储,但不会把存储从存储列表中删除，默认使用第一个存储,即stash@{0}，如果要使用其他个，git stash apply stash@{$num} ， 比如第二个：git stash apply stash@{1}   
（6）git stash pop ：命令恢复之前缓存的工作目录，将缓存堆栈中的对应stash删除，并将对应修改应用到当前的工作目录下,默认为第一个stash,即stash@{0}，如果要应用并删除其他stash，命令：git stash pop stash@{$num} ，比如应用并删除第二个：git stash pop stash@{1}  
（7）git stash drop stash@{$num} ：丢弃stash@{$num}存储，从列表中删除这个存储  
（8）git stash clear ：删除所有缓存的stash  
（9）git stash branch <branchname> <stash> 基于进度创建分支  
[返回*专题*](#专题)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    


### patch的使用
**打patch，生成补丁，git format-patch：**  
$ git format-patch -1 和 git format-patch HEAD^ 等效，生成当前分支最近一次提交的patch  
$ git format-patch -2 和 git format-patch HEAD^^ 等效，生成当前分支最近两次提交的patch  
$ git format-patch -1 SHA //生成指定提交的patch  
$ git format-patch -n SHA //从SHA值开始(含SHA值当次)之前的n次提交的patch  
**应用补丁，git am：**  
$ git am 0001-trival-patch.patch  
git am用了git apply，用它打补丁会生成commit信息。如果出现错误  
previous rebase directory ../.git/rebase-apply still exists but mbox given  
可以用  
$ git am --abort  

上述方法用于已经commit的更改，如果是还没有commit的修改，可以用git diff生成的本地修改的patch，则可以用下面方法生成patch、应用patch：  
$ git diff > diff.patch  
$ **patch -p1 < diff.patch** //推荐使用patch命令，git apply命令经常出错  
$ git apply diff.patch  /  $ git apply --ignore-space-change --ignore-whitespace diff.patch  

patch命令里面的层数-p0 -p1  
参数-p来指定从第几层开始比较。比如有一个patch文件的补丁头是这样的：  
--- old/modules/pcitableMon Sep 27 11:03:56 1999  
+++ new/modules/pcitableTue Dec 19 20:05:41 2000  
如果使用参数-p0，就表示从当前目录，找一个叫作new的目录，在它下面找一个叫modules的目录，再在它下面找一个叫pcitableMon的目录。   
如果使用参数-p1,就表示忽略第一层，从当前目录找一个叫modules的目录，在它下面找一个叫modules的目录。这样会忽略掉补丁头提到的new目录。  


当然这更像svn中的习惯，在git里反正是本地提交，提交的成本很低，所以可以先提交再生成patch。  

branch之间应用patch：  
$ git cherry-pick  

**git format-patch**  
使用git format-patch生成的一系列的patch。git format-patch生成的git专用补丁。  
法一：使用HEAD生成patch  
$ git format-patch HEAD^ <==最近的1次commit的patch  
$ git format-patch HEAD^^ <==最近的2次commit的patch  
$ git format-patch HEAD^^^ <==最近的3次commit的patch  
$ git format-patch HEAD^^^^ <==最近的4次commit的patch  
$ git format-patch HEAD^^^^^ <==不支持！！！！error！！！  
git format-patch -1 和 git format-patch HEAD^ 等效，生成当前分支最近一次提交的patch  
git format-patch -2 和 git format-patch HEAD^^ 等效，生成当前分支最近两次提交的patch  
git format-patch -n , n是具体某个数字， 例如 'git format-patch -1' 这时便会根据log生成一个对应的补丁，如果 'git format-patch -2' 那么便会生成2个补丁，当然前提是你的log上有至少有两个记录。  

法二：根据commit SHA生成patch  
$ git format-patch -1 SHA //生成指定提交的patch  
$ git format-patch -n SHA //从SHA值开始(含SHA当次)之前的n次提交的patch(比SHA更旧的提交、在SHA之前的提交)  
$ git format-patch commit1..commit4 //生成从commit2到commit4的patch  
$ git format-patch -s SHA //此SHA值提交以后的所有patch(不含SHA当次) (比SHA更新的提交、在SHA之后的提交)  

法三：指定分支  
$ git format-patch -M master //当前分支所有超前master的提交  
$ git format-patch -n master //生成最近n次commit的patch  
$ git format-patch master~4..master~2  //生成master~4和master~2之间差异的patch  

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
如果收到的补丁文件是用 git diff 或由其它 Unix 的 diff 命令生成，就该用 patch -p或git apply 命令来应用补丁。  
[返回*专题*](#专题)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### 撤销修改:checkout,reset,clean,revert
1. git checkout -- filename  
撤销最近一次工作区的修改，git add filename 命令的后悔药  
git checkout --filename 其实是用版本库的文件替换工作区的文件，无论工作区是修改还是删除，都可以“一键还原”。  
2. git  reset -- filename  
撤销暂存区的提交，git commit -m 'msg' 的后悔药  
git reset --hard HEAD，撤销工作区和暂存区的修改  
git reset --hard HEAD^ ，回退到上一个版本  
--soft – 缓存区和工作目录都不会被改变  
--mixed – 默认选项。撤销暂存区的修改，但工作目录不受影响  
--hard – 缓存区和工作目录都同步到你指定的提交  

小结：**git checkout / git reset只能撤销已经tracked的文件，git clean用来删除没有tracked的文件。**  

git clean命令用来从你的工作目录中删除所有没有tracked过的文件  
git clean经常和git reset --hard一起结合使用。reset只影响被track过的文件, 所以需要clean来删除没有track过的文件，结合使用这两个命令能让你的工作目录完全回到一个指定的<commit>的状态。  

git clean -n，是一次clean的演习, 告诉你哪些文件会被删除. 记住他不会真正的删除文件, 只是一个提醒  
git clean -f，删除当前目录下所有没有track过的文件，他不会删除.gitignore文件里面指定的文件夹和文件, 不管这些文件有没有被track过  
git clean -f <path>，删除指定路径下的没有被track过的文件  
git clean -df，删除当前目录下没有被track过的文件和文件夹  
git clean -xf，删除当前目录下所有没有track过的文件，不管他是否是.gitignore文件里面指定的文件夹和文件  

git clean对于刚编译过的项目也非常有用. 如, 他能轻易删除掉编译后生成的.o和.exe等文件. 这个在打包要发布一个release的时候非常有用。  
下面的例子要删除所有工作目录下面的修改, 包括新添加的文件. 假设你已经提交了一些快照了, 而且做了一些新的开发  
git reset --hard  
git clean -df  
运行后, 工作目录和缓存区回到最近一次commit时候一摸一样的状态，git status会告诉你这是一个干净的工作目录, 又是一个新的开始了。  
[返回*专题*](#专题)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    

### git rebase -i  
将多个提交合并成一个提交。操作如下：  
$ git log --oneline  
f185c6e (HEAD -> for_rebase, master, for_reset) C5--Add file5  
6d4c76e C4--Add file4  
d8bef46 C3--Add file3  
8ce9fe8 C2--Add file2  
a63777b C1--Add file1  

如果想将C3 C4 C5三个提交合并成一个提交，怎么写？  

$ git rebase -i HEAD\~3  
弹出编辑框：  
pick d8bef46 C3--Add file3        -- *显示的前后次序和git log相反*  
pick 6d4c76e C4--Add file4  
pick f185c6e C5--Add file5  
\# Rebase 8ce9fe8..f185c6e onto 8ce9fe8 (3 commands)  
\#
\# Commands:  
\# p, pick = use commit  
\# r, reword = use commit, but edit the commit message  
\# e, edit = use commit, but stop for amending  
\# s, squash = use commit, but meld into previous commit  
\# f, fixup = like "squash", but discard this commit's log message  
\# x, exec = run command (the rest of the line) using shell  
\# d, drop = remove commit  
将C4、C5前面的pick改为squash，就可以将C4、C5合并到C3，形成一个提交。  
根据提示：\# s, squash = use commit, but meld into previous commit，将某个提交融合到(meld into)比自己更早(previous)的提交上，也就是说只能将新的提交合并到旧的提交，但是不能将旧的提交合并到新的提交。上例中只能将C4、C5合并到C3，但反过来不行，不能将C3合并到C4，否则报错。    

git rebase -i进阶  
$ git rebase -i [start] [end]  
① (start, end]前开后闭区间，从start到end为止，包括start、不包括end。  
② 默认省略end，表示当前最新提交HEAD，git rebase -i SHA == git rebase -i SHA HEAD。  
③ start为旧的提交, end为新的提交，git rebase -i [start] [end] == git rebase -i [old] [new]。从start到end，从旧到新。  

base，基，基础，起点。  
旧的提交是新的提交的base(基)，旧的提交在前、新的提交在后，新的提交建立在旧的提交的基础之上。  
rebase， re-base， 重新(re)定义基(base)。  

[返回*专题*](#专题)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#git)    


## 网址收藏
https://learngitbranching.js.org/  
http://www.softwhy.com/qiduan/git_course/  
https://github.com/wangdoc/git-tutorial  
[*返回目录*](#git)    

