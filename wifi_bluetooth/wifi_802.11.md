# wifi 802.11

如同下表中，列举出来几种安全策略所对应的链路认证、接入认证和数据加密的方式。

| **安全策略**              | **链路认证方式** | **接入认证方式** | **数据加密方式**       | **说明**                                         |
| ------------------------- | ---------------- | ---------------- | ---------------------- | ------------------------------------------------ |
| WEP                       | Open             | 不涉及           | 不加密或WEP加密        | 不安全的安全策略                                 |
|                           | Shared-key Authentication | 不涉及  | WEP加密                | 仍然是不安全的安全策略                           |
| WPA/WPA2-802.1X           | Open             | 802.1X(EAP)      | TKIP或CCMP             | 安全性高的安全策略，适用于大型企业。             |
| WPA/WPA2-PSK              | Open             | PSK              | TKIP或CCMP             | 安全性高的安全策略，适用于中小型企业或家庭用户。 |
| WAPI-CERT                 | Open             | 预共享密钥鉴别   | SMS4                   | 国产货，应用的少，适用于大型企业和运营商。       |
| WAPI-PSK                  | Open             | WAPI证书鉴别     | SMS4                   | 国产货，应用的少，适用于小型企业和家庭用户       |

这里再配合下面这张图一起理解下。**链路认证和接入认证是先后两个不同阶段的认证**。  
![链路认证和接入认证是先后两个不同阶段的认证](https://github.com/gaheadus/daily_use/blob/master/Resources/%E9%93%BE%E8%B7%AF%E8%AE%A4%E8%AF%81%E5%92%8C%E6%8E%A5%E5%85%A5%E8%AE%A4%E8%AF%81%E6%98%AF%E5%85%88%E5%90%8E%E4%B8%A4%E4%B8%AA%E4%B8%8D%E5%90%8C%E9%98%B6%E6%AE%B5%E7%9A%84%E8%AE%A4%E8%AF%81.png)  
从表中可以看出，安全策略可分为WEP、WPA、WPA2和WAPI几种，这几种安全策略对应的链路认证其实只有Open和Shared-key Authentication两种，而802.1X和PSK则是属于接入认证方式。  



## 网址收藏
https://zhuanlan.zhihu.com/dot11

https://zhuanlan.zhihu.com/p/21623985

