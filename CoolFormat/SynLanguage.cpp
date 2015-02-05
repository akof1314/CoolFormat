#include "StdAfx.h"
#include "SynLanguage.h"


CSynLanguage::CSynLanguage(void)
{
	m_nLanguage = SYN_NORMALTEXT;
}

CSynLanguage::~CSynLanguage(void)
{
}

void CSynLanguage::SetCurLanguage( UINT nLanguage )
{
	m_nLanguage = nLanguage;
}

CString CSynLanguage::GetWordDelimeters()
{
	CString strWordDelimeters;
	strWordDelimeters = _T(" \t\n,./?<>;:\"'{[}]~`%^&*()-+=!");
	switch (m_nLanguage)
	{
	case SYN_ASM:
		strWordDelimeters = _T(" \t\n,/<>;:\"'{[}]~`^&*()-+=!");
		break;
	case SYN_ASP:
	case SYN_AUTOIT:
	case SYN_COBOL:
	case SYN_CSS:
	case SYN_HTML:
	case SYN_JSP:
	case SYN_PHP:
		strWordDelimeters = _T(" \t\n,./?<>;:\"'{[}]~`%^&*()+=");
		break;
	case SYN_VERILOG:
		strWordDelimeters = _T(" \t\n,./?<>;:\"'{[}]~%^&*()-+=!");
		break;
	}
	return strWordDelimeters;
}

CString CSynLanguage::GetSpecialDelimiters()
{	
	return _T (";.{}\n");	
}

CString CSynLanguage::GetIntelliSenseChars()
{
	return _T (".>:");
}

CString CSynLanguage::GetEscapeSequences()
{
	CString strEscapeSequences = _T("");
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
	case SYN_ASM:
	case SYN_CPP:
	case SYN_D:
	case SYN_HASKELL:
	case SYN_JAVA:
	case SYN_JSP:
	case SYN_OBJECTIVEC:
	case SYN_PERL:
	case SYN_RUBY:
	case SYN_VERILOG:
		strEscapeSequences = _T("\\\",\\\\,");
		break;
	case SYN_JAVASCRIPT:
		strEscapeSequences = _T("\\\",\\',\\\\,/*@,@*/,");
		break;
	case SYN_SQL:
		strEscapeSequences = _T("\\\",\\\\,\\',");
		break;
	}
	return strEscapeSequences;
}

void CSynLanguage::GetWords(CString &strWords, BOOL &bCaseSensitive)
{	
	strWords = _T("");
	bCaseSensitive = FALSE;
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
		strWords = _T("add,for,lt,tellTarget,and,ne,this,break,ge,new,typeof,continue,gt,not,var,delete,if,on,do,ifFrameLoaded,onClipEvent,while,else,in,or,with,eq,le,return,instanceof,case,default,switch,arguments,constructor,class,dynamic,false,extends,implements,import,interface,intrinsic,newline,private,public,super,static,true,undefined,Accessibility,Arguments,Button,Camera,ContextMenu,ContextMenuItem,CustomActions,Color,Function,Key,LoadVars,LocalConnection,Math,Microphone,Mouse,MovieClip,MovieClipLoader,NetConnection,NetStream,PrintJob,TextField,StyleSheet,TextFormat,TextSnapshot,SharedObject,Selection,Sound,Stage,System,XMLNode,XMLSocket,Void,abs,acos,asin,atan,atan2,ceil,cos,exp,floor,log,max,min,pow,random,round,sin,sqrt,tan,onActivity,onChanged,onClose,onConnect,onData,onDragOut,onDragOver,onEnterFrame,onID3,onKeyDown,onKeyUp,onKillFocus,onLoad,onLoadComplete,onLoadError,onLoadInit,onLoadProgress,onLoadStart,onMouseDown,onMouseMove,onMouseUp,onMouseWheel,onPress,onRelease,onReleaseOutside,onResize,onRollOut,onRollOver,onScroller,onSelect,onSetFocus,onSoundComplete,onStatus,onUnload,onUpdate,onXML,addListener,addPage,addProperty,addRequestHeader,allowDomain,allowInsecureDomain,appendChild,apply,applyChanges,asfunction,attachAudio,attachMovie,attachSound,attachVideo,beginFill,beginGradientFill,call,ceil,charAt,charCodeAt,clear,clearInterval,cloneNode,close,concat,connect,copy,cos,createElement,createEmptyMovieClip,createTextField,createTextNode,curveTo,domain,duplicateMovieClip,endFill,escape,eval,evaluate,exp,findText,floor,fscommand,flush,fromCharCode,get,getAscii,getBeginIndex,getBounds,getBytesLoaded,getBytesTotal,getCaretIndex,getCode,getCount,getDate,getDay,getDepth,getEndIndex,getFocus,getFontList,getFullYear,getHours,getInstanceAtDepth,getLocal,getMilliseconds,getMinutes,getMonth,getNewTextFormat,getNextHighestDepth,getPan,getProggress,getProperty,getRGB,getSeconds,getSelected,getSelectedText,getSize,")
			_T("getStyle,getStyleNames,getSWFVersion,getText,getTextExtent,getTextFormat,getTextSnapshot,getTime,getTimer,getTimezoneOffset,getTransform,getURL,getUTCDate,getUTCDay,getUTCFullYear,getUTCHours,getUTCMilliseconds,getUTCMinutes,getUTCMonth,getUTCSeconds,getVersion,getVolume,getYear,globalToLocal,gotoAndPlay,gotoAndStop,hasChildNodes,hide,hideBuiltInItems,hitTest,hitTestTextNearPos,indexOf,insertBefore,install,isActive,isDown,isToggled,join,lastIndexOf,lineStyle,lineTo,list,load,loadClip,loadMovie,loadMovieNum,loadSound,loadVariables,loadVariablesNum,localToGlobal,log,mbchr,mblength,mbord,mbsubstring,min,MMExecute,moveTo,nextFrame,nextScene,parseCSS,parseFloat,parseInt,parseXML,pause,play,pop,pow,prevScene,print,printAsBitmap,printAsBitmapNum,printNum,push,random,registerClass,removeListener,removeMovieClip,removeNode,removeTextField,replaceSel,replaceText,reverse,round,seek,send,sendAndLoad,setBufferTime,set,setDate,setFocus,setFullYear,setGain,setHours,setInterval,setMask,setMilliseconds,setMinutes,setMode,setMonth,setMotionLevel,setNewTextFormat,setPan,setProperty,setQuality,setRate,setRGB,setSeconds,setSelectColor,setSelected,setSelection,setSilenceLevel,setStyle,setTextFormat,setTime,setTransform,setUseEchoSuppression,setUTCDate,setUTCFullYear,setUTCHours,setUTCMilliseconds,setUTCMinutes,setUTCMonth,setUTCSeconds,setVolume,setYear,shift,show,showSettings,silenceLevel,silenceTimeout,sin,slice,sort,sortOn,splice,split,sqrt,start,startDrag,stop,stopAllSounds,stopDrag,substr,substring,swapDepths,tan,toggleHighQuality,toLowerCase,toString,toUpperCase,trace,unescape,uninstall,unLoadClip,unloadMovie,unloadMovieNum,unshift,unwatch,updateAfterEvent,updateProperties,useEchoSuppression,valueOf,watch,endinitclip,include,initclip,__proto__,_accProps,_alpha,_currentframe,_droptarget,_focusrect,_framesloaded,_global,_height,_highquality,_level,_lockroot,_name,_parent,_quality,_root,_rotation,_soundbuftime,_target,")
			_T("_totalframes,_url,_visible,_width,_x,_xmouse,_xscale,_y,_ymouse,_yscale,activityLevel,align,allowDomain,allowInsecureDomain,attributes,autoSize,avHardwareDisable,background,backgroundColor,bandwidth,blockIndent,bold,border,borderColor,bottomScroll,bufferLenght,bufferTime,builtInItems,bullet,bytesLoaded,bytesTotal,callee,caller,capabilities,caption,childNodes,color,condenseWhite,contentType,currentFps,customItems,data,deblocking,docTypeDecl,duration,embedFonts,enabled,exactSettings,firstChild,focusEnabled,font,fps,gain,globalStyleFormat,hasAccessibility,hasAudio,hasAudioEncoder,hasEmbeddedVideo,hasMP3,hasPrinting,hasScreenBroadcast,hasScreenPlayback,hasStreamingAudio,hasStreamingVideo,hasVideoEncoder,height,hitArea,hscroll,html,htmlText,indent,index,italic,instanceof,ignoreWhite,isDebugger,isDown,isFinite,italic,language,lastChild,leading,leftMargin,length,loaded,localFileReadDisable,manufacturer,maxChars,maxhscroll,maxscroll,menu,message,motionLevel,motionTimeout,mouseWheelEnabled,multiline,muted,name,names,NaN,nextSibling,nodeName,nodeType,nodeValue,os,parentNode,password,pixelAspectRatio,playerType,previousSibling,prototype,quality,rate,restrict,resolutionX,resolutionY,rightMargin,scaleMode,screenColor,screenDPI,screenResolutionX,screenResolutionY,scroll,selectable,separatorBefore,showMenu,size,smoothing,status,styleSheet,tabChildren,tabEnabled,tabIndex,tabStops,target,targetPath,text,textColor,textHeight,textWidth,time,trackAsMenu,type,underline,url,useCodepage,useEchoSuppression,useHandCursor,variable,version,visible,width,wordWrap,xmlDecl,function,namespace,package,try,catch,finally,throw,each,const,use,is,as,");
		bCaseSensitive = TRUE;
		break;
	case SYN_ADA:
		strWords = _T("abort,abs,abstract,accept,access,aliased,all,and,array,at,begin,body,case,constant,declare,delay,delta,digits,do,else,elsif,end,entry,exception,exit,for,function,generic,goto,if,in,is,limited,loop,mod,new,not,null,of,or,others,out,package,pragma,private,procedure,protected,raise,range,record,rem,renames,requeue,return,reverse,select,separate,subtype,tagged,task,terminate,then,type,until,use,when,while,with,xor,");
		break;
	case SYN_ASM:
		strWords = _T(".186,.286,.286c,.286p,.287,.386,.386c,.386p,.387,.486,.486p,.8086,.8087,.alpha,.break,.code,.const,.continue,.cref,.data,.data?,.dosseg,.else,.elseif,.endif,.endw,.err,.err1,.err2,.errb,.errdef,.errdif,.errdifi,.erre,.erridn,.erridni,.errnb,.errndef,.errnz,.exit,.fardata,.fardata?,.if,.lall,.lfcond,.list,.listall,.listif,.listmacro,.listmacroall,.model,.no87,.nocref,.nolist,.nolistif,.nolistmacro,.radix,.repeat,.sall,.seq,.sfcond,.stack,.startup,.tfcond,.type,.until,.untilcxz,.while,.xall,.xcref,.xlist,alias,align,assume,catstr,comm,comment,db,dd,df,dosseg,dq,dt,dup,dw,echo,else,elseif,elseif1,elseif2,elseifb,elseifdef,elseifdif,elseifdifi,elseife,elseifidn,elseifidni,elseifnb,elseifndef,end,endif,endm,endp,ends,eq,equ,even,exitm,extern,externdef,extrn,for,forc,ge,goto,group,gt,high,highword,if,if1,if2,ifb,ifdef,ifdif,ifdifi,ife,ifidn,ifidni,ifnb,ifndef,include,includelib,instr,invoke,irp,irpc,label,le,length,lengthof,local,low,lowword,lroffset,lt,macro,mask,mod,.msfloat,name,ne,offset,opattr,option,org,%out,page,popcontext,proc,proto,ptr,public,purge,pushcontext,record,repeat,rept,seg,segment,short,size,sizeof,sizestr,struc,struct,substr,subtitle,subttl,textequ,this,title,type,typedef,union,while,width,aaa,aad,aam,aas,adc,add,and,call,cbw,clc,cld,cli,cmc,cmp,cmps,cmpsb,cmpsw,cwd,daa,das,dec,div,esc,hlt,idiv,imul,in,inc,int,into,iret,ja,jae,jb,jbe,jc,jcxz,je,jg,jge,jl,jle,jmp,jna,jnae,jnb,jnbe,jnc,jne,jng,jnge,jnl,jnle,jno,jnp,jns,jnz,jo,jp,jpe,jpo,js,jz,lahf,lds,lea,les,lods,lodsb,lodsw,loop,loope,loopew,loopne,loopnew,loopnz,loopnzw,loopw,loopz,loopzw,mov,movs,movsb,movsw,mul,neg,nop,not,or,out,pop,popf,push,pushf,rcl,rcr,ret,retf,retn,rol,ror,sahf,sal,sar,sbb,scas,scasb,scasw,shl,shr,stc,std,sti,stos,stosb,stosw,sub,test,wait,xchg,xlat,xlatb,xor,bound,enter,ins,insb,insw,leave,outs,outsb,outsw,popa,pusha,pushw,arpl,lar,lsl,sgdt,sidt,sldt,smsw,str,verr,verw,clts,lgdt,lidt,lldt,lmsw,ltr,")
			_T("bsf,bsr,bt,btc,btr,bts,cdq,cmpsd,cwde,insd,iretd,iretdf,iretf,jecxz,lfs,lgs,lodsd,loopd,looped,loopned,loopnzd,loopzd,lss,movsd,movsx,movzx,outsd,popad,popfd,pushad,pushd,pushfd,scasd,seta,setae,setb,setbe,setc,sete,setg,setge,setl,setle,setna,setnae,setnb,setnbe,setnc,setne,setng,setnge,setnl,setnle,setno,setnp,setns,setnz,seto,setp,setpe,setpo,sets,setz,shld,shrd,stosd,bswap,cmpxchg,invd,invlpg,wbinvd,xadd,lock,rep,repe,repne,repnz,repz,f2xm1,fabs,fadd,faddp,fbld,fbstp,fchs,fclex,fcom,fcomp,fcompp,fdecstp,fdisi,fdiv,fdivp,fdivr,fdivrp,feni,ffree,fiadd,ficom,ficomp,fidiv,fidivr,fild,fimul,fincstp,finit,fist,fistp,fisub,fisubr,fld,fld1,fldcw,fldenv,fldenvw,fldl2e,fldl2t,fldlg2,fldln2,fldpi,fldz,fmul,fmulp,fnclex,fndisi,fneni,fninit,fnop,fnsave,fnsavew,fnstcw,fnstenv,fnstenvw,fnstsw,fpatan,fprem,fptan,frndint,frstor,frstorw,fsave,fsavew,fscale,fsqrt,fst,fstcw,fstenv,fstenvw,fstp,fstsw,fsub,fsubp,fsubr,fsubrp,ftst,fwait,fxam,fxch,fxtract,fyl2x,fyl2xp1,fsetpm,fcos,fldenvd,fnsaved,fnstenvd,fprem1,frstord,fsaved,fsin,fsincos,fstenvd,fucom,fucomp,fucompp,fcomi,fcomip,ffreep,fcmovb,fcmove,fcmovbe,fcmovu,fcmovnb,fcmovne,fcmovnbe,fcmovnu,addpd,addps,addsd,addss,andpd,andps,andnpd,andnps,cmpeqpd,cmpltpd,cmplepd,cmpunordpd,cmpnepd,cmpnltpd,cmpnlepd,cmpordpd,cmpeqps,cmpltps,cmpleps,cmpunordps,cmpneps,cmpnltps,cmpnleps,cmpordps,cmpeqsd,cmpltsd,cmplesd,cmpunordsd,cmpnesd,cmpnltsd,cmpnlesd,cmpordsd,cmpeqss,cmpltss,cmpless,cmpunordss,cmpness,cmpnltss,cmpnless,cmpordss,comisd,comiss,cvtdq2pd,cvtdq2ps,cvtpd2dq,cvtpd2pi,cvtpd2ps,cvtpi2pd,cvtpi2ps,cvtps2dq,cvtps2pd,cvtps2pi,cvtss2sd,cvtss2si,cvtsd2si,cvtsd2ss,cvtsi2sd,cvtsi2ss,cvttpd2dq,cvttpd2pi,cvttps2dq,cvttps2pi,cvttsd2si,cvttss2si,divpd,divps,divsd,divss,fxrstor,fxsave,ldmxscr,lfence,mfence,maskmovdqu,maskmovdq,maxpd,maxps,paxsd,maxss,minpd,minps,minsd,minss,movapd,movaps,movdq2q,movdqa,movdqu,movhlps,movhpd,movhps,movd,movq,movlhps,movlpd,movlps,movmskpd,")
			_T("movmskps,movntdq,movnti,movntpd,movntps,movntq,movq2dq,movsd,movss,movupd,movups,mulpd,mulps,mulsd,mulss,orpd,orps,packssdw,packsswb,packuswb,paddb,paddsb,paddw,paddsw,paddd,paddsiw,paddq,paddusb,paddusw,pand,pandn,pause,paveb,pavgb,pavgw,pavgusb,pdistib,pextrw,pcmpeqb,pcmpeqw,pcmpeqd,pcmpgtb,pcmpgtw,pcmpgtd,pf2id,pf2iw,pfacc,pfadd,pfcmpeq,pfcmpge,pfcmpgt,pfmax,pfmin,pfmul,pmachriw,pmaddwd,pmagw,pmaxsw,pmaxub,pminsw,pminub,pmovmskb,pmulhrwc,pmulhriw,pmulhrwa,pmulhuw,pmulhw,pmullw,pmuludq,pmvzb,pmvnzb,pmvlzb,pmvgezb,pfnacc,pfpnacc,por,prefetch,prefetchw,prefetchnta,prefetcht0,prefetcht1,prefetcht2,pfrcp,pfrcpit1,pfrcpit2,pfrsqit1,pfrsqrt,pfsub,pfsubr,pi2fd,pf2iw,pinsrw,psadbw,pshufd,pshufhw,pshuflw,pshufw,psllw,pslld,psllq,pslldq,psraw,psrad,psrlw,psrld,psrlq,psrldq,psubb,psubw,psubd,psubq,psubsb,psubsw,psubusb,psubusw,psubsiw,pswapd,punpckhbw,punpckhwd,punpckhdq,punpckhqdq,punpcklbw,punpcklwd,punpckldq,punpcklqdq,pxor,rcpps,rcpss,rsqrtps,rsqrtss,sfence,shufpd,shufps,sqrtpd,sqrtps,sqrtsd,sqrtss,stmxcsr,subpd,subps,subsd,subss,ucomisd,ucomiss,unpckhpd,unpckhps,unpcklpd,unpcklps,xorpd,xorps,");
		break;
	case SYN_ASP:
		strWords = _T("!doctype,a,abbr,accept-charset,accept,accesskey,acronym,action,address,align,alink,alt,applet,archive,area,article,aside,audio,axis,b,background,base,basefont,bdo,bgcolor,big,blockquote,body,border,br,button,canvas,caption,cellpadding,cellspacing,center,char,charoff,charset,checkbox,checked,cite,class,classid,clear,code,codebase,codetype,col,colgroup,color,cols,colspan,command,comment,compact,content,coords,data,datafld,dataformatas,datalist,datapagesize,datasrc,datetime,dd,declare,defer,del,details,dfn,dir,disabled,div,dl,dt,em,embed,enctype,event,face,fieldset,figure,figcaption,file,footer,font,for,form,frame,frameborder,frameset,h1,h2,h3,h4,h5,h6,head,header,headers,height,hgroup,hidden,hr,href,hreflang,hspace,html,http-equiv,i,id,iframe,image,img,input,ins,isindex,ismap,kbd,keygen,label,lang,language,leftmargin,legend,li,link,list,longdesc,map,marginwidth,marginheight,mark,maxlength,media,menu,meta,meter,method,multiple,name,nav,noframes,nohref,noresize,noscript,noshade,nowrap,object,ol,onblur,onchange,onclick,ondblclick,onfocus,onkeydown,onkeypress,onkeyup,onload,onmousedown,onmousemove,onmouseover,onmouseout,onmouseup,optgroup,option,onreset,onselect,onsubmit,onunload,output,p,param,password,profile,progress,pre,prompt,public,q,radio,readonly,rel,reset,rev,rows,rowspan,rp,rt,ruby,rules,s,samp,scheme,scope,script,scrolling,section,select,selected,shape,size,small,source,span,src,standby,start,strike,strong,style,sub,submit,summary,sup,tabindex,table,target,tbody,td,text,textarea,tfoot,th,thead,time,title,topmargin,tr,tt,type,u,ul,usemap,valign,value,valuetype,var,version,video,vlink,vspace,width,xml,xmlns,");
		strWords += _T("addhandler,addressof,andalso,alias,and,ansi,as,assembly,attribute,auto,begin,byref,byval,call,case,catch,cbool,cbyte,cchar,cdate,cdec,cdbl,cint,class,clng,cobj,compare,const,continue,cshort,csng,cstr,ctype,currency,declare,default,delegate,dim,do,each,else,elseif,end,enum,erase,error,event,exit,explicit,false,finally,for,friend,function,get,gettype,global,gosub,goto,handles,if,implement,implements,imports,in,inherits,interface,is,let,lib,like,load,loop,lset,me,mid,mod,module,mustinherit,mustoverride,mybase,myclass,namespace,new,next,not,nothing,notinheritable,notoverridable,on,option,optional,or,orelse,overloads,overridable,overrides,paramarray,preserve,private,property,protected,public,raiseevent,readonly,redim,rem,removehandler,rset,resume,return,select,set,shadows,shared,static,step,stop,structure,sub,synclock,then,throw,to,true,try,type,typeof,unload,unicode,until,variant,wend,when,while,with,withevents,writeonly,xor,#if,#end,#else,#const,#region,#externalSource,");
		break;
	case SYN_AUTOHOTKEY:
		strWords = _T("if,ifequal,ifexist,ifgreater,ifgreaterorequal,ifinstring,ifless,iflessorequal,ifmsgbox,ifnotequal,ifnotexist,ifnotinstring,ifwinactive,ifwinexist,ifwinnotactive,ifwinnotexist,break,continue,else,exit,exitapp,gosub,goto,loop,onexit,pause,repeat,return,settimer,sleep,suspend,static,global,local,var,byref,while,until,for,class,try,catch,throw,autotrim,blockinput,clipwait,control,controlclick,controlfocus,controlget,controlgetfocus,controlgetpos,controlgettext,controlmove,controlsend,controlsendraw,controlsettext,coordmode,critical,detecthiddentext,detecthiddenwindows,drive,driveget,drivespacefree,edit,endrepeat,envadd,envdiv,envget,envmult,envset,envsub,envupdate,fileappend,filecopy,filecopydir,filecreatedir,filecreateshortcut,filedelete,filegetattrib,filegetshortcut,filegetsize,filegettime,filegetversion,fileinstall,filemove,filemovedir,fileread,filereadline,filerecycle,filerecycleempty,fileremovedir,fileselectfile,fileselectfolder,filesetattrib,filesettime,formattime,getkeystate,groupactivate,groupadd,groupclose,groupdeactivate,gui,guicontrol,guicontrolget,hideautoitwin,hotkey,imagesearch,inidelete,iniread,iniwrite,input,inputbox,keyhistory,keywait,listhotkeys,listlines,listvars,menu,mouseclick,mouseclickdrag,mousegetpos,mousemove,msgbox,outputdebug,pixelgetcolor,pixelsearch,postmessage,process,progress,random,regdelete,regread,regwrite,reload,run,runas,runwait,send,sendevent,sendinput,sendmessage,sendmode,sendplay,sendraw,setbatchlines,setcapslockstate,setcontroldelay,setdefaultmousespeed,setenv,setformat,setkeydelay,setmousedelay,setnumlockstate,setscrolllockstate,setstorecapslockmode,settitlematchmode,setwindelay,setworkingdir,shutdown,sort,soundbeep,soundget,soundgetwavevolume,soundplay,soundset,soundsetwavevolume,splashimage,splashtextoff,splashtexton,splitpath,statusbargettext,statusbarwait,stringcasesense,stringgetpos,stringleft,stringlen,stringlower,stringmid,stringreplace,")
			_T("stringright,stringsplit,stringtrimleft,stringtrimright,stringupper,sysget,thread,tooltip,transform,traytip,urldownloadtofile,winactivate,winactivatebottom,winclose,winget,wingetactivestats,wingetactivetitle,wingetclass,wingetpos,wingettext,wingettitle,winhide,winkill,winmaximize,winmenuselectitem,winminimize,winminimizeall,winminimizeallundo,winmove,winrestore,winset,winsettitle,winshow,winwait,winwaitactive,winwaitclose,winwaitnotactive,fileencoding,");
		break;
	case SYN_AUTOIT:
		strWords = _T("#include,#include-once,#region,#endregion,and,byref,case,continueloop,dim,do,else,elseif,endfunc,endif,endselect,endswitch,exit,exitloop,for,func,global,if,local,next,not,or,return,select,step,then,to,until,wend,while,exit,abs,acos,adlibdisable,adlibenable,asc,asin,atan,autoitsetoption,autoitwingettitle,autoitwinsettitle,bitand,bitnot,bitor,bitshift,bitxor,blockinput,break,call,cdtray,chr,clipget,clipput,controlclick,controlcommand,controldisable,controlenable,controlfocus,controlgetfocus,controlgetpos,controlgettext,controlhide,controlmove,controlsend,controlsettext,controlshow,cos,dec,dircopy,dircreate,dirmove,dirremove,drivegetdrive,drivegetfilesystem,drivegetlabel,drivegetserial,drivegettype,drivesetlabel,drivespacefree,drivespacetotal,drivestatus,envget,envset,envupdate,eval,exp,filechangedir,fileclose,filecopy,filecreateshortcut,filedelete,fileexists,filefindfirstfile,filefindnextfile,filegetattrib,filegetlongname,filegetshortname,filegetsize,filegettime,filegetversion,fileinstall,filemove,fileopen,fileopendialog,fileread,filereadline,filerecycle,filerecycleempty,filesavedialog,fileselectfolder,filesetattrib,filesettime,filewrite,filewriteline,guicreate,guicreateex,guidefaultfont,guidelete,guigetcontrolstate,guihide,guimsg,guiread,guirecvmsg,guisendmsg,guisetcontrol,guisetcontroldata,guisetcontrolex,guisetcontrolfont,guisetcontrolnotify,guisetcoord,guisetcursor,guishow,guiwaitclose,guiwrite,hex,hotkeyset,inidelete,iniread,iniwrite,inputbox,int,isadmin,isarray,isdeclared,isfloat,isint,isnumber,isstring,log,memgetstats,mod,mouseclick,mouseclickdrag,mousedown,mousegetcursor,mousegetpos,mousemove,mouseup,mousewheel,msgbox,number,pixelchecksum,pixelgetcolor,pixelsearch,processclose,processexists,processsetpriority,processwait,processwaitclose,progressoff,progresson,progressset,random,regdelete,regenumkey,regenumval,regread,regwrite,round,run,runasset,runwait,send,seterror,shutdown,sin,sleep,")
			_T("soundplay,soundsetwavevolume,splashimageon,splashoff,splashtexton,sqrt,statusbargettext,string,stringaddcr,stringformat,stringinstr,stringisalnum,stringisalpha,stringisascii,stringisdigit,stringisfloat,stringisint,stringislower,stringisspace,stringisupper,stringisxdigit,stringleft,stringlen,stringlower,stringmid,stringreplace,stringright,stringsplit,stringstripcr,stringstripws,stringtrimleft,stringtrimright,stringupper,switch,tan,timerstart,timerstop,tooltip,traytip,ubound,urldownloadtofile,winactivate,winactive,winclose,winexists,wingetcaretpos,wingetclasslist,wingetclientsize,wingethandle,wingetpos,wingetstate,wingettext,wingettitle,winkill,winmenuselectitem,winminimizeall,winminimizeallundo,winmove,winsetontop,winsetstate,winsettitle,winwait,winwaitactive,winwaitclose,winwaitnotactive,");
		break;
	case SYN_BATCH:
		strWords = _T("echo,do,else,end,errorlevel,exist,exit,for,goto,if,not,pause,return,say,select,then,when,ansi,append,assign,attrib,autofail,backup,basedev,boot,break,buffers,cache,call,cd,chcp,chdir,chkdsk,choice,cls,cmd,codepage,command,comp,copy,country,date,ddinstal,debug,del,detach,device,devicehigh,devinfo,dir,diskcoache,diskcomp,diskcopy,doskey,dpath,dumpprocess,eautil,endlocal,erase,exit_vdm,extproc,fcbs,fdisk,fdiskpm,files,find,format,fsaccess,fsfilter,graftabl,iopl,join,keyb,keys,label,lastdrive,libpath,lh,loadhigh,makeini,maxwait,md,mem,memman,mkdir,mode,move,net,patch,path,pauseonerror,picview,pmrexx,print,printmonbufsize,priority,priority_disk_io,prompt,protectonly,protshell,pstat,rd,recover,reipl,ren,rename,replace,restore,rmdir,rmsize,run,set,setboot,setlocal,shell,shift,sort,spool,start,subst,suppresspopups,swappath,syslevel,syslog,threads,time,timeslice,trace,tracebuf,tracefmt,trapdump,tree,type,undelete,unpack,use,ver,verify,view,vmdisk,vol,xcopy,xcopy32,xdfcopy,");
		break;
	case  SYN_COBOL:
		strWords = _T("accept,add,alter,apply,assign,call,chain,close,compute,continue,control,convert,count,delete,display,divide,draw,drop,eject,else,enable,end-accept,end-add,end-call,end-chain,end-compute,end-delete,end-display,end-divide,end-evaluate,end-if,end-invoke,end-multiply,end-perform,end-read,end-receive,end-return,end-rewrite,end-search,end-start,end-string,end-subtract,end-unstring,end-write,erase,evaluate,examine,exec,execute,exit,go,goback,generate,if,ignore,initialize,initiate,insert,inspect,invoke,leave,merge,move,multiply,open,otherwise,perform,print,read,receive,release,reload,replace,report,reread,rerun,reserve,reset,return,rewind,rewrite,rollback,run,search,seek,select,send,set,sort,start,stop,store,string,subtract,sum,suppress,terminate,then,transform,unlock,unstring,update,use,wait,when,wrap,write,access,acquire,actual,address,advancing,after,all,allowing,alphabet,alphabetic,alphabetic-lower,alphabetic-upper,alphanumeric,alphanumeric-edited,also,alternate,and,any,are,area,areas,as,ascending,at,attribute,author,auto,auto-hyphen-skip,auto-skip,automatic,autoterminate,background-color,background-colour,backward,basis,beep,before,beginning,bell,binary,blank,blink,blinking,block,bold,bottom,box,boxed,by,c01,c02,c03,c04,c05,c06,c07,c08,c09,c10,c11,c12,cancel,cbl,cd,centered,cf,ch,chaining,changed,character,characters,chart,class,clock-units,cobol,code,code-set,col,collating,color,colour,column,com-reg,comma,command-line,commit,commitment,common,communication,comp,comp-0,comp-1,comp-2,comp-3,comp-4,comp-5,comp-6,comp-x,compression,computational,computational-1,computational-2,computational-3,computational-4,computational-5,computational-6,computational-x,computational,console,contains,content,control-area,controls,conversion,converting,core-index,corr,corresponding,crt,crt-under,csp,currency,current-date,cursor,cycle,cyl-index,cyl-overflow,date,date-compiled,date-written,day,day-of-week,dbcs,de,")
			_T("debug,debug-contents,debug-item,debug-line,debug-name,debug-sub-1,debug-sub-2,debug-sub-3,debugging,decimal-point,default,delimited,delimiter,depending,descending,destination,detail,disable,disk,disp,display-1,display-st,down,duplicates,dynamic,echo,egcs,egi,emi,empty-check,encryption,end,end-of-page,ending,enter,entry,eol,eop,eos,equal,equals,error,escape,esi,every,exceeds,exception,excess-3,exclusive,exhibit,extend,extended-search,external,externally-described-key,factory,false,fd,fh--fcd,fh--keydef,file-id,file-limit,file-limits,file-prefix,filler,final,first,fixed,footing,for,foreground-color,foreground-colour,footing,format,from,full,giving,global,greater,grid,group,heading,high,high-value,high-values,highlight,id,in,index,indexed,indic,indicate,indicator,indicators,inheriting,initial,installation,into,invalid,invoked,is,japanese,just,justified,kanji,kept,key,keyboard,label,last,leading,left,left-justify,leftline,length,length-check,less,limit,limits,lin,linage,linage-counter,line,line-counter,lines,lock,lock-holding,locking,low,low-value,low-values,lower,lowlight,manual,mass-update,master-index,memory,message,method,mode,modified,modules,more-labels,multiple,name,named,national,national-edited,native,nchar,negative,next,no,no-echo,nominal,not,note,nstd-reels,null,nulls,number,numeric,numeric-edited,numeric-fill,o-fill,object,object-computer,object-storage,occurs,of,off,omitted,on,oostackptr,optional,or,order,organization,other,others,overflow,overline,packed-decimal,padding,page,page-counter,packed-decimal,paragraph,password,pf,ph,pic,picture,plus,pointer,pop-up,pos,position,positioning,positive,previous,print-control,print-switch,printer,printer-1,printing,prior,private,procedure-pointer,procedures,proceed,process,processing,prompt,protected,public,purge,queue,quote,quotes,random,range,rd,readers,ready,record,record-overflow,recording,records,redefines,reel,reference,references,relative,")
			_T("remainder,remarks,removal,renames,reorg-criteria,repeated,replacing,reporting,reports,required,resident,return-code,returning,reverse,reverse-video,reversed,rf,rh,right,right-justify,rolling,rounded,s01,s02,s03,s04,s05,same,screen,scroll,sd,secure,security,segment,segment-limit,selective,self,selfclass,sentence,separate,sequence,sequential,service,setshadow,shift-in,shift-out,sign,size,skip1,skip2,skip3,sort-control,sort-core-size,sort-file-size,sort-merge,sort-message,sort-mode-size,sort-option,sort-return,source,source-computer,space,spaces,space-fill,spaces,standard,standard-1,standard-2,starting,status,sub-queue-1,sub-queue-2,sub-queue-3,subfile,super,symbolic,sync,synchronized,sysin,sysipt,syslst,sysout,syspch,syspunch,system-info,tab,tallying,tape,terminal,terminal-info,test,text,than,through,thru,time,time-of-day,time-out,timeout,times,title,to,top,totaled,totaling,trace,track-area,track-limit,tracks,trailing,trailing-sign,transaction,true,type,typedef,underline,underlined,unequal,unit,until,up,updaters,upon,upper,upsi-0,upsi-1,upsi-2,upsi-3,upsi-4,upsi-5,upsi-6,upsi-7,usage,user,using,value,values,variable,varying,when-compiled,window,with,words,write-only,write-verify,writerszero,zero,zero-fill,zeros,zeroes,");
		break;
	case SYN_CPP:
		strWords = _T("#define,#else,#elif,#elseif,#endif,#error,#if,#ifdef,#ifndef,#import,#include,#line,#pragma,#undef,#using,__asm,__based,__cdecl,__declspec,__except,__fastcall,__finally,__inline,__leave,__multiple_inheritance,__pascal,__single_inheritance,__stdcall,__try,__uuidof,__virtual_inheritance,_asm,_cdecl,_fastcall,_pascal,_stdcall,and,and_eq,asm,auto,bitand,bitor,break,case,catch,class,compl,const,const_cast,continue,default,delete,do,dynamic_cast,else,enum,explicit,extern,false,for,friend,goto,if,inline,mutable,namespace,new,not,not_eq,NULL,operator,or,or_eq,private,protected,public,register,reinterpret_cast,return,sizeof,static,static_cast,struct,switch,template,this,throw,true,try,typedef,typeid,typename,union,using,virtual,volatile,while,xor,xor_eq,");
		bCaseSensitive = TRUE;
		break;
	case SYN_CS:
		strWords = _T("#define,#else,#elif,#elseif,#endif,#endregion,#error,#if,#ifdef,#ifndef,#include,#line,#pragma,#region,#undef,#warning,__asm,__based,__cdecl,__declspec,__except,__fastcall,__finally,__inline,__int16,__int32,__int64,__int8,__leave,__multiple_inheritance,__pascal,__single_inheritance,__stdcall,__try,__uuidof,__virtual_inheritance,_asm,_cdecl,_fastcall,_pascal,_stdcall,abstract,as,base,break,case,catch,checked,continue,default,delegate,do,else,event,explicit,extern,false,finally,fixed,for,foreach,goto,if,implicit,in,interface,internal,is,lock,namespace,new,null,object,operator,out,override,params,private,protected,public,readonly,ref,return,sealed,sizeof,stackalloc,switch,this,throw,true,try,typeof,unchecked,unsafe,using,virtual,while,");
		bCaseSensitive = TRUE;
		break;
	case SYN_CSS:
		strWords = _T("azimuth,background,background-attachment,background-color,background-image,background-position,background-repeat,border,border-bottom,border-bottom-color,border-bottom-style,border-bottom-width,border-collapse,border-color,border-left,border-left-color,border-left-style,border-left-width,border-right,border-right-color,border-right-style,border-right-width,border-spacing,border-style,border-top,border-top-color,border-top-style,border-top-width,border-width,bottom,caption-side,clear,clip,color,content,counter-increment,counter-reset,cue,cue-after,cue-before,cursor,direction,display,elevation,empty-cells,float,font,font-family,font-size,font-size-adjust,font-stretch,font-style,font-variant,font-weight,height,left,letter-spacing,line-height,list-style,list-style-image,list-style-position,list-style-type,margin,margin-bottom,margin-left,margin-right,margin-top,marker-offset,marks,max-height,max-width,min-height,min-width,orphans,outline,outline-color,outline-style,outline-width,overflow,padding,padding-bottom,padding-left,padding-right,padding-top,page,page-break-after,page-break-before,page-break-inside,pause,pause-after,pause-before,pitch,pitch-range,play-during,position,quotes,richness,right,size,speak,speak-header,speak-numeral,speak-ponctuation,speech-rate,stress,table-layout,text-align,text-decoration,text-indent,text-shadow,text-transform,top,unicode-bidi,vertical-align,visibility,voice-family,volume,white-space,widows,width,word-spacing,z-index,");
		break;
	case SYN_D:
		strWords = _T("__FILE__,__LINE__,__DATE__,__TIME__,__TIMESTAMP__,abstract,align,asm,assert,auto,body,break,case,cast,catch,const,continue,debug,default,delete,deprecated,do,else,export,extern,false,final,finally,for,foreach,foreach_reverse,goto,if,import,in,inout,interface,invariant,is,lazy,mixin,module,new,null,out,override,package,pragma,private,protected,public,return,scope,static,super,switch,synchronized,template,this,throw,true,try,typedef,typeid,typeof,unittest,version,volatile,while,with,");
		bCaseSensitive = TRUE;
		break;
	case SYN_FORTRAN:
		strWords = _T("accept,assign,automatic,backspace,blockdata,break,byte,call,character,close,common,complex,contains,continue,data,date,decode,default,definefile,delete,dimension,do,doublecomplex,doubleprecision,else,elseif,encode,end,enddo,endfile,endif,endmap,endstructure,endunion,entry,equivalence,external,find,for,format,function,go,goto,if,implicit,implicitnone,implicitundefined,include,inquire,integer,interface,intrinsic,key,logical,map,module,namelist,none,nospanblocks,open,options,parameter,pause,pointer,print,program,read,readonly,real,record,recursive,return,rewind,rewrite,save,shared,static,stop,structure,subroutine,switch,then,to,type,undefined,union,unlock,use,virtual,volatile,while,write,");
		break;
	case SYN_HASKELL:
		strWords = _T("abs,absolute,accum,accumArray,acos,acosh,addition,addToClockTime,all,and,and,any,ap,appendFile,approxRational,array,array,as,asin,asinh,assocs,asTypeOf,atan,atan2,atanh,boolean,bounds,bracket,bracket_,break,calculation,calendarTimeToString,case,catch,catMaybes,ceiling,ceiling,character,chr,cis,class,compare,composition,concat,concatenate,concatenation,concatMap,conjugate,const,constant,construction,continuation,cos,cosh,cosine,cosine,cosine,cosine,cpuTimePrecision,createDirectory,curry,cycle,data,decodeFloat,default,defaultTimeLocale,delete,deleteBy,denominator,deriving,diffClockTimes,digitToInt,div,division,divMod,do,doesDirectoryExist,doesFileExist,drop,dropWhile,either,elem,elemIndex,elemIndices,elems,else,empty,encodeFloat,enumFrom,enumFromThen,enumFromThenTo,enumFromTo,equality,error,evaluation,even,even,executable,exitFailure,exitWith,exp,exponent,fail,False,filter,filterM,find,findIndex,findIndices,flip,floatDigits,floatRadix,floatRange,floatToDigits,floor,floor,fmap,foldl,foldl1,foldM,foldr,foldr1,forall,foreign,formatCalendarTime,fromEnum,fromInteger,fromIntegral,fromJust,fromMaybe,fromRat,fromRational,fst,function,gcd,genericDrop,genericIndex,genericLength,genericReplicate,genericSplitAt,genericTake,getArgs,getChar,getClockTime,getContents,getCPUTime,getCurrentDirectory,getDirectoryContents,getEnv,getLine,getModificationTime,getPermissions,getProgName,getStdGen,getStdRandom,group,groupBy,guard,hClose,head,hFileSize,hFlush,hGetBuffering,hGetChar,hGetContents,hGetLine,hGetPosn,hiding,hIsClosed,hIsEOF,hIsOpen,hIsReadable,hIsSeekable,hIsWritable,hLookAhead,hPrint,hPutChar,hPutStr,hPutStrLn,hReady,hSeek,hSetBuffering,hSetPosn,hWaitForInput,hyperbolic,hyperbolic,hyperbolic,hyperbolic,hyperbolic,hyperbolic,id,if,imagPart,import,in,index,index,indices,infix,infixl,infixr,init,inits,inRange,insert,insertBy,insertion,instance,interact,intersect,intersectBy,intersperse,intToDigit,inverse,")
			_T("inverse,inverse,inverse,inverse,inverse,ioeGetErrorString,ioeGetFileName,ioeGetHandle,ioError,isAlpha,isAlphaNum,isAlreadyExistsError,isAlreadyInUseError,isAscii,isControl,isDenormalized,isDigit,isDoesNotExistError,isEOF,isEOFError,isFullError,isHexDigit,isIEEE,isIllegalOperation,isInfinite,isJust,isLatin1,isLower,isNaN,isNegativeZero,isNothing,isOctDigit,isPermissionError,isPrefixOf,isPrint,isSpace,isSuffixOf,isUpper,isUserError,item,iterate,ixmap,join,last,lazy,lcm,length,length,let,lex,lexDigits,lexLitChar,liftM,liftM2,liftM3,liftM4,liftM5,lines,list,list,list,list,list,listArray,listToMaybe,log,logBase,lookup,magnitude,map,mapAccumL,mapAccumR,mapAndUnzipM,mapM,mapM_,mapMaybe,max,maxBound,maximum,maximumBy,maybe,maybeToList,mdo,min,minBound,minimum,minimumBy,mkPolar,mkStdGen,mod,module,modulo,monad,msum,multiplication,negate,newStdGen,newtype,next,nint,not,notElem,nub,nubBy,null,numerator,odd,odd,of,openFile,or,or,ord,order,otherwise,partition,passing,phase,pi,polar,power,pred,print,product,properFraction,putChar,putStr,putStrLn,qualified,quot,quotRem,random,randomIO,randomR,randomRIO,randomRs,randoms,range,rangeSize,read,readable,readDec,readFile,readFloat,readHex,readInt,readIO,readList,readLitChar,readLn,readOct,readParen,reads,readSigned,readsPrec,realPart,realToFrac,recip,rem,removeDirectory,removeFile,renameDirectory,renameFile,repeat,replicate,return,reverse,round,round,scaleFloat,scanl,scanl1,scanr,scanr1,searchable,seq,sequence,sequence_,setCurrentDirectory,setPermissions,setStdGen,show,showChar,showEFloat,showFFloat,showFloat,showGFloat,showInt,showList,showLitChar,showParen,shows,showSigned,showsPrec,showString,significand,signum,sin,sine,sine,sine,sine,sinh,snd,sort,sortBy,split,split,splitAt,sqrt,stderr,stdin,stdout,string,style,subtract,subtraction,succ,sum,sum,system,tail,tails,take,takeWhile,tan,tangent,tangent,tangent,tangent,tanh,then,toCalendarTime,toClockTime,toEnum,toInteger,")
			_T("toLower,toRational,toUpper,toUTCTime,transpose,trigonometry,True,truncate,truncation,try,tuple,type,uncurry,undefined,unfoldr,union,unionBy,unless,unlines,until,unwords,unzip,unzip3,unzip4,unzip5,unzip6,unzip7,userError,value,when,where,words,writable,writeFile,zip,zip3,zip4,zip5,zip6,zip7,zipWith,zipWith3,zipWith4,zipWith5,zipWith6,zipWith7,zipWithM,zipWithM_,");
		bCaseSensitive = TRUE;
		break;
	case SYN_HTML:
		strWords = _T("!doctype,a,abbr,accept-charset,accept,accesskey,acronym,action,address,align,alink,alt,applet,archive,area,article,aside,audio,axis,b,background,base,basefont,bdo,bgcolor,big,blockquote,body,border,br,button,canvas,caption,cellpadding,cellspacing,center,char,charoff,charset,checkbox,checked,cite,class,classid,clear,code,codebase,codetype,col,colgroup,color,cols,colspan,command,comment,compact,content,coords,data,datafld,dataformatas,datalist,datapagesize,datasrc,datetime,dd,declare,defer,del,details,dfn,dir,disabled,div,dl,dt,em,embed,enctype,event,face,fieldset,figure,figcaption,file,footer,font,for,form,frame,frameborder,frameset,h1,h2,h3,h4,h5,h6,head,header,headers,height,hgroup,hidden,hr,href,hreflang,hspace,html,http-equiv,i,id,iframe,image,img,input,ins,isindex,ismap,kbd,keygen,label,lang,language,leftmargin,legend,li,link,list,longdesc,map,marginwidth,marginheight,mark,maxlength,media,menu,meta,meter,method,multiple,name,nav,noframes,nohref,noresize,noscript,noshade,nowrap,object,ol,onblur,onchange,onclick,ondblclick,onfocus,onkeydown,onkeypress,onkeyup,onload,onmousedown,onmousemove,onmouseover,onmouseout,onmouseup,optgroup,option,onreset,onselect,onsubmit,onunload,output,p,param,password,profile,progress,pre,prompt,public,q,radio,readonly,rel,reset,rev,rows,rowspan,rp,rt,ruby,rules,s,samp,scheme,scope,script,scrolling,section,select,selected,shape,size,small,source,span,src,standby,start,strike,strong,style,sub,submit,summary,sup,tabindex,table,target,tbody,td,text,textarea,tfoot,th,thead,time,title,topmargin,tr,tt,type,u,ul,usemap,valign,value,valuetype,var,version,video,vlink,vspace,width,xml,xmlns,");
		break;
	case SYN_JAVA:
		strWords = _T("abstract,as,break,case,catch,class,const,continue,def,default,do,else,extends,final,finally,for,goto,if,implements,import,in,instanceof,interface,native,new,package,private,property,protected,public,return,static,strictfp,super,switch,synchronized,this,throw,throws,transient,try,volatile,while,");
		bCaseSensitive = TRUE;
		break;
	case SYN_JAVASCRIPT:
		strWords = _T("abstract,break,class,const,continue,debugger,default,delete,enum,export,extends,finally,instanceof,import,implements,in,goto,native,package,private,protected,public,super,throw,throws,transient,typeof,void,false,with,for,this,switch,try,while,if,do,else,return,null,case,catch,true,new,prototype,var,function,namespace,use,internal,interface,yields,let,");
		bCaseSensitive = TRUE;
		break;
	case SYN_JSON:
		strWords = _T("false,null,true,");
		bCaseSensitive = TRUE;
		break;
	case SYN_JSP:
		strWords = _T("abstract,as,break,case,catch,class,const,continue,def,default,do,else,extends,final,finally,for,goto,if,implements,import,in,instanceof,interface,native,new,package,private,property,protected,public,return,static,strictfp,super,switch,synchronized,this,throw,throws,transient,try,volatile,while,");
		bCaseSensitive = TRUE;
		break;
	case SYN_LISP:
		strWords = _T("abs,ads,alert,alloc,and,angle,angtof,angtos,append,apply,arx,arxload,arxunload,ascii,assoc,atan,atof,atoi,atom,atoms-family,autoarxload,autoload,autoxload,boole,boundp,caaar,caacdr,caadr,caar,cadddr,caddr,cadr,car,cdddr,cddr,cdr,chr,close,command,cond,cons,cos,cvunit,defun,dictadd,dictnext,dictremove,dictrename,dictsearch,distance,distof,entdel,entget,entlast,entmake,entmakex,entmod,entnext,entsel,entupd,eq,equal,eval,eval-when-compile,exit,exp,expand,expt,findfile,fix,float,foreach,gc,gcd,getangle,getcfg,getcname,getcorner,getdist,getenv,getfiled,getint,getkword,getorient,getpoint,getreal,getstring,getvar,graphscr,grclear,grdraw,grread,grtext,grvecs,handent,help,if,initget,inters,itoa,lambda,last,length,list,listp,load,log,logand,logior,lsh,mapcar,max,mem,member,menucmd,menugroup,min,minusp,namedobjdict,nentsel,nentselp,not,nth,null,numberp,open,or,osnap,polar,prin1,princ,print,progn,prompt,quit,quote,read,read-char,read-,line,redraw,regapp,rem,repeat,reverse,rtos,set,setcfg,setfunhelp,setq,setvar,setview,sin,snvalid,sqrt,ssadd,ssdel,ssget,ssgetfirst,sslength,ssmemb,ssname,ssnamex,sssetfirst,startapp,strcase,strcase,strcat,strlen,subst,substr,tablet,tblnext,tblobjname,tblsearch,terpri,textbox,textpage,textscr,trace,trans,type,untrace,ver,vports,wcmatch,while,write-char,write-line,xdroom,xdsize,xload,xunload,zerop,");
		break;
	case SYN_LUA:
		strWords = _T("abs,acos,and,appendto,asin,assert,atan,atan2,break,call,ceil,clock,closefile,collectgarbage,copytagmethods,cos,date,deg,do,dofile,dostring,else,elseif,end,error,execute,exit,exp,false,floor,flush,for,foreach,foreachi,format,frexp,function,getenv,getglobal,getn,gettagmethod,globals,gsub,if,in,ldexp,local,log,log10,max,min,mod,newtag,next,nil,not,number,openfile,or,print,rad,random,randomseed,rawget,rawset,read,readfrom,remove,rename,repeat,return,seek,setglobal,setlocale,settag,settagmethod,sin,sort,sqrt,strbyte,strchar,strfind,string,strlen,strlower,strrep,strsub,strupper,table,tag,tan,then,tinsert,tmpname,tonumber,tostring,tremove,true,type,until,userdata,while,write,writeto,");
		bCaseSensitive = TRUE;
		break;
	case SYN_OBJECTIVEC:
		strWords = _T("#define,#elif,#else,#endif,#error,#if,#ifdef,#ifndef,#include,#include_next,#import,#line,#pragma,#undef,@catch,@class,@encode,@end,@finally,@implementation,@interface,@private,@protected,@protocol,@public,@selector,@synchronized,@throw,@try,__asm,__based,__cdecl,__declspec,__except,__far,__fastcall,__finally,__fortran,__huge,__inline,__int16,__int32,__int64,__int8,__interrupt,__leave,__loadds,__near,__pascal,__saveregs,__segment,__segname,__self,__stdcall,__try,__uuidof,auto,break,bycopy,byref,case,class,const,continue,default,defs,do,else,encode,end,enum,extern,for,goto,if,implementation,in,inout,interface,nil,NIL,NULL,oneway,out,private,protected,protocol,public,register,return,selector,self,sizeof,static,struct,super,switch,typedef,union,volatile,while,");
		bCaseSensitive = TRUE;
		break;
	case SYN_PASCAL:
		strWords = _T("absolute,abstract,and,array,as,asm,assembler,automated,begin,case,cdecl,class,const,constructor,destructor,dispid,dispinterface,div,do,downto,dynamic,else,end,except,export,exports,external,false,far,file,finalization,finally,for,forward,function,goto,if,implementation,in,initialization,inherited,inline,interface,is,label,library,message,mod,near,nil,not,object,of,or,out,override,packed,pascal,private,procedure,program,property,protected,public,published,raise,record,register,repeat,resourcestring,safecall,set,shl,shr,stdcall,string,then,threadvar,to,try,true,type,unit,until,uses,var,virtual,while,with,xor,");
		break;
	case SYN_PERL:
		strWords = _T("NULL,__FILE__,__LINE__,__PACKAGE__,__DATA__,__END__,AUTOLOAD,BEGIN,CORE,DESTROY,END,EQ,GE,GT,INIT,LE,LT,NE,CHECK,abs,accept,alarm,and,atan2,bind,binmode,bless,caller,chdir,chmod,chomp,chop,chown,chr,chroot,close,closedir,cmp,connect,continue,cos,crypt,dbmclose,dbmopen,defined,delete,die,do,dump,each,else,elsif,endgrent,endhostent,endnetent,endprotoent,endpwent,endservent,eof,eq,eval,exec,exists,exit,exp,fcntl,fileno,flock,for,foreach,fork,format,formline,ge,getc,getgrent,getgrgid,getgrnam,gethostbyaddr,gethostbyname,gethostent,getlogin,getnetbyaddr,getnetbyname,getnetent,getpeername,getpgrp,getppid,getpriority,getprotobyname,getprotobynumber,getprotoent,getpwent,getpwnam,getpwuid,getservbyname,getservbyport,getservent,getsockname,getsockopt,glob,gmtime,goto,grep,gt,hex,if,index,int,ioctl,join,keys,kill,last,lc,lcfirst,le,length,link,listen,local,localtime,lock,log,lstat,lt,m,map,mkdir,msgctl,msgget,msgrcv,msgsnd,my,ne,next,no,not,oct,open,opendir,or,ord,our,pack,package,pipe,pop,pos,print,printf,prototype,push,q,qq,qr,quotemeta,qu,qw,qx,rand,read,readdir,readline,readlink,readpipe,recv,redo,ref,rename,require,reset,return,reverse,rewinddir,rindex,rmdir,s,scalar,seek,seekdir,select,semctl,semget,semop,send,setgrent,sethostent,setnetent,setpgrp,setpriority,setprotoent,setpwent,setservent,setsockopt,shift,shmctl,shmget,shmread,shmwrite,shutdown,sin,sleep,socket,socketpair,sort,splice,split,sprintf,sqrt,srand,stat,study,sub,substr,symlink,syscall,sysopen,sysread,sysseek,system,syswrite,tell,telldir,tie,tied,time,times,tr,truncate,uc,ucfirst,umask,undef,unless,unlink,unpack,unshift,untie,until,use,utime,values,vec,wait,waitpid,wantarray,warn,while,write,x,xor,y,");
		bCaseSensitive = TRUE;
		break;
	case SYN_PHP:
		strWords = _T("$argc,$argv,$_COOKIE,$_ENV,$_FILES,$_GET,$_POST,$_SERVER,$_SESSION,$_REQUEST,$GLOBALS,$HTTP_COOKIE_VARS,$HTTP_ENV_VARS,$HTTP_GET_VARS,$HTTP_POST_FILES,$HTTP_POST_VARS,$HTTP_SERVER_VARS,$HTTP_SESSION_VARS,$PHP_SELF,$this,__autoload,__call,__clone,__construct,__destruct,__get,__set,__sleep,__wakeup,abstract,as,break,case,catch,cfunction,continue,const,class,declare,default,die,do,echo,else,elseif,empty,enddeclare,endfor,endforeach,endif,endswitch,endwhile,eval,exit,extends,false,final,for,foreach,function,global,if,implements,include,include_once,interface,list,namespace,NULL,old_function,parent,print,private,protected,public,return,require,require_once,static,stdClass,switch,throw,true,try,var,virtual,while,");
		break;
	case SYN_PYTHON:
		strWords = _T("__abs__,__add__,__and__,__call__,__cmp__,__coerce__,__contains__,__del__,__delattr__,__delitem__,__delslice__,__div__,__divmod__,__eq__,__float__,__floordiv__,__ge__,__getattribute__,__getitem__,__getnewargs__,__getslice__,__gt__,__hash__,__hex__,__iadd__,__iand__,__idiv__,__ilshift__,__imod__,__imul__,__index__,__init__,__int__,__invert__,__ior__,__ipow__,__irshift__,__isub__,__iter__,__ixor__,__le__,__len__,__long__,__lshift__,__lt__,__mod__,__mul__,__ne__,__neg__,__nonzero__,__oct__,__or__,__pos__,__pow__,__radd__,__rand__,__rdiv__,__rdivmod__,__reduce__,__reduce_ex__,__repr__,__reserved__,__rfloordiv__,__rlshift__,__rmod__,__rmul__,__ror__,__rpow__,__rrshift__,__rshift__,__rsub__,__rtruediv__,__rxor__,__setattr__,__setitem__,__setslice__,__str__,__sub__,__xor__,add,and,append,ArithmeticError,as,assert,AssertionError,AttributeError,BaseException,break,capitalize,center,class,clear,close,conjugate,continue,copy,count,Decimal,decode,def,del,DeprecationWarning,difference,discard,elif,else,encode,endswith,EnvironmentError,EOFError,except,Exception,exec,expandtabs,extend,fileno,finally,find,FloatingPointError,flush,for,from,fromkeys,FutureWarning,GeneratorExit,get,getcontext,global,has_key,if,import,ImportError,ImportWarning,in,IndentationError,index,IndexError,insert,intersection,intersection_update,IOError,is,isalnum,isalpha,isatty,isdigit,islower,isspace,issubset,issuperset,istitle,isupper,items,iteritems,iterkeys,itervalues,join,KeyboardInterrupt,KeyError,keys,lambda,ljust,LookupError,lower,lstrip,MemoryError,NameError,next,not,NotImplementedError,object,or,OSError,OverflowError,OverflowWarning,pass,PendingDeprecationWarning,pop,popitem,print,raise,read,")
			_T("readline,readlines,ReferenceError,remove,replace,return,reverse,rfind,rindex,rjust,rsplit,rstrip,RuntimeError,RuntimeWarning,seek,setdefault,sort,split,splitlines,StandardError,startswith,StopIteration,strip,swapcase,symmetric_difference,symmetric_difference_update,SyntaxError,SyntaxWarning,SystemError,SystemExit,TabError,tell,title,translate,truncate,try,TypeError,UnboundLocalError,UnicodeDecodeError,UnicodeEncodeError,UnicodeError,UnicodeTranslateError,UnicodeWarning,union,update,upper,UserWarning,ValueError,values,Warning,while,WindowsError,with,write,writelines,yield,ZeroDivisionError,zfill,");
		bCaseSensitive = TRUE;
		break;
	case SYN_RUBY:
		strWords = _T("__FILE__,__LINE__,alias,and,ArgumentError,Array,begin,BEGIN,Bignum,Binding,break,case,class,Class,Complex,ConditionVariable,Continuation,def,defined?,DelegateClass,Dir,do,else,elsif,end,END,English,ensure,EOFError,Exception,false,FalseClass,Fatal,File,Fixnum,Float,FloatDomainError,for,GetoptLong,Hash,if,in,IndexError,Integer,Interrupt,IO,IOError,LoadError,LocalJumpError,MatchData,Method,module,Module,Mutex,NameError,next,nil,NilClass,NoMemoryError,not,NotImplementedError,Numeric,Object,or,Proc,Pstore,quit,Range,RangeError,redo,Regexp,RegexpError,rescue,retry,return,RuntimeError,ScriptError,SecurityError,self,SimpleDelegator,Singleton,StandardError,String,Struct,super,Symbol,SyntaxError,SystemCallError,SystemExit,SystemStackError,Tempfile,then,Thread,ThreadGroup,Time,true,TrueClass,TypeError,undef,unless,until,WeakRef,when,while,yield,ZeroDivisionError,");
		bCaseSensitive = TRUE;
		break;
	case SYN_SQL:
		strWords = _T("abs,absolute,access,acos,add,add_months,adddate,admin,after,aggregate,all,allocate,alter,and,any,app_name,are,array,as,asc,ascii,asin,assertion,at,atan,atn2,audit,authid,authorization,autonomous_transaction,avg,before,begin,benchmark,between,bfilename,bin,binary_checksum,binary_integer,bit_and,bit_count,bit_or,blob,body,both,breadth,bulk,by,call,cascade,cascaded,case,cast,catalog,ceil,ceiling,char_base,charindex,chartorowid,check,checksum,checksum_agg,chr,class,clob,close,cluster,coalesce,col_length,col_name,collate,collation,collect,column,comment,commit,completion,compress,concat,concat_ws,connect,connection,constant,constraint,constraints,constructorcreate,contains,containsable,continue,conv,convert,corr,corresponding,cos,cot,count,count_big,covar_pop,covar_samp,create,cross,cube,cume_dist,current,current_date,current_path,current_role,current_time,current_timestamp,current_user,currval,cycle,data,databasepropertyex,datalength,date_add,date_format,date_sub,dateadd,datediff,datename,datepart,day,db_id,db_name,deallocate,dec,declare,decode,default,deferrable,deferred,degrees,delete,dense_rank,depth,deref,desc,describe,descriptor,destroy,destructor,deterministic,diagnostics,dictionary,difference,disconnect,distinct,do,domain,double,drop,dump,dynamic,each,else,elsif,empth,encode,encrypt,end,end-exec,equals,escape,every,except,exception,exclusive,exec,execute,exists,exit,exp,export_set,extends,external,extract,false,fetch,file,file_id,file_name,filegroup_id,filegroup_name,filegroupproperty,fileproperty,first,first_value,floor,for,forall,foreign,format,formatmessage,found,freetexttable,from,from_days,fulltextcatalog,")
			_T("fulltextservice,function,general,get,get_lock,getansinull,getdate,getutcdate,global,go,goto,grant,greatest,group,grouping,having,heap,hex,hextoraw,host,host_id,host_name,hour,ident_current,ident_incr,ident_seed,identified,identity,if,ifnull,ignore,immediate,in,increment,index,index_col,indexproperty,indicator,initcap,initial,initialize,initially,inner,inout,input,insert,instr,instrb,interface,intersect,interval,into,is,is_member,is_null,is_numeric,is_srvrolemember,isdate,isnull,isolation,iterate,java,join,key,lag,language,large,last,last_day,last_value,lateral,lcase,lead,leading,least,left,len,length,lengthb,less,level,like,limit,limited,ln,local,localtime,localtimestamp,locator,lock,log,log10,loop,lower,lpad,ltrim,make_ref,map,match,max,maxextents,mid,min,minus,minute,mod,mode,modifies,modify,module,month,months_between,names,national,natural,naturaln,nclob,new,new_time,newid,next,next_day,nextval,no,noaudit,nocompress,nocopy,none,not,nowait,null,nullif,number_base,nvl,nvl2,object,object_id,object_name,object_property,ocirowid,oct,of,off,offline,old,on,online,only,opaque,open,operation,operator,option,or,ord,order,ordinalityorganization,others,out,outer,output,package,pad,parameter,parameters,partial,partition,path,pctfree,percent_rank,pi,pls_integer,positive,positiven,postfix,pow,power,pragma,precision,prefix,preorder,prepare,preserve,primary,prior,private,privileges,procedure,public,radians,raise,rand,range,rank,ratio_to_export,rawtohex,read,reads,record,recursive,ref,references,referencing,reftohex,relative,release,release_lock,rename,repeat,replace,resource,restrict,result,return,returns,reverse,revoke,right,rollback,")
			_T("rollup,round,routine,row,row_number,rowidtochar,rowlabel,rownum,rows,rowtype,rpad,rtrim,savepoint,schema,scope,scroll,search,second,section,seddev_samp,select,separate,sequence,session,session_user,set,sets,share,sign,sin,sinh,size,some,soundex,space,specific,specifictype,sql,sqlcode,sqlerrm,sqlexception,sqlstate,sqlwarning,sqrt,start,state,statement,static,std,stddev,stdev_pop,strcmp,structure,subdate,substr,substrb,substring,substring_index,subtype,successful,sum,synonym,sys_context,sys_guid,sysdate,system_user,tan,tanh,temporary,terminate,than,then,time,timezone_abbr,timezone_hour,timezone_minute,timezone_region,to,to_char,to_date,to_days,to_number,to_single_byte,trailing,transaction,translate,translation,treat,trigger,trim,true,trunc,truncate,type,ucase,uid,under,union,unique,unknown,unnest,update,upper,usage,use,user,userenv,using,validate,value,values,var_pop,var_samp,variable,variance,varying,view,vsize,when,whenever,where,while,with,without,work,write,year,zone,");
		break;
	case SYN_VB:
		strWords = _T("addhandler,addressof,andalso,alias,and,ansi,as,assembly,attribute,auto,begin,byref,byval,call,case,catch,cbool,cbyte,cchar,cdate,cdec,cdbl,cint,class,clng,cobj,compare,const,continue,cshort,csng,cstr,ctype,currency,declare,default,delegate,dim,do,each,else,elseif,end,enum,erase,error,event,exit,explicit,false,finally,for,friend,function,get,gettype,global,gosub,goto,handles,if,implement,implements,imports,in,inherits,interface,is,let,lib,like,load,loop,lset,me,mid,mod,module,mustinherit,mustoverride,mybase,myclass,namespace,new,next,not,nothing,notinheritable,notoverridable,on,option,optional,or,orelse,overloads,overridable,overrides,paramarray,preserve,private,property,protected,public,raiseevent,readonly,redim,removehandler,rset,resume,return,select,set,shadows,shared,static,step,stop,structure,sub,synclock,then,throw,to,true,try,type,typeof,unload,unicode,until,variant,wend,when,while,with,withevents,writeonly,xor,#if,#end,#else,#const,#region,#externalSource,");
		break;
	case SYN_VERILOG:
		strWords = _T("always,and,assign,automatic,begin,buf,bufif0,bufif1,case,casex,casez,cell,cmos,config,deassign,default,defparam,design,disable,edge,else,end,endcase,endconfig,endmodule,endfunction,endgenerate,endprimitive,endspecify,endtable,endtask,event,for,force,forever,fork,function,generate,genvar,highz0,highz1,if,ifnone,initial,inout,input,instance,integer,join,large,liblist,library,localparam,macromodule,medium,module,nand,negedge,nmos,none,nor,noshowcancelled,not,notif0,notif1,or,output,parameter,pulsestyle_onevent,pulsestyle_ondetect,pmos,posedge,primitive,pull0,pull1,pullup,pulldown,real,realtime,reg,release,repeat,rcmos,rnmos,rpmos,rtran,rtranif0,rtanif1,scalared,showcancelled,signed,small,specify,specparam,strength,strong0,strong1,supply0,supply1,table,task,time,tran,tranif0,tranif1,tri,tri1,tri0,triand,trior,trireg,use,vectored,wait,wand,weak0,weak1,while,wire,wor,xnor,xor,");
		bCaseSensitive = TRUE;
		break;
	case SYN_VHDL:
		strWords = _T("abs,access,active,after,alias,all,and,architecture,array,ascending,assert,attribute,base,begin,block,body,buffer,bus,case,component,configuration,constant,delayed,disconnect,downto,driving,driving_value,else,elsif,end,entity,event,exit,falling_edge,file,for,function,generate,generic,group,guarded,high,if,image,impure,in,inertial,inout,instance_name,is,label,last_active,last_event,last_value,left,leftof,length,library,linkage,literal,loop,low,map,mod,nand,new,next,nor,not,null,of,on,open,or,others,out,package,path_name,port,pos,postponed,pred,procedure,process,pure,quiet,range,record,register,reject,rem,report,return,reverse_range,right,rightof,rising_edge,rol,ror,select,severity,shared,signal,simple_name,sla,sll,sra,srl,stable,subtype,succ,then,to,transaction,transport,type,unaffected,until,untis,use,val,value,variable,wait,when,while,with,xnor,xor,");
		break;
	}
}

void CSynLanguage::GetTypeWords( CString &strWords, BOOL &bCaseSensitive )
{
	strWords = _T("");
	bCaseSensitive = FALSE; 
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
		strWords = _T("Boolean,int,Null,Number,String,uint,void,Object,Array,Date,Error,Function,RegExp,XML,XMLList,");
		bCaseSensitive = TRUE;
		break;
	case SYN_ADA:
		strWords = _T("boolean,character,duration,float,integer,long_float,long_integer,long_long_float,long_long_integer,natural,positive,short_float,short_integer,short_short_float,short_short_integer,string,wide_character,wide_string,");
		break;
	case SYN_ASM:
		strWords = _T("ah,al,ax,bh,bl,bp,bx,ch,cl,cr0,cr2,cr3,cr4,cs,cx,dh,di,dl,dr0,dr1,dr2,dr3,dr6,dr7,ds,dx,eax,ebp,ebx,ecx,edi,edx,es,esi,esp,fs,gs,si,sp,ss,st,tr3,tr4,tr5,tr6,tr7,st0,st1,st2,st3,st4,st5,st6,st7,mm0,mm1,mm2,mm3,mm4,mm5,mm6,mm7,xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,rax,rcx,rdx,rbx,rsp,rbp,rsi,rdi,r8,r8d,r8w,r8b,r9,r9d,r9w,r9b,r10,r10d,r10w,r10b,r11,r11d,r11w,r11b,r12,r12d,r12w,r12b,r13,r13d,r13w,r13b,r14,r14d,r14w,r14b,r15,r15d,r15w,r15b,rip,rflags,gdtr,idtr,ldtr,tr,cr8,xcr0,xmm8,xmm9,xmm10,xmm12,xmm12,xmm13,xmm14,xmm15,dd,byte,sbyte,sword,dword,sdword,fword,qword,tbyte,db,dw,dd,df,dq,dt,real4,real8,real10,atom,bool,false,farproc,globalhandle,handle,hglobal,hinstance,hlocal,hmodule,hstr,localhandle,lparam,lpbyte,lpcstr,lpdword,lphandle,lpint,lplong,lpstr,lpvoid,lpword,lresult,nearproc,npstr,null,pbyte,pdword,phandle,pint,plong,pstr,pword,sphandle,true,uint,wparam,hwnd,hmenu,hicon,hcursor,hbitmap,hbrush,hdc,hfont,hgdiobj,hpalette,hpen,hrgn,lppoint,lprect,lpsize,nppoint,nprect,npsize,point,ppoint,prect,psize,rect,word,$,?,@@:,@b,@catstr,@codesize,@cpu,@curseg,@datasize,@date,@environ,@f,@filecur,@filename,@instr,@interface,@line,@model,@sizestr,@substr,@time,@version,@wordsize,@code,@data,@fardata,@fardata?,@stack,");
		break;
	case SYN_AUTOHOTKEY:
		strWords = _T("a_ahkpath,a_ahkversion,a_appdata,a_appdatacommon,a_autotrim,a_batchlines,a_caretx,a_carety,a_computername,a_controldelay,a_cursor,a_dd,a_ddd,a_dddd,a_defaultmousespeed,a_desktop,a_desktopcommon,a_detecthiddentext,a_detecthiddenwindows,a_endchar,a_eventinfo,a_exitreason,a_formatfloat,a_formatinteger,a_gui,a_guievent,a_guicontrol,a_guicontrolevent,a_guiheight,a_guiwidth,a_guix,a_guiy,a_hour,a_iconfile,a_iconhidden,a_iconnumber,a_icontip,a_index,a_ipaddress1,a_ipaddress2,a_ipaddress3,a_ipaddress4,a_isadmin,a_iscompiled,a_issuspended,a_keydelay,a_language,a_lasterror,a_linefile,a_linenumber,a_loopfield,a_loopfileattrib,a_loopfiledir,a_loopfileext,a_loopfilefullpath,a_loopfilelongpath,a_loopfilename,a_loopfileshortname,a_loopfileshortpath,a_loopfilesize,a_loopfilesizekb,a_loopfilesizemb,a_loopfiletimeaccessed,a_loopfiletimecreated,a_loopfiletimemodified,a_loopreadline,a_loopregkey,a_loopregname,a_loopregsubkey,a_loopregtimemodified,a_loopregtype,a_mday,a_min,a_mm,a_mmm,a_mmmm,a_mon,a_mousedelay,a_msec,a_mydocuments,a_now,a_nowutc,a_numbatchlines,")
			_T("a_ostype,a_osversion,a_priorhotkey,a_programfiles,a_programs,a_programscommon,a_screenheight,a_screenwidth,a_scriptdir,a_scriptfullpath,a_scriptname,a_sec,a_space,a_startmenu,a_startmenucommon,a_startup,a_startupcommon,a_stringcasesense,a_tab,a_temp,a_thishotkey,a_thismenu,a_thismenuitem,a_thismenuitempos,a_tickcount,a_timeidle,a_timeidlephysical,a_timesincepriorhotkey,a_timesincethishotkey,a_titlematchmode,a_titlematchmodespeed,a_username,a_wday,a_windelay,a_windir,a_workingdir,a_yday,a_year,a_yweek,a_yyyy,clipboard,clipboardall,comspec,errorlevel,programfiles,true,false,a_thisfunc,a_thislabel,a_ispaused,a_iscritical,a_isunicode,a_ptrsize,a_scripthwnd,a_priorkey,");
		break;
	case SYN_AUTOIT:
		strWords = _T("@appdatacommondir,@appdatadir,@autoitversion,@commonfilesdir,@compiled,@computername,@comspec,@cr,@crlf,@desktopcommondir,@desktopdir,@desktopheight,@desktopwidth,@documentscommondir,@error,@favoritescommondir,@favoritesdir,@homedrive,@homepath,@homeshare,@hour,@ipaddress1,@ipaddress2,@ipaddress3,@ipaddress4,@lf,@logondnsdomain,@logondomain,@logonserver,@mday,@min,@mon,@mydocumentsdir,@osbuild,@oslang,@osservicepack,@ostype,@osversion,@programfilesdir,@programscommondir,@programsdir,@scriptdir,@scriptfullpath,@scriptname,@sec,@startmenucommondir,@startmenudir,@startupcommondir,@startupdir,@sw_hide,@sw_maximize,@sw_minimize,@sw_restore,@sw_show,@systemdir,@tab,@tempdir,@userprofiledir,@username,@wday,@windowsdir,@workingdir,@yday,@year,");
		break;
	case SYN_COBOL:
		strWords = _T("configuration,data,declaratives,division,environment,environment-division,file,file-control,function,i-o,i-o-control,identification,input,input-output,linkage,local-storage,output,procedure,program,program-id,section,special-names,working-storage,");
		break;
	case SYN_CPP:
		strWords = _T("__int16,__int32,__int64,__int8,bool,char,double,float,int,long,short,signed,unsigned,void,wchar_t,");
		bCaseSensitive = TRUE;
		break;
	case SYN_CS:
		strWords = _T("bool,byte,char,class,const,decimal,double,enum,float,int,long,sbyte,short,static,string,struct,uint,ulong,ushort,void,");
		bCaseSensitive = TRUE;
		break;
	case SYN_D:
		strWords = _T("alias,array,bool,byte,cdouble,cent,cfloat,char,class,creal,dchar,delegate,double,enum,float,function,idouble,ifloat,int,ireal,long,pointer,ptrdiff_t,real,short,size_t,struct,ubyte,ucent,uint,ulong,union,ushort,void,wchar,");
		bCaseSensitive = TRUE;
		break;
	case SYN_FORTRAN:
		strWords = _T("character,common,complex,dimension,double,external,implicit,integer,logical,parameter,precision,real,");
		break;
	case SYN_HASKELL:
		strWords = _T("Array,Bool,BufferMode,CalendarTime,Char,ClockTime,Complex,Complex,Day,Double,Either,ExitCode,FilePath,Float,Handle,HandlePosn,Int,Integer,IO,IOError,IOMode,Maybe,Month,Ordering,Permissions,Ratio,Rational,Rational,Read,ReadS,SeekMode,Show,ShowS,StdGen,String,TimeDiff,TimeLocale,");
		bCaseSensitive = TRUE;
		break;
	case SYN_JAVA:
		strWords = _T("boolean,byte,char,double,float,int,long,short,String,void,");
		bCaseSensitive = TRUE;
		break;
	case SYN_JAVASCRIPT:
		strWords = _T("boolean,byte,char,double,float,int,long,short,static,decimal,enum,sbyte,uint,ulong,ushort,void,");
		bCaseSensitive = TRUE;
		break;
	case SYN_JSP:
		strWords = _T("boolean,byte,char,double,float,int,long,short,String,void,");
		bCaseSensitive = TRUE;
		break;
	case SYN_OBJECTIVEC:
		strWords = _T("BOOL,char,Class,double,float,id,IMP,int,long,Method,SEL,short,signed,unsigned,void,");
		bCaseSensitive = TRUE;
		break;
	case SYN_PASCAL:
		strWords = _T("AnsiChar,AnsiString,Array,Boolean,Byte,ByteBool,Cardinal,Char,Currency,Double,Extended,File,Int64,Integer,LongBool,LongInt,LongWord,NativeInt,NativeUInt,PAnsiChar,PAnsiString,PBoolean,PByte,PCardinal,PChar,PCurrency,PDouble,PExtended,PInt64,PInteger,PLongBool,PLongint,PLongWord,PNativeInt,PNativeUInt,Pointer,PPointer,PShortInt,PShortString,PSingle,PSmallInt,PString,PUInt64,PUnicodeString,PVariant,PWideChar,PWideString,PWord,PWordBool,Real,Record,ShortInt,ShortString,Single,SmallInt,String,Text,TextFile,UInt64,UnicodeString,Variant,WideChar,WideString,Word,WordBool,");
		break;
	case SYN_PHP:
		strWords = _T("int,integer,real,double,float,string,array,object,");
		break;
	case SYN_PYTHON:
		strWords = _T("Ellipsis,False,None,NotImplemented,True,__import__,abs,all,any,basestring,bin,bool,buffer,callable,chr,classmethod,cmp,coerce,compile,complex,delattr,dict,dir,divmod,enumerate,eval,execfile,file,filter,float,format,frozenset,getattr,globals,hasattr,hash,help,hex,id,input,int,intern,isinstance,issubclass,iter,len,list,locals,long,map,max,min,next,object,oct,open,ord,pow,print,property,range,raw_input,reduce,reload,repr,reversed,round,set,setattr,slice,sorted,staticmethod,str,sum,super,tuple,type,unichr,unicode,vars,xrange,zip,");
		bCaseSensitive = TRUE;
		break;
	case SYN_RUBY:
		strWords = _T("AF_APPLETALK,AF_AX25,AF_INET,AF_INET6,AF_IPX,AF_UNIX,AF_UNSPEC,AI_ALL,AI_CANONNAME,AI_MASK,AI_NUMERICHOST,AI_PASSIVE,AI_V4MAPPED_CFG,ARGF,ARGV,Complex,cstime,cutime,Default,domain,E,EAI_ADDRFAMILY,EAI_AGAIN,EAI_BADFLAGS,EAI_BADHINTS,EAI_FAIL,EAI_FAMILY,EAI_MAX,EAI_MEMORY,EAI_NODATA,EAI_NONAME,EAI_PROTOCOL,EAI_SERVICE,EAI_SOCKTYPE,EAI_SYSTEM,expires,EXTENDED,FTP_PORT,IGNORECASE,IP_ADD_MEMBERSHIP,IP_DEFAULT_MULTICAST_LOOP,IP_DEFAULT_MULTICAST_TTL,IP_MAX_MEMBERSHIPS,IP_MULTICAST_IF,IP_MULTICAST_LOOP,IP_MULTICAST_TTL,LOOKUP_INET,LOOKUP_INET6,LOOKUP_UNSPEC,MSG_DONTROUTE,MSG_OOB,MSG_PEEK,MULTILINE,PF_APPLETALK,PF_AX25,PF_INET,PF_INET6,PF_IPX,PF_UNIX,PF_UNSPEC,PI,PLATFORM,PRIO_PGRP,PRIO_PROCESS,PRIO_USER,RUBY_PLATFORM,RUBY_RELEASE_DATE,RUBY_VERSION,secure,SO_BROADCAST,SO_DEBUG,SO_DONTROUTE,SO_ERROR,SO_KEEPALIVE,SO_LINGER,SO_NO_CHECK,SO_OOBINLINE,SO_PRIORITY,SO_RCVBUF,SO_REUSEADDR,SO_SNDBUF,SO_TYPE,SOCK_DGRAM,SOCK_PACKET,SOCK_RAW,SOCK_RDM,SOCK_SEQPACKET,SOCK_STREAM,SOL_ATALK,SOL_AX25,SOL_IP,SOL_IPX,SOL_SOCKET,SOL_TCP,SOL_UDP,SOPRI_BACKGROUND,SOPRI_INTERACTIVE,SOPRI_NORMAL,stime,TCP_MAXSEG,TCP_NODELAY,WIN32OLE,WNOHANG,WUNTRACED,yield,ZeroDivisionError,");
		bCaseSensitive = TRUE;
		break;
	case SYN_SQL:
		strWords = _T("bigint,binary,bit,boolean,char,character,cursor,date,datetime,decimal,float,image,int,integer,long,mlslabel,money,nchar,ntext,number,numeric,nvarchar,raw,real,rowid,smalldatetime,smallint,smallmoney,sql_variant,table,text,timestamp,tinyint,uniqueidentifier,varbinary,varchar,varchar2,varray,xml,");
		break;
	case SYN_ASP:
	case SYN_VB:
		strWords = _T("Boolean,Byte,Char,Date,DateTime,Decimal,Double,Integer,Int16,Int32,Int64,Long,Object,SByte,Short,Single,String,UInteger,UInt32,ULong,UInt64,UShort,UInt16,ValueType,");
		break;
	case SYN_VERILOG:
		strWords = _T("`accelerate,`autoexepand_vectornets,`celldefine,`default_nettype,`define,`default_decay_time,`default_trireg_strength,`delay_mode_distributed,`delay_mode_path,`delay_mode_unit,`delay_mode_zero,`else,`elsif,`endcelldefine,`endif,`endprotect,`endprotected,`expand_vectornets,`file,`ifdef,`ifndef,`include,`line,`noaccelerate,`noexpand_vectornets,`noremove_gatenames,`noremove_netnames,`nounconnected_drive,`protect,`protected,`remove_gatenames,`remove_netnames,`resetall,`timescale,`unconnected_drive,`undef,`uselib,$async$and$array,$async$and$plane,$async$nand$array,$async$nand$plane,$async$nor$array,$async$nor$plane,$async$or$array,$async$or$plane,$bitstoreal,$countdrivers,$display,$displayb,$displayh,$displayo,$dist_chi_square,$dist_erlang,$dist_exponential,$dist_normal,$dist_poisson,$dist_t,$dist_uniform,$dumpall,$dumpfile,$dumpflush,$dumplimit,$dumpoff,$dumpon,$dumpportsall,$dumpportsflush,$dumpportslimit,$dumpportsoff,$dumpportson,$dumpvars,$fclose,$fdisplayh,$fdisplay,$fdisplayf,$fdisplayb,$ferror,$fflush,$fgetc,$fgets,$finish,$fmonitorb,$fmonitor,$fmonitorf,$fmonitorh,$fopen,$fread,$fscanf,$fseek,$fsscanf,$fstrobe,$fstrobebb,$fstrobef,$fstrobeh,$ftel,$fullskew,$fwriteb,$fwritef,$fwriteh,$fwrite,$getpattern,")
			_T("$history,$hold,$incsave,$input,$itor,$key,$list,$log,$monitorb,$monitorh,$monitoroff,$monitoron,$monitor,$monitoro,$nochange,$nokey,$nolog,$period,$printtimescale,$q_add,$q_exam,$q_full,$q_initialize,$q_remove,$random,$readmemb,$readmemh,$realtime,$realtobits,$recovery,$recrem,$removal,$reset_count,$reset,$reset_value,$restart,$rewind,$rtoi,$save,$scale,$scope,$sdf_annotate,$setup,$setuphold,$sformat,$showscopes,$showvariables,$showvars,$signed,$skew,$sreadmemb,$sreadmemh,$stime,$stop,$strobeb,$strobe,$strobeh,$strobeo,$swriteb,$swriteh,$swriteo,$swrite,$sync$and$array,$sync$and$plane,$sync$nand$array,$sync$nand$plane,$sync$nor$array,$sync$nor$plane,$sync$or$array,$sync$or$plane,$test$plusargs,$time,$timeformat,$timeskew,$ungetc,$unsigned,$value$plusargs,$width,$writeb,$writeh,$write,$writeo,");
		bCaseSensitive = TRUE;
		break;
	case SYN_VHDL:
		strWords = _T("bit,bit_vector,boolean,,character,integer,line,natural,positive,real,signed,std_logic,std_logic_vector,string,text,time,unsigned,");
		break;
	}
}

void CSynLanguage::GetMultilineComment( CString &strBlockOpen, CString &strBlockClose, BOOL &bCaseSensitive )
{
	strBlockOpen = _T("");
	strBlockClose = _T("");
	bCaseSensitive = FALSE;
	switch (m_nLanguage)
	{
	case SYN_AUTOIT:
		strBlockOpen = _T("#CS");
		strBlockClose = _T("#CE");
		break;
	case SYN_ACTIONSCRIPT:
	case SYN_AUTOHOTKEY:
	case SYN_CPP:		
	case SYN_CS:
	case SYN_CSS:
	case SYN_D:
	case SYN_JAVA:
	case SYN_JAVASCRIPT:
	case SYN_JSP:
	case SYN_OBJECTIVEC:
	case SYN_PHP:
	case SYN_VERILOG:
		strBlockOpen = _T("/*");
		strBlockClose = _T("*/");
		break;
	case SYN_ASP:
	case SYN_HTML:
	case SYN_XML:
		strBlockOpen = _T("<!--");
		strBlockClose = _T("-->");
		break;
	case SYN_HASKELL:
		strBlockOpen = _T("{-");
		strBlockClose = _T("-}");
		break;
	case SYN_LISP:
		strBlockOpen = _T(";|");
		strBlockClose = _T("|;");
		break;
	case SYN_LUA:
		strBlockOpen = _T("--[[");
		strBlockClose = _T("]]");
		break;
	case SYN_PASCAL:
		strBlockOpen = _T("{");
		strBlockClose = _T("}");
		break;
	case SYN_RUBY:
		strBlockOpen = _T("=begin");
		strBlockClose = _T("=end");
		break;
	case SYN_SQL:
		strBlockOpen = _T("/*");
		strBlockClose = _T("*/");
		break;
	}
}

void CSynLanguage::GetLineComment( CString &strBlocks, BOOL &bCaseSensitive )
{
	strBlocks = _T("");
	bCaseSensitive = FALSE;
	switch (m_nLanguage)
	{
	case SYN_ASM:
	case SYN_AUTOHOTKEY:
	case SYN_AUTOIT:
	case SYN_INI:
	case SYN_LISP:
		strBlocks = _T(";,");
		break;
	case SYN_ASP:
		strBlocks = _T("',");
		break;
	case SYN_COBOL:
		strBlocks = _T("*,/,");
		break;
	case SYN_ACTIONSCRIPT:
	case SYN_CPP:		
	case SYN_CS:
	case SYN_D:
	case SYN_JAVA:
	case SYN_JAVASCRIPT:	
	case SYN_JSP:
	case SYN_OBJECTIVEC:
	case SYN_PASCAL:
	case SYN_VERILOG:
		strBlocks = _T("//,");
		break;
	case SYN_PERL:
	case SYN_PYTHON:
	case SYN_RUBY:
		strBlocks = _T("#,");
		break;
	case SYN_ADA:
	case SYN_HASKELL:
	case SYN_LUA:
	case SYN_SQL:
	case SYN_VHDL:
		strBlocks = _T("--,");
		break;	
	case SYN_BATCH:
		strBlocks = _T("REM,::,Rem,rem,");
		break;
	case SYN_VB:
		strBlocks = _T("REM,',Rem,rem,");
		break;	
	case SYN_FORTRAN:
		strBlocks = _T("!,");
		break;
	case SYN_PHP:
		strBlocks = _T("//,#,");
		break;
	}
}

void CSynLanguage::GetString( CString &strBlockOpen, CString &strBlockClose, BOOL &bCaseSensitive )
{
	strBlockOpen = _T("");
	strBlockClose = _T("");
	bCaseSensitive = FALSE;
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
	case SYN_ADA:
	case SYN_ASM:
	case SYN_ASP:
	case SYN_AUTOHOTKEY:
	case SYN_AUTOIT:
	case SYN_BATCH:
	case SYN_COBOL:
	case SYN_CPP:
	case SYN_CS:
	case SYN_CSS:
	case SYN_D:
	case SYN_FORTRAN:
	case SYN_HASKELL:
	case SYN_HTML:
	case SYN_JAVA:
	case SYN_JAVASCRIPT:
	case SYN_JSON:
	case SYN_JSP:
	case SYN_LISP:
	case SYN_LUA:
	case SYN_OBJECTIVEC:
	case SYN_PASCAL:
	case SYN_PERL:
	case SYN_PHP:
	case SYN_PYTHON:
	case SYN_RUBY:
	case SYN_SQL:
	case SYN_VB:
	case SYN_VERILOG:
	case SYN_VHDL:
	case SYN_XML:
		strBlockOpen = _T("\"");
		strBlockClose = _T("\"");
		break;
	case SYN_INI:
		strBlockOpen = _T("[");
		strBlockClose = _T("]");
		break;
	}
}

void CSynLanguage::GetChar( CString &strBlockOpen, CString &strBlockClose, BOOL &bCaseSensitive )
{
	strBlockOpen = _T("");
	strBlockClose = _T("");
	bCaseSensitive = FALSE;
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
	case SYN_ASM:
	case SYN_AUTOIT:
	case SYN_COBOL:
	case SYN_CPP:		
	case SYN_CS:
	case SYN_CSS:
	case SYN_D:
	case SYN_FORTRAN:
	case SYN_HTML:
	case SYN_JAVA:
	case SYN_JAVASCRIPT:
	case SYN_JSP:
	case SYN_LUA:
	case SYN_OBJECTIVEC:
	case SYN_PASCAL:
	case SYN_PERL:
	case SYN_PYTHON:
	case SYN_PHP:
	case SYN_RUBY:
	case SYN_SQL:
	case SYN_VHDL:
		strBlockOpen = _T("'");
		strBlockClose = _T("'");
		break;
	}
}

void CSynLanguage::GetIsNumberColor( BOOL &bNumberColor )
{
	bNumberColor = TRUE;
	switch (m_nLanguage)
	{
	case SYN_INI:
	case SYN_NORMALTEXT:
		bNumberColor = FALSE;
		break;
	}
}

BOOL CSynLanguage::GetOutlineCaseSensitive()
{
	BOOL bCaseSensitive = FALSE;
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
	case SYN_CPP:
	case SYN_CS:
	case SYN_D:
	case SYN_HASKELL:
	case SYN_JAVA:
	case SYN_JAVASCRIPT:
	case SYN_JSP:
	case SYN_LUA:
	case SYN_OBJECTIVEC:
	case SYN_PERL:
	case SYN_VERILOG:
		bCaseSensitive = TRUE;
		break;
	}
	return bCaseSensitive;
}

BOOL CSynLanguage::GetOutlineWholeWords()
{
	BOOL bWholeWords = TRUE;
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
	case SYN_CPP:
	case SYN_CS:
	case SYN_D:
	case SYN_HASKELL:
	case SYN_JAVA:
	case SYN_JAVASCRIPT:
	case SYN_JSP:
	case SYN_LUA:
	case SYN_OBJECTIVEC:
	case SYN_PERL:
	case SYN_VERILOG:
		bWholeWords = FALSE;
		break;
	}
	return bWholeWords;
}

void CSynLanguage::GetOutlineEscapeSequences( CString &strEscapeSequences )
{
	strEscapeSequences = _T("");
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
	case SYN_ASM:
	case SYN_AUTOIT:
	case SYN_CPP:
	case SYN_CS:
	case SYN_D:
	case SYN_HASKELL:
	case SYN_JAVA:
	case SYN_JSP:
	case SYN_LUA:
	case SYN_OBJECTIVEC:
	case SYN_PASCAL:
	case SYN_PERL:
	case SYN_PHP:
	case SYN_VB:
	case SYN_VERILOG:
		strEscapeSequences = _T("\\\",\\\\,");
		break;
	case SYN_JAVASCRIPT:
	case SYN_SQL:
		strEscapeSequences = _T("\\\",\\\\,\\',");
		break;
	case SYN_AUTOHOTKEY:
		strEscapeSequences = _T("\\\",\\`,");
		break;
	}
}

void CSynLanguage::GetOutlineBlockType( CString &strBlocks )
{
	strBlocks.Empty();
	switch (m_nLanguage)
	{
	case SYN_ACTIONSCRIPT:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,switch,catch,try,for,class,if,union,do,while,namespace,package,|");
		break;
	case SYN_ASM:
		strBlocks = _T("\",\",\"\",0,1,|;,\n,;...,0,1,|MACRO,ENDM,MACRO ...,1,0,|STRUCT,ENDSTRUCT,STRUCT ...,1,0,|IF,ENDIF,IF ... ENDIF,1,0,|SWITCH,ENDCASE,SWITCH ... CASE ... ENDCASE,1,1,|SECTION,ENDSECTION,SECTION ...,1,0,|SEGMENT,ENDS,SEGMENT ...,1,0,|PROC,ENDP,PROC ...,1,0,|");
		break;
	case SYN_ASP:
		strBlocks = _T("\",\",\"\",0,1,|',\n,Comment,0,1,|");
		break;
	case SYN_AUTOHOTKEY:
		strBlocks = _T("\",\",\"\",0,1,|;,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,if,loop,while,|");
		break;
	case SYN_AUTOIT:
		strBlocks = _T("\",\",\"\",0,1,|;,\n,;...,0,1,|#CS,#CE,#Comment,0,0,|#comments-start,#comments-end,#Comment,0,0,|IF,ENDIF,If ... Then ... EndIf,1,0,|Select,EndSelect,Select ... EndSelect,1,0,|Switch,EndSwitch,Switch ... EndSwitch,1,0,|FOR,NEXT,For ... Next ...,1,0,|WHILE,WEND,While ... WEnd,1,0,|DO,Until,Do ... Until ...,1,0,|Func,EndFunc,Func ... EndFunc,1,0,|");
		break;
	case SYN_CPP:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,struct,enum,switch,catch,try,for,foreach,operator,class,if,union,do,while,namespace,|");
		break;
	case SYN_CS:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,struct,enum,switch,catch,try,for,foreach,operator,class,if,union,do,while,namespace,|#region,#endregion,#region,1,0,|");
		break;
	case SYN_CSS:
		strBlocks = _T("\",\",\"\",0,1,|/*,*/,/**/,0,0,|{,},...,1,0,|");
		break;
	case SYN_D:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,struct,enum,switch,catch,try,finally,for,foreach,foreach_reverse,operator,class,if,union,do,while,with,|");
		break;
	case SYN_FORTRAN:
		strBlocks = _T("\",\",\"\",0,1,|!,\n,!...,0,1,|do,enddo,do ... enddo,1,0,|if,endif,if ... endif,1,0,|do,end do,do ... enddo,1,0,|if,end if,if ... endif,1,0,|FUNCTION,END FUNCTION,FUNCTION ... END FUNCTION,1,0,|MODULE,END MODULE,MODULE ... END MODULE,1,0,|PROGRAM,END PROGRAM,PROGRAM ... END PROGRAM,1,0,|SUBROUTINE,END SUBROUTINE,SUBROUTINE ... END SUBROUTINE,1,0,|SELECT,END SELECT,SELECT ... END SELECT,1,0,|");
		break;
	case SYN_HASKELL:
		strBlocks = _T("\",\",\"\",0,1,|--,\n,{- Comment -},0,1,|{-,-},{- Comment -},0,0,|");
		break;
	case SYN_JAVA:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,enum,switch,catch,try,for,operator,class,if,do,while,|");
		break;
	case SYN_JAVASCRIPT:
		strBlocks = _T("\",\",\"\",0,1,|',',\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,function,class,do,while,for,enum,package,if,else,enum,switch,catch,try,|@if,@end,@if...@end,1,0,|/*@,@*/,/*@...@*/,1,0,|");
		break;
	case SYN_JSON:
		strBlocks = _T("\",\",\"\",0,1,|{,},{ ... },1,0,|[,],[ ... ],1,0,|");
		break;
	case SYN_JSP:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,enum,switch,catch,try,for,operator,class,if,do,while,|");
		break;
	case SYN_LUA:
		strBlocks = _T("\",\",\"\",0,1,|--,\n,--[[ ... ]],0,1,|--[[,]],--[[ ... ]],0,0,|do,end,do ... end,1,0,while,for,|function,end,function ... end,1,0,|if,end,if ... end,1,0,|while,end,while ... end,1,0,|for,end,for ... end,1,0,|repeat,until,repeat ... until,1,0,|");
		break;
	case SYN_OBJECTIVEC:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,struct,enum,switch,catch,try,for,foreach,operator,class,if,union,do,while,namespace,|");
		break;
	case SYN_PASCAL:
		strBlocks = _T("',',\"\",0,1,|{,},{... Comment ...},1,1,|begin,end,begin ... end,1,0,procedure,function,for,if,else,do,while,with,|repeat,until,repeat ... until,1,0,|");
		break;
	case SYN_PERL:
		strBlocks = _T("\",\",\"\",0,1,|#,\n,###,0,1,|{,},...,1,0,if,while,foreach,sub,unless,for,|");
		break;
	case SYN_PHP:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|{,},...,1,0,else,enum,switch,catch,try,for,operator,class,if,do,while,function,|");
		break;
	case SYN_SQL:
		strBlocks = _T("\",\",\"\",0,1,|--,\n,/**/,0,1,|/*,*/,/**/,0,0,|',',\"\",0,1,|begin,end,begin ... end,1,0,|case,end,case ... end,1,0,|");
		break;
	case SYN_VB:
		strBlocks = _T("\",\",\"\",0,1,|',\n,Comment,0,1,|rem,\n,Comment,0,1,|IF,END IF,If ... Then ... End If,1,0,|DO,LOOP,Do ... Loop ...,1,0,|FOR,NEXT,For ... Next ...,1,0,|SELECT CASE,END SELECT,Select Case ... End Select,1,0,|WHILE,END WHILE,While ... End While,1,0,|USING,END USING,Using ... End Using,1,0,|WITH,END WITH,With ... End With,1,0,|TRY,END TRY,Try ... End Try,1,0,|SYNCLOCK,END SYNCLOCK,SyncLock ... End SyncLock,1,0,|SUB,END SUB,Sub ... End Sub,1,0,|FUNCTION,END FUNCTION,Function ... End Function,1,0,|CLASS,END CLASS,Class ... End Class,1,0,|STRUCTURE,END STRUCTURE,Structure ... End Structure,1,0,|ENUM,END ENUM,Enum ... End Enum,1,0,|OPERATOR,END OPERATOR,Operator ... End Operator,1,0,|PROPERTY,END PROPERTY,Property ... End Property,1,0,|INTERFACE,END INTERFACE,Interface ... End Interface,1,0,|MODULE,END MODULE,Module ... End Module,1,0,|NAMESPACE,END NAMESPACE,Namespace ... End Namespace,1,0,|#IF,#END IF,#If ... Then ... #End If,1,0,|#REGION,#END REGION,#Region,1,0,|'{\n,'},{... User block ...},1,0,|");
		break;
	case SYN_VERILOG:
		strBlocks = _T("\",\",\"\",0,1,|//,\n,/**/,0,1,|/*,*/,/**/,0,0,|case,endcase,case ... endcase,1,0,|fork,join,fork ... join,1,0,|specify,endspecify,specify ... endspecify,1,0,|table,endtable,table ... endtable,1,0,|config,endconfig,config ... endconfig,1,0,|module,endmodule,module ... endmodule,1,0,|task,endtask,task,1,0,|function,endfunction,function ... endfunction,1,0,|generate,endgenerate,generate ... endgenerate,1,0,|primitive,endprimitive,primitive ... endprimitive,1,0,|begin,end,begin ... end,1,0,|`ifdef,`endif,`ifdef ... `endif,1,0,|");
		break;
	case SYN_VHDL:
		strBlocks = _T("\",\",\"\",0,1,|--,\n,/**/,0,1,|',','...',0,1,|(,),( ... ),1,0,|loop,end loop,loop ... end,1,0,|process,end process,process ... end,1,0,|component,end component,component ... end,1,0,|if,end if,if ... end,1,0,|case,end case,case ... end,1,0,|block,end block,block ... end,1,0,|fold,end fold,fold ... end,1,0,|");
		break;
	}
}
