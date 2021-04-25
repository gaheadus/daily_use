# 一.ssh

## ssh的安装和配置
1.更新vim  
$ apt-get remove vim-common  
$ apt-get install vim  
2.安装sshd 远程访问  
apt-get install openssh-server  
/etc/init.d/ssh restart  
修改/etc/ssh/sshd_config文件，修改如下：  
    PermitRootLogin修改为yes  
    PubkeyAuthentication修改为no  
    AuthorizedKeysFile .ssh/authorized_keys前面加上#屏蔽掉  
    PasswordAuthentication修改为yes  

windows自带ssh工具，并不需要第三方工具。  
$ ssh dukang@192.168.119.128  //默认22端口，不需要写，ssh -p 22 dukang@192.168.119.128  
第三方工具，如putty、mobaXterm。  


## 解决ssh连接经常掉线
客户端配置(windows MobaXterm SSH连接)  
在使用MobaXterm的ssh服务连接远程服务器(如Linux)时，在一段无操作时间，系统会自动断开连接的问题。  
Settings -> Configuration -> SSH -> SSh settings，选中SSH keepalive  
测试MobaXterm这么设置有效。20210401  

不使用MobaXterm则需要在服务器端和客户端都进行配置，如下：
**服务器端配置(Ubuntu)**：  
vim /etc/ssh/sshd_config  
修改如下：  
ClientAliveInterval 30     \#服务器每隔多少秒发送心跳包给客户端，测试是否存活  
ClientAliveCountMax 9999 \#上述多少次心跳无响应之后，会认为Client已经断开  
所以，总共允许无响应的时间是30 * 9999 秒  
重启sshd服务：/etc/init.d/ssh restart。  
**客户端配置(Linux)**：  
如果是让主机所有用户都生效，修改/etc/ssh/ssh_config  
如果涨姿势让本人生效，修改~/.ssh/config  
Host \*  
    ServerAliveInterval 30  # 每隔30s向服务器发出一次心跳  
    ServerAliveInterval 100  # 超过100次请求都没有到发送成功则断开与服务器端的连接  
服务器端、客户端都要设置才有用，单独设置服务器端不起作用。  


## 使用ssh运行远程电脑上的图形界面程序
使用ssh运行远程电脑上的图形界面程序(也能运行远程桌面)，特别适用于没有显示器的远程服务器。参考：http://www.iis7.com/a/nr/1916396.html  
一、Ubuntu服务器安装运行SSH服务  
$ apt-get install openssh-server //安装ssh server  
$ vim /etc/ssh/sshd_config //**配置允许X11转发命令,设置选项 X11Forwarding yes**。  
$ /etc/init.d/ssh restart //启动服务  
二、客户端连接Ubuntu服务器  
①在windows客户端连接  
MobaXterm自带Xserver功能，推荐。MobaXterm的xserver是自动开启的，settings -> X11 -> Automaticly start X server at MobaXterm start up。对应的远程桌面登录工具是xdmcp。  
**程序跑在远程Ubuntu上，但是程序界面UI显示在本地windows上，让人感觉上去好像程序就是直接跑在windows上一样。有意思。**  
MobaXterm打开一个本地命令行窗口，输入**ssh -X dukang@192.168.1.107**登录远程Ubuntu,然后输xclock命令可以将xclock程序的UI界面启动到windows本地，输firefox命令可以将firefox浏览器的UI界面启动到windows本地，输gnome-session命令可以将远程Ubuntu的桌面启动到本地windows。  
区别：ssh -X dukang@192.168.1.107可以用ssh命令的方式运行图形界面程序，但ssh dukang@192.168.1.107不能。  
注：ssh -X登录后不能切换用户，切换用户后无法以上述方式启动Ubuntu图形界面程序。某些需要超级权限的操作只能使用sudo command来执行。  
也可以不ssh登录到远程Ubuntu，直接在MobaXterm执行本地命令就能运行Ubuntu图形程序：**MobaXterm本地命令窗口执行$ ssh -X dukang@192.168.1.107 firefox，和先$ ssh -X dukang@192.168.1.107登录远程电脑，再输firefox打开firefox，两者结果是一样的。**  
使用ssh -X dukang@192.168.1.107 gnome-session打开Ubuntu远程桌面，和MobaXterm自带的xdmcp是一样的。  

②在Ubuntu客户端连接  
安装ssh客户端命令:  
$ apt-get install openssh-client  
配置允许X11转发命令:  
$ vim /etc/ssh/ssh_config //设置选项  
ForwardAgent yes  
ForwardX11 yes  
ForwardX11Trusted yes //这个要设置，上面二项可以不要  
连接命令:  
$ ssh -X user@server_ip "program" //直接运行一个程序  
$ ssh -X user@server_ip //先登陆再运行程序  



# 二.samba
apt-get install samba  
apt-get install smbclient  
apt-get install samba-common system-config-samba python-glade2 gksu  
建立共享目录  
mkdir -p /home/dukang/work  
修改配置文件  
vim  /etc/samba/smb.conf  
添加以下内容  
[share]  
comment = share folder  
browseable = yes  
path = /home/dukang/work  
create mask = 0700  
directory mask = 0700  
valid users = dukang  
force user = dukang  
force group = dukang  
public = yes  
available = yes  
writable = yes  

samba服务添加用户(假设我的ubuntu用户名为：dukang)  
sudo smbpasswd -a dukang  
(输入访问Samba的密码)  

service smbd restart     //重启  
在Windows下访问共享目录，可点击运行，输入 \\192.168.0.203\share，这样就能以匿名用户访问共享目录share了。  



# 三.远程桌面

## (推荐)windows远程访问ubuntu(ubuntu自带远程共享、原生桌面)
①Ubuntu打开设置，系统->首选项->桌面共享  
将【允许其他人查看您的桌面】这一项勾上，然后在安全那项，勾选【要求远程用户输入此密码】，并设置远程密码。并且我们取消勾选【必须为对本机器的每次访问进行确定】(这样做，是为了被远程的时候不需要再确认，否则每次远程都要人为确认才能被远程，会很繁琐)如图所示  
②apt-get install xrdp vnc4server xbase-clients  
③apt-get install dconf-editor  
安装完成之后，我们需要打开dconf-editor工具，在桌面搜索dconf-editor打开  
打开之后，依次展开org->gnome->desktop->remote-access，然后取消 “require-encryption”的勾选即可。  
④windows连接远程桌面  
方法1：mstsc。win+r，输mstsc，**选择模式vnc-any**，输入ip地址、密码，连接。  
方法2：MobaXterm，Sessions -> New session -> VNC，同上。这种方式会自动适配本地显示的宽高度。  
       MobaXterm有多种远程桌面连接的方式：rdp、xdmcp、VNC。  
备注：是不是可以同时多人远程登录？-- 可以  

## 向日葵 / teamviewer等 -- 推荐
向日葵/teamviewer等软件不仅可用于局域网远程登录，也可用于广域网异地远程登录。  
向日葵软件有windows、linux、android等版本。Linux不仅有图形版，也有命令行版。PS：命令行版没用起来。  
向日葵Ubuntu版图形界面安装后，重开机会自动启动。免去配置的烦恼。  
向日葵远程桌面支持同时多个用户登录。推荐。  
---- 用这种软件，可能会有信息泄露。被人远程控制用来挖矿之类的。20210414  

技巧：无显示器的情况下使用启动远程Ubuntu的向日葵图形版  
参考：ssh登录远程图形界面  
$ ssh -X dukang@192.168.1.107  
$ firefox //打开远程Ubuntu的firefox，下载向日葵图形版，https://sunlogin.oray.com/，sunloginclient-11.0.0.36662-amd64.deb  
$ dpkg -i sunloginclient-11.0.0.36662-amd64.deb  
$ /usr/local/sunlogin/bin/sunloginclient  //启动Ubuntu向日葵（退出图形界面后仍然在后台运行）  
后续就可以在windows上用向日葵连接Ubuntu了。  
MobaXterm使用ssh -X dukang@192.168.1.107 gnome-session远程桌面不稳定、占内存、偶尔进程奔溃，相比较而言向日葵使用简单、稳定，当然用“(推荐)windows远程访问ubuntu 16.04 / ubuntu 18.04”一节的方式使用远程桌面最好，不需要第三方软件，简单、稳定。  
在没有界面的情况下，使用MobaXterm ssh -X dukang@192.168.1.107 gnome-session远程安装、打开向日葵图形版，然后在windows上用向日葵远程连接Ubuntu，切换到更稳定的向日葵远程桌面，后面就可以关闭Ubuntu向日葵图形界面了：向日葵仍然会在后台运行。  
小结：只要能用ssh，就有办法登录远程桌面。  

# 四.todo
