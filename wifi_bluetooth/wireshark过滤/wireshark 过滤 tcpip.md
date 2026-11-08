# tcp/ip过滤
## tcp/ip过滤
| 过滤器 | 功能 |  |  |
| --- | --- | --- | --- |
| ether src host 74:25:8a:c4:f7:7a | 源MAC地址为74:25:8a:c4:f7:7a的数据包 |  |  |
| src host 10.88.14.119 | 源ip地址为10.88.14.119的数据包 |  |  |
| host 10.88.14.119 | ip地址为10.88.14.119的数据包 |  |  |
| not host 10.88.14.119 | 除了ip地址为10.88.14.119的其他数据包 |  |  |
| ip | ipv4的数据包 |  |  |
| tcp | tcp协议的数据包 |  |  |
| port 23 | tcp端口为23或者udp端口为23的数据包 |  |  |
| tcp src port 23 | 源端口为23的tcp数据包 |  |  |
| tcp dst port 23 | 目标端口为23的tcp数据包 |  |  |
| tcp dst portrange 21-23 | 目标端口为21-23的tcp数据包 |  |  |
| tcp src port 2000 and tcp dst port 23 | 源端口为2000且目标端口为23的tcp数据包 |  |  |
| eth.addr == 74:25:8a:c4:f7:7a | MAC地址为74:25:8a:c4:f7:7a的数据包 |  |  |
| eth.src == 74:25:8a:c4:f7:7a | 源MAC地址为74:25:8a:c4:f7:7a的数据包 |  |  |
| eth.dst == 74:25:8a:c4:f7:7a | 目标MAC地址为74:25:8a:c4:f7:7a的数据包 |  |  |
| eth.src == 74:25:8a:c4:f7:7a && eth.dst == a0:48:1c:a8:6e:90 | 源MAC地址为74:25:8a:c4:f7:7a且目标MAC地址为a0:48:1c:a8:6e:90的数据包 |  |  |
| arp | arp数据包 |  |  |
| arp.src.hw_mac == 74:25:8a:c4:f7:7a | 源硬件地址为74:25:8a:c4:f7:7a的arp数据包 |  |  |
| arp.dst.hw_mac == 74:25:8a:c4:f7:7a | 目标硬件地址为74:25:8a:c4:f7:7a的arp数据包 |  |  |
| icmp | icmp数据包 |  |  |
| icmp.type == 8 | icmp请求包 |  |  |
| icmp.type == 0 | icmp应答包 |  |  |
| ip | ipv4报文 |  |  |
| ip.addr == 10.88.14.119 | ip地址为10.88.14.119的数据包 |  |  |
| ip.src == 10.88.14.119 | 源ip地址为10.88.14.119的数据包 |  |  |
| ip.dst == 10.88.14.119 | 目标ip地址为10.88.14.119的数据包 |  |  |
| ip.src == 10.88.14.119 |  | ip.dst == 10.88.142.120 | 源ip地址为10.88.14.119或目标ip地址为10.88.142.120的数据包 |
| ip.ttl == 1 | 显示TTL为1的数据包 |  |  |
| tcp | tcp数据包 |  |  |
| tcp.port == 23 | tcp端口为23的数据包 |  |  |
| tcp.srcport == 23 | tcp源端口为23的数据包 |  |  |
| tcp.dstport == 23 | tcp目标端口为23的数据包 |  |  |
| tcp.srcport == 2000 && tcp.dstport == 23 | tcp源端口为2000且目标端口为23的数据包 |  |  |


## TCP/IP过滤 2  
`ip.addr == 192.168.1.100`           //源或目的任一是该IP  
`ip.src == 10.0.0.1`  
`ip.dst == 8.8.8.8`  
`ip.src == 192.168.1.0/24`  
`ipv6.addr == 2001:db8::1`  
`eth.addr == 00:1a:2b:cc:dd:ee`  
`eth.src == 00:1a:2b:cc:dd:ee`  

`tcp.port == 443`                    //源或目的443  
`tcp.srcport == 80`  
`tcp.dstport == 443`  
`udp.port == 53`  
`tcp.port >= 8000 && tcp.port <= 8100`  

`frame.len > 1000`                   //包长  
`frame.time_relative > 60`           //抓包开始60秒后  
`frame.time_delta > 0.5`             //与前一包间隔>0.5s  

复合字段 `ip.addr/tcp.port/eth.addr` 配 `!=` 有坑：  
`ip.addr != 10.0.0.5` 等价于“源不等于它 或 目的不等于它”，几乎恒真。排除某IP应写：`!(ip.addr == 10.0.0.5)`  


**arp**  
`arp.src.hw_mac == 00:1a:2b:3c:4d:5e`   //ARP发送端MAC  
`arp.dst.hw_mac == 00:1a:2b:3c:4d:5e`   //ARP目标MAC（通常全F）  
`arp && eth.src == 00:1a:2b:3c:4d:5e`   //该MAC发出的所有ARP  

**DNS**:  
`dns`  
`dns.qry.name == "example.com"`  
`dns.qry.name contains "example"`  
`dns.qry.type == 1`                  //A记录  
`dns.flags.response == 0`            //查询  
`dns.flags.response == 1`            //响应  
`dns.flags.rcode == 0`               //无错误  
`dns.flags.rcode == 3`               //NXDOMAIN  
`dns.a == 1.2.3.4`                   //解析到某IP  

**icmp**    
`icmp.type == 0`                     //echo reply  
`icmp.type == 8`                     //echo request  
`icmp.type == 3`                     //目标不可达  

**dhcp**    
`dhcp or dhcpv6`  

**others**  
`ftp or telnet`                      //明文协议重点看  
`smb or smb2`  
`ssh`  


**字符串、正则、字节切片、按层**  
`http.request.uri contains "/login"`  
`tcp contains "admin"`                  //任意TCP载荷包含admin  
`udp contains 81:60:03`                 //UDP头/载荷包含该字节序列  
`http.request.uri matches "gl=se$"`  
`sip.To contains "a1762"`  
`dns.qry.name matches "\\.google\\.com$"`  

**字节切片：从某协议偏移取N字节**  
`udp[8:3] == 81:60:03`              //UDP载荷偏移8字节起3字节  
`eth.src[0:3] == 00:06:5b`          //按OUI过滤厂商  
`tcp[0:2] == 0x1500`                //示例：TCP头前2字节  

**多层层叠（GRE/VXLAN/隧道）指定第几层**  
`ip.src#1 == 10.1.2.3`              //外层源IP  
`ip.src#2 == 10.1.2.3`              //内层源IP  

**集合成员**  
`tcp.port in {443 8443}`  
`ip.addr in {10.0.0.5 .. 10.0.0.9}`  
`tcp.port in {4430..4434}`  
