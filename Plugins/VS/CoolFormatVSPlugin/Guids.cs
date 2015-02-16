// Guids.cs
// MUST match guids.h
using System;

namespace WuHuan.CoolFormatVSPlugin
{
    static class GuidList
    {
        public const string guidCoolFormatVSPluginPkgString = "a05fbe56-d5ad-489f-aaed-a2559ba2062c";
        public const string guidCoolFormatVSPluginCmdSetString = "ec7af48e-bad1-4f7c-9465-43623a7739ea";

        public static readonly Guid guidCoolFormatVSPluginCmdSet = new Guid(guidCoolFormatVSPluginCmdSetString);
    };
}