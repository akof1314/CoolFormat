#include <Constants.au3>
#NoTrayIcon
Opt("TrayMenuMode", 1) ;没有默认的（暂停脚本和退出）菜单.
Opt("trayOnEventMode", 1) ;应用 OnEvent 函数于系统托盘.

$Start = TrayCreateItem("启用") ;创建第一个菜单项
TrayItemSetOnEvent($Start, "TrayMsg") ;注册第一个菜单项的（被点下）事件
TrayCreateItem("") ;创建一个空白的菜单项（即横斜杠分割符）
$Close = TrayCreateItem("关闭") ;创建第二个菜单项
TrayItemSetOnEvent($Close, "TrayMsg") ;注册第二个菜单项的（被点下）事件
TrayCreateItem("") ;
$Quit = TrayCreateItem("退出") ;创建第三个菜单项
TrayItemSetOnEvent($Quit, "TrayMsg") ;注册第二个菜单项的（被点下）事件

TraySetOnEvent($TRAY_EVENT_PRIMARYDOUBLE, "TrayMsg") ;注册鼠标左键双击事件(只能在 TrayOnEventMode 设置为 1 时才能使用)
TraySetOnEvent($TRAY_EVENT_SECONDARYUP, "TrayMsg") ;注册鼠标右键双击事件(只能在 TrayOnEventMode 设置为 1 时才能使用)
TraySetState()

While 1
        Sleep(5000)
WEnd

Func TrayMsg()
        Switch @TRAY_ID   ;选择产生消息的 TrayItem 或其它特殊事件（如鼠标左键双击事件）
                Case $Start
                        MsgBox(48, "提示", "你点下了“启用”")
                Case $Close
                        MsgBox(48, "提示", "你点下了“关闭”")
                Case $TRAY_EVENT_PRIMARYDOUBLE
                        MsgBox(48, "提示", "你双击了鼠标左键")
                Case $Quit, $TRAY_EVENT_SECONDARYUP
                        Exit
        EndSwitch
EndFunc   ;==>TrayMsg