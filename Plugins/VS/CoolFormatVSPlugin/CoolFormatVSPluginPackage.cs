using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.ComponentModel.Design;
using System.Text;
using Microsoft.VisualStudio.TextManager.Interop;
using Microsoft.Win32;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio.OLE.Interop;
using Microsoft.VisualStudio.Shell;
using EnvDTE;

namespace WuHuan.CoolFormatVSPlugin
{
    /// <summary>
    /// This is the class that implements the package exposed by this assembly.
    ///
    /// The minimum requirement for a class to be considered a valid package for Visual Studio
    /// is to implement the IVsPackage interface and register itself with the shell.
    /// This package uses the helper classes defined inside the Managed Package Framework (MPF)
    /// to do it: it derives from the Package class that provides the implementation of the 
    /// IVsPackage interface and uses the registration attributes defined in the framework to 
    /// register itself and its components with the shell.
    /// </summary>
    // This attribute tells the PkgDef creation utility (CreatePkgDef.exe) that this class is
    // a package.
    [PackageRegistration(UseManagedResourcesOnly = true)]
    // This attribute is used to register the information needed to show this package
    // in the Help/About dialog of Visual Studio.
    [InstalledProductRegistration("#110", "#112", "1.0", IconResourceID = 400)]
    // This attribute is needed to let the shell know that this package exposes some menus.
    [ProvideMenuResource("Menus.ctmenu", 1)]
    [Guid(GuidList.guidCoolFormatVSPluginPkgString)]
    public sealed class CoolFormatVSPluginPackage : Package
    {
        private DTE _dte;

        private IVsTextManager _txtMngr;

        private OutputWindowPane _outputPane;

        /// <summary>
        /// Default constructor of the package.
        /// Inside this method you can place any initialization code that does not require 
        /// any Visual Studio service because at this point the package object is created but 
        /// not sited yet inside Visual Studio environment. The place to do all the other 
        /// initialization is the Initialize method.
        /// </summary>
        public CoolFormatVSPluginPackage()
        {
        }

        /////////////////////////////////////////////////////////////////////////////
        // Overridden Package Implementation
        #region Package Members

        /// <summary>
        /// Initialization of the package; this method is called right after the package is sited, so this is the place
        /// where you can put all the initialization code that rely on services provided by VisualStudio.
        /// </summary>
        protected override void Initialize()
        {
            base.Initialize();

            // Add our command handlers for menu (commands must exist in the .vsct file)
            OleMenuCommandService mcs = GetService(typeof(IMenuCommandService)) as OleMenuCommandService;
            if ( null != mcs )
            {
                // Create the command for the menu item.
                CommandID menuCommandID = new CommandID(GuidList.guidCoolFormatVSPluginCmdSet, (int)PkgCmdIDList.cmdidQuickFormat);
                MenuCommand menuItem = new MenuCommand(MenuQuickFormat, menuCommandID);
                mcs.AddCommand( menuItem );
                menuCommandID = new CommandID(GuidList.guidCoolFormatVSPluginCmdSet, (int)PkgCmdIDList.cmdidSelectedFormat);
                menuItem = new MenuCommand(MenuSelectedFormat, menuCommandID);
                mcs.AddCommand(menuItem);
                menuCommandID = new CommandID(GuidList.guidCoolFormatVSPluginCmdSet, (int)PkgCmdIDList.cmdidFormatterSetting);
                menuItem = new MenuCommand(MenuFormatterSetting, menuCommandID);
                mcs.AddCommand(menuItem);
            }

            _dte = (DTE) GetService(typeof (DTE));
            _txtMngr = (IVsTextManager) GetService(typeof (SVsTextManager));
        }
        #endregion

        /// <summary>
        /// This function is the callback used to execute a command when the a menu item is clicked.
        /// See the Initialize method to see how the menu item is associated to this function using
        /// the OleMenuCommandService service and the MenuCommand class.
        /// </summary>
        private void MenuQuickFormat(object sender, EventArgs e)
        {
            DoFormat(false);
        }

        private void MenuSelectedFormat(object sender, EventArgs e)
        {
            DoFormat(true);
        }

        private void MenuFormatterSetting(object sender, EventArgs e)
        {
            // Show a Message Box to prove we were here
            IVsUIShell uiShell = (IVsUIShell)GetService(typeof(SVsUIShell));
            Guid clsid = Guid.Empty;
            int result;
            Microsoft.VisualStudio.ErrorHandler.ThrowOnFailure(uiShell.ShowMessageBox(
                       0,
                       ref clsid,
                       "CoolFormatVSPlugin",
                       string.Format(CultureInfo.CurrentCulture, "Inside {0}.MenuItemCallback()", this.ToString()),
                       string.Empty,
                       0,
                       OLEMSGBUTTON.OLEMSGBUTTON_OK,
                       OLEMSGDEFBUTTON.OLEMSGDEFBUTTON_FIRST,
                       OLEMSGICON.OLEMSGICON_INFO,
                       0,        // false
                       out result));
        }

        private void DoFormat(bool selected)
        {
            if (_dte == null || _dte.ActiveDocument == null)
            {
                return;
            }

            string text = "";
            string initIndent = "";
            if (selected)
            {
                TextSelection sel = (TextSelection)_dte.ActiveDocument.Selection;
                //int bottomLine = sel.BottomPoint.Line;
                //for (int i = sel.TopPoint.Line; i <= bottomLine; i++)
                //{
                //    sel.GotoLine(i, true);
                //    text += sel.Text;
                //}
                EditPoint sp = sel.TopPoint.CreateEditPoint();
                text = sp.GetLines(sp.Line, sel.BottomPoint.Line + 1);

                foreach (var ch in text)
                {
                    if (ch != ' ' && ch != '\t')
                    {
                        break;
                    }
                    initIndent += ch;
                }
            }
            else
            {
                TextDocument doc = (TextDocument)_dte.ActiveDocument.Object("TextDocument");
                EditPoint sp = doc.StartPoint.CreateEditPoint();
                text = sp.GetText(doc.EndPoint);
            }

            if (String.IsNullOrEmpty(text))
            {
                return;
            }

            string eol = "\r\n";
            int lang = GetLanguage();
            int sizeOut = 0;
            int sizeMsg = 0;
            if (DoFormatter(lang, text, null, ref sizeOut, null, ref sizeMsg, 0, eol, initIndent))
            {
                StringBuilder textOut = new StringBuilder(sizeOut);
                StringBuilder textMsg = new StringBuilder(sizeMsg);
                if (DoFormatter(lang, text, textOut, ref sizeOut, textMsg, ref sizeMsg, 0, eol, initIndent))
                {
                    ShowOutput(textMsg.ToString());
                    if (selected)
                    {

                    }
                    else
                    {
                        TextDocument doc = (TextDocument)_dte.ActiveDocument.Object("TextDocument");
                        EditPoint sp = doc.StartPoint.CreateEditPoint();
                        sp.ReplaceText(doc.EndPoint, textOut.ToString(), (int)vsEPReplaceTextOptions.vsEPReplaceTextKeepMarkers);
                    }
                }
            }
        }

        private void ShowOutput(string output)
        {
            if (String.IsNullOrEmpty(output))
            {
                return;
            }

            if (_outputPane == null)
            {
                Window window = _dte.Windows.Item(EnvDTE.Constants.vsWindowKindOutput);
                OutputWindow outputWindow = (OutputWindow) window.Object;
                _outputPane = outputWindow.OutputWindowPanes.Add("CoolFormat");
            }
            _outputPane.Activate();
            _outputPane.OutputString(output);
        }

        private static readonly Dictionary<string, Syn_Language> DictLang = new Dictionary<string, Syn_Language>()
        {
            {"gcc", Syn_Language.SYN_CPP},
            {"avrgcc", Syn_Language.SYN_CPP},
            {"c/c++", Syn_Language.SYN_CPP},
            {"csharp", Syn_Language.SYN_CS},
            {"htmlx", Syn_Language.SYN_HTML},
            {"html", Syn_Language.SYN_HTML},
            {"xml", Syn_Language.SYN_XML},
            {"javascript", Syn_Language.SYN_JAVASCRIPT},
            {"css", Syn_Language.SYN_CSS},
            {"java", Syn_Language.SYN_JAVA},
            {"json", Syn_Language.SYN_JSON},
            {"m", Syn_Language.SYN_OBJECTIVEC},
            {"php", Syn_Language.SYN_PHP},
            {"sql", Syn_Language.SYN_SQL}
        };

        private int GetLanguage()
        {
            string lang = _dte.ActiveDocument.Language.ToLower();
            if (DictLang.ContainsKey(lang))
            {
                return (int)DictLang[lang];
            }
            lang = Path.GetExtension(_dte.ActiveDocument.Name);
            if (!String.IsNullOrEmpty(lang))
            {
                lang = lang.Remove(0, 1);
                lang = lang.ToLower();
                if (DictLang.ContainsKey(lang))
                {
                    return (int)DictLang[lang];
                }
            }
            return -1;
        }

        private string GetEol()
        {
            IVsTextView textViewCurrent;
            _txtMngr.GetActiveView(1, null, out textViewCurrent);
            return "";
        }

        [DllImport("CoolFormatLib/cf_windows_x32/CoolFormatLib", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool DoFormatter(
            int nLanguage,
            [MarshalAs(UnmanagedType.LPStr)]
            String pszTextIn,
            [MarshalAs(UnmanagedType.LPStr)]
	        StringBuilder pszTextOut,
	        ref int nTextOut,
            [MarshalAs(UnmanagedType.LPStr)]
	        StringBuilder pszMsgOut,
	        ref int nMsgOut,
	        int uCodepage,
            [MarshalAs(UnmanagedType.LPStr)]
	        String pszEol,
            [MarshalAs(UnmanagedType.LPStr)]
	        String pszInitIndent
        );

        enum Syn_Language
        {
            SYN_ACTIONSCRIPT,
            SYN_ADA,
            SYN_ASM,
            SYN_ASP,
            SYN_AUTOHOTKEY,
            SYN_AUTOIT,
            SYN_BATCH,
            SYN_COBOL,
            SYN_CPP,
            SYN_CS,
            SYN_CSS,
            SYN_D,
            SYN_FORTRAN,
            SYN_HASKELL,
            SYN_HTML,
            SYN_INI,
            SYN_JAVA,
            SYN_JAVASCRIPT,
            SYN_JSON,
            SYN_JSP,
            SYN_LISP,
            SYN_LUA,
            SYN_NORMALTEXT,
            SYN_OBJECTIVEC,
            SYN_PASCAL,
            SYN_PERL,
            SYN_PHP,
            SYN_PYTHON,
            SYN_RUBY,
            SYN_SQL,
            SYN_VB,
            SYN_VERILOG,
            SYN_VHDL,
            SYN_XML
        }
    }
}
