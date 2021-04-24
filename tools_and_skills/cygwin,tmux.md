# 目录
- [cygwin](#cygwin)  
- [tmux](#tmux)  


# cygwin
- [安装cygwin](#安装cygwin)  
- [安装gcc/g++/gdb](#安装gccggdb)  

## 安装cygwin
**1.1 基本概念：工作区、暂存区、本地仓库、远程仓库**  

## 安装gcc/g++/gdb
方法一 图像界面安装  
•双击setup-x86_64.exe，一步一步安装。  
•选择boost_build这一项  
![再选择这四项](https://github.com/gaheadus/daily_use/blob/master/Resources/%E9%80%89%E6%8B%A9boost_build%E8%BF%99%E4%B8%80%E9%A1%B9.png)  
•再选择这四项  
![再选择这四项](https://github.com/gaheadus/daily_use/blob/master/Resources/%E5%86%8D%E9%80%89%E6%8B%A9%E8%BF%99%E5%9B%9B%E9%A1%B9.png)  
•及gdb  
![再选择这四项](https://github.com/gaheadus/daily_use/blob/master/Resources/%E5%8F%8Agdb.png)  

  

方法二 命令行安装gcc/g++  
安装cygwin如果按照默认的方式一直点下去的话，安装完了会发现没有安装gcc/g++。  
这个时候可以在安装文件的目录打开命令行，并输入：  
setup-x86_64.exe -q -P wget -P gcc-g++ -P make -P diffutils -P libmpfr-devel -P libgmp-devel -P libmpc-devel  
其中，"setup-x86_64.exe"对应安装文件的名称。  
接着就会出来安装的界面，等待下载完成即可。  

[返回*目录*](#目录)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#目录)    


# tmux
- [安装tmux](#安装tmux)  
- [配置鼠标支持](#配置鼠标支持)  
- [tmux命令](#tmux命令)  
- [tmux快捷键](#tmux快捷键)  

## 安装tmux
$ apt install tmux  /  $ apt-cyg install tmux  
$ tmux //启动tmux，按ctrl+d或输exit退出tmux返回原来shell  

## 配置鼠标支持
tmux配置鼠标支持，在~/.tmux.conf文件中（如果没有这个配置文件的话先创建），增加：set-option -g mouse on ，重启tmux即可。  
鼠标支持的内容：  
•用鼠标点击窗格来激活该窗格；  
•用鼠标拖动调节窗格的大小（拖动位置是窗格之间的分隔线）；  
•用鼠标点击来切换活动窗口（点击位置是状态栏的窗口名称）；  
•开启窗口/窗格里面的鼠标支持，用鼠标回滚显示窗口内容，按下shift的同时用鼠标左键选取文本、右键进行复制粘贴，或ctrl+shift+c、ctrl+shift+v进行复制粘贴。注意全程按住shift。  
鼠标操作，比命令/快捷键操作方便多了。  
调整窗格大小：将鼠标指针放到窗格边界线上，点击边界线按住鼠标左键拖动。  


## tmux命令
$ tmux //启动tmux，按ctrl+d或输exit退出tmux返回原来shell  

会话相关命令：  
查看已有会话：tmux ls  
新建会话：tmux new -s <session-name>  
接入会话：tmux attach -t <session-name> 或 tmux a -t 0  
重命名会话：tmux rename-session -t 0 <new-name>  
切换会话：tmux switch -t <session-name> 或 tmux s -t 0  
杀死会话：tmux kill-session -t <session-name> 或 tmux kill-session -t 0  

窗格相关命令：  
$ tmux split-window  //划分上下两个窗格 -- 鼠标操作比命令更方便  
$ tmux split-window -h  //划分左右两个窗格  
$ tmux select-pane -U   //光标切换到上方窗格  
$ tmux select-pane -D   //光标切换到下方窗格  
$ tmux select-pane -L   //光标切换到左边窗格  
$ tmux select-pane -R   //光标切换到右边窗格  
$ tmux swap-pane -U  //当前窗格上移  
$ tmux swap-pane -D  //当前窗格下移  

## tmux快捷键
tmux 有大量快捷键，所有的快捷键都需要通过前缀键唤起，默认的前缀键是ctrl+b -- 先按ctrl+b，然后再按其他键，如按n就可以切换到下一个窗口。  
常用快捷键  
ctrl+b <arrow key>：光标切换到其他窗格。<arrow key>是指向要切换到的窗格的方向键，比如切换到下方窗格，就按方向键↓。  
ctrl+b x：关闭当前窗格。  
ctrl+b !：将当前窗格拆分为一个独立窗口。  
ctrl+b z：当前窗格全屏显示，再使用一次会变回原来大小。  
ctrl+b ctrl+<arrow key>：按箭头方向调整窗格大小。  

列出所有快捷键的命令：tmux list-keys  
2.1、会话的快捷键  
s：列出所有会话  
d：离开当前会话  
$：重命名当前会话  
2.2、窗口的快捷键  
c：创建一个新窗口  
n：切换到下一个窗口  
w：从列表中选择窗口  
<0~9>：切换到指定编号的窗口，编号显示在状态栏  
,：窗口重命名  
2.3、窗格的快捷键  
%：分成左右两个窗格  
"：分成上下两个窗格  
z：当前窗格全屏显示，再按一次恢复  
q：显示窗格编号  
t：在当前窗格显示时间  
<arrow key>：光标切换到其他窗格  
o：光标切换到下一个窗格  
{：左移当前窗格  
}：右移当前窗格  
ctrl+o：上移当前窗格  
Alt+o：下移当前窗格  
space：切换窗格布局  

[返回*目录*](#目录)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#目录)    




