//	Copyright (c) 1998-2011 BCGSoft Co Ltd. 
//	All rights reserved.
//	Visit us:	http://www.bcgsoft.com
//	E-mail: 	mailto:info@bcgsoft.com
//
//	The static example code includes self-test notes in comments
//	Note to improved noticeable syntax coloring测试中文的

#include "stdafx.h"         //  To set or remove a bookmark at the current line
                            //  click on the Edit toolbar, Toggle Bookmark ('Ctrl'+'F2');
#include <windows.h>
#include <stdio.h>          //  To move the cursor between bookmarks click on the
#include <conio.h>          //  Edit toolbar, Next Bookmark and Previous Bookmark

#define DO_TRACE(bTrace, lpszText)  { if (bTrace) { printf("%s\n",lpszText); } }

class CMyClass              //  To find the text use find combo box on the Standard toolbar
{                           //  or click on the Edit toolbar, Find ('Ctrl'+'F')
public:
    CMyClass(): m_bTrace(FALSE)
    {
        memset(&m_lf,0,sizeof(LOGFONT));
    }
    ~CMyClass()
    {                       //  To set or remove breakpoint (bookmark) click
        OnDestroy();        //  on the Build toolbar, Insert/Remove Breakpoint ('F9')
    }
    int DoMain()            //  To remove all breakpoints click on the Build toolbar,
    {                       //  Remove All Breakpoints
        DO_TRACE(m_bTrace,"CMyClass::DoMain ()");
        return 0;
    }
    const char* GetAppName() const  { return "Example.exe"; }
    inline void EnableTrace(BOOL bTrace = TRUE)  { m_bTrace = bTrace; }

protected:                  //  To change indentation of the text select lines and
            BOOL m_bTrace;  //  click on the Edit toolbar, Increase Ident ('Tab')
            LOGFONT m_lf;   //  or Decrease Indent ('Shift'+'Tab') to increase or
                            //  decrease the left indent of the lines
            virtual void OnDestroy()
            {               //  To look definition of a symbol just set mouse focus on it
                DO_TRACE(m_bTrace, "CMyClass::OnDestroy ()");
            }               //  To find out the class members' names type
};                          //  "this->" to open class members' popup list

int main()
//	The entry point for the console application
{
    CMyClass* pMyClass = new CMyClass();    //  To find out the class/struct
                                            //  members' names simple strike '.'
    DO_TRACE(TRUE, pMyClass->GetAppName()); //  after typing its name or just
    int nRet = pMyClass->DoMain();          //  press 'Ctrl'+'Alt'+'T'
    
    delete pMyClass;                        //  To find out the CMyClass->m_lf members'
                                            //  names type "pMyClass->m_lf." to open
    return nRet;                            //  class members' popup list
}
