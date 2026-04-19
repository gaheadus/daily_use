# BT

## UUID
UUID分配：Assigned_Numbers Bluetooth® Document.pdf  

• 0x180x 开头(0x1800–0x26FF) → 只能当 Service UUID  
• 0x2Axx 开头(0x2A00–0x7FFF) → 只能当 Characteristic UUID  
• 0x29xx 开头(0x2900–0x29FF) → 只能当 Descriptor UUID  


### 服务UUID  
##### 服务通用UUID  

|16-bit	| 服务英文名称 | 中文场景 |
|--------|--------------|----------|
| 0x1800 | Generic Access | 必含，设备名、外观、连接参数 |
| 0x1801 | Generic Attribute | 必含，Service Changed |
| 0x180A | Device Information | 厂商字符串/版本号 |
| 0x180F | Battery Service | 电池电量，手环/键鼠必备 |
基本上做 BLE 从机，都得加上 0x1800 / 0x1801 / 0x180A / 0x180F 四件套。

##### 传感器与健康（手环、手表、医疗）  

| 16-bit | 服务英文名称 | 中文场景 |
|---|---|---|
| 0x180D | Heart Rate | 心率 |
| 0x1809 | Health Thermometer | 体温计 |
| 0x1810 | Blood Pressure | 血压计 |
| 0x1818 | Cycling Power | 骑行功率计 |
| 0x1816 | Cycling Speed & Cadence | 踏频/速度 |
| 0x1814 | Running Speed & Cadence | 跑步速度 |
| 0x1843 | Pulse Oximeter | 血氧仪 |
| 0x183E | Weight Scale | 体重秤 |
| 0x183F | Location & Navigation | 自行车码表 |
| 0x181B | Environmental Sensing | 温湿度/气压/光照 |
| 0x183B | Binary Sensor | 门窗/烟雾开关量 |

做传感器需要用到 0x180D / 0x1809 / 0x1810 / 0x1843 / 0x183E / 0x181B 等上面这些。


##### HID & 音频 & OTA  

| 16-bit | 服务英文名称 | 中文场景 |
|---|---|---|
| 0x1812 | Human Interface Device | 键盘/鼠标/遥控 |
| 0x1813 | Scan Parameters | 扫描窗口参数（配合 HID） |
| 0x1811 | Alert Notification Service | 来电/短信提醒 |
| 0x184E | Common Audio | LE Audio 统一服务 |
| 0x181E | Bond Management | 删除配对键 |
| 0x181F | Immediate Alert | 防丢器“响铃” |
| 0x1825 | Object Transfer Service | OTA/文件传输 |


##### 手机/PC 常用后台服务  

| 16-bit | 服务英文名称 | 中文场景 |
|---|---|---|
| 0x1802 | Immediate Alert | 防丢响铃 |
| 0x1803 | Link Loss | 断开报警 |
| 0x1804 | Tx Power | 发射功率 |
| 0x1805 | Current Time Service | 同步系统时间 |
| 0x1806 | Reference Time Update | 网络校时 |
| 0x1807 | Next DST Change | 夏令时 |
| 0x1808 | Glucose | 血糖仪 |
| 0x1815 | Automation IO | 通用 GPIO 控制 |
| 0x1817 | Position Quality | 定位精度 |
| 0x1819 | Location & Speed | 位置速度 |
| 0x183A | Media Control | 媒体播放控制 |
| 0x183C | Mesh Provisioning | Mesh 配网 |
| 0x183D | Mesh Proxy | Mesh 代理 |


### 特征UUID  
0x2Axx (0x2A00 – 0x2AFF) 区间只能当 Characteristic UUID ， 同上面一样，反过来并不是必须用这个区间来做 Characteristic UUID。

##### 通用与设备信息

| UUID | 名称 | 典型用途 |
|---|---|---|
| 0x2A00 | Device Name | 设备名称，Generic Access 必含 |
| 0x2A01 | Appearance | 外观图标（键盘/鼠标/温度计…） |
| 0x2A04 | Peripheral Preferred Connection Parameters | PPCP，广播里常用 |
| 0x2A05 | Service Changed | Generic Attribute 必含，OTA 必备 |
| 0x2A19 | Battery Level | 电池百分比，0-100 |
| 0x2A23 | System ID | 8 字节，OUI+Vendor 自编 |
| 0x2A24 | Model Number String | 型号 |
| 0x2A25 | Serial Number String | 序列号 |
| 0x2A26 | Firmware Revision String | FW 版本 |
| 0x2A27 | Hardware Revision String | HW 版本 |
| 0x2A28 | Software Revision String | SW 版本 |
| 0x2A29 | Manufacturer Name String | 厂商名 |

##### 传感器与运动类（手环/手表/温度计）

| UUID | 名称（EN） | 中文说明 / 典型用途 |
|---|---|---|
| 0x2A37 | Heart Rate Measurement | 心率测量值，一次性通知（uint8 flags + 心率 + 能量等） |
| 0x2A38 | Body Sensor Location | 身体传感器位置（0-6：胸、腕、指、手、耳、足、腰） |
| 0x2A39 | Heart Rate Control Point | 心率控制点，写 0x01 可重置能量消耗累计 |
| 0x2A1C | Temperature Measurement | 温度测量结果（float °C + 时间戳可选） |
| 0x2A1D | Temperature Type | 测温位置类型（腋下、体表、直肠等，枚举 0-9） |
| 0x2A1E | Intermediate Temperature | 中间温度值，连续测温时周期性通知 |
| 0x2A6E | Pressure | 气压/压力值（uint32，分辨率 0.1 Pa） |
| 0x2A6F | Humidity | 相对湿度（uint16，分辨率 0.01 %） |
| 0x2A6D | Rainfall | 降雨量（uint16，分辨率 0.1 mm） |
| 0x2A5B | CSC Measurement | 骑行/步速综合测量（轮转速 + 曲柄转数 + 时间戳） |
| 0x2A5C | CSC Feature | CSC 支持特性位域（轮速、曲柄、多传感等） |
| 0x2A5D | Sensor Location | 传感器安装位置（曲柄、轮毂、鞋、胸等 0-15） |
| 0x2A63 | Cycling Power Measurement | 骑行功率实时测量（功率 W + 可选踏频、扭矩等） |
| 0x2A64 | Cycling Power Vector | 功率矢量（各踏点扭矩、角度等数组，用于高阶骑行分析） |
| 0x2A65 | Cycling Power Feature | 功率计功能位域（扭矩源、矢量、多链轮等） |
| 0x2A6C | Elevation | 海拔高度（uint24，分辨率 0.1 m） |
| 0x2A6A | Battery Power State | 电池功率状态（位域：是否充电、电量充足、低电、临界等） |


##### 电池与电源

| UUID | 名称（EN） | 中文说明 / 典型用途 |
|---|---|---|
| 0x2A19 | Battery Level | 电池剩余电量百分比（uint8，0–100）。最常用，单电池场景一条 Characteristic 即可。 |
| 0x2A1A | Battery Power State | 电池“功率/状态”位域：充电中/放电中/充满/低电/临界/故障等；与 0x2A6A 同义，二选一。 |
| 0x2A1B | Battery Group Info | 电池组信息：组内电池数量 + 每个电池的 0/1 状态位图；支持多电池设备一次性汇报。 |

HID 与 DFU（键鼠、OTA）

| UUID | 名称（EN） | 中文说明 / 典型用途 |
|---|---|---|
| 0x2A22 | Boot Keyboard Input Report | 8 字节键盘输入（BIOS 阶段），位图+修饰键。 |
| 0x2A32 | Boot Mouse Input Report | 3 字节鼠标输入（按键+XY 位移）。 |
| 0x2A33 | Boot Mouse Output Report | 1 字节主机→鼠标输出（LED 同步）。 |
| 0x2A4A | HID Information | HID 版本与特性标志（1 字节 country code + 2 字节 flags）。 |
| 0x2A4B | HID Control Point | 主机写 0x00/0x01 让设备 suspend/resume；无响应，纯控制。 |
| 0x2A4C | HID Protocol Mode | 切换 Boot Protocol(0x00) 与 Report Protocol(0x01)。 |
| 0x2A4D | Report（HID） | 通用输入/输出/特征报告，日常键鼠数据就靠它。 |
| 0x2A4E | Report Map | HID 用途描述符，主机先读它才能解析后续 Report。 |
| 0x2AE9 | Object Action Control Point | DFU 控制点：执行 Create/Execute/Verify/CRC/Abort 等动作，写命令+返回响应。 |
| 0x2AEB | Object ID | DFU 对象标识（uint32），例如镜像编号、Bank 号。 |
| 0x2AEC | Object Size（DFU） | DFU 对象总字节数（uint32），升级前主机先读。 |

##### 安全与配对

| UUID | 名称（EN） | 中文说明 / 典型用途 |
|---|---|---|
| 0x2A3D | Supported New Alert Category | 手机端支持的新增告警类型位图（邮件、短信、来电等 0-7 类）。 |
| 0x2A3E | Alert Category ID | 单条告警的类别编号（1 字节枚举）。 |
| 0x2A3F | Alert Category ID Bit Mask | 批量告警类别位掩码，每位对应 0x2A3E 的一个类别。 |
| 0x2A40 | Alert Level | 告警级别：无(0)、温和(1)、高(2)，用于立即提醒或震动。 |
| 0x2A41 | Alert Notification Control Point | 写命令控制：使能/禁能某类告警、立即清除未读计数等。 |
| 0x2A42 | Unread Alert Status | 未读计数器：类别 ID + 未读条数（uint8）。 |
| 0x2A43 | New Alert | 新增告警：类别 ID + 字符串内容（UTF-8），一次性通知。 |
| 0x2A4F | Scan Refresh | 扫描刷新：写 0x00 通知外设“可重新开始广播”，用于减小广播窗口。 |
| 0x2A31 | Scan Interval Window | 主机建议的扫描间隔与窗口（各 2 字节，单位 0.625 ms），外设可采纳以节电。 |
| 0x2A55 | Bond Management Control Point | 绑定管理控制点：删除指定绑定、删除所有绑定、清除密钥等，写命令+返回结果。 |
| 0x2A56 | Bond Management Feature | 绑定管理特性位域：支持删除单个/全部/授权列表等能力标志。 |

### 描述符UUID  
0x29xx 开头只能当 Descriptor UUID ，而且描述符 UUID 并不多。截至 Bluetooth v5.4，0x2900 ~ 0x290D 是当前已发布的标准描述符 UUID 。  
下面的比上面的记录多了变量名，是根据WCH CH585 示例工程中的定义来列举的：  

| 变量名（代码） | UUID | 标准名称（EN） | 简单用途（含必选提示） |
|---|---|---|---|
| charExtPropsUUID | 0x2900 | Characteristic Extended Properties | 扩展属性位；可选 |
| charUserDescUUID | 0x2901 | Characteristic User Description | 用户文字说明；可选 |
| clientCharCfgUUID | 0x2902 | Client Characteristic Configuration | 开/关通知或指示；通知/指示特征必备 |
| servCharCfgUUID | 0x2903 | Server Characteristic Configuration | 服务器端广播指示；极少用 |
| charFormatUUID | 0x2904 | Characteristic Presentation Format | 数值格式与单位；可选 |
| charAggFormatUUID | 0x2905 | Characteristic Aggregate Format | 组合多个格式；可选 |
| validRangeUUID | 0x2906 | Valid Range | 合法最小最大值；可选 |
| extReportRefUUID | 0x2907 | External Report Reference | 指向外部服务；HID 可选 |
| reportRefUUID | 0x2908 | Report Reference | Report ID 与类型；HID 可选 |


### 0x28XX 开头UUID  
0x28xx 一共只有 4 个（SIG 已全部分配完毕），它们是 GATT 的“骨架”UUID，永远不参与用户数据，只用来告诉客户端我这条属性是干什么的：这里是服务头 / 特征头 / 引用头。  

| 16-bit | 名字 | 在属性表里的作用 |
|---|---|---|
| 0x2800 | Primary Service | “一个主服务开始了” |
| 0x2801 | Secondary Service | “一个次级服务开始了”（极少用） |
| 0x2802 | Include | “这里包含另一个服务”（跨服务引用） |
| 0x2803 | Characteristic | “后面跟的是一条特征” |

### 备注
来源：https://blog.csdn.net/weixin_42328389/article/details/153262201  





