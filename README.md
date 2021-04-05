# npp的一些变量

```
FULL_CURRENT_PATH   : E:\my Web\main\welcome.html
CURRENT_DIRECTORY   : E:\my Web\main
FILE_NAME           : welcome.html
NAME_PART           : welcome
EXT_PART            : .html
```

# 将coolformat与npp run结合

## main.pyw
```python
import subprocess
import sys

if __name__ == '__main__':
    si = subprocess.STARTUPINFO()
    si.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    fname = sys.argv[1]
    subprocess.call('coolformat.exe -f {}'.format(fname), startupinfo=si)
    subprocess.call('notepad++.exe {}'.format(fname), startupinfo=si)
```

## run
```shell
pythonw.exe D:\coolformat\main.pyw "$(FULL_CURRENT_PATH)"
```

# 将coolformat与nppexec结合

## 方法1

```
NPP_CONSOLE 0
NPP_SAVE
coolformat.exe -f "$(FULL_CURRENT_PATH)"
notepad++.exe "$(FULL_CURRENT_PATH)"
```

## 方法2

```
NPP_CONSOLE 0
NPP_SAVE
powershell.exe cp "$(FULL_CURRENT_PATH)"  "$(CURRENT_DIRECTORY)\$(NAME_PART).bak$(EXT_PART)"
coolformat.exe -f "$(CURRENT_DIRECTORY)\$(NAME_PART).bak$(EXT_PART)"
notepad++.exe "$(CURRENT_DIRECTORY)\$(NAME_PART).bak$(EXT_PART)"
```

CoolFormat
==========
CoolFormat Source Code Formatter is a code formatter for C\C++\C#\CSS\HTML\Java\JavaScript\JSON\Objective-C\PHP\SQL\Verilog\XML.
It supports code highlighting for web publishment which is truly convenient for writing and reading a blog post, etc.

CoolFormat源代码格式化是一款C\C++\C#\CSS\HTML\Java\JavaScript\JSON\Objective-C\PHP\SQL\Verilog\XML代码格式化工具。软件可以快速多种风格格式化，并对语言进行着色。界面采用Office 2010风格，并有多种样式可以替换。并且支持代码高亮到网页上显示，方便博客文章之类的撰写阅读。

# Download #
Current version：3.5

Download [latest release](https://sourceforge.net/projects/coolformat/files/Release/)

# Documentation #
Check out the [formatter documentation](http://akof1314.github.io/CoolFormat/doc/index.html)

# Usage #
Check out the [instructions for use](https://github.com/akof1314/CoolFormat/wiki)

# Plugins #
- [Visual Studio 2013](https://sourceforge.net/projects/coolformat/files/Plugins/VS/)
- [Sublime Text](https://github.com/akof1314/Sublime-CoolFormat)
- [Notepad++](https://sourceforge.net/projects/coolformat/files/Plugins/NPP/)
- [VSCode](https://sourceforge.net/projects/coolformat/files/Plugins/VSCode/)

# How To Build #
Development tools and third-parties:

开发工具及第三方库：

- Visual Studio 2013
- BCGControlBar v.22.1
- Qt Creator (Optional)

Compiling the third-parties:

编译第三方库：

BCGControlBarPro 文件夹放到 CoolFormat 同级目录。编译 BCGCBProStatic120.sln 的 Unicode Debug 版本 和 Unicode Release 版本，“平台工具集”选择“Visual Studio 2013 - Windows XP (v120_xp)”
