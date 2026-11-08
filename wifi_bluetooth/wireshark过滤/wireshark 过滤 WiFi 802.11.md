# 通用
## mac地址过滤
| 过滤字段 | 含义 | 例子 |
| --- | --- | --- |
| wlan.addr | 源或目的 MAC 匹配 | `wlan.addr == aa:bb:cc:dd:ee:ff` |
| wlan.sa | 源 MAC 地址（Source Address） | `wlan.sa == aa:bb:cc:dd:ee:ff` |
| wlan.da | 目的 MAC 地址（Destination Address） | `wlan.da == aa:bb:cc:dd:ee:ff` |
| wlan.ta | 传输 MAC 地址（Transmitter Address） | `...` |
| wlan.ra | 接收 MAC 地址（Receiver Address） | `...` |
| wlan.bssid | BSSID（通常是 AP 的 MAC） | `wlan.bssid == aa:bb:cc:dd:ee:ff` |


**过滤多个 MAC 地址（或关系）：**
```Pure Text
wlan.addr == aa:bb:cc:dd:ee:ff || wlan.addr == 11:22:33:44:55:66
```

**过滤某 MAC 地址之外的所有流量（非关系）：**
```Pure Text
!(wlan.addr == aa:bb:cc:dd:ee:ff)
```

**结合其他条件（如只显示数据帧）：**
```Pure Text
wlan.addr == aa:bb:cc:dd:ee:ff && wlan.fc.type == 2
```
> 💡 wlan.fc.type == 2 表示数据帧，== 0 是管理帧，== 1 是控制帧  
> ⚠️ 抓包时需要开启网卡的**监听模式（Monitor Mode）**，否则只能看到发给本机或本机发出的数据帧，无法捕获 WiFi 空中所有报文。  

---

## ssid/bssid/隐藏ssid
wlan_mgt.ssid == "MyWiFi"    //按SSID名过滤(如过滤名为 "MyWiFi" 的信标)  
wlan.bssid == aa:bb:cc:dd:ee:ff  //查看某个AP (BSSID)的所有活动  
wlan.fc.type_subtype == 0x0008 and wlan_mgt.ssid == ""     //过滤隐藏SSID (SSID 长度为 0)  

## 安全/加密/四次握手
eapol          // EAPOL 握手包（WPA/WPA2 四次握手）  
eapol.type == 3  //过滤 WPA 四次握手中的特定帧  
wlan.fc.protected == 0 && wlan.fc.type == 2   //过滤未加密的数据流量  
wlan.fc.protected == 1                     //过滤加密的数据流量  
wps      // WPS 相关交互  


## 组合
实用组合过滤案例  
1. 抓取某个 STA 的完整生命周期(关联 → 认证 → 数据 → 断连)：  
```
(wlan.sa == aa:bb:cc:dd:ee:ff || wlan.da == aa:bb:cc:dd:ee:ff) &&
(wlan.fc.type == 0 || (wlan.fc.type == 2))
```

2. 只看 WPA2 握手 + 后续加密数据：
```
(eapol) || (wlan.bssid == aa:bb:cc:dd:ee:ff && wlan.fc.protected == 1)
```

3. 排查 WiFi 干扰(低信号 + 重传)：
```
radiotap.dbm_antsignal < -75 && wlan.fc.retry == 1
```

4. 只看 Beacon 帧中的特定 SSID：
```
wlan.fc.type_subtype == 0x0008 && wlan_mgt.ssid contains "Office"
```

5. 排除广播/组播，只看单播数据：
```
wlan.fc.type == 2 && !(wlan.da[0] & 1)
```

6. 查看某个信道上的所有 Probe Request(主动扫描)：
```
wlan.fc.type_subtype == 0x0004 && radiotap.channel.freq == 2437
```



# 802.11分类过滤
<details>
<summary>Deep thinking completed (took 2 seconds)</summary>
用户是在上一轮 Wireshark 按 MAC 地址过滤 WiFi 抓包的基础上继续追问，重点不是重复 wlan.addr、wlan.sa、wlan.da 这些基础用法，而是扩展 WiFi 抓包里更完整的过滤思路。回答应围绕 802.11 帧结构和排障场景组织：包括管理帧、控制帧、数据帧的类型/子类型过滤，BSSID/SSID/信道/信号相关字段过滤，MAC 地址组合与方向过滤，以及加密握手、EAPOL、空口重传、QoS 等实战过滤。由于这是 Wireshark 显示过滤器的固定功能知识，不需要联网搜索；我会用 wlan.fc.type、wlan.fc.subtype、wlan_mgt、eapol、radiotap 等字段给出可复制的表达式，并提醒 monitor mode/radiotap 是否可用会影响部分字段。
</details>

除了按 MAC 地址过滤，Wireshark 对 802.11（WiFi）抓包还提供了大量基于**帧类型、管理字段、控制字段、数据字段、Radiotap 头部**等的过滤方式。下面按实际使用场景分类整理。

## 一、按帧类型 / 子类型过滤
802.11 帧分为三大类：**管理帧（type=0）、控制帧（type=1）、数据帧（type=2）**。每类下又有多个子类型。  
按帧类型过滤：
```bash
wlan.fc.type == 0          # 所有管理帧
wlan.fc.type == 1          # 所有控制帧
wlan.fc.type == 2          # 所有数据帧
```

### 1. 管理帧（Management Frames）
| 过滤器 | 含义 |
|--------|------|
| wlan.fc.type == 0 | all management frames |
| wlan.fc.type_subtype == 0 | association requests |
| wlan.fc.type_subtype == 1 | association response |
| wlan.fc.type_subtype == 2 | re-association request |
| wlan.fc.type_subtype == 3 | re-association response |
| wlan.fc.type_subtype == 4 | probe requests |
| wlan.fc.type_subtype == 5 | probe responses |
| wlan.fc.type_subtype == 8 | beacons |
| wlan.fc.type_subtype == 9 | atims |
| wlan.fc.type_subtype == 10 | disassosiations |
| wlan.fc.type_subtype == 11 | authentications |
| wlan.fc.type_subtype == 12 | deauthentications |
| wlan.fc.type_subtype == 13 | actions |

### 2. 控制帧（Control Frames）
| 过滤器 | 含义 |
|--------|------|
| wlan.fc.type == 1 | all control frames |
| wlan.fc.type_subtype == 24 | block ack requests |
| wlan.fc.type_subtype == 25 | block ack |
| wlan.fc.type_subtype == 26 | ps-polls |
| wlan.fc.type_subtype == 27 | rts |
| wlan.fc.type_subtype == 28 | cts |
| wlan.fc.type_subtype == 29 | acks |
| wlan.fc.type_subtype == 30 | cf-ends |
| wlan.fc.type_subtype == 31 | cf-ends/cf-acks |

### 3. 数据帧（Data Frames）
| 过滤器 | 含义 |
|--------|------|
| wlan.fc.type == 2 | all data frames |
| wlan.fc.type_subtype == 32 | data frames |
| wlan.fc.type_subtype == 33 | data+cf-ack |
| wlan.fc.type_subtype == 34 | data+cf-poll |
| wlan.fc.type_subtype == 35 | data+cf-ack + cf-ack |
| wlan.fc.type_subtype == 36 | null data |
| wlan.fc.type_subtype == 37 | cf-ack |
| wlan.fc.type_subtype == 38 | cf-poll |
| wlan.fc.type_subtype == 39 | cf-ack + cf-poll |
| wlan.fc.type_subtype == 40 | qos data |
| wlan.fc.type_subtype == 41 | qos data + cf-ack |
| wlan.fc.type_subtype == 42 | qos data + cf-poll |
| wlan.fc.type_subtype == 43 | qos data + cf-ack+ cf-poll |
| wlan.fc.type_subtype == 44 | qos null |
| wlan.fc.type_subtype == 46 | qos cf-poll |
| wlan.fc.type_subtype == 47 | qos cf-ack + cf-poll |

### 4. 其他
Wireshark Display Filters related **Retries**:
| 过滤器 | 含义 |
|--------|------|
| wlan.fc.retry ==1 | retry frames |
| wlan.fc.retry ==1 && wlan.fc.tods ==1 | towards ap |
| wlan.fc.retry ==1 && wlan.fc.fromds ==1 | from ap towards client device |

Wireshark Display Filters related **802.11 k,v,r** traffic:

| 过滤器 | 含义 |
|--------|------|
| wlan.fixed.action_code ==23 | 802.11v dms request |
| wlan.fixed.action_code ==24 | 802.11v dms respose |
| wlan.rm.action_code ==4 | 802.11k neighbour request |
| wlan.rm.action_code ==5 | 802.11k neighbour response |
| (wlan.fc.type_subtype == 0)&&(wlan.rsn.akms.type == 3) | 802.11r auth request |
| (wlan.fc.type_subtype == 1)&&(wlan.tag.number == 55) | 802.11r auth response |
| (wlan.fc.type_subtype == 2)&&(wlan.tag.number == 55) | 802.11r re-association request |
| (wlan.fc.type_subtype == 3)&&(wlan.tag.number == 55) | 802.11r re-association response |

Wireshark Display Filters related **Weak signals**:
| 过滤器 | 含义 |
|--------|------|
| wlan_radio.signal_dbm < -67 | weak signal filter |
| wlan.fc.type_subtype == 0x05 && wlan_radio.signal_dbm < -75 | weak prob response |
| wlan.fc.type_subtype == 0x04 && wlan_radio.signal_dbm < -75 | weak prob requests |

Some **Extras**:
| 过滤器 | 含义 |
|--------|------|
| wlan.addr == mac address | specific client by mac address |
| wlan.ta == mac address | transmitter address |
| wlan.ra == mac address | receive address |
| wlan.sa == mac address | source address |
| wlan.da == mac address | destination address |
| wlan.bssid == ap mac address | radio mac address |
| wlan.mgt.ssid == "your-ssid" | filter by ssid |

Some **Extras 2**:
| 过滤器 | 含义 |
|--------|------|
| wlan.fc.type_subtype == 14 | Action No Ack |
| wlan.fc.type_subtype == 15 | Aruba Management |
| wlan.fc.type_subtype == 16 | Unrecognized (Reserved frame) |
| wlan.fc.type_subtype == 17 | Unrecognized (Reserved frame) |
| wlan.fc.type_subtype == 18 | Trigger |
| wlan.fc.type_subtype == 19 | Unrecognized (Reserved frame) |
| wlan.fc.type_subtype == 20 | Beamforming Report Poll |
| wlan.fc.type_subtype == 21 | VHT/HE NDP Announcement |
| wlan.fc.type_subtype == 23 | Control Wrapper |
| wlan.fc.type_subtype == 24 | 802.11 Block Ack Req |
| wlan.fc.type_subtype == 25 | 802.11 Block Ack |
| wlan.fc.type_subtype == 26 | Power-Save poll |
| wlan.fc.type_subtype == 27 | Request-to-send |
| wlan.fc.type_subtype == 28 | Cear-to-send |
| wlan.fc.type_subtype == 29 | Acknowledgement |
| wlan.fc.type_subtype == 30 | CF-End (Control-frame) |
| wlan.fc.type_subtype == 31 | CF-End + CF-Ack (Control-frame) |
| wlan.fc.type_subtype == 32 | Data |
| wlan.fc.type_subtype == 33 | Data + CT-Ack |

from : https://www.wifi-professionals.com/2019/03/wireshark-display-filters


## 二、按 SSID / BSSID 过滤
**按 SSID 名过滤（如过滤名为 "MyWiFi" 的信标）：**
```bash
wlan_mgt.ssid == "MyWiFi"
```

**查看某个 AP（BSSID）的所有活动：**
```bash
wlan.bssid == aa:bb:cc:dd:ee:ff
```

**过滤隐藏 SSID（SSID 长度为 0）：**

```bash
wlan.fc.type_subtype == 0x0008 and wlan_mgt.ssid == ""
```

## 三、按信道 / Radiotap 字段过滤
当你使用监听模式抓包时，每一帧前面会带有 **Radiotap 头部**，里面包含信道、信号强度、数据速率等信息。
```bash
# 按信道过滤（例如信道 6）
radiotap.channel.freq == 2437      # 2.4GHz 信道6 对应频率 2437 MHz
radiotap.channel.type == 0x0140    # 2.4GHz 信道

# 按信号强度过滤（dBm，负值越大信号越弱）
radiotap.dbm_antsignal >= -50      # 只显示信号较强的帧
radiotap.dbm_antsignal < -80       # 只显示信号很弱的帧

# 按传输速率过滤
radiotap.datarate == 54            # 54 Mbps 的帧

# 按 MCS 索引（802.11n/ac/ax）
radiotap.mcs.index == 7
radiotap.vht.mcs == 9
```

## 四、按安全 / 加密过滤
**EAPOL 握手包（WPA/WPA2 四次握手）：**
```bash
eapol
```

**过滤 WPA 四次握手中的特定帧：**
```bash
eapol.type == 3
```

**过滤未加密的数据流量：**
```bash
wlan.fc.protected == 0 && wlan.fc.type == 2
```

**过滤加密的数据流量：**
```bash
wlan.fc.protected == 1
```

**WPS 相关交互：**
```bash
wps
```

## 五、按 QoS / WMM 过滤
```bash
wlan.qos.priority == 0             # Background 优先级
wlan.qos.priority == 7             # Voice 优先级（语音流量）
wlan.qos.tid == 6                  # TID = 6
```

## 六、按重传 / 帧状态过滤
**过滤重传帧：**
```bash
wlan.fc.retry == 1
```

**过滤非重传帧：**
```bash
wlan.fc.retry == 0
```

**过滤 Power Management 位（节电模式）：**
```bash
wlan.fc.pwrmgt == 1                # STA 处于睡眠状态
wlan.fc.pwrmgt == 0                # STA 唤醒
```

## 七、按地址组合过滤（高级）
802.11 帧头最多可携带 4 个地址字段（Address 1~4），比以太网复杂：
```bash
# 源 MAC 和目的 MAC 同时匹配
wlan.sa == aa:bb:cc:dd:ee:ff && wlan.da == 11:22:33:44:55:66

# 发射端 / 接收端地址（TA/RA，用于 WDS 或 Mesh）
wlan.ta == aa:bb:cc:dd:ee:ff
wlan.ra == 11:22:33:44:55:66

# AP 间通信（WDS，4 地址帧）
wlan.addr4 != 00:00:00:00:00:00
```

## 八、按厂商 OUI 过滤
```bash
# 过滤某厂商前缀的 MAC（前 3 字节）
wlan.addr[0:3] == AA:BB:CC
```

## 九、实用组合过滤案例
**1. 抓取某个 STA 的完整生命周期（关联 → 认证 → 数据 → 断连）：**
```bash
(wlan.sa == aa:bb:cc:dd:ee:ff || wlan.da == aa:bb:cc:dd:ee:ff) && 
(wlan.fc.type == 0 || (wlan.fc.type == 2))
```

**2. 只看 WPA2 握手 + 后续加密数据：**
```bash
(eapol) || (wlan.bssid == aa:bb:cc:dd:ee:ff && wlan.fc.protected == 1)
```

**3. 排查 WiFi 干扰（低信号 + 重传）：**

```bash
radiotap.dbm_antsignal < -75 && wlan.fc.retry == 1
```

**4. 只看 Beacon 帧中的特定 SSID：**

```bash
wlan.fc.type_subtype == 0x0008 && wlan_mgt.ssid contains "Office"
```

**5. 排除广播/组播，只看单播数据：**
```bash
wlan.fc.type == 2 && !(wlan.da[0] & 1)
```

**6. 查看某个信道上的所有 Probe Request（主动扫描）：**
```bash
wlan.fc.type_subtype == 0x0004 && radiotap.channel.freq == 2437
```

## 十、调试技巧
- 在过滤器框输入 wlan. 后按 **Ctrl+Space** 可以自动补全所有可用字段
- 右键任意数据包的某个字段 → **"Apply as Filter"** 可以快速生成过滤表达式
- 使用 **!** 取反、&& 与、|| 或 来组合复杂条件
- 如果某些字段显示为 <none> 或未解析，请确认抓包时开启了 **Monitor Mode** 且驱动支持 Radiotap

> 💡 想要查看完整字段列表，可以在 Wireshark 中打开：**"View" → "Wireless Toolbar"**，或者使用 tshark -G fields | grep wlan 查看所有可用的 802.11 协议字段。

这些过滤器组合起来几乎可以覆盖所有 WiFi 排障场景——从信号质量分析、漫游行为追踪到安全审计都能胜任。
