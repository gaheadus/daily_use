1.**ssh**  
ssh的安装和配置  
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
$ ssh sgk@192.168.119.128  //默认22端口，不需要写，ssh -p 22 sgk@192.168.119.128  
第三方工具，如putty、mobaXterm。  


解决ssh连接经常掉线  
服务器端配置（Ubuntu）  
vim /etc/ssh/sshd_config  
修改如下：  
ClientAliveInterval 30     \#服务器每隔多少秒发送心跳包给客户端，测试是否存活  
ClientAliveCountMax 9999 \#上述多少次心跳无响应之后，会认为Client已经断开  
所以，总共允许无响应的时间是30 * 9999 秒  
重启sshd服务：/etc/init.d/ssh restart。  

客户端配置（Linux）  
如果是让主机所有用户都生效，修改/etc/ssh/ssh_config  
如果涨姿势让本人生效，修改~/.ssh/config  
Host \*  
    ServerAliveInterval 30  # 每隔30s向服务器发出一次心跳  
    ServerAliveInterval 100  # 超过100次请求都没有到发送成功则断开与服务器端的连接  
服务器端、客户端都要设置才有用，单独设置服务器端不起作用。  

客户端配置（windows MobaXterm SSH连接）  
在使用MobaXterm的ssh服务连接远程服务器（如Linux）时，在一段无操作时间，系统会自动断开连接的问题。  
Settings -> Configuration -> SSH -> SSh settings，选中SSH keepalive  
测试MobaXterm这么设置有效。20210401  


2.**samba**  
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

samba服务添加用户（假设我的ubuntu用户名为：dukang）  
sudo smbpasswd -a dukang  
（输入访问Samba的密码）  

service smbd restart     //重启  
在Windows下访问共享目录，可点击运行，输入 \\192.168.0.203\share，这样就能以匿名用户访问共享目录share了。  



3.**远程桌面**  
①Ubuntu打开设置，系统->首选项->桌面共享  
将【允许其他人查看您的桌面】这一项勾上，然后在安全那项，勾选【要求远程用户输入此密码】，并设置远程密码。并且我们取消勾选【必须为对本机器的每次访问进行确定】（这样做，是为了被远程的时候不需要再确认，否则每次远程都要人为确认才能被远程，会很繁琐）如图所示  
②apt-get install xrdp vnc4server xbase-clients  
③apt-get install dconf-editor  
安装完成之后，我们需要打开dconf-editor工具，在桌面搜索dconf-editor打开  
打开之后，依次展开org->gnome->desktop->remote-access，然后取消 “require-encryption”的勾选即可。  
④windows连接远程桌面  
方法1：mstsc。win+r，输mstsc，**选择模式vnc-any**，输入ip地址、密码，连接。  
方法2：MobaXterm，Sessions -> New session -> VNC，同上。这种方式会自动适配本地显示的宽高度。  
       MobaXterm有多种远程桌面连接的方式：rdp、xdmcp、VNC。  
备注：是不是可以同时多人远程登录？-- 可以  


4.**vi/vim**  
Ubuntu下vim默认显示行号  
$ vim /etc/vim/vimrc  //在末尾添加set number  
cygwin默认显示行号  
vim ~/.vimrc   //在末尾添加set number  
