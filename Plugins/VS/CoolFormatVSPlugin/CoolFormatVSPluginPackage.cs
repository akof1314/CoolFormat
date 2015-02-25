using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.ComponentModel.Design;
using System.Text;
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
            NativeMethods.ShowSettings();
        }

        private void DoFormat(bool selected)
        {
            if (_dte == null || _dte.ActiveDocument == null)
            {
                return;
            }

            string text = "";
            string initIndent = "";
            EditPoint sp;
            EditPoint sd;
            if (selected)
            {
                TextSelection sel = (TextSelection) _dte.ActiveDocument.Selection;
                sp = sel.TopPoint.CreateEditPoint();
                sd = sel.BottomPoint.CreateEditPoint();
                sel.MoveToLineAndOffset(sp.Line, 1);
                sel.MoveToLineAndOffset(sd.Line, 1, true);
                sel.EndOfLine(true);
                sp = sel.TopPoint.CreateEditPoint();
                sd = sel.BottomPoint.CreateEditPoint();
                text = sel.Text;

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
                TextDocument doc = (TextDocument) _dte.ActiveDocument.Object("TextDocument");
                sp = doc.StartPoint.CreateEditPoint();
                sd = doc.EndPoint.CreateEditPoint();
                text = sp.GetText(sd);
            }

            if (String.IsNullOrEmpty(text))
            {
                return;
            }

            string eol = GetEol(text);
            int lang = GetLanguage();
            int sizeOut = 0;
            int sizeMsg = 0;
            if (NativeMethods.DoFormatter(lang, text, null, ref sizeOut, null, ref sizeMsg, 0, eol, initIndent))
            {
                StringBuilder textOut = new StringBuilder(sizeOut);
                StringBuilder textMsg = new StringBuilder(sizeMsg);
                if (NativeMethods.DoFormatter(lang, text, textOut, ref sizeOut, textMsg, ref sizeMsg, 0, eol, initIndent))
                {
                    ShowOutput(textMsg.ToString());
                    sp.ReplaceText(sd, textOut.ToString(), (int)vsEPReplaceTextOptions.vsEPReplaceTextKeepMarkers);
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
            _outputPane.Clear();
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

        private string GetEol(string text)
        {
            string eolWin = "\r\n";
            string eolMac = "\r";
            string eolUnix = "\n";
            if (!String.IsNullOrEmpty(text))
            {
                if (text.IndexOf(eolWin) != -1)
                {
                    return eolWin;
                }
                if (text.IndexOf(eolUnix) != -1)
                {
                    return eolUnix;
                }
                if (text.IndexOf(eolMac) != -1)
                {
                    return eolMac;
                }
            }
            return eolWin;
        }

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

    internal static class NativeMethods
    {
        [DllImport("CoolFormatLib/cf_windows_x32/CoolFormatLib", CharSet = CharSet.Ansi, BestFitMapping = false, ThrowOnUnmappableChar = true, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool DoFormatter(
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

        [DllImport("CoolFormatLib/cf_windows_x32/CoolFormatLib", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool ShowSettings();
    }
}
