@echo off&rem 俄罗斯方块游戏，由netbenton编写，在bathome首发，完成时间：2009年9月25日 ver 2.0
if "%1" equ "para2" goto :para2

set "d-v=for %%a in (!str!) do set/a one=0x%%a,x=one/4+n,y=one%%4+m&(for %%b in ("r!x!.!y!") do if "!%%~b!" equ "　" (set r!x!.!y!=■) else (set err=1))"
::函数d-v，把str中的图标数据，放置到总坐标空间中，如果有覆盖，则err=1。调用方法：(%d-v%)
::变量使用：one  x  y

set "d-e=set aec=!cr!!cr!        ┌───────────┐!cr!&(for /l %%a in (2,1,#) do for %%b in ("│!ebuf:@=%%a!│　　!ebu%%a!") do set aec=!aec!        %%~b!cr!)&cls&echo;!aec!        └───────────┘"
::函数d-e，把总坐标空间显示出来，调用方法：(%d-e:#=行数%)
set ebu4=第!guan!关
set ebu6=总分：!fen!
set cr=^


::各种图标定义
set ga1=0 1 5 6
set ga2=1 4 5 8
::■■
::  ■■
set gb1=1 2 4 5
set gb2=0 4 5 9
::  ■■
::■■

set za1=4 5 6 7
set za2=1 5 9 d
::■■■■

set qa1=1 5 9 8
set qa2=0 4 5 6
set qa3=0 1 4 8
set qa4=0 1 2 6
::■■
::  ■
::  ■

set qb1=0 4 8 9
set qb2=0 1 2 4
set qb3=0 1 5 9
set qb4=2 4 5 6
::■■
::■
::■

set ta1=0 1 4 5
::■■
::■■

set sa1=0 1 2 5
set sa2=1 4 5 9
set sa3=1 4 5 6
set sa4=0 4 5 8
::  ■
::■■■
set tw1=0 1
set tw2=0 4

set on1=0
set on2=0

set sh1=1 4 5 6 9
set sh2=1 4 5 6 9

set ao1=0 1 2 4 6
set ao2=0 1 4 8 9
set ao3=0 4 5 6 2
set ao4=0 1 5 8 9

set tt1=0 1 2 5 9
set tt2=0 4 8 5 6
set tt3=1 5 8 9 a
set tt4=2 4 5 6 a


::cdef
::89ab
::4567
::0123

echo 0 2 >%~n0.tmp
start "aswd" %0 para2
::起动控制窗口

set k3=k%%=mx,k+
set k4=down
set k1=m-
set k2=m+
set k5=t+
::按键定义

setlocal enabledelayedexpansion
for /l %%a in (0,1,10) do (set "ebuf=!ebuf!^!r@.%%a^!")
for %%a in (sa_4 ta_1 qb_4 qa_4 za_2 ga_2 gb_2 tw_2 on_2 sh_2 ao_4 tt_4) do (
for /f "tokens=1,2 delims=_" %%b in ("%%a") do (
set _%%b=%%c
for /l %%d in (1,1,%%c) do set/a nx+=1&set ran!nx!=%%b%%d
)
)
::定义各种图型的可变型数，及单个图的随机号        

:restart
for /l %%a in (0,1,18) do (for /l %%b in (0,1,10) do set r%%a.%%b=　)
set/a fen=0,guan=1
::初始化坐标空间18行，10列


:loop
set/a "m=4,t=2,n=1,down=450/(guan<<2),bti=0"
set/a r=!random!%%nx+1
set err=

set ttr=!_ttr!
set _ttr=!ran%r%!
::随机取一个图标，

if not defined ttr goto :loop

set mx=!_%ttr:~,2%!
set k=%ttr:~2%
set str=!%ttr%!

set _str=!%_ttr%!


setlocal enabledelayedexpansion
for %%a in (!_str!) do set/a one=0x%%a,x=one/4+8,y=one%%4&set kk!x!.!y!=■
for /l %%a in (8,1,11) do for /l %%b in (0,1,3) do (
if defined kk%%a.%%b (set kk%%a=!kk%%a!!kk%%a.%%b!) else (set kk%%a=!kk%%a!　)
)
endlocal&set ebu8=%kk8%&set ebu9=%kk9%&set ebu10=%kk10%&set ebu11=%kk11%
::对预备图标的处理


:cont
for /f "tokens=1,2" %%a in (%~n0.tmp) do (
if %%b geq 6 (call :error %%b&exit)
if %%a neq !test! (
set bs=!str!&set/a bm=m,bk=k
set/a !k%%b!=1
if "%%b" equ "3" (for %%b in ("!ttr:~,2!!k!") do set str=!%%~b!)
setlocal enabledelayedexpansion
(%d-v:#=3%)
                rem 调用函数把图标点放置到总坐标空间
if defined err (
endlocal
set/a m=bm,k=bk
set str=!bs!
if "%%b" equ "4" goto :jmpout
) else (
(%d-e:#=18%)
                        rem 调用显示函数
endlocal
)
)
set test=%%a
)


set ti=1!time:~7,1!!time:~9,2!
if !ti! lss !bti! (set /a tn=ti-bti+1000) else (set /a tn=ti-bti)
if !tn! gtr !down! (
set/a bti=ti,n+=1
setlocal enabledelayedexpansion
(%d-v:#=3%)
if defined err (
endlocal
goto :jmpout
) else (
(%d-e:#=18%)
endlocal
)
)

goto :cont

:jmpout
set/a n-=1
(%d-v:#=3%)
set m=18

for /l %%a in (18,-1,2) do for %%b in ("!ebuf:@=%%a!") do if "%%~b" neq "■■■■■■■■■■■" (set e!m!=%%~b&set/a m-=1)

if !m! neq 1 (
for /l %%a in (!m!,-1,2) do set "e%%a=　　　　　　　　　　　"
for /l %%a in (18,-1,2) do (
for /l %%b in (0,1,10) do set r%%a.%%b=!e%%a:~%%b,1!
)
set/a "fen=fen+(m-1)*10,guan=fen/150+1"
)

if !n! leq 2 (
echo 游戏结束！
ping -n 3 127.1 >nul
goto :restart
)
goto :loop

:para2
mode con: cols=30 lines=2
echo a左 d右 w转 s加速 q退出
:p_lp
set/a n=n%%10+1
choice /c adwsgq /n >nul
>%~n0.tmp echo;%n% %errorlevel%
if %errorlevel% geq 6 exit
goto :p_lp

:error
if %1 equ 6 echo 谢谢使用，再见。。。
if %1 gtr 6 echo 对不起！choice.exe 文件不存在，不能运行。。。
ping -n 3 127.1 >nul
goto :eof