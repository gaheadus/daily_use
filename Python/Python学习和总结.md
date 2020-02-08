https://www.python.org/ ，官网  
https://docs.python.org/zh-cn/3/ ，  
https://docs.python.org/zh-cn/3/tutorial/index.html ， Python 教程  
https://docs.python.org/zh-cn/3/library/index.html#library-index ， Python 标准库  
https://docs.python.org/zh-cn/3.8/c-api/index.html ， Python API  
https://docs.python.org/zh-cn/3/reference/index.html ， Python 语言参考  

https://docs.pythontab.com/python/python3.4/controlflow.html#if ， Python3 中文手册 3.5.2 文档  
https://www.w3cschool.cn/python/dict ， Python速查  
https://www.runoob.com/python/python-tutorial.html ， Python基础教程  


# 串口操作
## pyserial安装  
下载pyserial-3.4.tar.gz，下载地址:https://pypi.org/project/pyserial/#files。  
下载完后，解压缩到指定目录，如D:\Python\Python38\Lib\pyserial\pyserial-3.4。  
打开cmd目录窗口，进入到解压缩目录，  
D:\Python\Python38\Lib\pyserial\pyserial-3.4> python setup.py build  
D:\Python\Python38\Lib\pyserial\pyserial-3.4> python setup.py install  

\# serial_test.py  
``` Python
import serial
import serial.tools.list_ports

plist = list(serial.tools.list_ports.comports())
if len(plist) <= 0:
    print("the serial port can't find")
else:
    plist_0 = list(plist[0])
    serialName = plist_0[0]
    serialFd = serial.Serial(serialName, 9600, timeout=60)
    print("check which[%s] port was really used>" % serialFd.name)

    for port in plist:
        print("port is : %s\n" % port)

try:
    serialFd
except NameError:
    print("serial open fail")
else:
    print("start read serial")
    while True:
        data = serialFd.read()
        print(data)
```

