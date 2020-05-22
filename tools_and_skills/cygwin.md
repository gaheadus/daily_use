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

[返回*目录*](#cygwin)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#cygwin)    
