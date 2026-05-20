# 用法
•组合搜索：例如，查找包含 "ERROR" 但不包含 "Timeout" 的日志，搜索："ERROR" and not("Timeout")。  
支持括号分组：(error OR warning) AND server1  
•多条件匹配：查找数据库连接错误或认证失败的日志："database.*error" or "authentication.*failed"  


# 快捷键
ctrl+shift+1~9 ：	为选中文本添加颜色标签  

ctrl+shift+f ： 高级搜索，和ctrl+s一样  
ctrl+f      ： 快捷搜索，和 '或"一样(单引号/双引号)  

ctrl+t、ctrl+1、2、3 ：在标签页之间切换  

\[ 、] ： 跳转到上一个/下一个标记行  

ctrl+l	：快速跳转到指定行号  

f ：实时跟踪日志。按 f进入跟随模式，适合监控正在写入的日志文件。  


| 快捷键（Windows/Linux） | 说明 |
| --- | --- |
| 文件操作​ | |
| ctrl+o | 打开单个文件 |
| ctrl+shift+o | 打开对话框切换文件 |
| ctrl + t | 新建标签页（方便同时打开多个日志文件对比） |
| ctrl+w | 关闭当前标签页 |
| ctrl + tab | 在不同标签页之间切换 |
| ctrl+1、2、3 | 在不同标签页之间切换 |
| f5 | 重新加载当前文件 |
| 导航与搜索​ | |
| ctrl+g | 输入行号快速定位 |
| ctrl+f | 打开页内搜索框 |
| ctrl+s | 聚焦到搜索框并启用正则模式 |
| ctrl+shift+f | 高级搜索。和ctrl+s一样？ |
| f3 / shift+f3 | 查找下一个 / 查找上一个匹配项 |
| alt + up/down | 在匹配结果之间快速跳转 |
| n / N (shift+n) | 跳转到下一个匹配项 |
| \*或 . | 搜索当前选中文本的下一个出现位置。备注：\*其实是shift+8 |
| /或 , | 搜索当前选中文本的上一个出现位置 |
| '或 " | 在当前屏幕启动快速查找（向前/向后） |
| ctrl+l | 快速跳转到指定行号 |
| 标记与视图​ | |
| ctrl+m | 标记当前行 |
| m | 将选中行加入 Marks |
| 1/ 2/ 3 | 直接切换到 Marks and matches、Marks、Matches 窗口 |
| v | 循环切换过滤视图显示模式（Matches → Marks → Marks and Matches） |
| [ 、] | 跳转到上一个/下一个标记行 |
| +/ - | 增大/减小过滤窗口的尺寸 |
| f | 激活跟随模式（类似 tail -f），实时显示文件尾部。  **实时跟踪日志**：按 f进入跟随模式，适合监控正在写入的日志文件。 |
| alt+滚动 | 水平滚动 |
| shift+滚动 | 加速滚动 |
| 编辑与工具​ | |
| ctrl+c | 复制当前行内容 |
| ctrl+shift+s | 打开 Scratchpad 工具窗口 |
| ctrl+shift+1~9 | 为选中文本添加颜色标签 1~9 |
| ctrl+shift+0 | 移除选中文本的颜色标签 |
| ctrl+d | 循环应用颜色标签 |
| vim风格导航​ | |
| j | 向下移动一行 |
| k | 向上移动一行 |
| g | 跳转到文件第一行 |
| shift+g | 跳转到文件最后一行 |
| 其他 | |
| f6 | 将选中的日志行发送至 Scratchpad（临时笔记） |
| ctrl + shift + r | 重置所有过滤器，恢复初始视图 |
| f5 | 手动刷新文件（查看最新日志） |