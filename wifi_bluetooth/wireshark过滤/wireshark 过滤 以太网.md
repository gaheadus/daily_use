# 以太网过滤  
一、显示过滤器（主用）  
基础字段：  
`eth.addr`  //源或目的任一匹配  
`eth.src`   //源 MAC  
`eth.dst`   //目的 MAC  
`eth.addr_resolved / eth.src_resolved / eth.dst_resolved`  //带厂商名解析后的显示值  
`eth.type`       //以太网类型，如 0x0800=IPv4、0x0806=ARP、0x86dd=IPv6  
`eth.dst.ig`     //组播/广播位，1=组地址；eth.src.ig 同理  
`eth.src.oui / eth.dst.oui / eth.addr.oui` //前3字节 OUI（整数）；*.oui_resolved 是厂商字符串  
`eth.addr == 00:1a:2b:3c:4d:5e`        // 源或目的是该MAC  
`eth.src == 00:1a:2b:3c:4d:5e`         // 仅该MAC发出  
`eth.dst == 00:1a:2b:3c:4d:5e`         // 仅发往该MAC  
`eth.addr == 00-1a-2b-3c-4d-5e`        // 连字符也行  
`eth.addr == 001a.2b3c.4d5e`           // 点分组也行  
MAC格式支持 :、-、点分组三种，Wireshark 显示过滤都认。    
1) 排除某个 MAC  
`eth.addr` 是“源或目的”复合字段，排除要用**整体取反**，**别用 !=**：  
`!(eth.addr == 00:1a:2b:3c:4d:5e)`     //正确：完全排除该MAC收发  
`eth.addr != 00:1a:2b:3c:4d:5e`        //不推荐：易把“另一头不是它”的包也放进来  
2) 按厂商 OUI / 前3字节    
`eth.src[0:3] == 00:06:5b`             //源MAC前3字节（DELL示例）  
`eth.dst[0:3] == 00:0c:29`             //VMware  
`eth.addr[0:3] == 00:50:56`            //源或目的前3字节命中即可  
`eth.src.oui == 0x000c29`              //等价整数写法（部分版本）  
`eth.src.oui_resolved contains "Cisco"`    
切片语法`[偏移:长度]`，MAC 偏移从0开始；只写 `eth.src[0]` 会按提供的字节串长度推断，给3字节就比前3字节。    
3) 广播 / 组播  
`eth.dst == ff:ff:ff:ff:ff:ff`         //以太网广播  
`eth.dst.ig == 1`                      //所有组播/广播目的（IG位=1）  
`eth.dst[0:1] == 01`                   //目的MAC首字节01，粗筛组播  
`eth.dst[0:3] == 01:00:5e`             //IPv4组播（01:00:5e:*)  
`eth.dst[0:2] == 33:33`                //IPv6组播（33:33:*)  
`!(eth.dst == ff:ff:ff:ff:ff:ff) && eth.dst.ig == 1`   //只要组播不要全F广播  
4) 结合协议/端口    
`eth.src == 00:1a:2b:3c:4d:5e && ip`  
`eth.src == 00:1a:2b:3c:4d:5e && tcp.port == 443`  
`eth.dst == 00:1a:2b:3c:4d:5e && arp`  
`eth.addr == 00:1a:2b:3c:4d:5e && (tcp || udp)`  
`eth.type == 0x0806`                   //只留ARP（不看MAC也行）  
`eth.type == 0x0800 && eth.src == 00:1a:2b:3c:4d:5e`  
5) ARP 里的 MAC  
ARP 请求/响应自带发送端、目标端硬件地址，可单独筛：  
`arp.src.hw_mac == 00:1a:2b:3c:4d:5e`   //ARP发送端MAC  
`arp.dst.hw_mac == 00:1a:2b:3c:4d:5e`   //ARP目标MAC（通常全F）  
`arp && eth.src == 00:1a:2b:3c:4d:5e`   //该MAC发出的所有ARP  
6) VLAN / 多层 MAC    
`vlan && eth.addr == 00:1a:2b:3c:4d:5e`  
`vlan.id == 100 && eth.dst == 00:1a:2b:3c:4d:5e`  
抓带 VLAN 标签的包时，显示过滤加 vlan 更稳；捕获过滤器用 vlan 关键字另行处理。    
二、捕获过滤器（BPF，抓包前填）  
`ether host 00:1a:2b:3c:4d:5e`      //源或目的该MAC  
`ether src 00:1a:2b:3c:4d:5e`       //仅源  
`ether dst 00:1a:2b:3c:4d:5e`       //仅目的  
`not ether host 00:1a:2b:3c:4d:5e`  //排除该MAC  
`ether broadcast`                   //广播  
`ether multicast`                   //组播  
`ether proto 0x0806`                //仅ARP  
`ether proto 0x0800`                //仅IPv4  
`ether src 00:0c:29:*`              //多数BPF不支持通配，按完整MAC写；部分前端可简化  
组合示例：    
`ether host 00:1a:2b:3c:4d:5e and tcp port 443`  
`ether src 00:1a:2b:3c:4d:5e and icmp`  
`ether dst 01:00:5e:00:00:01`  
`not ether broadcast and not ether multicast`  
捕获过滤器不支持 `eth.addr==`、不支持 OUI 切片通配；要“前3字节”只能在显示过滤用 `eth.src[0:3]`，或在 BPF 用裸偏移（如 `ether[0:3]=0x000c29` 一类，写法更绕，一般不推荐）。  