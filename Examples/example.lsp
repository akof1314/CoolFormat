;;设置自动缩进 
(setq indent-tabs-mode nil) 
(setq default-tab-width 8) 
(setq tab-width 8) 
(setq tab-stop-list ()) 
;;设置C语言风格 
(add-hook 'c-mode-hook 'linux-c-mode) 
(setq imenu-sort-function 'imenu--sort-by-name) 
(defun linux-c-mode() 
(define-key c-mode-map [return] 'newline-and-indent) 
(interactive) 
(c-set-style "K&R") 
(c-toggle-hungry-state) 
(setq c-basic-offset 4) 
(imenu-add-menubar-index) 
(which-function-mode) 
) 
;;取消警告声音 
(setq visible-bell nil) 
;;设置颜色主题 
(require 'color-theme) 
(color-theme-charcoal-black) 
;;设置默认字体 
(set-default-font "Bitstream Vera Sans Mono-16") 
;;支持 emacs 和外部程序的粘贴 
(setq x-select-enable-clipboard t) 
;;取消滚动条 
(scroll-bar-mode nil) 
;;显示列号 
(column-number-mode t) 
;;高亮显示选择区域 
(setq-default transient-mark-mod t) 
(transient-mark-mode t) 
;;括号匹配显示 
(show-paren-mode t) 
;;隐藏工具栏 
(tool-bar-mode -1) 
(menu-bar-mode -1) 
;;语法高亮 
(global-font-lock-mode t) 
;;关闭启动画面 
(setq inhibit-startup-message t) 
;;设置字体 
(if (not (member '("-*-Bitstream Vera Sans Mono-normal-r-*-*-18-*-*-*-c-*-fontset-chinese" 
. "fontset-chinese") fontset-alias-alist)) 
(progn 
(create-fontset-from-fontset-spec 
"-*-Bitstream Vera Sans Mono-normal-r-*-*-20-*-*-*-c-*-fontset-chinese, 
chinese-gb2312:-*-微软雅黑-normal-r-*-*-16-*-*-*-c-*-gb2312*-*, 
chinese-big5-1:-*-Bitstream Vera Sans Mono-normal-normal-r-*-*-20-*-*-*-c-*-big5*-*, 
chinese-big5-2:-*-Bitstream Vera Sans Mono-normal-normal-r-*-*-20-*-*-*-c-*-big5*-*" t) 
(setq default-frame-alist 
(append 
'((font . "fontset-chinese")) 
default-frame-alist)) 
) 
) 
[Original] [Print] [Top] 
(defun w32-restore-frame () 
"Restore a minimized frame" 
(interactive) 
(w32-send-sys-command 61728)) 
(defun w32-maximize-frame () 
"Maximize the current frame" 
(interactive) 
(w32-send-sys-command 61488)) 
(w32-maximize-frame)