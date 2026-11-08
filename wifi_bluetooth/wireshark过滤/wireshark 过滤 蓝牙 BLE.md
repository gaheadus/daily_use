# 过滤器表达式
| 过滤器表达式 | 用途/含义 |
|---|---|
| btle | 显示所有BLE数据包 |
| btatt | 查看所有ATT/GATT数据。过滤出所有服务发现、读写请求、通知等应用层交互 |
| btatt && btle.encrypted == 1 | 只显示加密后的ATT数据包 |
| btsmp | 只显示SMP配对过程数据包 |
| btl2cap | 只显示L2CAP层数据包，包括ATT、SMP、L2CAP层其它数据包。 |
| btatt.opcode == 0x02 \|\| btatt.opcode == 0x03 | 查看MTU协商过程。0x02 为 Exchange MTU Request，0x03 为 Response。用于确认最大传输单元大小 |
| btatt.opcode == 0x12 \|\| btatt.opcode == 0x52 | 查看写入操作(Write)。0x12 为 Write Request (有响应)，0x52 为 Write Command (无响应/写命令) |
| btatt.opcode == 0x1b \|\| btatt.opcode == 0x1d | 查看通知与指示(Notify & Indicate)。0x1b 为 Handle Value Notification (无需确认)，0x1d 为 Handle Value Indication (需确认) |
| btatt.opcode == 0x0a \|\| btatt.opcode == 0x0b | 查看读取操作(Read)。0x0a 为 Read Request，0x0b 为 Read Response |
| btatt.opcode == 0x01 | 查看错误响应(Error)。快速定位读写失败、权限不足或句柄无效等协议层错误 |
| btatt.handle == 0x0025 | 按特定Handle过滤。当你已知某个特征值(Characteristic)的句柄时，直接过滤该句柄的数据包 |
| btatt.opcode == 0x12 | 显示写入操作 |
| btle.advertising_address == aa:bb:cc:dd:ee:ff | 只显示特定设备的广播包 |
| btle.advertising_data.service_uuid16 == 0x180D | 只显示包含特定服务的广播 |
| btle.advertising_address == aa:bb:cc:dd:ee:ff && btle.advertising_data.service_uuid16 == 0x180D | 组合过滤条件 |
| btatt.opcode == 0x1b && btatt.handle == 0x000e | 显示特定特征的通知 |
| !(btle.length == 0) 或 btle.length != 0 | 过滤长度为0的包，即过滤掉空包。 |
| (frame.len == 38) \|\| (frame.len == 60) | 显示数据帧长度为38或者60字节长度的数据包。 |



# Wireshark过滤低功耗蓝牙空口包
**问：** wireshark过滤 低功耗蓝牙BLE 空口包
<details>
<summary>Deep thinking completed (took 7 seconds)</summary>

用户问的是 Wireshark 里如何过滤低功耗蓝牙 BLE 空口包（over-the-air / 空口抓包）。这涉及 Wireshark 的 BTLE/LE 显示过滤器语法、抓包来源（nRF Sniffer、Ubertooth、Adafruit、TI SmartRF、Ellisys、Frontline 等）、常见过滤场景（广播、扫描响应、连接请求、LL 控制、ATT、GATT、特定 MAC/地址、信道、方向、错误包等）。我先搜一下 Wireshark 当前 BTLE 显示过滤字段和空口抓包配置，避免凭记忆给错字段名。

- 1. 树莓派Raspbian构建BLE安全审计平台实战 - CSDN
- 2. How to Capture BLE Packets with nRF Sniffer and Wireshark
- 3. nRF51822  Wireshark:低功耗蓝牙空口抓包实战指南-CSDN博客 - CSDN
- 4. nRF52840 Dongle  Wireshark:BLE抓包实战方案全解析
- 5. BLE 抓包完全教程:nRF52840 Dongle  Wireshark
- 6. nRF Sniffer User Guide v2.0
- 7. Using Wireshark for Bluetooth Analysis
- 8. nRF Sniffer 在Wireshark中的高效过滤与实战技巧
- 9. Ubertooth One 使用系列 (一) — 破解蓝牙锁
- 10. nRF52840 Dongle  Wireshark 抓取 BLE 数据包:保姆级实战指南
- 11. 蓝牙与近场通信安全取证深度分析
- 12. 蓝牙抓包流程与实践:从加密机制到 Wireshark 实战指南

</details>

Wireshark 里 BLE 空口包主要靠 btle.* 系列显示过滤器，配合 btatt/btsmp/btl2cap 看上层。先分清一件事：用 nRF Sniffer、Ubertooth、Ellisys 等抓的是**空口 LL 包**，字段多在 btle 下；如果是本机 hcidump/HCI 日志，则用 bthci_* 那套，不是同一套过滤词。

## 一、最常用空口过滤

```text
btle                                  # 所有 BLE 链路层包
btle.advertising_address              # 有广播地址的包（广播/扫描/连接请求类）
btle.advertising_address == aa:bb:cc:dd:ee:ff   # 指定设备广播
btle.length != 0                      # 去掉空包，只看有数据的
btle.access_address == 0x8e89bed6     # 广播/空口默认接入地址；连接后用实际 access address 跟一条连接
```

nRF 插件还有私有头字段可按信道看数据通道包：

```text
nordic_ble.channel == 37              # 只看广播信道37（38/39同理）
nordic_ble.rssi < -80                 # 弱信号包，查射频/距离问题
```

> 注意：不同 Wireshark 版本字段路径可能变，比如广播 PDU 类型有的在 btle.advertising_header.pdu_type，有的旧版叫 btle.pdu_type。最稳的办法是包详情里右键目标字段 → **Apply as Filter** 或 **Apply as Column**，让 Wireshark 自己生成。

## 二、广播、扫描

```text
btle.advertising_header.pdu_type == 0x00   # ADV_IND 可连接无向
btle.advertising_header.pdu_type == 0x01   # ADV_DIRECT_IND 可连接定向
btle.advertising_header.pdu_type == 0x02   # ADV_NONCONN_IND 不可连接
btle.advertising_header.pdu_type == 0x03   # ADV_SCAN_IND 可扫描
btle.advertising_header.pdu_type == 0x04   # SCAN_RSP 扫描响应
```

按名称找设备（字段名随版本/插件不同）：
```text
btcommon.eir_ad.entry.local_name contains "MySensor"
# nRF Sniffer 有时用：
btcommon.eir_ad.entry.device_name contains "MySensor"
```
找不到名称字段就展开广播包详情 → 设备名 → 右键应用过滤器。

## 三、连接、信道、LL 控制
连接：  
```
btle.advertising_header.pdu_type == 0x05   # CONNECT_IND 连接请求（中央发出）
```
连接请求后可按接入地址跟整条连接：  
```text
btle.access_address == 0x9925cfbf     # 替换成抓到的连接 access address
```

LL 控制包 / 空包 / CRC：  
```text
btle.data_header.llid == 0x03         # LL Control PDU
btle.control_opcode == 0x00           # 例如 LL_CONNECTION_UPDATE_IND，按实际opcode换
btle.control_opcode == 0x02           # LL_TERMINATE_IND 断连原因
btle.ll_empty_pdu == 1                # 空包（keep-alive）
btle.crc_ok == 0                      # CRC 错误/坏包（有的版本字段名不同）
btle.crc.incorrect == 1               # 另一版 CRC 错误写法
```

排连接不稳定可看时间间隙：  
```text
frame.time_delta > 0.05               # 两包间隔大于50ms，查丢包/调度/监督超时
```

## 四、ATT / GATT 数据
```text
btatt                                 # 所有 ATT
btatt.opcode == 0x0a                  # Read Request
btatt.opcode == 0x0b                  # Read Response
btatt.opcode == 0x12                  # Write Request
btatt.opcode == 0x13                  # Write Response
btatt.opcode == 0x52                  # Write Command（write without response）
btatt.opcode == 0x1b                  # Handle Value Notification
btatt.opcode == 0x1d                  # Handle Value Indication
btatt.opcode == 0x01                  # ATT Error Response
btatt.handle == 0x0015                # 指定属性句柄
btatt.uuid16 == 0x2a19                # 比如电池电量；128位UUID用对应uuid字段
btgatt.service_uuid == 0x180d         # 按服务过滤（部分版本/解析支持）
```

组合举例：  
```text
btatt.opcode == 0x1b && btatt.handle == 0x0025      # 某特征所有notify
btatt.opcode == 0x01 && btatt.error_code == 0x05    # Insufficient Authentication
```

## 五、配对/加密（SMP）
```text
btsmp                                 # 所有安全管理包
btsmp.opcode == ...                   # pairing request/response、confirm、rand、DHKey check等按实际填
btle.ll.enc_req || btle.ll.enc_rsp    # 部分版本看LL加密请求/响应
```
nRF Sniffer 若在配对开始就跟着、并在 Wireshark 里填入 passkey/LTK/SC 私钥，可自动解密后续 ATT；否则加密包只能看到密文。

## 六、和“非空口”区分一下
- 空口嗅探（nRF/Ubertooth/TI/Ellisys/Frontline）：用 btle.*、nordic_ble.*、按 access address/channel/LL 过滤。  
- 本机 HCI 日志（Android btsnooz、Linux hcidump、Windows ETW）：用 bthci_cmd/bthci_evt/bthci_acl，广播事件用 bthci_evt.le_meta_subevent == 0x02，连接完成用 0x01，断通用 bthci_evt.code == 0x05。  
- 如果打开文件全是 “Unknown HCI” 或看不到 btle，说明抓的是 HCI 而不是空口，或者封装类型/解析器没配对。  
如果你愿意说下抓包硬件（nRF52840 / Ubertooth / 其他）和 Wireshark 版本，我可以按你的字段名给一套可直接粘贴的过滤组合。

---


# 过滤指定mac地址的连接请求
**问：** btle.advertising_header.pdu_type == 0x05 过滤CONNECT_IND 连接请求，如果要过滤指定mac地址的CONNECT_IND 连接请求应该如何写？

<details>
<summary>Deep thinking completed (took 7 seconds)</summary>

用户问 Wireshark 里用 btle.advertising_header.pdu_type==0x05 过滤 CONNECT_IND，还要加指定 MAC 地址怎么写。需要先核实 CONNECT_IND 在 BLE 空口里的地址字段：InitA（发起方/中央）和 AdvA（广告方/外设），Wireshark 不同版本/捕获源（纯空口 btle、nRF nordic_ble、HCI bthci）字段名可能不同。我要搜一下 btle CONNECT_IND 的 initiator/advertiser address 显示过滤字段名，以及 pdu_type 0x05 下如何组合。回答时应给可直接粘贴的写法，例如按外设 MAC 和按中央 MAC 两种，并提醒如果字段名不对可在包详情里展开 Connect_Ind → Initiator address / Advertiser address 右键复制过滤器；若用 nRF Sniffer 可能要用 nordic_ble 或 btle 下对应子字段。还要说明 MAC 大小写/格式用冒号十六进制。

- 1. btle.ll.opcode  0x05并没有你说的这个过滤指令,最多可用这个btle.advertising_header.pdu_type0x05过滤连接广播 - CSDN
- 2. nRF Sniffer 4.6.6 实战:5个高效过滤规则精准捕获目标BLE设备数据包
- 3. Working With ESP-C3-32S-Kit Dev Board
- 4. How to Capture BLE Packets with nRF Sniffer and Wireshark
- 5. nRF Sniffer 在Wireshark中的高效过滤与实战技巧
- 6. nRF52840 DK sniffer fails to display Data messages after Connect_Ind, only advertisements
- 7. BLE空口抓包分析:连接建立与协议解析
- 8. nRF Sniffer 在Wireshark中的使用 - CSDN
- 9. nRF51822  Wireshark:低功耗蓝牙空口抓包实战指南-CSDN博客 - CSDN
- 10. Display Filter Reference: Bluetooth Low Energy Link Layer
- 11. Sniffing Read and Write with Wireshark on Mac
- 12. 我要抓包蓝牙连接的广播,应该怎么过滤,为什么我过滤蓝牙广播设备的mac并没有连接广播,而我在抓包过程中使用nRF connect连接了广播设备,并且连接成功了 - CSDN
- 13. 蓝牙与近场通信安全取证深度分析
- 14. BLE / Bluetooth Low Energy
- 15. Microchip BLE嗅探器实战指南:从硬件配置到协议分析 - CSDN
- 16. Bluetooth Pentesting 101: BLE Sniffing with nRF52840 and Wireshark
- 17. ios 蓝牙 广播包 蓝牙广播包分析

</details>

CONNECT_IND 里有两个地址可筛：外设（被连方）叫 **Advertising/Advertiser Address**，中央（发起方）叫 **Initiator Address**。按你的 pdu_type 条件叠加即可。

## 一、按外设 MAC 筛（最常用）

只想看“谁去连某个外设”：

```text
btle.advertising_header.pdu_type == 0x05 && btle.advertising_address == aa:bb:cc:dd:ee:ff
```

部分版本/捕获源字段名是：

```text
btle.advertising_header.pdu_type == 0x05 && btle.advertising_address == AA:BB:CC:DD:EE:FF
# 旧版嵌套写法可能用：
btle.advertising_header.pdu_type == 0x05 && btle.connect_request.advertiser_address == aa:bb:cc:dd:ee:ff
```

btle.advertising_address 是 Wireshark BLE LL 标准字段，广播包和 CONNECT_IND 都可用 。

## 二、按中央 MAC 筛（看某手机/主机发起的连接）

```text
btle.advertising_header.pdu_type == 0x05 && btle.initiator_address == 11:22:33:44:55:66
```

nRF 抓包实践里就有直接用 btle.initiator_address 跟外设 btle.advertising_address 组合的例子 。旧版若不在顶层，试：

```text
btle.advertising_header.pdu_type == 0x05 && btle.connect_request.initiator_address == 11:22:33:44:55:66
```

## 三、外设或中央任一匹配

```text
btle.advertising_header.pdu_type == 0x05 && (btle.advertising_address == aa:bb:cc:dd:ee:ff || btle.initiator_address == 11:22:33:44:55:66)
```

## 四、字段名不对/报红时的取字段办法

不同 Wireshark 版本、nRF Sniffer 插件、Ubertooth/Ellisys 解析路径不完全一样：

- 在包列表点中 CONNECT_IND → 中间详情展开 Bluetooth Low Energy Link Layer → 能看到 Initiator Address 和 Advertising Address（nRF 示例就是这样）

- 对其中一行右键 → **Apply as Filter → Selected**，Wireshark 会自动生成当前版本正确的完整字段名，不用背

- 若走 btle.connect_request.* 仍不行，直接在详情里看它归在 Connect_Ind/LLData 下哪个子节点，照抄

## 五、顺手补几个实用组合

```text
# 指定外设 + 任意连接请求，排除其它广播噪声
btle.advertising_header.pdu_type == 0x05 && btle.advertising_address == aa:bb:cc:dd:ee:ff

# 外设在37/38/39任一信道发连接请求（CONNECT_IND只在广播信道）
btle.advertising_header.pdu_type == 0x05 && btle.advertising_address == aa:bb:cc:dd:ee:ff && (nordic_ble.channel == 37 || nordic_ble.channel == 38 || nordic_ble.channel == 39)

# 随机地址设备：除MAC外可再看地址类型标志
btle.advertising_header.pdu_type == 0x05 && btle.advertising_header.randomized_tx == 1 && btle.advertising_address == aa:bb:cc:dd:ee:ff
```

> 注意：如果外设开的是随机可解析地址（RPA），每次重启/MAC 可能变，按 MAC 筛会漏；这种先用广播名/IRK 锁定，或抓到一次 CONNECT_IND 后再用里面的实际地址写过滤。

如果你把 Wireshark 版本和抓包硬件（nRF52840 / Ubertooth / 其他）告诉我，可以直接按你那个环境的真实字段名给一条可粘贴的。

---


# 过滤指定mac地址的所有包

<details>
<summary>Deep thinking completed (took 7 seconds)</summary>

用户问的是在Wireshark里“如何过滤指定MAC地址的所有包”，结合上文是BLE/Bluetooth空口语境，但“所有包”也可能包括非蓝牙（以太网/Wi‑Fi/802.11）。我需要先搜一下Wireshark中BLE指定MAC全包过滤的常用字段，以及普通有线/无线MAC过滤的写法，避免只给btle而漏掉用户其实想看任意层。回答时应分场景：BLE空口（广播地址、initiator、连接后数据通道access address无法直接用MAC，需要靠advertising/initiator或nRF解析后的peer/bond信息）、传统HCI（bthci里的地址字段）、以太网(wlan/eth)和Wi‑Fi(802.11)。先搜索确认Wireshark各蓝牙字段名和通配写法。

- 1. BLE 抓包完全教程:nRF52840 Dongle  Wireshark
- 2. Using Wireshark for Bluetooth Analysis
- 3. Wireshark Commands Cheatsheet: Filters, Syntax & Shortcuts (2026 Update)
- 4. nRF51822  Wireshark:低功耗蓝牙空口抓包实战指南-CSDN博客 - CSDN
- 5. 资讯详情
- 6. Wireshark 搜索组合速查表
- 7. nRF52840 Dongle  Wireshark 抓取 BLE 数据包:保姆级实战指南
- 8. Wireshark 802.11 Filters - Reference Sheet PDF size
- 9. Tips for filtering BLE packets using Wireshark and Nordic BLE Sniffer
- 10. Wireshark过滤规则及过滤选项如何理解
- 11. 深入解析小米MiBeacon广播数据:从抓包到协议细节 - CSDN
- 12. wireshark过滤规则
- 13. nRF Sniffer 在Wireshark中的高效过滤与实战技巧
- 14. 蓝牙伪装攻击流量分析实战:Wireshark与Python自动化取证

</details>

“指定 MAC 的所有包”在 Wireshark 里要分场景写：BLE 空口、本机 HCI 日志、普通以太网/Wi‑Fi 字段完全不同。

## 一、BLE 空口（nRF / Ubertooth / Ellisys 等）

BLE 空口没有“一个字段覆盖设备全生命周期”的 MAC 过滤，要分两段：

**1）广播/扫描/连接请求阶段——用设备地址字段**

```text
# 指定外设（被连方）出现的所有广播/扫描响应/连接请求
btle.advertising_address == aa:bb:cc:dd:ee:ff

# 指定中央（发起方）发起的所有 CONNECT_IND
btle.initiator_address == 11:22:33:44:55:66

# 外设或中央任一匹配
(btle.advertising_address == aa:bb:cc:dd:ee:ff) || (btle.initiator_address == 11:22:33:44:55:66)
```

MAC 不区分大小写，aa:bb:cc… 和 AA:BB:CC… 等价。

**2）连接建立后——改用 Access Address 跟整条连接**

CONNECT_IND 之后数据信道包不再带设备 MAC，而是用 32bit Access Address 标识一条连接。先从抓到的 CONNECT_IND 详情里复制 access address，再写：

```text
btle.access_address == 0x9925cfbf
```

这样能拿到这条连接里所有空口包（LL 控制、空包、ATT、SMP 等）。

> 实操建议：先 btle.advertising_address == 目标MAC 找到它的 CONNECT_IND → 看包详情里的 Access Address → 换成 btle.access_address == … 跟连接后全部交互。nRF 环境也可对 CONNECT_IND 右键 **Follow → Bluetooth LE ACL** 直接跟整条。

**3）想“广播+连接”一起看的组合**

```text
(btle.advertising_address == aa:bb:cc:dd:ee:ff) || (btle.access_address == 0x9925cfbf)
```

前提是你已经知道这条连接的 access address 属于该 MAC。

## 二、本机 HCI 日志（Android btsnooz / Linux hcidump / Windows ETW）

HCI 里不走 btle.*，按事件筛：

```text
# 本机看到的指定蓝牙设备广告报告（LE Advertising Report）
bthci_evt.le_meta_subevent == 0x02 && bthci_evt.advertising_address == aa:bb:cc:dd:ee:ff

# 本机作为中央完成到某外设的连接
bthci_evt.le_meta_subevent == 0x01 && bthci_evt.peer_address == aa:bb:cc:dd:ee:ff
```

不同 Wireshark 版本 peer/advertiser 字段名会有差异，包详情里展开 HCI Event → 右键地址 → Apply as Filter 最稳。

## 三、普通以太网 / Wi‑Fi（非蓝牙）

```text
eth.addr == 00:1a:2b:3c:4d:5e     # 以太网源或目的任一匹配
eth.src  == 00:1a:2b:3c:4d:5e     # 仅源
eth.dst  == 00:1a:2b:3c:4d:5e     # 仅目的

wlan.addr  == 00:11:22:33:44:55   # Wi‑Fi 源/目的/收发任一
wlan.sa    == 00:11:22:33:44:55   # 源
wlan.da    == 00:11:22:33:44:55   # 目的
wlan.ta    == 00:11:22:33:44:55   # 发射端
wlan.ra    == 00:11:22:33:44:55   # 接收端
wlan.bssid == 00:11:22:33:44:55   # AP 的 BSSID
```

## 四、两个容易踩的坑

- **随机可解析地址（RPA）**：外设如果开 RPA，每次重连 MAC 可能变，按 advertising_address 会漏。要么用固定公共地址测试，要么先抓广播名/IRK 锁定，或直接在 CONNECT_IND 后转用 access address 跟。

- **字段报红**：Wireshark 版本、nRF 插件、Ubertooth 解析路径不一样。任意包中间面板展开协议树 → 找到地址行 → 右键 **Apply as Filter → Selected**，自动生成当前环境正确字段名，比背字段可靠。

如果你用的是 nRF52840 Sniffer 还是 Ubertooth、以及 Wireshark 版本号，我可以按那个环境给一套不报红的精确字段。

---

# 过滤蓝牙BLE MTU协商包
<details>
<summary>Deep thinking completed (took 10 seconds)</summary>

用户要的是在 Wireshark 里过滤 BLE 空口/抓包中的 MTU 协商包。MTU 协商在 BLE 里主要是 ATT 层的 Exchange MTU Request/Response，也可能涉及 L2CAP 在某些栈/日志中的表示，但标准 BLE GATT 用 ATT opcode。需要先搜一下 Wireshark 中 btatt 的 exchange mtu 过滤字段/opcode，以及如果用 nRF/空口 btle 如何定位 ATT 再 btatt.opcode。还要考虑 HCI/本机日志场景可能用 btl2cap 或 bthci 的不同。回答应给可直接粘贴的显示过滤器：btatt.opcode 对应 Exchange MTU Request/Response，若按名称可用 btatt.exchange_mtu_request/response 之类；同时说明如何先过滤所有 ATT、再缩小到 MTU，给出客户端/服务端、指定连接 access address、指定句柄如有。也要提醒如果抓的是 HCI 而不是空口，字段前缀不同；如果包被加密未解密则看不到 ATT。先搜索确认 Wireshark 具体字段名和 opcode 值。

- 1. 使用 Wireshark 分析 Android 蓝牙 HCI 日志:BLE 开发者常用过滤器与技巧 - CSDN
- 2. BLE MTU Negotiation Explained: How to Send More Data Per Packet
- 3. nRF52840 Dongle  Wireshark 抓取 BLE 数据包:保姆级实战指南
- 4. 蓝牙流量分析实战:从HCI抓包到GATT语义解析全链路 - CSDN
- 5. BLE ATT解析
- 6. nRF52840 Dongle  Wireshark:BLE抓包实战方案全解析
- 7. Integrating Polar H10 BLE Heart Rate Data into a PLC System
- 8. 从数据包抓取到协议解析:手把手教你用Wireshark分析BLE ATT层通信 - CSDN
- 9. How to Debug BLE Connection Failures with a Sniffer
- 10. BLE ATT协议中常见的技术问题: **ATT_MTU交换失败导致数据传输异常** - CSDN
- 11. WiresharkBLE dongle抓包log过滤器设置 - CSDN
- 12. 蓝牙与近场通信安全取证深度分析
- 13. WiresharkBLE dongle: BLE数据包捕获以及分析 - CSDN
- 14. wireshark抓取ble数据包 - CSDN

</details>

BLE 的 MTU 协商在 ATT 层，不叫 LL 包，而是 **Exchange MTU Request/Response**：

- Exchange MTU Request：opcode 0x02

- Exchange MTU Response：opcode 0x03

## 一、最常用：所有 MTU 协商包

```text
btatt.opcode == 0x02 || btatt.opcode == 0x03
```

只看 ATT 层、且只留 MTU，等价于上面这条。

## 二、拆成请求/响应

```text
btatt.opcode == 0x02        # 客户端发起 Exchange MTU Request
btatt.opcode == 0x03        # 服务端回 Exchange MTU Response
```

想看“谁申请多大、对方回多大”，两条都留最方便。

## 三、按协商值过滤

Wireshark 解析后通常有字段可写 MTU 数值，版本不同字段名可能略变，优先用详情右键：

```text
btatt.exchange_mtu_request.mtu == 247      # 请求 MTU=247（部分版本可用）
btatt.exchange_mtu_response.mtu == 23      # 响应仍回默认23，说明对端不支持大包
```

如果上面报红，展开包详情里 ATT → Exchange MTU → Client/Server RX MTU，对数值行右键 **Apply as Filter**。

## 四、空口/nRF 按连接跟 MTU

先找到目标连接 access address，再叠加：

```text
btle.access_address == 0x9925cfbf && (btatt.opcode == 0x02 || btatt.opcode == 0x03)
```

只抓某个外设的完整过程可先按广播地址定位连接：

```text
btle.advertising_address == aa:bb:cc:dd:ee:ff && (btatt.opcode == 0x02 || btatt.opcode == 0x03)
```

> 注意：连接建立后的数据信道包不一定还带 advertising_address，外设用 RPA 或要跟整条连接时，最好先从 CONNECT_IND 取 access_address 用 btle.access_address 过滤。

## 五、本机 HCI 日志（Android btsnooz / Linux hcidump / Windows ETW）

ATT 仍然走 btatt，所以同样的：

```text
btatt.opcode == 0x02 || btatt.opcode == 0x03
```

就能从 HCI 的 ACL→L2CAP→ATT 里筛出 MTU 协商；不需要换 bthci 字段。

## 六、排错注意

- 只看到 Request 没 Response：可能对端不支持大 MTU、连接超时、或请求后立刻断链；用 frame.time_delta 看请求到响应间隔。

- 加密连接没解密：ATT 是密文，btatt 出不来，先在 SMP/LL 加 LTK/SC 参数再重抓。

- 默认 MTU 23 也算“协商成功”：Response 回 23 表示对端只接受默认值，不是失败。

- 若 Info 列显示 “Exchange MTU Request (MTU: 247)” 之类，直接搜 mtu 也行，但显示过滤器还是用 opcode 最稳。

如果你用的是 nRF Sniffer 还是 Ubertooth、Wireshark 版本多少，可以给到不报红的精确字段名。

---


# 过滤BLE连接成功后服务发现、特征值读取、描述符设置等过程

<details>
<summary>Deep thinking completed (took 8 seconds)</summary>

用户要的是 Wireshark 过滤 BLE 连接成功之后的 GATT 流程：服务发现、特征值读取、描述符设置（含 CCC 通知/指示开关等）。我需要先核实 Wireshark 里 btatt 各 opcode 的准确写法、GATT discovery（primary service/include/characteristic/descriptor）、read/write/notification/indication，以及描述符尤其是 0x2902 CCC 的过滤示例；再结合前面对话里用户关心“指定 MAC/连接”的上下文，补充用 btle.access_address 或 advertising/initiator 限定某条连接的组合。回答时给可直接粘贴的显示过滤器，并提醒 HCI 与空口、加密未解密、UUID 字段名版本差异、右键 Apply as Filter 的兜底方法。

- 1. 借Polar IOTS一道困难挑战题简单入门蓝牙流量分析 - CSDN
- 2. 使用 Wireshark 分析 Android 蓝牙 HCI 日志:BLE 开发者常用过滤器与技巧 - CSDN
- 3. 蓝牙与近场通信安全取证深度分析
- 4. Using Wireshark for Bluetooth Analysis
- 5. Ellisys 抓包实操:ATT/GATT 服务与特征值分析
- 6. How to Capture BLE Packets with nRF Sniffer and Wireshark
- 7. 蓝牙抓包流程与实践:从加密机制到 Wireshark 实战指南
- 8. GATT Protocol Implementation  noble/noble  DeepWiki
- 9. nRF Sniffer 4.6.6 实战:5个高效过滤规则精准捕获目标BLE设备数据包
- 10. Integrating Polar H10 BLE Heart Rate Data into a PLC System
- 11. BLE 抓包完全教程:nRF52840 Dongle  Wireshark
- 12. Bluetooth Pentesting 101: BLE Sniffing with nRF52840 and Wireshark
- 13. wireshark-capture
- 14. nRF52840 Dongle:Windows蓝牙BLE开发与嗅探实战指南
- 15. BLE GATT Notify, Indicate, Descriptors & GATT Service
- 16. nRF52840 Dongle  Wireshark:BLE抓包实战方案全解析
- 17. WiresharkBLE dongle: BLE数据包捕获以及分析 - CSDN

</details>

连接成功后的 GATT 流程都在 ATT 层，用 btatt.* 过滤最省事。下面按“服务发现 → 特征发现 → 描述符发现 → 读特征 → 写特征/写描述符 → 通知/指示”给可直接粘贴的过滤器。

## 一、MTU 协商（连接后第一步，通常先过）

```text
btatt.opcode == 0x02 || btatt.opcode == 0x03      # Exchange MTU Request/Response
```

## 二、服务发现（Primary Service）

主服务发现用 Read By Group Type，UUID 固定 0x2800：

```text
btatt.opcode == 0x10 || btatt.opcode == 0x11      # Read By Group Type Req/Rsp（发现主服务）
btatt.uuid16 == 0x2800                            # 仅看主服务声明（部分版本可用）
btgatt.service_uuid == 0x180d                     # 直接按服务UUID，如心率；版本不支持就改按handle
```

典型中央会发 0x10、起始句柄 0x0001、结束 0xffff、UUID 0x2800，从端回若干服务范围。

## 三、特征发现（Characteristic）

特征声明 UUID 0x2803，用 Read By Type：

```text
btatt.opcode == 0x08 || btatt.opcode == 0x09      # Read By Type Req/Rsp（发现特征声明）
btatt.uuid16 == 0x2803                            # 仅特征声明
btatt.uuid16 == 0x2a19                            # 按特征UUID，如电池电量；自定义UUID换对应值
```

注意 0x2803 是“特征声明”，真正读写的是它后面那个 Value Handle，Wireshark 展开后能看到 Value Handle / Properties / UUID。

## 四、描述符发现（含 CCCD 0x2902、用户描述 0x2901 等）

用 Find Information：

```text
btatt.opcode == 0x04 || btatt.opcode == 0x05      # Find Information Req/Rsp（枚举描述符）
btatt.uuid16 == 0x2902                            # 只挑CCCD（通知/指示开关）
btatt.uuid16 == 0x2901                            # 用户描述符
```

如果已经知道 CCCD 句柄，直接按句柄看更准（见下）。

## 五、读特征值 / 读描述符

```text
btatt.opcode == 0x0a                              # Read Request
btatt.opcode == 0x0b                              # Read Response
btatt.opcode == 0x0c || btatt.opcode == 0x0d      # Read Blob Request/Response（长值分段读）
btatt.handle == 0x0025 && (btatt.opcode == 0x0a || btatt.opcode == 0x0b)   # 某句柄读
```

## 六、写特征值 / 写描述符（含CCCD使能通知）

```text
btatt.opcode == 0x12                              # Write Request（有Response）
btatt.opcode == 0x13                              # Write Response
btatt.opcode == 0x52                              # Write Command（无响应）
btatt.handle == 0x0029 && btatt.opcode == 0x12    # 某句柄写请求，如CCCD句柄
```

CCCD 开关值惯例：写 01 00=开 Notify，02 00=开 Indicate，00 00=关。 完整看“开通知”过程：

```text
btatt.handle == 0x0029 && (btatt.opcode == 0x12 || btatt.opcode == 0x13)   # 替换成实际CCCD句柄
# 或按UUID粗筛所有CCCD写
btatt.uuid16 == 0x2902 && (btatt.opcode == 0x12 || btatt.opcode == 0x52)
```

长写入（超过 MTU）会走 Prepare/Execute：

```text
btatt.opcode == 0x16 || btatt.opcode == 0x17 || btatt.opcode == 0x18 || btatt.opcode == 0x19
# Prepare Write Req/Rsp、Execute Write Req/Rsp
```

## 七、通知 / 指示（设备主动推）

```text
btatt.opcode == 0x1b                              # Handle Value Notification
btatt.opcode == 0x1d                              # Handle Value Indication
btatt.opcode == 0x1e                              # Handle Value Confirmation（指示确认）
btatt.handle == 0x002a && btatt.opcode == 0x1b    # 某特征通知
```

## 八、错误排查

```text
btatt.opcode == 0x01                              # ATT Error Response
btatt.error_code == 0x05                          # Insufficient Authentication（需配对/加密）
btatt.error_code == 0x0a                          # Attribute Not Found
btatt.error_code == 0x06                          # Request Not Supported
```

## 九、把“整条连接的所有GATT”圈出来

空口/nRF 先按连接 access address 跟：

```text
btle.access_address == 0x9925cfbf && btatt
```

没 access address 时先用外设 MAC 定位 CONNECT_IND，再从包详情复制连接 Access Address：

```text
btle.advertising_address == aa:bb:cc:dd:ee:ff && (btle.advertising_header.pdu_type == 0x05 || btatt)
```

HCI 日志（Android btsnooz / Linux hcidump）同样用 btatt，定位设备用：

```text
bthci_evt.le_meta_subevent == 0x01 && bthci_evt.peer_address == aa:bb:cc:dd:ee:ff && btatt
```

## 十、一条“连接成功后完整GATT流程”组合

```text
btle.access_address == 0x9925cfbf && (
  btatt.opcode == 0x02 || btatt.opcode == 0x03 ||   # MTU
  btatt.opcode == 0x10 || btatt.opcode == 0x11 ||   # 服务
  btatt.opcode == 0x08 || btatt.opcode == 0x09 ||   # 特征
  btatt.opcode == 0x04 || btatt.opcode == 0x05 ||   # 描述符
  btatt.opcode == 0x0a || btatt.opcode == 0x0b ||   # 读
  btatt.opcode == 0x0c || btatt.opcode == 0x0d ||   # 长读
  btatt.opcode == 0x12 || btatt.opcode == 0x13 || btatt.opcode == 0x52 ||  # 写
  btatt.opcode == 0x16 || btatt.opcode == 0x17 || btatt.opcode == 0x18 || btatt.opcode == 0x19 ||  # 队列写
  btatt.opcode == 0x1b || btatt.opcode == 0x1d || btatt.opcode == 0x1e ||  # 通知/指示
  btatt.opcode == 0x01                               # 错误
)
```

> 小技巧：字段名因 Wireshark 版本/抓包源不同可能变（如 btatt.uuid16 vs btgatt.*、CCCD 字段路径不同）。任意 ATT 包中间面板展开 → 对目标行右键 **Apply as Filter → Selected**，自动生成当前环境可用表达式，比背 opcode 更稳。

如果你用的是 nRF Sniffer 还是 Android HCI snoop、以及 Wireshark 版本，我可以按你的环境把上面再精简成几条第手过滤。

---

# 过滤出特定MAC地址的GATT服务发现包中的特定字段？

<details>
<summary>Deep thinking completed (took 9 seconds)</summary>

用户要的是 Wireshark 里按「特定 BLE MAC」过滤 GATT 服务发现，并且进一步按「特定字段」（比如服务 UUID、特征 UUID、句柄、声明类型 0x2800/0x2803 等）缩小。需要先核实 Wireshark 对 BLE 空口/ATT 的可用显示过滤字段，尤其是 btle.advertising_address、btle.access_address、btatt 各 opcode/uuid/handle 字段，以及服务发现（Read By Group Type 主服务、Read By Type 特征/包含/声明）的写法。还要考虑连接后空口不再带 MAC，必须用 CONNECT_IND 的 access address 跟流；如果只按 advertising_address 过滤，服务发现多数在数据信道、可能不匹配，需要给替代方案（先按 MAC 找连接→取 access address→再 btatt 过滤，或用 nRF/PCAP 若带地址上下文）。我会搜索 Wireshark 官方/常见字段名和示例，避免凭记忆给错字段。回答时按场景给可粘贴过滤器：全服务发现、指定服务UUID、指定特征UUID、指定句柄范围、指定声明UUID，以及「MAC+字段」组合和报红时右键 Apply as Filter 的兜底办法。

- 1. Microchip BLE嗅探器实战指南:从硬件配置到协议分析 - CSDN
- 2. 【Bluetooth-SIG】【CoreV6.2】【Vol3 Part F】【四】【Attribute Type——UUID 是 Attribute 的身份证】
- 3. nRF52840 Dongle  Wireshark 抓取 BLE 数据包:保姆级实战指南
- 4. 借Polar IOTS一道困难挑战题简单入门蓝牙流量分析 - CSDN
- 5. Ellisys 抓包实操:ATT/GATT 服务与特征值分析
- 6. 资讯详情
- 7. BLE 抓包完全教程:nRF52840 Dongle  Wireshark
- 8. 【Bluetooth-SIG】【CoreV6.2】【Vol3 Part G】【GATT】【55】【Vol 3 Part G 总结篇:GATT 从 Attribute 表到服务框架的完整闭环】 - CSDN
- 9. BLE协议分析仪实战:用nRF52840 Dongle和Wireshark定位蓝牙连接疑难杂症 - CSDN
- 10. Using Wireshark for Bluetooth Analysis
- 11. Integrating Polar H10 BLE Heart Rate Data into a PLC System
- 12. 蓝牙与近场通信安全取证深度分析
- 13. wireshark-capture
- 14. 别再死记硬背ATT报文了!用Wireshark抓包实战,带你搞懂BLE通信里Handle和UUID的映射过程
- 15. How to Capture BLE Packets with nRF Sniffer and Wireshark
- 16. Bluetooth Pentesting 101: BLE Sniffing with nRF52840 and Wireshark
- 17. BLE抓包实战:nRF Dongle与Wireshark环境搭建及链路层解析-CSDN博客 - CSDN

</details>

按“特定 MAC + GATT 服务发现 + 指定字段”做，空口和 HCI 思路不一样。最关键一点：服务发现发生在**连接建立后的 ATT 阶段**，数据信道包通常不再带广播 MAC，所以不能直接只写 btle.advertising_address 就指望筛出所有 Read By Group/Read By Type；要先按 MAC 定位连接，再用 access address 跟 ATT。

## 一、先按 MAC 锁定这条连接

**空口/nRF/Ubertooth/Ellisys**：先从广播和 CONNECT_IND 找到目标外设 MAC，取连接 access address。

```text
# 1）该MAC所有广播/扫描响应/连接请求
btle.advertising_address == aa:bb:cc:dd:ee:ff

# 2）该MAC作为被连方的CONNECT_IND，详情里复制Access Address
btle.advertising_header.pdu_type == 0x05 && btle.advertising_address == aa:bb:cc:dd:ee:ff

# 3）用连接access address跟后续所有ATT（服务发现都在这）
btle.access_address == 0x9925cfbf && btatt
```

如果只要“该 MAC 相关的一切空口包（广播+连接后ATT）”，分两段合并：

```text
(btle.advertising_address == aa:bb:cc:dd:ee:ff) || (btle.access_address == 0x9925cfbf && btatt)
```

nRF Sniffer 更简单：Wireshark 设备下拉选该 MAC，它会自动跟广播→CONNECT→数据信道；不想用下拉就用手工 access address。

**本机 HCI 日志**（Android btsnooz / Linux hcidump / Windows ETW）：连接完成事件按对端地址定位，再直接 btatt：

```text
bthci_evt.le_meta_subevent == 0x01 && bthci_evt.peer_address == aa:bb:cc:dd:ee:ff && btatt
```

## 二、只筛“服务发现”过程

GATT 服务发现主要三类：

```text
# 主服务发现：Read By Group Type，UUID 0x2800
btatt.opcode == 0x10 || btatt.opcode == 0x11

# 特征发现：Read By Type，UUID 0x2803
btatt.opcode == 0x08 || btatt.opcode == 0x09

# 描述符发现：Find Information
btatt.opcode == 0x04 || btatt.opcode == 0x05
```

全量服务发现一股脑看：

```text
btatt.opcode == 0x10 || btatt.opcode == 0x11 || btatt.opcode == 0x08 || btatt.opcode == 0x09 || btatt.opcode == 0x04 || btatt.opcode == 0x05
```

## 三、按“特定字段”继续缩

**按声明类型（服务/特征/CCCD）**

```text
btatt.uuid16 == 0x2800   # 主服务声明
btatt.uuid16 == 0x2803   # 特征声明
btatt.uuid16 == 0x2902   # CCCD（通知/指示开关）
btatt.uuid16 == 0x2901   # 用户描述符
```

**按具体服务 UUID**（16 位 SIG UUID）

```text
btatt.uuid16 == 0x180d   # 心率
btatt.uuid16 == 0x180f   # 电池
btatt.uuid16 == 0x1812   # HID
btatt.uuid16 == 0x180a   # Device Information
```

**按具体特征 UUID**

```text
btatt.uuid16 == 0x2a19   # 电池电量
btatt.uuid16 == 0x2a37   # 心率测量
btatt.uuid16 == 0x2a00   # Device Name
```

**按属性句柄**

```text
btatt.handle == 0x0012          # 某句柄的ATT操作
btatt.handle >= 0x0010 && btatt.handle <= 0x0020   # 某服务句柄区间
```

**128 位自定义 UUID**：字段名随版本可能叫 btatt.uuid、btatt.uuid128、btgatt.*。最稳是对包详情里 UUID 行右键 **Apply as Filter → Selected**。例如自定义 0000ff01-0000-1000-8000-00805f9b34fb 就别硬背字段，直接右键生成。

## 四、“特定 MAC + 特定服务/特征”组合示例

假设外设 MAC AA:BB:CC:DD:EE:FF、连接 access address 0x9925cfbf，只看重它的主服务发现和“电池服务/电量特征”：

```text
btle.access_address == 0x9925cfbf && (
  (btatt.opcode == 0x10 || btatt.opcode == 0x11) ||
  btatt.uuid16 == 0x180f ||
  btatt.uuid16 == 0x2a19
)
```

只看它发现“某自定义特征 ff01”的声明：

```text
btle.access_address == 0x9925cfbf && btatt.uuid16 == 0x2803 && btatt.uuid16 == 0xff01
```

> 注意：Read By Type 请求包里过滤“要查的UUID”和响应包里“返回的特征UUID”用的都是 btatt.uuid16；有些版本请求阶段字段层级较深，若 btatt.uuid16==0xff01 报红，展开 ATT → Read By Type → Attribute Type/Characteristic UUID 右键应用。

## 五、偷懒/防报红办法

Wireshark 不同版本、nRF 插件、Ubertooth 解析路径不完全一致：

1.包列表选中一个服务发现包；

2.中间面板展开 Bluetooth Attribute Protocol / ATT；

3.找到 Service UUID、Characteristic UUID、Handle、Opcode 任一行；

4.右键 → **Apply as Filter → Selected**，自动出当前环境可用字段名。

另外可用菜单 **Wireless → Bluetooth ATT Server Attributes** 直接列出抓包里所有服务/特征/句柄，不必写过滤。

如果你把 Wireshark 版本、抓包源（nRF52840 / Ubertooth / Android btsnooz / Linux hcidump）和目标 UUID 发我，可以直接给不报红的完整一条。

---

# btle.access_address == 0x9925cfbf 是什么意思？其中 0x9925cfbf 代表什么？

<details>
<summary>Deep thinking completed (took 3 seconds)</summary>

我们需要理解用户的问题：用户问的是“btle.access_address == 0x9925cfbf 是什么意思？其中 0x9925cfbf 代表什么？”这涉及到BLE（低功耗蓝牙）空口包的结构。在之前的对话中，我们提到了用access_address来过滤连接后的数据包。现在用户希望解释这个过滤条件的含义。

首先，btle.access_address是Wireshark中用于过滤BLE链路层数据包的字段，它指的是蓝牙空口包中的“接入地址”（Access Address）。在BLE中，每个物理信道上的数据包都有一个接入地址。对于广播信道（37/38/39），接入地址是固定的0x8E89BED6。而对于数据信道（连接后），接入地址是由连接发起方在CONNECT_IND中随机生成的唯一32位值，用于标识特定的连接。因此，0x9925cfbf是一个具体的接入地址值，代表某条特定的BLE连接。

所以，解释应该包括：这个过滤条件的作用是只显示具有该特定接入地址的BLE数据包，也就是只显示某条特定连接的所有空口包（包括LL控制包、空包、数据包等）。而0x9925cfbf是该连接的接入地址，通常是从CONNECT_IND包中获取的。

回答需要清晰、准确，并且符合元宝的角色规范（不要使用括号旁白，不要主动提自己是元宝等）。用户可能是在学习Wireshark过滤，所以解释应通俗易懂。

另外，注意用户之前问了很多关于BLE过滤的问题，所以回答时可以稍微联系上下文，但重点还是直接回答问题

</details>

btle.access_address == 0x9925cfbf 是一个 Wireshark 显示过滤器，意思是：

**只显示蓝牙低功耗（BLE）空口包中，接入地址（Access Address）等于 0x9925CFBF 的所有数据包。**

---

## 0x9925cfbf 是什么？

这是一个 **32 位的十六进制数**，代表**某条 BLE 连接的接入地址（Access Address）**。

### BLE 空口包结构背景

每个 BLE 空口包的前 4 个字节就是接入地址：

- **广播信道（37/38/39）**：接入地址固定为 0x8E89BED6，所有广播包都用同一个。

- **数据信道（连接建立后）**：接入地址由连接发起方（中央）在 CONNECT_IND 包中随机生成，**每条连接独享一个**，用于标识这条连接上的所有数据包（LL 数据、LL 控制、空包等）。

所以 0x9925cfbf 就是你在抓包中看到的某条具体连接的接入地址，用它过滤就能只看那条连接的所有空口交互，不看其他广播或其他连接的包。

---

## 怎么来的？

一般流程：

1.先用 btle.advertising_address == 目标MAC 找到该设备的广播包和 CONNECT_IND。

2.在 CONNECT_IND 包的详情里找到 Access Address 字段，记下它的值（比如 0x9925cfbf）。

3.然后输入 btle.access_address == 0x9925cfbf，就能看到这条连接从建立到断开的所有数据包。

---

## 对比一下

| 过滤表达式 | 作用 |
| --- | --- |
| btle.access_address == 0x8e89bed6 | 只看所有广播包（所有设备） |
| btle.access_address == 0x9925cfbf | 只看某一条特定连接的数据包 |

---

一句话总结：**btle.access_address == 0x9925cfbf 就是把 Wireshark 的视野锁定在某一条 BLE 连接上，忽略其他无关流量。**

---

**问：** mac地址是48位的，但是0x9925cfbf 只有32位，为什么？

<details>
<summary>Deep thinking completed (took 1 seconds)</summary>

我们注意到用户问了一个关于MAC地址位数和Access Address位数矛盾的问题。用户之前问了btle.access_address == 0x9925cfbf的含义，现在质疑为什么MAC地址是48位而这里是32位。需要澄清：Access Address不是MAC地址，它们是不同的概念。解释清楚BLE数据包结构中，连接后的数据包使用32位Access Address而非48位MAC地址来标识连接。这是BLE协议的设计，用于节省开销和提高效率。同时指出Access Address由中央在CONNECT_IND中随机生成，唯一标识一条连接

</details>

好问题。**Access Address 不是 MAC 地址，它们是两个完全不同的东西。**

| 项目 | MAC 地址 | Access Address |
| --- | --- | --- |
| 位数 | 48 位（6 字节） | 32 位（4 字节） |
| 用途 | 标识设备身份（全球唯一） | 标识**一条 BLE 连接**（连接内唯一） |
| 出现阶段 | 广播包、连接请求包（CONNECT_IND） | 连接建立后的**所有数据信道包** |
| 是否固定 | 设备出厂固定或可配置（随机/公共） | 由中央在 CONNECT_IND 中**随机生成**，每条连接不同 |

---

## 为什么连接后不用 MAC 地址，改用 32 位的 Access Address？

1.**减少空中开销**：每个数据包都要带地址，48 位 MAC 比 32 位多 2 字节。BLE 追求低功耗、短包，省下这 2 字节对吞吐量和功耗都有好处。

2.**隐私保护**：如果用固定 MAC 地址，第三方可以持续追踪设备。Access Address 每次连接随机生成，连接断开后失效，无法跨连接关联。

3.**连接唯一性**：一个设备可能同时存在多条连接（比如手机同时连手表和耳机），每条连接用不同的 Access Address 区分，互不干扰。

---

## 数据包结构示意

```Pure Text
广播包（37/38/39信道）：
[4字节固定接入地址 0x8E89BED6] [PDU头] [广播地址(MAC)] [数据] [CRC]

数据信道包（连接后）：
[4字节随机Access Address] [LL头] [LL数据] [MIC(可选)] [CRC]
```

广播信道的接入地址是固定的 0x8E89BED6，所有广播包共用；数据信道的接入地址是随机生成的，每条连接唯一。

---

## 一句话总结

**0x9925cfbf 不是 MAC 地址，它是 BLE 连接内部用来标识“这条连接”的 32 位随机编号。** 你用 btle.access_address == 0x9925cfbf 过滤，是在说“只看这条连接上的所有数据包”，而不是按设备 MAC 过滤。

---


# btle.access_address == 0x9925cfbf 只看某一条特定连接的数据包，0x9925cfbf 代表哪条特定链路？还有哪些Access Address？

<details>
<summary>Deep thinking completed (took 8 seconds)</summary>

用户问的是 Wireshark 里 btle.access_address == 0x9925cfbf 到底代表哪条链路、0x9925cfbf 本身怎么对应到具体连接，以及 BLE 还有哪些 Access Address。需要先核实 BLE 规范里 Access Address 的分类：广播固定 0x8E89BED6、连接态由发起方在 CONNECT_IND/LLData 里生成随机 32 位值并满足格式约束、可能还有不同版本/角色下的特殊用例；再结合 Wireshark 如何从包里看 access_address、如何在 CONNECT_IND 找到它、如何把它映射到对端 MAC/角色。还要提醒 0x9925cfbf 只是示例值，本身不代表某厂商或固定链路，必须回到抓包上下文看它出现在哪个 CONNECT_IND、advertiser/initiator 地址、信道、接入后 ATT 等。搜索用几个精准 query 覆盖规范取值、Wireshark 定位方法、连接请求中的分配逻辑。回答时给出过滤示例、常见地址表、以及如何从“未知 0x…”反查是哪条链路的操作步骤。

- 1. nRF Sniffer for Bluetooth LE v4.1.0 User Guide
- 2. The Bluetooth Low Energy primer  Bluetooth Technology Website
- 3. How to Capture BLE Packets with nRF Sniffer and Wireshark
- 4. 智能腰带升级方案
- 5. Bluetooth Core Specification
- 6. Nordic nRF Sniffer实战:5分钟搞定BLE加密报文抓包与解密(附LESC配对调试技巧) - CSDN
- 7. BLE空中数据包格式 - CSDN
- 8. BLE抓包实战:nRF Dongle与Wireshark环境搭建及链路层解析-CSDN博客 - CSDN
- 9. BLE的广播､扫描和连接等工作机制总结 - CSDN
- 10. 低功耗蓝牙黑客:从数字逃逸到现实.pdf
- 11. Demystifying Bluetooth LE (BLE) Addresses
- 12. ios 蓝牙 广播包 蓝牙广播包分析
- 13. 蓝牙专题(4)--链路层Link Layer(空中接口包 & 比特流处理) - 爱码网
- 14. 西安城市开发者社区 - CSDN
- 15. 低功耗蓝牙BLE之报文 - CSDN

</details>

0x9925cfbf 本身只是一个 32 位随机数，不绑定任何厂商、不绑定 MAC。它在你的抓包里“代表哪条链路”，完全取决于**谁在 CONNECT_IND 里把它分配给了哪两个设备**。下面说清楚。

## 一、0x9925cfbf 代表“哪条”链路

在 BLE 空口里，一条 ACL 连接由这些信息共同确定，Access Address 只是其中一个“会话 ID”：

- 由谁发起：CONNECT_IND 里的 Initiator Address（中央/主机 MAC）

- 连谁：CONNECT_IND 里的 Advertising Address（外设/从机 MAC）

- 会话标识：Access Address（如 0x9925cfbf）

- 同步参数：CRC Init、Channel Map、Hop Increment、Interval/Latency/Timeout 等

所以 btle.access_address == 0x9925cfbf 的含义是：“只看接入地址为 0x9925cfbf 的这条连接的所有数据信道包”。它对应哪两个设备，要去 CONNECT_IND 里反查，不能从 0x9925cfbf 直接看出 MAC。nRF 抓包示例里就出现过 Access Address: 0x9925cfbf 同时带 Master Address / Slave Address，那种情况下它才明确对应那对主从。

> 也就是说：0x9925cfbf 不是“某设备”，是“某次连接”。设备重连通常会重新生成新的 AA。

## 二、BLE 里都有哪些 Access Address

按规范大致分几类 ：

| 场景 | Access Address | 说明 |
| --- | --- | --- |
| 传统/扩展广播信道包（37/38/39 的 ADV_*，以及其它广播物理信道包） | 0x8E89BED6 固定 | 所有设备公共识别，不区分设备 |
| ACL 连接数据信道（CONNECT_IND 建立） | 随机 32 位，如 0x9925cfbf | 由发起方/中央为每次连接生成，整条连接不变 |
| 周期广播 train（AUX_SYNC/AUX_CHAIN 等） | 在 AUX_ADV_IND 的 SyncInfo 里下发 | 每个周期广播序列一个 AA |
| 带响应的周期广播子事件 | 另一套 AA（SyncInfo/响应计时信息里） | 与同步子事件 AA 不同 |
| 扩展广播里的 AUX_CONNECT_REQ / RSP | 按对应同步/连接参数 | 辅助连接请求场景 |
| CIS（连接同步流，LE Audio 等） | 随机 32 位，由中央通过 LL CIS 建立 PDU 下发 | 每条 CIS 一个，和 ACL AA 不同 |
| BIS/BIG（广播同步，广播音频） | 由 Seed AA 派生 | 每个 BIS 及 BIG Control 各有 AA |

连接用 AA 的生成约束（核心规范摘要）：

- 32 位随机值

- 不能等于广播 AA 0x8E89BED6，也不能只和它差 1 位

- 四个字节不能全相等

- 连续 0 或连续 1 不超过 6 个

- 总跳变不超过 24 次，最高 6 位至少 2 次跳变

- 不能与本设备已有 ACL/CIS/周期广播/BIS 的 AA 重复

这些约束是为了空口相关性和防误判，不是安全密钥（虽然它也顺带起到“别的设备忽略此包”的作用）。

## 三、在 Wireshark 里把 0x9925cfbf 反查成“谁连谁”

1.过滤找到分配它的连接请求：

  ```text
btle.advertising_header.pdu_type == 0x05 && btle.access_address == 0x9925cfbf
```

  不同版本字段可能嵌套在 btle.connect_request.* / LLData 下；找不到就直接搜 access_address。

2.打开该 CONNECT_IND 包详情：

  - Bluetooth LE Link Layer → Connect_Ind / LLData

  - 看 Access Address: 0x9925cfbf

  - 看 Initiator Address（中央）、Advertising Address（外设）

  - 看 CRC Init、Channel Map、Hop Increment、Interval/Latency/Timeout

3.确认后可用这对地址或 AA 跟全程：

  ```text
# 这条连接所有空口包
btle.access_address == 0x9925cfbf
# 该外设广播+这条连接（需手动替换AA）
(btle.advertising_address == aa:bb:cc:dd:ee:ff) || (btle.access_address == 0x9925cfbf)
# 该中央发起的连接
btle.initiator_address == 11:22:33:44:55:66 && btle.access_address == 0x9925cfbf
```

4.nRF Sniffer 更省事：设备下拉选外设 → 它会自动从广播跟到 CONNECT_IND 再按 AA 跟数据信道；包列表里 AA 列、Master/Slave 地址列都能直接看。

## 四、容易混的点

- 广播阶段全是 0x8E89BED6，所以用 AA 不能区分“哪个设备广播”；区分设备用 btle.advertising_address。

- 进入数据信道后包头不再带 MAC，只用 AA；想按人过滤就必须先由 CONNECT_IND 建立“MAC↔AA”映射。

- 若外设用 RPA（可解析随机地址），每次广播 MAC 可能变，但同一次连接里 AA 不变；跨多次连接 AA 也会变，不能长期用固定 AA 跟人。

- 加密连接若没在 Wireshark 导入 LTK/SC 信息，ATT 层看不了明文，但 AA、LL 控制、连接参数这些空口字段仍然能用。

如果你把抓到的 CONNECT_IND 截图或贴一下 Initiator/Advertising Address + Access Address + Channel Map/Hop 几行，可以直接帮你判断 0x9925cfbf 对应哪对设备、以及为什么它只跟到部分包。

---


# wireshark使用btle.access_address == 0x9925cfbf过滤，没有任何过滤结果，这是怎么回事？备注：抓包是全的
<details>
<summary>Deep thinking completed (took 8 seconds)</summary>
用户说在 Wireshark 用 btle.access_address == 0x9925cfbf 过滤没结果，且自称抓包“全的”。需要先核实可能原因：字段名/写法问题、抓的是HCI不是空口、access address根本没出现或被解析器放在不同路径、CONNECT_IND里实际AA不是这个值、广播阶段只用0x8E89BED6而连接后数据没抓到、nRF/其他sniffer的封装字段不同、大小写/十六进制前缀/显示过滤器报红但未注意、加密或重组导致btle层不识别、Wireshark版本字段改名。回答要先给排查步骤：看捕获里是否有CONNECT_IND、搜索access_address原始字段、用btle帧尝试、查Link-Layer协议列、用nordic_ble/ubertooth/其他空口字段、确认抓包接口类型。可搜索一下Wireshark btle.access_address无结果常见原因和nRF sniffer字段名，给出可直接替换的过滤示例。

- 1. nRF52840 DK sniffer fails to display Data messages after Connect_Ind, only advertisements
- 2. BLE协议分析仪实战:用nRF52840 Dongle和Wireshark定位蓝牙连接疑难杂症 - CSDN
- 3. How to Capture BLE Packets with nRF Sniffer and Wireshark
- 4. nRF Sniffer 4.6.6 实战:5个高效过滤规则精准捕获目标BLE设备数据包
- 5. nRF Sniffer User Guide v2.1
- 6. BLE 抓包完全教程:nRF52840 Dongle  Wireshark
- 7. nRF51822  Wireshark:低功耗蓝牙空口抓包实战指南-CSDN博客 - CSDN
- 8. nRF52840 Dongle  Wireshark:BLE抓包实战方案全解析
- 9. Tips for filtering BLE packets using Wireshark and Nordic BLE Sniffer
- 10. nRF52840 Dongle  Wireshark 抓取 BLE 数据包:保姆级实战指南
- 11. 蓝牙与近场通信安全取证深度分析
- 12. BLE抓包实战:nRF Dongle与Wireshark环境搭建及链路层解析-CSDN博客 - CSDN

</details>

btle.access_address == 0x9925cfbf 无结果，通常不是语法问题（btle.access_address 是标准 32 位字段，Wireshark 1.12+ 都有），而是“这个值在你这份抓包里根本没出现”或“抓包没被解析成 btle 空口”。按下面顺序查最快。

## 一、先确认这份抓包到底是“空口”还是“HCI”

btle.access_address 只存在于 BLE 空口链路层。如果你抓的是：

- 本机 Android btsnooz、Linux hcidump/btmon、Windows ETW Bluetooth

- 手机/电脑自身 HCI 日志

那通常没有 btle.access_address，或字段层级不同，用 bthci_* 而不是 btle.*。空口才用 nRF52840、Ubertooth、Ellisys、Frontline 这类。

快速判断：随便点一个包，中间详情看协议列/树：

- 有 Bluetooth Low Energy Link Layer → 空口，继续查 AA

- 只有 HCI Command/Event/ACL、Bluetooth HCI → 不是空口，别用 access_address

## 二、确认 0x9925cfbf 真的来自本抓包

别拿别的抓包、别的设备、网上示例值直接套。在本文件里这样找：

1.过滤 btle 看所有 BLE 空口包

2.找 CONNECT_IND：btle.advertising_header.pdu_type == 0x05（老版本可能 btle.pdu_type==5）

3.展开该包 → Bluetooth Low Energy Link Layer → Connect_Ind/LLData → Access Address，看实际值是不是 0x9925cfbf

4.如果 CONNECT_IND 里 AA 是别的，比如 0x50656bdc，那你写 9925 当然空

nRF 数据信道包详情里会直接显示 Access Address: 0x... 以及 Master/Slave 地址，照抄再过滤。

## 三、连接已经在“开始抓包前”建立 → 跟不到数据信道

nRF Sniffer 要在 CONNECT_IND 那一刻抓到连接参数（AA、Channel Map、Hop、CRC Init）才能跟跳频。如果：

- 设备早就连上了，你中途才开始抓

- Sniffer 没听到 CONNECT_IND（距离远、只听某广播信道、被 Wi‑Fi 干扰）

- 中央用了扩展广播/AUX_CONNECT 而你的固件/版本不全支持

结果就是：广播有、CONNECT_IND 没有、数据信道全跟不上，按 AA 过滤自然空。

验证：过滤 btle.advertising_header.pdu_type == 0x05 看有没有连接请求；没有就重抓，且在设备断链重连瞬间开始抓。

## 四、广播阶段本来就不是这个值

广播/扫描/连接请求都在广播信道，接入地址固定 0x8E89BED6；只有 CONNECT_IND 之后的数据信道包才用随机 AA。比如你只抓到广播、没抓到后续数据，写 0x9925cfbf 必空。

可先试：

```text
btle.access_address == 0x8e89bed6      # 所有广播类包（有结果说明空口解析正常）
btle                                # 所有btle包，看协议列和数量
btle.advertising_header.pdu_type == 0x05   # 有没有CONNECT_IND
```

如果前两条有、第三条没有，说明没捕获到建连，AA 过滤为空是正常的。

## 五、解析器/字段名/过滤栏问题

- 过滤栏报红：说明字段不被当前解析器识别。空口正常应有 btle.access_address；报红就别硬写，去包详情找 Access Address 行，右键 → Apply as Filter → Selected，让 Wireshark 自动生成。

- 某些封装/老版本把连接参数放 btle.connect_request.*、btle.connect_request.access_address 或 LLData.access_address；但数据信道包标准字段仍是 btle.access_address。

- nRF 环境还有 nordic_ble.* 元数据（channel/rssi/board），但 AA 仍走 btle.access_address，不要用 nordic_ble.access_address（一般没有这字段）。

- 用 tshark 离线确认文件里到底有没有这个字段值：

```bash
tshark -r file.pcap -Y "btle.access_address==0x9925cfbf"
# 看所有出现的AA值：
tshark -r file.pcap -T fields -e btle.access_address | sort -u
```

第二条能把文件里实际存在的所有 AA 列出来，比盲猜强。

## 六、CRC/加密/空包误区

- CRC 错：nRF 默认可能仍显示但标记错误；极端情况某些捕获源丢弃坏包。可试放宽：先看 btle 总数，再对比 btle.crc.ok==0 或 nordic_ble.crcok==0（nRF 字段）看是否大量丢。

- 加密：只影响 ATT/SMP 明文，不影响 btle.access_address 显示。所以“完全无结果”不是加密导致的。

- 空包/keepalive：空包也有 AA，不会让 AA 过滤落空；如果只想要非空数据可再加 btle.length!=0。

## 七、最短排查脚本

```text
btle                                  # 1) 有包吗？协议列是btle吗？
btle.access_address == 0x8e89bed6     # 2) 广播有吗？
btle.advertising_header.pdu_type == 0x05   # 3) 有CONNECT_IND吗？
btle.access_address                    # 4) 直接输字段名，Wireshark自动补全/看是否报红
```

找到 CONNECT_IND 后从详情复制真实 AA，再：

```text
btle.access_address == 0x这里填真实值
```

配合 nRF 跟设备：工具栏选目标外设 → 它会自动从广播跟到连接并按 AA 显示，比手写更稳。

如果你愿意，把抓包里一条 CONNECT_IND 的「Access Address / Initiator / Advertising / Channel Map / Hop」贴出来，或者直接说抓包源（nRF52840 固件版本+Wireshark 版本/Android btsnooz/Ubertooth），可以判断是“值写错”还是“没跟上连接”。

---

**问：** 抓的是空口包

<details>
<summary>Deep thinking completed (took 2 seconds)</summary>

我们确认了用户抓的是空口包，但使用 btle.access_address == 0x9925cfbf 无结果。需要系统排查原因并给出解决方案。用户强调抓包是全的，所以大概率是值不对或字段层级问题。提供逐步诊断方法

</details>

既然确认是空口包（有 Bluetooth Low Energy Link Layer 协议），btle.access_address == 0x9925cfbf 无结果，原因集中在以下三点，按优先级排查：

---

## 1. 这个 0x9925cfbf 根本不存在于当前抓包文件中

你可能是从其他地方（教程、旧抓包、网络示例）复制了这个值，但它并不在你的文件里。

**验证方法：**

```text
# 查看文件里所有出现的 Access Address（包括广播固定值和所有连接的随机值）
tshark -r yourfile.pcapng -T fields -e btle.access_address 2>/dev/null | sort -u
```

如果没有 0x9925cfbf，说明这个值不是你抓包里的。此时应该：

- 找出你抓到的 CONNECT_IND，从中提取真实的 Access Address

- 或者用 nRF Sniffer 的“跟随设备”功能自动关联

---

## 2. 字段层级/名称与当前 Wireshark 版本不匹配

不同 Wireshark 版本、不同抓包插件（nRF、TI CC2540、Ubertooth）对 btle.access_address 的解析路径可能有细微差异。

**快速检查方法：**

1.随便点一个数据信道包（非广播，看 btle.advertising_header.pdu_type 不为 0~5）

2.在中间详情面板展开 Bluetooth Low Energy Link Layer

3.找到 Access Address 这一行，看看它左边的字段名是什么

4.右键 → **Copy → Field Name**，得到准确的字段名

常见变体：

- btle.access_address（标准）

- btle.ll_access_address（某些旧版 nRF 插件）

- btle.connect_request.access_address（仅限 CONNECT_IND 包内）

- nordic_ble.access_address（极少，通常不这样）

**替代方案：** 直接在详情面板的 Access Address 行右键 → **Apply as Filter → Selected**，Wireshark 自动生成当前版本的正确表达式。

---

## 3. 你看到的包全是广播信道包（AA = 0x8E89BED6）

如果你只抓到了广播阶段的包（ADV_IND、SCAN_REQ、CONNECT_IND 本身），而没有抓到连接建立后的数据信道包，那么所有包的 AA 都是 0x8E89BED6，不会有随机 AA。

**验证方法：**

```text
btle.access_address == 0x8e89bed6
```

如果有大量结果，说明你只抓到了广播阶段。这时 btle.access_address == 0x9925cfbf 必然为空。

**为什么会抓不到数据信道包？**

- 抓包硬件只监听广播信道（37/38/39），没有跳到数据信道

- nRF Sniffer 必须在 CONNECT_IND 发生时在场才能获取跳频参数，否则无法跟踪数据信道

- 连接建立后 sniffer 离设备太远，丢包严重

- 使用了扩展广播（Extended Advertising），CONNECT_IND 在 AUX_ADV_IND 中，部分老版本 nRF 固件不支持

**解决办法：**

- 重新抓包，确保在设备断连重连的瞬间开始抓

- 使用 nRF Sniffer 的“设备跟随”功能（在 Wireshark 工具栏选择目标设备 MAC）

- 升级抓包硬件固件到最新版，确保支持扩展广播和所有信道跳频

---

## 4. 连接已经建立，但 sniffer 没有同步到跳频序列

nRF Sniffer 需要收到 CONNECT_IND 才能知道 Access Address、CRC Init、Channel Map、Hop Increment。如果 CONNECT_IND 被错过（例如你只开启了某个广播信道监听，而 CONNECT_IND 发在另一个信道），sniffer 就无法跟踪后续数据包，表现为：

- 广播包正常

- CONNECT_IND 可见（如果它恰好落在你监听的广播信道上）

- 数据信道包完全看不到

**验证方法：**

- 过滤 btle.advertising_header.pdu_type == 0x05，看是否有 CONNECT_IND

- 如果有，展开该包，看 Access Address 的值是多少

- 然后用那个值过滤数据信道包

如果 CONNECT_IND 存在但数据信道包仍然没有，说明 sniffer 未能成功同步（可能因为 CRC 初始化值未正确捕获，或跳频算法不匹配）。尝试更换抓包硬件或调整 nRF Sniffer 配置。

---

## 5. 最终建议：不要依赖记忆中的值

**最可靠的操作步骤：**

1.清空过滤栏，输入 btle 回车，确认看到 BLE 包

2.输入 btle.advertising_header.pdu_type == 0x05 找到连接请求包

3.点开第一个 CONNECT_IND，在中间面板找到 Access Address，记下实际值（比如 0xaabbccdd）

4.输入 btle.access_address == 0xaabbccdd 即可看到该连接的所有数据包

5.如果第2步没有结果，说明你根本没有抓到连接请求，需要重新抓包

---

如果以上步骤仍无效，请提供：

- Wireshark 版本号（Help → About）

- 抓包硬件型号及固件版本（nRF52840 DK 哪个固件版本？Ubertooth One？）

- 在过滤栏输入 btle 后，统计栏显示的包数量

- 截一张 CONNECT_IND 包的 Bluetooth Low Energy Link Layer 展开图（如有）

我可以根据这些信息给出精确的字段路径。

---

# 如何找出CONNECT_IND，从中提取真实的 Access Address。
Access Address在CONNECT_IND的哪个位置？一旦连接成功，后面所有的包都包含这个Access Address吗？不论是peripheral发往central、还是central发往peripheral都携带这个Access Address吗？

<details>
<summary>Deep thinking completed (took 8 seconds)</summary>

用户是在追问BLE空口抓包里CONNECT_IND的Access Address位置，以及建连后双向数据信道包是否都用同一个AA。需要先搜Wireshark中CONNECT_IND的btle字段路径、Access Address在LL包/Packet／LLData里的位置，再核实BLE规范里数据信道包前导后Access Address的使用规则、主从收发是否共用同一条连接AA、以及广播AA与连接AA的区别。回答时要避免只说“在详情里”，要给出Wireshark展开路径和过滤定位方法；同时说明AA标识连接而非方向，peripheral→central和central→peripheral在同一连接通常用同一AA，除非是独立新连接、CIS/BIS等不同类型链路；还要提示若没抓到CONNECT_IND，后续数据信道包即使存在也无法从该抓包反推AA，需要靠sniffer从建连参数同步。

- 1. nordic蓝牙BLE配对第一次抓包
- 2. The Bluetooth Low Energy primer  Bluetooth Technology Website
- 3. 5.BLE---报文 - CSDN
- 4. How to Capture BLE Packets with nRF Sniffer and Wireshark
- 5. Bluetooth Core Specification
- 6. BLE 从广播到 ACL 连接——时序､空口与 Spec 对照 - CSDN
- 7. 深入BLE低功耗蓝牙
- 8. 从零实现BLE协议栈(3-1)连接契约:CONNECT_IND参数解析
- 9. @嵌入式系统资料:BLE Core 4... - 腾讯网
- 10. BLE Link layer tutorial – slave latency and supervision timeout
- 11. 蓝牙学习系列(五):BLE 连接建立过程详解 - CSDN
- 12. BLE 协议栈分层详解:物理层链路层状态机跳频与设备地址
- 13. BLE LL层数据结构分析——抓包分析 - CSDN
- 14. 亚马逊云科技技术品牌专区 - CSDN
- 15. 认识BLE5协议栈[八]--链路层

</details>

在 BLE 空口里，CONNECT_IND 的 Access Address 要分“外层包头的 AA”和“LLData 里的连接 AA”两层看，很多人卡在这里。

## 一、CONNECT_IND 里 AA 在哪

CONNECT_IND 发在广播信道（37/38/39），所以它**整个空口包外层**的 Access Address 是广播固定值：

- 外层 Access Address：0x8E89BED6（所有 ADV/SCAN/CONNECT_IND 都一样）

真正的“这条连接以后用什么 AA”放在 PDU payload 的 LLData 第一个字段：

- Payload 结构：InitA（中央地址 6B）＋ AdvA（外设地址 6B）＋ LLData（22B）

- LLData 第一个 4 字节就是 AA，后面依次是 CRCInit(3)、WinSize(1)、WinOffset(2)、Interval(2)、Latency(2)、Timeout(2)、ChM(5)、Hop+SCA(1)

规范原文：CONNECT_IND/AUX_CONNECT_REQ 的 LLData 中 AA 字段放“该 ACL 连接的 Access Address”，由链路层按随机规则生成。

## 二、Wireshark 里怎么点出来

选一条 CONNECT_IND（可用 btle.advertising_header.pdu_type == 0x05 或老版 btle.pdu_type == 5 定位），中间面板展开：

```Pure Text
Bluetooth Low Energy Link Layer
  Access Address: 0x8e89bed6        ← 外层广播AA，别用这个过滤数据信道
  Packet Header
    PDU Type: CONNECT_IND (0x05)
  Initiator Address: xx:xx:xx:xx:xx:xx   ← 中央
  Advertising Address: yy:yy:yy:yy:yy:yy  ← 外设
  Link Layer Data / LLData
    Access Address: 0x9925cfbf     ← 连接AA，后续数据信道用这个
    CRC Init: ...
    Window Size / Offset
    Interval / Latency / Timeout
    Channel Map
    Hop / SCA
```

nRF Sniffer 抓到的 CONNECT_IND 示例就是这样：外层 Access Address: 0x8e89bed6，LLData 里 Access Address: 0x5e9cde29，后续包 Source/Destination 显示 Central_0x5e9cde29/Peripheral_0x5e9cde29。

> 小坑：如果你在 CONNECT_IND 上直接复制“Access Address”，可能复制到外层的 0x8E89BED6，过滤数据信道必然空。要往 LLData 里再点一层。

## 三、建连后是不是所有包都带这个 AA

是，同一条传统 ACL 连接：

- 中央→外设、外设→中央，数据信道包外层 Access Address 都用 CONNECT_IND/LLData 里那个 AA

- 包括：LL 空包、LL 控制（FEATURE/VER/ENC/UPDATE/TERMINATE 等）、L2CAP、ATT/GATT、SMP，全带同一个 AA

- AA 标识“连接/链路”，不区分方向；方向靠后续 LL header、以及 Wireshark 的 Source/Destination（nRF 会标 Central_0x… / Peripheral_0x…）判断

广播阶段不用它；CONNECT_IND 本身也不用它（用 0x8E89BED6）；从 CONNECT_IND 之后的第一个数据信道包开始用。

## 四、哪些情况“不是同一个 AA”

- 重新建连：中央再次发 CONNECT_IND，会重新随机分配 AA，旧连接 AA 作废

- 扩展广播建连：用 AUX_CONNECT_REQ，AA 同样在 LLData 里，不在传统 CONNECT_IND

- 周期广播/Periodic：SyncInfo 里带独立 AA

- CIS（LE Audio 等）：由建立 CIS 的 LL 控制分配独立 AA，不和 ACL 共用

- BIS/BIG 广播音频：有 Seed AA 并派生各 BIS AA

- 不同 ACL 连接：各自不同 AA，哪怕同一个中央连两个外设，也是两个 AA

也就是“一个 ACL 会话＝一个 AA；跨会话/跨类型链路不共用”。

## 五、配合过滤的最稳做法

1.先找建连包并确认真实连接 AA：

```text
btle.advertising_header.pdu_type == 0x05
# 或老版
btle.pdu_type == 5
```

2.点开 LLData→Access Address 抄值（比如 0x9925cfbf）

3.跟整条连接：

```text
btle.access_address == 0x9925cfbf
```

4.只跟某方向可加 nRF/协议方向（nRF 用 Source/Destination 别名不一定可过滤，标准用 AA 即可；要分主从可结合包内容）：

```text
btle.access_address == 0x9925cfbf && btle.data_header.llid == 0x03   # 仅LL控制
btle.access_address == 0x9925cfbf && btatt                            # 仅GATT
```

如果 btle.access_address == 0x9925cfbf 一直空，而 btle.access_address == 0x8e89bed6 有结果，基本就是：要么 0x9925cfbf 不是本文件里 CONNECT_IND 的 LLData AA，要么 sniffer 没跟上 CONNECT_IND 所以后续数据信道没被解析出来。

要不要我按 nRF52840 抓包界面给你列一个“从 CONNECT_IND 复制 AA→建显示过滤器按钮”的点击路径？

---

**问：** 如何过滤蓝牙BLE终止连接包？

<details>
<summary>Deep thinking completed (took 7 seconds)</summary>

用户问Wireshark里如何过滤蓝牙BLE终止连接包。终止连接在BLE里有两层：链路层LL TERMINATE_IND（opcode 0x02的LL控制PDU，携带错误码/原因）和更上层的HCI Disconnect Complete事件（本机HCI日志）。空口抓包主要看LL控制。需要搜索确认Wireshark字段名，因为不同版本可能用btle.control_opcode、btle.llctrl.opcode、btle.ll_terminate_ind.reason、btle.terminate_reason等。还要提CONNECT_IND之后用access_address跟某条连接，以及HCI用bthci_evt.disconnect_complete / bthci_evt.code==0x05等。先搜一下当前Wireshark BLE LL terminate字段名，避免给错。

- 1. How to Debug BLE Connection Failures with a Sniffer
- 2. BLE协议分析仪实战:用nRF52840 Dongle和Wireshark定位蓝牙连接疑难杂症 - CSDN
- 3. 蓝牙HCI日志:移动端开发的显微镜
- 4. How to Capture BLE Packets with nRF Sniffer and Wireshark
- 5. WiresharkBLE dongle抓包log过滤器设置 - CSDN
- 6. 使用 Wireshark 分析 Android 蓝牙 HCI 日志:BLE 开发者常用过滤器与技巧 - CSDN
- 7. epan/dissectors/packet-btle.c · a6ea26a131555992518aef9b031470790fb113b6 · external-tools / wireshark · GitLab
- 8. 蓝牙协议分析(7)_BLE连接有关的技术分析
- 9. Using Wireshark for Bluetooth Analysis
- 10. BT 4.2 低功耗蓝牙LE linklayer层解析 - 爱码网
- 11. 蓝牙 Ellisys和Wireshark关键字过滤
- 12. 蓝牙相关学习:4.2.BLE空口包结构 - PDU - CSDN
- 13. Btsnoop_hci Log: Different Ways to Export and View the Logs - GeekChamp
- 14. BLE链路层(LL)数据结构详解:从广播包到数据包的完整解析(附PDU类型对比表) - CSDN
- 15. Display Filter Reference: Bluetooth HCI Event

</details>

BLE 终止连接分两层过滤：空口看链路层 LL 控制包，本机 HCI 日志看 Disconnection Complete 事件。

## 一、空口抓包：LL_TERMINATE_IND

链路层控制包 LLID=0b11，TERMINATE 的 opcode=0x02，payload 里带 1 字节错误原因。

**所有终止包：**

```text
btle.control_opcode == 0x02
```

nRF 排障资料也直接用这条定位“连接异常掉线”。

**按某条连接跟：**

```text
btle.access_address == 0x9925cfbf && btle.control_opcode == 0x02
```

**按终止原因码筛：**

```text
btle.control_opcode == 0x02 && btle.terminate_reason == 0x08     # supervision timeout 超时断连
btle.control_opcode == 0x02 && btle.terminate_reason == 0x13     # remote user terminated 对端主动断开
btle.control_opcode == 0x02 && btle.terminate_reason == 0x05     # authentication failure
btle.control_opcode == 0x02 && btle.terminate_reason == 0x16     # instant passed 参数更新失效
```

常见原因码：0x08 监督超时、0x13 对端用户/应用断开、0x05 认证失败、0x06 缺密钥、0x16 Instant Passed、0x3B 不可接受连接参数。

> 字段名兜底：部分版本/插件把控制 opcode 放在 btle.link_layer.control_opcode、btle.llctrl.opcode，原因放在 btle.llctrl.terminate.reason 或 btle.terminate_reason。最稳做法：包列表点中一条 LL_TERMINATE_IND → 中间面板展开 Bluetooth Low Energy Link Layer → Control → 对 Opcode/Error Code 行右键 **Apply as Filter → Selected**。

补充相关“类终止/拒绝”控制包，排问题时常一起看：

```text
btle.control_opcode == 0x02   # LL_TERMINATE_IND
btle.control_opcode == 0x07   # LL_UNKNOWN_RSP
btle.control_opcode == 0x0d   # LL_REJECT_IND
btle.control_opcode == 0x11   # LL_REJECT_IND_EXT
btle.control_opcode == 0x22   # LL_CIS_TERMINATE_IND（LE Audio CIS 专用）
```

opcode 完整表可对照 Wireshark btle 解析源码。

## 二、本机 HCI 日志（Android btsnooz / Linux btmon/hcidump / Windows ETW）

空口没有 MAC/AA 概念时用 HCI 事件：

```text
bthci_evt.code == 0x05          # Disconnection Complete，所有BLE/经典断连都进这里
bthci_evt.disconnect_reason == 0x08   # 按HCI原因筛，字段名随版本可能不同
```

配合 LE 连接生命周期：

```text
bthci_evt.le_meta_subevent == 0x01   # LE Connection Complete 建连
bthci_evt.le_meta_subevent == 0x03   # LE Connection Update Complete 参数更新
bthci_evt.code == 0x05               # 断连
```

多设备按连接句柄跟：

```text
bthci_evt.connection_handle == 0x0001 && bthci_evt.code == 0x05
```

HCI 断连事件与过滤参考 Wireshark HCI 分析资料。

## 三、实操排查“为什么断”

1.空口先全量定位终止包：

```text
btle.control_opcode == 0x02
```

2.没有 TERMINATE 但连接消失 → 可能 sniffer 没跟上跳频、或纯超时没发终止包；看 CONNECT_IND 里的 supervision timeout，再对比最后一次数据包到“消失”的时间差。

3.有 TERMINATE 看 reason：0x08 多为主从某侧丢包/干扰；0x13 多为 App 或主机主动关；0x05/0x06 多为配对加密问题；0x16 多为连接参数/信道更新 instant 没对齐。

4.想分“谁发的终止”：LL_TERMINATE_IND 不显式带主从标志，靠包方向/AA 所属连接判断；nRF Sniffer 的 Source/Destination 列（Central_0x…/Peripheral_0x…）可辅助。

如果你把 Wireshark 版本和一条 LL_TERMINATE_IND 的“Control”展开贴出来，可以直接按你环境给不报红的字段名。

---


# 如何区分正常的连接终止和异常断连？有哪些关键指标？
<details>
<summary>Deep thinking completed (took 6 seconds)</summary>

好的，用户问的是如何区分正常的连接终止和异常断连，以及有哪些关键指标。这个问题很专业，说明用户对BLE协议有一定了解，可能正在调试蓝牙连接稳定性问题，或者在做产品开发时需要分析连接行为。

嗯，回顾之前的对话，用户一直在深入询问Wireshark过滤BLE包的各种细节，从广播、连接请求、服务发现到MTU协商、终止连接包。现在他聚焦在“终止”这个环节，并且想知道怎么判断是正常还是异常。他的深层需求不仅仅是知道过滤字段，而是想通过抓包数据来诊断连接问题的根因，比如是软件主动关闭、信号干扰导致超时，还是协议栈内部错误。

我需要从几个层面来构建回答。首先，最直接的依据是空口LL层的终止原因码（Terminate Reason），这是协议定义的。正常终止通常是0x13（远程用户终止）或0x16（连接参数更新完成后的合理终止）。异常则包括0x08（监督超时，最常见）、0x05/0x06（认证/密钥问题）、0x3B（参数不合理）等。

其次，光看原因码还不够，还要看终止是由哪一方发起的。可以通过Wireshark里的Source/Destination（比如nRF Sniffer会标注Central/Peripheral）来判断是谁主动发了LL_TERMINATE_IND。主动发起方通常是正常关闭的那一方。

第三，结合上下文时序很重要。比如，连接刚建立几秒就断，大概率是异常（如参数协商失败、配对失败）。如果是在空闲期长时间无数据交换后断，可能是监督超时。如果是在执行GATT读写操作后立即断，可能是应用层逻辑或错误处理导致的异常。

第四，一些辅助指标也能帮助判断。比如连接参数（Connection Interval, Supervision Timeout）的设置是否合理；是否频繁出现CRC错误或重传；以及HCI日志层面的Disconnection Complete事件的Reason字段，与空口原因码对应。

最后，用户可能需要一个清晰的判断流程图或总结表格，方便他对照抓包数据快速定位。考虑到他之前的问题都很技术化，我应该给出具体的Wireshark过滤表达式和字段名，让他能直接上手分析。

总之，我的回答需要结构清晰，从协议层原因码、方向、时序、上下文等多个维度给出可操作的判断方法和关键指标，并提醒常见的陷阱（比如HCI日志和空口字段名的差异）。

</details>

区分 BLE 连接的正常终止与异常断连，核心看三个层面：**LL 终止原因码、终止发起方、以及终止前后的上下文**。下面逐一展开，附 Wireshark 过滤方式。

---

## 一、看 LL_TERMINATE_IND 的原因码（最直接）

空口终止包自带 1 字节原因码，这是协议层给出的最权威判断依据。

| 原因码 | 含义 | 分类 |
| --- | --- | --- |
| 0x13（19） | Remote User Terminated Connection | ✅ **正常**：对端应用/协议栈主动调用断开 API |
| 0x16（22） | Instant Passed | ⚠️ 多数算正常：连接参数/信道更新过程中 instant 未对齐，属协议机制内的正常终止 |
| 0x08（8） | Connection Timeout / Supervision Timeout | ❌ **异常**：对端在 supervision timeout 内没收到任何包，认为连接丢失 |
| 0x05（5） | Authentication Failure | ❌ 异常：配对/加密失败，如密钥缺失、MIC 校验失败 |
| 0x06（6） | Pin or Key Missing | ❌ 异常：存储的密钥丢失或不匹配 |
| 0x3B（59） | Unacceptable Connection Parameters | ❌ 异常：连接参数（Interval/Latency/Timeout）超出对端允许范围 |
| 0x22（34） | LMP Response Timeout / LL Response Timeout | ❌ 异常：等待 LL 控制响应超时 |
| 0x28（40） | Instant Passed (Controller内部) | ⚠️ 与 0x16 类似，多数正常 |
| 0x00–0x04 | 保留/成功 | 极少出现在终止中，通常不用 |

**Wireshark 过滤：**

```text
btle.control_opcode == 0x02 && btle.terminate_reason == 0x13   # 正常
btle.control_opcode == 0x02 && btle.terminate_reason == 0x08   # 异常：超时
btle.control_opcode == 0x02 && btle.terminate_reason == 0x05   # 异常：认证失败
```

> 字段名兜底：btle.terminate_reason 在某些版本/插件中可能叫 btle.llctrl.terminate.reason 或 btle.link_layer.control.terminate_reason。右键应用最稳。

---

## 二、看终止是由谁发起的

正常终止通常由**应用层/主机**发起（GAP 角色主动断开）；异常终止往往由**控制器/链路层**因超时或错误触发。

**Wireshark 怎么看方向：**

- nRF Sniffer 在包列表的 Source/Destination 列会标注 Central_0x... 或 Peripheral_0x...

- 标准空口包没有“主/从”字段，但可以从 LL_TERMINATE_IND 前后上下文推断：

  - 如果之前该方向有大量正常 ATT 交互，突然发 TERMINATE → 可能是应用层主动断开

  - 如果之前长时间无包（接近 supervision timeout），然后某侧发 TERMINATE with reason 0x08 → 控制器触发的异常超时

**经验规律：**

- **中央主动发** reason=0x13：多为用户/App 正常关闭连接（如 App 退出、用户点断开）

- **外设主动发** reason=0x13：也可能是正常，但较少见（外设通常被动等待中央断）

- **任一侧发** reason=0x08：一定是异常，说明对端已经“失联”超过 supervision timeout

- **任一侧发** reason=0x05/0x06：异常，加密/配对阶段出了问题

---

## 三、看终止前的上下文时序

| 场景 | 判断 |
| --- | --- |
| 刚连接几秒就断（reason=0x08 或 0x3B） | 异常：参数协商失败、信号太弱、对端拒绝连接参数 |
| 正常交互一段时间后断（reason=0x13） | 正常：应用任务完成或用户退出 |
| 长时间无数据后断（reason=0x08） | 异常：设备离开范围、电池耗尽、射频干扰 |
| 在配对/加密过程中断（reason=0x05/0x06） | 异常：密钥不匹配、配对失败 |
| 在连接参数更新过程中断（reason=0x16） | 正常机制：instant 未对齐，重试即可 |
| 断连前有大量 CRC 错误或重传 | 异常：射频环境差，链路质量恶化导致超时 |

**Wireshark 辅助过滤：**

```text
# 看终止前最后几秒的包
btle.access_address == 0x9925cfbf && frame.time_relative > (终止包时间 - 3)
# 看 CRC 错误率
btle.access_address == 0x9925cfbf && btle.crc_ok == 0
# 看连接持续时间
btle.access_address == 0x9925cfbf && btle.control_opcode == 0x02
# 对比第一个 CONNECT_IND 的时间戳
```

---

## 四、看 HCI 日志（本机抓包时）

如果抓的是 Android btsnooz / Linux btmon / Windows ETW，用 HCI Disconnection Complete 事件：

```text
bthci_evt.code == 0x05
```

展开后看 Reason 字段，值与空口原因码一致（0x13=正常、0x08=超时等）。

**HCI 额外优势：** 可以看到是本机主动断（Host 发 HCI_Disconnect 命令）还是对端断（Controller 上报 Disconnection Complete 事件）。过滤本机主动断：

```text
bthci_cmd.opcode == 0x0406   # HCI_Disconnect 命令
```

---

## 五、总结：快速判断流程

```
graph TD
    A[抓到 LL_TERMINATE_IND] --> B{原因码?}
    B -->|0x13| C[正常终止]
    B -->|0x16| D[正常/参数更新失败]
    B -->|0x08| E[异常: 监督超时]
    B -->|0x05/0x06| F[异常: 配对/加密失败]
    B -->|0x3B| G[异常: 参数被拒]
    B -->|其他| H[视具体码判断]
    
    C --> I{谁发的?}
    I -->|中央| J[App/用户主动断开]
    I -->|外设| K[外设主动断开, 少见]
    
    E --> L{终止前有CRC错误?}
    L -->|是| M[射频干扰/距离远]
    L -->|否| N[设备断电/死机]
    
    F --> O{发生在配对阶段?}
    O -->|是| P[密钥不匹配/IO能力冲突]
    O -->|否| Q[加密后MIC校验失败]
```

---

## 六、实战排错常用组合

```text
# 所有异常断连（排除正常原因码）
btle.control_opcode == 0x02 && btle.terminate_reason != 0x13 && btle.terminate_reason != 0x16

# 某条连接上的超时断连
btle.access_address == 0x9925cfbf && btle.control_opcode == 0x02 && btle.terminate_reason == 0x08

# 断连前最后 5 个数据包（看有无异常）
btle.access_address == 0x9925cfbf && frame.number >= (断连包帧号 - 5) && frame.number <= 断连包帧号

# 看整条连接生命周期（建连→断连）
btle.access_address == 0x9925cfbf
```

如果你能贴出一条 LL_TERMINATE_IND 的完整展开（含 Opcode、Terminate Reason、以及前后几个数据包），我可以帮你判断是正常还是异常，并指出可能的根因。



# wireshark过滤 低功耗蓝牙BLE 空口包
BLE 空口包在 Wireshark 里主要用 **`btle`** 协议族过滤。
先确认你的抓包来源：如果是 **nRF Sniffer / Ubertooth / Ellisys**，用 `btle.*`；如果是 Linux `btmon`/HCI snoop 导出，看到的是 `bthci_*`，不是真正空口包。

### 常用显示过滤器

| 目标 | 过滤器 |
|---|---|
| 只看 BLE 空口包 | `btle` |
| 只看广播包 | `btle.advertising_header.pdu_type < 4` |
| 只看 ADV_IND | `btle.advertising_header.pdu_type == 0` |
| 只看连接请求 | `btle.ll.control_opcode == 0x05` |
| 只看某设备 | `bluetooth.addr == AA:BB:CC:DD:EE:FF` |
| 只看 ATT/GATT 数据 | `btatt` |
| 只看 SMP 配对 | `btsmp` |
| 排除空 PDU | `!( _ws.col.info == "Empty PDU")` |
| 只看主机→从机方向 | `bthci_acl.direction == 0x00` |

### 实用组合

```text
btle && bluetooth.addr == AA:BB:CC:DD:EE:FF
```

```text
btle.advertising_header.pdu_type == 0 && btle.advertising_data contains "你的设备名"
```

```text
btle.ll.control_opcode == 0x05 || btle.ll.control_opcode == 0x01
```

```text
btatt.opcode == 0x12 || btatt.opcode == 0x1b
```

### 如果是 nRF Sniffer

可以在接口选项里直接选：

- **Only advertising packets**
- **Only legacy advertising packets**
- **Scan and follow devices on LE Coded PHY**

也可以在捕获过滤器里按信号强度过滤，例如：

```text
rssi >= -70
```

### 如果抓不到包
优先检查三点：  
1. 硬件是否真的是 BLE 嗅探器，普通蓝牙适配器通常不能直接抓空口包。
2. Wireshark 是否选择了正确的捕获接口，例如 `nRF Sniffer for Bluetooth LE`。
3. 加密连接后的数据如果没有 LTK，只能看到密文，无法直接看到 ATT 明文。

如果你贴一段 Wireshark 里的包列表或 `btle` 字段截图，我可以帮你把过滤表达式精确到具体阶段，比如广播、连接、SMP 配对或 ATT 读写。

---

# 如何过滤蓝牙BLE终止连接包？

BLE 空口里"终止连接"的包是链路层控制 PDU：**LL_TERMINATE_IND**。

### 直接过滤表达式

```text
btle.ll.control_opcode == 0x02
```

或者：

```text
btle.ll.control_opcode == LL_TERMINATE_IND
```

如果你的 Wireshark 版本支持按名称匹配，写 `LL_TERMINATE_IND` 会更直观；不支持时就写 `0x02`。

### 常用组合写法

只看某个连接的终止包：

```text
btle.ll.control_opcode == 0x02 && btle.access_address == 0x12345678
```

按设备地址过滤：

```text
btle.ll.control_opcode == 0x02 && bluetooth.addr == AA:BB:CC:DD:EE:FF
```

同时看连接建立和断开：

```text
btle.ll.control_opcode == 0x05 || btle.ll.control_opcode == 0x02
```

### 注意点

- `0x05` 是 **LL_CONNECT_REQ / CONNECTION_IND**，不是断开。
- `LL_TERMINATE_IND` 是链路层包，通常出现在连接状态下，不是广播包。
- 如果连接已加密且没有 LTK，空口抓包能看到 `LL_TERMINATE_IND`，但前面的 ATT/GATT 数据可能仍是密文。
- 如果你抓的是 HCI log，而不是空口包，可能看到的是 `HCI LE Meta Event: Disconnection Complete`，那种情况不能直接用 `btle.ll.control_opcode` 过滤。

需要我帮你整理一份 BLE 链路层控制 PDU 操作码对照表吗？方便你随时查其他操作码对应的含义。

---

# wireshark4.6.9输btle.ll.control_opcode == 0x05 || btle.ll.control_opcode == 0x02过滤，语法报错

大概率不是 `||` 本身的问题，而是 **`btle.ll.control_opcode` 这个字段在你当前的抓包/版本里不存在**。Wireshark 显示过滤器一旦遇到无效字段名，整行都会报红。

### 先试这几种替代写法

```text
btle.ll.opcode == 0x05 || btle.ll.opcode == 0x02
```

```text
btle.control_opcode == 0x05 || btle.control_opcode == 0x02
```

```text
btle.opcode == 0x05 || btle.opcode == 0x02
```

```text
btle.ll_control_opcode == 0x05 || btle.ll_control_opcode == 0x02
```

如果只想看断开连接：

```text
btle.ll.opcode == 0x02
```

其中：

| 值 | 含义 |
|---|---|
| `0x05` | LL_CONNECT_REQ / CONNECTION_IND |
| `0x02` | LL_TERMINATE_IND |

### 确认字段名的办法

在 Wireshark 里随便点一个 BLE 链路层包，展开到 **Link Layer Control PDU / Control Opcode** 那个字段，右键选择 **Apply as Filter → Selected**，Wireshark 会自动生成当前版本真正可用的字段名。

### 如果仍然报红

常见原因有三个：

1. 抓的不是 BLE 空口包，而是 HCI log，此时没有 `btle.ll.*` 字段。
2. 包没有被识别为 `btle` 协议，可以在过滤器里先只输入 `btle`，看是否能匹配到包。
3. 版本里该字段改名了，所以必须用右键生成的字段名。

如果你把 Wireshark 里那条红色报错提示，或者一个 BLE 包的协议树截图发出来，我可以帮你把字段名精确改成当前版本可用的形式。

---

# btle.control_opcode == 0x02能正确过滤连接断开包，但btle.control_opcode == 0x05并不能过滤连接建立包，为什么？

原因在于：**`0x05` 不是"连接建立包"的 PDU 类型，而是链路层控制 PDU 里的一个 opcode**；而真正的连接建立包 `CONNECT_IND` 属于广播信道 PDU，不在 `btle.control_opcode` 这个字段里。

### 为什么 `0x02` 能命中，`0x05` 不能

`btle.control_opcode` 只出现在 **数据信道的 LL Control PDU** 里。

| 值 | 字段含义 | 是否属于 control_opcode |
|---|---|---|
| `0x02` | `LL_TERMINATE_IND` | 是，所以能过滤到 |
| `0x05` | `LL_START_ENC_REQ` | 是，但它是加密启动请求，不是连接建立 |

也就是说，`btle.control_opcode == 0x05` 过滤到的不是连接建立，而是链路层加密握手里的 **LL_START_ENC_REQ**。

### 连接建立包应该这样过滤

BLE 的连接建立包是 **CONNECT_IND**，它的类型在广播 PDU 头里：

```text
btle.advertising_header.pdu_type == 5
```

或者更直观地用 Info 列过滤：

```text
frame contains "CONNECT_IND"
```

更稳妥的做法是：在 Wireshark 里点中一个 `CONNECT_IND` 包，展开到：

```text
Bluetooth Low Energy Link Layer -> Advertising Channel PDU -> Advertising Header -> Type
```

然后右键该字段，选择 **Apply as Filter -> Selected**，这样能得到当前 Wireshark 版本真正可用的字段名。

### 推荐组合

同时看连接建立和连接断开：

```text
btle.advertising_header.pdu_type == 5 || btle.control_opcode == 0x02
```

如果还想确认连接建立后的第一个控制过程，可以加：

```text
btle.control_opcode == 0x0C
```

`0x0C` 通常是 `LL_VERSION_IND`，很多连接建立后会出现。

你抓的是空口包还是HCI log？如果是HCI，连接建立包可能走的是HCI LE Meta Event: Connection Complete，过滤方式会不一样。
