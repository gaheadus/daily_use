# 快捷键





# theme主题

## 接近source insight 4.0的主题

此配置以VSCode浅色主题为基础，模拟Source Insight经典样式。可以根据实际观察的Source Insight界面颜色进行微调。  
```
"workbench.colorTheme": "Visual Studio Light", // 建议先选择浅色主题作为基础

  "editor.fontFamily": "Consolas, 'Courier New', monospace",

  "editor.fontSize": 13,

  "editor.lineHeight": 1.5,

  

  "workbench.colorCustomizations": {

​    "[Visual Studio Light]": { // 此设置仅在"Visual Studio Light"主题下生效

​      "editor.background": "#FFFFFF",

​      "sideBar.background": "#F0F0F0",

​      "activityBar.background": "#2B2B2B"

​    }

  },

  

  "editor.tokenColorCustomizations": {

​    "[Visual Studio Light]": { // 同样指定在特定主题下生效

​      "comments": "#008000",

​      "keywords": "#0000FF",

​      "strings": "#000000",

​      "functions": "#000080",

​      "variables": "#800080",

​      "types": "#008000",

​      

​      "textMateRules": [ // 更精细的语法作用域规则

​        {

​          "scope": "entity.name.function",

​          "settings": {

​            "foreground": "#000080",

​            "fontStyle": "bold"

​          }

​        },

​        {

​          "scope": "variable.other.local",

​          "settings": {

​            "foreground": "#800080"

​          }

​        },

​        {

​          "scope": "entity.name.function.preprocessor",

​          "settings": {

​            "foreground": "#FF0000",

​            "fontStyle": "bold"

​          }

​        },

​        {

​          "scope": [

​            "storage.type",

​            "keyword.control"

​          ],

​          "settings": {

​            "foreground": "#0000FF"

​          }

​        },

​        {

​          "scope": [

​            "constant.numeric"

​          ],

​          "settings": {

​            "foreground": "#FF0000"

​          }

​        }

​      ]

​    }

  }
```

