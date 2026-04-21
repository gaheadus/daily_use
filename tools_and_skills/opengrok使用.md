# opengrok搜索
## 搜索语法  
- To find where setResourceMonitors is defined:  `defs:setResourceMonitors`  
- To find files that use sprintf in usr/src/cmd/cmd-inet/usr.sbin/:  `refs:sprintf` path:usr/src/cmd/cmd-inet/usr.sbin  
- To find assignments to variable foo:  `"foo ="`  
- To search for phrase "Bill Joy":  `"Bill Joy"`  
- To find Makefiles where the pstack binary is being built:  `pstack path:Makefile`  
- To find perl files that do not use /usr/bin/perl but something else:  `-"/usr/bin/perl" +"/bin/perl"`  
- To find all strings beginning with foo use the wildcard:  `foo*`  
- To find all files which have .c in their name (dot is a token!):  `".c"`  
- To find all files which start with "ma" and then have only alphabet characters do:  `path:/ma[a-zA-Z]*/`  
- To find all main methods in all files analyzed by C analyzer (so .c, .h, ...) do:  `main type:c`  

<br>

| 域   | 功能 |
|:-----|:-----|
| full | Search through all text tokens (words,strings,identifiers,numbers) in index. |
| defs | Only finds symbol definitions (where e.g. a variable (function, ...) is defined). |
| refs | Only finds symbols (e.g. methods, classes, functions, variables). |
| path | path of the source file (no need to use dividers, or if, then use "/" \-\- Windows users, "\" is an escape key in Lucene query syntax! <br> Please don't use "\", or replace it with "/").\-\-windows opengrok也用\/作为路径分隔符 <br> Also note that if you want just exact path, enclose it in "", e.g. "src/mypath", otherwise dividers will be removed and you get more hits. |
| hist | History log comments.  |
| type | Type of analyzer used to scope down to certain file types (e.g. just C sources). |
|      | Current mappings: \[ada=Ada, asm=Asm, bzip2=Bzip(2), c=C, clojure=Clojure, csharp=C\#, cxx=C\+\+, eiffel=Eiffel, elf=ELF, erlang=Erlang, file=Image file, fortran=Fortran, golang=Golang, gzip=GZIP, haskell=Haskell, hcl=HCL, jar=Jar, java=Java, javaclass=Java class, javascript=JavaScript, json=Json, kotlin=Kotlin, lisp=Lisp, lua=Lua, mandoc=Manual pages, pascal=Pascal, perl=Perl, php=PHP, plain=Plain Text, plsql=PL/SQL, powershell=PowerShell script, python=Python, r=R, ruby=Ruby, rust=Rust, scala=Scala, sh=Shell script, sql=SQL, swift=Swift, tar=Tar, tcl=Tcl, terraform=Terraform, troff=Troff, typescript=TypeScript, uuencode=UUEncoded, vb=Visual Basic, verilog=Verilog, xml=XML, yaml=Yaml, zip=Zip] |

上述不同域有对应的搜索框：  
①主页搜索框细分为六类：完整搜索/定义/引用/路径/历史/文件类型(full/defs/refs/path/hist/type)。  
完整搜索框不加前缀表示搜索纯文本、加上defs:/refs:/path:等前缀表示搜索对应的类型。或者直接到对应类型的搜索框中搜索。  
②打开具体的代码页，页面顶上的搜索框是完整搜索。



## 例子
搜索双引号：\"\\"string\\.h\\"\" 或 \"\\"string.h\\"\"   


## 搜索语法(2)  

OpenGrok 是一个基于 Java 的开源源代码搜索引擎，其搜索语法强大且灵活，支持全文检索、符号查找、路径过滤、逻辑运算等多种高级功能。以下是基于最新公开资料整理的核心搜索语法。

#### 一、基础搜索语法

- **简单文本搜索**：直接输入关键词，如 `Thread`，会匹配所有包含该词的代码、注释或字符串。
- **短语搜索**：用双引号包裹精确匹配，如 `"command_line ="`。
- **通配符**：
  - `*` 匹配零个或多个字符，如 `start_*`。
  - `?` 匹配单个字符，如 `te?t`（可匹配 `test`、`text`）。
- **模糊查询**：使用 `~` 进行近似匹配，如 `res~`。
- **范围查询**：用于数值或版本号，如 `version:[1.0 TO 2.0]`。
- **精确匹配**：使用双引号包裹短语进行精确匹配（如 `"final String"`），避免拆词搜索。

#### 二、域（Field）限定搜索

通过 `域:值` 格式限定搜索范围，常用域包括：

- `def:`：查找函数、变量、类等**定义**，如 `def:start_kernel`。
- `refs:`：查找**引用**（调用位置），如 `refs:sprintf`。
- `path:`：按**文件路径**搜索，如 `path:sound/core/`（注意斜杠需转义）。
- `type:`：按**文件类型**过滤，如 `type:c`（C文件）、`type:java`（Java文件）。
- `full:`：**全文本搜索**（默认行为）。
- `hist:`：搜索**提交历史**或日志，如 `bugfix hist:true`。
- 时间范围：`date:20220101-20221231` 限定在2022年内的文件修改记录。

支持的文件类型包括：c, cxx, java, python, shell, Makefile 等30+种。

#### 三、逻辑与组合查询

- **AND（必须同时包含）**：用 `+` 或 `AND`，如 `+init +module`。
- **OR（或关系）**：用 `||` 或 `OR`，如 `malloc OR new`。
- **NOT（排除）**：用 `-` 或 `!`，如 `-path:staging/`。
- **组合示例**：`(malloc OR new) AND (type:c OR type:cpp)`。
  - `def:"finish" path:Activity.java`，在 `Activity.java` 文件中查找 `finish` 函数定义。
  - `refs:printf path:drivers/ type:c`，在C语言驱动的代码中查找 `printf` 的调用。
- **包含/排除**：
  - `+"关键词"` 强制包含（如 `+"activity"`）；
  - `-"关键词"` 排除结果（如 `-"service"` 过滤含 `service` 的文件）。
  - `-"/usr/bin/perl" +"/bin/perl"`，排除特定路径的Perl文件。
  - `+"activity" -"service"`，搜索包含 `activity` 字符串但是不包含 `service` 字符串的**文件**（去掉双引号同样可以，但是对于不可分割的词且两者间包含空格则双引号不可去，此规则适用于所有的搜索规则，例如 Full Search `"final String"`，双引号去除表示或的关系，这个与 Google 的搜索规则是一样的）。而且只能使用双引号，单引号不起作用。
- **逻辑操作符**：`AND`、`OR`、`NOT`（**必须大写**），例如 `"final" AND "String"` 查找同时包含两者的文件。

> **注意**：`"final" AND "String"` 不是查找同时包含 `"final"` 和 `"String"` 的**行**，而是查找同时包含 `"final"` 和 `"String"` 的**文件**。  
> `"final String"` 才是搜索同时包含 `"final"` 和 `"String"` 的行。同样，`"final" "String"`、`"final" +"String"` 查找同时包含 `"final"` 和 `"String"` 的文件，`"final" -"String"` 查找包含 `"final"` 但不包含 `"String"` 的文件。可知，**逻辑操作符 AND、包含排除符 `+` `-` 不是以行为单位查找，是以文件为单位查找，双引号 `""` 里面的文字才是以行为单位查找**。  
> 如何查找包含 `"final"` 但不包含 `"String"` 的行？——还是用 `"final" -"String"`，包含 `"final"` 但不包含 `"String"` 的文件，符合这个条件的行也包括在其中了。

#### 四、正则表达式与特殊字符处理

- **正则搜索**：用 `/pattern/` 包裹，如 `/[mb]an/`（匹配 `man` 或 `ban`）。
- **转义特殊字符**：若搜索内容含 `+ - && || ! ( ) { } [ ] ^ " ~ * ? : \`，需加 `\` 转义，如：`\(1\+\)\:2` 匹配 `(1+1):2`。

> **注意**：  
> ① 15类（18个）特殊字符，如果放在双引号里面，则表示字符本身，不具有特殊含义。搜索 `Bill Joy`，搜索框填 `"Bill Joy"`；搜索 `Bill*Joy`，搜索框填 `"Bill*Joy"` 或 `"Bill\*Joy"` 都可以——双引号里面特殊字符可转义、也可不转义。  
> ② **点号**有点特殊：  
> 1. 搜索 `Bill.Joy`，搜索框填 `"Bill.Joy"`，结果不正确，必须写成 `"Bill\.Joy"`，点号在双引号中必须转义。点号并不是 OpenGrok 特殊字符，为什么需要转义？  
> 2. 搜索 `Bill.Joy`，搜索框填 `Bill.Joy` 或 `Bill\.Joy`，结果都不正确，必须整体加双引号，而且点号需要转义，只能写成 `"Bill\.Joy"`。


#### 五、实用技巧与优化建议

- **限定范围提升效率**：先用 `path:` 或 `type:` 缩小范围，再细化查询。
- **避免全库模糊搜索**：大项目中直接搜索通用词（如 `log`）可能超时，应结合 `type:` 或 `path:`。
- **历史搜索指定时间**：结合 `hist:` 和版本控制信息追溯变更。
- **项目过滤**：在多项目环境中，通过顶部 "Project(s)" 下拉框限定搜索范围。
- 使用 `project:项目名` 限定搜索范围（如 `project:linux-kernel` 仅在指定内核代码库中搜索）。
- 文件路径模式匹配：`path:/ma[a-zA-Z]*/` 查找以 `ma` 开头的目录下的文件。
- VS Code 插件集成：通过 `vscode_opengrok` 扩展直接在编辑器中搜索并跳转结果。

#### 六、常见使用场景示例‌
| 目标 |	查询示例 |
| --- | --- |
|查找main函数(C文件) |	main type:c |
|查找Makefile中构建init\-mm.o |	"init\-mm.o" path:Makefile |
|查找sound/core下所有sprintf调用 |	refs:sprintf path:sound/core/ |
|查找以ma开头的文件 |	path:/ma\[a\-zA\-Z\]\*/ |
|查找printk但排除staging目录 | 	refs:printk path:drivers/ type:c -path:drivers/staging/ |

--百度搜索



