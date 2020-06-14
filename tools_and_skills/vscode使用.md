# vscode
- [快捷键](#快捷键)  
- [插件](#插件)  
- [第一个程序](#第一个程序)  


## 快捷键
F1 / Ctrl + Shift + P :  Show All Commands  
Ctrl + P          :   Go to File  
Ctrl + Shift + F    :   Find in Files  
F5              :    Start Debugging  
Ctrl + `          :    Toggle Terminal  



## 插件
**1.C/C++ for Visual Studio Code**  
This preview release of the C/C++ extension adds language support for C/C++ to Visual Studio Code, including features such as IntelliSense and debugging.


**2.C/C++ Project Generator**  
Create C/C++ projects  

Features  
Project will generate the following:  
Project structure: Common folders like src, include and bin Makefile: A makefile already set up to build and run your project VSCode task: Configurations for building and running your project  

Requirements  
If you are on linux you must install gcc and make  
If you are on window you must install mingw  

How to use  
Go to command pallete (usually : ctrl + shift + p)  
Search for "Create C project" or "Create c++ project" depending on your preference  
Select the folder where the project should be created  
That's it, project will open  


**3.C/C++ Compile Run**  
An extension running on Visual Studio Code to Compile & Run single c/c++ files easly  

Features  
Compile & Run C/C++ opened file directly from the command pallet or by pressing 'f6' or 'f7'  

Requirements  
If you are on linux you must install gcc  
If you are on window you must install mingw  

How to use  
Make sure you have .c or .cpp file open. Press "F6", this will compile and run the file using default arguments in settings. Or press "F7", this will use the arguments you specify for the program. If you want to register gcc/g++ path manually, you can set it under settings. You can also set to save file before compiling.  


**4.mingw / gcc**  


## 第一个程序
**1.创建一个C工程**  
安装完C/C++ Project Generator插件后，按ctrl + shift + p或f1，打开vscode命令窗口，输入create命令，弹出如下：  
![vscode创建一个工程](https://github.com/gaheadus/daily_use/blob/master/Resources/vscode%E5%88%9B%E5%BB%BA%E4%B8%80%E4%B8%AA%E5%B7%A5%E7%A8%8B.png)  
选择创建C工程，弹出对话框，选择想要新建工程所在的目录，新建一个文件夹，然后选择刚才新建的文件夹，确认。这样就新建一个C工程了。  
![vscode生成一个工程](https://github.com/gaheadus/daily_use/blob/master/Resources/vscode%E7%94%9F%E6%88%90%E4%B8%80%E4%B8%AA%E5%B7%A5%E7%A8%8B.png)  
新建工程后自动生成如上目录结构，也自动生成main.c文件。  

也可以选择一个已有工程所在文件夹，打开已有工程。  

**2.执行**  
按F5编译、执行(提前配置好mingw / gcc)。  

或者：按**Ctrl+`键**打开命令行窗口，手动使用命令编译、执行。  
和在cmd窗口使用命令行是一样的，例如，编译：gcc main.c -o test，执行：./test。  
这样做的好处是可以使用自己熟悉的命令来编译执行，不需要每个工程都配置launch.json / tasks.json。  


[返回*目录*](#vscode)  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;  [*返回目录*](#vscode)    
