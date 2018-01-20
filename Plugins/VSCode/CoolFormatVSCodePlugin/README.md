# VSCode CoolFormat Format

This extension allows you to run CoolFormat on Visual Studio Code to format code.

## Installation

Open the command palette (Ctrl-Shift-P / Cmd-Shift-P)

> ext install vscode-astyle

## How to Start

1. Download CoolFormatExec from https://sourceforge.net/projects/coolformat/files/Plugins/
1. Prepare your style by editting coolformatrc and put it in the search path. 
1. Enable supported languages in configration. (C and C++ are enabled by default)
1. When you open a supoprted language file, you can find 'Format' in context menu or just shortcut Shift-Alt-F.

## Configuration



## FAQ

- Q1. How to avoid conflict with ClangFormat in C/C++ package
- A1. VSCode is not support dominate code formatter but with scores, and it two formatter has same score, it choose the later one. However, in the latest version of C/C++ package, you can disable ClangFormat with options `"C_Cpp.formatting" : "disabled"`. 

## Source code

Available on github: https://github.com/akof1314/CoolFormat