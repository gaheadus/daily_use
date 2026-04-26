# 1. 配置与初始化 (Config & Init)  
### config  
git config \--list  
git config \--global user.name "name"  
git config \--global user.email "email"  
git config user.name //查看  
git config \--global core.editor "vim"  
git config \--global alias.\<alias\> \<command\>  
git config \--global alias.br branch  
git config \--global alias.ci commit  
git config \--global alias.st status  
git config \--local  
git config \--system  
git config \--unset \<key\>  
git config \--global \--unset \<key\>  


生成SSH Key：  
\$ ssh-keygen -t rsa -C "youremail@example.com"  
\$ ssh-keygen -t ed25519 -C "Gitee SSH Key"  
\$ cat \~/.ssh/id_ed25519.pub，复制公钥，设置到github/gitee网页。  
通过 ssh -T 测试，输出 SSH Key 绑定的用户名：  
\$ ssh -T git@gitee.com  

### init  
git init  
git init -b main  

### help  
git help  
git add \--help  
git commit \--help  

### version  
git version  

# 2. 日常开发与提交 (Add, Commit, Status, Log)  
### status  
git status  
git status -s //简洁版状态输出  

### add  
git add src/test.c  
git add src  
git add \*.c  
git add . //添加所有修改、新增文件到暂存区  
git add -u //只添加已追踪文件的修改/删除  
git add -A //等同于 add . + add -u，全部提交暂存，同git add \--all  
git add -f //强制添加忽略的文件  
git add -p //交互式添加，用于精细控制提交内容  

### commit  
git commit  
git commit -m "feat: add new feature"  
git commit -a -m "fix: fix bug"  
git commit \--amend  
git commit \--amend -m "update commit message"  
git commit \--amend \--no-edit  
git commit -v //显示diff  
git commit -s //sign-off  
git commit -S //GPG签名  
git commit \--allow-empty -m "chore: trigger CI build"  

### rm  
基础删除操作  
用于从工作区和暂存区同时删除文件。  
git rm test.c  
git rm src/test.c  
git rm \*.log  
git rm -r directory\_name  
git rm -r src/  
git rm file1.txt file2.txt  
仅停止跟踪 (保留本地文件)  
常用于配合 .gitignore，将已提交的文件(如 node\_modules 或配置文件)移出Git管理，但保留在本地磁盘。  
git rm \--cached test.c  
git rm \--cached -r directory\_name  
git rm \--cached src/  
git rm -r \--cached node\_modules/  
git rm \--cached \*.log  
强制与特殊删除  
用于处理文件已被修改未暂存，或需要模拟删除的情况。  
git rm -f test.c  
git rm \--force test.c  
git rm -f -r directory\_name  
git rm \--dry-run test.c  
git rm \--dry-run -r .  
git rm \--ignore-unmatch test.c  
删除后的恢复操作  
如果误删了文件，可以使用以下命令恢复(参考自搜索结果)。  
git checkout HEAD \-- test.c  
git checkout HEAD \-- src/  
git restore test.c  
git restore \--source=HEAD~1 \-- test.c  
git reset HEAD test.c  

### diff  
git diff //查看工作区 vs 暂存区改动  
git diff \--staged //查看暂存区 vs 本地仓库改动  
git diff \--cached //同\--staged  
git diff src/test.c  
git diff HEAD  
git diff main //查看当前分支与main分支的差异  
git diff \<commit1\> \<commit2\>  
git diff \--name-only  
git diff \--stat  
git diff \<branch1\>..\<branch2\>  
git diff \--word-diff  

### log  
git log  
git log \--oneline  
git log \--graph \--oneline \--all \--decorate //查看带分支装饰的图形化历史  
git log -n 5  
git log -p //显示diff，查看提交的具体差异  
git log \-- filename //文件历史  
git log \--name-status  
git log \--name-only  
git log \--stat  
git status -s //short  
git status -sb //short with branch  
git status \--ignored  
git log \--author="Name"  
git log \--grep="keyword"  
git log \--since="2 weeks ago"  
git log \--until="2023-12-31"  
git log \--follow //跟踪重命名  

### shortlog  
git shortlog //汇总提交日志，按作者分组显示。  

### ls-files  
git ls-files //查看已追踪文件  

### reflog  
git reflog  
git reflog -n 10  
git reflog show \--all  
git reflog show \<branch\>  
git reflog expire \--expire=now \--all  
git reflog delete \<ref\>  

### show  
git show a1b2c3d //查看某次提交的详细信息和差异  
git show a1b2c3d:test.c //查看某次提交中某个文件的内容  
git show HEAD  
git show HEAD:test.c  
git show v1.0.0  
git show \--name-only SHA  
git show \--name-status SHA  
git show \--stat SHA  

### grep  
git grep //在代码库中搜索指定的文本  
git grep "function\_name"  
git grep "TODO"  

### blame  
git blame test.c //查看文件每一行的修改人和修改时间  
git blame -L 10,20 test.c //查看文件第10到20行的修改记录  
git blame -w //忽略空白  
git blame -C //检测移动  
git blame -M  
git blame \<commit\> \-- \<file\>  

# 3. 分支管理 (Branch, Checkout, Switch, Worktree)  
### branch  
git branch  
git branch -v  
git branch -a  
git branch -r  
git branch dev //创建新分支  
git branch -d dev  
git branch -D dev  
git branch -m old\_name new\_name  
git branch \--merged  
git branch \--no-merged  
git branch \--set-upstream-to=origin/\<branch\>  
git branch \--unset-upstream  
git branch \--contains \<commit\>  

### switch  
git switch \<branch\>  
git switch -c \<new-branch\>  //创建并切换  
git switch -C \<new-branch\>  //强制  
git switch \--detach \<commit\>  
git switch - //切换到上一个分支  

### worktree  
git worktree list  
git worktree add ../project-dev dev  
git worktree remove ../project-dev  
git worktree move ../project-old ../project-new  
git worktree repair ../project  
git worktree lock ../project  
git worktree lock \--reason "comments" ../project  
git worktree unlock ../project  
git worktree add \<path\> \<branch\>  
git worktree add -b \<new-branch\> \<path\> \<commit>  



# 4. 远程同步 (Push, Pull, Clone, Remote)  
### clone  
git clone https://github.com/user/repo.git  
git clone -b dev https://github.com/user/repo.git  
git clone \--depth 1 https://github.com/user/repo.git  

### remote  
git remote -v  
git remote add \<name\> \<url\>  
git remote remove \<name\>  
git remote rename \<old\> \<new\>  
git remote set-url \<name\> \<newurl\>  
git remote add origin https://github.com/user/repo.git  
git remote remove origin  
git remote set-url origin https://new-url.git  
git remote show \<name\>  
git remote prune \<name\>  
git remote update  

### push  
git push  
git push origin main  
git push -u origin main  
git push \--force  
git push \--force-with-lease //安全地强制推送，比 \--force 更安全  
git push origin \--delete dev  

### pull  
git pull  
git pull origin main  
git pull \--rebase  
git pull \--rebase origin main  
git pull \--ff-only  
git pull \--no-ff  
git pull -v  

### fetch  
git fetch  
git fetch \--all  
git fetch origin main  
git fetch \--prune  

# 5. 合并与变基 (Merge, Rebase, Cherry-pick)  
### merge  
git merge dev  
git merge \--no-ff //保留分支记录的合并  
git merge \--ff-only  
git merge \--abort  
git merge \--continue  
git merge -m "message"  
git merge \--no-commit  
git merge \--no-ff dev //禁用快进合并，保留分支历史  
git merge \--squash feature //将分支的所有提交压缩成一个提交合并进来  

### rebase  
git rebase main //将当前分支变基到main分支之上  
git rebase -i HEAD~3 //交互式变基，整理最近3次提交  
git rebase \--abort  
git rebase \--continue  
git rebase \--skip //跳过当前引起冲突的提交  
git rebase \--onto main dev feature //将feature分支从dev之上迁移到main之上  

### cherry-pick  
git cherry-pick \<commit\>  
git cherry-pick \<commit1\> \<commit2\> ...  
git cherry-pick \<commit1\>..\<commit2\>  //范围，拣选一个区间的提交  
git cherry-pick \--abort  
git cherry-pick \--continue  
git cherry-pick -n 5d3a1b2 // \--no-commit  
git cherry-pick -x 5d3a1b2 //记录来源  

# 6. 撤销与重置 (Reset, Revert, Clean, Stash)  
### reset  
git reset HEAD test.c  
git reset \--soft HEAD^  
git reset \--mixed HEAD^  
git reset \--hard HEAD^  
git reset \--hard SHA  
git reset \--hard origin/main //将本地分支强行重置为和远程分支一模一样  

### revert  
git revert SHA  
git revert HEAD  
git revert -n HEAD  

### restore  
git restore 是 Git 2.23 版本引入的新命令，专门用于撤销修改**或**恢复文件，旨在替代 git checkout 的文件恢复功能，语义更加清晰。  
恢复工作区文件 (丢弃修改)  
用于放弃工作区(Working Directory)中未提交的修改，将文件还原到暂存区或最新提交的状态。  
git restore test.c  
git restore src/test.c  
git restore .  
git restore src/  
git restore \*.js  
git restore file1.txt file2.txt  
撤销暂存 (Unstage)  
用于将文件从暂存区(Staging Area)移出，还原到工作区，保留你的修改内容。相当于旧版的 git reset HEAD \<file\>。  
git restore \--staged test.c  
git restore \--staged src/  
git restore \--staged .  
git restore -S test.c  
git restore \--staged file1.txt file2.txt  
恢复到指定版本 (历史版本)  
用于从特定的提交(Commit)、分支或标签中恢复文件内容。  
git restore \--source=HEAD test.c  
git restore -s HEAD^ test.c  
git restore \--source=main test.c  
git restore \--source=v1.0.0 test.c  
git restore \--source=5d3a1b2 test.c  
git restore \--source=origin/main src/  
彻底重置 (工作区 + 暂存区)  
用于同时重置工作区和暂存区，彻底丢弃所有未提交的修改(包括 git add 过的和没 git add 的)，相当于旧版的 git reset \--hard(针对文件)。  
git restore \--staged \--worktree test.c  
git restore -SW test.c  
git restore \--staged \--worktree .  
git restore \--source=HEAD \--staged \--worktree test.c  
交互式恢复 (Patch)  
用于只恢复文件中的部分修改，Git 会逐块询问你是否要恢复。  
git restore \--patch test.c  
git restore -p test.c  
git restore -p src/  
git restore \--patch \--staged test.c  
恢复被删除的文件  
如果你误删了文件(rm test.c)，且尚未提交删除操作，可以用此命令找回。  
git restore test.c  
git restore src/deleted\_file.txt  
常用参数速查表  
| 参数 | 简写 | 作用 | 场景 |
| --- | --- | --- | --- |
| \--staged | -S | 仅恢复暂存区 | 撤销 git add，保留代码修改 |
| \--worktree | -W | 仅恢复工作区 | 丢弃代码修改(默认行为) |
| \--source | -s | 指定来源 | 恢复到某个分支或历史版本 |
| \--patch | -p | 交互模式 | 选择性恢复部分代码块 |
| \--ignore-unmerged | - | 忽略未合并 | 在冲突解决时使用 |

### checkout  
git checkout \-- test.c  
git checkout HEAD \-- test.c  
git checkout main  
git checkout -b dev  
git checkout -b \<branch\> \<start-point\>  
git checkout -  
注意：Git 2.23后推荐使用 switch 替代 checkout 进行分支切换。  

### stash  
git stash  
git stash push -m "temp work"  
git stash save "wip: unfinished login" //旧命令  
git stash list  
git stash show stash@{0}  
git stash show stash@{0} -p  
git stash branch \<branch\>  
git stash apply //恢复储藏，保留储藏记录  
git stash pop //恢复最近一次储藏并删除记录  
git stash apply stash@{0}  
git stash drop //删除最近一条储藏  
git stash drop stash@{0}  
git stash clear //清空所有储藏  

### clean  
git clean -f //强制删除未跟踪的文件  
git clean -fd //强制删除未跟踪的文件和目录  
git clean -fx //删除忽略文件  
git clean -i //interactive  
git clean -n //查看将要被删除的未跟踪文件，空跑测试  

# 7. 补丁与邮件工作流 (Format-patch, Am)  
### format-patch  
git format-patch -1 //将最近一次提交生成为补丁文件  
git format-patch -1 HEAD  
git format-patch -2 HEAD  
git format-patch HEAD~3 //将最近3次提交生成为补丁文件  
git format-patch main //生成从main分支分叉后到当前HEAD的所有补丁  
git format-patch -o ./patches origin..HEAD  
git format-patch -o dir  
git format-patch \--cover-letter  

### am  
git am 0001-fix-bug.patch  
git am -3 0001-fix-bug.patch // three-way  
git am \--abort  
git am \--continue  
git am \--skip  
git am \--reject  

### apply  
git apply //应用补丁文件，通常由git diff生成  

# 8. 标签管理 (Tag)  
### tag  
git tag //查看所有标签  
git show [tagname] // 查看标签详情  
git tag -l "pattern"  
git tag \<tagname\> //创建轻量标签  
git tag -a \<tagname\> -m "message" //annotate，创建带备注的附注标签  
git tag -s \<tagname\> -m "message" //signed  
git tag -d \<tagname\>  
git push origin \<tagname\>  
git push \--tags  
git push origin \--tags  
git push origin \--delete \<tagname\>  
git tag -f \<tagname\>  //force  

# 9. 其他实用命令 (Reflog, Show, Grep)  
### bitsect  

### gc  
git gc  

### fsck  
git fsck  

# 10. 低级(管道)命令  
cat-file  
checkout-index  
commit-tree  
hash-object  
index-pack  
ls-files  
ls-tree  
mktag  
mktree  
pack-objects  
read-tree  
symbolic-ref  
unpack-objects  
update-index  
update-ref  
write-tree  

# 11. 辅助工具  
annotate  
archive  
bundle  
citool  
gui  
instaweb  
mergetool  
notes  
p4  
replace  
request-pull  
stage  
stash  
submodule  
svn  
web\--browse  